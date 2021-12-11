#include "cbase.h"
#include "vance_player.h"
#include "vance_gamerules.h"
#include "game.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern CBaseEntity* FindPickerEntityClass(CBasePlayer* pPlayer, char* classname);
extern bool g_fGameOver;
extern ConVar gamerules_survival;

void ClientPutInServer(edict_t* pEdict, const char* pszPlayerName)
{
	CVancePlayer* pPlayer = CVancePlayer::Create(pEdict);
	pPlayer->SetPlayerName(pszPlayerName);
}

void ClientActive(edict_t* pEdict, bool bLoadGame)
{
	CVancePlayer* pPlayer = static_cast<CVancePlayer*>(CBaseEntity::Instance(pEdict));

	Assert(pPlayer);
	if (!pPlayer)
		return;

	pPlayer->InitialSpawn();

	if (!bLoadGame)
		pPlayer->Spawn();
}

const char* GetGameDescription()
{
	return "Vance";
}

CBaseEntity* FindEntity(edict_t* pEdict, char* pszClassName)
{
	// If no name was given set bits based on the picked
	if (FStrEq(pszClassName, ""))
		return (FindPickerEntityClass(static_cast<CBasePlayer*>(GetContainingEntity(pEdict)), pszClassName));

	return nullptr;
}

void ClientGamePrecache(void)
{
	CBaseEntity::PrecacheModel("models/player.mdl");
	CBaseEntity::PrecacheModel("models/gibs/agibs.mdl");
	CBaseEntity::PrecacheModel("models/weapons/v_hands.mdl");

	CBaseEntity::PrecacheScriptSound("HUDQuickInfo.LowAmmo");
	CBaseEntity::PrecacheScriptSound("HUDQuickInfo.LowHealth");

	CBaseEntity::PrecacheScriptSound("FX_AntlionImpact.ShellImpact");
	CBaseEntity::PrecacheScriptSound("Missile.ShotDown");
	CBaseEntity::PrecacheScriptSound("Bullets.DefaultNearmiss");
	CBaseEntity::PrecacheScriptSound("Bullets.GunshipNearmiss");
	CBaseEntity::PrecacheScriptSound("Bullets.StriderNearmiss");

	CBaseEntity::PrecacheScriptSound("Geiger.BeepHigh");
	CBaseEntity::PrecacheScriptSound("Geiger.BeepLow");
}

// Called by ClientKill and DeadThink
void respawn(CBaseEntity* pEdict, bool bCopyCorpse)
{
	if (gpGlobals->coop || gpGlobals->deathmatch)
	{
		if (bCopyCorpse)
		{
			// Make a copy of the dead body for appearances sake
			static_cast<CVancePlayer*>(pEdict)->CreateCorpse();
		}

		// Respawn player
		pEdict->Spawn();
	}
	else
	{
		// restart the entire server
		engine->ServerCommand("reload\n");
	}
}

void GameStartFrame(void)
{
	if (g_fGameOver)
		return;

	gpGlobals->teamplay = (teamplay.GetInt() != 0);
}

void InstallGameRules()
{
	CreateGameRulesObject("CVanceGameRules");
}