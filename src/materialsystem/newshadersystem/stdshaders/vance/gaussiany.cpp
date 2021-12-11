//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "screenspace_simple_vs30.inc"
#include "gaussiany_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER( GaussianY, "Help for Gaussian Y" )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
		SHADER_PARAM( BLURSIZE, SHADER_PARAM_TYPE_FLOAT, "1.0", "" )
		SHADER_PARAM( RESDIVISOR, SHADER_PARAM_TYPE_INTEGER, "1", "" )
	END_SHADER_PARAMS

	SHADER_INIT
	{
		if( params[FBTEXTURE]->IsDefined() )
		{
			LoadTexture( FBTEXTURE );
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
			int fmt = VERTEX_POSITION;
			pShaderShadow->VertexShaderVertexFormat( fmt, 1, 0, 0 );

			// Pre-cache shaders
			DECLARE_STATIC_VERTEX_SHADER( screenspace_simple_vs30 );
			SET_STATIC_VERTEX_SHADER( screenspace_simple_vs30 );

			//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_STATIC_PIXEL_SHADER( gaussiany_ps30 );
				SET_STATIC_PIXEL_SHADER( gaussiany_ps30 );
			}
		}

		DYNAMIC_STATE
		{
			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions( nWidth, nHeight );

			float fBlurSize[4];
			if( params[RESDIVISOR]->GetIntValue() == 1 || params[RESDIVISOR]->GetIntValue() == 0 )
			{
				fBlurSize[0] = params[BLURSIZE]->GetFloatValue()/float(nHeight);
			}
			else
			{
				fBlurSize[0] = params[BLURSIZE]->GetFloatValue()/float(nHeight/params[RESDIVISOR]->GetIntValue());
			}
			fBlurSize[1] = fBlurSize[2] = fBlurSize[3] = fBlurSize[0];
			pShaderAPI->SetPixelShaderConstant( 0, fBlurSize );

			if (FBTEXTURE != -1 && params[FBTEXTURE]->IsDefined())
			{
				BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);
			}
			else
			{
				BindTexture(SHADER_SAMPLER0, pShaderAPI->GetRenderTargetEx(0));
			}
			DECLARE_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs30 );

			//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER( gaussiany_ps30 );
				SET_DYNAMIC_PIXEL_SHADER( gaussiany_ps30 );
			}
		}
		Draw();
	}
END_SHADER