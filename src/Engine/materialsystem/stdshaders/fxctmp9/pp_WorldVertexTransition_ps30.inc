#include "shaderlib/cshader.h"
class pp_worldvertextransition_ps30_Static_Index
{
private:
	int m_nMACROS;
#ifdef _DEBUG
	bool m_bMACROS;
#endif
public:
	void SetMACROS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nMACROS = i;
#ifdef _DEBUG
		m_bMACROS = true;
#endif
	}
	void SetMACROS( bool i )
	{
		m_nMACROS = i ? 1 : 0;
#ifdef _DEBUG
		m_bMACROS = true;
#endif
	}
public:
	pp_worldvertextransition_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bMACROS = false;
#endif // _DEBUG
		m_nMACROS = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bMACROS;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nMACROS ) + 0;
	}
};
#define shaderStaticTest_pp_worldvertextransition_ps30 psh_forgot_to_set_static_MACROS + 0
class pp_worldvertextransition_ps30_Dynamic_Index
{
public:
	pp_worldvertextransition_ps30_Dynamic_Index()
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
#define shaderDynamicTest_pp_worldvertextransition_ps30 0
