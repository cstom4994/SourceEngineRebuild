//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//
#include "BaseVSShader.h"
#include "LightmappedPBR_dx9_helper.h"
#include "convar.h"
#include "cpp_shader_constant_register_map.h"
#include "lightmappedPBR_vs30.inc"
#include "lightmappedPBR_ps30.inc"
#include "commandbuilder.h"

#include "IDeferredExt.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static ConVar mat_fullbright( "mat_fullbright", "0", FCVAR_CHEAT );


extern ConVar r_csm_bias;
extern ConVar r_csm_slopescalebias;
extern ConVar r_csm_performance;
extern ConVar mat_cubemapparallax;

//-----------------------------------------------------------------------------
// Initialize shader parameters
//-----------------------------------------------------------------------------
void InitParamsLightmappedPBR_DX9( CBaseVSShader *pShader, IMaterialVar** params, const char *pMaterialName, LightmappedPBR_DX9_Vars_t &info )
{	
	// FLASHLIGHTFIXME: Do ShaderAPI::BindFlashlightTexture
	Assert( info.m_nFlashlightTexture >= 0 );
	
	params[info.m_nBRDF]->SetStringValue("models/PBRTest/BRDF");

	if ( g_pHardwareConfig->SupportsBorderColor() )
	{
		params[FLASHLIGHTTEXTURE]->SetStringValue( "effects/flashlight_border" );
	}
	else
	{
		params[FLASHLIGHTTEXTURE]->SetStringValue( "effects/flashlight001" );
	}

	if (((info.m_nBumpmap != -1 && params[info.m_nBumpmap]->IsDefined()) && g_pConfig->UseBumpmapping())
		// we don't need a tangent space if we have envmap without bumpmap
		//		|| ( info.m_nEnvmap != -1 && params[info.m_nEnvmap]->IsDefined() ) 
		)
	{
		SET_FLAGS2(MATERIAL_VAR2_NEEDS_TANGENT_SPACES);
	}

	SET_FLAGS2(MATERIAL_VAR2_LIGHTING_LIGHTMAP);
	if (g_pConfig->UseBumpmapping() && params[info.m_nBumpmap]->IsDefined())
	{
		SET_FLAGS2(MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP);
	}


	if (info.m_nEnvmapRadius != -1 && !params[info.m_nEnvmapRadius]->IsDefined())
		params[info.m_nEnvmapRadius]->SetIntValue(-1);
}

//-----------------------------------------------------------------------------
// Initialize shader
//-----------------------------------------------------------------------------
void InitLightmappedPBR_DX9( CBaseVSShader *pShader, IMaterialVar** params, LightmappedPBR_DX9_Vars_t &info )
{
	Assert( info.m_nFlashlightTexture >= 0 );
	pShader->LoadTexture(info.m_nFlashlightTexture, TEXTUREFLAGS_SRGB);
	
	bool bIsBaseTextureTranslucent = false;
	if ( params[info.m_nBaseTexture]->IsDefined() )
	{
		pShader->LoadTexture( info.m_nBaseTexture, TEXTUREFLAGS_SRGB );
		
		if ( params[info.m_nBaseTexture]->GetTextureValue()->IsTranslucent() )
		{
			bIsBaseTextureTranslucent = true;
		}
	}

	if (info.m_nRoughness != -1 && params[info.m_nRoughness]->IsDefined())
	{
		pShader->LoadTexture(info.m_nRoughness);
	}
	if (info.m_nMetallic != -1 && params[info.m_nMetallic]->IsDefined())
	{
		pShader->LoadTexture(info.m_nMetallic);
	}
	if (info.m_nAO != -1 && params[info.m_nAO]->IsDefined())
	{
		pShader->LoadTexture(info.m_nAO);
	}
	if (info.m_nEmissive != -1 && params[info.m_nEmissive]->IsDefined())
	{
		pShader->LoadTexture(info.m_nEmissive);
	}
	if (info.m_nBRDF != -1 && params[info.m_nBRDF]->IsDefined())
	{
		pShader->LoadTexture(info.m_nBRDF);
	}

	if (info.m_nEnvmap != -1 && params[info.m_nEnvmap]->IsDefined())
	{
		if (!IS_FLAG_SET(MATERIAL_VAR_ENVMAPSPHERE))
		{
			int flags = g_pHardwareConfig->GetHDRType() == HDR_TYPE_NONE ? TEXTUREFLAGS_SRGB : 0;
			flags |= TEXTUREFLAGS_ALL_MIPS;
			pShader->LoadCubeMap(info.m_nEnvmap, flags);
		}
		else
		{
			pShader->LoadTexture(info.m_nEnvmap, g_pHardwareConfig->GetHDRType() == HDR_TYPE_NONE ? TEXTUREFLAGS_SRGB : 0);
		}

		if (!g_pHardwareConfig->SupportsCubeMaps())
		{
			SET_FLAGS(MATERIAL_VAR_ENVMAPSPHERE);
		}
	}

	if (g_pConfig->UseBumpmapping())
	{
		if ((info.m_nBumpmap != -1) && params[info.m_nBumpmap]->IsDefined())
		{
			pShader->LoadBumpMap(info.m_nBumpmap);
			SET_FLAGS2(MATERIAL_VAR2_DIFFUSE_BUMPMAPPED_MODEL);
		}
	}
}

class CLightmappedPBR_DX9_Context : public CBasePerMaterialContextData
{
public:
	CCommandBufferBuilder< CFixedCommandStorageBuffer< 800 > > m_SemiStaticCmdsOut;
	bool m_bFastPath;

};

//-----------------------------------------------------------------------------
// Draws the shader
//-----------------------------------------------------------------------------
static void DrawLightmappedPBR_DX9_Internal( CBaseVSShader *pShader, IMaterialVar** params, IShaderDynamicAPI *pShaderAPI, IShaderShadow* pShaderShadow,
	bool bHasFlashlight, LightmappedPBR_DX9_Vars_t &info, VertexCompressionType_t vertexCompression,
							CBasePerMaterialContextData **pContextDataPtr )
{
	bool bHasBaseTexture = (info.m_nBaseTexture != -1) && params[info.m_nBaseTexture]->IsTexture();
	bool bHasRoughness = (info.m_nRoughness != -1) && params[info.m_nRoughness]->IsTexture();
	bool bHasMetallic = (info.m_nMetallic != -1) && params[info.m_nMetallic]->IsTexture();
	bool bHasAO = (info.m_nAO != -1) && params[info.m_nAO]->IsTexture();
	bool bHasEmissive = (info.m_nEmissive != -1) && params[info.m_nEmissive]->IsTexture();
	bool bIsAlphaTested = IS_FLAG_SET( MATERIAL_VAR_ALPHATEST ) != 0;
	bool bHasEnvmap =(info.m_nEnvmap != -1) && params[info.m_nEnvmap]->IsTexture();
	bool bHasLegacyEnvSphereMap = bHasEnvmap && IS_FLAG_SET(MATERIAL_VAR_ENVMAPSPHERE);
	bool bHasBump = IsTextureSet(info.m_nBumpmap, params);
	bool bUseSmoothness = info.m_nUseSmoothness != -1 && params[info.m_nUseSmoothness]->GetIntValue() == 1;
	bool bSeamlessMapping = ((info.m_nSeamlessMappingScale != -1) && (params[info.m_nSeamlessMappingScale]->GetFloatValue() != 0.0));

	bool bHasVertexColor = IS_FLAG_SET(MATERIAL_VAR_VERTEXCOLOR);
	bool bHasVertexAlpha = IS_FLAG_SET(MATERIAL_VAR_VERTEXALPHA);

	BlendType_t nBlendType= pShader->EvaluateBlendRequirements( info.m_nBaseTexture, true );
	bool bFullyOpaque = ( nBlendType != BT_BLENDADD ) && ( nBlendType != BT_BLEND ) && !bIsAlphaTested && !bHasFlashlight;

	CLightmappedPBR_DX9_Context *pContextData = reinterpret_cast< CLightmappedPBR_DX9_Context *> ( *pContextDataPtr );
	if ( !pContextData )
	{
		pContextData = new CLightmappedPBR_DX9_Context;
		*pContextDataPtr = pContextData;
	}

	if( pShader->IsSnapshotting() )
	{
		pShaderShadow->EnableAlphaTest( bIsAlphaTested );

		if( info.m_nAlphaTestReference != -1 && params[info.m_nAlphaTestReference]->GetFloatValue() > 0.0f )
		{
			pShaderShadow->AlphaFunc( SHADER_ALPHAFUNC_GEQUAL, params[info.m_nAlphaTestReference]->GetFloatValue() );
		}

		int nShadowFilterMode = 0;
		if( bHasFlashlight )
		{
			if (params[info.m_nBaseTexture]->IsTexture())
			{
				pShader->SetAdditiveBlendingShadowState( info.m_nBaseTexture, true );
			}

			if( bIsAlphaTested )
			{
				// disable alpha test and use the zfunc zequals since alpha isn't guaranteed to 
				// be the same on both the regular pass and the flashlight pass.
				pShaderShadow->EnableAlphaTest( false );
				pShaderShadow->DepthFunc( SHADER_DEPTHFUNC_EQUAL );
			}
			pShaderShadow->EnableBlending( true );
			pShaderShadow->EnableDepthWrites( false );

			// Be sure not to write to dest alpha
			pShaderShadow->EnableAlphaWrites( false );

			nShadowFilterMode = g_pHardwareConfig->GetShadowFilterMode();	// Based upon vendor and device dependent formats
		}
		else // not flashlight pass
		{
			if (params[info.m_nBaseTexture]->IsTexture())
			{
				pShader->SetDefaultBlendingShadowState( info.m_nBaseTexture, true );
			}
		}
		
		unsigned int flags = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_TANGENT_SPACE;

		// Always enable...will bind white if nothing specified...
		pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );		// Base (albedo) map
		pShaderShadow->EnableSRGBRead( SHADER_SAMPLER0, true );

		pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);		// Roughness map
		pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);		// Metallic map

		if (bHasEnvmap)
		{
			pShaderShadow->EnableTexture(SHADER_SAMPLER7, true);
			if (g_pHardwareConfig->GetHDRType() == HDR_TYPE_NONE)
			{
				pShaderShadow->EnableSRGBRead(SHADER_SAMPLER7, true);
			}
		}


		if (bHasVertexColor || bHasVertexAlpha)
		{
			flags |= VERTEX_COLOR;
		}

		pShaderShadow->EnableTexture( SHADER_SAMPLER4, true ); // Shadow depth map
		pShaderShadow->SetShadowDepthFiltering( SHADER_SAMPLER4 );
		pShaderShadow->EnableSRGBRead( SHADER_SAMPLER4, false );

		if( bHasFlashlight )
		{
			pShaderShadow->EnableTexture( SHADER_SAMPLER5, true );	// Noise map
			pShaderShadow->EnableTexture( SHADER_SAMPLER6, true );	// Flashlight cookie
			pShaderShadow->EnableSRGBRead( SHADER_SAMPLER6, true );
		}

		pShaderShadow->EnableTexture(SHADER_SAMPLER8, true);	// BRDF for IBL

		pShaderShadow->EnableTexture(SHADER_SAMPLER9, true);	// Ambient Occlusion
		pShaderShadow->EnableTexture(SHADER_SAMPLER10, true);	// Emissive map
		pShaderShadow->EnableTexture(SHADER_SAMPLER11, true);	// Lightmap

		// Always enable, since flat normal will be bound
		pShaderShadow->EnableTexture( SHADER_SAMPLER3, true );		// Normal map
		pShaderShadow->EnableTexture( SHADER_SAMPLER5, true );		// Normalizing cube map
		pShaderShadow->EnableSRGBWrite( true );
		
		// texcoord0 : base texcoord
		// texcoord1 : lightmap texcoord
		// texcoord2 : lightmap texcoord offset
		int numTexCoords = 3;

		pShaderShadow->VertexShaderVertexFormat( flags, numTexCoords, 0, 0 );

		DECLARE_STATIC_VERTEX_SHADER( lightmappedpbr_vs30 );
		SET_STATIC_VERTEX_SHADER_COMBO(VERTEXCOLOR, bHasVertexColor || bHasVertexAlpha);
		SET_STATIC_VERTEX_SHADER_COMBO(BUMPMAP, bHasBump);
		SET_STATIC_VERTEX_SHADER_COMBO(DIFFUSEBUMPMAP, bHasBump);
		SET_STATIC_VERTEX_SHADER_COMBO(VERTEXALPHATEXBLENDFACTOR, false);
		SET_STATIC_VERTEX_SHADER(lightmappedpbr_vs30);

		// Assume we're only going to get in here if we support 2b
		DECLARE_STATIC_PIXEL_SHADER(lightmappedpbr_ps30);
		SET_STATIC_PIXEL_SHADER_COMBO( CUBEMAP, bHasEnvmap && !bHasFlashlight);
		SET_STATIC_PIXEL_SHADER_COMBO( CUBEMAP_SPHERE_LEGACY, bHasLegacyEnvSphereMap);
		SET_STATIC_PIXEL_SHADER_COMBO( FLASHLIGHT, bHasFlashlight );
		SET_STATIC_PIXEL_SHADER_COMBO( CONVERT_TO_SRGB, 0 );
		SET_STATIC_PIXEL_SHADER_COMBO(SMOOTHNESS, bUseSmoothness);
		SET_STATIC_PIXEL_SHADER_COMBO(SEAMLESS, false);
		SET_STATIC_PIXEL_SHADER_COMBO(BUMPMAP, bHasBump);
		SET_STATIC_PIXEL_SHADER(lightmappedpbr_ps30);

		if( bHasFlashlight )
		{
			pShader->FogToBlack();
		}
		else
		{
			pShader->DefaultFog();
		}

		// HACK HACK HACK - enable alpha writes all the time so that we have them for underwater stuff
		pShaderShadow->EnableAlphaWrites( bFullyOpaque );
	}
	else // not snapshotting -- begin dynamic state
	{
		bool bLightingOnly = mat_fullbright.GetInt() == 2 && !IS_FLAG_SET( MATERIAL_VAR_NO_DEBUG_OVERRIDE );
		bool isEnvmapCorrected = (info.m_nEnvmapRadius != -1 && info.m_nEnvmapOrigin != -1) && (params[info.m_nEnvmapRadius]->IsDefined() && params[info.m_nEnvmapRadius]->GetIntValue() > 0) && params[info.m_nEnvmapOrigin]->IsDefined();

		float color[4] = { 1.0, 1.0, 1.0, 1.0 };
		pShader->ComputeModulationColor(color);
		float flLScale = pShaderAPI->GetLightMapScaleFactor();
		color[0] *= flLScale;
		color[1] *= flLScale;
		color[2] *= flLScale;
		pShaderAPI->SetPixelShaderConstant(20, color, 1);

		if (isEnvmapCorrected)
		{
			float* origin = (float*)params[info.m_nEnvmapOrigin]->GetVecValue();
			float radius = (float)params[info.m_nEnvmapRadius]->GetIntValue();
			float origin_And_Radius[4] = { origin[0], origin[1], origin[2], radius };
			pShaderAPI->SetPixelShaderConstant(21, origin_And_Radius);
		}

		if( bHasBaseTexture )
			pShader->BindTexture( SHADER_SAMPLER0, info.m_nBaseTexture, info.m_nBaseTextureFrame );
		else
			pShaderAPI->BindStandardTexture( SHADER_SAMPLER0, TEXTURE_WHITE );

		if (bHasRoughness)
			pShader->BindTexture(SHADER_SAMPLER1, info.m_nRoughness);
		else
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER1, TEXTURE_WHITE);

		if (bHasMetallic)
			pShader->BindTexture(SHADER_SAMPLER2, info.m_nMetallic);
		else
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER2, TEXTURE_BLACK);

		if (bHasEnvmap)
			pShader->BindTexture(SHADER_SAMPLER7, info.m_nEnvmap);

		if (bHasAO)
			pShader->BindTexture(SHADER_SAMPLER9, info.m_nAO);
		else
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER9, TEXTURE_WHITE);

		if (bHasEmissive)
			pShader->BindTexture(SHADER_SAMPLER10, info.m_nEmissive);
		else
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER10, TEXTURE_BLACK);

		pShaderAPI->BindStandardTexture(SHADER_SAMPLER11, TEXTURE_LIGHTMAP);

		ITexture *pCascadedDepthTexture = (ITexture *)pShaderAPI->GetIntRenderingParameter( INT_RENDERPARM_CASCADED_DEPTHTEXTURE );
		bool bUseCSM = pCascadedDepthTexture != NULL;

		if (!g_pConfig->m_bFastNoBump)
		{
			if (bHasBump)
			{
				pShader->BindTexture(SHADER_SAMPLER3, info.m_nBumpmap);
			}
			else
			{
				pShaderAPI->BindStandardTexture(SHADER_SAMPLER3, TEXTURE_NORMALMAP_FLAT);
			}
		}
		else
		{
			if (bHasBump)
			{
				pShaderAPI->BindStandardTexture(SHADER_SAMPLER3, TEXTURE_NORMALMAP_FLAT);
			}
		}

		pShader->BindTexture(SHADER_SAMPLER8, info.m_nBRDF);
		
		LightState_t lightState = { 0, false, false };
		bool bFlashlightShadows = false;
		if( bHasFlashlight )
		{
			Assert( info.m_nFlashlightTexture >= 0 && info.m_nFlashlightTextureFrame >= 0 );
			pShader->BindTexture( SHADER_SAMPLER6, info.m_nFlashlightTexture, info.m_nFlashlightTextureFrame );
			VMatrix worldToTexture;
			ITexture *pFlashlightDepthTexture;
			FlashlightState_t state = pShaderAPI->GetFlashlightStateEx( worldToTexture, &pFlashlightDepthTexture );
			bFlashlightShadows = state.m_bEnableShadows && ( pFlashlightDepthTexture != NULL );

			SetFlashLightColorFromState( state, pShaderAPI, PSREG_FLASHLIGHT_COLOR );

			if( pFlashlightDepthTexture && g_pConfig->ShadowDepthTexture() && state.m_bEnableShadows )
			{
				pShader->BindTexture( SHADER_SAMPLER4, pFlashlightDepthTexture, 0 );
				pShaderAPI->BindStandardTexture( SHADER_SAMPLER5, TEXTURE_SHADOW_NOISE_2D );
			}
		}
		else // no flashlight
		{
			pShaderAPI->GetDX9LightState( &lightState );
		}

		MaterialFogMode_t fogType = pShaderAPI->GetSceneFogMode();
		int fogIndex = ( fogType == MATERIAL_FOG_LINEAR_BELOW_FOG_Z ) ? 1 : 0;

		bool bWriteDepthToAlpha = false;
		bool bWriteWaterFogToAlpha = false;
		if( bFullyOpaque ) 
		{
			bWriteDepthToAlpha = pShaderAPI->ShouldWriteDepthToDestAlpha();
			bWriteWaterFogToAlpha = (fogType == MATERIAL_FOG_LINEAR_BELOW_FOG_Z);
			AssertMsg( !(bWriteDepthToAlpha && bWriteWaterFogToAlpha), "Can't write two values to alpha at the same time." );
		}

		DECLARE_DYNAMIC_VERTEX_SHADER( lightmappedpbr_vs30 );
		SET_DYNAMIC_VERTEX_SHADER_COMBO( DOWATERFOG, fogIndex );
		SET_DYNAMIC_VERTEX_SHADER_COMBO( FASTPATH, true);
		SET_DYNAMIC_VERTEX_SHADER(lightmappedpbr_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(lightmappedpbr_ps30);
		SET_DYNAMIC_PIXEL_SHADER_COMBO( WRITEWATERFOGTODESTALPHA, bWriteWaterFogToAlpha );
		SET_DYNAMIC_PIXEL_SHADER_COMBO( WRITE_DEPTH_TO_DESTALPHA, bWriteDepthToAlpha );
		SET_DYNAMIC_PIXEL_SHADER_COMBO( PIXELFOGTYPE, pShaderAPI->GetPixelFogCombo() );
		SET_DYNAMIC_PIXEL_SHADER_COMBO( FLASHLIGHTSHADOWS, bFlashlightShadows );
		SET_DYNAMIC_PIXEL_SHADER_COMBO( CUBEMAPCORRECTED, isEnvmapCorrected && mat_cubemapparallax.GetBool());
		SET_DYNAMIC_PIXEL_SHADER_COMBO( LIGHT_PREVIEW, pShaderAPI->GetIntRenderingParameter( INT_RENDERPARM_ENABLE_FIXED_LIGHTING ) );
		SET_DYNAMIC_PIXEL_SHADER_COMBO( CSM, bUseCSM && !bHasFlashlight );
		SET_DYNAMIC_PIXEL_SHADER_COMBO( CSM_PERF, MAX( 0, MIN( r_csm_performance.GetInt(), 2 ) ) ); // i just dont know anymore
		SET_DYNAMIC_PIXEL_SHADER(lightmappedpbr_ps30);

		if (bSeamlessMapping)
		{
			float scale = params[info.m_nSeamlessMappingScale]->GetFloatValue();
			pShaderAPI->SetVertexShaderConstant(VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, &scale);
		}

		pShader->SetVertexShaderTextureTransform( VERTEX_SHADER_SHADER_SPECIFIC_CONST_2, info.m_nBaseTextureTransform );
		pShader->SetModulationPixelShaderDynamicState_LinearColorSpace( 1 );
		pShader->SetAmbientCubeDynamicStateVertexShader();

		// handle mat_fullbright 2 (diffuse lighting only)
		if( bLightingOnly )
		{
			pShaderAPI->BindStandardTexture( SHADER_SAMPLER0, TEXTURE_GREY );
		}

		pShaderAPI->SetPixelShaderFogParams( PSREG_FOG_PARAMS );

		float vEyePos_SpecExponent[4];
		pShaderAPI->GetWorldSpaceCameraPosition(vEyePos_SpecExponent);
		vEyePos_SpecExponent[3] = 0.0f;
		pShaderAPI->SetPixelShaderConstant(PSREG_EYEPOS_SPEC_EXPONENT, vEyePos_SpecExponent, 1);

		if( bHasFlashlight )
		{
			VMatrix worldToTexture;
			float atten[4], pos[4], tweaks[4];

			const FlashlightState_t &flashlightState = pShaderAPI->GetFlashlightState( worldToTexture );

			float const* pFlashlightColor = flashlightState.m_Color;
			float vPsConst[4] = { pFlashlightColor[0], pFlashlightColor[1], pFlashlightColor[2], 4.5f };
			pShaderAPI->SetPixelShaderConstant(PSREG_FLASHLIGHT_COLOR, vPsConst, 1);

			pShader->BindTexture( SHADER_SAMPLER6, flashlightState.m_pSpotlightTexture, flashlightState.m_nSpotlightTextureFrame );

			atten[0] = flashlightState.m_fConstantAtten;		// Set the flashlight attenuation factors
			atten[1] = flashlightState.m_fLinearAtten;
			atten[2] = flashlightState.m_fQuadraticAtten;
			atten[3] = flashlightState.m_FarZ;
			pShaderAPI->SetPixelShaderConstant( PSREG_FLASHLIGHT_ATTENUATION, atten, 1 );

			pos[0] = flashlightState.m_vecLightOrigin[0];		// Set the flashlight origin
			pos[1] = flashlightState.m_vecLightOrigin[1];
			pos[2] = flashlightState.m_vecLightOrigin[2];
			pShaderAPI->SetPixelShaderConstant( PSREG_FLASHLIGHT_POSITION_RIM_BOOST, pos, 1 );

			pShaderAPI->SetPixelShaderConstant( PSREG_FLASHLIGHT_TO_WORLD_TEXTURE, worldToTexture.Base(), 4 );

			// Tweaks associated with a given flashlight
			tweaks[0] = ShadowFilterFromState( flashlightState );
			tweaks[1] = ShadowAttenFromState( flashlightState );
			pShader->HashShadow2DJitter( flashlightState.m_flShadowJitterSeed, &tweaks[2], &tweaks[3] );
			pShaderAPI->SetPixelShaderConstant( PSREG_ENVMAP_TINT__SHADOW_TWEAKS, tweaks, 1 );
		}
		else
		{
			if ( bUseCSM )
			{
				pShader->BindTexture( SHADER_SAMPLER4, pCascadedDepthTexture );

				VMatrix *worldToTexture0 = (VMatrix *)pShaderAPI->GetIntRenderingParameter( INT_RENDERPARM_CASCADED_MATRIX_ADDRESS_0 );
				pShaderAPI->SetPixelShaderConstant( 22, worldToTexture0->Base(), 4 );

				lightData_Global_t csmData = GetDeferredExt()->GetLightData_Global();
				Vector csmFwd = csmData.vecLight;
				pShaderAPI->SetPixelShaderConstant( 26, csmFwd.Base() );

				Vector csmLight = csmData.light.AsVector3D();
				pShaderAPI->SetPixelShaderConstant( 27, csmLight.Base() );

				Vector csmAmbient = csmData.ambient.AsVector3D();
				pShaderAPI->SetPixelShaderConstant( 28, csmAmbient.Base() );

				float biasVar[2] = { r_csm_slopescalebias.GetFloat(), r_csm_bias.GetFloat() };
				pShaderAPI->SetPixelShaderConstant( 31, biasVar );

				float textureSize[2] = { pCascadedDepthTexture->GetActualWidth(), pCascadedDepthTexture->GetActualHeight() };
				pShaderAPI->SetPixelShaderConstant( 32, textureSize );

				pShaderAPI->SetPixelShaderConstant( 33, GetDeferredExt()->GetLightData_Global().sizes.Base() );
			}
		}
	}
	pShader->Draw();
}


//-----------------------------------------------------------------------------
// Draws the shader
//-----------------------------------------------------------------------------
void DrawLightmappedPBR_DX9( CBaseVSShader *pShader, IMaterialVar** params, IShaderDynamicAPI *pShaderAPI, IShaderShadow* pShaderShadow, bool bHasFlashlight,
				   LightmappedPBR_DX9_Vars_t &info, VertexCompressionType_t vertexCompression, CBasePerMaterialContextData **pContextDataPtr )

{
	DrawLightmappedPBR_DX9_Internal( pShader, params, pShaderAPI,	pShaderShadow, bHasFlashlight, info, vertexCompression, pContextDataPtr );
}
