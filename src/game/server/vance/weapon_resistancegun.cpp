#include "cbase.h"
#include "npcevent.h"
#include "vance_baseweapon_shared.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "gamerules.h"
#include "in_buttons.h"
#include "soundent.h"
#include "game.h"
#include "vstdlib/random.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar sk_alyxgun_burst_rate( "sk_alyxgun_burst_rate", "0.05", FCVAR_CHEAT );
ConVar sk_alyxgun_burst_damage( "sk_alyxgun_burst_damage", "5.0", FCVAR_CHEAT );

ConVar sk_alyxgun_semiauto_damage( "sk_alyxgun_semiauto_damage", "15.0", FCVAR_CHEAT );

//-----------------------------------------------------------------------------
// CWeaponResistanceGun
//-----------------------------------------------------------------------------

class CWeaponResistanceGun : public CBaseVanceWeapon
{
	DECLARE_CLASS(CWeaponResistanceGun, CBaseVanceWeapon);
	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();
	DECLARE_ACTTABLE();

public:

	CWeaponResistanceGun();

	virtual bool		Deploy();
	virtual bool		Holster(CBaseCombatWeapon* pSwitchingTo);

	virtual void		Spawn();
	void				DryFire();
	
	void				BurstThink();

	virtual void		PrimaryAttack();
	virtual void		SecondaryAttack();

	virtual void		ItemPostFrame();
	void				AddViewKick();

	virtual Activity	GetIdleActivity() { return !m_bSemiAutoMode ? ACT_VM_IDLE : ACT_VM_IDLE_EXTENDED; }
	virtual Activity	GetWalkActivity() { return !m_bSemiAutoMode ? ACT_VM_WALK : ACT_VM_WALK_EXTENDED; }
	virtual Activity	GetSprintActivity() { return !m_bSemiAutoMode ? ACT_VM_SPRINT : ACT_VM_SPRINT_EXTENDED; }
	virtual bool		SendWeaponAnim( int iActivity );

	virtual bool		CanAttackWhileZoomed() { return m_bSemiAutoMode; }

private:
	float	m_flSoonestPrimaryAttack;
	float	m_flLastAttackTime;

	bool	m_bSemiAutoMode;
	float	m_flDoneSwitchingMode;

	bool	m_bInBurst;
	int		m_nBurstShot;
	bool	m_bInTransition;
};


IMPLEMENT_SERVERCLASS_ST(CWeaponResistanceGun, DT_WeaponResistanceGun)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_resistancegun, CWeaponResistanceGun);
PRECACHE_WEAPON_REGISTER(weapon_resistancegun);

BEGIN_DATADESC(CWeaponResistanceGun)
	DEFINE_FIELD(m_flSoonestPrimaryAttack, FIELD_TIME),
	DEFINE_FIELD(m_flLastAttackTime, FIELD_TIME),
	DEFINE_FIELD(m_bSemiAutoMode, FIELD_BOOLEAN),
	DEFINE_THINKFUNC(BurstThink),
END_DATADESC()

acttable_t CWeaponResistanceGun::m_acttable[] = {
	{ ACT_IDLE, ACT_IDLE_PISTOL, true },
	{ ACT_IDLE_ANGRY, ACT_IDLE_ANGRY_PISTOL, true },
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_PISTOL, true },
	{ ACT_RELOAD, ACT_RELOAD_PISTOL, true },
	{ ACT_WALK_AIM, ACT_WALK_AIM_PISTOL, true },
	{ ACT_RUN_AIM, ACT_RUN_AIM_PISTOL, true },
	{ ACT_GESTURE_RANGE_ATTACK1, ACT_GESTURE_RANGE_ATTACK_PISTOL, true },
	{ ACT_RELOAD_LOW, ACT_RELOAD_PISTOL_LOW, false },
	{ ACT_RANGE_ATTACK1_LOW, ACT_RANGE_ATTACK_PISTOL_LOW, false },
	{ ACT_COVER_LOW, ACT_COVER_PISTOL_LOW, false },
	{ ACT_RANGE_AIM_LOW, ACT_RANGE_AIM_PISTOL_LOW, false },
	{ ACT_GESTURE_RELOAD, ACT_GESTURE_RELOAD_PISTOL, false },
	{ ACT_WALK, ACT_WALK_PISTOL, false },
	{ ACT_RUN, ACT_RUN_PISTOL, false },
	{ ACT_HL2MP_IDLE, ACT_HL2MP_IDLE_PISTOL, false },
	{ ACT_HL2MP_RUN, ACT_HL2MP_RUN_PISTOL, false },
	{ ACT_HL2MP_IDLE_CROUCH, ACT_HL2MP_IDLE_CROUCH_PISTOL, false },
	{ ACT_HL2MP_WALK_CROUCH, ACT_HL2MP_WALK_CROUCH_PISTOL, false },
	{ ACT_HL2MP_GESTURE_RANGE_ATTACK, ACT_HL2MP_GESTURE_RANGE_ATTACK_PISTOL, false },
	{ ACT_HL2MP_GESTURE_RELOAD, ACT_HL2MP_GESTURE_RELOAD_PISTOL, false },
	{ ACT_HL2MP_JUMP, ACT_HL2MP_JUMP_PISTOL, false },
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_PISTOL, false },
};
IMPLEMENT_ACTTABLE( CWeaponResistanceGun );

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponResistanceGun::CWeaponResistanceGun()
{
	m_flSoonestPrimaryAttack = gpGlobals->curtime; // stupid hack to make the weapon not fire when you pick it up

	m_fMinRange1 = 24;
	m_fMaxRange1 = 1500;
	m_fMinRange2 = 24;
	m_fMaxRange2 = 200;

	m_bFiresUnderwater = false;

	m_bSemiAutoMode = false;
	m_bInTransition = false;
	m_flDoneSwitchingMode = 0.0f;

	m_bInBurst = false;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::Spawn()
{
	m_bInTransition = false;
	m_flDoneSwitchingMode = 0.0f;

	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::DryFire()
{
	WeaponSound( EMPTY );
	SendWeaponAnim( ACT_VM_DRYFIRE );
}

//-----------------------------------------------------------------------------
// Purpose: Handles burst fire
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::BurstThink()
{
	const int BURST_SIZE = 3;

	CBasePlayer *pPlayer = ToBasePlayer( GetOwner() );
	if ( !pPlayer )
		return;

	if ( m_iClip1 <= 0 || m_nBurstShot == BURST_SIZE )
	{
		if ( m_nBurstShot != BURST_SIZE )
		{
			DryFire();
		}

		m_flSoonestPrimaryAttack = gpGlobals->curtime + 0.4f;
		m_flNextPrimaryAttack = gpGlobals->curtime + 0.4f;
		m_nBurstShot = 0;
		m_bInBurst = false;
		SetNextThink(TICK_NEVER_THINK); // We're out of ammo, end of burst.
		return;
	}

	Vector vecShootOrigin = pPlayer->Weapon_ShootPosition();
	Vector vecShootDir;
	pPlayer->EyeVectors( &vecShootDir );
	Vector vecSpread = m_nBurstShot == 0 ? VECTOR_CONE_PRECALCULATED : VECTOR_CONE_4DEGREES;

	FireBulletProjectiles(1, vecShootOrigin, vecShootDir, vecSpread, MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 1, -1, 1, sk_alyxgun_burst_damage.GetFloat());

	pPlayer->DoMuzzleFlash();

	m_iClip1--;
	m_nBurstShot++;

	SetNextThink( gpGlobals->curtime + sk_alyxgun_burst_rate.GetFloat() );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::PrimaryAttack()
{
	CBasePlayer *pOwner = ToBasePlayer( GetOwner() );
	if ( !pOwner )
		return;

	if ( m_bInTransition )
	{
		return;
	}

	if ( m_iClip1 <= 0 )
	{
		DryFire();
		m_flSoonestPrimaryAttack = gpGlobals->curtime + 0.2f;
		m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
		return;
	}
	
	pOwner->ViewPunchReset();

	CSoundEnt::InsertSound(SOUND_COMBAT | SOUND_CONTEXT_GUNFIRE, pOwner->GetAbsOrigin(), SOUNDENT_VOLUME_PISTOL, 0.2, pOwner, SOUNDENT_CHANNEL_WEAPON, pOwner->GetEnemy());
	SendWeaponAnim( ACT_VM_PRIMARYATTACK );

	if ( m_bSemiAutoMode )
	{
		Vector vecShootOrigin = pOwner->Weapon_ShootPosition();
		Vector vecShootDir;
		pOwner->EyeVectors( &vecShootDir );
		
		WeaponSound(SINGLE);
		FireBulletProjectiles( 1, vecShootOrigin, vecShootDir, VECTOR_CONE_PRECALCULATED, MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 1, entindex(), -1, sk_alyxgun_semiauto_damage.GetFloat() );
		pOwner->DoMuzzleFlash();
		m_iClip1--;

		m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate();
		m_flSoonestPrimaryAttack = m_flNextPrimaryAttack;
	}
	else if ( !m_bInBurst )
	{
		// Burst fires are handle almost entirely by our think function
		WeaponSound( BURST );
		m_bInBurst = true;
		SetThink( &CWeaponResistanceGun::BurstThink );
		SetNextThink( gpGlobals->curtime );
	}

	m_iPrimaryAttacks++;
}

//-----------------------------------------------------------------------------
// Purpose: Used for switching between fire modes (Burst / Full Auto)
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::SecondaryAttack()
{
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	if (m_bSemiAutoMode)
	{
		m_bSemiAutoMode = false;
		SendWeaponAnim(ACT_VM_RETRACT);
	}
	else
	{
		m_bSemiAutoMode = true;
		SendWeaponAnim(ACT_VM_EXTEND);
	}

	m_bInTransition = true;
	m_flDoneSwitchingMode = gpGlobals->curtime + GetViewModelSequenceDuration();

	m_flNextSecondaryAttack = gpGlobals->curtime + GetViewModelSequenceDuration();
	m_flSoonestPrimaryAttack = m_flNextSecondaryAttack;
}

//-----------------------------------------------------------------------------
// Purpose: Allows firing as fast as button is pressed
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::ItemPostFrame()
{
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if ( !pPlayer )
		return;

	if ( m_bInTransition )
	{
		if ( m_flDoneSwitchingMode > gpGlobals->curtime )
		{
			WeaponIdle();
		}
		else
		{
			m_flDoneSwitchingMode = 0.0f;
			m_bInTransition = false;
		}
	}

	CheckReload();

	if ((((pPlayer->m_afButtonPressed & IN_RELOAD) && (m_iClip1 < GetMaxClip1())) || (m_iClip1 == 0)) && !m_bInReload && !m_bInBurst)
	{
		Reload();
		return;
	}

	if ((pPlayer->m_afButtonPressed & IN_ATTACK) && (m_flSoonestPrimaryAttack <= gpGlobals->curtime) && m_bSemiAutoMode) // shoot as fast as the player can click
	{
		PrimaryAttack();
		return;
	}
	else if ((pPlayer->m_nButtons & IN_ATTACK) && (m_flNextPrimaryAttack <= gpGlobals->curtime) && !m_bSemiAutoMode) // if we're holding shoot at a slower speed
	{
		PrimaryAttack();
		return;
	}
	else if ((pPlayer->m_afButtonPressed & IN_ATTACK2) && (m_flNextSecondaryAttack <= gpGlobals->curtime)) // switch modes
	{
		SecondaryAttack();
		return;
	}

	// We always return if we're doing something,
	// so here we're idling
	WeaponIdle();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CWeaponResistanceGun::Deploy()
{
	m_flDoneSwitchingMode = 0.0f;

	return BaseClass::Deploy();
}

bool CWeaponResistanceGun::Holster(CBaseCombatWeapon* pSwitchingTo)
{
	if (m_bInTransition && m_flDoneSwitchingMode > gpGlobals->curtime)
	{
		// Still switching mode. Cancel the transition.
		m_bSemiAutoMode = !m_bSemiAutoMode;
	}

	return BaseClass::Holster( pSwitchingTo );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponResistanceGun::AddViewKick()
{
	CBasePlayer *pPlayer = ToBasePlayer( GetOwner() );
	if ( !pPlayer )
		return;

	QAngle viewPunch;

	viewPunch.x = random->RandomFloat( 0.25f, 0.5f );
	viewPunch.y = random->RandomFloat( -.6f, .6f );
	viewPunch.z = 0.0f;

	//Add it to the view punch
	pPlayer->ViewPunch( viewPunch );
}


bool CWeaponResistanceGun::SendWeaponAnim( int iActivity )
{
	if ( m_bSemiAutoMode )
	{
		switch ( iActivity )
		{
			default:
				break;
			case ACT_VM_PRIMARYATTACK:
				iActivity = ACT_VM_FIRE_EXTENDED;
				break;
			case ACT_VM_HOLSTER:
				iActivity = ACT_VM_HOLSTER_EXTENDED;
				break;
			case ACT_VM_RELOAD:
				iActivity = ACT_VM_RELOAD_EXTENDED;
				break;
			/*case ACT_VM_IDLE:
				iActivity = ACT_VM_IDLE_EXTENDED;
				break;
			case ACT_VM_WALK:
				iActivity = ACT_VM_WALK_EXTENDED;
				break;
			case ACT_VM_SPRINT:
				iActivity = ACT_VM_SPRINT_EXTENDED;
				break;*/
			case ACT_VM_DRAW:
				iActivity = ACT_VM_DRAW_EXTENDED;
				break;
			case ACT_VM_KICK:
				iActivity = ACT_VM_KICK_EXTENDED;
		}
	}

	return BaseClass::SendWeaponAnim( iActivity );
}