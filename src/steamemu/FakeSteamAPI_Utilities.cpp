#include "FakeSteamAPI_Utilities.h"
#include "FakeSteamAPI_LogSys.h"

typedef struct _PEB PEB, *PPEB;

void (__stdcall *g_RtlGetCallersAddress)(void **CallersAddress, void **CallersCaller);

void __stdcall RtlGetCallersAddress_Stub(void **CallersAddress, void **CallersCaller) {
    if (CallersAddress)
        *CallersAddress = nullptr;
    if (CallersCaller)
        *CallersCaller = nullptr;
}

void FakeSteamAPI_Utilities_Init(void) {
    g_RtlGetCallersAddress = (decltype(g_RtlGetCallersAddress)) GetProcAddress(GetModuleHandleA("ntdll.dll"),
                                                                               "RtlGetCallersAddress");
    if (g_RtlGetCallersAddress == nullptr)
        g_RtlGetCallersAddress = RtlGetCallersAddress_Stub;
}

PPEB NtCurrentPeb(void) {
    //32-bit Windows only
    return (PPEB) *((DWORD_PTR *) NtCurrentTeb() + 12);    //Hardcoded offset
}

void *NtGetImageStartAddress(void) {
    //32-bit Windows only
    return (void *) *((DWORD_PTR *) NtCurrentPeb() + 2);    //Hardcoded offset
}

void *FakeSteamAPI_GetImageBase(void) {
    return NtGetImageStartAddress();
}