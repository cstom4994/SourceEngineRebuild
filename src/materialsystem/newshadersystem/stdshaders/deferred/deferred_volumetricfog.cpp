//===== Copyright  1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "deferred_composite_vs30.inc"
#include "deferred_volumetricfog_ps30.inc"

#include "IDeferredExt.h"

extern ConVar csm_enabled;
extern ConVar r_csm_bias;
extern ConVar r_csm_slopescalebias;

static ConVar r_volumetricfog_height("r_volumetricfog_height", "0"/*, FCVAR_HIDDEN Add this flag when we are going to release the mod*/);
static ConVar r_volumetricfog_density("r_volumetricfog_density", "1"/*, FCVAR_HIDDEN*/);
static ConVar r_volumetricfog_color("r_volumetricfog_color", "1 1 1"/*, FCVAR_HIDDEN*/);
static ConVar r_volumetricfog_height2("r_volumetricfog_height2", "0"/*, FCVAR_HIDDEN*/);
static ConVar r_volumetricfog_csm("r_volumetricfog_csm", "0"/*, FCVAR_HIDDEN*/);
static ConVar r_volumetricfog_noise("r_volumetricfog_noise", "1"/*, FCVAR_HIDDEN*/);

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

BEGIN_VS_SHADER_FLAGS(deferred_volumetricfog, "Help for Bloom", SHADER_NOT_EDITABLE)
BEGIN_SHADER_PARAMS
SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "")
SHADER_PARAM(POSITION, SHADER_PARAM_TYPE_TEXTURE, "_rt_defPosition", "")
SHADER_PARAM(NORMAL, SHADER_PARAM_TYPE_TEXTURE, "_rt_defNormal", "")
SHADER_PARAM(DEPTH, SHADER_PARAM_TYPE_TEXTURE, "_rt_DepthBuffer", "")
SHADER_PARAM(MR, SHADER_PARAM_TYPE_TEXTURE, "_rt_defMR", "")
END_SHADER_PARAMS
SHADER_INIT_PARAMS()
{
	params[FBTEXTURE]->SetStringValue("_rt_FullFrameFB");
	params[POSITION]->SetStringValue("_rt_defPosition");
	params[NORMAL]->SetStringValue("_rt_defNormal");
	params[DEPTH]->SetStringValue("_rt_DepthBuffer");
	params[MR]->SetStringValue("_rt_defMR");
}

SHADER_INIT
{
	if (params[FBTEXTURE]->IsDefined())
	{
		LoadTexture(FBTEXTURE);
	}
	if (params[POSITION]->IsDefined())
	{
		LoadTexture(POSITION);
	}
	if (params[NORMAL]->IsDefined())
	{
		LoadTexture(NORMAL);
	}
	if (params[DEPTH]->IsDefined())
	{
		LoadTexture(DEPTH);
	}
	if (params[MR]->IsDefined())
	{
		LoadTexture(MR);
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

		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER5, true);
		int fmt = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(fmt, 1, 0, 0);

		// Pre-cache shaders
		DECLARE_STATIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_STATIC_VERTEX_SHADER(deferred_composite_vs30);

		//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
		{
			DECLARE_STATIC_PIXEL_SHADER(deferred_volumetricfog_ps30);
			SET_STATIC_PIXEL_SHADER(deferred_volumetricfog_ps30);
		}
	}

	DYNAMIC_STATE
	{

		ITexture * pCascadedDepthTexture = (ITexture*)pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_CASCADED_DEPTHTEXTURE);
		bool hasShadow = true;

		if (!pCascadedDepthTexture)
		{
			hasShadow = false;
		}
		pShaderAPI->SetDefaultState();
		BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);
		BindTexture(SHADER_SAMPLER1, POSITION, -1);
		BindTexture(SHADER_SAMPLER2, NORMAL, -1);
		BindTexture(SHADER_SAMPLER3, DEPTH, -1);
		BindTexture(SHADER_SAMPLER5, MR, -1);

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


		if (hasShadow)
		{
			BindTexture(SHADER_SAMPLER4, pCascadedDepthTexture, -1);
			VMatrix * worldToTexture0 = (VMatrix*)pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_CASCADED_MATRIX_ADDRESS_0);
			pShaderAPI->SetPixelShaderConstant(4, worldToTexture0->Base(), 4);

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
		}

		float fogVar[3] = { r_volumetricfog_height.GetFloat(), r_volumetricfog_height2.GetFloat(), r_volumetricfog_density.GetFloat() };
		pShaderAPI->SetPixelShaderConstant(14, fogVar);

		float fogColor[3];
		UTIL_StringToFloatArray(fogColor, 3, r_volumetricfog_color.GetString());
		pShaderAPI->SetPixelShaderConstant(15, fogColor);

		DECLARE_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);
		SET_DYNAMIC_VERTEX_SHADER(deferred_composite_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(deferred_volumetricfog_ps30);
		SET_DYNAMIC_PIXEL_SHADER_COMBO(FOG, r_volumetricfog_density.GetFloat() != 0.0f);
		SET_DYNAMIC_PIXEL_SHADER_COMBO(CSM, r_volumetricfog_csm.GetBool() && hasShadow);
		SET_DYNAMIC_PIXEL_SHADER(deferred_volumetricfog_ps30);

	}
	Draw();
}
END_SHADER
