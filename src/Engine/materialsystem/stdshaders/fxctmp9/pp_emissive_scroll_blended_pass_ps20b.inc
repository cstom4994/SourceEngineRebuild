#include "shaderlib/cshader.h"
class pp_emissive_scroll_blended_pass_ps20b_Static_Index
{
private:
	int m_nCONVERT_TO_SRGB;
#ifdef _DEBUG
	bool m_bCONVERT_TO_SRGB;
#endif
public:
	void SetCONVERT_TO_SRGB( int i )
	{
		Assert( i >= 0 && i <= 1 );
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
	int m_nCORRECTED_FLOW;
#ifdef _DEBUG
	bool m_bCORRECTED_FLOW;
#endif
public:
	void SetCORRECTED_FLOW( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCORRECTED_FLOW = i;
#ifdef _DEBUG
		m_bCORRECTED_FLOW = true;
#endif
	}
	void SetCORRECTED_FLOW( bool i )
	{
		m_nCORRECTED_FLOW = i ? 1 : 0;
#ifdef _DEBUG
		m_bCORRECTED_FLOW = true;
#endif
	}
public:
	pp_emissive_scroll_blended_pass_ps20b_Static_Index( )
	{
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = true;
#endif // _DEBUG
		m_nCONVERT_TO_SRGB =  g_pHardwareConfig->NeedsShaderSRGBConversion();
#ifdef _DEBUG
		m_bCORRECTED_FLOW = false;
#endif // _DEBUG
		m_nCORRECTED_FLOW = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bCONVERT_TO_SRGB && m_bCORRECTED_FLOW;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 2 * m_nCONVERT_TO_SRGB ) + ( 4 * m_nCORRECTED_FLOW ) + 0;
	}
};
#define shaderStaticTest_pp_emissive_scroll_blended_pass_ps20b psh_forgot_to_set_static_CORRECTED_FLOW + 0
class pp_emissive_scroll_blended_pass_ps20b_Dynamic_Index
{
private:
	int m_nFLOW_DEBUG;
#ifdef _DEBUG
	bool m_bFLOW_DEBUG;
#endif
public:
	void SetFLOW_DEBUG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLOW_DEBUG = i;
#ifdef _DEBUG
		m_bFLOW_DEBUG = true;
#endif
	}
	void SetFLOW_DEBUG( bool i )
	{
		m_nFLOW_DEBUG = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLOW_DEBUG = true;
#endif
	}
public:
	pp_emissive_scroll_blended_pass_ps20b_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bFLOW_DEBUG = false;
#endif // _DEBUG
		m_nFLOW_DEBUG = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bFLOW_DEBUG;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nFLOW_DEBUG ) + 0;
	}
};
#define shaderDynamicTest_pp_emissive_scroll_blended_pass_ps20b psh_forgot_to_set_dynamic_FLOW_DEBUG + 0
