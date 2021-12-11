#include "shaderlib/cshader.h"
class pp_downsample_nohdr_ps20b_Static_Index
{
private:
	int m_nBLOOMTYPE;
#ifdef _DEBUG
	bool m_bBLOOMTYPE;
#endif
public:
	void SetBLOOMTYPE( int i )
	{
		Assert( i >= 1 && i <= 3 );
		m_nBLOOMTYPE = i;
#ifdef _DEBUG
		m_bBLOOMTYPE = true;
#endif
	}
	void SetBLOOMTYPE( bool i )
	{
		m_nBLOOMTYPE = i ? 1 : 0;
#ifdef _DEBUG
		m_bBLOOMTYPE = true;
#endif
	}
private:
	int m_nPS3REGCOUNT48;
#ifdef _DEBUG
	bool m_bPS3REGCOUNT48;
#endif
public:
	void SetPS3REGCOUNT48( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nPS3REGCOUNT48 = i;
#ifdef _DEBUG
		m_bPS3REGCOUNT48 = true;
#endif
	}
	void SetPS3REGCOUNT48( bool i )
	{
		m_nPS3REGCOUNT48 = i ? 1 : 0;
#ifdef _DEBUG
		m_bPS3REGCOUNT48 = true;
#endif
	}
private:
	int m_nSRGB_INPUT_ADAPTER;
#ifdef _DEBUG
	bool m_bSRGB_INPUT_ADAPTER;
#endif
public:
	void SetSRGB_INPUT_ADAPTER( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSRGB_INPUT_ADAPTER = i;
#ifdef _DEBUG
		m_bSRGB_INPUT_ADAPTER = true;
#endif
	}
	void SetSRGB_INPUT_ADAPTER( bool i )
	{
		m_nSRGB_INPUT_ADAPTER = i ? 1 : 0;
#ifdef _DEBUG
		m_bSRGB_INPUT_ADAPTER = true;
#endif
	}
public:
	pp_downsample_nohdr_ps20b_Static_Index( )
	{
#ifdef _DEBUG
		m_bBLOOMTYPE = false;
#endif // _DEBUG
		m_nBLOOMTYPE = 0;
#ifdef _DEBUG
		m_bPS3REGCOUNT48 = false;
#endif // _DEBUG
		m_nPS3REGCOUNT48 = 0;
#ifdef _DEBUG
		m_bSRGB_INPUT_ADAPTER = false;
#endif // _DEBUG
		m_nSRGB_INPUT_ADAPTER = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bBLOOMTYPE && m_bPS3REGCOUNT48 && m_bSRGB_INPUT_ADAPTER;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 2 * m_nBLOOMTYPE ) + ( 6 * m_nPS3REGCOUNT48 ) + ( 6 * m_nSRGB_INPUT_ADAPTER ) + 0;
	}
};
#define shaderStaticTest_pp_downsample_nohdr_ps20b psh_forgot_to_set_static_BLOOMTYPE + psh_forgot_to_set_static_PS3REGCOUNT48 + psh_forgot_to_set_static_SRGB_INPUT_ADAPTER + 0
class pp_downsample_nohdr_ps20b_Dynamic_Index
{
private:
	int m_nFLOAT_BACK_BUFFER;
#ifdef _DEBUG
	bool m_bFLOAT_BACK_BUFFER;
#endif
public:
	void SetFLOAT_BACK_BUFFER( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLOAT_BACK_BUFFER = i;
#ifdef _DEBUG
		m_bFLOAT_BACK_BUFFER = true;
#endif
	}
	void SetFLOAT_BACK_BUFFER( bool i )
	{
		m_nFLOAT_BACK_BUFFER = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLOAT_BACK_BUFFER = true;
#endif
	}
public:
	pp_downsample_nohdr_ps20b_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bFLOAT_BACK_BUFFER = false;
#endif // _DEBUG
		m_nFLOAT_BACK_BUFFER = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bFLOAT_BACK_BUFFER;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nFLOAT_BACK_BUFFER ) + 0;
	}
};
#define shaderDynamicTest_pp_downsample_nohdr_ps20b psh_forgot_to_set_dynamic_FLOAT_BACK_BUFFER + 0
