
#include "BaseVSShader.h"
#include "mathlib/vmatrix.h"
#include "convar.h"
#include "IDeferredExt.h"

#include "light_volumetrics_ps30.inc"
#include "light_volumetrics_vs30.inc"

extern ConVar r_csm_performance;

BEGIN_VS_SHADER( light_volumetrics, "" )

	BEGIN_SHADER_PARAMS
	SHADER_PARAM(ISCSM, SHADER_PARAM_TYPE_BOOL, "0", "use CSM Light")
	SHADER_PARAM(DEPTHBUFFER, SHADER_PARAM_TYPE_TEXTURE, "_rt_DepthBuffer", "")
	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
		params[DEPTHBUFFER]->SetStringValue("_rt_DepthBuffer");
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
		if (params[DEPTHBUFFER]->IsDefined())
		{
			LoadTexture(DEPTHBUFFER);
		}
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

			// Set Vertex Shader Combos
			DECLARE_DYNAMIC_VERTEX_SHADER( light_volumetrics_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( light_volumetrics_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( light_volumetrics_ps30 );
			SET_DYNAMIC_PIXEL_SHADER_COMBO( CSM, params[ISCSM]->GetIntValue() == 1);
			SET_DYNAMIC_PIXEL_SHADER_COMBO( PERF, MAX(0, MIN(r_csm_performance.GetInt(), 2)));
			SET_DYNAMIC_PIXEL_SHADER( light_volumetrics_ps30 );

			VMatrix worldToTexture;
			ITexture *pFlashlightDepthTexture;
			const FlashlightState_t &flashlightState = pShaderAPI->GetFlashlightStateEx( worldToTexture, &pFlashlightDepthTexture );
			pShaderAPI->SetVertexShaderConstant( VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, worldToTexture.Base(), 4 );

			BindTexture( SHADER_SAMPLER0, flashlightState.m_pSpotlightTexture, flashlightState.m_nSpotlightTextureFrame );
			BindTexture( SHADER_SAMPLER1, pFlashlightDepthTexture, 0 );
			BindTexture( SHADER_SAMPLER2, DEPTHBUFFER);

			//const float flParam0[4] = { XYZ( flashlightState.m_vecLightOrigin ) };
			//pShaderAPI->SetPixelShaderConstant( 0, flParam0 );
			pShaderAPI->SetPixelShaderConstant( 0, flashlightState.m_Color );
			pShaderAPI->SetDepthFeatheringPixelShaderConstant( 1, 50.0f );
			pShaderAPI->SetDepthFeatheringPixelShaderConstant( 2, GetDeferredExt()->GetZDistNear());
			pShaderAPI->SetDepthFeatheringPixelShaderConstant( 3, GetDeferredExt()->GetZDistFar());
			if (params[ISCSM]->GetIntValue() > 0)
			{
				ITexture* pCascadedDepthTexture = (ITexture*)pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_CASCADED_DEPTHTEXTURE);
				if (!pCascadedDepthTexture)
				{
					Draw(false);
					return;
				}

				if (pCascadedDepthTexture)
				{
					BindTexture(SHADER_SAMPLER1, pCascadedDepthTexture, -1);
					VMatrix* worldToTexture0 = (VMatrix*)pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_CASCADED_MATRIX_ADDRESS_0);
					pShaderAPI->SetPixelShaderConstant(6, worldToTexture0->Base(), 4);
				}

				lightData_Global_t csmData = GetDeferredExt()->GetLightData_Global();

				Vector csmLight = csmData.light.AsVector3D();
				pShaderAPI->SetPixelShaderConstant(10, csmLight.Base());

				float textureSize[2] = { pCascadedDepthTexture->GetMappingHeight() * 4.0f, pCascadedDepthTexture->GetMappingHeight() };
				pShaderAPI->SetPixelShaderConstant(11, textureSize);

				pShaderAPI->SetPixelShaderConstant(12, GetDeferredExt()->GetLightData_Global().sizes.Base());
			}
		}

		Draw();
	}
END_SHADER

