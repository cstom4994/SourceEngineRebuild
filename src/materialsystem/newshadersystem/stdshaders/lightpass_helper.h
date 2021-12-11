//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#ifndef GLOBAL_LIGHT_HELPER_H
#define GLOBAL_LIGHT_HELPER_H

#include <string.h>

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class CBaseVSShader;
class IMaterialVar;
class IShaderDynamicAPI;
class IShaderShadow;

struct DrawLightPass_Vars_t
{
	DrawLightPass_Vars_t() { memset(this, 0xFF, sizeof(*this)); }

	int m_nBaseTexture;
	int m_nBaseTextureFrame;
	int m_nBaseTextureTransform;
	int m_nAlphaTestReference;
	int m_nBumpmap;
	int m_nBumpmap2;
	int m_nBumpFrame2;
	int m_nBumpTransform2;
	int m_nBaseTexture2;
	int m_nBaseTexture2Frame;
	int m_nSeamlessMappingScale;
	int m_nRoughness;
	int m_nMetallic;
	int m_nNoise;

	// config
	bool bModel;
	int m_nUseSmoothness;
};

void InitParamsLightPass(CBaseVSShader* pShader, IMaterialVar** params,
	const char* pMaterialName, DrawLightPass_Vars_t& info);

void InitLightPass(CBaseVSShader* pShader, IMaterialVar** params, DrawLightPass_Vars_t& info);

void DrawLightPass(CBaseVSShader* pShader, IMaterialVar** params, IShaderDynamicAPI* pShaderAPI,
	IShaderShadow* pShaderShadow, VertexCompressionType_t vertexCompression,
	CBasePerMaterialContextData** pContextDataPtr, DrawLightPass_Vars_t& info);

#endif // GLOBAL_LIGHT_HELPER_H
