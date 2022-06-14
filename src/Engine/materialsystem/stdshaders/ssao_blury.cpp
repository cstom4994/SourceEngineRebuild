//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "ssao_blury_vs20.inc"
#include "ssao_blury_ps20.inc"
#include "ssao_blury_ps20b.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER( SSAO_BlurY, "Help for SSAO Blur Y" )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_SSAO", "" )
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
			DECLARE_STATIC_VERTEX_SHADER( ssao_blury_vs20 );
			SET_STATIC_VERTEX_SHADER( ssao_blury_vs20 );

			if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_STATIC_PIXEL_SHADER( ssao_blury_ps20b );
				SET_STATIC_PIXEL_SHADER( ssao_blury_ps20b );
			}
			else
			{
				DECLARE_STATIC_PIXEL_SHADER( ssao_blury_ps20 );
				SET_STATIC_PIXEL_SHADER( ssao_blury_ps20 );
			}
		}

		DYNAMIC_STATE
		{
			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions( nWidth, nHeight );

			float fResolution;
			if( params[RESDIVISOR]->GetIntValue() == 1 || params[RESDIVISOR]->GetIntValue() == 0 )
			{
				fResolution = float(nHeight);
			}
			else
			{
				fResolution = float(nHeight/params[RESDIVISOR]->GetIntValue());
			}
			float const0[4]={fResolution,0,0,0}; //Window Size
			pShaderAPI->SetVertexShaderConstant( VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, const0 );

			float const1[4]={ params[BLURSIZE]->GetFloatValue(),0,0,0}; //Blur Size
			pShaderAPI->SetVertexShaderConstant( VERTEX_SHADER_SHADER_SPECIFIC_CONST_1, const1 );

			BindTexture( SHADER_SAMPLER0, FBTEXTURE, -1 );
			DECLARE_DYNAMIC_VERTEX_SHADER( ssao_blury_vs20 );
			SET_DYNAMIC_VERTEX_SHADER( ssao_blury_vs20 );

			if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER( ssao_blury_ps20b );
				SET_DYNAMIC_PIXEL_SHADER( ssao_blury_ps20b );
			}
			else
			{
				DECLARE_DYNAMIC_PIXEL_SHADER( ssao_blury_ps20 );
				SET_DYNAMIC_PIXEL_SHADER( ssao_blury_ps20 );
			}
		}
		Draw();
	}
END_SHADER