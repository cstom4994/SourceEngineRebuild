//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef SHADERAPIVK_GLOBAL_H
#define SHADERAPIVK_GLOBAL_H

#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class IShaderUtil;
class IShaderManager;

//-----------------------------------------------------------------------------
// Global interfaces
//-----------------------------------------------------------------------------
extern IShaderUtil *g_pShaderUtil;
inline IShaderUtil *ShaderUtil() { return g_pShaderUtil; }

//-----------------------------------------------------------------------------
// Manager of all vertex + pixel shaders
//-----------------------------------------------------------------------------
inline IShaderManager *ShaderManager()
{
	extern IShaderManager *g_pShaderManager;
	return g_pShaderManager;
}

#endif // SHADERAPIVK_GLOBAL_H