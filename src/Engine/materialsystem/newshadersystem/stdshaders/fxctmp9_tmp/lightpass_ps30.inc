#include "shaderlib/cshader.h"
class lightpass_ps30_Static_Index
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
private:
	int m_nBUMPMAP;
#ifdef _DEBUG
	bool m_bBUMPMAP;
#endif
public:
	void SetBUMPMAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBUMPMAP = i;
#ifdef _DEBUG
		m_bBUMPMAP = true;
#endif
	}
	void SetBUMPMAP( bool i )
	{
		m_nBUMPMAP = i ? 1 : 0;
#ifdef _DEBUG
		m_bBUMPMAP = true;
#endif
	}
private:
	int m_nBASETEXTURE2;
#ifdef _DEBUG
	bool m_bBASETEXTURE2;
#endif
public:
	void SetBASETEXTURE2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBASETEXTURE2 = i;
#ifdef _DEBUG
		m_bBASETEXTURE2 = true;
#endif
	}
	void SetBASETEXTURE2( bool i )
	{
		m_nBASETEXTURE2 = i ? 1 : 0;
#ifdef _DEBUG
		m_bBASETEXTURE2 = true;
#endif
	}
private:
	int m_nSEAMLESS;
#ifdef _DEBUG
	bool m_bSEAMLESS;
#endif
public:
	void SetSEAMLESS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSEAMLESS = i;
#ifdef _DEBUG
		m_bSEAMLESS = true;
#endif
	}
	void SetSEAMLESS( bool i )
	{
		m_nSEAMLESS = i ? 1 : 0;
#ifdef _DEBUG
		m_bSEAMLESS = true;
#endif
	}
private:
	int m_nDECAL;
#ifdef _DEBUG
	bool m_bDECAL;
#endif
public:
	void SetDECAL( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDECAL = i;
#ifdef _DEBUG
		m_bDECAL = true;
#endif
	}
	void SetDECAL( bool i )
	{
		m_nDECAL = i ? 1 : 0;
#ifdef _DEBUG
		m_bDECAL = true;
#endif
	}
private:
	int m_nMODEL;
#ifdef _DEBUG
	bool m_bMODEL;
#endif
public:
	void SetMODEL( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nMODEL = i;
#ifdef _DEBUG
		m_bMODEL = true;
#endif
	}
	void SetMODEL( bool i )
	{
		m_nMODEL = i ? 1 : 0;
#ifdef _DEBUG
		m_bMODEL = true;
#endif
	}
private:
	int m_nSMOOTHNESS;
#ifdef _DEBUG
	bool m_bSMOOTHNESS;
#endif
public:
	void SetSMOOTHNESS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSMOOTHNESS = i;
#ifdef _DEBUG
		m_bSMOOTHNESS = true;
#endif
	}
	void SetSMOOTHNESS( bool i )
	{
		m_nSMOOTHNESS = i ? 1 : 0;
#ifdef _DEBUG
		m_bSMOOTHNESS = true;
#endif
	}
public:
	lightpass_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = false;
#endif // _DEBUG
		m_nCONVERT_TO_SRGB = 0;
#ifdef _DEBUG
		m_bBUMPMAP = false;
#endif // _DEBUG
		m_nBUMPMAP = 0;
#ifdef _DEBUG
		m_bBASETEXTURE2 = false;
#endif // _DEBUG
		m_nBASETEXTURE2 = 0;
#ifdef _DEBUG
		m_bSEAMLESS = false;
#endif // _DEBUG
		m_nSEAMLESS = 0;
#ifdef _DEBUG
		m_bDECAL = false;
#endif // _DEBUG
		m_nDECAL = 0;
#ifdef _DEBUG
		m_bMODEL = false;
#endif // _DEBUG
		m_nMODEL = 0;
#ifdef _DEBUG
		m_bSMOOTHNESS = false;
#endif // _DEBUG
		m_nSMOOTHNESS = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bCONVERT_TO_SRGB && m_bBUMPMAP && m_bBASETEXTURE2 && m_bSEAMLESS && m_bDECAL && m_bMODEL && m_bSMOOTHNESS;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 3 * m_nCONVERT_TO_SRGB ) + ( 3 * m_nBUMPMAP ) + ( 6 * m_nBASETEXTURE2 ) + ( 12 * m_nSEAMLESS ) + ( 24 * m_nDECAL ) + ( 48 * m_nMODEL ) + ( 96 * m_nSMOOTHNESS ) + 0;
	}
};
#define shaderStaticTest_lightpass_ps30 psh_forgot_to_set_static_CONVERT_TO_SRGB + psh_forgot_to_set_static_BUMPMAP + psh_forgot_to_set_static_BASETEXTURE2 + psh_forgot_to_set_static_SEAMLESS + psh_forgot_to_set_static_DECAL + psh_forgot_to_set_static_MODEL + psh_forgot_to_set_static_SMOOTHNESS + 0
class lightpass_ps30_Dynamic_Index
{
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
	lightpass_ps30_Dynamic_Index()
	{
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
		bool bAllDynamicVarsDefined = m_bPERF;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nPERF ) + 0;
	}
};
#define shaderDynamicTest_lightpass_ps30 psh_forgot_to_set_dynamic_PERF + 0
