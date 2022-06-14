#include "BaseVSShader.h"

#include "pp_skymask_vs20.inc"
#include "pp_skymask_ps20.inc"

BEGIN_VS_SHADER(PP_FILL_SKYMASK, "")
BEGIN_SHADER_PARAMS
SHADER_PARAM(COMBINEMODE, SHADER_PARAM_TYPE_BOOL, "", "")
END_SHADER_PARAMS

SHADER_INIT
{
	if (params[COMBINEMODE]->GetIntValue())
		LoadTexture(BASETEXTURE);
}

SHADER_FALLBACK
{
	return 0;
}

SHADER_DRAW
{
	const bool bCombineMode = !!params[COMBINEMODE]->GetIntValue();

//if (!bCombineMode)
{
	SHADOW_STATE
	{
		pShaderShadow->SetDefaultState();

		pShaderShadow->EnableDepthWrites(false);
		pShaderShadow->EnableDepthTest(false);
		pShaderShadow->EnableColorWrites(false);
		pShaderShadow->EnableAlphaWrites(true);
		pShaderShadow->EnableCulling(false);

		pShaderShadow->VertexShaderVertexFormat(VERTEX_POSITION, 1, 0, 0);

		if (bCombineMode)
			pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);

		pp_skymask_vs20_Static_Index index_vs;
		index_vs.SetDRAWWHITE(false);
		index_vs.SetCOMBINE(bCombineMode);
		pp_skymask_ps20_Static_Index index_ps;
		index_ps.SetDRAWWHITE(false);
		index_ps.SetCOMBINE(bCombineMode);

		pShaderShadow->SetVertexShader("pp_skymask_vs20", index_vs.GetIndex());
		pShaderShadow->SetPixelShader("pp_skymask_ps20", index_ps.GetIndex());
	}
		DYNAMIC_STATE
	{
		pShaderAPI->SetDefaultState();

		pShaderAPI->SetVertexShaderIndex();
		pShaderAPI->SetPixelShaderIndex(0);

		if (bCombineMode)
			BindTexture(SHADER_SAMPLER0, BASETEXTURE);
	}

	Draw();
}

		SHADOW_STATE
		{
			pShaderShadow->SetDefaultState();

			pShaderShadow->EnableDepthWrites(false);
			pShaderShadow->EnableDepthTest(true);
			pShaderShadow->EnableColorWrites(false);
			pShaderShadow->EnableAlphaWrites(true);
			pShaderShadow->EnableCulling(false);
			pShaderShadow->VertexShaderVertexFormat(VERTEX_POSITION, 1, 0, 0);

			if (bCombineMode)
				pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);

			pp_skymask_vs20_Static_Index index_vs;
			index_vs.SetDRAWWHITE(true);
			index_vs.SetCOMBINE(bCombineMode);
			pp_skymask_ps20_Static_Index index_ps;
			index_ps.SetDRAWWHITE(true);
			index_ps.SetCOMBINE(bCombineMode);

			pShaderShadow->SetVertexShader("pp_skymask_vs20", index_vs.GetIndex());
			pShaderShadow->SetPixelShader("pp_skymask_ps20", index_ps.GetIndex());
		}
		DYNAMIC_STATE
		{
			pShaderAPI->SetDefaultState();

			pShaderAPI->SetVertexShaderIndex();
			pShaderAPI->SetPixelShaderIndex(0);

			if (bCombineMode)
				BindTexture(SHADER_SAMPLER0, BASETEXTURE);
		}

		Draw();
}

END_SHADER