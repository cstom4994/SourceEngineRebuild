﻿//====== Copyright (c) 1996-2014, Valve Corporation, All rights reserved. =======
//
// Purpose: Header for flatted SteamAPI. Use this for binding to other languages.
// This file is auto-generated, do not edit it.
//
//=============================================================================

#ifndef STEAMAPIFLAT_H
#define STEAMAPIFLAT_H
#ifdef _WIN32
#pragma once
#endif

#include <stdint.h>


typedef unsigned char uint8;
typedef unsigned char uint8;
typedef signed char int8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef int64 lint64;
typedef uint64 ulint64;
typedef uint8 Salt_t[8];
typedef uint64 GID_t;
typedef uint64 JobID_t;
typedef GID_t TxnID_t;
typedef uint32 PackageId_t;
typedef uint32 BundleId_t;
typedef uint32 AppId_t;
typedef uint64 AssetClassId_t;
typedef uint32 PhysicalItemId_t;
typedef uint32 DepotId_t;
typedef uint32 RTime32;
typedef uint32 CellID_t;
typedef uint64 SteamAPICall_t;
typedef uint32 AccountID_t;
typedef uint32 PartnerId_t;
typedef uint64 ManifestId_t;
typedef uint64 SiteId_t;
typedef uint32 HAuthTicket;
typedef void *BREAKPAD_HANDLE;
typedef char compile_time_assert_type[1];
typedef int32 HSteamPipe;
typedef int32 HSteamUser;
typedef int16 FriendsGroupID_t;
typedef void *HServerListRequest;
typedef int HServerQuery;
typedef uint64 UGCHandle_t;
typedef uint64 PublishedFileUpdateHandle_t;
typedef uint64 PublishedFileId_t;
typedef uint64 UGCFileWriteStreamHandle_t;
typedef char compile_time_assert_type[1];
typedef uint64 SteamLeaderboard_t;
typedef uint64 SteamLeaderboardEntries_t;
typedef uint32 SNetSocket_t;
typedef uint32 SNetListenSocket_t;
typedef uint32 ScreenshotHandle;
typedef uint32 HTTPRequestHandle;
typedef uint32 HTTPCookieContainerHandle;
typedef uint64 ControllerHandle_t;
typedef uint64 ControllerActionSetHandle_t;
typedef uint64 ControllerDigitalActionHandle_t;
typedef uint64 ControllerAnalogActionHandle_t;
typedef uint64 UGCQueryHandle_t;
typedef uint64 UGCUpdateHandle_t;
typedef uint32 HHTMLBrowser;
typedef uint64 SteamItemInstanceID_t;
typedef int32 SteamItemDef_t;
typedef int32 SteamInventoryResult_t;
typedef uint64 SteamInventoryUpdateHandle_t;
// OpenVR Constants
int const_k_iSteamUserCallbacks = 100;
int const_k_iSteamGameServerCallbacks = 200;
int const_k_iSteamFriendsCallbacks = 300;
int const_k_iSteamBillingCallbacks = 400;
int const_k_iSteamMatchmakingCallbacks = 500;
int const_k_iSteamContentServerCallbacks = 600;
int const_k_iSteamUtilsCallbacks = 700;
int const_k_iClientFriendsCallbacks = 800;
int const_k_iClientUserCallbacks = 900;
int const_k_iSteamAppsCallbacks = 1000;
int const_k_iSteamUserStatsCallbacks = 1100;
int const_k_iSteamNetworkingCallbacks = 1200;
int const_k_iClientRemoteStorageCallbacks = 1300;
int const_k_iClientDepotBuilderCallbacks = 1400;
int const_k_iSteamGameServerItemsCallbacks = 1500;
int const_k_iClientUtilsCallbacks = 1600;
int const_k_iSteamGameCoordinatorCallbacks = 1700;
int const_k_iSteamGameServerStatsCallbacks = 1800;
int const_k_iSteam2AsyncCallbacks = 1900;
int const_k_iSteamGameStatsCallbacks = 2000;
int const_k_iClientHTTPCallbacks = 2100;
int const_k_iClientScreenshotsCallbacks = 2200;
int const_k_iSteamScreenshotsCallbacks = 2300;
int const_k_iClientAudioCallbacks = 2400;
int const_k_iClientUnifiedMessagesCallbacks = 2500;
int const_k_iSteamStreamLauncherCallbacks = 2600;
int const_k_iClientControllerCallbacks = 2700;
int const_k_iSteamControllerCallbacks = 2800;
int const_k_iClientParentalSettingsCallbacks = 2900;
int const_k_iClientDeviceAuthCallbacks = 3000;
int const_k_iClientNetworkDeviceManagerCallbacks = 3100;
int const_k_iClientMusicCallbacks = 3200;
int const_k_iClientRemoteClientManagerCallbacks = 3300;
int const_k_iClientUGCCallbacks = 3400;
int const_k_iSteamStreamClientCallbacks = 3500;
int const_k_IClientProductBuilderCallbacks = 3600;
int const_k_iClientShortcutsCallbacks = 3700;
int const_k_iClientRemoteControlManagerCallbacks = 3800;
int const_k_iSteamAppListCallbacks = 3900;
int const_k_iSteamMusicCallbacks = 4000;
int const_k_iSteamMusicRemoteCallbacks = 4100;
int const_k_iClientVRCallbacks = 4200;
int const_k_iClientGameNotificationCallbacks = 4300;
int const_k_iSteamGameNotificationCallbacks = 4400;
int const_k_iSteamHTMLSurfaceCallbacks = 4500;
int const_k_iClientVideoCallbacks = 4600;
int const_k_iClientInventoryCallbacks = 4700;
int const_k_iClientBluetoothManagerCallbacks = 4800;
int const_k_iClientSharedConnectionCallbacks = 4900;
int const_k_ISteamParentalSettingsCallbacks = 5000;
int const_k_iClientShaderCallbacks = 5100;
int const_k_cchPersonaNameMax = 128;
int const_k_cwchPersonaNameMax = 32;
int const_k_cchMaxRichPresenceKeys = 20;
int const_k_cchMaxRichPresenceKeyLength = 64;
int const_k_cchMaxRichPresenceValueLength = 256;
int const_k_cchStatNameMax = 128;
int const_k_cchLeaderboardNameMax = 128;
int const_k_cLeaderboardDetailsMax = 64;
unsigned long const_k_SteamItemInstanceIDInvalid = 0xffffffff;
int const_k_SteamInventoryResultInvalid = -1;



// OpenVR Enums
// OpenVR Structs



S_API HSteamPipe
SteamAPI_ISteamClient_CreateSteamPipe(intptr_t
instancePtr);

S_API bool SteamAPI_ISteamClient_BReleaseSteamPipe(intptr_t instancePtr, HSteamPipe hSteamPipe);

S_API HSteamUser
SteamAPI_ISteamClient_ConnectToGlobalUser(intptr_t
instancePtr,
HSteamPipe hSteamPipe
);
S_API HSteamUser
SteamAPI_ISteamClient_CreateLocalUser(intptr_t
instancePtr,
HSteamPipe *phSteamPipe, EAccountType
eAccountType);

S_API void SteamAPI_ISteamClient_ReleaseUser(intptr_t instancePtr, HSteamPipe hSteamPipe, HSteamUser hUser);

S_API class ISteamUser *
SteamAPI_ISteamClient_GetISteamUser(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                    const char *pchVersion);

S_API class ISteamGameServer *
SteamAPI_ISteamClient_GetISteamGameServer(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                          const char *pchVersion);

S_API void SteamAPI_ISteamClient_SetLocalIPBinding(intptr_t instancePtr, uint32 unIP, uint16 usPort);

S_API class ISteamFriends *
SteamAPI_ISteamClient_GetISteamFriends(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                       const char *pchVersion);

S_API class ISteamUtils *
SteamAPI_ISteamClient_GetISteamUtils(intptr_t instancePtr, HSteamPipe hSteamPipe, const char *pchVersion);

S_API class ISteamMatchmaking *
SteamAPI_ISteamClient_GetISteamMatchmaking(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                           const char *pchVersion);

S_API class ISteamMatchmakingServers *
SteamAPI_ISteamClient_GetISteamMatchmakingServers(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                                  const char *pchVersion);

S_API void *
SteamAPI_ISteamClient_GetISteamGenericInterface(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                                const char *pchVersion);

S_API class ISteamUserStats *
SteamAPI_ISteamClient_GetISteamUserStats(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                         const char *pchVersion);

S_API class ISteamGameServerStats *
SteamAPI_ISteamClient_GetISteamGameServerStats(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                               const char *pchVersion);

S_API class ISteamApps *
SteamAPI_ISteamClient_GetISteamApps(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                    const char *pchVersion);

S_API class ISteamNetworking *
SteamAPI_ISteamClient_GetISteamNetworking(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                          const char *pchVersion);

S_API class ISteamRemoteStorage *
SteamAPI_ISteamClient_GetISteamRemoteStorage(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                             const char *pchVersion);

S_API class ISteamScreenshots *
SteamAPI_ISteamClient_GetISteamScreenshots(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                           const char *pchVersion);

S_API uint32
SteamAPI_ISteamClient_GetIPCCallCount(intptr_t
instancePtr);

S_API void SteamAPI_ISteamClient_SetWarningMessageHook(intptr_t instancePtr, SteamAPIWarningMessageHook_t pFunction);

S_API bool SteamAPI_ISteamClient_BShutdownIfAllPipesClosed(intptr_t instancePtr);

S_API class ISteamHTTP *
SteamAPI_ISteamClient_GetISteamHTTP(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                    const char *pchVersion);

S_API class ISteamController *
SteamAPI_ISteamClient_GetISteamController(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                          const char *pchVersion);

S_API class ISteamUGC *
SteamAPI_ISteamClient_GetISteamUGC(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                   const char *pchVersion);

S_API class ISteamAppList *
SteamAPI_ISteamClient_GetISteamAppList(intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe,
                                       const char *pchVersion);

S_API class ISteamMusic *
SteamAPI_ISteamClient_GetISteamMusic(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                     const char *pchVersion);

S_API class ISteamMusicRemote *
SteamAPI_ISteamClient_GetISteamMusicRemote(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                           const char *pchVersion);

S_API class ISteamHTMLSurface *
SteamAPI_ISteamClient_GetISteamHTMLSurface(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                           const char *pchVersion);

S_API class ISteamInventory *
SteamAPI_ISteamClient_GetISteamInventory(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                         const char *pchVersion);

S_API class ISteamVideo *
SteamAPI_ISteamClient_GetISteamVideo(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                     const char *pchVersion);

S_API class ISteamParentalSettings *
SteamAPI_ISteamClient_GetISteamParentalSettings(intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe,
                                                const char *pchVersion);

S_API HSteamUser
SteamAPI_ISteamUser_GetHSteamUser(intptr_t
instancePtr);

S_API bool SteamAPI_ISteamUser_BLoggedOn(intptr_t instancePtr);

S_API uint64
SteamAPI_ISteamUser_GetSteamID(intptr_t
instancePtr);

S_API int SteamAPI_ISteamUser_InitiateGameConnection(intptr_t instancePtr, void *pAuthBlob, int cbMaxAuthBlob,
                                                     class CSteamID steamIDGameServer, uint32 unIPServer,
                                                     uint16 usPortServer, bool bSecure);

S_API void SteamAPI_ISteamUser_TerminateGameConnection(intptr_t instancePtr, uint32 unIPServer, uint16 usPortServer);

S_API void SteamAPI_ISteamUser_TrackAppUsageEvent(intptr_t instancePtr, class CGameID gameID, int eAppUsageEvent,
                                                  const char *pchExtraInfo);

S_API bool SteamAPI_ISteamUser_GetUserDataFolder(intptr_t instancePtr, char *pchBuffer, int cubBuffer);

S_API void SteamAPI_ISteamUser_StartVoiceRecording(intptr_t instancePtr);

S_API void SteamAPI_ISteamUser_StopVoiceRecording(intptr_t instancePtr);

S_API EVoiceResult
SteamAPI_ISteamUser_GetAvailableVoice(intptr_t
instancePtr,
uint32 *pcbCompressed, uint32
* pcbUncompressed_Deprecated,
uint32 nUncompressedVoiceDesiredSampleRate_Deprecated
);
S_API EVoiceResult
SteamAPI_ISteamUser_GetVoice(intptr_t
instancePtr,
bool bWantCompressed,
void *pDestBuffer, uint32
cbDestBufferSize,
uint32 *nBytesWritten,
bool bWantUncompressed_Deprecated,
void *pUncompressedDestBuffer_Deprecated, uint32
cbUncompressedDestBufferSize_Deprecated,
uint32 *nUncompressBytesWritten_Deprecated, uint32
nUncompressedVoiceDesiredSampleRate_Deprecated);
S_API EVoiceResult
SteamAPI_ISteamUser_DecompressVoice(intptr_t
instancePtr,
const void *pCompressed, uint32
cbCompressed,
void *pDestBuffer, uint32
cbDestBufferSize,
uint32 *nBytesWritten, uint32
nDesiredSampleRate);
S_API uint32
SteamAPI_ISteamUser_GetVoiceOptimalSampleRate(intptr_t
instancePtr);
S_API HAuthTicket
SteamAPI_ISteamUser_GetAuthSessionTicket(intptr_t
instancePtr,
void *pTicket,
int cbMaxTicket, uint32
* pcbTicket);
S_API EBeginAuthSessionResult
SteamAPI_ISteamUser_BeginAuthSession(intptr_t
instancePtr,
const void *pAuthTicket,
int cbAuthTicket,

class CSteamID steamID

);

S_API void SteamAPI_ISteamUser_EndAuthSession(intptr_t instancePtr, class CSteamID steamID);

S_API void SteamAPI_ISteamUser_CancelAuthTicket(intptr_t instancePtr, HAuthTicket hAuthTicket);

S_API EUserHasLicenseForAppResult
SteamAPI_ISteamUser_UserHasLicenseForApp(intptr_t
instancePtr,

class CSteamID steamID, AppId_t

appID);

S_API bool SteamAPI_ISteamUser_BIsBehindNAT(intptr_t instancePtr);

S_API void SteamAPI_ISteamUser_AdvertiseGame(intptr_t instancePtr, class CSteamID steamIDGameServer, uint32 unIPServer,
                                             uint16 usPortServer);

S_API SteamAPICall_t
SteamAPI_ISteamUser_RequestEncryptedAppTicket(intptr_t
instancePtr,
void *pDataToInclude,
int cbDataToInclude
);

S_API bool
SteamAPI_ISteamUser_GetEncryptedAppTicket(intptr_t instancePtr, void *pTicket, int cbMaxTicket, uint32 *pcbTicket);

S_API int SteamAPI_ISteamUser_GetGameBadgeLevel(intptr_t instancePtr, int nSeries, bool bFoil);

S_API int SteamAPI_ISteamUser_GetPlayerSteamLevel(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamUser_RequestStoreAuthURL(intptr_t
instancePtr,
const char *pchRedirectURL
);

S_API bool SteamAPI_ISteamUser_BIsPhoneVerified(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUser_BIsTwoFactorEnabled(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUser_BIsPhoneIdentifying(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUser_BIsPhoneRequiringVerification(intptr_t instancePtr);

S_API const char *SteamAPI_ISteamFriends_GetPersonaName(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamFriends_SetPersonaName(intptr_t
instancePtr,
const char *pchPersonaName
);
S_API EPersonaState
SteamAPI_ISteamFriends_GetPersonaState(intptr_t
instancePtr);

S_API int SteamAPI_ISteamFriends_GetFriendCount(intptr_t instancePtr, int iFriendFlags);

S_API uint64
SteamAPI_ISteamFriends_GetFriendByIndex(intptr_t
instancePtr,
int iFriend,
int iFriendFlags
);
S_API EFriendRelationship
SteamAPI_ISteamFriends_GetFriendRelationship(intptr_t
instancePtr,

class CSteamID steamIDFriend

);
S_API EPersonaState
SteamAPI_ISteamFriends_GetFriendPersonaState(intptr_t
instancePtr,

class CSteamID steamIDFriend

);

S_API const char *SteamAPI_ISteamFriends_GetFriendPersonaName(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API bool SteamAPI_ISteamFriends_GetFriendGamePlayed(intptr_t instancePtr, class CSteamID steamIDFriend,
                                                      struct FriendGameInfo_t *pFriendGameInfo);

S_API const char *SteamAPI_ISteamFriends_GetFriendPersonaNameHistory(intptr_t instancePtr, class CSteamID steamIDFriend,
                                                                     int iPersonaName);

S_API int SteamAPI_ISteamFriends_GetFriendSteamLevel(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API const char *SteamAPI_ISteamFriends_GetPlayerNickname(intptr_t instancePtr, class CSteamID steamIDPlayer);

S_API int SteamAPI_ISteamFriends_GetFriendsGroupCount(intptr_t instancePtr);

S_API FriendsGroupID_t
SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex(intptr_t
instancePtr,
int iFG
);

S_API const char *SteamAPI_ISteamFriends_GetFriendsGroupName(intptr_t instancePtr, FriendsGroupID_t friendsGroupID);

S_API int SteamAPI_ISteamFriends_GetFriendsGroupMembersCount(intptr_t instancePtr, FriendsGroupID_t friendsGroupID);

S_API void SteamAPI_ISteamFriends_GetFriendsGroupMembersList(intptr_t instancePtr, FriendsGroupID_t friendsGroupID,
                                                             class CSteamID *pOutSteamIDMembers, int nMembersCount);

S_API bool SteamAPI_ISteamFriends_HasFriend(intptr_t instancePtr, class CSteamID steamIDFriend, int iFriendFlags);

S_API int SteamAPI_ISteamFriends_GetClanCount(intptr_t instancePtr);

S_API uint64
SteamAPI_ISteamFriends_GetClanByIndex(intptr_t
instancePtr,
int iClan
);

S_API const char *SteamAPI_ISteamFriends_GetClanName(intptr_t instancePtr, class CSteamID steamIDClan);

S_API const char *SteamAPI_ISteamFriends_GetClanTag(intptr_t instancePtr, class CSteamID steamIDClan);

S_API bool SteamAPI_ISteamFriends_GetClanActivityCounts(intptr_t instancePtr, class CSteamID steamIDClan, int *pnOnline,
                                                        int *pnInGame, int *pnChatting);

S_API SteamAPICall_t
SteamAPI_ISteamFriends_DownloadClanActivityCounts(intptr_t
instancePtr,

class CSteamID *psteamIDClans,

int cClansToRequest
);

S_API int SteamAPI_ISteamFriends_GetFriendCountFromSource(intptr_t instancePtr, class CSteamID steamIDSource);

S_API uint64
SteamAPI_ISteamFriends_GetFriendFromSourceByIndex(intptr_t
instancePtr,

class CSteamID steamIDSource,

int iFriend
);

S_API bool
SteamAPI_ISteamFriends_IsUserInSource(intptr_t instancePtr, class CSteamID steamIDUser, class CSteamID steamIDSource);

S_API void
SteamAPI_ISteamFriends_SetInGameVoiceSpeaking(intptr_t instancePtr, class CSteamID steamIDUser, bool bSpeaking);

S_API void SteamAPI_ISteamFriends_ActivateGameOverlay(intptr_t instancePtr, const char *pchDialog);

S_API void
SteamAPI_ISteamFriends_ActivateGameOverlayToUser(intptr_t instancePtr, const char *pchDialog, class CSteamID steamID);

S_API void SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage(intptr_t instancePtr, const char *pchURL);

S_API void
SteamAPI_ISteamFriends_ActivateGameOverlayToStore(intptr_t instancePtr, AppId_t nAppID, EOverlayToStoreFlag eFlag);

S_API void SteamAPI_ISteamFriends_SetPlayedWith(intptr_t instancePtr, class CSteamID steamIDUserPlayedWith);

S_API void SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog(intptr_t instancePtr, class CSteamID steamIDLobby);

S_API int SteamAPI_ISteamFriends_GetSmallFriendAvatar(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API int SteamAPI_ISteamFriends_GetMediumFriendAvatar(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API int SteamAPI_ISteamFriends_GetLargeFriendAvatar(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API bool
SteamAPI_ISteamFriends_RequestUserInformation(intptr_t instancePtr, class CSteamID steamIDUser, bool bRequireNameOnly);

S_API SteamAPICall_t
SteamAPI_ISteamFriends_RequestClanOfficerList(intptr_t
instancePtr,

class CSteamID steamIDClan

);
S_API uint64
SteamAPI_ISteamFriends_GetClanOwner(intptr_t
instancePtr,

class CSteamID steamIDClan

);

S_API int SteamAPI_ISteamFriends_GetClanOfficerCount(intptr_t instancePtr, class CSteamID steamIDClan);

S_API uint64
SteamAPI_ISteamFriends_GetClanOfficerByIndex(intptr_t
instancePtr,

class CSteamID steamIDClan,

int iOfficer
);
S_API uint32
SteamAPI_ISteamFriends_GetUserRestrictions(intptr_t
instancePtr);

S_API bool SteamAPI_ISteamFriends_SetRichPresence(intptr_t instancePtr, const char *pchKey, const char *pchValue);

S_API void SteamAPI_ISteamFriends_ClearRichPresence(intptr_t instancePtr);

S_API const char *
SteamAPI_ISteamFriends_GetFriendRichPresence(intptr_t instancePtr, class CSteamID steamIDFriend, const char *pchKey);

S_API int SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API const char *
SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex(intptr_t instancePtr, class CSteamID steamIDFriend, int iKey);

S_API void SteamAPI_ISteamFriends_RequestFriendRichPresence(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API bool SteamAPI_ISteamFriends_InviteUserToGame(intptr_t instancePtr, class CSteamID steamIDFriend,
                                                   const char *pchConnectString);

S_API int SteamAPI_ISteamFriends_GetCoplayFriendCount(intptr_t instancePtr);

S_API uint64
SteamAPI_ISteamFriends_GetCoplayFriend(intptr_t
instancePtr,
int iCoplayFriend
);

S_API int SteamAPI_ISteamFriends_GetFriendCoplayTime(intptr_t instancePtr, class CSteamID steamIDFriend);

S_API AppId_t
SteamAPI_ISteamFriends_GetFriendCoplayGame(intptr_t
instancePtr,

class CSteamID steamIDFriend

);
S_API SteamAPICall_t
SteamAPI_ISteamFriends_JoinClanChatRoom(intptr_t
instancePtr,

class CSteamID steamIDClan

);

S_API bool SteamAPI_ISteamFriends_LeaveClanChatRoom(intptr_t instancePtr, class CSteamID steamIDClan);

S_API int SteamAPI_ISteamFriends_GetClanChatMemberCount(intptr_t instancePtr, class CSteamID steamIDClan);

S_API uint64
SteamAPI_ISteamFriends_GetChatMemberByIndex(intptr_t
instancePtr,

class CSteamID steamIDClan,

int iUser
);

S_API bool
SteamAPI_ISteamFriends_SendClanChatMessage(intptr_t instancePtr, class CSteamID steamIDClanChat, const char *pchText);

S_API int SteamAPI_ISteamFriends_GetClanChatMessage(intptr_t instancePtr, class CSteamID steamIDClanChat, int iMessage,
                                                    void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType,
                                                    class CSteamID *psteamidChatter);

S_API bool SteamAPI_ISteamFriends_IsClanChatAdmin(intptr_t instancePtr, class CSteamID steamIDClanChat,
                                                  class CSteamID steamIDUser);

S_API bool SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam(intptr_t instancePtr, class CSteamID steamIDClanChat);

S_API bool SteamAPI_ISteamFriends_OpenClanChatWindowInSteam(intptr_t instancePtr, class CSteamID steamIDClanChat);

S_API bool SteamAPI_ISteamFriends_CloseClanChatWindowInSteam(intptr_t instancePtr, class CSteamID steamIDClanChat);

S_API bool SteamAPI_ISteamFriends_SetListenForFriendsMessages(intptr_t instancePtr, bool bInterceptEnabled);

S_API bool SteamAPI_ISteamFriends_ReplyToFriendMessage(intptr_t instancePtr, class CSteamID steamIDFriend,
                                                       const char *pchMsgToSend);

S_API int SteamAPI_ISteamFriends_GetFriendMessage(intptr_t instancePtr, class CSteamID steamIDFriend, int iMessageID,
                                                  void *pvData, int cubData, EChatEntryType *peChatEntryType);

S_API SteamAPICall_t
SteamAPI_ISteamFriends_GetFollowerCount(intptr_t
instancePtr,

class CSteamID steamID

);
S_API SteamAPICall_t
SteamAPI_ISteamFriends_IsFollowing(intptr_t
instancePtr,

class CSteamID steamID

);
S_API SteamAPICall_t
SteamAPI_ISteamFriends_EnumerateFollowingList(intptr_t
instancePtr,
uint32 unStartIndex
);

S_API bool SteamAPI_ISteamFriends_IsClanPublic(intptr_t instancePtr, class CSteamID steamIDClan);

S_API bool SteamAPI_ISteamFriends_IsClanOfficialGameGroup(intptr_t instancePtr, class CSteamID steamIDClan);

S_API uint32
SteamAPI_ISteamUtils_GetSecondsSinceAppActive(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamUtils_GetSecondsSinceComputerActive(intptr_t
instancePtr);
S_API EUniverse
SteamAPI_ISteamUtils_GetConnectedUniverse(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamUtils_GetServerRealTime(intptr_t
instancePtr);

S_API const char *SteamAPI_ISteamUtils_GetIPCountry(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUtils_GetImageSize(intptr_t instancePtr, int iImage, uint32 *pnWidth, uint32 *pnHeight);

S_API bool SteamAPI_ISteamUtils_GetImageRGBA(intptr_t instancePtr, int iImage, uint8 *pubDest, int nDestBufferSize);

S_API bool SteamAPI_ISteamUtils_GetCSERIPPort(intptr_t instancePtr, uint32 *unIP, uint16 *usPort);

S_API uint8
SteamAPI_ISteamUtils_GetCurrentBatteryPower(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamUtils_GetAppID(intptr_t
instancePtr);

S_API void
SteamAPI_ISteamUtils_SetOverlayNotificationPosition(intptr_t instancePtr, ENotificationPosition eNotificationPosition);

S_API bool SteamAPI_ISteamUtils_IsAPICallCompleted(intptr_t instancePtr, SteamAPICall_t hSteamAPICall, bool *pbFailed);

S_API ESteamAPICallFailure
SteamAPI_ISteamUtils_GetAPICallFailureReason(intptr_t
instancePtr,
SteamAPICall_t hSteamAPICall
);

S_API bool SteamAPI_ISteamUtils_GetAPICallResult(intptr_t instancePtr, SteamAPICall_t hSteamAPICall, void *pCallback,
                                                 int cubCallback, int iCallbackExpected, bool *pbFailed);

S_API uint32
SteamAPI_ISteamUtils_GetIPCCallCount(intptr_t
instancePtr);

S_API void SteamAPI_ISteamUtils_SetWarningMessageHook(intptr_t instancePtr, SteamAPIWarningMessageHook_t pFunction);

S_API bool SteamAPI_ISteamUtils_IsOverlayEnabled(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUtils_BOverlayNeedsPresent(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamUtils_CheckFileSignature(intptr_t
instancePtr,
const char *szFileName
);

S_API bool SteamAPI_ISteamUtils_ShowGamepadTextInput(intptr_t instancePtr, EGamepadTextInputMode eInputMode,
                                                     EGamepadTextInputLineMode eLineInputMode,
                                                     const char *pchDescription, uint32 unCharMax,
                                                     const char *pchExistingText);

S_API uint32
SteamAPI_ISteamUtils_GetEnteredGamepadTextLength(intptr_t
instancePtr);

S_API bool SteamAPI_ISteamUtils_GetEnteredGamepadTextInput(intptr_t instancePtr, char *pchText, uint32 cchText);

S_API const char *SteamAPI_ISteamUtils_GetSteamUILanguage(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUtils_IsSteamRunningInVR(intptr_t instancePtr);

S_API void
SteamAPI_ISteamUtils_SetOverlayNotificationInset(intptr_t instancePtr, int nHorizontalInset, int nVerticalInset);

S_API bool SteamAPI_ISteamUtils_IsSteamInBigPictureMode(intptr_t instancePtr);

S_API void SteamAPI_ISteamUtils_StartVRDashboard(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled(intptr_t instancePtr);

S_API void SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled(intptr_t instancePtr, bool bEnabled);

S_API int SteamAPI_ISteamMatchmaking_GetFavoriteGameCount(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMatchmaking_GetFavoriteGame(intptr_t instancePtr, int iGame, AppId_t *pnAppID, uint32 *pnIP,
                                                      uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags,
                                                      uint32 *pRTime32LastPlayedOnServer);

S_API int SteamAPI_ISteamMatchmaking_AddFavoriteGame(intptr_t instancePtr, AppId_t nAppID, uint32 nIP, uint16 nConnPort,
                                                     uint16 nQueryPort, uint32 unFlags,
                                                     uint32 rTime32LastPlayedOnServer);

S_API bool
SteamAPI_ISteamMatchmaking_RemoveFavoriteGame(intptr_t instancePtr, AppId_t nAppID, uint32 nIP, uint16 nConnPort,
                                              uint16 nQueryPort, uint32 unFlags);

S_API SteamAPICall_t
SteamAPI_ISteamMatchmaking_RequestLobbyList(intptr_t
instancePtr);

S_API void SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter(intptr_t instancePtr, const char *pchKeyToMatch,
                                                                      const char *pchValueToMatch,
                                                                      ELobbyComparison eComparisonType);

S_API void
SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter(intptr_t instancePtr, const char *pchKeyToMatch,
                                                              int nValueToMatch, ELobbyComparison eComparisonType);

S_API void
SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter(intptr_t instancePtr, const char *pchKeyToMatch,
                                                              int nValueToBeCloseTo);

S_API void
SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable(intptr_t instancePtr, int nSlotsAvailable);

S_API void SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter(intptr_t instancePtr,
                                                                        ELobbyDistanceFilter eLobbyDistanceFilter);

S_API void SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter(intptr_t instancePtr, int cMaxResults);

S_API void SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter(intptr_t instancePtr,
                                                                                 class CSteamID steamIDLobby);

S_API uint64
SteamAPI_ISteamMatchmaking_GetLobbyByIndex(intptr_t
instancePtr,
int iLobby
);
S_API SteamAPICall_t
SteamAPI_ISteamMatchmaking_CreateLobby(intptr_t
instancePtr,
ELobbyType eLobbyType,
int cMaxMembers
);
S_API SteamAPICall_t
SteamAPI_ISteamMatchmaking_JoinLobby(intptr_t
instancePtr,

class CSteamID steamIDLobby

);

S_API void SteamAPI_ISteamMatchmaking_LeaveLobby(intptr_t instancePtr, class CSteamID steamIDLobby);

S_API bool SteamAPI_ISteamMatchmaking_InviteUserToLobby(intptr_t instancePtr, class CSteamID steamIDLobby,
                                                        class CSteamID steamIDInvitee);

S_API int SteamAPI_ISteamMatchmaking_GetNumLobbyMembers(intptr_t instancePtr, class CSteamID steamIDLobby);

S_API uint64
SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex(intptr_t
instancePtr,

class CSteamID steamIDLobby,

int iMember
);

S_API const char *
SteamAPI_ISteamMatchmaking_GetLobbyData(intptr_t instancePtr, class CSteamID steamIDLobby, const char *pchKey);

S_API bool
SteamAPI_ISteamMatchmaking_SetLobbyData(intptr_t instancePtr, class CSteamID steamIDLobby, const char *pchKey,
                                        const char *pchValue);

S_API int SteamAPI_ISteamMatchmaking_GetLobbyDataCount(intptr_t instancePtr, class CSteamID steamIDLobby);

S_API bool
SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex(intptr_t instancePtr, class CSteamID steamIDLobby, int iLobbyData,
                                               char *pchKey, int cchKeyBufferSize, char *pchValue,
                                               int cchValueBufferSize);

S_API bool
SteamAPI_ISteamMatchmaking_DeleteLobbyData(intptr_t instancePtr, class CSteamID steamIDLobby, const char *pchKey);

S_API const char *SteamAPI_ISteamMatchmaking_GetLobbyMemberData(intptr_t instancePtr, class CSteamID steamIDLobby,
                                                                class CSteamID steamIDUser, const char *pchKey);

S_API void
SteamAPI_ISteamMatchmaking_SetLobbyMemberData(intptr_t instancePtr, class CSteamID steamIDLobby, const char *pchKey,
                                              const char *pchValue);

S_API bool
SteamAPI_ISteamMatchmaking_SendLobbyChatMsg(intptr_t instancePtr, class CSteamID steamIDLobby, const void *pvMsgBody,
                                            int cubMsgBody);

S_API int SteamAPI_ISteamMatchmaking_GetLobbyChatEntry(intptr_t instancePtr, class CSteamID steamIDLobby, int iChatID,
                                                       class CSteamID *pSteamIDUser, void *pvData, int cubData,
                                                       EChatEntryType *peChatEntryType);

S_API bool SteamAPI_ISteamMatchmaking_RequestLobbyData(intptr_t instancePtr, class CSteamID steamIDLobby);

S_API void
SteamAPI_ISteamMatchmaking_SetLobbyGameServer(intptr_t instancePtr, class CSteamID steamIDLobby, uint32 unGameServerIP,
                                              uint16 unGameServerPort, class CSteamID steamIDGameServer);

S_API bool SteamAPI_ISteamMatchmaking_GetLobbyGameServer(intptr_t instancePtr, class CSteamID steamIDLobby,
                                                         uint32 *punGameServerIP, uint16 *punGameServerPort,
                                                         class CSteamID *psteamIDGameServer);

S_API bool
SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit(intptr_t instancePtr, class CSteamID steamIDLobby, int cMaxMembers);

S_API int SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit(intptr_t instancePtr, class CSteamID steamIDLobby);

S_API bool
SteamAPI_ISteamMatchmaking_SetLobbyType(intptr_t instancePtr, class CSteamID steamIDLobby, ELobbyType eLobbyType);

S_API bool
SteamAPI_ISteamMatchmaking_SetLobbyJoinable(intptr_t instancePtr, class CSteamID steamIDLobby, bool bLobbyJoinable);

S_API uint64
SteamAPI_ISteamMatchmaking_GetLobbyOwner(intptr_t
instancePtr,

class CSteamID steamIDLobby

);

S_API bool SteamAPI_ISteamMatchmaking_SetLobbyOwner(intptr_t instancePtr, class CSteamID steamIDLobby,
                                                    class CSteamID steamIDNewOwner);

S_API bool SteamAPI_ISteamMatchmaking_SetLinkedLobby(intptr_t instancePtr, class CSteamID steamIDLobby,
                                                     class CSteamID steamIDLobbyDependent);

S_API void
SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded(intptr_t instancePtr, HServerListRequest hRequest,
                                                             int iServer);

S_API void
SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond(intptr_t instancePtr, HServerListRequest hRequest,
                                                                   int iServer);

S_API void
SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete(intptr_t instancePtr, HServerListRequest hRequest,
                                                             EMatchMakingServerResponse response);

S_API void SteamAPI_ISteamMatchmakingPingResponse_ServerResponded(intptr_t instancePtr, class gameserveritem_t &server);

S_API void SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond(intptr_t instancePtr);

S_API void
SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList(intptr_t instancePtr, const char *pchName, int nScore,
                                                          float flTimePlayed);

S_API void SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond(intptr_t instancePtr);

S_API void SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete(intptr_t instancePtr);

S_API void
SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded(intptr_t instancePtr, const char *pchRule, const char *pchValue);

S_API void SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond(intptr_t instancePtr);

S_API void SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete(intptr_t instancePtr);

S_API HServerListRequest
SteamAPI_ISteamMatchmakingServers_RequestInternetServerList(intptr_t
instancePtr,
AppId_t iApp,
struct MatchMakingKeyValuePair_t **ppchFilters, uint32
nFilters,

class ISteamMatchmakingServerListResponse *pRequestServersResponse

);
S_API HServerListRequest
SteamAPI_ISteamMatchmakingServers_RequestLANServerList(intptr_t
instancePtr,
AppId_t iApp,

class ISteamMatchmakingServerListResponse *pRequestServersResponse

);
S_API HServerListRequest
SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList(intptr_t
instancePtr,
AppId_t iApp,
struct MatchMakingKeyValuePair_t **ppchFilters, uint32
nFilters,

class ISteamMatchmakingServerListResponse *pRequestServersResponse

);
S_API HServerListRequest
SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList(intptr_t
instancePtr,
AppId_t iApp,
struct MatchMakingKeyValuePair_t **ppchFilters, uint32
nFilters,

class ISteamMatchmakingServerListResponse *pRequestServersResponse

);
S_API HServerListRequest
SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList(intptr_t
instancePtr,
AppId_t iApp,
struct MatchMakingKeyValuePair_t **ppchFilters, uint32
nFilters,

class ISteamMatchmakingServerListResponse *pRequestServersResponse

);
S_API HServerListRequest
SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList(intptr_t
instancePtr,
AppId_t iApp,
struct MatchMakingKeyValuePair_t **ppchFilters, uint32
nFilters,

class ISteamMatchmakingServerListResponse *pRequestServersResponse

);

S_API void
SteamAPI_ISteamMatchmakingServers_ReleaseRequest(intptr_t instancePtr, HServerListRequest hServerListRequest);

S_API class gameserveritem_t *
SteamAPI_ISteamMatchmakingServers_GetServerDetails(intptr_t instancePtr, HServerListRequest hRequest, int iServer);

S_API void SteamAPI_ISteamMatchmakingServers_CancelQuery(intptr_t instancePtr, HServerListRequest hRequest);

S_API void SteamAPI_ISteamMatchmakingServers_RefreshQuery(intptr_t instancePtr, HServerListRequest hRequest);

S_API bool SteamAPI_ISteamMatchmakingServers_IsRefreshing(intptr_t instancePtr, HServerListRequest hRequest);

S_API int SteamAPI_ISteamMatchmakingServers_GetServerCount(intptr_t instancePtr, HServerListRequest hRequest);

S_API void
SteamAPI_ISteamMatchmakingServers_RefreshServer(intptr_t instancePtr, HServerListRequest hRequest, int iServer);

S_API HServerQuery
SteamAPI_ISteamMatchmakingServers_PingServer(intptr_t
instancePtr,
uint32 unIP, uint16
usPort,

class ISteamMatchmakingPingResponse *pRequestServersResponse

);
S_API HServerQuery
SteamAPI_ISteamMatchmakingServers_PlayerDetails(intptr_t
instancePtr,
uint32 unIP, uint16
usPort,

class ISteamMatchmakingPlayersResponse *pRequestServersResponse

);
S_API HServerQuery
SteamAPI_ISteamMatchmakingServers_ServerRules(intptr_t
instancePtr,
uint32 unIP, uint16
usPort,

class ISteamMatchmakingRulesResponse *pRequestServersResponse

);

S_API void SteamAPI_ISteamMatchmakingServers_CancelServerQuery(intptr_t instancePtr, HServerQuery hServerQuery);

S_API bool
SteamAPI_ISteamRemoteStorage_FileWrite(intptr_t instancePtr, const char *pchFile, const void *pvData, int32 cubData);

S_API int32
SteamAPI_ISteamRemoteStorage_FileRead(intptr_t
instancePtr,
const char *pchFile,
void *pvData, int32
cubDataToRead);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_FileWriteAsync(intptr_t
instancePtr,
const char *pchFile,
const void *pvData, uint32
cubData);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_FileReadAsync(intptr_t
instancePtr,
const char *pchFile, uint32
nOffset,
uint32 cubToRead
);

S_API bool
SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete(intptr_t instancePtr, SteamAPICall_t hReadCall, void *pvBuffer,
                                                   uint32 cubToRead);

S_API bool SteamAPI_ISteamRemoteStorage_FileForget(intptr_t instancePtr, const char *pchFile);

S_API bool SteamAPI_ISteamRemoteStorage_FileDelete(intptr_t instancePtr, const char *pchFile);

S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_FileShare(intptr_t
instancePtr,
const char *pchFile
);

S_API bool SteamAPI_ISteamRemoteStorage_SetSyncPlatforms(intptr_t instancePtr, const char *pchFile,
                                                         ERemoteStoragePlatform eRemoteStoragePlatform);

S_API UGCFileWriteStreamHandle_t
SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen(intptr_t
instancePtr,
const char *pchFile
);

S_API bool
SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk(intptr_t instancePtr, UGCFileWriteStreamHandle_t writeHandle,
                                                       const void *pvData, int32 cubData);

S_API bool
SteamAPI_ISteamRemoteStorage_FileWriteStreamClose(intptr_t instancePtr, UGCFileWriteStreamHandle_t writeHandle);

S_API bool
SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel(intptr_t instancePtr, UGCFileWriteStreamHandle_t writeHandle);

S_API bool SteamAPI_ISteamRemoteStorage_FileExists(intptr_t instancePtr, const char *pchFile);

S_API bool SteamAPI_ISteamRemoteStorage_FilePersisted(intptr_t instancePtr, const char *pchFile);

S_API int32
SteamAPI_ISteamRemoteStorage_GetFileSize(intptr_t
instancePtr,
const char *pchFile
);
S_API int64
SteamAPI_ISteamRemoteStorage_GetFileTimestamp(intptr_t
instancePtr,
const char *pchFile
);
S_API ERemoteStoragePlatform
SteamAPI_ISteamRemoteStorage_GetSyncPlatforms(intptr_t
instancePtr,
const char *pchFile
);
S_API int32
SteamAPI_ISteamRemoteStorage_GetFileCount(intptr_t
instancePtr);

S_API const char *
SteamAPI_ISteamRemoteStorage_GetFileNameAndSize(intptr_t instancePtr, int iFile, int32 *pnFileSizeInBytes);

S_API bool SteamAPI_ISteamRemoteStorage_GetQuota(intptr_t instancePtr, uint64 *pnTotalBytes, uint64 *puAvailableBytes);

S_API bool SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount(intptr_t instancePtr);

S_API bool SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp(intptr_t instancePtr);

S_API void SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp(intptr_t instancePtr, bool bEnabled);

S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_UGCDownload(intptr_t
instancePtr,
UGCHandle_t hContent, uint32
unPriority);

S_API bool SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress(intptr_t instancePtr, UGCHandle_t hContent,
                                                               int32 *pnBytesDownloaded, int32 *pnBytesExpected);

S_API bool SteamAPI_ISteamRemoteStorage_GetUGCDetails(intptr_t instancePtr, UGCHandle_t hContent, AppId_t *pnAppID,
                                                      char **ppchName, int32 *pnFileSizeInBytes,
                                                      class CSteamID *pSteamIDOwner);

S_API int32
SteamAPI_ISteamRemoteStorage_UGCRead(intptr_t
instancePtr,
UGCHandle_t hContent,
void *pvData, int32
cubDataToRead,
uint32 cOffset, EUGCReadAction
eAction);
S_API int32
SteamAPI_ISteamRemoteStorage_GetCachedUGCCount(intptr_t
instancePtr);
S_API UGCHandle_t
SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle(intptr_t
instancePtr,
int32 iCachedContent
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_PublishWorkshopFile(intptr_t
instancePtr,
const char *pchFile,
const char *pchPreviewFile, AppId_t
nConsumerAppId,
const char *pchTitle,
const char *pchDescription, ERemoteStoragePublishedFileVisibility
eVisibility,
struct SteamParamStringArray_t *pTags, EWorkshopFileType
eWorkshopFileType);
S_API PublishedFileUpdateHandle_t
SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId
);

S_API bool
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile(intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle,
                                                     const char *pchFile);

S_API bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile(intptr_t instancePtr,
                                                                       PublishedFileUpdateHandle_t updateHandle,
                                                                       const char *pchPreviewFile);

S_API bool
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle(intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle,
                                                      const char *pchTitle);

S_API bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription(intptr_t instancePtr,
                                                                       PublishedFileUpdateHandle_t updateHandle,
                                                                       const char *pchDescription);

S_API bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility(intptr_t instancePtr,
                                                                      PublishedFileUpdateHandle_t updateHandle,
                                                                      ERemoteStoragePublishedFileVisibility eVisibility);

S_API bool
SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags(intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle,
                                                     struct SteamParamStringArray_t *pTags);

S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate(intptr_t
instancePtr,
PublishedFileUpdateHandle_t updateHandle
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId, uint32
unMaxSecondsOld);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_DeletePublishedFile(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles(intptr_t
instancePtr,
uint32 unStartIndex
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_SubscribePublishedFile(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles(intptr_t
instancePtr,
uint32 unStartIndex
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId
);

S_API bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription(intptr_t instancePtr,
                                                                                PublishedFileUpdateHandle_t updateHandle,
                                                                                const char *pchChangeDescription);

S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId,
bool bVoteUp
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles(intptr_t
instancePtr,

class CSteamID steamId, uint32

unStartIndex,
struct SteamParamStringArray_t *pRequiredTags,
struct SteamParamStringArray_t *pExcludedTags
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_PublishVideo(intptr_t
instancePtr,
EWorkshopVideoProvider eVideoProvider,
const char *pchVideoAccount,
const char *pchVideoIdentifier,
const char *pchPreviewFile, AppId_t
nConsumerAppId,
const char *pchTitle,
const char *pchDescription, ERemoteStoragePublishedFileVisibility
eVisibility,
struct SteamParamStringArray_t *pTags
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction(intptr_t
instancePtr,
PublishedFileId_t unPublishedFileId, EWorkshopFileAction
eAction);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction(intptr_t
instancePtr,
EWorkshopFileAction eAction, uint32
unStartIndex);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles(intptr_t
instancePtr,
EWorkshopEnumerationType eEnumerationType, uint32
unStartIndex,
uint32 unCount, uint32
unDays,
struct SteamParamStringArray_t *pTags,
struct SteamParamStringArray_t *pUserTags
);
S_API SteamAPICall_t
SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation(intptr_t
instancePtr,
UGCHandle_t hContent,
const char *pchLocation, uint32
unPriority);

S_API bool SteamAPI_ISteamUserStats_RequestCurrentStats(intptr_t instancePtr);

S_API bool SteamAPI_ISteamUserStats_GetStat(intptr_t instancePtr, const char *pchName, int32 *pData);

S_API bool SteamAPI_ISteamUserStats_GetStat0(intptr_t instancePtr, const char *pchName, float *pData);

S_API bool SteamAPI_ISteamUserStats_SetStat(intptr_t instancePtr, const char *pchName, int32 nData);

S_API bool SteamAPI_ISteamUserStats_SetStat0(intptr_t instancePtr, const char *pchName, float fData);

S_API bool
SteamAPI_ISteamUserStats_UpdateAvgRateStat(intptr_t instancePtr, const char *pchName, float flCountThisSession,
                                           double dSessionLength);

S_API bool SteamAPI_ISteamUserStats_GetAchievement(intptr_t instancePtr, const char *pchName, bool *pbAchieved);

S_API bool SteamAPI_ISteamUserStats_SetAchievement(intptr_t instancePtr, const char *pchName);

S_API bool SteamAPI_ISteamUserStats_ClearAchievement(intptr_t instancePtr, const char *pchName);

S_API bool
SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime(intptr_t instancePtr, const char *pchName, bool *pbAchieved,
                                                     uint32 *punUnlockTime);

S_API bool SteamAPI_ISteamUserStats_StoreStats(intptr_t instancePtr);

S_API int SteamAPI_ISteamUserStats_GetAchievementIcon(intptr_t instancePtr, const char *pchName);

S_API const char *
SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute(intptr_t instancePtr, const char *pchName, const char *pchKey);

S_API bool
SteamAPI_ISteamUserStats_IndicateAchievementProgress(intptr_t instancePtr, const char *pchName, uint32 nCurProgress,
                                                     uint32 nMaxProgress);

S_API uint32
SteamAPI_ISteamUserStats_GetNumAchievements(intptr_t
instancePtr);

S_API const char *SteamAPI_ISteamUserStats_GetAchievementName(intptr_t instancePtr, uint32 iAchievement);

S_API SteamAPICall_t
SteamAPI_ISteamUserStats_RequestUserStats(intptr_t
instancePtr,

class CSteamID steamIDUser

);

S_API bool SteamAPI_ISteamUserStats_GetUserStat(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                                int32 *pData);

S_API bool SteamAPI_ISteamUserStats_GetUserStat0(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                                 float *pData);

S_API bool
SteamAPI_ISteamUserStats_GetUserAchievement(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                            bool *pbAchieved);

S_API bool SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime(intptr_t instancePtr, class CSteamID steamIDUser,
                                                                    const char *pchName, bool *pbAchieved,
                                                                    uint32 *punUnlockTime);

S_API bool SteamAPI_ISteamUserStats_ResetAllStats(intptr_t instancePtr, bool bAchievementsToo);

S_API SteamAPICall_t
SteamAPI_ISteamUserStats_FindOrCreateLeaderboard(intptr_t
instancePtr,
const char *pchLeaderboardName, ELeaderboardSortMethod
eLeaderboardSortMethod,
ELeaderboardDisplayType eLeaderboardDisplayType
);
S_API SteamAPICall_t
SteamAPI_ISteamUserStats_FindLeaderboard(intptr_t
instancePtr,
const char *pchLeaderboardName
);

S_API const char *
SteamAPI_ISteamUserStats_GetLeaderboardName(intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard);

S_API int SteamAPI_ISteamUserStats_GetLeaderboardEntryCount(intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard);

S_API ELeaderboardSortMethod
SteamAPI_ISteamUserStats_GetLeaderboardSortMethod(intptr_t
instancePtr,
SteamLeaderboard_t hSteamLeaderboard
);
S_API ELeaderboardDisplayType
SteamAPI_ISteamUserStats_GetLeaderboardDisplayType(intptr_t
instancePtr,
SteamLeaderboard_t hSteamLeaderboard
);
S_API SteamAPICall_t
SteamAPI_ISteamUserStats_DownloadLeaderboardEntries(intptr_t
instancePtr,
SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest
eLeaderboardDataRequest,
int nRangeStart,
int nRangeEnd
);
S_API SteamAPICall_t
SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers(intptr_t
instancePtr,
SteamLeaderboard_t hSteamLeaderboard,

class CSteamID *prgUsers,

int cUsers
);

S_API bool SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry(intptr_t instancePtr,
                                                                  SteamLeaderboardEntries_t hSteamLeaderboardEntries,
                                                                  int index,
                                                                  struct LeaderboardEntry_t *pLeaderboardEntry,
                                                                  int32 *pDetails, int cDetailsMax);

S_API SteamAPICall_t
SteamAPI_ISteamUserStats_UploadLeaderboardScore(intptr_t
instancePtr,
SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod
eLeaderboardUploadScoreMethod,
int32 nScore,
const int32 *pScoreDetails,
int cScoreDetailsCount
);
S_API SteamAPICall_t
SteamAPI_ISteamUserStats_AttachLeaderboardUGC(intptr_t
instancePtr,
SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t
hUGC);
S_API SteamAPICall_t
SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers(intptr_t
instancePtr);
S_API SteamAPICall_t
SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages(intptr_t
instancePtr);

S_API int
SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo(intptr_t instancePtr, char *pchName, uint32 unNameBufLen,
                                                        float *pflPercent, bool *pbAchieved);

S_API int
SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo(intptr_t instancePtr, int iIteratorPrevious, char *pchName,
                                                            uint32 unNameBufLen, float *pflPercent, bool *pbAchieved);

S_API bool
SteamAPI_ISteamUserStats_GetAchievementAchievedPercent(intptr_t instancePtr, const char *pchName, float *pflPercent);

S_API SteamAPICall_t
SteamAPI_ISteamUserStats_RequestGlobalStats(intptr_t
instancePtr,
int nHistoryDays
);

S_API bool SteamAPI_ISteamUserStats_GetGlobalStat(intptr_t instancePtr, const char *pchStatName, int64 *pData);

S_API bool SteamAPI_ISteamUserStats_GetGlobalStat0(intptr_t instancePtr, const char *pchStatName, double *pData);

S_API int32
SteamAPI_ISteamUserStats_GetGlobalStatHistory(intptr_t
instancePtr,
const char *pchStatName, int64
* pData,
uint32 cubData
);
S_API int32
SteamAPI_ISteamUserStats_GetGlobalStatHistory0(intptr_t
instancePtr,
const char *pchStatName,
double *pData, uint32
cubData);

S_API bool SteamAPI_ISteamApps_BIsSubscribed(intptr_t instancePtr);

S_API bool SteamAPI_ISteamApps_BIsLowViolence(intptr_t instancePtr);

S_API bool SteamAPI_ISteamApps_BIsCybercafe(intptr_t instancePtr);

S_API bool SteamAPI_ISteamApps_BIsVACBanned(intptr_t instancePtr);

S_API const char *SteamAPI_ISteamApps_GetCurrentGameLanguage(intptr_t instancePtr);

S_API const char *SteamAPI_ISteamApps_GetAvailableGameLanguages(intptr_t instancePtr);

S_API bool SteamAPI_ISteamApps_BIsSubscribedApp(intptr_t instancePtr, AppId_t appID);

S_API bool SteamAPI_ISteamApps_BIsDlcInstalled(intptr_t instancePtr, AppId_t appID);

S_API uint32
SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime(intptr_t
instancePtr,
AppId_t nAppID
);

S_API bool SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend(intptr_t instancePtr);

S_API int SteamAPI_ISteamApps_GetDLCCount(intptr_t instancePtr);

S_API bool SteamAPI_ISteamApps_BGetDLCDataByIndex(intptr_t instancePtr, int iDLC, AppId_t *pAppID, bool *pbAvailable,
                                                  char *pchName, int cchNameBufferSize);

S_API void SteamAPI_ISteamApps_InstallDLC(intptr_t instancePtr, AppId_t nAppID);

S_API void SteamAPI_ISteamApps_UninstallDLC(intptr_t instancePtr, AppId_t nAppID);

S_API void SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey(intptr_t instancePtr, AppId_t nAppID);

S_API bool SteamAPI_ISteamApps_GetCurrentBetaName(intptr_t instancePtr, char *pchName, int cchNameBufferSize);

S_API bool SteamAPI_ISteamApps_MarkContentCorrupt(intptr_t instancePtr, bool bMissingFilesOnly);

S_API uint32
SteamAPI_ISteamApps_GetInstalledDepots(intptr_t
instancePtr,
AppId_t appID, DepotId_t
* pvecDepots,
uint32 cMaxDepots
);
S_API uint32
SteamAPI_ISteamApps_GetAppInstallDir(intptr_t
instancePtr,
AppId_t appID,
char *pchFolder, uint32
cchFolderBufferSize);

S_API bool SteamAPI_ISteamApps_BIsAppInstalled(intptr_t instancePtr, AppId_t appID);

S_API uint64
SteamAPI_ISteamApps_GetAppOwner(intptr_t
instancePtr);

S_API const char *SteamAPI_ISteamApps_GetLaunchQueryParam(intptr_t instancePtr, const char *pchKey);

S_API bool SteamAPI_ISteamApps_GetDlcDownloadProgress(intptr_t instancePtr, AppId_t nAppID, uint64 *punBytesDownloaded,
                                                      uint64 *punBytesTotal);

S_API int SteamAPI_ISteamApps_GetAppBuildId(intptr_t instancePtr);

S_API void SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamApps_GetFileDetails(intptr_t
instancePtr,
const char *pszFileName
);

S_API bool
SteamAPI_ISteamNetworking_SendP2PPacket(intptr_t instancePtr, class CSteamID steamIDRemote, const void *pubData,
                                        uint32 cubData, EP2PSend eP2PSendType, int nChannel);

S_API bool SteamAPI_ISteamNetworking_IsP2PPacketAvailable(intptr_t instancePtr, uint32 *pcubMsgSize, int nChannel);

S_API bool
SteamAPI_ISteamNetworking_ReadP2PPacket(intptr_t instancePtr, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize,
                                        class CSteamID *psteamIDRemote, int nChannel);

S_API bool SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser(intptr_t instancePtr, class CSteamID steamIDRemote);

S_API bool SteamAPI_ISteamNetworking_CloseP2PSessionWithUser(intptr_t instancePtr, class CSteamID steamIDRemote);

S_API bool
SteamAPI_ISteamNetworking_CloseP2PChannelWithUser(intptr_t instancePtr, class CSteamID steamIDRemote, int nChannel);

S_API bool SteamAPI_ISteamNetworking_GetP2PSessionState(intptr_t instancePtr, class CSteamID steamIDRemote,
                                                        struct P2PSessionState_t *pConnectionState);

S_API bool SteamAPI_ISteamNetworking_AllowP2PPacketRelay(intptr_t instancePtr, bool bAllow);

S_API SNetListenSocket_t
SteamAPI_ISteamNetworking_CreateListenSocket(intptr_t
instancePtr,
int nVirtualP2PPort, uint32
nIP,
uint16 nPort,
bool bAllowUseOfPacketRelay
);
S_API SNetSocket_t
SteamAPI_ISteamNetworking_CreateP2PConnectionSocket(intptr_t
instancePtr,

class CSteamID steamIDTarget,

int nVirtualPort,
int nTimeoutSec,
bool bAllowUseOfPacketRelay
);
S_API SNetSocket_t
SteamAPI_ISteamNetworking_CreateConnectionSocket(intptr_t
instancePtr,
uint32 nIP, uint16
nPort,
int nTimeoutSec
);

S_API bool SteamAPI_ISteamNetworking_DestroySocket(intptr_t instancePtr, SNetSocket_t hSocket, bool bNotifyRemoteEnd);

S_API bool
SteamAPI_ISteamNetworking_DestroyListenSocket(intptr_t instancePtr, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);

S_API bool
SteamAPI_ISteamNetworking_SendDataOnSocket(intptr_t instancePtr, SNetSocket_t hSocket, void *pubData, uint32 cubData,
                                           bool bReliable);

S_API bool
SteamAPI_ISteamNetworking_IsDataAvailableOnSocket(intptr_t instancePtr, SNetSocket_t hSocket, uint32 *pcubMsgSize);

S_API bool SteamAPI_ISteamNetworking_RetrieveDataFromSocket(intptr_t instancePtr, SNetSocket_t hSocket, void *pubDest,
                                                            uint32 cubDest, uint32 *pcubMsgSize);

S_API bool
SteamAPI_ISteamNetworking_IsDataAvailable(intptr_t instancePtr, SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize,
                                          SNetSocket_t *phSocket);

S_API bool SteamAPI_ISteamNetworking_RetrieveData(intptr_t instancePtr, SNetListenSocket_t hListenSocket, void *pubDest,
                                                  uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket);

S_API bool
SteamAPI_ISteamNetworking_GetSocketInfo(intptr_t instancePtr, SNetSocket_t hSocket, class CSteamID *pSteamIDRemote,
                                        int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote);

S_API bool
SteamAPI_ISteamNetworking_GetListenSocketInfo(intptr_t instancePtr, SNetListenSocket_t hListenSocket, uint32 *pnIP,
                                              uint16 *pnPort);

S_API ESNetSocketConnectionType
SteamAPI_ISteamNetworking_GetSocketConnectionType(intptr_t
instancePtr,
SNetSocket_t hSocket
);

S_API int SteamAPI_ISteamNetworking_GetMaxPacketSize(intptr_t instancePtr, SNetSocket_t hSocket);

S_API ScreenshotHandle
SteamAPI_ISteamScreenshots_WriteScreenshot(intptr_t
instancePtr,
void *pubRGB, uint32
cubRGB,
int nWidth,
int nHeight
);
S_API ScreenshotHandle
SteamAPI_ISteamScreenshots_AddScreenshotToLibrary(intptr_t
instancePtr,
const char *pchFilename,
const char *pchThumbnailFilename,
int nWidth,
int nHeight
);

S_API void SteamAPI_ISteamScreenshots_TriggerScreenshot(intptr_t instancePtr);

S_API void SteamAPI_ISteamScreenshots_HookScreenshots(intptr_t instancePtr, bool bHook);

S_API bool
SteamAPI_ISteamScreenshots_SetLocation(intptr_t instancePtr, ScreenshotHandle hScreenshot, const char *pchLocation);

S_API bool
SteamAPI_ISteamScreenshots_TagUser(intptr_t instancePtr, ScreenshotHandle hScreenshot, class CSteamID steamID);

S_API bool SteamAPI_ISteamScreenshots_TagPublishedFile(intptr_t instancePtr, ScreenshotHandle hScreenshot,
                                                       PublishedFileId_t unPublishedFileID);

S_API bool SteamAPI_ISteamScreenshots_IsScreenshotsHooked(intptr_t instancePtr);

S_API ScreenshotHandle
SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary(intptr_t
instancePtr,
EVRScreenshotType eType,
const char *pchFilename,
const char *pchVRFilename
);

S_API bool SteamAPI_ISteamMusic_BIsEnabled(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusic_BIsPlaying(intptr_t instancePtr);

S_API AudioPlayback_Status
SteamAPI_ISteamMusic_GetPlaybackStatus(intptr_t
instancePtr);

S_API void SteamAPI_ISteamMusic_Play(intptr_t instancePtr);

S_API void SteamAPI_ISteamMusic_Pause(intptr_t instancePtr);

S_API void SteamAPI_ISteamMusic_PlayPrevious(intptr_t instancePtr);

S_API void SteamAPI_ISteamMusic_PlayNext(intptr_t instancePtr);

S_API void SteamAPI_ISteamMusic_SetVolume(intptr_t instancePtr, float flVolume);

S_API float SteamAPI_ISteamMusic_GetVolume(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote(intptr_t instancePtr, const char *pchName);

S_API bool SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_BActivationSuccess(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_SetDisplayName(intptr_t instancePtr, const char *pchDisplayName);

S_API bool SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64(intptr_t instancePtr, void *pvBuffer, uint32 cbBufferLength);

S_API bool SteamAPI_ISteamMusicRemote_EnablePlayPrevious(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_EnablePlayNext(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_EnableShuffled(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_EnableLooped(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_EnableQueue(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_EnablePlaylists(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus(intptr_t instancePtr, AudioPlayback_Status nStatus);

S_API bool SteamAPI_ISteamMusicRemote_UpdateShuffled(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_UpdateLooped(intptr_t instancePtr, bool bValue);

S_API bool SteamAPI_ISteamMusicRemote_UpdateVolume(intptr_t instancePtr, float flValue);

S_API bool SteamAPI_ISteamMusicRemote_CurrentEntryWillChange(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable(intptr_t instancePtr, bool bAvailable);

S_API bool SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText(intptr_t instancePtr, const char *pchText);

S_API bool SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds(intptr_t instancePtr, int nValue);

S_API bool
SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt(intptr_t instancePtr, void *pvBuffer, uint32 cbBufferLength);

S_API bool SteamAPI_ISteamMusicRemote_CurrentEntryDidChange(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_QueueWillChange(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_ResetQueueEntries(intptr_t instancePtr);

S_API bool
SteamAPI_ISteamMusicRemote_SetQueueEntry(intptr_t instancePtr, int nID, int nPosition, const char *pchEntryText);

S_API bool SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry(intptr_t instancePtr, int nID);

S_API bool SteamAPI_ISteamMusicRemote_QueueDidChange(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_PlaylistWillChange(intptr_t instancePtr);

S_API bool SteamAPI_ISteamMusicRemote_ResetPlaylistEntries(intptr_t instancePtr);

S_API bool
SteamAPI_ISteamMusicRemote_SetPlaylistEntry(intptr_t instancePtr, int nID, int nPosition, const char *pchEntryText);

S_API bool SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry(intptr_t instancePtr, int nID);

S_API bool SteamAPI_ISteamMusicRemote_PlaylistDidChange(intptr_t instancePtr);

S_API HTTPRequestHandle
SteamAPI_ISteamHTTP_CreateHTTPRequest(intptr_t
instancePtr,
EHTTPMethod eHTTPRequestMethod,
const char *pchAbsoluteURL
);

S_API bool
SteamAPI_ISteamHTTP_SetHTTPRequestContextValue(intptr_t instancePtr, HTTPRequestHandle hRequest, uint64 ulContextValue);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                                    uint32 unTimeoutSeconds);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                         const char *pchHeaderName, const char *pchHeaderValue);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                                const char *pchParamName, const char *pchParamValue);

S_API bool
SteamAPI_ISteamHTTP_SendHTTPRequest(intptr_t instancePtr, HTTPRequestHandle hRequest, SteamAPICall_t *pCallHandle);

S_API bool SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                                SteamAPICall_t *pCallHandle);

S_API bool SteamAPI_ISteamHTTP_DeferHTTPRequest(intptr_t instancePtr, HTTPRequestHandle hRequest);

S_API bool SteamAPI_ISteamHTTP_PrioritizeHTTPRequest(intptr_t instancePtr, HTTPRequestHandle hRequest);

S_API bool SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                         const char *pchHeaderName, uint32 *unResponseHeaderSize);

S_API bool SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                          const char *pchHeaderName, uint8 *pHeaderValueBuffer,
                                                          uint32 unBufferSize);

S_API bool
SteamAPI_ISteamHTTP_GetHTTPResponseBodySize(intptr_t instancePtr, HTTPRequestHandle hRequest, uint32 *unBodySize);

S_API bool
SteamAPI_ISteamHTTP_GetHTTPResponseBodyData(intptr_t instancePtr, HTTPRequestHandle hRequest, uint8 *pBodyDataBuffer,
                                            uint32 unBufferSize);

S_API bool
SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData(intptr_t instancePtr, HTTPRequestHandle hRequest, uint32 cOffset,
                                                     uint8 *pBodyDataBuffer, uint32 unBufferSize);

S_API bool SteamAPI_ISteamHTTP_ReleaseHTTPRequest(intptr_t instancePtr, HTTPRequestHandle hRequest);

S_API bool
SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct(intptr_t instancePtr, HTTPRequestHandle hRequest, float *pflPercentOut);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                         const char *pchContentType, uint8 *pubBody, uint32 unBodyLen);

S_API HTTPCookieContainerHandle
SteamAPI_ISteamHTTP_CreateCookieContainer(intptr_t
instancePtr,
bool bAllowResponsesToModify
);

S_API bool SteamAPI_ISteamHTTP_ReleaseCookieContainer(intptr_t instancePtr, HTTPCookieContainerHandle hCookieContainer);

S_API bool
SteamAPI_ISteamHTTP_SetCookie(intptr_t instancePtr, HTTPCookieContainerHandle hCookieContainer, const char *pchHost,
                              const char *pchUrl, const char *pchCookie);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                             HTTPCookieContainerHandle hCookieContainer);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                           const char *pchUserAgentInfo);

S_API bool
SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                              bool bRequireVerifiedCertificate);

S_API bool SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS(intptr_t instancePtr, HTTPRequestHandle hRequest,
                                                               uint32 unMilliseconds);

S_API bool
SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut(intptr_t instancePtr, HTTPRequestHandle hRequest, bool *pbWasTimedOut);

S_API bool SteamAPI_ISteamController_Init(intptr_t instancePtr);

S_API bool SteamAPI_ISteamController_Shutdown(intptr_t instancePtr);

S_API void SteamAPI_ISteamController_RunFrame(intptr_t instancePtr);

S_API int SteamAPI_ISteamController_GetConnectedControllers(intptr_t instancePtr, ControllerHandle_t *handlesOut);

S_API bool SteamAPI_ISteamController_ShowBindingPanel(intptr_t instancePtr, ControllerHandle_t controllerHandle);

S_API ControllerActionSetHandle_t
SteamAPI_ISteamController_GetActionSetHandle(intptr_t
instancePtr,
const char *pszActionSetName
);

S_API void SteamAPI_ISteamController_ActivateActionSet(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                       ControllerActionSetHandle_t actionSetHandle);

S_API ControllerActionSetHandle_t
SteamAPI_ISteamController_GetCurrentActionSet(intptr_t
instancePtr,
ControllerHandle_t controllerHandle
);

S_API void SteamAPI_ISteamController_ActivateActionSetLayer(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                            ControllerActionSetHandle_t actionSetLayerHandle);

S_API void SteamAPI_ISteamController_DeactivateActionSetLayer(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                              ControllerActionSetHandle_t actionSetLayerHandle);

S_API void
SteamAPI_ISteamController_DeactivateAllActionSetLayers(intptr_t instancePtr, ControllerHandle_t controllerHandle);

S_API int SteamAPI_ISteamController_GetActiveActionSetLayers(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                             ControllerActionSetHandle_t *handlesOut);

S_API ControllerDigitalActionHandle_t
SteamAPI_ISteamController_GetDigitalActionHandle(intptr_t
instancePtr,
const char *pszActionName
);

S_API struct ControllerDigitalActionData_t
SteamAPI_ISteamController_GetDigitalActionData(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                               ControllerDigitalActionHandle_t digitalActionHandle);

S_API int SteamAPI_ISteamController_GetDigitalActionOrigins(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                            ControllerActionSetHandle_t actionSetHandle,
                                                            ControllerDigitalActionHandle_t digitalActionHandle,
                                                            EControllerActionOrigin *originsOut);

S_API ControllerAnalogActionHandle_t
SteamAPI_ISteamController_GetAnalogActionHandle(intptr_t
instancePtr,
const char *pszActionName
);

S_API struct ControllerAnalogActionData_t
SteamAPI_ISteamController_GetAnalogActionData(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                              ControllerAnalogActionHandle_t analogActionHandle);

S_API int SteamAPI_ISteamController_GetAnalogActionOrigins(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                           ControllerActionSetHandle_t actionSetHandle,
                                                           ControllerAnalogActionHandle_t analogActionHandle,
                                                           EControllerActionOrigin *originsOut);

S_API void SteamAPI_ISteamController_StopAnalogActionMomentum(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                              ControllerAnalogActionHandle_t eAction);

S_API void SteamAPI_ISteamController_TriggerHapticPulse(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                        ESteamControllerPad eTargetPad,
                                                        unsigned short usDurationMicroSec);

S_API void
SteamAPI_ISteamController_TriggerRepeatedHapticPulse(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                     ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec,
                                                     unsigned short usOffMicroSec, unsigned short unRepeat,
                                                     unsigned int nFlags);

S_API void SteamAPI_ISteamController_TriggerVibration(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                      unsigned short usLeftSpeed, unsigned short usRightSpeed);

S_API void
SteamAPI_ISteamController_SetLEDColor(intptr_t instancePtr, ControllerHandle_t controllerHandle, uint8 nColorR,
                                      uint8 nColorG, uint8 nColorB, unsigned int nFlags);

S_API int
SteamAPI_ISteamController_GetGamepadIndexForController(intptr_t instancePtr, ControllerHandle_t ulControllerHandle);

S_API ControllerHandle_t
SteamAPI_ISteamController_GetControllerForGamepadIndex(intptr_t
instancePtr,
int nIndex
);

S_API struct ControllerMotionData_t
SteamAPI_ISteamController_GetMotionData(intptr_t instancePtr, ControllerHandle_t controllerHandle);

S_API bool SteamAPI_ISteamController_ShowDigitalActionOrigins(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                              ControllerDigitalActionHandle_t digitalActionHandle,
                                                              float flScale, float flXPosition, float flYPosition);

S_API bool SteamAPI_ISteamController_ShowAnalogActionOrigins(intptr_t instancePtr, ControllerHandle_t controllerHandle,
                                                             ControllerAnalogActionHandle_t analogActionHandle,
                                                             float flScale, float flXPosition, float flYPosition);

S_API const char *
SteamAPI_ISteamController_GetStringForActionOrigin(intptr_t instancePtr, EControllerActionOrigin eOrigin);

S_API const char *
SteamAPI_ISteamController_GetGlyphForActionOrigin(intptr_t instancePtr, EControllerActionOrigin eOrigin);

S_API ESteamInputType
SteamAPI_ISteamController_GetInputTypeForHandle(intptr_t
instancePtr,
ControllerHandle_t controllerHandle
);
S_API UGCQueryHandle_t
SteamAPI_ISteamUGC_CreateQueryUserUGCRequest(intptr_t
instancePtr,
AccountID_t unAccountID, EUserUGCList
eListType,
EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder
eSortOrder,
AppId_t nCreatorAppID, AppId_t
nConsumerAppID,
uint32 unPage
);
S_API UGCQueryHandle_t
SteamAPI_ISteamUGC_CreateQueryAllUGCRequest(intptr_t
instancePtr,
EUGCQuery eQueryType, EUGCMatchingUGCType
eMatchingeMatchingUGCTypeFileType,
AppId_t nCreatorAppID, AppId_t
nConsumerAppID,
uint32 unPage
);
S_API UGCQueryHandle_t
SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest(intptr_t
instancePtr,
PublishedFileId_t *pvecPublishedFileID, uint32
unNumPublishedFileIDs);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_SendQueryUGCRequest(intptr_t
instancePtr,
UGCQueryHandle_t handle
);

S_API bool SteamAPI_ISteamUGC_GetQueryUGCResult(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index,
                                                struct SteamUGCDetails_t *pDetails);

S_API bool
SteamAPI_ISteamUGC_GetQueryUGCPreviewURL(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, char *pchURL,
                                         uint32 cchURLSize);

S_API bool
SteamAPI_ISteamUGC_GetQueryUGCMetadata(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, char *pchMetadata,
                                       uint32 cchMetadatasize);

S_API bool SteamAPI_ISteamUGC_GetQueryUGCChildren(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index,
                                                  PublishedFileId_t *pvecPublishedFileID, uint32 cMaxEntries);

S_API bool SteamAPI_ISteamUGC_GetQueryUGCStatistic(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index,
                                                   EItemStatistic eStatType, uint64 *pStatValue);

S_API uint32
SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews(intptr_t
instancePtr,
UGCQueryHandle_t handle, uint32
index);

S_API bool SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index,
                                                           uint32 previewIndex, char *pchURLOrVideoID,
                                                           uint32 cchURLSize, char *pchOriginalFileName,
                                                           uint32 cchOriginalFileNameSize,
                                                           EItemPreviewType *pPreviewType);

S_API uint32
SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags(intptr_t
instancePtr,
UGCQueryHandle_t handle, uint32
index);

S_API bool SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index,
                                                     uint32 keyValueTagIndex, char *pchKey, uint32 cchKeySize,
                                                     char *pchValue, uint32 cchValueSize);

S_API bool SteamAPI_ISteamUGC_ReleaseQueryUGCRequest(intptr_t instancePtr, UGCQueryHandle_t handle);

S_API bool SteamAPI_ISteamUGC_AddRequiredTag(intptr_t instancePtr, UGCQueryHandle_t handle, const char *pTagName);

S_API bool SteamAPI_ISteamUGC_AddExcludedTag(intptr_t instancePtr, UGCQueryHandle_t handle, const char *pTagName);

S_API bool SteamAPI_ISteamUGC_SetReturnOnlyIDs(intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnOnlyIDs);

S_API bool
SteamAPI_ISteamUGC_SetReturnKeyValueTags(intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnKeyValueTags);

S_API bool
SteamAPI_ISteamUGC_SetReturnLongDescription(intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnLongDescription);

S_API bool SteamAPI_ISteamUGC_SetReturnMetadata(intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnMetadata);

S_API bool SteamAPI_ISteamUGC_SetReturnChildren(intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnChildren);

S_API bool SteamAPI_ISteamUGC_SetReturnAdditionalPreviews(intptr_t instancePtr, UGCQueryHandle_t handle,
                                                          bool bReturnAdditionalPreviews);

S_API bool SteamAPI_ISteamUGC_SetReturnTotalOnly(intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnTotalOnly);

S_API bool SteamAPI_ISteamUGC_SetReturnPlaytimeStats(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 unDays);

S_API bool SteamAPI_ISteamUGC_SetLanguage(intptr_t instancePtr, UGCQueryHandle_t handle, const char *pchLanguage);

S_API bool
SteamAPI_ISteamUGC_SetAllowCachedResponse(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);

S_API bool SteamAPI_ISteamUGC_SetCloudFileNameFilter(intptr_t instancePtr, UGCQueryHandle_t handle,
                                                     const char *pMatchCloudFileName);

S_API bool SteamAPI_ISteamUGC_SetMatchAnyTag(intptr_t instancePtr, UGCQueryHandle_t handle, bool bMatchAnyTag);

S_API bool SteamAPI_ISteamUGC_SetSearchText(intptr_t instancePtr, UGCQueryHandle_t handle, const char *pSearchText);

S_API bool SteamAPI_ISteamUGC_SetRankedByTrendDays(intptr_t instancePtr, UGCQueryHandle_t handle, uint32 unDays);

S_API bool SteamAPI_ISteamUGC_AddRequiredKeyValueTag(intptr_t instancePtr, UGCQueryHandle_t handle, const char *pKey,
                                                     const char *pValue);

S_API SteamAPICall_t
SteamAPI_ISteamUGC_RequestUGCDetails(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID, uint32
unMaxAgeSeconds);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_CreateItem(intptr_t
instancePtr,
AppId_t nConsumerAppId, EWorkshopFileType
eFileType);
S_API UGCUpdateHandle_t
SteamAPI_ISteamUGC_StartItemUpdate(intptr_t
instancePtr,
AppId_t nConsumerAppId, PublishedFileId_t
nPublishedFileID);

S_API bool SteamAPI_ISteamUGC_SetItemTitle(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pchTitle);

S_API bool
SteamAPI_ISteamUGC_SetItemDescription(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pchDescription);

S_API bool
SteamAPI_ISteamUGC_SetItemUpdateLanguage(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pchLanguage);

S_API bool SteamAPI_ISteamUGC_SetItemMetadata(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pchMetaData);

S_API bool SteamAPI_ISteamUGC_SetItemVisibility(intptr_t instancePtr, UGCUpdateHandle_t handle,
                                                ERemoteStoragePublishedFileVisibility eVisibility);

S_API bool SteamAPI_ISteamUGC_SetItemTags(intptr_t instancePtr, UGCUpdateHandle_t updateHandle,
                                          const struct SteamParamStringArray_t *pTags);

S_API bool
SteamAPI_ISteamUGC_SetItemContent(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pszContentFolder);

S_API bool
SteamAPI_ISteamUGC_SetItemPreview(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pszPreviewFile);

S_API bool
SteamAPI_ISteamUGC_RemoveItemKeyValueTags(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pchKey);

S_API bool SteamAPI_ISteamUGC_AddItemKeyValueTag(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pchKey,
                                                 const char *pchValue);

S_API bool
SteamAPI_ISteamUGC_AddItemPreviewFile(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pszPreviewFile,
                                      EItemPreviewType type);

S_API bool
SteamAPI_ISteamUGC_AddItemPreviewVideo(intptr_t instancePtr, UGCUpdateHandle_t handle, const char *pszVideoID);

S_API bool SteamAPI_ISteamUGC_UpdateItemPreviewFile(intptr_t instancePtr, UGCUpdateHandle_t handle, uint32 index,
                                                    const char *pszPreviewFile);

S_API bool SteamAPI_ISteamUGC_UpdateItemPreviewVideo(intptr_t instancePtr, UGCUpdateHandle_t handle, uint32 index,
                                                     const char *pszVideoID);

S_API bool SteamAPI_ISteamUGC_RemoveItemPreview(intptr_t instancePtr, UGCUpdateHandle_t handle, uint32 index);

S_API SteamAPICall_t
SteamAPI_ISteamUGC_SubmitItemUpdate(intptr_t
instancePtr,
UGCUpdateHandle_t handle,
const char *pchChangeNote
);
S_API EItemUpdateStatus
SteamAPI_ISteamUGC_GetItemUpdateProgress(intptr_t
instancePtr,
UGCUpdateHandle_t handle, uint64
* punBytesProcessed,
uint64 *punBytesTotal
);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_SetUserItemVote(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID,
bool bVoteUp
);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_GetUserItemVote(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID
);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_AddItemToFavorites(intptr_t
instancePtr,
AppId_t nAppId, PublishedFileId_t
nPublishedFileID);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_RemoveItemFromFavorites(intptr_t
instancePtr,
AppId_t nAppId, PublishedFileId_t
nPublishedFileID);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_SubscribeItem(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID
);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_UnsubscribeItem(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID
);
S_API uint32
SteamAPI_ISteamUGC_GetNumSubscribedItems(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamUGC_GetSubscribedItems(intptr_t
instancePtr,
PublishedFileId_t *pvecPublishedFileID, uint32
cMaxEntries);
S_API uint32
SteamAPI_ISteamUGC_GetItemState(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID
);

S_API bool
SteamAPI_ISteamUGC_GetItemInstallInfo(intptr_t instancePtr, PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk,
                                      char *pchFolder, uint32 cchFolderSize, uint32 *punTimeStamp);

S_API bool SteamAPI_ISteamUGC_GetItemDownloadInfo(intptr_t instancePtr, PublishedFileId_t nPublishedFileID,
                                                  uint64 *punBytesDownloaded, uint64 *punBytesTotal);

S_API bool
SteamAPI_ISteamUGC_DownloadItem(intptr_t instancePtr, PublishedFileId_t nPublishedFileID, bool bHighPriority);

S_API bool
SteamAPI_ISteamUGC_BInitWorkshopForGameServer(intptr_t instancePtr, DepotId_t unWorkshopDepotID, const char *pszFolder);

S_API void SteamAPI_ISteamUGC_SuspendDownloads(intptr_t instancePtr, bool bSuspend);

S_API SteamAPICall_t
SteamAPI_ISteamUGC_StartPlaytimeTracking(intptr_t
instancePtr,
PublishedFileId_t *pvecPublishedFileID, uint32
unNumPublishedFileIDs);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_StopPlaytimeTracking(intptr_t
instancePtr,
PublishedFileId_t *pvecPublishedFileID, uint32
unNumPublishedFileIDs);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems(intptr_t
instancePtr);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_AddDependency(intptr_t
instancePtr,
PublishedFileId_t nParentPublishedFileID, PublishedFileId_t
nChildPublishedFileID);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_RemoveDependency(intptr_t
instancePtr,
PublishedFileId_t nParentPublishedFileID, PublishedFileId_t
nChildPublishedFileID);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_AddAppDependency(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID, AppId_t
nAppID);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_RemoveAppDependency(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID, AppId_t
nAppID);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_GetAppDependencies(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID
);
S_API SteamAPICall_t
SteamAPI_ISteamUGC_DeleteItem(intptr_t
instancePtr,
PublishedFileId_t nPublishedFileID
);
S_API uint32
SteamAPI_ISteamAppList_GetNumInstalledApps(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamAppList_GetInstalledApps(intptr_t
instancePtr,
AppId_t *pvecAppID, uint32
unMaxAppIDs);

S_API int SteamAPI_ISteamAppList_GetAppName(intptr_t instancePtr, AppId_t nAppID, char *pchName, int cchNameMax);

S_API int
SteamAPI_ISteamAppList_GetAppInstallDir(intptr_t instancePtr, AppId_t nAppID, char *pchDirectory, int cchNameMax);

S_API int SteamAPI_ISteamAppList_GetAppBuildId(intptr_t instancePtr, AppId_t nAppID);

S_API void SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface(intptr_t instancePtr);

S_API bool SteamAPI_ISteamHTMLSurface_Init(intptr_t instancePtr);

S_API bool SteamAPI_ISteamHTMLSurface_Shutdown(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamHTMLSurface_CreateBrowser(intptr_t
instancePtr,
const char *pchUserAgent,
const char *pchUserCSS
);

S_API void SteamAPI_ISteamHTMLSurface_RemoveBrowser(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_LoadURL(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char *pchURL,
                                              const char *pchPostData);

S_API void
SteamAPI_ISteamHTMLSurface_SetSize(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight);

S_API void SteamAPI_ISteamHTMLSurface_StopLoad(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_Reload(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_GoBack(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_GoForward(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_AddHeader(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char *pchKey,
                                                const char *pchValue);

S_API void
SteamAPI_ISteamHTMLSurface_ExecuteJavascript(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char *pchScript);

S_API void SteamAPI_ISteamHTMLSurface_MouseUp(intptr_t instancePtr, HHTMLBrowser unBrowserHandle,
                                              ISteamHTMLSurface::EHTMLMouseButton eMouseButton);

S_API void SteamAPI_ISteamHTMLSurface_MouseDown(intptr_t instancePtr, HHTMLBrowser unBrowserHandle,
                                                ISteamHTMLSurface::EHTMLMouseButton eMouseButton);

S_API void SteamAPI_ISteamHTMLSurface_MouseDoubleClick(intptr_t instancePtr, HHTMLBrowser unBrowserHandle,
                                                       ISteamHTMLSurface::EHTMLMouseButton eMouseButton);

S_API void SteamAPI_ISteamHTMLSurface_MouseMove(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, int x, int y);

S_API void SteamAPI_ISteamHTMLSurface_MouseWheel(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, int32 nDelta);

S_API void SteamAPI_ISteamHTMLSurface_KeyDown(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode,
                                              ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers);

S_API void SteamAPI_ISteamHTMLSurface_KeyUp(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode,
                                            ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers);

S_API void SteamAPI_ISteamHTMLSurface_KeyChar(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar,
                                              ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers);

S_API void SteamAPI_ISteamHTMLSurface_SetHorizontalScroll(intptr_t instancePtr, HHTMLBrowser unBrowserHandle,
                                                          uint32 nAbsolutePixelScroll);

S_API void SteamAPI_ISteamHTMLSurface_SetVerticalScroll(intptr_t instancePtr, HHTMLBrowser unBrowserHandle,
                                                        uint32 nAbsolutePixelScroll);

S_API void
SteamAPI_ISteamHTMLSurface_SetKeyFocus(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus);

S_API void SteamAPI_ISteamHTMLSurface_ViewSource(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_CopyToClipboard(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_PasteFromClipboard(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void SteamAPI_ISteamHTMLSurface_Find(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char *pchSearchStr,
                                           bool bCurrentlyInFind, bool bReverse);

S_API void SteamAPI_ISteamHTMLSurface_StopFind(intptr_t instancePtr, HHTMLBrowser unBrowserHandle);

S_API void
SteamAPI_ISteamHTMLSurface_GetLinkAtPosition(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, int x, int y);

S_API void SteamAPI_ISteamHTMLSurface_SetCookie(intptr_t instancePtr, const char *pchHostname, const char *pchKey,
                                                const char *pchValue, const char *pchPath, RTime32 nExpires,
                                                bool bSecure, bool bHTTPOnly);

S_API void
SteamAPI_ISteamHTMLSurface_SetPageScaleFactor(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, float flZoom,
                                              int nPointX, int nPointY);

S_API void
SteamAPI_ISteamHTMLSurface_SetBackgroundMode(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bBackgroundMode);

S_API void
SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, float flDPIScaling);

S_API void
SteamAPI_ISteamHTMLSurface_AllowStartRequest(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bAllowed);

S_API void
SteamAPI_ISteamHTMLSurface_JSDialogResponse(intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bResult);

S_API EResult
SteamAPI_ISteamInventory_GetResultStatus(intptr_t
instancePtr,
SteamInventoryResult_t resultHandle
);

S_API bool SteamAPI_ISteamInventory_GetResultItems(intptr_t instancePtr, SteamInventoryResult_t resultHandle,
                                                   struct SteamItemDetails_t *pOutItemsArray,
                                                   uint32 *punOutItemsArraySize);

S_API bool SteamAPI_ISteamInventory_GetResultItemProperty(intptr_t instancePtr, SteamInventoryResult_t resultHandle,
                                                          uint32 unItemIndex, const char *pchPropertyName,
                                                          char *pchValueBuffer, uint32 *punValueBufferSizeOut);

S_API uint32
SteamAPI_ISteamInventory_GetResultTimestamp(intptr_t
instancePtr,
SteamInventoryResult_t resultHandle
);

S_API bool SteamAPI_ISteamInventory_CheckResultSteamID(intptr_t instancePtr, SteamInventoryResult_t resultHandle,
                                                       class CSteamID steamIDExpected);

S_API void SteamAPI_ISteamInventory_DestroyResult(intptr_t instancePtr, SteamInventoryResult_t resultHandle);

S_API bool SteamAPI_ISteamInventory_GetAllItems(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle);

S_API bool SteamAPI_ISteamInventory_GetItemsByID(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                 const SteamItemInstanceID_t *pInstanceIDs, uint32 unCountInstanceIDs);

S_API bool
SteamAPI_ISteamInventory_SerializeResult(intptr_t instancePtr, SteamInventoryResult_t resultHandle, void *pOutBuffer,
                                         uint32 *punOutBufferSize);

S_API bool SteamAPI_ISteamInventory_DeserializeResult(intptr_t instancePtr, SteamInventoryResult_t *pOutResultHandle,
                                                      const void *pBuffer, uint32 unBufferSize,
                                                      bool bRESERVED_MUST_BE_FALSE);

S_API bool SteamAPI_ISteamInventory_GenerateItems(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                  const SteamItemDef_t *pArrayItemDefs, const uint32 *punArrayQuantity,
                                                  uint32 unArrayLength);

S_API bool SteamAPI_ISteamInventory_GrantPromoItems(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle);

S_API bool SteamAPI_ISteamInventory_AddPromoItem(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                 SteamItemDef_t itemDef);

S_API bool SteamAPI_ISteamInventory_AddPromoItems(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                  const SteamItemDef_t *pArrayItemDefs, uint32 unArrayLength);

S_API bool SteamAPI_ISteamInventory_ConsumeItem(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                SteamItemInstanceID_t itemConsume, uint32 unQuantity);

S_API bool SteamAPI_ISteamInventory_ExchangeItems(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                  const SteamItemDef_t *pArrayGenerate,
                                                  const uint32 *punArrayGenerateQuantity, uint32 unArrayGenerateLength,
                                                  const SteamItemInstanceID_t *pArrayDestroy,
                                                  const uint32 *punArrayDestroyQuantity, uint32 unArrayDestroyLength);

S_API bool SteamAPI_ISteamInventory_TransferItemQuantity(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                         SteamItemInstanceID_t itemIdSource, uint32 unQuantity,
                                                         SteamItemInstanceID_t itemIdDest);

S_API void SteamAPI_ISteamInventory_SendItemDropHeartbeat(intptr_t instancePtr);

S_API bool SteamAPI_ISteamInventory_TriggerItemDrop(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                                    SteamItemDef_t dropListDefinition);

S_API bool SteamAPI_ISteamInventory_TradeItems(intptr_t instancePtr, SteamInventoryResult_t *pResultHandle,
                                               class CSteamID steamIDTradePartner,
                                               const SteamItemInstanceID_t *pArrayGive,
                                               const uint32 *pArrayGiveQuantity, uint32 nArrayGiveLength,
                                               const SteamItemInstanceID_t *pArrayGet, const uint32 *pArrayGetQuantity,
                                               uint32 nArrayGetLength);

S_API bool SteamAPI_ISteamInventory_LoadItemDefinitions(intptr_t instancePtr);

S_API bool SteamAPI_ISteamInventory_GetItemDefinitionIDs(intptr_t instancePtr, SteamItemDef_t *pItemDefIDs,
                                                         uint32 *punItemDefIDsArraySize);

S_API bool SteamAPI_ISteamInventory_GetItemDefinitionProperty(intptr_t instancePtr, SteamItemDef_t iDefinition,
                                                              const char *pchPropertyName, char *pchValueBuffer,
                                                              uint32 *punValueBufferSizeOut);

S_API SteamAPICall_t
SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs(intptr_t
instancePtr,

class CSteamID steamID

);

S_API bool SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs(intptr_t instancePtr, class CSteamID steamID,
                                                                      SteamItemDef_t *pItemDefIDs,
                                                                      uint32 *punItemDefIDsArraySize);

S_API SteamAPICall_t
SteamAPI_ISteamInventory_StartPurchase(intptr_t
instancePtr,
const SteamItemDef_t *pArrayItemDefs,
const uint32 *punArrayQuantity, uint32
unArrayLength);
S_API SteamAPICall_t
SteamAPI_ISteamInventory_RequestPrices(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamInventory_GetNumItemsWithPrices(intptr_t
instancePtr);

S_API bool
SteamAPI_ISteamInventory_GetItemsWithPrices(intptr_t instancePtr, SteamItemDef_t *pArrayItemDefs, uint64 *pPrices,
                                            uint32 unArrayLength);

S_API bool SteamAPI_ISteamInventory_GetItemPrice(intptr_t instancePtr, SteamItemDef_t iDefinition, uint64 *pPrice);

S_API SteamInventoryUpdateHandle_t
SteamAPI_ISteamInventory_StartUpdateProperties(intptr_t
instancePtr);

S_API bool SteamAPI_ISteamInventory_RemoveProperty(intptr_t instancePtr, SteamInventoryUpdateHandle_t handle,
                                                   SteamItemInstanceID_t nItemID, const char *pchPropertyName);

S_API bool SteamAPI_ISteamInventory_SetProperty(intptr_t instancePtr, SteamInventoryUpdateHandle_t handle,
                                                SteamItemInstanceID_t nItemID, const char *pchPropertyName,
                                                const char *pchPropertyValue);

S_API bool SteamAPI_ISteamInventory_SetProperty0(intptr_t instancePtr, SteamInventoryUpdateHandle_t handle,
                                                 SteamItemInstanceID_t nItemID, const char *pchPropertyName,
                                                 bool bValue);

S_API bool SteamAPI_ISteamInventory_SetProperty1(intptr_t instancePtr, SteamInventoryUpdateHandle_t handle,
                                                 SteamItemInstanceID_t nItemID, const char *pchPropertyName,
                                                 int64 nValue);

S_API bool SteamAPI_ISteamInventory_SetProperty2(intptr_t instancePtr, SteamInventoryUpdateHandle_t handle,
                                                 SteamItemInstanceID_t nItemID, const char *pchPropertyName,
                                                 float flValue);

S_API bool SteamAPI_ISteamInventory_SubmitUpdateProperties(intptr_t instancePtr, SteamInventoryUpdateHandle_t handle,
                                                           SteamInventoryResult_t *pResultHandle);

S_API void SteamAPI_ISteamVideo_GetVideoURL(intptr_t instancePtr, AppId_t unVideoAppID);

S_API bool SteamAPI_ISteamVideo_IsBroadcasting(intptr_t instancePtr, int *pnNumViewers);

S_API void SteamAPI_ISteamVideo_GetOPFSettings(intptr_t instancePtr, AppId_t unVideoAppID);

S_API bool SteamAPI_ISteamVideo_GetOPFStringForApp(intptr_t instancePtr, AppId_t unVideoAppID, char *pchBuffer,
                                                   int32 *pnBufferSize);

S_API bool SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled(intptr_t instancePtr);

S_API bool SteamAPI_ISteamParentalSettings_BIsParentalLockLocked(intptr_t instancePtr);

S_API bool SteamAPI_ISteamParentalSettings_BIsAppBlocked(intptr_t instancePtr, AppId_t nAppID);

S_API bool SteamAPI_ISteamParentalSettings_BIsAppInBlockList(intptr_t instancePtr, AppId_t nAppID);

S_API bool SteamAPI_ISteamParentalSettings_BIsFeatureBlocked(intptr_t instancePtr, EParentalFeature eFeature);

S_API bool SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList(intptr_t instancePtr, EParentalFeature eFeature);

S_API bool
SteamAPI_ISteamGameServer_InitGameServer(intptr_t instancePtr, uint32 unIP, uint16 usGamePort, uint16 usQueryPort,
                                         uint32 unFlags, AppId_t nGameAppId, const char *pchVersionString);

S_API void SteamAPI_ISteamGameServer_SetProduct(intptr_t instancePtr, const char *pszProduct);

S_API void SteamAPI_ISteamGameServer_SetGameDescription(intptr_t instancePtr, const char *pszGameDescription);

S_API void SteamAPI_ISteamGameServer_SetModDir(intptr_t instancePtr, const char *pszModDir);

S_API void SteamAPI_ISteamGameServer_SetDedicatedServer(intptr_t instancePtr, bool bDedicated);

S_API void SteamAPI_ISteamGameServer_LogOn(intptr_t instancePtr, const char *pszToken);

S_API void SteamAPI_ISteamGameServer_LogOnAnonymous(intptr_t instancePtr);

S_API void SteamAPI_ISteamGameServer_LogOff(intptr_t instancePtr);

S_API bool SteamAPI_ISteamGameServer_BLoggedOn(intptr_t instancePtr);

S_API bool SteamAPI_ISteamGameServer_BSecure(intptr_t instancePtr);

S_API uint64
SteamAPI_ISteamGameServer_GetSteamID(intptr_t
instancePtr);

S_API bool SteamAPI_ISteamGameServer_WasRestartRequested(intptr_t instancePtr);

S_API void SteamAPI_ISteamGameServer_SetMaxPlayerCount(intptr_t instancePtr, int cPlayersMax);

S_API void SteamAPI_ISteamGameServer_SetBotPlayerCount(intptr_t instancePtr, int cBotplayers);

S_API void SteamAPI_ISteamGameServer_SetServerName(intptr_t instancePtr, const char *pszServerName);

S_API void SteamAPI_ISteamGameServer_SetMapName(intptr_t instancePtr, const char *pszMapName);

S_API void SteamAPI_ISteamGameServer_SetPasswordProtected(intptr_t instancePtr, bool bPasswordProtected);

S_API void SteamAPI_ISteamGameServer_SetSpectatorPort(intptr_t instancePtr, uint16 unSpectatorPort);

S_API void SteamAPI_ISteamGameServer_SetSpectatorServerName(intptr_t instancePtr, const char *pszSpectatorServerName);

S_API void SteamAPI_ISteamGameServer_ClearAllKeyValues(intptr_t instancePtr);

S_API void SteamAPI_ISteamGameServer_SetKeyValue(intptr_t instancePtr, const char *pKey, const char *pValue);

S_API void SteamAPI_ISteamGameServer_SetGameTags(intptr_t instancePtr, const char *pchGameTags);

S_API void SteamAPI_ISteamGameServer_SetGameData(intptr_t instancePtr, const char *pchGameData);

S_API void SteamAPI_ISteamGameServer_SetRegion(intptr_t instancePtr, const char *pszRegion);

S_API bool SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate(intptr_t instancePtr, uint32 unIPClient,
                                                                    const void *pvAuthBlob, uint32 cubAuthBlobSize,
                                                                    class CSteamID *pSteamIDUser);

S_API uint64
SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection(intptr_t
instancePtr);

S_API void SteamAPI_ISteamGameServer_SendUserDisconnect(intptr_t instancePtr, class CSteamID steamIDUser);

S_API bool
SteamAPI_ISteamGameServer_BUpdateUserData(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchPlayerName,
                                          uint32 uScore);

S_API HAuthTicket
SteamAPI_ISteamGameServer_GetAuthSessionTicket(intptr_t
instancePtr,
void *pTicket,
int cbMaxTicket, uint32
* pcbTicket);
S_API EBeginAuthSessionResult
SteamAPI_ISteamGameServer_BeginAuthSession(intptr_t
instancePtr,
const void *pAuthTicket,
int cbAuthTicket,

class CSteamID steamID

);

S_API void SteamAPI_ISteamGameServer_EndAuthSession(intptr_t instancePtr, class CSteamID steamID);

S_API void SteamAPI_ISteamGameServer_CancelAuthTicket(intptr_t instancePtr, HAuthTicket hAuthTicket);

S_API EUserHasLicenseForAppResult
SteamAPI_ISteamGameServer_UserHasLicenseForApp(intptr_t
instancePtr,

class CSteamID steamID, AppId_t

appID);

S_API bool SteamAPI_ISteamGameServer_RequestUserGroupStatus(intptr_t instancePtr, class CSteamID steamIDUser,
                                                            class CSteamID steamIDGroup);

S_API void SteamAPI_ISteamGameServer_GetGameplayStats(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamGameServer_GetServerReputation(intptr_t
instancePtr);
S_API uint32
SteamAPI_ISteamGameServer_GetPublicIP(intptr_t
instancePtr);

S_API bool
SteamAPI_ISteamGameServer_HandleIncomingPacket(intptr_t instancePtr, const void *pData, int cbData, uint32 srcIP,
                                               uint16 srcPort);

S_API int
SteamAPI_ISteamGameServer_GetNextOutgoingPacket(intptr_t instancePtr, void *pOut, int cbMaxOut, uint32 *pNetAdr,
                                                uint16 *pPort);

S_API void SteamAPI_ISteamGameServer_EnableHeartbeats(intptr_t instancePtr, bool bActive);

S_API void SteamAPI_ISteamGameServer_SetHeartbeatInterval(intptr_t instancePtr, int iHeartbeatInterval);

S_API void SteamAPI_ISteamGameServer_ForceHeartbeat(intptr_t instancePtr);

S_API SteamAPICall_t
SteamAPI_ISteamGameServer_AssociateWithClan(intptr_t
instancePtr,

class CSteamID steamIDClan

);
S_API SteamAPICall_t
SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility(intptr_t
instancePtr,

class CSteamID steamIDNewPlayer

);
S_API SteamAPICall_t
SteamAPI_ISteamGameServerStats_RequestUserStats(intptr_t
instancePtr,

class CSteamID steamIDUser

);

S_API bool
SteamAPI_ISteamGameServerStats_GetUserStat(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                           int32 *pData);

S_API bool
SteamAPI_ISteamGameServerStats_GetUserStat0(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                            float *pData);

S_API bool
SteamAPI_ISteamGameServerStats_GetUserAchievement(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                                  bool *pbAchieved);

S_API bool
SteamAPI_ISteamGameServerStats_SetUserStat(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                           int32 nData);

S_API bool
SteamAPI_ISteamGameServerStats_SetUserStat0(intptr_t instancePtr, class CSteamID steamIDUser, const char *pchName,
                                            float fData);

S_API bool SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat(intptr_t instancePtr, class CSteamID steamIDUser,
                                                                const char *pchName, float flCountThisSession,
                                                                double dSessionLength);

S_API bool SteamAPI_ISteamGameServerStats_SetUserAchievement(intptr_t instancePtr, class CSteamID steamIDUser,
                                                             const char *pchName);

S_API bool SteamAPI_ISteamGameServerStats_ClearUserAchievement(intptr_t instancePtr, class CSteamID steamIDUser,
                                                               const char *pchName);

S_API SteamAPICall_t
SteamAPI_ISteamGameServerStats_StoreUserStats(intptr_t
instancePtr,

class CSteamID steamIDUser

);
#endif // STEAMAPIFLAT_H


