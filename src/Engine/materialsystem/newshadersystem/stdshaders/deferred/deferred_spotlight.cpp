//===== Copyright  1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "../BaseVSShader.h"

#include "deferred_composite_vs30.inc"
#include "deferred_spotlight_ps30.inc"

#include "IDeferredExt.h"

BEGIN_VS_SHADER_FLAGS(deferred_spotlight, "", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "")
SHADER_PARAM(ALBEDO, SHADER_PARAM_TYPE_TEXTURE, "_rt_defAlbedo", "")
SHADER_PARAM(POSITION, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPosition", "")
SHADER_PARAM(NORMAL, SHADER_PARAM_TYPE_TEXTURE, "_rt_defNormal", "")
SHADER_PARAM(MR, SHADER_PARAM_TYPE_TEXTURE, "_rt_defMR", "")
SHADER_PARAM(AO, SHADER_PARAM_TYPE_TEXTURE, "_rt_SSGIFB1", "")
SHADER_PARAM(DEPTH, SHADER_PARAM_TYPE_TEXTURE, "_rt_DepthBuffer", "")
END_SHADER_PARAMS
SHADER_INIT_PARAMS()
{
	params[FBTEXTURE]->SetStringValue("_rt_FullFrameFB");
	params[AO]->SetStringValue("_rt_SSGIFB");
	params[ALBEDO]->SetStringValue("_rt_defAlbedo");
	params[POSITION]->SetStringValue("_rt_defPosition");
	params[NORMAL]->SetStringValue("_rt_defNormal");
	params[MR]->SetStringValue("_rt_defMR");
	params[DEPTH]->SetStringValue("_rt_DepthBuffer");
}

SHADER_INIT
{
	if (params[FBTEXTURE]->IsDefined())
	{
		LoadTexture(FBTEXTURE);
	}
	if (params[ALBEDO]->IsDefined())
	{
		LoadTexture(ALBEDO);
	}
	if (params[POSITION]->IsDefined())
	{
		LoadTexture(POSITION);
	}
	if (params[NORMAL]->IsDefined())
	{
		LoadTexture(NORMAL);
	}
	if (params[MR]->IsDefined())
	{
		LoadTexture(MR);
	}
	if (params[AO]->IsDefined())
	{
		LoadTexture(AO);
	}
	if (params[DEPTH]->IsDefined())
	{
		LoadTexture(DEPTH);
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

		EnableAlphaBlending(SHADER_BLEND_ONE, SHADER_BLEND_ONE);

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
			DECLARE_STATIC_PIXEL_SHADER(deferred_spotlight_ps30);
			SET_STATIC_PIXEL_SHADER(deferred_spotlight_ps30);
		}
	}

	DYNAMIC_STATE
	{
		BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);
		BindTexture(SHADER_SAMPLER1, ALBEDO, -1);
		BindTexture(SHADER_SAMPLER2, POSITION, -1);
		BindTexture(SHADER_SAMPLER3, NORMAL, -1);
		BindTexture(SHADER_SAMPLER4, MR, -1);
		BindTexture(SHADER_SAMPLER5, AO, -1);
		BindTexture(SHADER_SAMPLER6, DEPTH, -1);

		int nWidth, nHeight;
		pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
		float fResolution[4];
		fResolution[0] = float(nWidth);
		fResolution[1] = float(nHeight);
		pShaderAPI->SetPixelShaderConstant(1, fResolution);

		// Set Pixel Shader Constants 
		pShaderAPI->SetPixelShaderConstant(2, GetDeferredExt()->GetOriginBase());

		Vector4D lightData[MAX_LIGHTS_SPOT * 3];
		for (int i = 0; i < MAX_LIGHTS_SPOT * 3; i = i + 3)
		{
			lightData_Spot_t light = GetDeferredExt()->GetLightData_Spot(i / 3);
			lightData[i].Init(light.pos.x, light.pos.y, light.pos.z, light.pos.w);
			lightData[i + 1].Init(light.diff.x, light.diff.y, light.diff.z, light.diff.w);
			lightData[i + 2].Init(light.dir.x, light.dir.y, light.dir.z, light.dir.w);
		}
		pShaderAPI->SetPixelShaderConstant(4, lightData[0].Base(), MAX_LIGHTS_SPOT * 3);

		DECLARE_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(deferred_spotlight_ps30);
		SET_DYNAMIC_PIXEL_SHADER(deferred_spotlight_ps30);
	}
	Draw();
}
END_SHADER
