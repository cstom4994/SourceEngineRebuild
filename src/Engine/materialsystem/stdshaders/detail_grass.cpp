
#include "BaseVSShader.h"
#include "mathlib/vmatrix.h"
#include "convar.h"
#include "cpp_shader_constant_register_map.h"

#include "detail_prop_shader_ps30.inc"
#include "detail_prop_shader_vs30.inc"

static const float kDefaultSpecColor[] = { 0.905750f, 1.0f, 0.675000f };

BEGIN_VS_SHADER(detail_grass, "")

BEGIN_SHADER_PARAMS

SHADER_PARAM(MUTABLE_01, SHADER_PARAM_TYPE_VEC3, "[0 0 0]", "Wind Dir")
SHADER_PARAM(MUTABLE_02, SHADER_PARAM_TYPE_FLOAT, "0.0f", "Wind Angle (Radians)")

SHADER_PARAM(GRASS_SPEC_COLOR, SHADER_PARAM_TYPE_COLOR, "[0.905750 1 0.675000]", "")

SHADER_PARAM(TIME, SHADER_PARAM_TYPE_FLOAT, "0.0", "Needs CurrentTime Proxy")

END_SHADER_PARAMS



SHADER_INIT_PARAMS()
{
	SET_PARAM_VEC_IF_NOT_DEFINED(GRASS_SPEC_COLOR, kDefaultSpecColor, 3);
}

SHADER_FALLBACK
{
	return 0;
}

SHADER_INIT
{
	LoadTexture(BASETEXTURE);

	LoadTexture(FLASHLIGHTTEXTURE, TEXTUREFLAGS_SRGB);
}

SHADER_DRAW
{
	int nShadowFilterMode = 0;
	bool bHasFlashlight = UsingFlashlight(params);

	if (bHasFlashlight)
	{
		nShadowFilterMode = g_pHardwareConfig->GetShadowFilterMode();	// Based upon vendor and device dependent formats
	}

	SHADOW_STATE
	{
	// Reset shadow state manually since we're drawing from two materials
	SetInitialShadowState();

	pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
	pShaderShadow->EnableSRGBRead(SHADER_SAMPLER0, false);

	pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
	pShaderShadow->EnableSRGBRead(SHADER_SAMPLER1, true);
	pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);	// Depth texture
	pShaderShadow->SetShadowDepthFiltering(SHADER_SAMPLER2);
	pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
	pShaderShadow->EnableSRGBRead(SHADER_SAMPLER3, false);

	pShaderShadow->EnableSRGBWrite(false);
	pShaderShadow->EnableDepthWrites(true);
	pShaderShadow->EnableCulling(false);
	pShaderShadow->EnableAlphaTest(true);
	pShaderShadow->EnableBlending(false);
	pShaderShadow->EnableDepthTest(true);
	pShaderShadow->AlphaFunc(SHADER_ALPHAFUNC_GEQUAL, 0.5f);
	

	unsigned int flags = VERTEX_POSITION|VERTEX_NORMAL|VERTEX_COLOR| VERTEX_FORMAT_VERTEX_SHADER;
	int nTexCoordCount = 3;
	int userDataSize = 0;
	int nTexCoordDims[] = { 2, 3, 3 };
	pShaderShadow->VertexShaderVertexFormat(flags, nTexCoordCount, nTexCoordDims, userDataSize);

	// Vertex Shader
	DECLARE_STATIC_VERTEX_SHADER(detail_prop_shader_vs30);
	SET_STATIC_VERTEX_SHADER_COMBO(FLASHLIGHT, bHasFlashlight);
	SET_STATIC_VERTEX_SHADER(detail_prop_shader_vs30);

	DECLARE_STATIC_PIXEL_SHADER(detail_prop_shader_ps30);
	SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHT, bHasFlashlight);
	SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHTDEPTHFILTERMODE, nShadowFilterMode);
	SET_STATIC_PIXEL_SHADER(detail_prop_shader_ps30);
}
DYNAMIC_STATE
{
	// Reset render state manually since we're drawing from two materials
	pShaderAPI->SetDefaultState();

	bool bFlashlightShadows = false;
	if (bHasFlashlight)
	{
		VMatrix worldToTexture;
		ITexture *pFlashlightDepthTexture;
		FlashlightState_t state = pShaderAPI->GetFlashlightStateEx(worldToTexture, &pFlashlightDepthTexture);
		bFlashlightShadows = state.m_bEnableShadows && (pFlashlightDepthTexture != NULL);

		BindTexture(SHADER_SAMPLER1, state.m_pSpotlightTexture, state.m_nSpotlightTextureFrame);

		SetFlashLightColorFromState(state, pShaderAPI, PSREG_FLASHLIGHT_COLOR);

		if (pFlashlightDepthTexture && g_pConfig->ShadowDepthTexture() && state.m_bEnableShadows)
		{
			BindTexture(SHADER_SAMPLER2, pFlashlightDepthTexture, 0);
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER3, TEXTURE_SHADOW_NOISE_2D);
		}
	}

	// Set Vertex Shader Combos
	DECLARE_DYNAMIC_VERTEX_SHADER(detail_prop_shader_vs30);
	SET_DYNAMIC_VERTEX_SHADER(detail_prop_shader_vs30);

	DECLARE_DYNAMIC_PIXEL_SHADER(detail_prop_shader_ps30);
	SET_DYNAMIC_PIXEL_SHADER_COMBO(WRITEWATERFOGTODESTALPHA, false);
	SET_DYNAMIC_PIXEL_SHADER_COMBO(PIXELFOGTYPE, pShaderAPI->GetPixelFogCombo());
	SET_DYNAMIC_PIXEL_SHADER_COMBO(FLASHLIGHTSHADOWS, bFlashlightShadows);
	SET_DYNAMIC_PIXEL_SHADER(detail_prop_shader_ps30);

	if (params[BASETEXTURE]->IsTexture())
	{
		BindTexture(SHADER_SAMPLER0, BASETEXTURE, FRAME);
	}
	else
	{
		pShaderAPI->BindStandardTexture(SHADER_SAMPLER0, TEXTURE_WHITE);
	}


	pShaderAPI->SetPixelShaderFogParams(PSREG_FOG_PARAMS);

	float vPsConst0[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	if (IS_PARAM_DEFINED(MUTABLE_01))
	{
		params[MUTABLE_01]->GetVecValue(vPsConst0, 3);
	}

	if (IS_PARAM_DEFINED(MUTABLE_02))
	{
		vPsConst0[3] = params[MUTABLE_02]->GetFloatValue();
	}

	pShaderAPI->SetVertexShaderConstant(VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, vPsConst0);

	float flTime = IS_PARAM_DEFINED(TIME) && params[TIME]->GetFloatValue() > 0.0f ? params[TIME]->GetFloatValue() : pShaderAPI->CurrentTime();
	float vPsConst1[4] = { flTime, 0.0f, 0.0f, 0.0f };
	pShaderAPI->SetVertexShaderConstant(VERTEX_SHADER_SHADER_SPECIFIC_CONST_1, vPsConst1);

	if (bHasFlashlight)
	{
		VMatrix worldToTexture;
		float atten[4], pos[4], tweaks[4];

		const FlashlightState_t &flashlightState = pShaderAPI->GetFlashlightState(worldToTexture);
		SetFlashLightColorFromState(flashlightState, pShaderAPI, PSREG_FLASHLIGHT_COLOR);

		BindTexture(SHADER_SAMPLER1, flashlightState.m_pSpotlightTexture, flashlightState.m_nSpotlightTextureFrame);

		atten[0] = flashlightState.m_fConstantAtten;		// Set the flashlight attenuation factors
		atten[1] = flashlightState.m_fLinearAtten;
		atten[2] = flashlightState.m_fQuadraticAtten;
		atten[3] = flashlightState.m_FarZ;
		pShaderAPI->SetPixelShaderConstant(PSREG_FLASHLIGHT_ATTENUATION, atten, 1);

		pos[0] = flashlightState.m_vecLightOrigin[0];		// Set the flashlight origin
		pos[1] = flashlightState.m_vecLightOrigin[1];
		pos[2] = flashlightState.m_vecLightOrigin[2];
		pShaderAPI->SetPixelShaderConstant(PSREG_FLASHLIGHT_POSITION_RIM_BOOST, pos, 1);

		pShaderAPI->SetVertexShaderConstant(VERTEX_SHADER_SHADER_SPECIFIC_CONST_2, worldToTexture.Base(), 4);

		// Tweaks associated with a given flashlight
		tweaks[0] = ShadowFilterFromState(flashlightState);
		tweaks[1] = ShadowAttenFromState(flashlightState);
		HashShadow2DJitter(flashlightState.m_flShadowJitterSeed, &tweaks[2], &tweaks[3]);
		pShaderAPI->SetPixelShaderConstant(PSREG_ENVMAP_TINT__SHADOW_TWEAKS, tweaks, 1);

		// Dimensions of screen, used for screen-space noise map sampling
		float vScreenScale[4] = { 1280.0f / 32.0f, 720.0f / 32.0f, 0, 0 };
		int nWidth, nHeight;
		pShaderAPI->GetBackBufferDimensions(nWidth, nHeight);
		vScreenScale[0] = (float)nWidth / 32.0f;
		vScreenScale[1] = (float)nHeight / 32.0f;
		pShaderAPI->SetPixelShaderConstant(PSREG_FLASHLIGHT_SCREEN_SCALE, vScreenScale, 1);
	}

	float eyePos[4];
	pShaderAPI->GetWorldSpaceCameraPosition(eyePos);
	pShaderAPI->SetPixelShaderConstant(PSREG_EYEPOS_SPEC_EXPONENT, eyePos);

	SetPixelShaderConstant(17, GRASS_SPEC_COLOR);
	
}

Draw();
}
END_SHADER
