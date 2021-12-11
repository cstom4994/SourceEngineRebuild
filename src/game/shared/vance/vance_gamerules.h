#ifndef VANCE_GAMERULES_H
#define VANCE_GAMERULES_H

#include "hl2_gamerules.h"

class CVanceGameRules : public CHalfLife2
{
	DECLARE_CLASS(CVanceGameRules, CHalfLife2);
public:
	virtual bool	Damage_IsTimeBased(int iDmgType);
	virtual bool	FShouldSwitchWeapon(CBasePlayer* pPlayer, CBaseCombatWeapon* pWeapon);
};

//-----------------------------------------------------------------------------
// Gets us at the Half-Life 2 game rules
//-----------------------------------------------------------------------------
inline CVanceGameRules *VanceGameRules()
{
	return static_cast<CVanceGameRules *>(g_pGameRules);
}

#endif // VANCE_GAMERULES_H