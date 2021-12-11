﻿#include "shaderlib/cshader.h"
class downsample_nohdr_ps20_Static_Index
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
	int m_nCSTRIKE;
#ifdef _DEBUG
	bool m_bCSTRIKE;
#endif
public:
	void SetCSTRIKE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCSTRIKE = i;
#ifdef _DEBUG
		m_bCSTRIKE = true;
#endif
	}
	void SetCSTRIKE( bool i )
	{
		m_nCSTRIKE = i ? 1 : 0;
#ifdef _DEBUG
		m_bCSTRIKE = true;
#endif
	}
public:
	downsample_nohdr_ps20_Static_Index( )
	{
#ifdef _DEBUG
		m_bCONVERT_TO_SRGB = true;
#endif // _DEBUG
		m_nCONVERT_TO_SRGB =  0;
#ifdef _DEBUG
		m_bCSTRIKE = false;
#endif // _DEBUG
		m_nCSTRIKE = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bCONVERT_TO_SRGB && m_bCSTRIKE;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nCONVERT_TO_SRGB ) + ( 1 * m_nCSTRIKE ) + 0;
	}
};
#define shaderStaticTest_downsample_nohdr_ps20 psh_forgot_to_set_static_CSTRIKE + 0
class downsample_nohdr_ps20_Dynamic_Index
{
public:
	downsample_nohdr_ps20_Dynamic_Index()
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
#define shaderDynamicTest_downsample_nohdr_ps20 0