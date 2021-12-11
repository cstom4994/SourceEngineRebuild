
#include "cbase.h"
#include "vance_baseweapon_shared.h"
#include "basecombatweapon.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "soundent.h"
#include "game.h"

ConVar sk_plr_num_anastasia_pellets( "sk_plr_num_anastasia_pellets", "14", FCVAR_REPLICATED );


class CWeaponAnastasia : public CBaseVanceWeapon
{
	DECLARE_CLASS( CWeaponAnastasia, CBaseVanceWeapon );
	DECLARE_SERVERCLASS();

public:
	virtual void PrimaryAttack();
	void DryFire();
	virtual Vector &GetBulletSpread() override
	{
		static Vector vecCone = VECTOR_CONE_10DEGREES + VECTOR_CONE_6DEGREES;
		return vecCone;
	}
};

IMPLEMENT_SERVERCLASS_ST( CWeaponAnastasia, DT_WeaponAnastasia )
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( weapon_anastasia, CWeaponAnastasia );
PRECACHE_WEAPON_REGISTER( weapon_anastasia );


void CWeaponAnastasia::PrimaryAttack()
{
	// Only the player fires this way so we can cast.
	CBasePlayer *pPlayer = ToBasePlayer( GetOwner() );
	if ( !pPlayer )
		return;

	if ( pPlayer->GetAmmoCount( m_iSecondaryAmmoType ) <= 0 )
	{
		DryFire();
		pPlayer->SwitchToNextBestWeapon( this );
		return;
	}

	// MUST call sound before removing a round from the clip of a CMachineGun.
	WeaponSound( SINGLE );

	pPlayer->DoMuzzleFlash();

	SendWeaponAnim( ACT_VM_PRIMARYATTACK );

	// player "shoot" animation
	pPlayer->SetAnimation( PLAYER_ATTACK1 );

	// Don't fire again until fire animation has completed.
	m_flNextPrimaryAttack = gpGlobals->curtime + GetViewModelSequenceDuration();

	pPlayer->RemoveAmmo( 1, m_iSecondaryAmmoType );


	//EmitAmmoIndicationSound( m_iClip1, GetMaxClip2() );

	Vector vecSrc = pPlayer->Weapon_ShootPosition();
	Vector vecAiming = pPlayer->GetAutoaimVector( AUTOAIM_SCALE_DEFAULT );

	pPlayer->SetMuzzleFlashTime( gpGlobals->curtime + 1.0f );

	// Fire the bullets, and force the first shot to be perfectly accuracy.
	ProjectileBulletsInfo_t info;
	info.m_iShots = sk_plr_num_anastasia_pellets.GetInt();
	FireBulletProjectiles( sk_plr_num_anastasia_pellets.GetInt(), vecSrc, vecAiming, GetBulletSpread(), MAX_TRACE_LENGTH, m_iSecondaryAmmoType, 1, -1, -1, 0, NULL, true, true );

	pPlayer->ViewPunch( QAngle( random->RandomFloat( -6.0f, -3.0f ), random->RandomFloat( -2.0f, 2.0f ), 0.0f ) );

	CSoundEnt::InsertSound( SOUND_COMBAT, GetAbsOrigin(), SOUNDENT_VOLUME_SHOTGUN, 0.2f, GetOwner() );

	if ( pPlayer->GetAmmoCount( m_iSecondaryAmmoType ) <= 0 )
	{
		// HEV suit - indicate out of ammo condition.
		pPlayer->SetSuitUpdate( "!HEV_AMO0", FALSE, 0 );
	}
}

void CWeaponAnastasia::DryFire()
{
	WeaponSound( EMPTY );
	SendWeaponAnim( ACT_VM_DRYFIRE );

	m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
}