//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"
#include "IDeferredExt.h"

#include "passthru_vs30.inc"
#include "ssgi_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static ConVar r_post_ssgi_bias("r_post_ssao_bias", "0.001");
static ConVar r_post_ssgi_radius("r_post_ssao_radius", "5");
static ConVar r_post_ssgi_fallof("r_post_ssao_fallof", "0.0");
static ConVar r_post_ssgi_area("r_post_ssao_area", "0.005");
static ConVar r_post_ssgi_strength("r_post_ssao_strength", "0.175");
static ConVar r_post_ssgi_samples("r_post_ssao_samples", "16");

extern ConVar csm_enabled;

BEGIN_VS_SHADER_FLAGS(SSGI, "Help for SSGI", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(DEPTHBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_DepthBuffer", "")
SHADER_PARAM(NOISE, SHADER_PARAM_TYPE_TEXTURE, "shaders/bluenoise", "")
SHADER_PARAM(FRAMEBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_VanceHDR", "")
SHADER_PARAM(CSM, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPassCSM", "")
SHADER_PARAM(NORMAL, SHADER_PARAM_TYPE_TEXTURE, "_rt_defNormal", "")
SHADER_PARAM(POSITION, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPosition", "")
END_SHADER_PARAMS
SHADER_INIT_PARAMS()
{
	params[NOISE]->SetStringValue("shaders/bluenoise");
	params[CSM]->SetStringValue("_rt_defPassCSM");
	params[NORMAL]->SetStringValue("_rt_Normals");
	params[POSITION]->SetStringValue("_rt_defPosition");
	params[DEPTHBUFFER]->SetStringValue("_rt_DepthBuffer");
	params[FRAMEBUFFER]->SetStringValue("_rt_VanceHDR");
}

SHADER_INIT
{
	if (params[DEPTHBUFFER]->IsDefined())
	{
		LoadTexture(DEPTHBUFFER);
	}
	if (params[FRAMEBUFFER]->IsDefined())
	{
		LoadTexture(FRAMEBUFFER);
	}
	if (params[NOISE]->IsDefined())
	{
		LoadTexture(NOISE);
	}
	if (params[CSM]->IsDefined())
	{
		LoadTexture(CSM);
	}
	if (params[NORMAL]->IsDefined())
	{
		LoadTexture(NORMAL);
	}
	if (params[POSITION]->IsDefined())
	{
		LoadTexture(POSITION);
	}
}

SHADER_FALLBACK
{
	// Requires DX9 + above
	// But for some reason some GPUs dont support the SM3 but they clearly do, probably a bug
	/*if ( g_pHardwareConfig->GetDXSupportLevel() < 90 || !g_pHardwareConfig->SupportsShaderModel_3_0() )
	{
		Assert( 0 );
		return "Wireframe";
	}*/
	return 0;
}

SHADER_DRAW
{
	SHADOW_STATE
	{
		pShaderShadow->EnableDepthWrites(false);
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER5, true);

		DECLARE_STATIC_VERTEX_SHADER(passthru_vs30);
		SET_STATIC_VERTEX_SHADER(passthru_vs30);

		DECLARE_STATIC_PIXEL_SHADER(ssgi_ps30);
		SET_STATIC_PIXEL_SHADER(ssgi_ps30);
	}

	DYNAMIC_STATE
	{
		int nWidth, nHeight;
		pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
		float fResolution[4];
		fResolution[0] = float(1.0 / nWidth);
		fResolution[1] = float(1.0 / nHeight);
		pShaderAPI->SetPixelShaderConstant(1, fResolution);

		float fTime[4];
		fTime[0] = pShaderAPI->CurrentTime();
		fTime[2] = fTime[1] = fTime[0];
		pShaderAPI->SetPixelShaderConstant(2, fTime);

		float flParams[4];
		flParams[0] = r_post_ssgi_radius.GetFloat();
		flParams[1] = 1.0f;
		flParams[2] = r_post_ssgi_fallof.GetFloat();
		flParams[3] = r_post_ssgi_strength.GetFloat();
		pShaderAPI->SetPixelShaderConstant(4, flParams);

		float flParams2[4];
		flParams2[0] = r_post_ssgi_bias.GetFloat();
		flParams2[1] = r_post_ssgi_area.GetFloat();
		flParams2[2] = r_post_ssgi_samples.GetFloat();
		flParams2[3] = 0;
		pShaderAPI->SetPixelShaderConstant(5, flParams2);

		float zPlanes[2] = { GetDeferredExt()->GetZDistNear(), GetDeferredExt()->GetZDistFar() };
		pShaderAPI->SetPixelShaderConstant(6, zPlanes);

		pShaderAPI->SetPixelShaderConstant(7, GetDeferredExt()->GetOriginBase());

		pShaderAPI->SetPixelShaderConstant(8, GetDeferredExt()->m_matViewInv.Base(), 4);
		pShaderAPI->SetPixelShaderConstant(12, GetDeferredExt()->m_matProjInv.Base(), 4);
		pShaderAPI->SetPixelShaderConstant(16, GetDeferredExt()->m_matView.Base(), 4);
		pShaderAPI->SetPixelShaderConstant(20, GetDeferredExt()->m_matProj.Base(), 4);

		BindTexture(SHADER_SAMPLER0, DEPTHBUFFER);
		BindTexture(SHADER_SAMPLER1, FRAMEBUFFER);
		BindTexture(SHADER_SAMPLER2, NOISE);
		BindTexture(SHADER_SAMPLER3, CSM);
		BindTexture(SHADER_SAMPLER4, NORMAL);
		BindTexture(SHADER_SAMPLER5, POSITION);

		DECLARE_DYNAMIC_VERTEX_SHADER(passthru_vs30);
		SET_DYNAMIC_VERTEX_SHADER(passthru_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(ssgi_ps30);
		SET_DYNAMIC_PIXEL_SHADER(ssgi_ps30);
	}
	Draw();
}
END_SHADER