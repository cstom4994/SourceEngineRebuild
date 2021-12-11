//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "../BaseVSShader.h"

#include "deferred_composite_vs30.inc"
#include "deferred_composite_ps30.inc"

BEGIN_VS_SHADER_FLAGS(deferred_composite, "Help for Bloom", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "")
SHADER_PARAM(LIGHTTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_defLightPass", "")
SHADER_PARAM(SKYTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPassSky", "")
SHADER_PARAM(VOLUMETRICS, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPassVolumetrics", "")
SHADER_PARAM(POSITION, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPosition", "")
END_SHADER_PARAMS

SHADER_INIT_PARAMS()
{
	params[FBTEXTURE]->SetStringValue("_rt_FullFrameFB");
	params[LIGHTTEXTURE]->SetStringValue("_rt_defLightPass");
	params[SKYTEXTURE]->SetStringValue("_rt_defPassSky");
	params[POSITION]->SetStringValue("_rt_defPosition");
	params[VOLUMETRICS]->SetStringValue("_rt_defPassVolumetrics");
}

SHADER_INIT
{
	if (params[FBTEXTURE]->IsDefined())
	{
		LoadTexture(FBTEXTURE);
	}
	if (params[LIGHTTEXTURE]->IsDefined())
	{
		LoadTexture(LIGHTTEXTURE);
	}
	if (params[SKYTEXTURE]->IsDefined())
	{
		LoadTexture(SKYTEXTURE);
	}
	if (params[POSITION]->IsDefined())
	{
		LoadTexture(POSITION);
	}
	if (params[VOLUMETRICS]->IsDefined())
	{
		LoadTexture(VOLUMETRICS);
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
		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER5, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER6, true);
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		// Pre-cache shaders
		DECLARE_STATIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_STATIC_VERTEX_SHADER(deferred_composite_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_STATIC_PIXEL_SHADER(deferred_composite_ps30);
			SET_STATIC_PIXEL_SHADER(deferred_composite_ps30);
		}
	}

	DYNAMIC_STATE
	{
		BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);
		BindTexture(SHADER_SAMPLER1, LIGHTTEXTURE);
		pShaderAPI->BindStandardTexture(SHADER_SAMPLER2, TEXTURE_BLACK);
		BindTexture(SHADER_SAMPLER3, SKYTEXTURE, -1);
		BindTexture(SHADER_SAMPLER4, POSITION, -1);
		pShaderAPI->BindStandardTexture(SHADER_SAMPLER5, TEXTURE_BLACK);
		BindTexture(SHADER_SAMPLER6, VOLUMETRICS, -1);

		int nWidth, nHeight;
		pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
		float fResolution[4];
		fResolution[0] = float(nWidth);
		fResolution[1] = float(nHeight);
		pShaderAPI->SetPixelShaderConstant(1, fResolution);

		DECLARE_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_DYNAMIC_PIXEL_SHADER(deferred_composite_ps30);
			SET_DYNAMIC_PIXEL_SHADER(deferred_composite_ps30);
		}
	}
	Draw();
}
END_SHADER
