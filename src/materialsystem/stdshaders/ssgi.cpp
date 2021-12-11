//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "passthru_vs30.inc"
#include "ssgi_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER_FLAGS( SSGI, "Help for SSGI", SHADER_NOT_EDITABLE )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( DEPTHBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameDepth", "" )
		SHADER_PARAM( RANDOMNORMAL, SHADER_PARAM_TYPE_TEXTURE, "", "" )
		SHADER_PARAM( FRAMEBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
		SHADER_PARAM( CAMERARANGE, SHADER_PARAM_TYPE_VEC2, "[1 4000]", "" )
	END_SHADER_PARAMS
	SHADER_INIT_PARAMS()
	{
		if( !params[CAMERARANGE]->IsDefined() )
		{
			params[CAMERARANGE]->SetVecValue( 1.0f, 4000.0f );
		}
	}

	SHADER_INIT
	{
		if( params[DEPTHBUFFER]->IsDefined() )
		{
			LoadTexture( DEPTHBUFFER );
		}
		if( params[RANDOMNORMAL]->IsDefined() )
		{
			LoadTexture( RANDOMNORMAL );
		}
		if( params[FRAMEBUFFER]->IsDefined() )
		{
			LoadTexture( FRAMEBUFFER );
		}
	}
	
	SHADER_FALLBACK
	{
		// Requires DX9 + above
		if ( g_pHardwareConfig->GetDXSupportLevel() < 90 || !g_pHardwareConfig->SupportsShaderModel_3_0() )
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
			int fmt = VERTEX_POSITION;
			pShaderShadow->VertexShaderVertexFormat( fmt, 1, 0, 0 );

			pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );

			DECLARE_STATIC_VERTEX_SHADER( passthru_vs30 );
			SET_STATIC_VERTEX_SHADER( passthru_vs30 );

			DECLARE_STATIC_PIXEL_SHADER( ssgi_ps30 );
			SET_STATIC_PIXEL_SHADER( ssgi_ps30 );
		}

		DYNAMIC_STATE
		{
			SetPixelShaderConstant( 0, CAMERARANGE );

			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions( nWidth, nHeight );
			float fResolution[4];
			fResolution[0] = float(1.0/nWidth*0.5);
			fResolution[1] = float(1.0/nHeight*0.5);
			pShaderAPI->SetPixelShaderConstant( 1, fResolution );

			SetPixelShaderConstant(0, CAMERARANGE);
		
			BindTexture( SHADER_SAMPLER0, DEPTHBUFFER );
			BindTexture( SHADER_SAMPLER1, RANDOMNORMAL );
			BindTexture( SHADER_SAMPLER2, FRAMEBUFFER );

			DECLARE_DYNAMIC_VERTEX_SHADER( passthru_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( passthru_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( ssgi_ps30 );
			SET_DYNAMIC_PIXEL_SHADER( ssgi_ps30 );
		}
		Draw();
	}
END_SHADER