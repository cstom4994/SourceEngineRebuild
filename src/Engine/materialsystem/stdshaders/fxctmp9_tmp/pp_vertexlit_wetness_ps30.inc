#include "shaderlib/cshader.h"
class pp_vertexlit_wetness_ps30_Static_Index
{
private:
	int m_nCONVERT_TO_SRGB;
#ifdef _DEBUG
	bool m_bCONVERT_TO_SRGB;
#endif
public:
	void SetCONVERT_TO_SRGB( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nCONVERT_TO_SRGB = i;
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = true;
#endif
	}
	void SetCONVERT_TO_SRGB( bool i )
	{
		m_nCONVERT_TO_SRGB = i ? 1 : 0;
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = true;
#endif
	}
private:
	int m_nFLASHLIGHT;
#ifdef _DEBUG
	bool m_bFLASHLIGHT;
#endif
public:
	void SetFLASHLIGHT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLASHLIGHT = i;
#ifdef _DEBUG
		m_bFLASHLIGHT = true;
#endif
	}
	void SetFLASHLIGHT( bool i )
	{
		m_nFLASHLIGHT = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLASHLIGHT = true;
#endif
	}
private:
	int m_nPHONGWARPTEXTURE;
#ifdef _DEBUG
	bool m_bPHONGWARPTEXTURE;
#endif
public:
	void SetPHONGWARPTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPHONGWARPTEXTURE = i;
#ifdef _DEBUG
		m_bPHONGWARPTEXTURE = true;
#endif
	}
	void SetPHONGWARPTEXTURE( bool i )
	{
		m_nPHONGWARPTEXTURE = i ? 1 : 0;
#ifdef _DEBUG
		m_bPHONGWARPTEXTURE = true;
#endif
	}
private:
	int m_nWRINKLEMAP;
#ifdef _DEBUG
	bool m_bWRINKLEMAP;
#endif
public:
	void SetWRINKLEMAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nWRINKLEMAP = i;
#ifdef _DEBUG
		m_bWRINKLEMAP = true;
#endif
	}
	void SetWRINKLEMAP( bool i )
	{
		m_nWRINKLEMAP = i ? 1 : 0;
#ifdef _DEBUG
		m_bWRINKLEMAP = true;
#endif
	}
private:
	int m_nRIMLIGHT;
#ifdef _DEBUG
	bool m_bRIMLIGHT;
#endif
public:
	void SetRIMLIGHT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nRIMLIGHT = i;
#ifdef _DEBUG
		m_bRIMLIGHT = true;
#endif
	}
	void SetRIMLIGHT( bool i )
	{
		m_nRIMLIGHT = i ? 1 : 0;
#ifdef _DEBUG
		m_bRIMLIGHT = true;
#endif
	}
private:
	int m_nFLASHLIGHTDEPTHFILTERMODE;
#ifdef _DEBUG
	bool m_bFLASHLIGHTDEPTHFILTERMODE;
#endif
public:
	void SetFLASHLIGHTDEPTHFILTERMODE( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nFLASHLIGHTDEPTHFILTERMODE = i;
#ifdef _DEBUG
		m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif
	}
	void SetFLASHLIGHTDEPTHFILTERMODE( bool i )
	{
		m_nFLASHLIGHTDEPTHFILTERMODE = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif
	}
public:
	pp_vertexlit_wetness_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = false;
#endif // _DEBUG
		m_nCONVERT_TO_SRGB = 0;
#ifdef _DEBUG
		m_bFLASHLIGHT = false;
#endif // _DEBUG
		m_nFLASHLIGHT = 0;
#ifdef _DEBUG
		m_bPHONGWARPTEXTURE = false;
#endif // _DEBUG
		m_nPHONGWARPTEXTURE = 0;
#ifdef _DEBUG
		m_bWRINKLEMAP = false;
#endif // _DEBUG
		m_nWRINKLEMAP = 0;
#ifdef _DEBUG
		m_bRIMLIGHT = false;
#endif // _DEBUG
		m_nRIMLIGHT = 0;
#ifdef _DEBUG
		m_bFLASHLIGHTDEPTHFILTERMODE = false;
#endif // _DEBUG
		m_nFLASHLIGHTDEPTHFILTERMODE = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bCONVERT_TO_SRGB && m_bFLASHLIGHT && m_bPHONGWARPTEXTURE && m_bWRINKLEMAP && m_bRIMLIGHT && m_bFLASHLIGHTDEPTHFILTERMODE;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 160 * m_nCONVERT_TO_SRGB ) + ( 160 * m_nFLASHLIGHT ) + ( 320 * m_nPHONGWARPTEXTURE ) + ( 640 * m_nWRINKLEMAP ) + ( 1280 * m_nRIMLIGHT ) + ( 2560 * m_nFLASHLIGHTDEPTHFILTERMODE ) + 0;
	}
};
#define shaderStaticTest_pp_vertexlit_wetness_ps30 psh_forgot_to_set_static_CONVERT_TO_SRGB + psh_forgot_to_set_static_FLASHLIGHT + psh_forgot_to_set_static_PHONGWARPTEXTURE + psh_forgot_to_set_static_WRINKLEMAP + psh_forgot_to_set_static_RIMLIGHT + psh_forgot_to_set_static_FLASHLIGHTDEPTHFILTERMODE + 0
class pp_vertexlit_wetness_ps30_Dynamic_Index
{
private:
	int m_nPIXELFOGTYPE;
#ifdef _DEBUG
	bool m_bPIXELFOGTYPE;
#endif
public:
	void SetPIXELFOGTYPE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPIXELFOGTYPE = i;
#ifdef _DEBUG
		m_bPIXELFOGTYPE = true;
#endif
	}
	void SetPIXELFOGTYPE( bool i )
	{
		m_nPIXELFOGTYPE = i ? 1 : 0;
#ifdef _DEBUG
		m_bPIXELFOGTYPE = true;
#endif
	}
private:
	int m_nNUM_LIGHTS;
#ifdef _DEBUG
	bool m_bNUM_LIGHTS;
#endif
public:
	void SetNUM_LIGHTS( int i )
	{
		Assert( i >= 0 && i <= 4 );
		m_nNUM_LIGHTS = i;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif
	}
	void SetNUM_LIGHTS( bool i )
	{
		m_nNUM_LIGHTS = i ? 1 : 0;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif
	}
private:
	int m_nFLASHLIGHTSHADOWS;
#ifdef _DEBUG
	bool m_bFLASHLIGHTSHADOWS;
#endif
public:
	void SetFLASHLIGHTSHADOWS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLASHLIGHTSHADOWS = i;
#ifdef _DEBUG
		m_bFLASHLIGHTSHADOWS = true;
#endif
	}
	void SetFLASHLIGHTSHADOWS( bool i )
	{
		m_nFLASHLIGHTSHADOWS = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLASHLIGHTSHADOWS = true;
#endif
	}
private:
	int m_nPHONG_USE_EXPONENT_FACTOR;
#ifdef _DEBUG
	bool m_bPHONG_USE_EXPONENT_FACTOR;
#endif
public:
	void SetPHONG_USE_EXPONENT_FACTOR( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPHONG_USE_EXPONENT_FACTOR = i;
#ifdef _DEBUG
		m_bPHONG_USE_EXPONENT_FACTOR = true;
#endif
	}
	void SetPHONG_USE_EXPONENT_FACTOR( bool i )
	{
		m_nPHONG_USE_EXPONENT_FACTOR = i ? 1 : 0;
#ifdef _DEBUG
		m_bPHONG_USE_EXPONENT_FACTOR = true;
#endif
	}
private:
	int m_nCASCADED_SHADOW;
#ifdef _DEBUG
	bool m_bCASCADED_SHADOW;
#endif
public:
	void SetCASCADED_SHADOW( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCASCADED_SHADOW = i;
#ifdef _DEBUG
		m_bCASCADED_SHADOW = true;
#endif
	}
	void SetCASCADED_SHADOW( bool i )
	{
		m_nCASCADED_SHADOW = i ? 1 : 0;
#ifdef _DEBUG
		m_bCASCADED_SHADOW = true;
#endif
	}
private:
	int m_nUBERLIGHT;
#ifdef _DEBUG
	bool m_bUBERLIGHT;
#endif
public:
	void SetUBERLIGHT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nUBERLIGHT = i;
#ifdef _DEBUG
		m_bUBERLIGHT = true;
#endif
	}
	void SetUBERLIGHT( bool i )
	{
		m_nUBERLIGHT = i ? 1 : 0;
#ifdef _DEBUG
		m_bUBERLIGHT = true;
#endif
	}
public:
	pp_vertexlit_wetness_ps30_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bPIXELFOGTYPE = false;
#endif // _DEBUG
		m_nPIXELFOGTYPE = 0;
#ifdef _DEBUG
		m_bNUM_LIGHTS = false;
#endif // _DEBUG
		m_nNUM_LIGHTS = 0;
#ifdef _DEBUG
		m_bFLASHLIGHTSHADOWS = false;
#endif // _DEBUG
		m_nFLASHLIGHTSHADOWS = 0;
#ifdef _DEBUG
		m_bPHONG_USE_EXPONENT_FACTOR = false;
#endif // _DEBUG
		m_nPHONG_USE_EXPONENT_FACTOR = 0;
#ifdef _DEBUG
		m_bCASCADED_SHADOW = false;
#endif // _DEBUG
		m_nCASCADED_SHADOW = 0;
#ifdef _DEBUG
		m_bUBERLIGHT = false;
#endif // _DEBUG
		m_nUBERLIGHT = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bPIXELFOGTYPE && m_bNUM_LIGHTS && m_bFLASHLIGHTSHADOWS && m_bPHONG_USE_EXPONENT_FACTOR && m_bCASCADED_SHADOW && m_bUBERLIGHT;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nPIXELFOGTYPE ) + ( 2 * m_nNUM_LIGHTS ) + ( 10 * m_nFLASHLIGHTSHADOWS ) + ( 20 * m_nPHONG_USE_EXPONENT_FACTOR ) + ( 40 * m_nCASCADED_SHADOW ) + ( 80 * m_nUBERLIGHT ) + 0;
	}
};
#define shaderDynamicTest_pp_vertexlit_wetness_ps30 psh_forgot_to_set_dynamic_PIXELFOGTYPE + psh_forgot_to_set_dynamic_NUM_LIGHTS + psh_forgot_to_set_dynamic_FLASHLIGHTSHADOWS + psh_forgot_to_set_dynamic_PHONG_USE_EXPONENT_FACTOR + psh_forgot_to_set_dynamic_CASCADED_SHADOW + psh_forgot_to_set_dynamic_UBERLIGHT + 0
