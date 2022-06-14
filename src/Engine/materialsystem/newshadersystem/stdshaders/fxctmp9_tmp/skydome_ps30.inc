#include "shaderlib/cshader.h"
class skydome_ps30_Static_Index
{
private:
	int m_nCONVERT_TO_SRGB;
#ifdef _DEBUG
	bool m_bCONVERT_TO_SRGB;
#endif
public:
	void SetCONVERT_TO_SRGB( int i )
	{
		Assert( i >= 0 && i <= 0 );
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
public:
	skydome_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = false;
#endif // _DEBUG
		m_nCONVERT_TO_SRGB = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bCONVERT_TO_SRGB;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 2 * m_nCONVERT_TO_SRGB ) + 0;
	}
};
#define shaderStaticTest_skydome_ps30 psh_forgot_to_set_static_CONVERT_TO_SRGB + 0
class skydome_ps30_Dynamic_Index
{
private:
	int m_nRENDER_SKY;
#ifdef _DEBUG
	bool m_bRENDER_SKY;
#endif
public:
	void SetRENDER_SKY( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nRENDER_SKY = i;
#ifdef _DEBUG
		m_bRENDER_SKY = true;
#endif
	}
	void SetRENDER_SKY( bool i )
	{
		m_nRENDER_SKY = i ? 1 : 0;
#ifdef _DEBUG
		m_bRENDER_SKY = true;
#endif
	}
public:
	skydome_ps30_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bRENDER_SKY = false;
#endif // _DEBUG
		m_nRENDER_SKY = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bRENDER_SKY;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nRENDER_SKY ) + 0;
	}
};
#define shaderDynamicTest_skydome_ps30 psh_forgot_to_set_dynamic_RENDER_SKY + 0
