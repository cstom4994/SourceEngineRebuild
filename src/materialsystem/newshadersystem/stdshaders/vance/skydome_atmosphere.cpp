//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#include "BaseVSShader.h"
#include "convar.h"
#include "skydome_atmosphere_helper.h"
#include "commandbuilder.h"
#include "IDeferredExt.h"

#include "skydome_vs30.inc"
#include "skydome_ps30.inc"

ConVar cl_sky_turbidity("cl_sky_turbidity", "1.9");
static ConVar r_csm_time("r_csm_time", "-1", 0, "-1 = use entity angles, everything else = force"); // HACKHACK: need a better way to get this variable

// HDTV rec. 709 matrix.
static float M_XYZ2RGB[] =
{
	 3.240479f, -0.969256f,  0.055648f,
	-1.53715f,   1.875991f, -0.204043f,
	-0.49853f,   0.041556f,  1.057311f,
};

// Converts color repesentation from CIE XYZ to RGB color-space.
Vector xyzToRgb(const Vector& xyz)
{
	Vector rgb;
	rgb.x = M_XYZ2RGB[0] * xyz.x + M_XYZ2RGB[3] * xyz.y + M_XYZ2RGB[6] * xyz.z;
	rgb.y = M_XYZ2RGB[1] * xyz.x + M_XYZ2RGB[4] * xyz.y + M_XYZ2RGB[7] * xyz.z;
	rgb.z = M_XYZ2RGB[2] * xyz.x + M_XYZ2RGB[5] * xyz.y + M_XYZ2RGB[8] * xyz.z;
	return rgb;
};


// Precomputed luminance of sunlight in XYZ colorspace.
// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
// This table is used for piecewise linear interpolation. Transitions from and to 0.0 at sunset and sunrise are highly inaccurate
static Vector sunLuminanceXYZTable[] = {
	{  0.000000f,  0.000000f,  0.000000f },
	{ 12.703322f, 12.989393f,  9.100411f },
	{ 13.202644f, 13.597814f, 11.524929f },
	{ 13.192974f, 13.597458f, 12.264488f },
	{ 13.132943f, 13.535914f, 12.560032f },
	{ 13.088722f, 13.489535f, 12.692996f },
	{ 13.067827f, 13.467483f, 12.745179f },
	{ 13.069653f, 13.469413f, 12.740822f },
	{ 13.094319f, 13.495428f, 12.678066f },
	{ 13.142133f, 13.545483f, 12.526785f },
	{ 13.201734f, 13.606017f, 12.188001f },
	{ 13.182774f, 13.572725f, 11.311157f },
	{ 12.448635f, 12.672520f,  8.267771f },
	{  0.000000f,  0.000000f,  0.000000f },
};

// Precomputed luminance of sky in the zenith point in XYZ colorspace.
// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
// This table is used for piecewise linear interpolation. Day/night transitions are highly inaccurate.
// The scale of luminance change in Day/night transitions is not preserved.
// Luminance at night was increased to eliminate need the of HDR render.
static Vector skyLuminanceXYZTable[] = {
	{ 0.308f,    0.308f,    0.411f    },
	{ 0.308f,    0.308f,    0.410f    },
	{ 0.301f,    0.301f,    0.402f    },
	{ 0.287f,    0.287f,    0.382f    },
	{ 0.258f,    0.258f,    0.344f    },
	{ 0.258f,    0.258f,    0.344f    },
	{ 0.610f,    0.629f,    1.045f    },
	{ 0.962851f, 1.000000f, 1.747835f },
	{ 0.967787f, 1.000000f, 1.776762f },
	{ 0.970173f, 1.000000f, 1.788413f },
	{ 0.971431f, 1.000000f, 1.794102f },
	{ 0.972099f, 1.000000f, 1.797096f },
	{ 0.972385f, 1.000000f, 1.798389f },
	{ 0.972361f, 1.000000f, 1.798278f },
	{ 0.972020f, 1.000000f, 1.796740f },
	{ 0.971275f, 1.000000f, 1.793407f },
	{ 0.969885f, 1.000000f, 1.787078f },
	{ 0.967216f, 1.000000f, 1.773758f },
	{ 0.961668f, 1.000000f, 1.739891f },
	{ 0.610f,    0.629f,    1.045f    },
	{ 0.264f,    0.264f,    0.352f    },
	{ 0.264f,    0.264f,    0.352f    },
	{ 0.290f,    0.290f,    0.386f    },
	{ 0.303f,    0.303f,    0.404f    },
};


// Turbidity tables. Taken from:
// A. J. Preetham, P. Shirley, and B. Smits. A Practical Analytic Model for Daylight. SIGGRAPH '99
// Coefficients correspond to xyY colorspace.
static Vector ABCDE[] =
{
	{ -0.2592f, -0.2608f, -1.4630f },
	{  0.0008f,  0.0092f,  0.4275f },
	{  0.2125f,  0.2102f,  5.3251f },
	{ -0.8989f, -1.6537f, -2.5771f },
	{  0.0452f,  0.0529f,  0.3703f },
};
static Vector ABCDE_t[] =
{
	{ -0.0193f, -0.0167f,  0.1787f },
	{ -0.0665f, -0.0950f, -0.3554f },
	{ -0.0004f, -0.0079f, -0.0227f },
	{ -0.0641f, -0.0441f,  0.1206f },
	{ -0.0033f, -0.0109f, -0.0670f },
};


static const Vector interpolate(float lowerTime, const Vector& lowerVal, float upperTime, const Vector& upperVal, float time)
{
	const float tt = (time - lowerTime) / (upperTime - lowerTime);
	const Vector result = VectorLerp(lowerVal, upperVal, tt);
	return result;
};

static Vector MultAdd(const Vector& src1, const Vector& src2, const Vector& src3)
{
	Vector tmp;
	tmp.x = src1.x * src2.x + src3.x;
	tmp.y = src1.y * src2.y + src3.y;
	tmp.z = src1.z * src2.z + src3.z;
	return tmp;
}

static void computePerezCoeff(float _turbidity, float* _outPerezCoeff)
{
	const Vector turbidity = { _turbidity, _turbidity, _turbidity };
	for (int ii = 0; ii < 5; ++ii)
	{
		const Vector tmp = MultAdd(ABCDE_t[ii], turbidity, ABCDE[ii]);
		float* out = _outPerezCoeff + 4 * ii;
		out[0] = tmp.x;
		out[1] = tmp.y;
		out[2] = tmp.z;
		out[3] = 0.0f;
	}
}

class CSkydome_Context : public CBasePerMaterialContextData
{
public:
	CCommandBufferBuilder< CFixedCommandStorageBuffer< 800 > > m_SemiStaticCmdsOut;
	bool m_bFastPath;

};

BEGIN_VS_SHADER(SKYDOME_ATMOSPHERE, "SKY")

BEGIN_SHADER_PARAMS
END_SHADER_PARAMS

void SetupVars(Skydome_Vars_t& info)
{
}

SHADER_INIT_PARAMS()
{
	Skydome_Vars_t info;
	SetupVars(info);
	InitParamsSkydome(this, params, pMaterialName, info);
}

SHADER_FALLBACK
{
	return 0;
}

SHADER_INIT
{
	Skydome_Vars_t info;
	SetupVars(info);
	InitSkydome(this, params, info);
}


SHADER_DRAW
{

	CSkydome_Context* pContextData = reinterpret_cast<CSkydome_Context*> (*pContextDataPtr);
	if (!pContextData)
	{
		pContextData = new CSkydome_Context;
		*pContextDataPtr = pContextData;
	}

	if (IsSnapshotting())
	{
		pShaderShadow->EnableSRGBWrite(true);
		unsigned int flags = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_FORMAT_COMPRESSED;
		pShaderShadow->VertexShaderVertexFormat(flags, 1, 0, 0);

		DECLARE_STATIC_VERTEX_SHADER(skydome_vs30);
		SET_STATIC_VERTEX_SHADER(skydome_vs30);

		// Assume we're only going to get in here if we support 2b
		DECLARE_STATIC_PIXEL_SHADER(skydome_ps30);
		SET_STATIC_PIXEL_SHADER_COMBO(CONVERT_TO_SRGB, 0);
		SET_STATIC_PIXEL_SHADER(skydome_ps30);

		// HACK HACK HACK - enable alpha writes all the time so that we have them for underwater stuff
		pShaderShadow->EnableAlphaWrites(true);
	}
	else // not snapshotting -- begin dynamic state
	{
		DECLARE_DYNAMIC_VERTEX_SHADER(skydome_vs30);
		SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, (int)vertexCompression);
		SET_DYNAMIC_VERTEX_SHADER(skydome_vs30);

		DECLARE_DYNAMIC_PIXEL_SHADER(skydome_ps30);
		SET_DYNAMIC_PIXEL_SHADER_COMBO(RENDER_SKY, 1);
		SET_DYNAMIC_PIXEL_SHADER(skydome_ps30);

		/*float flthickness[4];
		flthickness[0] = cl_sky_thickness.GetFloat();
		flthickness[1] = flthickness[2] = flthickness[3] = flthickness[0];
		pShaderAPI->SetPixelShaderConstant(PSREG_CONSTANT_04, flthickness);

		float flcoverage[4];
		flcoverage[0] = cl_sky_coverage.GetFloat();
		flcoverage[1] = flcoverage[2] = flcoverage[3] = flcoverage[0];
		pShaderAPI->SetPixelShaderConstant(PSREG_CONSTANT_05, flcoverage);

		float flSunPos[4];
		UTIL_StringToFloatArray(flSunPos, 4, cl_sky_SunPos.GetString());
		pShaderAPI->SetPixelShaderConstant(PSREG_CONSTANT_06, flSunPos);

		float flwindspeed[4];
		UTIL_StringToFloatArray(flwindspeed, 4, cl_sky_windspeed.GetString());
		pShaderAPI->SetPixelShaderConstant(PSREG_CONSTANT_07, flwindspeed);
		*/

		float time = GetDeferredExt()->GetCurrentTime();
		time = clamp(fmod(time, 24.0f), 0.0f, 23.0f);
		float lowerTime = clamp(fmod(floor(time) - 1, 24.0f), 0.0f, 23.0f);
		float upperTime = clamp(fmod(ceil(time), 24.0f), 0.0f, 23.0f);
		Vector lowerVal = skyLuminanceXYZTable[(int)lowerTime];
		Vector upperVal = skyLuminanceXYZTable[(int)upperTime];
		Vector skyLuminance = interpolate(lowerTime, lowerVal, upperTime, upperVal, time);

		pShaderAPI->SetPixelShaderConstant(0, GetDeferredExt()->GetLightData_Global().vecLight.Base());
		pShaderAPI->SetPixelShaderConstant(1, skyLuminance.Base());

		float exposition[4] = { 0.02f, 3.0f, 0.1f, time };
		pShaderAPI->SetPixelShaderConstant(2, exposition);

		float turbidity = cl_sky_turbidity.GetFloat();
		float perezCoeff[4 * 5];
		computePerezCoeff(turbidity, perezCoeff);
		pShaderAPI->SetPixelShaderConstant(3, perezCoeff, 5);

		float flTime[4];
		flTime[0] = pShaderAPI->CurrentTime();
		flTime[1] = flTime[2] = flTime[3] = flTime[0];
		pShaderAPI->SetPixelShaderConstant(8, flTime);
	}
	
	Draw();
}

END_SHADER

