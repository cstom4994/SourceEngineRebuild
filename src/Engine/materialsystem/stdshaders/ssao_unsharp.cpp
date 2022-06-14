//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "screenspace_simple_vs20.inc"
#include "ssao_unsharp_ps20.inc"
#include "ssao_unsharp_ps20b.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER( SSAO_Unsharp, "Help for SSAO Unsharp" )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
		SHADER_PARAM( FBBLURTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_SSAOFB1", "" )
	END_SHADER_PARAMS

	SHADER_INIT
	{
		if( params[FBTEXTURE]->IsDefined() )
		{
			LoadTexture( FBTEXTURE );
		}

		if( params[FBBLURTEXTURE]->IsDefined() )
		{
			LoadTexture( FBBLURTEXTURE );
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
			pShaderShadow->EnableTexture( SHADER_SAMPLER1, true );
			int fmt = VERTEX_POSITION;
			pShaderShadow->VertexShaderVertexFormat( fmt, 1, 0, 0 );

			// Pre-cache shaders
			DECLARE_STATIC_VERTEX_SHADER( screenspace_simple_vs20 );
			SET_STATIC_VERTEX_SHADER( screenspace_simple_vs20 );

			if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_STATIC_PIXEL_SHADER( ssao_unsharp_ps20b );
				SET_STATIC_PIXEL_SHADER( ssao_unsharp_ps20b );
			}
			else
			{
				DECLARE_STATIC_PIXEL_SHADER( ssao_unsharp_ps20 );
				SET_STATIC_PIXEL_SHADER( ssao_unsharp_ps20 );
			}
		}

		DYNAMIC_STATE
		{	
			BindTexture( SHADER_SAMPLER0, FBTEXTURE, -1 );
			BindTexture( SHADER_SAMPLER1, FBBLURTEXTURE, -1 );
			DECLARE_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs20 );
			SET_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs20 );

			if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER( ssao_unsharp_ps20b );
				SET_DYNAMIC_PIXEL_SHADER( ssao_unsharp_ps20b );
			}
			else
			{
				DECLARE_DYNAMIC_PIXEL_SHADER( ssao_unsharp_ps20 );
				SET_DYNAMIC_PIXEL_SHADER( ssao_unsharp_ps20 );
			}
		}
		Draw();
	}
END_SHADER