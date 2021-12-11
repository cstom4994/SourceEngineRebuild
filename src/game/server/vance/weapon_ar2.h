//========= Copyright Valve Corporation, All rights reserved. ============//

#ifndef	WEAPON_AR2_H
#define	WEAPON_AR2_H

#include "basegrenade_shared.h"
#include "vance_baseweapon_shared.h"

class CWeaponAR2 : public CVanceMachineGun
{
	DECLARE_CLASS(CWeaponAR2, CVanceMachineGun);
	DECLARE_SERVERCLASS();
	DECLARE_ACTTABLE();
	DECLARE_DATADESC();
public:

	CWeaponAR2();

	virtual void	ItemPostFrame();
	virtual void	Precache();

	virtual void	PrimaryAttack();
	virtual void	SecondaryAttack();
	virtual void	DelayedAttack();

	virtual const char *GetTracerType() { return "AR2Tracer"; }

	void			AddViewKick();

	virtual void	FireNPCPrimaryAttack( CBaseCombatCharacter *pOperator, bool bUseWeaponAngles );
	virtual void	FireNPCSecondaryAttack( CBaseCombatCharacter *pOperator, bool bUseWeaponAngles );
	virtual void	Operator_ForceNPCFire( CBaseCombatCharacter  *pOperator, bool bSecondary );
	virtual void	Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );

	virtual int		GetMinBurst() { return 2; }
	virtual int		GetMaxBurst() { return 5; }

	virtual bool	CanHolster();
	virtual bool	Reload();

	virtual int		CapabilitiesGet() { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual Activity	GetPrimaryAttackActivity();
	
	virtual void	DoImpactEffect( trace_t &tr, int nDamageType );

	virtual const Vector& GetBulletSpread()
	{
		static Vector cone;
		
		cone = VECTOR_CONE_3DEGREES;

		return cone;
	}

	virtual const WeaponProficiencyInfo_t *GetProficiencyValues();

protected:

	float					m_flDelayedFire;
	bool					m_bShotDelayed;
	int						m_nVentPose;
	bool					m_bPelletReload;
};


#endif // WEAPON_AR2_H
