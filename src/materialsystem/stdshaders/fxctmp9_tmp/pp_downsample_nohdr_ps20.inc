#include "shaderlib/cshader.h"
class pp_downsample_nohdr_ps20_Static_Index
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
public:
	pp_downsample_nohdr_ps20_Static_Index( )
	{
#ifdef _DEBUG
		m_bBLOOMTYPE = false;
#endif // _DEBUG
		m_nBLOOMTYPE = 0;
#ifdef _DEBUG
		m_bPS3REGCOUNT48 = false;
#endif // _DEBUG
		m_nPS3REGCOUNT48 = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bBLOOMTYPE && m_bPS3REGCOUNT48;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nBLOOMTYPE ) + ( 3 * m_nPS3REGCOUNT48 ) + 0;
	}
};
#define shaderStaticTest_pp_downsample_nohdr_ps20 psh_forgot_to_set_static_BLOOMTYPE + psh_forgot_to_set_static_PS3REGCOUNT48 + 0
class pp_downsample_nohdr_ps20_Dynamic_Index
{
public:
	pp_downsample_nohdr_ps20_Dynamic_Index()
	{
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
#endif // _DEBUG
		return 0;
	}
};
#define shaderDynamicTest_pp_downsample_nohdr_ps20 0
