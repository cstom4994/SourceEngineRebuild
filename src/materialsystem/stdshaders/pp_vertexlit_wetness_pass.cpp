#include "BaseVSShader.h"
#include "pp_vertexlit_wetness_pass.h"
#include "commandbuilder.h"
#include "cpp_shader_constant_register_map.h"
#include "gstring_lighting_helper.h"

#include "pp_vertexlit_wetness_ps30.inc"
#include "pp_vertexlit_wetness_vs30.inc"
#include "pp_vertexlit_wetness_ps20b.inc"
#include "pp_vertexlit_wetness_vs20.inc"

static ConVar r_rimlight("r_rimlight", "1", FCVAR_NONE);

void InitParamsVertexLitWetness_DX9(CBaseVSShader* pShader, IMaterialVar** params, const char* pMaterialName, VertexLitWetness_DX9_Vars_t& info)
{
	// FLASHLIGHTFIXME: Do ShaderAPI::BindFlashlightTexture
	Assert(info.m_nFlashlightTexture >= 0);

	if (g_pHardwareConfig->SupportsBorderColor())
	{
		params[FLASHLIGHTTEXTURE]->SetStringValue("effects/flashlight_border");
	}
	else
	{
		params[FLASHLIGHTTEXTURE]->SetStringValue("effects/flashlight001");
	}

	// This shader can be used with hw skinning
	SET_FLAGS2(MATERIAL_VAR2_SUPPORTS_HW_SKINNING);
	SET_FLAGS2(MATERIAL_VAR2_LIGHTING_VERTEX_LIT);

	// No texture means no env mask in base alpha
	if (!params[info.m_nWetBaseTexture]->IsDefined())
	{
		CLEAR_FLAGS(MATERIAL_VAR_BASEALPHAENVMAPMASK);
	}

	// If in decal mode, no debug override...
	if (IS_FLAG_SET(MATERIAL_VAR_DECAL))
	{
		SET_FLAGS(MATERIAL_VAR_NO_DEBUG_OVERRIDE);
	}

	if (true)
	{
		SET_FLAGS2(MATERIAL_VAR2_NEEDS_TANGENT_SPACES);
	}
	else
	{
		CLEAR_FLAGS(MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK);
	}

	if ((info.m_nWetBaseMapAlphaPhongMask != -1) && (!params[info.m_nWetBaseMapAlphaPhongMask]->IsDefined()))
	{
		params[info.m_nWetBaseMapAlphaPhongMask]->SetIntValue(0);
	}
}

void InitVertexLitWetness_DX9(CBaseVSShader* pShader, IMaterialVar** params, VertexLitWetness_DX9_Vars_t& info)
{
	Assert(info.m_nFlashlightTexture >= 0);
	pShader->LoadTexture(info.m_nFlashlightTexture, TEXTUREFLAGS_SRGB);

	bool bIsBaseTextureTranslucent = false;
	if (params[info.m_nWetBaseTexture]->IsDefined())
	{
		pShader->LoadTexture(info.m_nWetBaseTexture, TEXTUREFLAGS_SRGB);

		if (params[info.m_nWetBaseTexture]->GetTextureValue()->IsTranslucent())
		{
			bIsBaseTextureTranslucent = true;
		}
	}

	// No alpha channel in any of the textures? No self illum or envmapmask
	if (!bIsBaseTextureTranslucent)
	{
		CLEAR_FLAGS(MATERIAL_VAR_BASEALPHAENVMAPMASK);
	}

	if ((info.m_nWetPhongExponentTexture != -1) && params[info.m_nWetPhongExponentTexture]->IsDefined() )
	{
		pShader->LoadTexture(info.m_nWetPhongExponentTexture);
	}

	if ((info.m_nWetPhongWarpTexture != -1) && params[info.m_nWetPhongWarpTexture]->IsDefined())
	{
		pShader->LoadTexture(info.m_nWetPhongWarpTexture);
	}

	if (g_pConfig->UseBumpmapping())
	{
		if ((info.m_nWetBumpmap != -1) && params[info.m_nWetBumpmap]->IsDefined())
		{
			pShader->LoadBumpMap(info.m_nWetBumpmap);
			SET_FLAGS2(MATERIAL_VAR2_DIFFUSE_BUMPMAPPED_MODEL);

			if ((info.m_nWetNormalWrinkle != -1) && (info.m_nWetNormalStretch != -1) &&
				params[info.m_nWetNormalWrinkle]->IsDefined() && params[info.m_nWetNormalStretch]->IsDefined())
			{
				pShader->LoadTexture(info.m_nWetNormalWrinkle);
				pShader->LoadTexture(info.m_nWetNormalStretch);
			}
		}
	}
}

void DrawVertexLitWetness_DX9(CBaseVSShader* pShader, IMaterialVar** params, IShaderDynamicAPI* pShaderAPI, IShaderShadow* pShaderShadow, VertexLitWetness_DX9_Vars_t& info, VertexCompressionType_t vertexCompression, bool bForceFlashlight)
{
	bool bHasFlashlight = pShader->UsingFlashlight(params);
	bool bHasBaseTexture = (info.m_nWetBaseTexture != -1) && params[info.m_nWetBaseTexture]->IsTexture();
	bool bHasBump = (info.m_nWetBumpmap != -1) && params[info.m_nWetBumpmap]->IsTexture();

	bool bHasBumpWrinkle = bHasBump &&
		(info.m_nWetNormalWrinkle != -1) && params[info.m_nWetNormalWrinkle]->IsTexture() &&
		(info.m_nWetNormalStretch != -1) && params[info.m_nWetNormalStretch]->IsTexture();

	// Tie these to specular
	bool bHasPhong = true;
	bool bHasSpecularExponentTexture = (info.m_nWetPhongExponentTexture != -1) && params[info.m_nWetPhongExponentTexture]->IsTexture();
	bool bHasPhongTintMap = bHasSpecularExponentTexture && (info.m_nWetPhongAlbedoTint != -1) && (params[info.m_nWetPhongAlbedoTint]->GetIntValue() != 0);
	bool bHasPhongWarp = (info.m_nWetPhongWarpTexture != -1) && params[info.m_nWetPhongWarpTexture]->IsTexture();
	//bool bHasNormalMapAlphaEnvmapMask = IS_FLAG_SET(MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK);

	bool bHasRimLight = r_rimlight.GetBool() && bHasPhong && (info.m_nWetRimLight != -1) && (params[info.m_nWetRimLight]->GetIntValue() != 0);
	bool bHasRimMaskMap = bHasSpecularExponentTexture && bHasRimLight && (info.m_nWetRimMask != -1) && (params[info.m_nWetRimMask]->GetIntValue() != 0);

	float flPhongExponentFactor = (info.m_nWetPhongExponentFactor != -1) ? GetFloatParam(info.m_nWetPhongExponentFactor, params) : 0.0f;
	const bool bHasPhongExponentFactor = flPhongExponentFactor != 0.0f;

	if (pShaderShadow)
	{
		int nShadowFilterMode = g_pHardwareConfig->GetShadowFilterMode();
		if (bHasFlashlight)
		{
			if (params[info.m_nWetBaseTexture]->IsTexture())
			{
				pShader->SetAdditiveBlendingShadowState(info.m_nWetBaseTexture, true);
			}

			pShaderShadow->EnableBlending(true);
			pShaderShadow->EnableDepthWrites(false);

			// Be sure not to write to dest alpha
			pShaderShadow->EnableAlphaWrites(false);
		}
		else // not flashlight pass
		{
			if (params[info.m_nWetBaseTexture]->IsTexture())
			{
				pShader->SetAdditiveBlendingShadowState(info.m_nWetBaseTexture, true);
			}
		}

		unsigned int flags = VERTEX_POSITION;
		if (bHasBump)
		{
			flags |= VERTEX_NORMAL;
		}

		int userDataSize = 0;

		// Always enable...will bind white if nothing specified...
		pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);		// Base (albedo) map
		pShaderShadow->EnableSRGBRead(SHADER_SAMPLER0, true);

		if (bHasPhongWarp)
		{
			pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);	// Specular warp texture
		}

		// Specular exponent map or dummy
		pShaderShadow->EnableTexture(SHADER_SAMPLER7, true);	// Specular exponent map

		if (bHasFlashlight)
		{
			pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);	// Shadow depth map
			pShaderShadow->SetShadowDepthFiltering(SHADER_SAMPLER4);
			pShaderShadow->EnableSRGBRead(SHADER_SAMPLER4, false);
			pShaderShadow->EnableTexture(SHADER_SAMPLER6, true);	// Flashlight cookie
			pShaderShadow->EnableSRGBRead(SHADER_SAMPLER6, true);
		}
		else
		{
			pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);	// Shadow depth map
			pShaderShadow->SetShadowDepthFiltering(SHADER_SAMPLER4);
			pShaderShadow->EnableSRGBRead(SHADER_SAMPLER4, false);
		}

		if (bHasBumpWrinkle)
		{
			pShaderShadow->EnableTexture(SHADER_SAMPLER11, true);
			pShaderShadow->EnableTexture(SHADER_SAMPLER12, true);
		}

		// Always enable, since flat normal will be bound
		pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);		// Normal map
		userDataSize = 4; // tangent S
		pShaderShadow->EnableTexture(SHADER_SAMPLER5, true);		// Normalizing cube map

		pShaderShadow->EnableSRGBWrite(true);

		// texcoord0 : base texcoord, texcoord2 : decal hw morph delta
		int pTexCoordDim[3] = { 2, 0, 3 };
		int nTexCoordCount = 1;

#ifndef _X360
		// Special morphed decal information 
		/*if (bIsDecal && g_pHardwareConfig->HasFastVertexTextures())
		{
			nTexCoordCount = 3;
		}*/
#endif

		// This shader supports compressed vertices, so OR in that flag:
		flags |= VERTEX_FORMAT_COMPRESSED;

		pShaderShadow->VertexShaderVertexFormat(flags, nTexCoordCount, pTexCoordDim, userDataSize);

		if (!g_pHardwareConfig->SupportsShaderModel_3_0())
		{
			bool bUseStaticControlFlow = g_pHardwareConfig->SupportsStaticControlFlow();

			DECLARE_STATIC_VERTEX_SHADER(pp_vertexlit_wetness_vs20);
			SET_STATIC_VERTEX_SHADER_COMBO(USE_STATIC_CONTROL_FLOW, bUseStaticControlFlow);
			SET_STATIC_VERTEX_SHADER_COMBO(FLASHLIGHT, bHasFlashlight);
			SET_STATIC_VERTEX_SHADER(pp_vertexlit_wetness_vs20);

			// Assume we're only going to get in here if we support 2b
			DECLARE_STATIC_PIXEL_SHADER(pp_vertexlit_wetness_ps20b);
			SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHT, bHasFlashlight);
			SET_STATIC_PIXEL_SHADER_COMBO(PHONGWARPTEXTURE, bHasPhongWarp && bHasPhong);
			SET_STATIC_PIXEL_SHADER_COMBO(WRINKLEMAP, bHasBumpWrinkle);
			SET_STATIC_PIXEL_SHADER_COMBO(RIMLIGHT, bHasRimLight);
			SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHTDEPTHFILTERMODE, nShadowFilterMode);
			SET_STATIC_PIXEL_SHADER_COMBO(CONVERT_TO_SRGB, 0);
			SET_STATIC_PIXEL_SHADER(pp_vertexlit_wetness_ps20b);
		}
		else
		{
			const bool bFastVertexTextures = g_pHardwareConfig->HasFastVertexTextures();

			// The vertex shader uses the vertex id stream
			if (bFastVertexTextures)
				SET_FLAGS2(MATERIAL_VAR2_USES_VERTEXID);

			DECLARE_STATIC_VERTEX_SHADER(pp_vertexlit_wetness_vs30);
			SET_STATIC_VERTEX_SHADER_COMBO(FLASHLIGHT, bHasFlashlight);
			SET_STATIC_VERTEX_SHADER(pp_vertexlit_wetness_vs30);

			DECLARE_STATIC_PIXEL_SHADER(pp_vertexlit_wetness_ps30);
			SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHT, bHasFlashlight);
			SET_STATIC_PIXEL_SHADER_COMBO(PHONGWARPTEXTURE, bHasPhongWarp&& bHasPhong);
			SET_STATIC_PIXEL_SHADER_COMBO(WRINKLEMAP, bHasBumpWrinkle);
			SET_STATIC_PIXEL_SHADER_COMBO(RIMLIGHT, bHasRimLight);
			SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHTDEPTHFILTERMODE, nShadowFilterMode);
			SET_STATIC_PIXEL_SHADER_COMBO(CONVERT_TO_SRGB, 0);
			SET_STATIC_PIXEL_SHADER(pp_vertexlit_wetness_ps30);
		}

		pShaderShadow->EnableAlphaWrites(false);
	}

	if (pShaderAPI)
	{
		static CCommandBufferBuilder< CFixedCommandStorageBuffer< 2000 > > DynamicCmdsOut;
		DynamicCmdsOut.Reset();

		if (bHasBaseTexture)
		{
			DynamicCmdsOut.BindTexture(pShader, SHADER_SAMPLER0, info.m_nWetBaseTexture, info.m_nWetBaseTextureFrame);
		}
		else
		{
			DynamicCmdsOut.BindStandardTexture(SHADER_SAMPLER0, TEXTURE_WHITE);
		}

		if (bHasPhongWarp)
		{
			DynamicCmdsOut.BindTexture(pShader, SHADER_SAMPLER1, info.m_nWetPhongWarpTexture);
		}

		if (bHasSpecularExponentTexture && bHasPhong)
		{
			DynamicCmdsOut.BindTexture(pShader, SHADER_SAMPLER7, info.m_nWetPhongExponentTexture);
		}
		else
		{
			DynamicCmdsOut.BindStandardTexture(SHADER_SAMPLER7, TEXTURE_WHITE);
		}

		if (bHasBump)
			DynamicCmdsOut.BindTexture(pShader, SHADER_SAMPLER3, info.m_nWetBumpmap, info.m_nWetBumpFrame);
		else
			DynamicCmdsOut.BindStandardTexture(SHADER_SAMPLER3, TEXTURE_NORMALMAP_FLAT);

		if (bHasBumpWrinkle)
		{
			DynamicCmdsOut.BindTexture(pShader, SHADER_SAMPLER11, info.m_nWetNormalWrinkle, info.m_nWetBumpFrame);
			DynamicCmdsOut.BindTexture(pShader, SHADER_SAMPLER12, info.m_nWetNormalStretch, info.m_nWetBumpFrame);
		}

		float vRimBoost[4] = { 1, 1, 1, 1 };
		ITexture* pCascadedDepthTexture = NULL;
		LightState_t lightState = { 0, false, false, false };
		bool bFlashlightShadows = false;
		bool bUberlight = false;
		if (bHasFlashlight)
		{
			VMatrix worldToTexture;
			ITexture* pFlashlightDepthTexture;
			const FlashlightState_t& flashlightState = pShaderAPI->GetFlashlightStateEx(worldToTexture, &pFlashlightDepthTexture);
			bFlashlightShadows = flashlightState.m_bEnableShadows;

			bUberlight = g_pHardwareConfig->SupportsShaderModel_3_0() && DynamicCmdsOut.SetupUberlightFromState(flashlightState);

			if (pFlashlightDepthTexture && g_pConfig->ShadowDepthTexture() && flashlightState.m_bEnableShadows)
			{
				DynamicCmdsOut.BindTexture(SHADER_SAMPLER4, pFlashlightDepthTexture, 0);
				DynamicCmdsOut.BindStandardTexture(SHADER_SAMPLER5, TEXTURE_SHADOW_NOISE_2D);
			}
		}
		else // no flashlight
		{
			pShaderAPI->GetDX9LightState(&lightState);

			pCascadedDepthTexture = (ITexture*)pShaderAPI->GetIntRenderingParameter(INT_CASCADED_DEPTHTEXTURE);
			if (pCascadedDepthTexture != NULL)
			{
				pShader->BindTexture(SHADER_SAMPLER4, pCascadedDepthTexture);

				VMatrix* worldToTexture0 = (VMatrix*)pShaderAPI->GetIntRenderingParameter(INT_CASCADED_MATRIX_ADDRESS_0);
				DynamicCmdsOut.SetVertexShaderConstant(VERTEX_SHADER_SHADER_SPECIFIC_CONST_6, worldToTexture0->Base(), 4);

				const Vector& vecCascadedFwd = pShaderAPI->GetVectorRenderingParameter(VECTOR_RENDERPARM_GSTRING_CASCADED_FORWARD);
				vRimBoost[0] = vecCascadedFwd.x;
				vRimBoost[1] = vecCascadedFwd.y;
				vRimBoost[2] = vecCascadedFwd.z;

				float vScreenScale[4] = { 1280.0f / 32.0f, 720.0f / 32.0f, 0, 0 };
				int nWidth, nHeight;
				pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
				vScreenScale[0] = (float)nWidth / 32.0f;
				vScreenScale[1] = (float)nHeight / 32.0f;
				DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_SCREEN_SCALE, vScreenScale, 1);

				// We have to rebuild the lighting state by hand. Fading static lights are out of order!
				float vDirectionalLights[4] = { 0.0f };
				SetCustomPixelLightingState(DynamicCmdsOut, lightState, pShaderAPI, PSREG_LIGHT_INFO_ARRAY);
				SetCustomVertexLightingState(DynamicCmdsOut, lightState, pShaderAPI, 27, vDirectionalLights);
				DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_COLOR, vDirectionalLights);

				const Vector vecCascadedStep = pShaderAPI->GetVectorRenderingParameter(VECTOR_RENDERPARM_GSTRING_CASCADED_STEP);
				float vCascadedStep[4] = { XYZ(vecCascadedStep) };
				DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_TO_WORLD_TEXTURE, vCascadedStep, 1);
			}
		}

		if (pCascadedDepthTexture == NULL)
		{
			DynamicCmdsOut.CommitPixelShaderLighting(PSREG_LIGHT_INFO_ARRAY);
		}

		MaterialFogMode_t fogType = pShaderAPI->GetSceneFogMode();
		int fogIndex = (fogType == MATERIAL_FOG_LINEAR_BELOW_FOG_Z) ? 1 : 0;
		int numBones = pShaderAPI->GetCurrentNumBones();

		if (!g_pHardwareConfig->SupportsShaderModel_3_0())
		{
			bool bUseStaticControlFlow = g_pHardwareConfig->SupportsStaticControlFlow();

			DECLARE_DYNAMIC_VERTEX_SHADER(pp_vertexlit_wetness_vs20);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(DOWATERFOG, fogIndex);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, numBones > 0);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, (int)vertexCompression);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(NUM_LIGHTS, bUseStaticControlFlow ? 0 : lightState.m_nNumLights);
			SET_DYNAMIC_VERTEX_SHADER_CMD(DynamicCmdsOut, pp_vertexlit_wetness_vs20);

			DECLARE_DYNAMIC_PIXEL_SHADER(pp_vertexlit_wetness_ps20b);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(NUM_LIGHTS, lightState.m_nNumLights);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(PIXELFOGTYPE, pShaderAPI->GetPixelFogCombo());
			SET_DYNAMIC_PIXEL_SHADER_COMBO(FLASHLIGHTSHADOWS, bFlashlightShadows);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(PHONG_USE_EXPONENT_FACTOR, bHasPhongExponentFactor);
			SET_DYNAMIC_PIXEL_SHADER_CMD(DynamicCmdsOut, pp_vertexlit_wetness_ps20b);
		}
		else
		{
			const bool bFastVertexTextures = g_pHardwareConfig->HasFastVertexTextures();
			const int iCascadedShadowCombo = (pCascadedDepthTexture != NULL) ? 1 : 0;

			if (bFastVertexTextures)
				pShader->SetHWMorphVertexShaderState(VERTEX_SHADER_SHADER_SPECIFIC_CONST_6, VERTEX_SHADER_SHADER_SPECIFIC_CONST_7, SHADER_VERTEXTEXTURE_SAMPLER0);

			DECLARE_DYNAMIC_VERTEX_SHADER(pp_vertexlit_wetness_vs30);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(DOWATERFOG, fogIndex);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, numBones > 0);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(MORPHING, bFastVertexTextures && pShaderAPI->IsHWMorphingEnabled());
			SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, (int)vertexCompression);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(CASCADED_SHADOW, iCascadedShadowCombo);
			SET_DYNAMIC_VERTEX_SHADER_CMD(DynamicCmdsOut, pp_vertexlit_wetness_vs30);

			DECLARE_DYNAMIC_PIXEL_SHADER(pp_vertexlit_wetness_ps30);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(NUM_LIGHTS, lightState.m_nNumLights);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(PIXELFOGTYPE, pShaderAPI->GetPixelFogCombo());
			SET_DYNAMIC_PIXEL_SHADER_COMBO(FLASHLIGHTSHADOWS, bFlashlightShadows);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(PHONG_USE_EXPONENT_FACTOR, bHasPhongExponentFactor);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(CASCADED_SHADOW, iCascadedShadowCombo);
			SET_DYNAMIC_PIXEL_SHADER_COMBO(UBERLIGHT, bUberlight);
			SET_DYNAMIC_PIXEL_SHADER_CMD(DynamicCmdsOut, pp_vertexlit_wetness_ps30);

			if (bFastVertexTextures)
			{
				bool bUnusedTexCoords[3] = { false, false, !pShaderAPI->IsHWMorphingEnabled() || false };
				pShaderAPI->MarkUnusedVertexFields(0, 3, bUnusedTexCoords);
			}
		}

		DynamicCmdsOut.SetVertexShaderTextureTransform(VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, info.m_nWetBaseTextureTransform);


		bool bInvertPhongMask = (info.m_nWetInvertPhongMask != -1) && (params[info.m_nWetInvertPhongMask]->GetIntValue() != 0);
		float fInvertPhongMask = bInvertPhongMask ? 1 : 0;

		bool bHasBaseAlphaPhongMask = (info.m_nWetBaseMapAlphaPhongMask != -1) && (params[info.m_nWetBaseMapAlphaPhongMask]->GetIntValue() != 0);
		float fHasBaseAlphaPhongMask = bHasBaseAlphaPhongMask ? 1 : 0;
		// Controls for lerp-style paths through shader code
		float vShaderControls[4] = { fHasBaseAlphaPhongMask, 0.0f/*unused*/, GetFloatParam(info.m_nWetBlendStrength, params), fInvertPhongMask };
		DynamicCmdsOut.SetPixelShaderConstant(PSREG_CONSTANT_27, vShaderControls, 1);

		DynamicCmdsOut.SetAmbientCubeDynamicStateVertexShader();

		if (!bHasFlashlight)
		{
			if (g_pHardwareConfig->SupportsShaderModel_3_0())
				DynamicCmdsOut.BindStandardTexture(SHADER_SAMPLER5, TEXTURE_SHADOW_NOISE_2D);
			else
				DynamicCmdsOut.BindStandardTexture(SHADER_SAMPLER5, TEXTURE_NORMALIZATION_CUBEMAP_SIGNED);
		}

		DynamicCmdsOut.SetPixelShaderStateAmbientLightCube(PSREG_AMBIENT_CUBE);	// Force to black if not bAmbientLight

		// Pack Phong exponent in with the eye position
		float vEyePos_SpecExponent[4], vFresnelRanges_SpecBoost[4] = { 1, 0.5, 1, 1 };
		float vSpecularTint[4] = { 1, 1, 1, 4 };
		pShaderAPI->GetWorldSpaceCameraPosition(vEyePos_SpecExponent);

		// If we have a phong exponent factor, then use that as a multiplier against the texture.
		if (bHasPhongExponentFactor)
		{
			vEyePos_SpecExponent[3] = flPhongExponentFactor;
		}
		else
		{
			// Use the alpha channel of the normal map for the exponent by default
			vEyePos_SpecExponent[3] = -1.f;
			if ((info.m_nWetPhongExponent != -1) && params[info.m_nWetPhongExponent]->IsDefined())
			{
				float fValue = params[info.m_nWetPhongExponent]->GetFloatValue();
				if (fValue > 0.f)
				{
					// Nonzero value in material overrides map channel
					vEyePos_SpecExponent[3] = fValue;
				}
			}
		}

		// Get the tint parameter
		if ((info.m_nWetPhongTint != -1) && params[info.m_nWetPhongTint]->IsDefined())
		{
			params[info.m_nWetPhongTint]->GetVecValue(vSpecularTint, 3);
		}

		// Get the rim light power (goes in w of Phong tint)
		if (bHasRimLight && (info.m_nWetRimLightPower != -1) && params[info.m_nWetRimLightPower]->IsDefined())
		{
			vSpecularTint[3] = params[info.m_nWetRimLightPower]->GetFloatValue();
			vSpecularTint[3] = max(vSpecularTint[3], 1.0f);	// Make sure this is at least 1
		}

		// Get the rim boost (goes in w of flashlight position)
		if (bHasRimLight && (info.m_nWetRimLightBoost != -1) && params[info.m_nWetRimLightBoost]->IsDefined())
		{
			vRimBoost[3] = params[info.m_nWetRimLightBoost]->GetFloatValue();
		}

		if (!bHasFlashlight)
		{
			float vRimMaskControl[4] = { 0, 0, 0, 0 }; // Only x is relevant in shader code
			vRimMaskControl[0] = bHasRimMaskMap ? params[info.m_nWetRimMask]->GetFloatValue() : 0.0f;

			// Rim mask...if this is true, use alpha channel of spec exponent texture to mask the rim term
			DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_ATTENUATION, vRimMaskControl, 1);
		}

		// If it's all zeros, there was no constant tint in the vmt
		if ((vSpecularTint[0] == 0.0f) && (vSpecularTint[1] == 0.0f) && (vSpecularTint[2] == 0.0f))
		{
			if (bHasPhongTintMap)				// If we have a map to use, tell the shader
			{
				vSpecularTint[0] = -1;
			}
			else								// Otherwise, just tint with white
			{
				vSpecularTint[0] = 1.0f;
				vSpecularTint[1] = 1.0f;
				vSpecularTint[2] = 1.0f;
			}
		}

		if ((info.m_nWetPhongFresnelRanges != -1) && params[info.m_nWetPhongFresnelRanges]->IsDefined())
		{
			params[info.m_nWetPhongFresnelRanges]->GetVecValue(vFresnelRanges_SpecBoost, 3);	// Grab optional Fresnel range parameters
			// Change fresnel range encoding from (min, mid, max) to ((mid-min)*2, mid, (max-mid)*2)
			//vFresnelRanges_SpecBoost[0] = (vFresnelRanges_SpecBoost[1] - vFresnelRanges_SpecBoost[0]) * 2;
			//vFresnelRanges_SpecBoost[2] = (vFresnelRanges_SpecBoost[2] - vFresnelRanges_SpecBoost[1]) * 2;
		}

		if ((info.m_nWetPhongBoost != -1) && params[info.m_nWetPhongBoost]->IsDefined())		// Grab optional Phong boost param
			vFresnelRanges_SpecBoost[3] = params[info.m_nWetPhongBoost]->GetFloatValue();
		else
			vFresnelRanges_SpecBoost[3] = 1.0f;

		DynamicCmdsOut.SetPixelShaderConstant(PSREG_EYEPOS_SPEC_EXPONENT, vEyePos_SpecExponent, 1);
		DynamicCmdsOut.SetPixelShaderConstant(PSREG_FRESNEL_SPEC_PARAMS, vFresnelRanges_SpecBoost, 1);

		DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_POSITION_RIM_BOOST, vRimBoost, 1);	// Rim boost in w on non-flashlight pass

		DynamicCmdsOut.SetPixelShaderConstant(PSREG_SPEC_RIM_PARAMS, vSpecularTint, 1);
		DynamicCmdsOut.SetPixelShaderFogParams(PSREG_FOG_PARAMS);

		// flashlightfixme: put this in common code.
		if (bHasFlashlight)
		{
			VMatrix worldToTexture;
			float atten[4], pos[4], tweaks[4];

			const FlashlightState_t& flashlightState = pShaderAPI->GetFlashlightState(worldToTexture);
			DynamicCmdsOut.SetFlashLightColorFromState(flashlightState, pShaderAPI, PSREG_FLASHLIGHT_COLOR);

			DynamicCmdsOut.BindTexture(SHADER_SAMPLER6, flashlightState.m_pSpotlightTexture, flashlightState.m_nSpotlightTextureFrame);

			atten[0] = flashlightState.m_fConstantAtten;		// Set the flashlight attenuation factors
			atten[1] = flashlightState.m_fLinearAtten;
			atten[2] = flashlightState.m_fQuadraticAtten;
			atten[3] = flashlightState.m_FarZ;
			DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_ATTENUATION, atten, 1);

			pos[0] = flashlightState.m_vecLightOrigin[0];		// Set the flashlight origin
			pos[1] = flashlightState.m_vecLightOrigin[1];
			pos[2] = flashlightState.m_vecLightOrigin[2];
			DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_POSITION_RIM_BOOST, pos, 1);	// steps on rim boost

			DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_TO_WORLD_TEXTURE, worldToTexture.Base(), 4);

			// Tweaks associated with a given flashlight
			tweaks[0] = ShadowFilterFromState(flashlightState);
			tweaks[1] = ShadowAttenFromState(flashlightState);
			pShader->HashShadow2DJitter(flashlightState.m_flShadowJitterSeed, &tweaks[2], &tweaks[3]);
			DynamicCmdsOut.SetPixelShaderConstant(PSREG_ENVMAP_TINT__SHADOW_TWEAKS, tweaks, 1);

			// Dimensions of screen, used for screen-space noise map sampling
			float vScreenScale[4] = { 1280.0f / 32.0f, 720.0f / 32.0f, 0, 0 };
			int nWidth, nHeight;
			pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
			vScreenScale[0] = (float)nWidth / 32.0f;
			vScreenScale[1] = (float)nHeight / 32.0f;
			DynamicCmdsOut.SetPixelShaderConstant(PSREG_FLASHLIGHT_SCREEN_SCALE, vScreenScale, 1);
		}

		DynamicCmdsOut.End();
		pShaderAPI->ExecuteCommandBuffer(DynamicCmdsOut.Base());
	}

	pShader->Draw();
}
