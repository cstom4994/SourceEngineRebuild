// Copyright(c) 2019 - 2021, KaoruXun All rights reserved.

// Purpose: Uploads KeyValue stats to the new SteamWorks gamestats system.

#include "cbase.h"
#include "cdll_int.h"
#include "tier2/tier2.h"
#include <time.h>

#ifdef    GAME_DLL
#include "gameinterface.h"
#elif    CLIENT_DLL

#include "c_playerresource.h"

#endif

#include "steam/isteamutils.h"

#include "steamworks_gamestats.h"
#include "achievementmgr.h"
#include "icommandline.h"

// NOTE: This has to be the last file included!
#include "tier0/memdbgon.h"

#if defined(CLIENT_DLL) || defined(CSTRIKE_DLL)
ConVar steamworks_sessionid_client("steamworks_sessionid_client", "0", FCVAR_HIDDEN,
                                   "The client session ID for the new steamworks gamestats.");
#endif

// This is used to replicate our server id to the client so that client data can be associated with the server's.
ConVar steamworks_sessionid_server("steamworks_sessionid_server", "0", FCVAR_REPLICATED | FCVAR_HIDDEN,
                                   "The server session ID for the new steamworks gamestats.");

// This is used to show when the steam works is uploading stats
#define steamworks_show_uploads 0

// This is a stop gap to disable the steam works game stats from ever initializing in the event that we need it
#if defined(CSTRIKE_DLL)
#define steamworks_stats_disable 1
#else
#define steamworks_stats_disable 0
#endif

// This is used to control when the stats get uploaded. If we wait until the end of the session, we miss out on all the stats if the server crashes. If we upload as we go, then we will have the data
#define steamworks_immediate_upload 1

// If set to zero all cvars will be tracked.
#define steamworks_track_cvar 0

// If set to non zero only cvars that are don't have default values will be tracked, but only if steamworks_track_cvar is also not zero.
#define steamworks_track_cvar_diff_only 1

// Methods that clients connect to servers.  note that positive numbers are reserved
// for quickplay sessions
enum {
    k_ClientJoinMethod_Unknown = -1,
    k_ClientJoinMethod_ListenServer = -2,
    k_ClientJoinMethod_ServerBrowser_UNKNOWN = -3, // server browser, unknown tab
    k_ClientJoinMethod_Steam = -4,
    k_ClientJoinMethod_Matchmaking = -5,
    k_ClientJoinMethod_Coaching = -6,
    k_ClientJoinMethod_Redirect = -7,
    k_ClientJoinMethod_ServerBrowserInternet = -10,
    k_ClientJoinMethod_ServerBrowserFriends = -11,
    k_ClientJoinMethod_ServerBrowserFavorites = -12,
    k_ClientJoinMethod_ServerBrowserHistory = -13,
    k_ClientJoinMethod_ServerBrowserLAN = -14,
    k_ClientJoinMethod_ServerBrowserSpectator = -15
};

static CSteamWorksGameStatsUploader g_SteamWorksGameStats;

extern ConVar developer;

#if defined(CLIENT_DLL) || defined(CSTRIKE_DLL)

void Show_Steam_Stats_Session_ID(void) {
    DevMsg("Client session ID (%s).\n", steamworks_sessionid_client.GetString());
    DevMsg("Server session ID (%s).\n", steamworks_sessionid_server.GetString());
}

static ConCommand ShowSteamStatsSessionID("ShowSteamStatsSessionID", Show_Steam_Stats_Session_ID,
                                          "Prints out the game stats session ID's (developer convar must be set to non-zero).",
                                          FCVAR_DEVELOPMENTONLY);
#endif

#ifdef CLIENT_DLL

//-----------------------------------------------------------------------------
// Purpose: Clients store the server's session IDs so we can associate client rows with server rows.
//-----------------------------------------------------------------------------
void ServerSessionIDChangeCallback(IConVar *pConVar, const char *pOldString, float flOldValue) {
    ConVarRef var(pConVar);
    if (var.IsValid()) {
        // Treat the variable as a string, since the sessionID is 64 bit and the convar int interface is only 32 bit.
        const char *pVarString = var.GetString();
        uint64 newServerSessionID = Q_atoi64(pVarString);
        g_SteamWorksGameStats.SetServerSessionID(newServerSessionID);
    }
}

#endif

//-----------------------------------------------------------------------------
// Purpose: Returns the time since the epoch
//-----------------------------------------------------------------------------
time_t CSteamWorksGameStatsUploader::GetTimeSinceEpoch(void) {
    if (steamapicontext && steamapicontext->SteamUtils())
        return steamapicontext->SteamUtils()->GetServerRealTime();
    else {
        // Default to system time.
        time_t aclock;
        time(&aclock);
        return aclock;
    }
}

//-----------------------------------------------------------------------------
// Purpose: Returns a reference to the global object
//-----------------------------------------------------------------------------
CSteamWorksGameStatsUploader &GetSteamWorksSGameStatsUploader() {
    return g_SteamWorksGameStats;
}

//-----------------------------------------------------------------------------
// Purpose: Constructor. Sets up the steam callbacks accordingly depending on client/server dll 
//-----------------------------------------------------------------------------
CSteamWorksGameStatsUploader::CSteamWorksGameStatsUploader() : CAutoGameSystemPerFrame("CSteamWorksGameStatsUploader") {
    Reset();
}

//-----------------------------------------------------------------------------
// Purpose: Reset uploader state.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::Reset() {
    ClearSessionID();

#ifdef    CLIENT_DLL
    steamworks_sessionid_client.SetValue(0);
    ClearServerSessionID();
#endif

    m_ServiceTicking = false;
    m_LastServiceTick = 0;
    m_SessionIDRequestUnsent = false;
    m_SessionIDRequestPending = false;
    m_UploadedStats = false;
    m_bCollectingAny = false;
    m_bCollectingDetails = false;
    m_UserID = 0;
    m_iAppID = 0;
    m_iServerIP = 0;
    m_nClientJoinMethod = k_ClientJoinMethod_Unknown;
    memset(m_pzServerIP, 0, ARRAYSIZE(m_pzServerIP));
    memset(m_pzMapStart, 0, ARRAYSIZE(m_pzMapStart));
    memset(m_pzHostName, 0, ARRAYSIZE(m_pzHostName));
    m_StartTime = 0;
    m_EndTime = 0;
    m_HumanCntInGame = 0;
    m_FriendCntInGame = 0;

    m_ActiveSession.Reset();
    m_iServerConnectCount = 0;

    for (int i = 0; i < m_StatsToSend.Count(); ++i) {
        m_StatsToSend[i]->deleteThis();
    }

    m_StatsToSend.RemoveAll();
}

//-----------------------------------------------------------------------------
// Purpose: Init function from CAutoGameSystemPerFrame and must return true.
//-----------------------------------------------------------------------------
bool CSteamWorksGameStatsUploader::Init() {
//	ListenForGameEvent( "hostname_changed" );
    ListenForGameEvent("server_spawn");

#ifdef CLIENT_DLL
    ListenForGameEvent("client_disconnect");
    ListenForGameEvent("client_beginconnect");
    steamworks_sessionid_server.InstallChangeCallback(ServerSessionIDChangeCallback);
#endif

    return true;
}

//-----------------------------------------------------------------------------
// Purpose: Event handler for gathering basic info as well as ending sessions.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::FireGameEvent(IGameEvent *event) {
    if (!event) {
        return;
    }

    const char *pEventName = event->GetName();
    if (FStrEq("hostname_changed", pEventName)) {
        const char *pzHostname = event->GetString("hostname");
        if (pzHostname) {
            V_strncpy(m_pzHostName, pzHostname, sizeof(m_pzHostName));
        } else {
            V_strncpy(m_pzHostName, "No Host Name", sizeof(m_pzHostName));
        }
    } else if (FStrEq("server_spawn", pEventName)) {

#if 0        // the next three disabled if()'s are in the latest l4d2 branch, I'm not sure if they should be brought over
        if ( !m_pzServerIP[0] )
#endif
        {
            const char *pzAddress = event->GetString("address");
            if (pzAddress) {
                V_snprintf(m_pzServerIP, ARRAYSIZE(m_pzServerIP), "%s:%d", pzAddress, event->GetInt("port"));
                ServerAddressToInt();
            } else {
                V_strncpy(m_pzServerIP, "No Server Address", sizeof(m_pzServerIP));
                m_iServerIP = 0;
            }
        }

#if 0
        if ( !m_pzHostName[0] )
#endif
        {
            const char *pzHostname = event->GetString("hostname");
            if (pzHostname) {
                V_strncpy(m_pzHostName, pzHostname, sizeof(m_pzHostName));
            } else {
                V_strncpy(m_pzHostName, "No Host Name", sizeof(m_pzHostName));
            }
        }

#if 0
        if ( !m_pzMapStart[0] )
#endif
        {
            const char *pzMapName = event->GetString("mapname");
            if (pzMapName) {
                V_strncpy(m_pzMapStart, pzMapName, sizeof(m_pzMapStart));
            } else {
                V_strncpy(m_pzMapStart, "No Map Name", sizeof(m_pzMapStart));
            }
        }

        m_bPassword = event->GetBool("password");
    }
#ifdef CLIENT_DLL
        // Started attempting connection to gameserver
    else if (FStrEq("client_beginconnect", pEventName)) {
        const char *pszSource = event->GetString("source", "");
        m_nClientJoinMethod = k_ClientJoinMethod_Unknown;
        if (pszSource[0] != '\0') {
            if (FStrEq("listenserver", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_ListenServer;
            else if (FStrEq("serverbrowser", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowser_UNKNOWN;
            else if (FStrEq("serverbrowser_internet", pszSource))
                m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowserInternet;
            else if (FStrEq("serverbrowser_friends", pszSource))
                m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowserFriends;
            else if (FStrEq("serverbrowser_favorites", pszSource))
                m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowserFavorites;
            else if (FStrEq("serverbrowser_history", pszSource))
                m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowserHistory;
            else if (FStrEq("serverbrowser_lan", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowserLAN;
            else if (FStrEq("serverbrowser_spectator", pszSource))
                m_nClientJoinMethod = k_ClientJoinMethod_ServerBrowserSpectator;
            else if (FStrEq("-ConnectStringOnCommandline", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_Unknown;
            else if (FStrEq("steam", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_Steam;
            else if (FStrEq("matchmaking", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_Matchmaking;
            else if (FStrEq("coaching", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_Coaching;
            else if (FStrEq("redirect", pszSource)) m_nClientJoinMethod = k_ClientJoinMethod_Redirect;
            else if (sscanf(pszSource, "quickplay_%d", &m_nClientJoinMethod) == 1)
                Assert(m_nClientJoinMethod > 0);
            else
                Warning("Unrecognized client_beginconnect event 'source' argument: '%s'\n", pszSource);
        }
    } else if (FStrEq("client_disconnect", pEventName)) {
        ClientDisconnect();
    }
#endif
}

#ifdef CLIENT_DLL

//-----------------------------------------------------------------------------
// Purpose:	Sets the server session ID but ONLY if it's not 0. We are using this to avoid a race 
// 			condition where a server sends their session stats before a client does, thereby,
//			resetting the client's server session ID to 0.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::SetServerSessionID(uint64 serverSessionID) {
    if (!serverSessionID)
        return;

    if (serverSessionID != m_ActiveSession.m_ServerSessionID) {
        m_ActiveSession.m_ServerSessionID = serverSessionID;
        m_ActiveSession.m_ConnectTime = GetTimeSinceEpoch();
        m_ActiveSession.m_DisconnectTime = 0;

        m_iServerConnectCount++;
    }

    m_ServerSessionID = serverSessionID;
}

//-----------------------------------------------------------------------------
// Purpose:	Writes the disconnect time to the current server session entry.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::ClientDisconnect() {

    // Save client join method, reset it to make sure it gets set properly
    // next time and we don't just reuse the current method
    int nClientJoinMethod = m_nClientJoinMethod;
    m_nClientJoinMethod = k_ClientJoinMethod_Unknown;

    if (m_ActiveSession.m_ServerSessionID == 0)
        return;

    if (!IsCollectingAnyData())
        return;

    m_ActiveSession.Reset();
}

#endif

//-----------------------------------------------------------------------------
// Purpose: Called when the level shuts down.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::LevelShutdown() {
#ifdef CLIENT_DLL
    ClearServerSessionID();
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Clears our session id and session id convar.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::ClearSessionID() {
    m_SessionID = 0;
    steamworks_sessionid_server.SetValue(0);
}

#ifndef NO_STEAM

//-----------------------------------------------------------------------------
// Purpose: Per frame think. Used to periodically check if we have queued operations.
// For example: we may request a session id before steam is ready.
//-----------------------------------------------------------------------------
void CSteamWorksGameStatsUploader::FrameUpdatePostEntityThink() {
    if (!m_ServiceTicking)
        return;

    if (gpGlobals->realtime - m_LastServiceTick < 3)
        return;
    m_LastServiceTick = gpGlobals->realtime;


    // If we had nothing to resend, stop ticking.
    m_ServiceTicking = false;
}

#endif

//-------------------------------------------------------------------------------------------------
/**
*	Purpose:	Calculates the number of humans in the game
*/
int CSteamWorksGameStatsUploader::GetHumanCountInGame() {
    int iHumansInGame = 0;
    // TODO: Need to add server/client code to count the number of connected humans.
    return iHumansInGame;
}

#ifdef    CLIENT_DLL
//-------------------------------------------------------------------------------------------------
/**
*	Purpose:	Calculates the number of friends in the game
*/
int CSteamWorksGameStatsUploader::GetFriendCountInGame() {
    // Get the number of steam friends in game
    int friendsInOurGame = 0;


    // Do we have access to the steam API?
    {
        CSteamID m_SteamID = steamapicontext->SteamUser()->GetSteamID();
        // Let's get our game info so we can use that to test if our friends are connected to the same game as us
        FriendGameInfo_t myGameInfo;
        steamapicontext->SteamFriends()->GetFriendGamePlayed(m_SteamID, &myGameInfo);
        CSteamID myLobby = steamapicontext->SteamMatchmaking()->GetLobbyOwner(myGameInfo.m_steamIDLobby);

        // This returns the number of friends that are playing a game
        int activeFriendCnt = steamapicontext->SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);

        // Check each active friend's lobby ID to see if they are in our game
        for (int h = 0; h < activeFriendCnt; ++h) {
            FriendGameInfo_t friendInfo;
            CSteamID friendID = steamapicontext->SteamFriends()->GetFriendByIndex(h, k_EFriendFlagImmediate);

            if (steamapicontext->SteamFriends()->GetFriendGamePlayed(friendID, &friendInfo)) {
                // Does our friend have a valid lobby ID?
                if (friendInfo.m_gameID.IsValid()) {
                    // Get our friend's lobby info
                    CSteamID friendLobby = steamapicontext->SteamMatchmaking()->GetLobbyOwner(
                            friendInfo.m_steamIDLobby);

                    // Double check the validity of the friend lobby ID then check to see if they are in our game
                    if (friendLobby.IsValid() && myLobby == friendLobby) {
                        ++friendsInOurGame;
                    }
                }
            }
        }
    }

    return friendsInOurGame;
}

#endif

void CSteamWorksGameStatsUploader::ServerAddressToInt() {
    CUtlStringList IPs;
    V_SplitString(m_pzServerIP, ".", IPs);

    if (IPs.Count() < 4) {
        // Not an actual IP.
        m_iServerIP = 0;
        return;
    }

    byte ip[4];
    m_iServerIP = 0;
    for (int i = 0; i < IPs.Count() && i < 4; ++i) {
        ip[i] = (byte) Q_atoi(IPs[i]);
    }
    m_iServerIP = (ip[0] << 24) + (ip[1] << 16) + (ip[2] << 8) + ip[3];
}

