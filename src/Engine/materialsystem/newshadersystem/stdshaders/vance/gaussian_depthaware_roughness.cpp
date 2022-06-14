//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"
#include "IDeferredExt.h"

#include "screenspace_simple_vs30.inc"
#include "gaussian_depthaware_roughness_ps30.inc"

ConVar r_post_ssr_blursize("r_post_ssr_blursize", "5.0", FCVAR_CHEAT);
ConVar r_post_ssr_blurarea("r_post_ssr_blurarea", "0.001", FCVAR_CHEAT);
ConVar r_post_ssr_blurangle_theshold("r_post_ssr_blurangle_theshold", "30", FCVAR_CHEAT);

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER( Gaussian_DepthAware_Roughness, "Depth aware gaussian blur that depends on roughness from MRAO buffer" )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
		SHADER_PARAM( DEPTHBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_DepthBuffer", "")
		SHADER_PARAM( MRAO, SHADER_PARAM_TYPE_TEXTURE, "_rt_MRAO", "")
		SHADER_PARAM( NORMALS, SHADER_PARAM_TYPE_TEXTURE, "_rt_Normals", "")
		SHADER_PARAM( HORIZONTAL, SHADER_PARAM_TYPE_INTEGER, "1", "")
		SHADER_PARAM( BLURSIZE, SHADER_PARAM_TYPE_FLOAT, "1.0", "" )
		SHADER_PARAM(RESDIVISOR, SHADER_PARAM_TYPE_INTEGER, "1", "")
	END_SHADER_PARAMS


	SHADER_INIT_PARAMS()
	{
		params[DEPTHBUFFER]->SetStringValue("_rt_DepthBuffer");
		params[NORMALS]->SetStringValue("_rt_Normals");
	}

	SHADER_INIT
	{
		if( params[FBTEXTURE]->IsDefined() )
		{
			LoadTexture( FBTEXTURE );
		}
		if (params[DEPTHBUFFER]->IsDefined())
		{
			LoadTexture(DEPTHBUFFER);
		}
		if (params[NORMALS]->IsDefined())
		{
			LoadTexture(NORMALS);
		}
		if (params[MRAO]->IsDefined())
		{
			LoadTexture(MRAO);
		}
	}
	
	SHADER_FALLBACK
	{
		// Requires DX9 + above
		if ( g_pHardwareConfig->GetDXSupportLevel() < 90 )
		{
			Assert( 0 );
			return "Wireframe";
		}
		return 0;
	}

	SHADER_DRAW
	{
		SHADOW_STATE
		{
			pShaderShadow->EnableDepthWrites( false );

			pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );
			pShaderShadow->EnableTexture( SHADER_SAMPLER1, true);
			pShaderShadow->EnableTexture( SHADER_SAMPLER2, true);
			pShaderShadow->EnableTexture( SHADER_SAMPLER3, true);
			int fmt = VERTEX_POSITION;
			pShaderShadow->VertexShaderVertexFormat( fmt, 1, 0, 0 );

			// Pre-cache shaders
			DECLARE_STATIC_VERTEX_SHADER( screenspace_simple_vs30 );
			SET_STATIC_VERTEX_SHADER( screenspace_simple_vs30 );

			DECLARE_STATIC_PIXEL_SHADER(gaussian_depthaware_roughness_ps30);
			SET_STATIC_PIXEL_SHADER_COMBO(HORIZONTAL, params[HORIZONTAL]->GetIntValue());
			SET_STATIC_PIXEL_SHADER(gaussian_depthaware_roughness_ps30);
		}

		DYNAMIC_STATE
		{
			float fBlurSize[4];
			fBlurSize[0] = r_post_ssr_blursize.GetFloat();
			fBlurSize[1] = r_post_ssr_blurarea.GetFloat();
			fBlurSize[2] = cos(r_post_ssr_blurangle_theshold.GetFloat());
			fBlurSize[3] = 0.0f;
			pShaderAPI->SetPixelShaderConstant( 0, fBlurSize );

			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
			float fResolution[4];
			fResolution[0] = float(1.0 / nWidth);
			fResolution[1] = float(1.0 / nHeight);
			pShaderAPI->SetPixelShaderConstant(1, fResolution);

			float zPlanes[2] = { GetDeferredExt()->GetZDistNear(), GetDeferredExt()->GetZDistFar() };
			pShaderAPI->SetPixelShaderConstant(6, zPlanes);
			
			BindTexture( SHADER_SAMPLER0, FBTEXTURE, -1 );
			BindTexture( SHADER_SAMPLER1, DEPTHBUFFER, -1);
			BindTexture( SHADER_SAMPLER2, NORMALS, -1);
			BindTexture( SHADER_SAMPLER3, MRAO, -1);
			DECLARE_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs30 );

			pShaderAPI->SetPixelShaderConstant(2, GetDeferredExt()->m_matProjInv.Base(), 4);

			//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER(gaussian_depthaware_roughness_ps30);
				SET_DYNAMIC_PIXEL_SHADER(gaussian_depthaware_roughness_ps30);
			}
		}
		Draw();
	}
END_SHADER