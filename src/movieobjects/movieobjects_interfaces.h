//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================

#ifndef MOVIEOBJECTS_INTERFACE_H
#define MOVIEOBJECTS_INTERFACE_H

#ifdef _WIN32
#pragma once
#endif


#include "platform.h"

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class IGlobalFlexController;


//-----------------------------------------------------------------------------
// Global interfaces used by the movieobjects library
//-----------------------------------------------------------------------------
extern IGlobalFlexController *g_pGlobalFlexController;


#endif // MOVIEOBJECTS_INTERFACE_H