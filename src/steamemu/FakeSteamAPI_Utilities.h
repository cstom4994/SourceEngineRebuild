#pragma once

#include <Windows.h>

extern void (__stdcall *g_RtlGetCallersAddress)(void **CallersAddress, void **CallersCaller);

void FakeSteamAPI_Utilities_Init(void);

void *FakeSteamAPI_GetImageBase(void);

__forceinline bool FakeSteamAPI_GetEIP(void *&ptr) {
    void *p1, *p2;
    g_RtlGetCallersAddress(&p1, &p2);
    ptr = p2;
    return true;
}

__forceinline void *FakeSteamAPI_GetEIP(void) {
    void *p1, *p2;
    g_RtlGetCallersAddress(&p1, &p2);
    return p2;
}

__forceinline void *FakeSteamAPI_GetEIP0(void) {
    void *p1, *p2;
    g_RtlGetCallersAddress(&p1, &p2);
    return p1;
}

__forceinline void *FakeSteamAPI_GetEIP1(void) {
    void *p1, *p2;
    g_RtlGetCallersAddress(&p1, &p2);
    return p2;
}