//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		ResistanceGun - hand gun
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "npcevent.h"
#include "vance_baseweapon_shared.h"
#ifdef GAME_DLL
#include "basecombatweapon.h"
#include "basecombatcharacter.h"
#include "vance_bludgeonweapon.h"
#endif
#ifdef CLIENT_DLL
#include "c_weapon__stubs.h"
#endif
#include "gamerules.h"
#include "in_buttons.h"
#include "vstdlib/random.h"
#include "gamestats.h"
#include "saverestore.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

 // SERVER
#ifdef GAME_DLL
ConVar    sk_plr_bottle_dmg("sk_plr_bottle_dmg", "0");
ConVar    sk_plr_bottle_range("sk_plr_bottle_range", "50");
ConVar    sk_plr_bottle_firerate("sk_plr_bottle_firerate", "0.5");

//-----------------------------------------------------------------------------
// CWeaponCrowbar
//-----------------------------------------------------------------------------

class CWeaponBottle : public CVanceBludgeonWeapon
{
public:
	DECLARE_CLASS(CWeaponBottle, CVanceBludgeonWeapon);

	DECLARE_SERVERCLASS();
	DECLARE_ACTTABLE();

	CWeaponBottle();

	float		GetRange(void) { return	sk_plr_bottle_range.GetFloat(); }
	float		GetFireRate(void) { return	sk_plr_bottle_firerate.GetFloat(); }

	float		GetDamageForActivity(Activity hitActivity) { return sk_plr_bottle_dmg.GetFloat(); }

	void		SecondaryAttack(void) { return; }

	Activity	GetSecondaryAttackActivity(void) { return	ACT_VM_HITCENTER2; }
};

IMPLEMENT_SERVERCLASS_ST(CWeaponBottle, DT_WeaponBottle)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_bottle, CWeaponBottle);
PRECACHE_WEAPON_REGISTER(weapon_bottle);

acttable_t CWeaponBottle::m_acttable[] =
{
	{ ACT_MELEE_ATTACK1,	ACT_MELEE_ATTACK_SWING, true },
	{ ACT_IDLE,				ACT_IDLE_ANGRY_MELEE,	false },
	{ ACT_IDLE_ANGRY,		ACT_IDLE_ANGRY_MELEE,	false },
};

IMPLEMENT_ACTTABLE(CWeaponBottle);

//-----------------------------------------------------------------------------
// Primary Attack
//-----------------------------------------------------------------------------
CWeaponBottle::CWeaponBottle(void)
{
}
#else
// HACKHACK: stub stub stub. i hate this. everyone hates this
STUB_WEAPON_CLASS(weapon_bottle, WeaponBottle, C_VanceBludgeonWeapon);
#endif