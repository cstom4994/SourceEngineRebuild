//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "../BaseVSShader.h"

#include "SDK_screenspaceeffect_vs30.inc"
#include "vance_bloom_combine_ps30.inc"

BEGIN_VS_SHADER_FLAGS( Bloom_Combine, "Help for Bloom", SHADER_NOT_EDITABLE )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
		SHADER_PARAM( BLOOMTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_BloomDS0", "")
		SHADER_PARAM( BLOOMTEXTURE1, SHADER_PARAM_TYPE_TEXTURE, "_rt_BloomDS1", "")
		SHADER_PARAM( BLOOMTEXTURE2, SHADER_PARAM_TYPE_TEXTURE, "_rt_BloomDS2", "")
		SHADER_PARAM( BLOOMTEXTURE3, SHADER_PARAM_TYPE_TEXTURE, "_rt_BloomDS3", "")
		SHADER_PARAM( AMOUNT, SHADER_PARAM_TYPE_FLOAT, "1", "")
	END_SHADER_PARAMS

	SHADER_INIT
	{
		if( params[FBTEXTURE]->IsDefined() )
		{
			LoadTexture( FBTEXTURE );
		}
		if (params[BLOOMTEXTURE]->IsDefined())
		{
			LoadTexture(BLOOMTEXTURE);
		}
		if (params[BLOOMTEXTURE1]->IsDefined())
		{
			LoadTexture(BLOOMTEXTURE1);
		}
		if (params[BLOOMTEXTURE2]->IsDefined())
		{
			LoadTexture(BLOOMTEXTURE2);
		}
		if (params[BLOOMTEXTURE3]->IsDefined())
		{
			LoadTexture(BLOOMTEXTURE3);
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
			pShaderShadow->EnableTexture( SHADER_SAMPLER2, true);
			pShaderShadow->EnableTexture( SHADER_SAMPLER3, true);
			pShaderShadow->EnableTexture( SHADER_SAMPLER4, true);
			int fmt = VERTEX_POSITION;
			pShaderShadow->VertexShaderVertexFormat( fmt, 1, 0, 0 );

			// Pre-cache shaders
			DECLARE_STATIC_VERTEX_SHADER( sdk_screenspaceeffect_vs30 );
			SET_STATIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);

			//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_STATIC_PIXEL_SHADER(vance_bloom_combine_ps30);
				SET_STATIC_PIXEL_SHADER(vance_bloom_combine_ps30);
			}
		}

		DYNAMIC_STATE
		{
			BindTexture( SHADER_SAMPLER0, FBTEXTURE, -1 );
			BindTexture( SHADER_SAMPLER1, BLOOMTEXTURE, -1);
			BindTexture( SHADER_SAMPLER2, BLOOMTEXTURE1, -1);
			BindTexture( SHADER_SAMPLER3, BLOOMTEXTURE2, -1);
			BindTexture( SHADER_SAMPLER4, BLOOMTEXTURE3, -1);

			float fBlurSize[4];
			fBlurSize[0] = params[AMOUNT]->GetFloatValue();
			fBlurSize[1] = fBlurSize[2] = fBlurSize[3] = fBlurSize[0];
			pShaderAPI->SetPixelShaderConstant(0, fBlurSize);

			DECLARE_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);
			SET_DYNAMIC_VERTEX_SHADER(sdk_screenspaceeffect_vs30);

			//if( g_pHardwareConfig->SupportsPixelShaders_2_b() )
			{
				DECLARE_DYNAMIC_PIXEL_SHADER(vance_bloom_combine_ps30);
				SET_DYNAMIC_PIXEL_SHADER(vance_bloom_combine_ps30);
			}
		}
		Draw();
	}
END_SHADER
