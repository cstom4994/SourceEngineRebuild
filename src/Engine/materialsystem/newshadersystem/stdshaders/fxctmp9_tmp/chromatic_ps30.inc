#include "shaderlib/cshader.h"
class chromatic_ps30_Static_Index
{
public:
	chromatic_ps30_Static_Index( )
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
#define shaderStaticTest_chromatic_ps30 0
class chromatic_ps30_Dynamic_Index
{
private:
	int m_nRADIAL;
#ifdef _DEBUG
	bool m_bRADIAL;
#endif
public:
	void SetRADIAL( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nRADIAL = i;
#ifdef _DEBUG
		m_bRADIAL = true;
#endif
	}
	void SetRADIAL( bool i )
	{
		m_nRADIAL = i ? 1 : 0;
#ifdef _DEBUG
		m_bRADIAL = true;
#endif
	}
public:
	chromatic_ps30_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bRADIAL = false;
#endif // _DEBUG
		m_nRADIAL = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bRADIAL;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nRADIAL ) + 0;
	}
};
#define shaderDynamicTest_chromatic_ps30 psh_forgot_to_set_dynamic_RADIAL + 0
