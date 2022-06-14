#include "shaderlib/cshader.h"
class gaussian_depthaware_roughness_ps30_Static_Index
{
private:
	int m_nHORIZONTAL;
#ifdef _DEBUG
	bool m_bHORIZONTAL;
#endif
public:
	void SetHORIZONTAL( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nHORIZONTAL = i;
#ifdef _DEBUG
		m_bHORIZONTAL = true;
#endif
	}
	void SetHORIZONTAL( bool i )
	{
		m_nHORIZONTAL = i ? 1 : 0;
#ifdef _DEBUG
		m_bHORIZONTAL = true;
#endif
	}
public:
	gaussian_depthaware_roughness_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bHORIZONTAL = false;
#endif // _DEBUG
		m_nHORIZONTAL = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bHORIZONTAL;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nHORIZONTAL ) + 0;
	}
};
#define shaderStaticTest_gaussian_depthaware_roughness_ps30 psh_forgot_to_set_static_HORIZONTAL + 0
class gaussian_depthaware_roughness_ps30_Dynamic_Index
{
public:
	gaussian_depthaware_roughness_ps30_Dynamic_Index()
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
#define shaderDynamicTest_gaussian_depthaware_roughness_ps30 0
