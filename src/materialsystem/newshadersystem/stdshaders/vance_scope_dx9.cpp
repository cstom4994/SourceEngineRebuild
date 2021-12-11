//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#include "BaseVSShader.h"
#include "convar.h"

#include "vance_scope_ps30.inc"
#include "vance_scope_vs30.inc"

ConVar vance_sniper_scope_dist("vance_sniper_scope_dist", "5.0");
ConVar vance_sniper_scope_scale("vance_sniper_scope_scale", "5.0");

BEGIN_VS_SHADER( Scope, "VANCE Scope shader, like in insurgency or something" )

	BEGIN_SHADER_PARAMS
		SHADER_PARAM( OVERLAY, SHADER_PARAM_TYPE_TEXTURE, "", "" )
	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
		if (params[BASETEXTURE]->IsDefined())
		{
			LoadTexture(BASETEXTURE);
		}
		if (params[OVERLAY]->IsDefined())
		{
			LoadTexture(OVERLAY);
		}
	}

	SHADER_DRAW
	{ 
		SHADOW_STATE
		{
			pShaderShadow->EnableSRGBWrite(true);
			pShaderShadow->EnableDepthWrites(false);

			unsigned int flags = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_FORMAT_COMPRESSED;
			// We need three texcoords, all in the default float2 size
			pShaderShadow->VertexShaderVertexFormat(flags, 1, 0, 0);

			pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);		// Base (albedo) map
			pShaderShadow->EnableSRGBRead(SHADER_SAMPLER0, true);
			pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);		// Overlay

			// Vertex Shader
			DECLARE_STATIC_VERTEX_SHADER(vance_scope_vs30);
			SET_STATIC_VERTEX_SHADER(vance_scope_vs30);

			DECLARE_STATIC_PIXEL_SHADER(vance_scope_ps30);
			SET_STATIC_PIXEL_SHADER(vance_scope_ps30);
		}
		DYNAMIC_STATE
		{
			BindTexture(SHADER_SAMPLER0, BASETEXTURE, FRAME);
			BindTexture(SHADER_SAMPLER1, OVERLAY);

			int numBones = pShaderAPI->GetCurrentNumBones();

			float vEyePos_SpecExponent[4];
			pShaderAPI->GetWorldSpaceCameraPosition(vEyePos_SpecExponent);
			vEyePos_SpecExponent[3] = 0.0f;
			pShaderAPI->SetPixelShaderConstant(0, vEyePos_SpecExponent, 1);

			float settings[2] = { vance_sniper_scope_dist.GetFloat(), vance_sniper_scope_scale.GetFloat()};
			pShaderAPI->SetPixelShaderConstant(1, settings, 1);

			int width, height;
			pShaderAPI->GetBackBufferDimensions(width, height);
			float resolution[2] = {width, height};
			pShaderAPI->SetPixelShaderConstant(2, resolution, 1);

			// Set Vertex Shader Combos
			DECLARE_DYNAMIC_VERTEX_SHADER(vance_scope_vs30);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, numBones > 0);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, (int)vertexCompression);
			SET_DYNAMIC_VERTEX_SHADER(vance_scope_vs30);

			DECLARE_DYNAMIC_PIXEL_SHADER(vance_scope_ps30);
			SET_DYNAMIC_PIXEL_SHADER(vance_scope_ps30);
		}
	
		Draw();
	}

END_SHADER

