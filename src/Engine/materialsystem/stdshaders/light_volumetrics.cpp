
#include "BaseVSShader.h"
#include "mathlib/vmatrix.h"
#include "convar.h"

#include "light_volumetrics_ps30.inc"
#include "light_volumetrics_vs30.inc"

BEGIN_VS_SHADER( light_volumetrics, "" )

	BEGIN_SHADER_PARAMS

	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
	}

	SHADER_DRAW
	{
		SHADOW_STATE
		{
			// Reset shadow state manually since we're drawing from two materials
			SetInitialShadowState();

			pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );
			pShaderShadow->EnableSRGBRead( SHADER_SAMPLER0, true );
			pShaderShadow->EnableTexture( SHADER_SAMPLER1, true );	// Depth texture
			pShaderShadow->SetShadowDepthFiltering( SHADER_SAMPLER1 );
			pShaderShadow->EnableTexture( SHADER_SAMPLER2, true );
			pShaderShadow->EnableSRGBRead( SHADER_SAMPLER2, false );

			pShaderShadow->EnableSRGBWrite( true );
			pShaderShadow->EnableDepthWrites( false );
			pShaderShadow->EnableCulling( false );

			EnableAlphaBlending( SHADER_BLEND_SRC_ALPHA, SHADER_BLEND_ONE );

			unsigned int flags = VERTEX_POSITION;
			int nTexCoordCount = 1;
			int userDataSize = 0;
			pShaderShadow->VertexShaderVertexFormat( flags, nTexCoordCount, NULL, userDataSize );

			// Vertex Shader
			DECLARE_STATIC_VERTEX_SHADER( light_volumetrics_vs30 );
			SET_STATIC_VERTEX_SHADER( light_volumetrics_vs30 );

			DECLARE_STATIC_PIXEL_SHADER( light_volumetrics_ps30 );
			SET_STATIC_PIXEL_SHADER( light_volumetrics_ps30 );
		}
		DYNAMIC_STATE
		{
			// Reset render state manually since we're drawing from two materials
			pShaderAPI->SetDefaultState();

			VMatrix worldToTexture;
			ITexture *pFlashlightDepthTexture;
			const FlashlightState_t &flashlightState = pShaderAPI->GetFlashlightStateEx(worldToTexture, &pFlashlightDepthTexture);
			pShaderAPI->SetVertexShaderConstant(VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, worldToTexture.Base(), 4);

			bool bUberlight = g_pHardwareConfig->SupportsShaderModel_3_0() && SetupUberlightFromState(flashlightState);

			// Set Vertex Shader Combos
			DECLARE_DYNAMIC_VERTEX_SHADER( light_volumetrics_vs30 );
			SET_DYNAMIC_VERTEX_SHADER_COMBO(UBERLIGHT, bUberlight);
			SET_DYNAMIC_VERTEX_SHADER( light_volumetrics_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( light_volumetrics_ps30 );
			SET_DYNAMIC_PIXEL_SHADER_COMBO(UBERLIGHT, bUberlight);
			SET_DYNAMIC_PIXEL_SHADER( light_volumetrics_ps30 );

			

			BindTexture( SHADER_SAMPLER0, flashlightState.m_pSpotlightTexture, flashlightState.m_nSpotlightTextureFrame );
			BindTexture( SHADER_SAMPLER1, pFlashlightDepthTexture, 0 );
			pShaderAPI->BindStandardTexture( SHADER_SAMPLER2, TEXTURE_FRAME_BUFFER_FULL_TEXTURE_0 );

			//const float flParam0[4] = { XYZ( flashlightState.m_vecLightOrigin ) };
			//pShaderAPI->SetPixelShaderConstant( 0, flParam0 );
			pShaderAPI->SetPixelShaderConstant( 0, flashlightState.m_Color );
			pShaderAPI->SetDepthFeatheringPixelShaderConstant( 1, 50.0f );
		}

		Draw();
	}
END_SHADER
