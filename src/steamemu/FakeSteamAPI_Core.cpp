#define _CRT_SECURE_NO_WARNINGS
#define STEAM_API_EXPORTS
#define WIN32_LEAN_AND_MEAN

#include "FakeSteamAPI_ContextProvider.h"
#include "FakeSteamAPI_Utilities.h"
#include "FakeSteamAPI_Settings.h"
#include "FakeSteamAPI_LogSys.h"

#include "steam_api.h"
#include <Windows.h>


void FakeSteamAPI_DoInitialization(void) {
    FakeSteamAPI_Settings_Init();
    FakeSteamAPI_Utilities_Init();
}

//steam_api.h
bool SteamAPI_Init() {
    bool bClickedOk;

    FakeSteamAPI_DoInitialization();

    //FakeSteamAPI_NullPlaceholderRef();

    FakeSteamAPI_EmptyLog();

    //FakeSteamAPI_NewLogLine();

    FakeSteamAPI_AllocLogWindow();

    FakeSteamAPI_AppendLog(LogLevel_Info, "FakeSteamAPI has been started.");

    FakeSteamAPI_LogFuncBeingCalled();

    if (IsDebuggerPresent())
        FakeSteamAPI_AppendLog(LogLevel_Info,
                               "Debugger detected. You can jump to desired addresses with logged EIPs inside debugger.");
    else
        FakeSteamAPI_AppendLog(LogLevel_Info,
                               "Debugger not detected. You can still attach debugger and jump to logged EIPs later.");

    bClickedOk = true;

    /*
    bClickedOk = MessageBoxA(
        NULL,
        "SteamAPI_Init() is being called.\nPress \"Yes\" to return true, \"No\" to return false.",
        placeholder,
        MB_YESNO | MB_ICONINFORMATION
    ) == IDYES;
    */

    FakeSteamAPI_AppendLog(LogLevel_Info, "%s() will pass %s to the application.", __FUNCTION__,
                           bClickedOk ? "true" : "false");

    return bClickedOk;
}

void SteamAPI_Shutdown() {
    FakeSteamAPI_LogFuncBeingCalled();
    FakeSteamAPI_FreeLogWindow();
    return;
}

bool SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID) {
    FakeSteamAPI_LogFuncBeingCalled();
    FakeSteamAPI_AppendLog(LogLevel_Info, "%s() will pass false to the application.", __FUNCTION__);
    return false;
}

void SteamAPI_ReleaseCurrentThreadMemory() {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamAPI_UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime,
                                      bool bFullMemoryDumps, void *pvContext,
                                      PFNPreMinidumpCallback m_pfnPreMinidumpCallback) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

HSteamPipe SteamGameServer_GetHSteamPipe() { return 0; }

HSteamUser SteamGameServer_GetHSteamUser() { return 0; }

void SteamAPI_SetBreakpadAppID(uint32 unAppID) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamGameServer_RunCallbacks() {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

bool SteamGameServer_BSecure() {
    FakeSteamAPI_LogFuncBeingCalled();
    return true;
}

bool SteamAPI_InitSafe() {
    FakeSteamAPI_LogFuncBeingCalled();
    return true;
}

void SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void *pvExceptionInfo, uint32 uBuildID) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamAPI_SetMiniDumpComment(const char *pchMsg) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamAPI_RunCallbacks() {
    static bool bFirst = true;
    MSG msg;

    if (bFirst) {
        bFirst = false;
        FakeSteamAPI_LogFuncBeingCalled();
        FakeSteamAPI_AppendLog(LogLevel_Info, "Calls to %s() will only be shown once.", __FUNCTION__);
    }

    if (FakeSteamAPI_GetSettingsItemInt32(FakeSteamAPI_SettingsIndex_ProcessMessageInRunCallbacks) != 0) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            //TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return;
}

void SteamAPI_RegisterCallback(class CCallbackBase *pCallback, int iCallback) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamAPI_UnregisterCallback(class CCallbackBase *pCallback) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamAPI_RegisterCallResult(class CCallbackBase *pCallback, SteamAPICall_t hAPICall) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void SteamAPI_UnregisterCallResult(class CCallbackBase *pCallback, SteamAPICall_t hAPICall) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

bool SteamAPI_IsSteamRunning() {
    FakeSteamAPI_LogFuncBeingCalled();
    FakeSteamAPI_AppendLog(LogLevel_Info, "%s() will pass false to the application.", __FUNCTION__);
    return false;
}

void Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

void Steam_RegisterInterfaceFuncs(void *hModule) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

HSteamUser Steam_GetHSteamUserCurrent() {
    FakeSteamAPI_LogFuncBeingCalled();
    return NULL;
}

const char *SteamAPI_GetSteamInstallPath() {
    FakeSteamAPI_LogFuncBeingCalled();
    return NULL;
}

HSteamPipe SteamAPI_GetHSteamPipe() {
    FakeSteamAPI_LogFuncBeingCalled();
    return NULL;
}

void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks) {
    FakeSteamAPI_LogFuncBeingCalled();
    return;
}

HSteamPipe GetHSteamPipe() {
    FakeSteamAPI_LogFuncBeingCalled();
    return NULL;
}

HSteamUser GetHSteamUser() {
    FakeSteamAPI_LogFuncBeingCalled();
    return NULL;
}

//steam_api_internal.h
HSteamUser SteamAPI_GetHSteamUser() {
    FakeSteamAPI_LogFuncBeingCalled();
    FakeSteamAPI_AppendLog(LogLevel_Info, "%s() will pass NULL to the application.", __FUNCTION__);
    return NULL;
}

void *SteamInternal_ContextInit(void *pContextInitData) {
    static bool bFirst = true;
    if (bFirst) {
        bFirst = false;
        FakeSteamAPI_LogFuncBeingCalled();
        FakeSteamAPI_AppendLog(LogLevel_Info, "Calls to %s() will only be shown once.", __FUNCTION__);
    }
    //FakeSteamAPI_AppendLog(LogLevel_Info, "%s() will pass NULL to the application.", __FUNCTION__);
    return &FakeSteamAPI_GetContextInstance();
}

void *SteamInternal_CreateInterface(const char *ver) {
    FakeSteamAPI_LogFuncBeingCalled();
    FakeSteamAPI_AppendLog(LogLevel_Info, "%s() will pass NULL to the application.", __FUNCTION__);
    return NULL;
}