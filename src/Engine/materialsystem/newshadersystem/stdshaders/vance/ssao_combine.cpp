//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "SDK_screenspaceeffect_vs30.inc"
#include "ssgi_combine_ps30.inc"


BEGIN_VS_SHADER_FLAGS(SSGI_Combine, "Help for SSGI", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "")
SHADER_PARAM(COMBINE, SHADER_PARAM_TYPE_TEXTURE, "_rt_SSGI02", "")
SHADER_PARAM(ALBEDO, SHADER_PARAM_TYPE_TEXTURE, "_rt_defAlbedo", "")
SHADER_PARAM(AMOUNT, SHADER_PARAM_TYPE_FLOAT, "1", "")
END_SHADER_PARAMS

SHADER_INIT_PARAMS()
{
	params[ALBEDO]->SetStringValue("_rt_defAlbedo");
}

SHADER_INIT
{
	if (params[FBTEXTURE]->IsDefined())
	{
		LoadTexture(FBTEXTURE);
	}
	if (params[COMBINE]->IsDefined())
	{
		LoadTexture(COMBINE);
	}
	if (params[ALBEDO]->IsDefined())
	{
		LoadTexture(ALBEDO);
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
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		// Pre-cache shaders
		DECLARE_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);
		SET_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_STATIC_PIXEL_SHADER(ssgi_combine_ps30);
			SET_STATIC_PIXEL_SHADER(ssgi_combine_ps30);
		}
	}

	DYNAMIC_STATE
	{
		BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);
		BindTexture(SHADER_SAMPLER1, COMBINE, -1);
		BindTexture(SHADER_SAMPLER2, ALBEDO, -1);

		float fBlurSize[4];
		fBlurSize[0] = 1.0f;
		fBlurSize[1] = fBlurSize[2] = fBlurSize[3] = fBlurSize[0];
		pShaderAPI->SetPixelShaderConstant(0, fBlurSize);

		int nWidth, nHeight;
		pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
		float fResolution[4];
		fResolution[0] = float(1.0 / nWidth);
		fResolution[1] = float(1.0 / nHeight);
		pShaderAPI->SetPixelShaderConstant(1, fResolution);

		DECLARE_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);
		SET_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_DYNAMIC_PIXEL_SHADER(ssgi_combine_ps30);
			SET_DYNAMIC_PIXEL_SHADER(ssgi_combine_ps30);
		}
	}
	Draw();
}
END_SHADER
