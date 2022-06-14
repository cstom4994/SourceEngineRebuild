//===== Copyright � 2011, GearDev Software, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//=====================================================================//

#include "BaseVSShader.h"

#include "screenspace_simple_vs30.inc"
#include "luma_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER_FLAGS( LUMA, "Help for luma", SHADER_NOT_EDITABLE )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( FRAMEBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
	END_SHADER_PARAMS
	SHADER_INIT_PARAMS()
	{
	}

	SHADER_INIT
	{
		if( params[FRAMEBUFFER]->IsDefined() )
		{
			LoadTexture( FRAMEBUFFER );
		}
	}
	
	SHADER_FALLBACK
	{
		// Requires DX9 + above
		// But for some reason some GPUs dont support the SM3 but they clearly do, probably a bug
		/*if ( g_pHardwareConfig->GetDXSupportLevel() < 90 || !g_pHardwareConfig->SupportsShaderModel_3_0() )
		{
			Assert( 0 );
			return "Wireframe";
		}*/
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

			pShaderShadow->EnableColorWrites( false );
			pShaderShadow->EnableAlphaWrites( true );

			DECLARE_STATIC_VERTEX_SHADER( screenspace_simple_vs30 );
			SET_STATIC_VERTEX_SHADER( screenspace_simple_vs30 );

			DECLARE_STATIC_PIXEL_SHADER( luma_ps30 );
			SET_STATIC_PIXEL_SHADER( luma_ps30 );
		}

		DYNAMIC_STATE
		{
			BindTexture( SHADER_SAMPLER0, FRAMEBUFFER );

			DECLARE_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( screenspace_simple_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( luma_ps30 );
			SET_DYNAMIC_PIXEL_SHADER( luma_ps30 );
		}
		Draw();
	}
END_SHADER