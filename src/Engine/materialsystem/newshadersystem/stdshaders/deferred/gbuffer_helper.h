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

class CGBuffer_Context : public CBasePerMaterialContextData
{
public:

	CGBuffer_Context()
	{
		m_iAllocated = -1;
		m_piCommandArray = NULL;
	};

	~CGBuffer_Context()
	{
		if (m_piCommandArray != NULL)
		{
			for (int i = 0; i <= m_iAllocated; i++)
				delete[] m_piCommandArray[i];

			delete[] m_piCommandArray;
		}
	};

	void SetCommands(uint8 * p_iCmd)
	{

		uint8** pNewCmds = new uint8 * [1];
		Q_memset(pNewCmds, 0, sizeof(uint8*) * (1));

		if (m_piCommandArray != NULL)
		{
			Assert(m_iAllocated >= 0);

			Q_memcpy(pNewCmds, m_piCommandArray, sizeof(uint8*) * (m_iAllocated + 1));
			delete[] m_piCommandArray;
		}

		m_piCommandArray = pNewCmds;
		m_iAllocated = 0;

		delete[] m_piCommandArray[0];
		m_piCommandArray[0] = p_iCmd;
	};

	uint8* GetCommands()
	{
		return m_piCommandArray[0];
	}

	bool HasCommands()
	{
		return m_piCommandArray[0] != NULL;
	}

private:

	int m_iAllocated;

	uint8** m_piCommandArray;
};

struct DrawDeferredMesh_Vars_t
{
	DrawDeferredMesh_Vars_t() { memset(this, 0xFF, sizeof(*this)); }

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
};

void InitParamsDeferredMesh(CBaseVSShader* pShader, IMaterialVar** params,
	const char* pMaterialName, DrawDeferredMesh_Vars_t& info);

void InitDeferredMesh(CBaseVSShader* pShader, IMaterialVar** params, DrawDeferredMesh_Vars_t& info);

void DrawGBuffer(CBaseVSShader* pShader, IMaterialVar** params, IShaderDynamicAPI* pShaderAPI,
	IShaderShadow* pShaderShadow, VertexCompressionType_t vertexCompression,
	CBasePerMaterialContextData** pContextDataPtr, DrawDeferredMesh_Vars_t& info);

#endif // GLOBAL_LIGHT_HELPER_H
