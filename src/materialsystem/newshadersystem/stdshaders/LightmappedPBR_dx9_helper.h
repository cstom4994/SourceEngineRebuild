//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#ifndef EXAMPLE_MODEL_DX9_HELPER_H
#define EXAMPLE_MODEL_DX9_HELPER_H

#include <string.h>

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class CBaseVSShader;
class IMaterialVar;
class IShaderDynamicAPI;
class IShaderShadow;

//-----------------------------------------------------------------------------
// Init params/ init/ draw methods
//-----------------------------------------------------------------------------
struct LightmappedPBR_DX9_Vars_t
{
	LightmappedPBR_DX9_Vars_t() { memset( this, 0xFF, sizeof(*this) ); }

	int m_nBaseTexture;
	int m_nBaseTextureFrame;
	int m_nBaseTextureTransform;
	int m_nAlphaTestReference;
	int m_nRoughness;
	int m_nMetallic;
	int m_nAO;
	int m_nEmissive;
	int m_nEnvmap;
	int m_nBumpmap;
	int m_nFlashlightTexture;
	int m_nFlashlightTextureFrame;
	int m_nBRDF;
	int m_nUseSmoothness;
	int m_nSeamlessMappingScale;

	int m_nEnvmapOrigin;
	int m_nEnvmapRadius;
};

void InitParamsLightmappedPBR_DX9( CBaseVSShader *pShader, IMaterialVar** params,
						 const char *pMaterialName, LightmappedPBR_DX9_Vars_t &info );

void InitLightmappedPBR_DX9( CBaseVSShader *pShader, IMaterialVar** params, 
				   LightmappedPBR_DX9_Vars_t &info );

void DrawLightmappedPBR_DX9( CBaseVSShader *pShader, IMaterialVar** params, IShaderDynamicAPI *pShaderAPI,
				   IShaderShadow* pShaderShadow, bool bHasFlashlight,
				   LightmappedPBR_DX9_Vars_t &info, VertexCompressionType_t vertexCompression,
				   CBasePerMaterialContextData **pContextDataPtr );

#endif // EXAMPLE_MODEL_DX9_HELPER_H
