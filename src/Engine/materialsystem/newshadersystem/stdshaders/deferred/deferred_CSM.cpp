//===== Copyright  1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "deferred_composite_vs30.inc"
#include "deferred_CSM_ps30.inc"

#include "IDeferredExt.h"

ConVar csm_enabled("r_csm", "1", 0, "0 = off, 1 = on/force");
ConVar r_csm_bias("r_csm_post_bias", "0.0");
ConVar r_csm_slopescalebias("r_csm_post_slopescale_depthbias", "1");

BEGIN_VS_SHADER_FLAGS(deferred_CSM, "Help for Bloom", SHADER_NOT_EDITABLE)
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
		pShaderShadow->SetDefaultState();

		pShaderShadow->EnableDepthTest(false);

		EnableAlphaBlending(SHADER_BLEND_ONE, SHADER_BLEND_ONE);

		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER5, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER6, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER7, true);
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		// Pre-cache shaders
		DECLARE_STATIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_STATIC_VERTEX_SHADER(deferred_composite_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_STATIC_PIXEL_SHADER(deferred_csm_ps30);
			SET_STATIC_PIXEL_SHADER(deferred_csm_ps30);
		}
	}

	DYNAMIC_STATE
	{

		ITexture* pCascadedDepthTexture = (ITexture*)pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_CASCADED_DEPTHTEXTURE);

		if (!pCascadedDepthTexture)
		{
			Draw(false);
			return;
		}
		pShaderAPI->SetDefaultState();
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

		float flZDists[2];
		flZDists[0] = GetDeferredExt()->GetZDistNear();
		flZDists[1] = GetDeferredExt()->GetZDistFar();
		flZDists[2] = GetDeferredExt()->GetZScale();
		pShaderAPI->SetPixelShaderConstant(3, flZDists);


		if (pCascadedDepthTexture)
		{
			BindTexture(SHADER_SAMPLER7, pCascadedDepthTexture, -1);
			VMatrix* worldToTexture0 = (VMatrix*)pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_CASCADED_MATRIX_ADDRESS_0);
			pShaderAPI->SetPixelShaderConstant(4, worldToTexture0->Base(), 4);
		}

		lightData_Global_t csmData = GetDeferredExt()->GetLightData_Global();
		Vector csmFwd = csmData.vecLight;
		pShaderAPI->SetPixelShaderConstant(8, csmFwd.Base());

		Vector csmLight = csmData.light.AsVector3D();
		pShaderAPI->SetPixelShaderConstant(9, csmLight.Base());

		Vector csmAmbient = csmData.ambient.AsVector3D();
		pShaderAPI->SetPixelShaderConstant(10, csmAmbient.Base());

		float biasVar[2] = { r_csm_slopescalebias.GetFloat(), r_csm_bias.GetFloat() };
		pShaderAPI->SetPixelShaderConstant(11, biasVar);

		float textureSize[2] = { pCascadedDepthTexture->GetMappingHeight() * 4.0f, pCascadedDepthTexture->GetMappingHeight() };
		pShaderAPI->SetPixelShaderConstant(12, textureSize);

		pShaderAPI->SetPixelShaderConstant(13, GetDeferredExt()->GetLightData_Global().sizes.Base());

		DECLARE_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(deferred_csm_ps30);
		SET_DYNAMIC_PIXEL_SHADER_COMBO(AMBIENT, 0);
		SET_DYNAMIC_PIXEL_SHADER(deferred_csm_ps30);

	}
	Draw();
}
END_SHADER
