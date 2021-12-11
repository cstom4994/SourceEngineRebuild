//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#include "BaseVSShader.h"
#include "convar.h"
#include "skydome_atmosphere_helper.h"
#include "commandbuilder.h"
#include "IDeferredExt.h"

#include "light_mesh_vs30.inc"
#include "light_mesh_ps30.inc"


BEGIN_VS_SHADER(LIGHT, "Lighting")

BEGIN_SHADER_PARAMS
SHADER_PARAM(NORMAL, SHADER_PARAM_TYPE_TEXTURE, "_rt_Normals", "")
SHADER_PARAM(DEPTH, SHADER_PARAM_TYPE_TEXTURE, "_rt_DepthBuffer", "")
SHADER_PARAM(ALBEDO, SHADER_PARAM_TYPE_TEXTURE, "_rt_Albedo", "")
SHADER_PARAM(MRAO, SHADER_PARAM_TYPE_TEXTURE, "_rt_MRAO", "")
END_SHADER_PARAMS

void SetupVars(Skydome_Vars_t& info)
{
}

SHADER_INIT_PARAMS()
{
	params[NORMAL]->SetStringValue("_rt_Normals");
	params[DEPTH]->SetStringValue("_rt_DepthBuffer");
	params[ALBEDO]->SetStringValue("_rt_Albedo");
	params[MRAO]->SetStringValue("_rt_MRAO");
}

SHADER_FALLBACK
{
	return 0;
}

SHADER_INIT
{
	if (params[DEPTH]->IsDefined())
	{
		LoadTexture(DEPTH);
	}
	if (params[NORMAL]->IsDefined())
	{
		LoadTexture(NORMAL);
	}
	if (params[ALBEDO]->IsDefined())
	{
		LoadTexture(ALBEDO);
	}
	if (params[MRAO]->IsDefined())
	{
		LoadTexture(MRAO);
	}
}


SHADER_DRAW
{
	if (IsSnapshotting())
	{
		pShaderShadow->EnableSRGBWrite(true);
		pShaderShadow->EnableDepthWrites(false);
		pShaderShadow->EnableDepthTest(false);
		pShaderShadow->EnableCulling(true);

		EnableAlphaBlending(SHADER_BLEND_SRC_ALPHA, SHADER_BLEND_ONE);

		unsigned int flags = VERTEX_POSITION;
		pShaderShadow->VertexShaderVertexFormat(flags, 1, 0, 0);

		DECLARE_STATIC_VERTEX_SHADER(light_mesh_vs30);
		SET_STATIC_VERTEX_SHADER(light_mesh_vs30);

		// Assume we're only going to get in here if we support 2b
		DECLARE_STATIC_PIXEL_SHADER(light_mesh_ps30);
		SET_STATIC_PIXEL_SHADER(light_mesh_ps30);

		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
	}
	else // not snapshotting -- begin dynamic state
	{
		DECLARE_DYNAMIC_VERTEX_SHADER(light_mesh_vs30);
		SET_DYNAMIC_VERTEX_SHADER(light_mesh_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(light_mesh_ps30);
		SET_DYNAMIC_PIXEL_SHADER(light_mesh_ps30);

		LightDesc_t light = pShaderAPI->GetLight(0);
		float pdot = light.m_PhiDot;
		float tdot = light.m_ThetaDot;
		if (light.m_Type == MATERIAL_LIGHT_POINT)
		{
			// model point light as a spot with infinite inner radius
			pdot = 1.0e10;
			tdot = 0.5;
		}

		float vec1[] = { light.m_Color.x, light.m_Color.y, light.m_Color.z, tdot };
		float vec2[] = { light.m_Direction.x, light.m_Direction.y, light.m_Direction.z, pdot };
		float* vec3 = light.m_Position.Base();
		float vec4[] = { light.m_Attenuation2, light.m_Attenuation1, light.m_Attenuation0, 1.0 };

		pShaderAPI->SetPixelShaderConstant(0, vec1);
		pShaderAPI->SetPixelShaderConstant(1, vec2);
		pShaderAPI->SetPixelShaderConstant(2, vec3);
		pShaderAPI->SetPixelShaderConstant(3, vec4);

		pShaderAPI->SetPixelShaderConstant(4, GetDeferredExt()->GetViewInvBase(), 4);
		pShaderAPI->SetPixelShaderConstant(8, GetDeferredExt()->GetProjInvBase(), 4);

		float vEyePos[4];
		pShaderAPI->GetWorldSpaceCameraPosition(vEyePos);
		pShaderAPI->SetPixelShaderConstant(12, vEyePos);

		BindTexture(SHADER_SAMPLER0, DEPTH);
		BindTexture(SHADER_SAMPLER1, NORMAL);
		BindTexture(SHADER_SAMPLER2, ALBEDO);
		BindTexture(SHADER_SAMPLER3, MRAO);
	}
	
	Draw();
}

END_SHADER

