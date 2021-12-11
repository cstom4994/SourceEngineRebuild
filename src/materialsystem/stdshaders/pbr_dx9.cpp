//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#include "BaseVSShader.h"

#include "pbr_dx9_helper.h"
#include "cloak_blended_pass_helper.h"
#include "emissive_scroll_blended_pass_helper.h"
#include "flesh_interior_blended_pass_helper.h"


//DEFINE_FALLBACK_SHADER( UnlitGeneric, PBR )
BEGIN_VS_SHADER( PBR, "PBR shader" )

BEGIN_SHADER_PARAMS
	SHADER_PARAM(ALPHATESTREFERENCE, SHADER_PARAM_TYPE_FLOAT, "0.0", "")
	//SHADER_PARAM(METALNESS, SHADER_PARAM_TYPE_FLOAT, "1.0", "Sets the metalness of the material.")
	//SHADER_PARAM(ROUGHNESS, SHADER_PARAM_TYPE_FLOAT, "1.0", "Sets the roughness of the material.")
	SHADER_PARAM(ENVMAP, SHADER_PARAM_TYPE_ENVMAP, "", "Set the cubemap for this material.")
	SHADER_PARAM(MRAOTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "Texture with metalness in R, roughness in G, ambient occlusion in B.")
	SHADER_PARAM_FLAGS(PBRLOOKUP, SHADER_PARAM_TYPE_TEXTURE, "dev/pbr_lookup", "The PBR lookup texture, don't change this.", SHADER_PARAM_NOT_EDITABLE)
	SHADER_PARAM( BUMPMAP, SHADER_PARAM_TYPE_TEXTURE, "models/shadertest/shader1_normal", "bump map" )
	SHADER_PARAM( BUMPFRAME, SHADER_PARAM_TYPE_INTEGER, "0", "frame number for $bumpmap" )
	SHADER_PARAM( BUMPTRANSFORM, SHADER_PARAM_TYPE_MATRIX, "center .5 .5 scale 1 1 rotate 0 translate 0 0", "$bumpmap texcoord transform" )

	// Cloak Pass
	SHADER_PARAM(CLOAKPASSENABLED, SHADER_PARAM_TYPE_BOOL, "0", "Enables cloak render in a second pass")
	SHADER_PARAM(CLOAKFACTOR, SHADER_PARAM_TYPE_FLOAT, "0.0", "")
	SHADER_PARAM(CLOAKCOLORTINT, SHADER_PARAM_TYPE_COLOR, "[1 1 1]", "Cloak color tint")
	SHADER_PARAM(REFRACTAMOUNT, SHADER_PARAM_TYPE_FLOAT, "2", "")

	// Emissive Scroll Pass
	SHADER_PARAM(EMISSIVEBLENDENABLED, SHADER_PARAM_TYPE_BOOL, "0", "Enable emissive blend pass")
	SHADER_PARAM(EMISSIVEBLENDBASETEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "self-illumination map")
	SHADER_PARAM(EMISSIVEBLENDSCROLLVECTOR, SHADER_PARAM_TYPE_VEC2, "[0.11 0.124]", "Emissive scroll vec")
	SHADER_PARAM(EMISSIVEBLENDSTRENGTH, SHADER_PARAM_TYPE_FLOAT, "1.0", "Emissive blend strength")
	SHADER_PARAM(EMISSIVEBLENDTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "self-illumination map")
	SHADER_PARAM(EMISSIVEBLENDTINT, SHADER_PARAM_TYPE_COLOR, "[1 1 1]", "Self-illumination tint")
	SHADER_PARAM(EMISSIVEBLENDFLOWTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "flow map")

	// Flesh Interior Pass
	SHADER_PARAM(FLESHINTERIORENABLED, SHADER_PARAM_TYPE_BOOL, "0", "Enable Flesh interior blend pass")
	SHADER_PARAM(FLESHINTERIORTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "Flesh color texture")
	SHADER_PARAM(FLESHINTERIORNOISETEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "Flesh noise texture")
	SHADER_PARAM(FLESHBORDERTEXTURE1D, SHADER_PARAM_TYPE_TEXTURE, "", "Flesh border 1D texture")
	SHADER_PARAM(FLESHNORMALTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "Flesh normal texture")
	SHADER_PARAM(FLESHSUBSURFACETEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "Flesh subsurface texture")
	SHADER_PARAM(FLESHCUBETEXTURE, SHADER_PARAM_TYPE_TEXTURE, "", "Flesh cubemap texture")
	SHADER_PARAM(FLESHBORDERNOISESCALE, SHADER_PARAM_TYPE_FLOAT, "1.5", "Flesh Noise UV scalar for border")
	SHADER_PARAM(FLESHDEBUGFORCEFLESHON, SHADER_PARAM_TYPE_BOOL, "0", "Flesh Debug full flesh")
	SHADER_PARAM(FLESHEFFECTCENTERRADIUS1, SHADER_PARAM_TYPE_VEC4, "[0 0 0 0.001]", "Flesh effect center and radius")
	SHADER_PARAM(FLESHEFFECTCENTERRADIUS2, SHADER_PARAM_TYPE_VEC4, "[0 0 0 0.001]", "Flesh effect center and radius")
	SHADER_PARAM(FLESHEFFECTCENTERRADIUS3, SHADER_PARAM_TYPE_VEC4, "[0 0 0 0.001]", "Flesh effect center and radius")
	SHADER_PARAM(FLESHEFFECTCENTERRADIUS4, SHADER_PARAM_TYPE_VEC4, "[0 0 0 0.001]", "Flesh effect center and radius")
	SHADER_PARAM(FLESHSUBSURFACETINT, SHADER_PARAM_TYPE_COLOR, "[1 1 1]", "Subsurface Color")
	SHADER_PARAM(FLESHBORDERWIDTH, SHADER_PARAM_TYPE_FLOAT, "0.3", "Flesh border")
	SHADER_PARAM(FLESHBORDERSOFTNESS, SHADER_PARAM_TYPE_FLOAT, "0.42", "Flesh border softness (> 0.0 && <= 0.5)")
	SHADER_PARAM(FLESHBORDERTINT, SHADER_PARAM_TYPE_COLOR, "[1 1 1]", "Flesh border Color")
	SHADER_PARAM(FLESHGLOBALOPACITY, SHADER_PARAM_TYPE_FLOAT, "1.0", "Flesh global opacity")
	SHADER_PARAM(FLESHGLOSSBRIGHTNESS, SHADER_PARAM_TYPE_FLOAT, "0.66", "Flesh gloss brightness")
	SHADER_PARAM(FLESHSCROLLSPEED, SHADER_PARAM_TYPE_FLOAT, "1.0", "Flesh scroll speed")

	SHADER_PARAM(ENVMAPPARALLAX, SHADER_PARAM_TYPE_MATRIX, "[1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1]", "")
	SHADER_PARAM(ENVMAPORIGIN, SHADER_PARAM_TYPE_VEC3, "[0 0 0]", "The world space position of the env_cubemap being corrected")

	SHADER_PARAM(TIME, SHADER_PARAM_TYPE_FLOAT, "0.0", "Needs CurrentTime Proxy")
END_SHADER_PARAMS

	void SetupVars( PBR_Vars_t& info )
	{
		info.baseTexture = BASETEXTURE;
		info.baseColor = COLOR;
		info.normalTexture = BUMPMAP;
		info.bumpFrame = BUMPFRAME;
		info.bumpTransform = BUMPTRANSFORM;
		info.baseTextureFrame = FRAME;
		info.baseTextureTransform = BASETEXTURETRANSFORM;
		info.alphaTestReference = ALPHATESTREFERENCE;
		//info.metalness = METALNESS;
		//info.roughness = ROUGHNESS;
		info.flashlightTexture = FLASHLIGHTTEXTURE;
		info.flashlightTextureFrame = FLASHLIGHTTEXTUREFRAME;
		info.envMap = ENVMAP;
		info.pbrLookupTexture = PBRLOOKUP;
		info.mraoTexture = MRAOTEXTURE;
		info.m_nEnvmapOrigin = ENVMAPORIGIN;
		info.m_nEnvmapParallax = ENVMAPPARALLAX;
	}

// Cloak Pass
void SetupVarsCloakBlendedPass(CloakBlendedPassVars_t &info)
{
	info.m_nCloakFactor = CLOAKFACTOR;
	info.m_nCloakColorTint = CLOAKCOLORTINT;
	info.m_nRefractAmount = REFRACTAMOUNT;

	// Delete these lines if not bump mapping!
	info.m_nBumpmap = BUMPMAP;
	info.m_nBumpFrame = BUMPFRAME;
	info.m_nBumpTransform = BUMPTRANSFORM;
}

// Emissive Scroll Pass
void SetupVarsEmissiveScrollBlendedPass(EmissiveScrollBlendedPassVars_t &info)
{
	info.m_nBlendStrength = EMISSIVEBLENDSTRENGTH;
	info.m_nBaseTexture = EMISSIVEBLENDBASETEXTURE;
	info.m_nFlowTexture = EMISSIVEBLENDFLOWTEXTURE;
	info.m_nEmissiveTexture = EMISSIVEBLENDTEXTURE;
	info.m_nEmissiveTint = EMISSIVEBLENDTINT;
	info.m_nEmissiveScrollVector = EMISSIVEBLENDSCROLLVECTOR;
	info.m_nTime = TIME;
}

// Flesh Interior Pass
void SetupVarsFleshInteriorBlendedPass(FleshInteriorBlendedPassVars_t &info)
{
	info.m_nFleshTexture = FLESHINTERIORTEXTURE;
	info.m_nFleshNoiseTexture = FLESHINTERIORNOISETEXTURE;
	info.m_nFleshBorderTexture1D = FLESHBORDERTEXTURE1D;
	info.m_nFleshNormalTexture = FLESHNORMALTEXTURE;
	info.m_nFleshSubsurfaceTexture = FLESHSUBSURFACETEXTURE;
	info.m_nFleshCubeTexture = FLESHCUBETEXTURE;

	info.m_nflBorderNoiseScale = FLESHBORDERNOISESCALE;
	info.m_nflDebugForceFleshOn = FLESHDEBUGFORCEFLESHON;
	info.m_nvEffectCenterRadius1 = FLESHEFFECTCENTERRADIUS1;
	info.m_nvEffectCenterRadius2 = FLESHEFFECTCENTERRADIUS2;
	info.m_nvEffectCenterRadius3 = FLESHEFFECTCENTERRADIUS3;
	info.m_nvEffectCenterRadius4 = FLESHEFFECTCENTERRADIUS4;

	info.m_ncSubsurfaceTint = FLESHSUBSURFACETINT;
	info.m_nflBorderWidth = FLESHBORDERWIDTH;
	info.m_nflBorderSoftness = FLESHBORDERSOFTNESS;
	info.m_ncBorderTint = FLESHBORDERTINT;
	info.m_nflGlobalOpacity = FLESHGLOBALOPACITY;
	info.m_nflGlossBrightness = FLESHGLOSSBRIGHTNESS;
	info.m_nflScrollSpeed = FLESHSCROLLSPEED;

	info.m_nTime = TIME;
}

bool NeedsPowerOfTwoFrameBufferTexture(IMaterialVar **params, bool bCheckSpecificToThisFrame) const
{
	if (params[CLOAKPASSENABLED]->GetIntValue()) // If material supports cloaking
	{
		if (bCheckSpecificToThisFrame == false) // For setting model flag at load time
			return true;
		else if ((params[CLOAKFACTOR]->GetFloatValue() > 0.0f) && (params[CLOAKFACTOR]->GetFloatValue() < 1.0f)) // Per-frame check
			return true;
		// else, not cloaking this frame, so check flag2 in case the base material still needs it
	}

	// Check flag2 if not drawing cloak pass
	return IS_FLAG2_SET(MATERIAL_VAR2_NEEDS_POWER_OF_TWO_FRAME_BUFFER_TEXTURE);
}

bool IsTranslucent(IMaterialVar **params) const
{
	if (params[CLOAKPASSENABLED]->GetIntValue()) // If material supports cloaking
	{
		if ((params[CLOAKFACTOR]->GetFloatValue() > 0.0f) && (params[CLOAKFACTOR]->GetFloatValue() < 1.0f)) // Per-frame check
			return true;
		// else, not cloaking this frame, so check flag in case the base material still needs it
	}

	// Check flag if not drawing cloak pass
	return IS_FLAG_SET(MATERIAL_VAR_TRANSLUCENT);
}

	SHADER_INIT_PARAMS()
	{
		PBR_Vars_t info;
		SetupVars(info);

		InitParamsPBR_DX9(this, params, pMaterialName, info);

		// Cloak Pass
		if (!params[CLOAKPASSENABLED]->IsDefined())
		{
			params[CLOAKPASSENABLED]->SetIntValue(0);
		}
		else if (params[CLOAKPASSENABLED]->GetIntValue())
		{
			CloakBlendedPassVars_t info;
			SetupVarsCloakBlendedPass(info);
			InitParamsCloakBlendedPass(this, params, pMaterialName, info);
		}

		// Emissive Scroll Pass
		if (!params[EMISSIVEBLENDENABLED]->IsDefined())
		{
			params[EMISSIVEBLENDENABLED]->SetIntValue(0);
		}
		else if (params[EMISSIVEBLENDENABLED]->GetIntValue())
		{
			EmissiveScrollBlendedPassVars_t info;
			SetupVarsEmissiveScrollBlendedPass(info);
			InitParamsEmissiveScrollBlendedPass(this, params, pMaterialName, info);
		}

		// Flesh Interior Pass
		if (!params[FLESHINTERIORENABLED]->IsDefined())
		{
			params[FLESHINTERIORENABLED]->SetIntValue(0);
		}
		else if (params[FLESHINTERIORENABLED]->GetIntValue())
		{
			FleshInteriorBlendedPassVars_t info;
			SetupVarsFleshInteriorBlendedPass(info);
			InitParamsFleshInteriorBlendedPass(this, params, pMaterialName, info);
		}
	}



	SHADER_FALLBACK
	{
		if (!g_pHardwareConfig->SupportsShaderModel_3_0())
		{
			if (IS_FLAG_SET(MATERIAL_VAR_MODEL))
				return "PP_VertexLitGeneric";
			else
				return "PP_LightmappedGeneric";
		}

		return 0;
	}

	SHADER_INIT
	{
		PBR_Vars_t info;
		SetupVars( info );

		InitPBR_DX9(this, params, info);

		// Cloak Pass
		if (params[CLOAKPASSENABLED]->GetIntValue())
		{
			CloakBlendedPassVars_t info;
			SetupVarsCloakBlendedPass(info);
			InitCloakBlendedPass(this, params, info);
		}

		// Emissive Scroll Pass
		if (params[EMISSIVEBLENDENABLED]->GetIntValue())
		{
			EmissiveScrollBlendedPassVars_t info;
			SetupVarsEmissiveScrollBlendedPass(info);
			InitEmissiveScrollBlendedPass(this, params, info);
		}

		// Flesh Interior Pass
		if (params[FLESHINTERIORENABLED]->GetIntValue())
		{
			FleshInteriorBlendedPassVars_t info;
			SetupVarsFleshInteriorBlendedPass(info);
			InitFleshInteriorBlendedPass(this, params, info);
		}
	}

	SHADER_DRAW
	{
		// Skip the standard rendering if cloak pass is fully opaque
			bool bDrawStandardPass = true;
			if (params[CLOAKPASSENABLED]->GetIntValue() && (pShaderShadow == NULL)) // && not snapshotting
			{
				CloakBlendedPassVars_t info;
				SetupVarsCloakBlendedPass(info);
				if (CloakBlendedPassIsFullyOpaque(params, info))
				{
					bDrawStandardPass = false;
				}
			}

			// Standard rendering pass
			if (bDrawStandardPass)
			{
				PBR_Vars_t info;
				SetupVars(info);

				DrawPBR_DX9(this, params, pShaderAPI, pShaderShadow, info, vertexCompression, pContextDataPtr);
			}
			else
			{
				// Skip this pass!
				Draw(false);
			}

			// Cloak Pass
			if (params[CLOAKPASSENABLED]->GetIntValue())
			{
				// If ( snapshotting ) or ( we need to draw this frame )
				if ((pShaderShadow != NULL) || ((params[CLOAKFACTOR]->GetFloatValue() > 0.0f) && (params[CLOAKFACTOR]->GetFloatValue() < 1.0f)))
				{
					CloakBlendedPassVars_t info;
					SetupVarsCloakBlendedPass(info);
					DrawCloakBlendedPass(this, params, pShaderAPI, pShaderShadow, info, vertexCompression);
				}
				else // We're not snapshotting and we don't need to draw this frame
				{
					// Skip this pass!
					Draw(false);
				}
			}

			// Emissive Scroll Pass
			if (params[EMISSIVEBLENDENABLED]->GetIntValue())
			{
				// If ( snapshotting ) or ( we need to draw this frame )
				if ((pShaderShadow != NULL) || (params[EMISSIVEBLENDSTRENGTH]->GetFloatValue() > 0.0f))
				{
					EmissiveScrollBlendedPassVars_t info;
					SetupVarsEmissiveScrollBlendedPass(info);
					DrawEmissiveScrollBlendedPass(this, params, pShaderAPI, pShaderShadow, info, vertexCompression);
				}
				else // We're not snapshotting and we don't need to draw this frame
				{
					// Skip this pass!
					Draw(false);
				}
			}

			// Flesh Interior Pass
			if (params[FLESHINTERIORENABLED]->GetIntValue())
			{
				// If ( snapshotting ) or ( we need to draw this frame )
				if ((pShaderShadow != NULL) || (true))
				{
					FleshInteriorBlendedPassVars_t info;
					SetupVarsFleshInteriorBlendedPass(info);
					DrawFleshInteriorBlendedPass(this, params, pShaderAPI, pShaderShadow, info, vertexCompression);
				}
				else // We're not snapshotting and we don't need to draw this frame
				{
					// Skip this pass!
					Draw(false);
				}
			}
	}

END_SHADER

