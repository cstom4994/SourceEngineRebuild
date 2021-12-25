//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//=============================================================================//
typedef enum {
    eUninitialized,
    eUnknown,
    eWin9x,
    eWinNT,
} eOSVersion;

extern void initOSVersion();

extern eOSVersion getOSVersion();
