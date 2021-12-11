//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#include "BaseVSShader.h"
#include "convar.h"
#include "globallight_mesh_helper.h"

BEGIN_VS_SHADER( Global_Light, "Help for Global Light" )
	BEGIN_SHADER_PARAMS
	END_SHADER_PARAMS

	void SetupVars( GlobalLight_Vars_t& info )
	{
		info.m_nBaseTexture = BASETEXTURE;
		info.m_nBaseTextureFrame = FRAME;
		info.m_nBaseTextureTransform = BASETEXTURETRANSFORM;
		info.m_nFlashlightTexture = FLASHLIGHTTEXTURE;
		info.m_nFlashlightTextureFrame = FLASHLIGHTTEXTUREFRAME;
	}

	SHADER_INIT_PARAMS()
	{
		InitParamsGlobalLight( this, params, pMaterialName );
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
		GlobalLight_Vars_t info;
		SetupVars( info );
		InitGlobalLight( this, params, info );
	}

	SHADER_DRAW
	{
		GlobalLight_Vars_t info;
		SetupVars( info );
		DrawGlobalLight( this, params, pShaderAPI, pShaderShadow, info, vertexCompression, pContextDataPtr );
	}

END_SHADER

