//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $Header: $
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "pp_fog_vs20.inc"
#include "pp_fog_ps20.inc"
#include "pp_fog_ps20b.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER( PP_Fog, "Help for PP_Fog" )
	BEGIN_SHADER_PARAMS

	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
		SET_FLAGS2( MATERIAL_VAR2_SUPPORTS_HW_SKINNING );
	}

	SHADER_INIT
	{
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	
	SHADER_DRAW
	{
		SHADOW_STATE
		{
			// Set stream format (note that this shader supports compression)
			unsigned int flags = VERTEX_POSITION;
			int nTexCoordCount = 1;
			int userDataSize = 0;
			pShaderShadow->VertexShaderVertexFormat( flags, nTexCoordCount, NULL, userDataSize );

			DECLARE_STATIC_VERTEX_SHADER(pp_fog_vs20 );
			SET_STATIC_VERTEX_SHADER(pp_fog_vs20 );

			if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_STATIC_PIXEL_SHADER(pp_fog_ps20b );
				SET_STATIC_PIXEL_SHADER(pp_fog_ps20b );
			}
			else
			{
				DECLARE_STATIC_PIXEL_SHADER(pp_fog_ps20 );
				SET_STATIC_PIXEL_SHADER(pp_fog_ps20 );
			}

			pShaderShadow->EnableSRGBWrite(true);

			FogToFogColor();
		}
		DYNAMIC_STATE
		{
			DECLARE_DYNAMIC_VERTEX_SHADER(pp_fog_vs20);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, pShaderAPI->GetCurrentNumBones() > 0 );
			SET_DYNAMIC_VERTEX_SHADER(pp_fog_vs20);

			if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER(pp_fog_ps20b);
				SET_DYNAMIC_PIXEL_SHADER(pp_fog_ps20b);
			}
			else
			{
				DECLARE_DYNAMIC_PIXEL_SHADER(pp_fog_ps20);
				SET_DYNAMIC_PIXEL_SHADER(pp_fog_ps20);
			}
		}
		Draw();
	}
END_SHADER


