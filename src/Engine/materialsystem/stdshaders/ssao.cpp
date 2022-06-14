//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "BaseVSShader.h"

#include "simple_vs30.inc"
#include "ssao_ps30.inc"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_VS_SHADER_FLAGS( SSAO, "Help for SSAO", SHADER_NOT_EDITABLE )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( DEPTHBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_SSAOFB0", "" )
		SHADER_PARAM( RADIUS, SHADER_PARAM_TYPE_FLOAT, "2", "" )
		SHADER_PARAM( STRENGTH, SHADER_PARAM_TYPE_FLOAT, "1", "" )
		SHADER_PARAM( CLAMP, SHADER_PARAM_TYPE_FLOAT, "0.5", "" )
		SHADER_PARAM( THICKNESSMODEL, SHADER_PARAM_TYPE_FLOAT, "100", "" )
		SHADER_PARAM( FOV, SHADER_PARAM_TYPE_FLOAT, "75", "" )
	END_SHADER_PARAMS

	SHADER_INIT
	{
		if( params[DEPTHBUFFER]->IsDefined() )
		{
			LoadTexture( DEPTHBUFFER );
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

			DECLARE_STATIC_PIXEL_SHADER( ssao_ps30 );
			SET_STATIC_PIXEL_SHADER( ssao_ps30 );
		}

		DYNAMIC_STATE
		{
			float g_const0[4] = { params[RADIUS]->GetFloatValue(), 0.0f, 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 0, g_const0 );

			float g_const1[4] = { params[STRENGTH]->GetFloatValue(), 0.0f, 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 1, g_const1 );

			float g_const2[4] = { params[CLAMP]->GetFloatValue(), 0.0f, 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 2, g_const2 );

			float g_const3[4] = { params[THICKNESSMODEL]->GetFloatValue(), 0.0f, 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 3, g_const3 );

			float g_const4[4] = { params[FOV]->GetFloatValue(), 0.0f, 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 4, g_const4 );

			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions( nWidth, nHeight );
			float g_const5[4] = { float(nWidth), float(nHeight), 0.0f, 0.0f };
			pShaderAPI->SetPixelShaderConstant( 5, g_const5 );

			float zDeltaFar = pShaderAPI->GetFloatRenderingParameter( FLOAT_RENDERPARM_FARZ );
			float zDeltaNear = pShaderAPI->GetFloatRenderingParameter( FLOAT_RENDERPARM_NEARZ );
			float depthrange[2] = {zDeltaNear, zDeltaFar};
			pShaderAPI->SetPixelShaderConstant( 6, depthrange );

			BindTexture( SHADER_SAMPLER0, DEPTHBUFFER );

			DECLARE_DYNAMIC_VERTEX_SHADER( simple_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( simple_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( ssao_ps30 );
			SET_DYNAMIC_PIXEL_SHADER( ssao_ps30 );
		}
		Draw();
	}
END_SHADER