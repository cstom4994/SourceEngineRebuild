#pragma once


class IDiscordPresence
{
public:
	virtual void InitDiscord(const char* applicationId) = 0;
	virtual void ShutdownDiscord() = 0;
	virtual void SetServerPorts(int iGame, int iSpectate) = 0;
	virtual void ResetTimeStamp() = 0;
	virtual void RunCallbacks() = 0;
};