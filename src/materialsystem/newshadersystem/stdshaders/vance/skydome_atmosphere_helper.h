//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#ifndef EXAMPLE_MODEL_DX9_HELPER_H
#define EXAMPLE_MODEL_DX9_HELPER_H

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
struct Skydome_Vars_t
{
	Skydome_Vars_t() { memset( this, 0xFF, sizeof(*this) ); }

	int m_nLUTTexture;
	int m_nFlashlightTexture;
	int m_nFlashlightTextureFrame;
};

void InitParamsSkydome( CBaseVSShader *pShader, IMaterialVar** params,
						 const char *pMaterialName, Skydome_Vars_t &info );

void InitSkydome( CBaseVSShader *pShader, IMaterialVar** params, 
				   Skydome_Vars_t &info );

void DrawSkydome( CBaseVSShader *pShader, IMaterialVar** params, IShaderDynamicAPI *pShaderAPI,
				   IShaderShadow* pShaderShadow,
				   Skydome_Vars_t &info, VertexCompressionType_t vertexCompression,
				   CBasePerMaterialContextData **pContextDataPtr );

#endif // EXAMPLE_MODEL_DX9_HELPER_H
