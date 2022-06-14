#include "shaderlib/cshader.h"
class light_volumetrics_ps30_Static_Index
{
public:
	light_volumetrics_ps30_Static_Index( )
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
#define shaderStaticTest_light_volumetrics_ps30 0
class light_volumetrics_ps30_Dynamic_Index
{
private:
	int m_nCSM;
#ifdef _DEBUG
	bool m_bCSM;
#endif
public:
	void SetCSM( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCSM = i;
#ifdef _DEBUG
		m_bCSM = true;
#endif
	}
	void SetCSM( bool i )
	{
		m_nCSM = i ? 1 : 0;
#ifdef _DEBUG
		m_bCSM = true;
#endif
	}
private:
	int m_nPERF;
#ifdef _DEBUG
	bool m_bPERF;
#endif
public:
	void SetPERF( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nPERF = i;
#ifdef _DEBUG
		m_bPERF = true;
#endif
	}
	void SetPERF( bool i )
	{
		m_nPERF = i ? 1 : 0;
#ifdef _DEBUG
		m_bPERF = true;
#endif
	}
public:
	light_volumetrics_ps30_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bCSM = false;
#endif // _DEBUG
		m_nCSM = 0;
#ifdef _DEBUG
		m_bPERF = false;
#endif // _DEBUG
		m_nPERF = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bCSM && m_bPERF;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nCSM ) + ( 2 * m_nPERF ) + 0;
	}
};
#define shaderDynamicTest_light_volumetrics_ps30 psh_forgot_to_set_dynamic_CSM + psh_forgot_to_set_dynamic_PERF + 0
