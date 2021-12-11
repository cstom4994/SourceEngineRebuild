#include "shaderlib/cshader.h"
class pp_portal_refract_ps20b_Static_Index
{
private:
	int m_nSTAGE;
#ifdef _DEBUG
	bool m_bSTAGE;
#endif
public:
	void SetSTAGE( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nSTAGE = i;
#ifdef _DEBUG
		m_bSTAGE = true;
#endif
	}
	void SetSTAGE( bool i )
	{
		m_nSTAGE = i ? 1 : 0;
#ifdef _DEBUG
		m_bSTAGE = true;
#endif
	}
private:
	int m_nPORTAL_TINT;
#ifdef _DEBUG
	bool m_bPORTAL_TINT;
#endif
public:
	void SetPORTAL_TINT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPORTAL_TINT = i;
#ifdef _DEBUG
		m_bPORTAL_TINT = true;
#endif
	}
	void SetPORTAL_TINT( bool i )
	{
		m_nPORTAL_TINT = i ? 1 : 0;
#ifdef _DEBUG
		m_bPORTAL_TINT = true;
#endif
	}
public:
	pp_portal_refract_ps20b_Static_Index( )
	{
#ifdef _DEBUG
		m_bSTAGE = false;
#endif // _DEBUG
		m_nSTAGE = 0;
#ifdef _DEBUG
		m_bPORTAL_TINT = false;
#endif // _DEBUG
		m_nPORTAL_TINT = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bSTAGE && m_bPORTAL_TINT;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 2 * m_nSTAGE ) + ( 6 * m_nPORTAL_TINT ) + 0;
	}
};
#define shaderStaticTest_pp_portal_refract_ps20b psh_forgot_to_set_static_STAGE + psh_forgot_to_set_static_PORTAL_TINT + 0
class pp_portal_refract_ps20b_Dynamic_Index
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
public:
	pp_portal_refract_ps20b_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bPIXELFOGTYPE = false;
#endif // _DEBUG
		m_nPIXELFOGTYPE = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bPIXELFOGTYPE;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nPIXELFOGTYPE ) + 0;
	}
};
#define shaderDynamicTest_pp_portal_refract_ps20b psh_forgot_to_set_dynamic_PIXELFOGTYPE + 0
