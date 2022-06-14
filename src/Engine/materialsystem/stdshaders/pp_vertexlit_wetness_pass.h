#ifndef VERTEXLIT_WETNESS_PASS_H
#define  VERTEXLIT_WETNESS_PASS_H
#pragma once

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
struct VertexLitWetness_DX9_Vars_t
{
	VertexLitWetness_DX9_Vars_t() { memset(this, 0xFF, sizeof(*this)); }

	int m_nWetBaseTexture;
	int m_nWetBaseTextureFrame;
	int m_nWetBaseTextureTransform;
	int m_nWetBumpmap;
	int m_nWetNormalWrinkle;
	int m_nWetNormalStretch;
	int m_nWetBumpFrame;
	int m_nWetBumpTransform;
	int m_nFlashlightTexture;
	int m_nFlashlightTextureFrame;

	int m_nWetPhongExponent;
	int m_nWetPhongTint;
	int m_nWetPhongAlbedoTint;
	int m_nWetPhongExponentTexture;
	int m_nWetPhongWarpTexture;
	int m_nWetPhongBoost;
	int m_nWetPhongFresnelRanges;
	int m_nWetPhongExponentFactor;
	int m_nWetBaseMapAlphaPhongMask;

	// Rim lighting parameters
	int m_nWetRimLight;
	int m_nWetRimLightPower;
	int m_nWetRimLightBoost;
	int m_nWetRimMask;

	int m_nWetInvertPhongMask;
	int m_nWetBlendStrength;
};

void InitParamsVertexLitWetness_DX9(CBaseVSShader* pShader, IMaterialVar** params, const char* pMaterialName, VertexLitWetness_DX9_Vars_t& info);
void InitVertexLitWetness_DX9(CBaseVSShader* pShader, IMaterialVar** params, VertexLitWetness_DX9_Vars_t& info);
void DrawVertexLitWetness_DX9(CBaseVSShader* pShader, IMaterialVar** params, IShaderDynamicAPI* pShaderAPI, IShaderShadow* pShaderShadow,
	VertexLitWetness_DX9_Vars_t& info, VertexCompressionType_t vertexCompression, bool bForceFlashlight = false
);

#endif // !VERTEXLIT_WETNESS_PASS_H
