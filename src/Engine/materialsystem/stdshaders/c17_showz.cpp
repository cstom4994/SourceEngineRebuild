//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "SDK_screenspaceeffect_vs20.inc"
#include "c17_showz_ps20.inc"
#include "c17_showz_ps20b.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER( C17_ShowZ, "Help for C17 ShowZ" )
	BEGIN_SHADER_PARAMS
		//SHADER_PARAM( DEPTHTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameDepth_Alt", "" )
	END_SHADER_PARAMS

	SHADER_INIT
	{
		if( params[BASETEXTURE]->IsDefined() )
		{
			LoadTexture( BASETEXTURE );
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
			DECLARE_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs20);
			SET_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs20);

			DECLARE_STATIC_PIXEL_SHADER(c17_showz_ps20);
			SET_STATIC_PIXEL_SHADER(c17_showz_ps20);
		}

		DYNAMIC_STATE
		{
			BindTexture( SHADER_SAMPLER0, BASETEXTURE, -1 );
			DECLARE_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs20);
			SET_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs20);

			DECLARE_DYNAMIC_PIXEL_SHADER(c17_showz_ps20);
			SET_DYNAMIC_PIXEL_SHADER(c17_showz_ps20);
		}
		Draw();
	}
END_SHADER