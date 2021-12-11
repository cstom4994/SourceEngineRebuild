//============================ AdV Software, 2019 ============================//
//
//	Base Vance Weapon
//
//============================================================================//

#include "cbase.h"
#include "vance_baseweapon_shared.h"
#include "vance_weapon_parse.h"
#include "in_buttons.h"

#ifdef GAME_DLL
#include "globalstate.h"
#include "vance_player.h"
#include "gamestats.h"
#include "ai_condition.h"
#include "soundent.h"
#else
#include "c_vance_player.h"
#include "weapon_selection.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef CLIENT_DLL
#define CVancePlayer C_VancePlayer
#endif

LINK_ENTITY_TO_CLASS(basevanceweapon, CBaseVanceWeapon);

BEGIN_DATADESC(CBaseVanceWeapon)
DEFINE_FIELD(m_bFirstDraw, FIELD_BOOLEAN),
END_DATADESC()

extern ConVar sk_auto_reload_time;
ConVar sv_recoil_override("sv_recoil_override", "", FCVAR_CHEAT, "USAGE: min:[pitch yaw roll] max:[pitch yaw roll]. Use just min if you want no randomness.");

//-----------------------------------------------------------------------------
// Purpose: Get my data in the file weapon info array
//-----------------------------------------------------------------------------
const VanceWeaponInfo_t &CBaseVanceWeapon::GetVanceWpnData() const
{
	return (VanceWeaponInfo_t &)GetWpnData();
}

#ifdef GAME_DLL
QAngle CBaseVanceWeapon::GetRecoil()
{
	const VanceWeaponInfo_t& info = GetVanceWpnData();

	if (V_strcmp(sv_recoil_override.GetString(), "") != 0)
	{
		QAngle recoil[2]; // min and max
		UTIL_StringToFloatArray(recoil[0].Base(), 6, sv_recoil_override.GetString());

		if (recoil[1] != vec3_angle) // This weapon wants random min/max-based recoil
		{
			return QAngle(RandomFloat(recoil[0].x, recoil[1].x),
				RandomFloat(recoil[0].y, recoil[1].y),
				RandomFloat(recoil[0].z, recoil[1].z));
		}
		else // This weapon wants fixed recoil
		{
			return recoil[0];
		}
	}

	if (info.recoilMax != vec3_angle) // This weapon wants random min/max-based recoil
	{
		return QAngle(RandomFloat(info.recoilMin.x, info.recoilMax.x),
			RandomFloat(info.recoilMin.y, info.recoilMax.y),
			RandomFloat(info.recoilMin.z, info.recoilMax.z));
	}
	else // This weapon wants fixed recoil
	{
		return info.recoilMin;
	}
}
#endif

void CBaseVanceWeapon::Spawn(void)
{
	BaseClass::Spawn();
	
	m_pszMuzzleFlashTexture = GetVanceWpnData().szMuzzleFlashTexture;
	m_bFirstDraw = true;
}

void CBaseVanceWeapon::PrimaryAttack(void)
{
	BaseClass::PrimaryAttack();
	EmitAmmoIndicationSound(m_iClip1, GetMaxClip1());
}

//-----------------------------------------------------------------------------
// Purpose: Called when gun is drawn.
//-----------------------------------------------------------------------------
Activity CBaseVanceWeapon::GetDrawActivity(void)
{
	if (m_bFirstDraw && GetVanceWpnData().bHasFirstDrawAnim)
	{
		m_bFirstDraw = false;
		return ACT_VM_FIRSTDRAW;
	}
	else
	{
		return ACT_VM_DRAW;
	}
}

void CBaseVanceWeapon::Precache(void)
{
	BaseClass::Precache();

	PrecacheScriptSound("Weapon.LowAmmo");
	PrecacheScriptSound("Weapon.NoAmmo");
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBaseVanceWeapon::ItemHolsterFrame(void)
{
	BaseClass::ItemHolsterFrame();

	// Must be player held.
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	// We can't be active.
	if (pPlayer->GetActiveWeapon() == this)
		return;

	// If it's been longer than three seconds when we're suited up, reload.
	if (pPlayer->IsSuitEquipped() && (gpGlobals->curtime - m_flHolsterTime) > sk_auto_reload_time.GetFloat())
	{
		// Just load the clip with no animations.
		FinishReload();
		m_flHolsterTime = gpGlobals->curtime;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CBaseVanceWeapon::CanSprint()
{
	CVancePlayer *pPlayer = assert_cast<CVancePlayer *>(GetOwner());
	if (pPlayer && SelectWeightedSequence(ACT_VM_SPRINT) == ACTIVITY_NOT_AVAILABLE)
		return false;

	return true;
}

bool CBaseVanceWeapon::CanWalkBob()
{
	CVancePlayer *pPlayer = assert_cast<CVancePlayer *>(GetOwner());
	if (pPlayer && SelectWeightedSequence(ACT_VM_WALK) == ACTIVITY_NOT_AVAILABLE)
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseVanceWeapon::Deploy(void)
{
	// If we should be lowered, deploy in the lowered position
	// We have to ask the player if the last time it checked, the weapon was lowered
	if (GetOwner() && GetOwner()->IsPlayer())
	{
		CVancePlayer *pPlayer = assert_cast<CVancePlayer *>(GetOwner());
		if (pPlayer->IsWeaponLowered())
		{
			if (CanLower())
			{
				if (DefaultDeploy((char*)GetViewModel(), (char*)GetWorldModel(), ACT_VM_IDLE_LOWERED, (char*)GetAnimPrefix()))
				{
					m_bLowered = true;

					// Stomp the next attack time to fix the fact that the lower idles are long
					pPlayer->SetNextAttack(gpGlobals->curtime + 1.0);
					m_flNextPrimaryAttack = gpGlobals->curtime + 1.0;
					m_flNextSecondaryAttack = gpGlobals->curtime + 1.0;
					return true;
				}
			}
		}
	}

	m_bLowered = false;
	return BaseClass::Deploy();
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseVanceWeapon::WeaponShouldBeLowered(void)
{
	// Can't be in the middle of another animation
	if (GetIdealActivity() != ACT_VM_IDLE_LOWERED && GetIdealActivity() != ACT_VM_IDLE &&
		GetIdealActivity() != ACT_VM_IDLE_TO_LOWERED && GetIdealActivity() != ACT_VM_LOWERED_TO_IDLE)
		return false;

	if (m_bLowered)
		return true;

#if !defined( CLIENT_DLL )
	if (GlobalEntity_GetState("friendly_encounter") == GLOBAL_ON)
		return true;

	/*CBasePlayer* player = dynamic_cast<CBasePlayer*>(GetOwner());
	if (player)
	{
		//Trace forward and see if he hit a wall.
		trace_t tr;
		Vector forward;
		player->EyeVectors(&forward);
		UTIL_TraceLine(player->EyePosition(),
			player->EyePosition() + forward * 36,
			MASK_SOLID, this, COLLISION_GROUP_WEAPON, &tr);

		// Lower if we hit something.
		if (tr.fraction != 1.0)
			return true;
	}*/
#endif

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Allows the weapon to choose proper weapon idle animation
//-----------------------------------------------------------------------------
void CBaseVanceWeapon::WeaponIdle(void)
{
	CVancePlayer *pPlayer = static_cast<CVancePlayer *>( GetOwner() );
	if ( !pPlayer )
		return;

	float speed = pPlayer->GetLocalVelocity().Length2D();

	if ( pPlayer->IsSprinting() && speed >= 300 )
	{
		int iActivity = GetActivity();
		if (HasWeaponIdleTimeElapsed() || 
				(
					GetActivity() != ACT_VM_KICK &&
					(
						GetActivity() == GetIdleActivity() ||
						GetActivity() == GetWalkActivity() ||
						GetActivity() == GetIdleLoweredActivity()
					) ||
					GetActivity() == ACT_VM_IDLE_TO_LOWERED ||
					GetActivity() == ACT_VM_LOWERED_TO_IDLE
				)
			)
			// (idling || not kicking && activity == idle, walk or lowered || 
		{
			iActivity = GetSprintActivity();
		}

		int iSequence = SelectWeightedSequence(GetIdleActivity());
		if (iSequence >= 0 && iActivity != GetActivity())
		{
			SendWeaponAnim(iActivity);
		}
	}

	//See if we should idle high or low
	else if (WeaponShouldBeLowered())
	{
#if !defined( CLIENT_DLL )
		pPlayer->Weapon_Lower();
#endif

		// Move to lowered position if we're not there yet
		if (GetActivity() != GetIdleLoweredActivity() && GetActivity() != ACT_VM_IDLE_TO_LOWERED
			&& GetActivity() != ACT_TRANSITION)
		{
			SendWeaponAnim(GetIdleLoweredActivity());
		}
		else if (HasWeaponIdleTimeElapsed())
		{
			// Keep idling low
			SendWeaponAnim(GetIdleLoweredActivity());
		}
	}
	else if (CanWalkBob() && speed >= 100 && pPlayer->GetWaterLevel() != 3 && (pPlayer->GetFlags() & FL_ONGROUND))
	{
		if (GetActivity() != GetWalkActivity() && GetActivity() != ACT_VM_KICK && (GetActivity() == GetIdleActivity() || GetActivity() == GetSprintActivity()))
		{
			SendWeaponAnim(GetWalkActivity());
		}
		else if (HasWeaponIdleTimeElapsed())
		{
			SendWeaponAnim(GetWalkActivity());
		}
	}
	else
	{
		// See if we need to raise immediately
		if (m_flRaiseTime < gpGlobals->curtime && GetActivity() == GetIdleLoweredActivity())
		{
			SendWeaponAnim(GetIdleActivity());
		}

		else if (speed <= (pPlayer->IsSuitEquipped() ? 300 : 200) && GetActivity() == GetSprintActivity())
		{
			SendWeaponAnim(GetIdleActivity());
		}
		else if (speed <= 100 && GetActivity() == GetWalkActivity())
		{
			SendWeaponAnim(GetIdleActivity());
		}
		else if (HasWeaponIdleTimeElapsed())
		{
			if (gpGlobals->curtime >= m_flNextFidgetTime)
			{
				//DevMsg("ACT_VM_FIDGET time!\n");
				SendWeaponAnim(ACT_VM_FIDGET);
				m_flNextFidgetTime = gpGlobals->curtime + 9.0f;
			}
			else
			{
				SendWeaponAnim(GetIdleActivity());
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseVanceWeapon::EmitAmmoIndicationSound(int iClip, int iMaxClip)
{
#ifdef GAME_DLL
	CBasePlayer* pOwner = dynamic_cast<CBasePlayer*>(GetOwner());
	if (!pOwner)
		return;

	CSoundParameters params;
	if (CBaseEntity::GetParametersForSound(iClip > 0 ? "Weapon.LowAmmo" : "Weapon.NoAmmo", params, NULL))
	{
		params.volume = Clamp((float)((iMaxClip / 2) - iClip) / (iMaxClip / 2), 0.0f, 1.0f);

		CRecipientFilter filter;
		filter.AddRecipient(pOwner);

		CBaseEntity::EmitSound(filter, pOwner->entindex(), params);
	}
#endif
}

#ifdef CLIENT_DLL
//-----------------------------------------------------------------------------
// Purpose: 
// Input  : bnewentity - 
//-----------------------------------------------------------------------------
void CBaseVanceWeapon::OnDataChanged(DataUpdateType_t updateType)
{
	BaseClass::OnDataChanged(updateType);

	CHandle< C_BaseCombatWeapon > handle = this;

	// If it's being carried by the *local* player, on the first update,
	// find the registered weapon for this ID

	C_BasePlayer* pPlayer = C_BasePlayer::GetLocalPlayer();
	C_BaseCombatCharacter* pOwner = GetOwner();

	// check if weapon is carried by local player
	bool bIsLocalPlayer = pPlayer && pPlayer == pOwner;
	if (bIsLocalPlayer && !C_BasePlayer::ShouldDrawLocalPlayer())		// TODO: figure out the purpose of the ShouldDrawLocalPlayer() test.
	{
		// If I was just picked up, or created & immediately carried, add myself to this client's list of weapons
		if ((m_iState != WEAPON_NOT_CARRIED) && (m_iOldState == WEAPON_NOT_CARRIED))
		{
			// Tell the HUD this weapon's been picked up
			if (ShouldDrawPickup())
			{
				if (pPlayer->IsSuitEquipped())
				{
					CBaseHudWeaponSelection* pHudSelection = GetHudWeaponSelection();
					if (pHudSelection)
					{
						pHudSelection->OnWeaponPickup(this);
					}

					pPlayer->EmitSound("Player.PickupWeapon");
				}
				else
				{
					pPlayer->EmitSound("HL2Player.PickupWeapon_Suitless");
				}
			}
		}
	}
	else // weapon carried by other player or not at all
	{
		int overrideModelIndex = CalcOverrideModelIndex();
		if (overrideModelIndex != -1 && overrideModelIndex != GetModelIndex())
		{
			SetModelIndex(overrideModelIndex);
		}
	}

	UpdateVisibility();

	m_iOldState = m_iState;

	m_bJustRestored = false;
}
#endif

IMPLEMENT_NETWORKCLASS_ALIASED(VanceMachineGun, DT_VanceMachineGun)

BEGIN_NETWORK_TABLE(CVanceMachineGun, DT_VanceMachineGun)
END_NETWORK_TABLE()

#ifdef GAME_DLL
BEGIN_DATADESC(CVanceMachineGun)
DEFINE_FIELD(m_nShotsFired, FIELD_INTEGER),
DEFINE_FIELD(m_flNextSoundTime, FIELD_TIME),
END_DATADESC()

CVanceMachineGun::CVanceMachineGun(void)
{
}

const Vector& CVanceMachineGun::GetBulletSpread(void)
{
	static Vector cone = VECTOR_CONE_3DEGREES;
	return cone;
}

void CVanceMachineGun::PrimaryAttack(void)
{
	// Only the player fires this way so we can cast
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	// Abort here to handle burst and auto fire modes
	if ((UsesClipsForAmmo1() && m_iClip1 == 0) || (!UsesClipsForAmmo1() && !pPlayer->GetAmmoCount(m_iPrimaryAmmoType)))
		return;

	m_nShotsFired++;

	pPlayer->DoMuzzleFlash();

	// To make the firing framerate independent, we may have to fire more than one bullet here on low-framerate systems, 
	// especially if the weapon we're firing has a really fast rate of fire.
	int iBulletsToFire = 0;
	float fireRate = GetFireRate();

	// MUST call sound before removing a round from the clip of a CHLMachineGun
	while (m_flNextPrimaryAttack <= gpGlobals->curtime)
	{
		WeaponSound(SINGLE, m_flNextPrimaryAttack);
		m_flNextPrimaryAttack = m_flNextPrimaryAttack + fireRate;
		iBulletsToFire++;
	}

	// Make sure we don't fire more than the amount in the clip, if this weapon uses clips
	if (UsesClipsForAmmo1())
	{
		if (iBulletsToFire > m_iClip1)
			iBulletsToFire = m_iClip1;
		m_iClip1 -= iBulletsToFire;
	}

	m_iPrimaryAttacks++;
	gamestats->Event_WeaponFired(pPlayer, true, GetClassname());

	// Fire the bullets
	Vector vecSrc = pPlayer->Weapon_ShootPosition();
	Vector vecDirShooting = pPlayer->GetAutoaimVector(AUTOAIM_SCALE_DEFAULT);
	Vector vecSpread = pPlayer->GetAttackSpread(this);
	FireBulletProjectiles(iBulletsToFire, vecSrc, vecDirShooting, vecSpread, MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 1);

	//Factor in the view kick
	AddViewKick();

	CSoundEnt::InsertSound(SOUND_COMBAT, GetAbsOrigin(), SOUNDENT_VOLUME_MACHINEGUN, 0.2, pPlayer);

	if (!m_iClip1 && pPlayer->GetAmmoCount(m_iPrimaryAmmoType) <= 0)
	{
		// HEV suit - indicate out of ammo condition
		pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	SendWeaponAnim(GetPrimaryAttackActivity());
	pPlayer->SetAnimation(PLAYER_ATTACK1);

	// Register a muzzleflash for the AI
	pPlayer->SetMuzzleFlashTime(gpGlobals->curtime + 0.5);
}

int CVanceMachineGun::WeaponRangeAttack1Condition(float flDot, float flDist)
{
	if (m_iClip1 <= 0)
	{
		return COND_NO_PRIMARY_AMMO;
	}
	else if (flDist < m_fMinRange1)
	{
		return COND_TOO_CLOSE_TO_ATTACK;
	}
	else if (flDist > m_fMaxRange1)
	{
		return COND_TOO_FAR_TO_ATTACK;
	}
	else if (flDot < 0.5f)	// UNDONE: Why check this here? Isn't the AI checking this already?
	{
		return COND_NOT_FACING_ATTACK;
	}

	return COND_CAN_RANGE_ATTACK1;
}

void CVanceMachineGun::DoMachineGunKick(CBasePlayer* pPlayer, float dampEasy, float maxVerticleKickAngle, float fireDurationTime, float slideLimitTime)
{
#define	KICK_MIN_X			0.2f	//Degrees
#define	KICK_MIN_Y			0.2f	//Degrees
#define	KICK_MIN_Z			0.1f	//Degrees

	QAngle vecScratch;

	//Find how far into our accuracy degradation we are
	float duration = (fireDurationTime > slideLimitTime) ? slideLimitTime : fireDurationTime;
	float kickPerc = duration / slideLimitTime;

	// do this to get a hard discontinuity, clear out anything under 10 degrees punch
	//pPlayer->ViewPunchReset(10);

	//Apply this to the view angles as well
	vecScratch.x = -(KICK_MIN_X + (maxVerticleKickAngle * kickPerc));
	vecScratch.y = -(KICK_MIN_Y + (maxVerticleKickAngle * kickPerc)) / 3;
	vecScratch.z = KICK_MIN_Z + (maxVerticleKickAngle * kickPerc) / 8;

	//Wibble left and right
	if (random->RandomInt(-1, 1) >= 0)
		vecScratch.y *= -1;

	//Wobble up and down
	if (random->RandomInt(-1, 1) >= 0)
		vecScratch.z *= -1;

	//If we're in easy, dampen the effect a bit
	if (g_pGameRules->IsSkillLevel(SKILL_EASY))
	{
		for (int i = 0; i < 3; i++)
		{
			vecScratch[i] *= dampEasy;
		}
	}

	//Clip this to our desired min/max
	UTIL_ClipPunchAngleOffset(vecScratch, pPlayer->m_Local.m_vecPunchAngle, QAngle(24.0f, 3.0f, 1.0f));

	//Add it to the view punch
	// NOTE: 0.5 is just tuned to match the old effect before the punch became simulated
	pPlayer->ViewPunch(vecScratch * 0.5);
}

bool CVanceMachineGun::Deploy(void)
{
	m_nShotsFired = 0;

	return BaseClass::Deploy();
}


int CVanceMachineGun::WeaponSoundRealtime(WeaponSound_t shoot_type)
{
	int numBullets = 0;

	// ran out of time, clamp to current
	if (m_flNextSoundTime < gpGlobals->curtime)
	{
		m_flNextSoundTime = gpGlobals->curtime;
	}

	// make enough sound events to fill up the next estimated think interval
	float dt = clamp(m_flAnimTime - m_flPrevAnimTime, 0, 0.2);
	if (m_flNextSoundTime < gpGlobals->curtime + dt)
	{
		WeaponSound(SINGLE_NPC, m_flNextSoundTime);
		m_flNextSoundTime += GetFireRate();
		numBullets++;
	}
	if (m_flNextSoundTime < gpGlobals->curtime + dt)
	{
		WeaponSound(SINGLE_NPC, m_flNextSoundTime);
		m_flNextSoundTime += GetFireRate();
		numBullets++;
	}

	return numBullets;
}

void CVanceMachineGun::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());

	if (pOwner == NULL)
		return;

	// Debounce the recoiling counter
	if ((pOwner->m_nButtons & IN_ATTACK) == false)
	{
		m_nShotsFired = 0;
	}

	BaseClass::ItemPostFrame();
}

#endif

// HACKHACK: need to put entire VanceBludgeonWeapon here later. this is a stub
#ifdef CLIENT_DLL
IMPLEMENT_CLIENTCLASS_DT(C_VanceBludgeonWeapon, DT_VanceBludgeonWeapon, CVanceBludgeonWeapon)
END_RECV_TABLE()
#endif