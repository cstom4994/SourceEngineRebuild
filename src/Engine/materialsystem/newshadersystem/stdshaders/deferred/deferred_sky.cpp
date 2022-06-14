//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "deferred_composite_vs30.inc"
#include "deferred_sky_ps30.inc"

extern ConVar cl_sky_thickness;
extern ConVar cl_sky_coverage;
extern ConVar cl_sky_SunPos;
extern ConVar cl_sky_windspeed;

static void UTIL_StringToFloatArray(float* pVector, int count, const char* pString)
{
	char* pstr, * pfront, tempString[128];
	int	j;

	Q_strncpy(tempString, pString, sizeof(tempString));
	pstr = pfront = tempString;

	for (j = 0; j < count; j++)			// lifted from pr_edict.c
	{
		pVector[j] = atof(pfront);

		// skip any leading whitespace
		while (*pstr && *pstr <= ' ')
			pstr++;

		// skip to next whitespace
		while (*pstr && *pstr > ' ')
			pstr++;

		if (!*pstr)
			break;

		pstr++;
		pfront = pstr;
	}
	for (j++; j < count; j++)
	{
		pVector[j] = 0;
	}
}

BEGIN_VS_SHADER_FLAGS(deferred_sky, "Sky atmosphere screen-space shader", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(POSITION, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPosition", "")
END_SHADER_PARAMS

SHADER_INIT_PARAMS()
{
	params[POSITION]->SetStringValue("_rt_defPosition");
}

SHADER_INIT
{
	if (params[POSITION]->IsDefined())
	{
		LoadTexture(POSITION);
	}
}

SHADER_FALLBACK
{
	// Requires DX9 + above
	if (g_pHardwareConfig->GetDXSupportLevel() < 90)
	{
		Assert(0);
		return "Wireframe";
	}
	return 0;
}

SHADER_DRAW
{
	SHADOW_STATE
	{
		pShaderShadow->EnableDepthWrites(false);

		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		// Pre-cache shaders
		DECLARE_STATIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_STATIC_VERTEX_SHADER(deferred_composite_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_STATIC_PIXEL_SHADER(deferred_sky_ps30);
			SET_STATIC_PIXEL_SHADER(deferred_sky_ps30);
		}
	}

	DYNAMIC_STATE
	{
		BindTexture(SHADER_SAMPLER0, POSITION, -1);

		DECLARE_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_DYNAMIC_PIXEL_SHADER(deferred_sky_ps30);
			SET_DYNAMIC_PIXEL_SHADER(deferred_sky_ps30);
		}

		float flthickness[4];
		flthickness[0] = cl_sky_thickness.GetFloat();
		flthickness[1] = flthickness[2] = flthickness[3] = flthickness[0];
		pShaderAPI->SetPixelShaderConstant(4, flthickness);

		float flcoverage[4];
		flcoverage[0] = cl_sky_coverage.GetFloat();
		flcoverage[1] = flcoverage[2] = flcoverage[3] = flcoverage[0];
		pShaderAPI->SetPixelShaderConstant(5, flcoverage);

		float flSunPos[4];
		UTIL_StringToFloatArray(flSunPos, 4, cl_sky_SunPos.GetString());
		pShaderAPI->SetPixelShaderConstant(6, flSunPos);

		float flwindspeed[4];
		UTIL_StringToFloatArray(flwindspeed, 4, cl_sky_windspeed.GetString());
		pShaderAPI->SetPixelShaderConstant(7, flwindspeed);

		float flTime[4];
		flTime[0] = pShaderAPI->CurrentTime();
		flTime[1] = flTime[2] = flTime[3] = flTime[0];
		pShaderAPI->SetPixelShaderConstant(8, flTime);

	}
	Draw();
}
END_SHADER
