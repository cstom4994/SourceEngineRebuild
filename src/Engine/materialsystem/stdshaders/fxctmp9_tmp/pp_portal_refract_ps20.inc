#include "shaderlib/cshader.h"
class pp_portal_refract_ps20_Static_Index
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
	pp_portal_refract_ps20_Static_Index( )
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
		return ( 1 * m_nSTAGE ) + ( 3 * m_nPORTAL_TINT ) + 0;
	}
};
#define shaderStaticTest_pp_portal_refract_ps20 psh_forgot_to_set_static_STAGE + psh_forgot_to_set_static_PORTAL_TINT + 0
class pp_portal_refract_ps20_Dynamic_Index
{
public:
	pp_portal_refract_ps20_Dynamic_Index()
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
#define shaderDynamicTest_pp_portal_refract_ps20 0
