#ifndef SPP_UTILS_H
#define SPP_UTILS_H
#pragma once

#include "appframework/IAppSystem.h"
#include "utlvector.h"

class IVEngineClient;
class IBaseClientDLL;
class CGlobalVarsBase;
class IVEngineServer;
class IServerGameDLL;
class CGlobalVars;
class CUserMessages;

#define SPP_UTILS_INTERFACE "VGameSharedUtils008"

class IGameSharedUtils : public IAppSystem
{
public:
	virtual const char* DoMapEdit(const char* pMapName, const char* pMapEntities, CUtlVector<char *> *pVecVariants = nullptr) = 0;
	//virtual IHolidayEvents* GetEventSystem() = 0; // Removed in version 6

	// Version 3
	virtual bool	InitServer(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn gameFactory, CGlobalVars *pGlobals, CUserMessages *pUsermessages) = 0;
	virtual bool	ServerLevelInit(const char* pMapName, char const* pOldLevel, bool loadGame, bool background) = 0;
	virtual void	ServerLevelShutdown() = 0;

	virtual bool	InitClient(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn clientFactory, CGlobalVarsBase* pGlobals, CUserMessages* pUsermessages) = 0;
	virtual bool	ClientLevelInit(char const* pMapName) = 0;
	virtual void	ClientLevelShutdown() = 0;

	//virtual IDiscordPresence* GetRichPresence() = 0; // Removed in version 7

	// Unload the module if this returns 0
	virtual	const int	GetRefCount() const = 0;
	virtual void	ShaderInit() = 0;
	virtual void	ShaderShutdown() = 0;
};

#endif // !SPP_UTILS_H
