//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "simple_vs30.inc"
#include "ssao_blur_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER_FLAGS( SSAO_Blur, "Help for SSAO Blur", SHADER_NOT_EDITABLE )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( SSAOBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_SSAOFB1", "" )
	END_SHADER_PARAMS

	SHADER_INIT
	{
		if( params[SSAOBUFFER]->IsDefined() )
		{
			LoadTexture( SSAOBUFFER );
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

			DECLARE_STATIC_VERTEX_SHADER( simple_vs30 );
			SET_STATIC_VERTEX_SHADER( simple_vs30 );

			DECLARE_STATIC_PIXEL_SHADER( ssao_blur_ps30 );
			SET_STATIC_PIXEL_SHADER( ssao_blur_ps30 );
		}

		DYNAMIC_STATE
		{
			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions( nWidth, nHeight );
			float g_const0[4] = { float(nWidth), float(nHeight), 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 0, g_const0 );

			BindTexture( SHADER_SAMPLER0, SSAOBUFFER );

			DECLARE_DYNAMIC_VERTEX_SHADER( simple_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( simple_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( ssao_blur_ps30 );
			SET_DYNAMIC_PIXEL_SHADER( ssao_blur_ps30 );
		}
		Draw();
	}
END_SHADER