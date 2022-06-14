#include "shaderlib/cshader.h"
class pp_splinerope_vs20_Static_Index
{
private:
	int m_nSSAODEPTH;
#ifdef _DEBUG
	bool m_bSSAODEPTH;
#endif
public:
	void SetSSAODEPTH( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSSAODEPTH = i;
#ifdef _DEBUG
		m_bSSAODEPTH = true;
#endif
	}
	void SetSSAODEPTH( bool i )
	{
		m_nSSAODEPTH = i ? 1 : 0;
#ifdef _DEBUG
		m_bSSAODEPTH = true;
#endif
	}
public:
	pp_splinerope_vs20_Static_Index( )
	{
#ifdef _DEBUG
		m_bSSAODEPTH = false;
#endif // _DEBUG
		m_nSSAODEPTH = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bSSAODEPTH;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nSSAODEPTH ) + 0;
	}
};
#define shaderStaticTest_pp_splinerope_vs20 vsh_forgot_to_set_static_SSAODEPTH + 0
class pp_splinerope_vs20_Dynamic_Index
{
public:
	pp_splinerope_vs20_Dynamic_Index()
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
#define shaderDynamicTest_pp_splinerope_vs20 0
