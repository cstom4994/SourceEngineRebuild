//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef GRENADE_FRAG_H
#define GRENADE_FRAG_H
#pragma once

#include "basehlcombatweapon.h"

class CBaseGrenade;
struct edict_t;

class CWeaponFrag : public CBaseHLCombatWeapon
{
	DECLARE_CLASS(CWeaponFrag, CBaseHLCombatWeapon);
public:
	DECLARE_SERVERCLASS();

public:
	CWeaponFrag();

	void	Precache(void);
	void	Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);
	void	PrimaryAttack(void);
	void	SecondaryAttack(void);
	virtual void	DecrementAmmo(CBaseCombatCharacter* pOwner);
	void	ItemPostFrame(void);

	bool	Deploy(void);
	bool	Holster(CBaseCombatWeapon* pSwitchingTo = NULL);

	int		CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	bool	Reload(void);

	bool	ShouldDisplayHUDHint() { return true; }

protected:
	virtual void	ThrowGrenade(CBasePlayer* pPlayer);
	virtual void	RollGrenade(CBasePlayer* pPlayer);
	virtual void	LobGrenade(CBasePlayer* pPlayer);
	// check a throw from vecSrc.  If not valid, move the position back along the line to vecEye
	void	CheckThrowPosition(CBasePlayer* pPlayer, const Vector& vecEye, Vector& vecSrc);

	bool	m_bRedraw;	//Draw the weapon again after throwing a grenade

	int		m_AttackPaused;
	bool	m_fDrawbackFinished;

	DECLARE_ACTTABLE();

	DECLARE_DATADESC();
};


CBaseGrenade *Fraggrenade_Create( const Vector &position, const QAngle &angles, const Vector &velocity, const AngularImpulse &angVelocity, CBaseEntity *pOwner, float timer, bool combineSpawned );
bool	Fraggrenade_WasPunted( const CBaseEntity *pEntity );
bool	Fraggrenade_WasCreatedByCombine( const CBaseEntity *pEntity );

#endif // GRENADE_FRAG_H
