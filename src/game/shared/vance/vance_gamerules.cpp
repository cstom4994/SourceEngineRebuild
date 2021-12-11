#include "cbase.h"
#include "vance_gamerules.h"
#include "vance_shareddefs.h"
#include "tier0/memdbgon.h"

REGISTER_GAMERULES_CLASS(CVanceGameRules);

ConVar	sk_plr_dmg_ar1("sk_plr_dmg_ar1", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_ar1("sk_npc_dmg_ar1", "0", FCVAR_REPLICATED);
ConVar	sk_max_ar1("sk_max_ar1", "0", FCVAR_REPLICATED);

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : iDmgType - 
// Output :		bool
//-----------------------------------------------------------------------------
bool CVanceGameRules::Damage_IsTimeBased(int iDmgType)
{
	// Damage types that are time-based.
	return ((iDmgType & (DMG_PARALYZE | DMG_NERVEGAS | DMG_POISON | 
		DMG_RADIATION | DMG_DROWNRECOVER | DMG_SLOWBURN | DMG_BLEED)) != 0);
}

bool CVanceGameRules::FShouldSwitchWeapon(CBasePlayer* pPlayer, CBaseCombatWeapon* pWeapon)
{
	//Must have ammo
	if ((pWeapon->HasAnyAmmo() == false) && (pPlayer->GetAmmoCount(pWeapon->m_iPrimaryAmmoType) <= 0))
		return false;

	//Always take a loaded gun if we have nothing else
	if (pPlayer->GetActiveWeapon() == NULL)
		return true;

	// The given weapon must allow autoswitching to it from another weapon.
//	if (!pWeapon->AllowsAutoSwitchTo())
//		return false;

	// The active weapon must allow autoswitching from it.
//	if (!pPlayer->GetActiveWeapon()->AllowsAutoSwitchFrom())
//		return false;

	//Don't switch if our current gun doesn't want to be holstered
//	if (pPlayer->GetActiveWeapon()->CanHolster() == false)
//		return false;

	return false;
}