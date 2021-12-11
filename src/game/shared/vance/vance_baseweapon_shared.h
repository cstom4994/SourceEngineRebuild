//============================ AdV Software, 2019 ============================//
//
//	Base Vance Weapon
//
//============================================================================//

#ifndef VANCE_BASEWEAPON_SHARED_H
#define VANCE_BASEWEAPON_SHARED_H

#include "basehlcombatweapon_shared.h"
#include "vance_weapon_parse.h"

#ifdef CLIENT_DLL
#define CBaseVanceWeapon C_BaseVanceWeapon
#else
#include "basehlcombatweapon.h"
#endif

class CBaseVanceWeapon : public CBaseHLCombatWeapon
{
	DECLARE_CLASS(CBaseVanceWeapon, CBaseHLCombatWeapon);
	DECLARE_DATADESC();
public:

	virtual void		Spawn();
	virtual void		Precache();

	virtual void		PrimaryAttack();

	inline float		GetFireRate()
	{
		return GetVanceWpnData().roundsPerMinute;
	}

	bool				CanSprint();
	bool				CanWalkBob();

	void				EmitAmmoIndicationSound(int iClip, int iMaxClip);

	virtual bool		WeaponShouldBeLowered();

	virtual bool		Deploy();
	
	virtual void		ItemHolsterFrame();

	const char			*GetMuzzleFlashTexture() { return m_pszMuzzleFlashTexture; }

	const VanceWeaponInfo_t &GetVanceWpnData() const;

	inline void FireBulletProjectiles(int cShots, const Vector& vecSrc, const Vector& vecDirShooting,
		const Vector& vecSpread, float flDistance, int iAmmoType, int iTracerFreq = 4,
		int firingEntID = -1, int attachmentID = -1, int iDamage = 0,
		CBaseEntity* pAttacker = NULL, bool bFirstShotAccurate = false, bool bPrimaryAttack = true,
		float flBulletSpeed = 0.0f, float flBulletSize = 0.0f)
	{
		ProjectileBulletsInfo_t info;
		info.m_iShots = cShots;
		info.m_vecSrc = vecSrc;
		info.m_vecDirShooting = vecDirShooting;
		info.m_vecSpread = vecSpread;
		info.m_flDistance = flDistance;
		info.m_iAmmoType = iAmmoType;
		info.m_iTracerFreq = iTracerFreq;
		info.m_flDamage = iDamage;
		info.m_pAttacker = pAttacker;
		info.m_nFlags = bFirstShotAccurate ? FIRE_BULLETS_FIRST_SHOT_ACCURATE : 0;
		info.m_bPrimaryAttack = bPrimaryAttack;
		info.m_flBulletSize = flBulletSize;
		info.m_flBulletSpeed = flBulletSpeed == 0.0f ? GetVanceWpnData().flBulletSpeed : flBulletSpeed;

		CBaseEntity* pOwner = GetOwner();
		if (!pOwner)
			return;

		pOwner->FireBulletProjectiles(info);
	}

#ifdef GAME_DLL
	virtual QAngle		GetRecoil();
#endif

	virtual void		WeaponIdle();

	virtual Activity	GetDrawActivity();
	virtual Activity	GetIdleLoweredActivity() { return ACT_VM_IDLE_LOWERED; };
	virtual Activity	GetIdleActivity() { return ACT_VM_IDLE; };
	virtual Activity	GetWalkActivity() { return ACT_VM_WALK; };
	virtual Activity	GetSprintActivity() { return ACT_VM_SPRINT; };

	virtual bool		CanAttackWhileZoomed() { return false; }

#ifdef CLIENT_DLL
	virtual void		OnDataChanged(DataUpdateType_t updateType);
#endif

private:
	const char			*m_pszMuzzleFlashTexture;

	float				m_flNextFidgetTime;

protected:
	bool				m_bFirstDraw;
	bool				m_bJustRestored;
};

//	Re-implementented CHLMachine and CHLSelectFireMachineGun
//

#ifdef CLIENT_DLL
#define CVanceMachineGun C_VanceMachineGun
#define CVanceSelectFireMachineGun C_VanceSelectFireMachineGun
#endif

abstract_class CVanceMachineGun : public CBaseVanceWeapon
{
	DECLARE_CLASS(CVanceMachineGun, CBaseVanceWeapon);
	DECLARE_NETWORKCLASS();
#ifdef GAME_DLL
	DECLARE_DATADESC();
public:
	CVanceMachineGun();

	virtual void	PrimaryAttack();

	virtual void	ItemPostFrame();

	virtual int		WeaponRangeAttack1Condition(float flDot, float flDist);
	virtual bool	Deploy();

	virtual const Vector& GetBulletSpread(void);

	int				WeaponSoundRealtime(WeaponSound_t shoot_type);

	static void		DoMachineGunKick(CBasePlayer* pPlayer, float dampEasy, float maxVerticleKickAngle, float fireDurationTime, float slideLimitTime);

protected:
	int	m_nShotsFired;	// Number of consecutive shots fired
	float	m_flNextSoundTime;	// real-time clock of when to make next sound
#endif
};

#ifdef CLIENT_DLL
// HACKHACK: i hate this
class C_VanceBludgeonWeapon : public CBaseVanceWeapon
{
public:
	DECLARE_CLASS(C_VanceBludgeonWeapon, CBaseVanceWeapon);
	DECLARE_CLIENTCLASS();
};

#endif // CLIENT_DLL


#endif // VANCE_BASEWEAPON_SHARED_H