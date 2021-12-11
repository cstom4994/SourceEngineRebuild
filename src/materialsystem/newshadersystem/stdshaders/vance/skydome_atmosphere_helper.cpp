//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//
#include "BaseVSShader.h"
#include "skydome_atmosphere_helper.h"
#include "convar.h"
#include "cpp_shader_constant_register_map.h"
#include "skydome_vs30.inc"
#include "skydome_ps30.inc"
#include "commandbuilder.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static ConVar mat_fullbright("mat_fullbright", "0", FCVAR_CHEAT);


//-----------------------------------------------------------------------------
// Initialize shader parameters
//-----------------------------------------------------------------------------
void InitParamsSkydome(CBaseVSShader *pShader, IMaterialVar** params, const char *pMaterialName, Skydome_Vars_t &info)
{
}

//-----------------------------------------------------------------------------
// Initialize shader
//-----------------------------------------------------------------------------
void InitSkydome(CBaseVSShader *pShader, IMaterialVar** params, Skydome_Vars_t &info)
{
}
