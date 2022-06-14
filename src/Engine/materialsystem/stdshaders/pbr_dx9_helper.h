#ifndef PBR_DX9_HELPER_H
#define PBR_DX9_HELPER_H
#pragma once

struct PBR_Vars_t
{
	PBR_Vars_t() { memset(this, 0xFF, sizeof(*this)); }

	int baseTexture;
	int baseColor;
	int normalTexture;
	int bumpFrame;
	int bumpTransform;
	int envMap;
	int baseTextureFrame;
	int baseTextureTransform;
	int alphaTestReference;
	int flashlightTexture;
	int flashlightTextureFrame;
	int pbrLookupTexture;
	int mraoTexture;
	//int metalness;
	//int roughness;

	int m_nEnvmapParallax;
	int m_nEnvmapOrigin;
};

void InitParamsPBR_DX9(CBaseVSShader *pShader, IMaterialVar** params,
	const char *pMaterialName, PBR_Vars_t &info);

void InitPBR_DX9(CBaseVSShader *pShader, IMaterialVar** params,
	PBR_Vars_t &info);

void DrawPBR_DX9(CBaseVSShader *pShader, IMaterialVar** params, IShaderDynamicAPI *pShaderAPI,
	IShaderShadow* pShaderShadow,
	PBR_Vars_t &info, VertexCompressionType_t vertexCompression,
	CBasePerMaterialContextData **pContextDataPtr);

#endif // !PBR_DX9_HELPER_H
