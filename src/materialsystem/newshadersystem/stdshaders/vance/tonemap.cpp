//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "SDK_screenspaceeffect_vs30.inc"
#include "Vance_Tonemap_ps30.inc"

ConVar r_post_tonemap_underexposure("r_post_tonemap_underexposure", "1");
ConVar r_post_tonemap_overexposure("r_post_tonemap_overexposure", "1");
ConVar r_post_tonemap_exposure("r_post_tonemap_exposure", "1");
ConVar r_post_tonemap_mode("r_post_tonemap_mode", "1");

BEGIN_VS_SHADER_FLAGS(Vance_Tonemap, "Help for Bloom", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "")
END_SHADER_PARAMS

SHADER_INIT
{
	if (params[FBTEXTURE]->IsDefined())
	{
		LoadTexture(FBTEXTURE);
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
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		// Pre-cache shaders
		DECLARE_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);
		SET_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_STATIC_PIXEL_SHADER(vance_tonemap_ps30);
			SET_STATIC_PIXEL_SHADER(vance_tonemap_ps30);
		}
	}

	DYNAMIC_STATE
	{
		BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);

			float fOverExposure[4];
			fOverExposure[0] = r_post_tonemap_overexposure.GetFloat();
			fOverExposure[1] = fOverExposure[2] = fOverExposure[3] = fOverExposure[0];
			pShaderAPI->SetPixelShaderConstant(0, fOverExposure);

			float fUnderExposure[4];
			fUnderExposure[0] = r_post_tonemap_underexposure.GetFloat();
			fUnderExposure[1] = fUnderExposure[2] = fUnderExposure[3] = fUnderExposure[0];
			pShaderAPI->SetPixelShaderConstant(1, fUnderExposure);

			float fExposure[4];
			fExposure[0] = r_post_tonemap_exposure.GetFloat();
			fExposure[1] = fExposure[2] = fExposure[3] = fExposure[0];
			pShaderAPI->SetPixelShaderConstant(2, fExposure);

		DECLARE_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);
		SET_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_DYNAMIC_PIXEL_SHADER(vance_tonemap_ps30);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(MODE, clamp(r_post_tonemap_mode.GetInt(), 0, 3));
			SET_DYNAMIC_PIXEL_SHADER(vance_tonemap_ps30);
		}
	}
	Draw();
}
END_SHADER
