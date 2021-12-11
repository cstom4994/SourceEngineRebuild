//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "basehlcombatweapon.h"
#include "player.h"
#include "gamerules.h"
#include "grenade_frag.h"
#include "grenade_hopwire.h"
#include "npcevent.h"
#include "engine/IEngineSound.h"
#include "items.h"
#include "in_buttons.h"
#include "soundent.h"
#include "gamestats.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


//-----------------------------------------------------------------------------
// Fragmentation grenades
//-----------------------------------------------------------------------------
class CWeaponHopwire: public CWeaponFrag
{
	DECLARE_CLASS( CWeaponHopwire, CWeaponFrag );
public:
protected:
	virtual void ThrowGrenade(CBasePlayer *pPlayer);
	virtual void DecrementAmmo(CBaseCombatCharacter* pOwner);
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void ItemPostFrame();
	DECLARE_DATADESC();
};


BEGIN_DATADESC( CWeaponHopwire )
	/*DEFINE_FIELD( m_bRedraw, FIELD_BOOLEAN ),
	DEFINE_FIELD( m_AttackPaused, FIELD_INTEGER ),
	DEFINE_FIELD( m_fDrawbackFinished, FIELD_BOOLEAN ),
	DEFINE_FIELD( m_hActiveHopWire, FIELD_EHANDLE ),*/
END_DATADESC()


LINK_ENTITY_TO_CLASS( weapon_hopwire, CWeaponHopwire );
PRECACHE_WEAPON_REGISTER(weapon_hopwire);

void CWeaponHopwire::ThrowGrenade(CBasePlayer* pPlayer)
{
	Vector	vecEye = pPlayer->EyePosition();
	Vector	vForward, vRight;

	pPlayer->EyeVectors(&vForward, &vRight, NULL);
	Vector vecSrc = vecEye + vForward * 18.0f + vRight * 8.0f;
	CheckThrowPosition(pPlayer, vecEye, vecSrc);
	//	vForward[0] += 0.1f;
	vForward[2] += 0.1f;

	Vector vecThrow;
	pPlayer->GetVelocity(&vecThrow, NULL);
	vecThrow += vForward * 1200;
	HopWire_Create(vecSrc, vec3_angle, vecThrow, AngularImpulse(600, random->RandomInt(-1200, 1200), 0), pPlayer, NULL);

	m_bRedraw = true;

	WeaponSound(SINGLE);
	pPlayer->SetAnimation(PLAYER_ATTACK1);

	m_iPrimaryAttacks++;
	gamestats->Event_WeaponFired(pPlayer, true, GetClassname());
}

void CWeaponHopwire::DecrementAmmo(CBaseCombatCharacter *pOwner)
{
	pOwner->RemoveAmmo(1, m_iSecondaryAmmoType);
}

void CWeaponHopwire::PrimaryAttack(void)
{
	if (m_bRedraw)
		return;

	CBaseCombatCharacter* pOwner = GetOwner();

	if (pOwner == NULL)
	{
		return;
	}

	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());;

	if (!pPlayer)
		return;

	// Note that this is a primary attack and prepare the grenade attack to pause.
	m_AttackPaused = 1; //GRENADE_PAUSED_PRIMARY;
	SendWeaponAnim(ACT_VM_PULLBACK_HIGH);

	// Put both of these off indefinitely. We do not know how long
	// the player will hold the grenade.
	m_flTimeWeaponIdle = FLT_MAX;
	m_flNextPrimaryAttack = FLT_MAX;

	// If I'm now out of ammo, switch away
	if (!HasSecondaryAmmo())
	{
		pPlayer->SwitchToNextBestWeapon(this);
	}
}

void CWeaponHopwire::SecondaryAttack()
{
	//loop over every hopwire entity and blow it up
	CBaseEntity* pEntity = NULL;
	while ((pEntity = gEntList.FindEntityByClassname(pEntity, "npc_grenade_hopwire")) != NULL)
	{
		CGrenadeHopwire* pGrenade = dynamic_cast<CGrenadeHopwire*>(pEntity);
		if (pGrenade)
		{
			if (pGrenade->m_bStuck)
			{
				pGrenade->Detonate();
			}
		}
	}
}

void CWeaponHopwire::ItemPostFrame()
{
	BaseClass::ItemPostFrame();
	//this is needed to explicitely call SecondaryAttack as the base grenade code doesnt sometimes?
	//kinda inefficient but does it really matter lol
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (pOwner)
	{
		if (pOwner->m_nButtons & IN_ATTACK2)
		{
			SecondaryAttack();
		}
	}
}