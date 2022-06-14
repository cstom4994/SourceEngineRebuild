#include "shaderlib/cshader.h"
class solidenergy_ps30_Static_Index
{
private:
	int m_nADDITIVE;
#ifdef _DEBUG
	bool m_bADDITIVE;
#endif
public:
	void SetADDITIVE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nADDITIVE = i;
#ifdef _DEBUG
		m_bADDITIVE = true;
#endif
	}
	void SetADDITIVE( bool i )
	{
		m_nADDITIVE = i ? 1 : 0;
#ifdef _DEBUG
		m_bADDITIVE = true;
#endif
	}
private:
	int m_nDETAIL1;
#ifdef _DEBUG
	bool m_bDETAIL1;
#endif
public:
	void SetDETAIL1( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDETAIL1 = i;
#ifdef _DEBUG
		m_bDETAIL1 = true;
#endif
	}
	void SetDETAIL1( bool i )
	{
		m_nDETAIL1 = i ? 1 : 0;
#ifdef _DEBUG
		m_bDETAIL1 = true;
#endif
	}
private:
	int m_nDETAIL1BLENDMODE;
#ifdef _DEBUG
	bool m_bDETAIL1BLENDMODE;
#endif
public:
	void SetDETAIL1BLENDMODE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDETAIL1BLENDMODE = i;
#ifdef _DEBUG
		m_bDETAIL1BLENDMODE = true;
#endif
	}
	void SetDETAIL1BLENDMODE( bool i )
	{
		m_nDETAIL1BLENDMODE = i ? 1 : 0;
#ifdef _DEBUG
		m_bDETAIL1BLENDMODE = true;
#endif
	}
private:
	int m_nDETAIL2;
#ifdef _DEBUG
	bool m_bDETAIL2;
#endif
public:
	void SetDETAIL2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDETAIL2 = i;
#ifdef _DEBUG
		m_bDETAIL2 = true;
#endif
	}
	void SetDETAIL2( bool i )
	{
		m_nDETAIL2 = i ? 1 : 0;
#ifdef _DEBUG
		m_bDETAIL2 = true;
#endif
	}
private:
	int m_nDETAIL2BLENDMODE;
#ifdef _DEBUG
	bool m_bDETAIL2BLENDMODE;
#endif
public:
	void SetDETAIL2BLENDMODE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDETAIL2BLENDMODE = i;
#ifdef _DEBUG
		m_bDETAIL2BLENDMODE = true;
#endif
	}
	void SetDETAIL2BLENDMODE( bool i )
	{
		m_nDETAIL2BLENDMODE = i ? 1 : 0;
#ifdef _DEBUG
		m_bDETAIL2BLENDMODE = true;
#endif
	}
private:
	int m_nTANGENTTOPACITY;
#ifdef _DEBUG
	bool m_bTANGENTTOPACITY;
#endif
public:
	void SetTANGENTTOPACITY( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nTANGENTTOPACITY = i;
#ifdef _DEBUG
		m_bTANGENTTOPACITY = true;
#endif
	}
	void SetTANGENTTOPACITY( bool i )
	{
		m_nTANGENTTOPACITY = i ? 1 : 0;
#ifdef _DEBUG
		m_bTANGENTTOPACITY = true;
#endif
	}
private:
	int m_nTANGENTSOPACITY;
#ifdef _DEBUG
	bool m_bTANGENTSOPACITY;
#endif
public:
	void SetTANGENTSOPACITY( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nTANGENTSOPACITY = i;
#ifdef _DEBUG
		m_bTANGENTSOPACITY = true;
#endif
	}
	void SetTANGENTSOPACITY( bool i )
	{
		m_nTANGENTSOPACITY = i ? 1 : 0;
#ifdef _DEBUG
		m_bTANGENTSOPACITY = true;
#endif
	}
private:
	int m_nFRESNELOPACITY;
#ifdef _DEBUG
	bool m_bFRESNELOPACITY;
#endif
public:
	void SetFRESNELOPACITY( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFRESNELOPACITY = i;
#ifdef _DEBUG
		m_bFRESNELOPACITY = true;
#endif
	}
	void SetFRESNELOPACITY( bool i )
	{
		m_nFRESNELOPACITY = i ? 1 : 0;
#ifdef _DEBUG
		m_bFRESNELOPACITY = true;
#endif
	}
private:
	int m_nDEPTHBLEND;
#ifdef _DEBUG
	bool m_bDEPTHBLEND;
#endif
public:
	void SetDEPTHBLEND( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nDEPTHBLEND = i;
#ifdef _DEBUG
		m_bDEPTHBLEND = true;
#endif
	}
	void SetDEPTHBLEND( bool i )
	{
		m_nDEPTHBLEND = i ? 1 : 0;
#ifdef _DEBUG
		m_bDEPTHBLEND = true;
#endif
	}
private:
	int m_nVERTEXCOLOR;
#ifdef _DEBUG
	bool m_bVERTEXCOLOR;
#endif
public:
	void SetVERTEXCOLOR( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nVERTEXCOLOR = i;
#ifdef _DEBUG
		m_bVERTEXCOLOR = true;
#endif
	}
	void SetVERTEXCOLOR( bool i )
	{
		m_nVERTEXCOLOR = i ? 1 : 0;
#ifdef _DEBUG
		m_bVERTEXCOLOR = true;
#endif
	}
private:
	int m_nFLOWMAP;
#ifdef _DEBUG
	bool m_bFLOWMAP;
#endif
public:
	void SetFLOWMAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLOWMAP = i;
#ifdef _DEBUG
		m_bFLOWMAP = true;
#endif
	}
	void SetFLOWMAP( bool i )
	{
		m_nFLOWMAP = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLOWMAP = true;
#endif
	}
private:
	int m_nFLOW_CHEAP;
#ifdef _DEBUG
	bool m_bFLOW_CHEAP;
#endif
public:
	void SetFLOW_CHEAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLOW_CHEAP = i;
#ifdef _DEBUG
		m_bFLOW_CHEAP = true;
#endif
	}
	void SetFLOW_CHEAP( bool i )
	{
		m_nFLOW_CHEAP = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLOW_CHEAP = true;
#endif
	}
private:
	int m_nREFRACT;
#ifdef _DEBUG
	bool m_bREFRACT;
#endif
public:
	void SetREFRACT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nREFRACT = i;
#ifdef _DEBUG
		m_bREFRACT = true;
#endif
	}
	void SetREFRACT( bool i )
	{
		m_nREFRACT = i ? 1 : 0;
#ifdef _DEBUG
		m_bREFRACT = true;
#endif
	}
public:
	solidenergy_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bADDITIVE = false;
#endif // _DEBUG
		m_nADDITIVE = 0;
#ifdef _DEBUG
		m_bDETAIL1 = false;
#endif // _DEBUG
		m_nDETAIL1 = 0;
#ifdef _DEBUG
		m_bDETAIL1BLENDMODE = false;
#endif // _DEBUG
		m_nDETAIL1BLENDMODE = 0;
#ifdef _DEBUG
		m_bDETAIL2 = false;
#endif // _DEBUG
		m_nDETAIL2 = 0;
#ifdef _DEBUG
		m_bDETAIL2BLENDMODE = false;
#endif // _DEBUG
		m_nDETAIL2BLENDMODE = 0;
#ifdef _DEBUG
		m_bTANGENTTOPACITY = false;
#endif // _DEBUG
		m_nTANGENTTOPACITY = 0;
#ifdef _DEBUG
		m_bTANGENTSOPACITY = false;
#endif // _DEBUG
		m_nTANGENTSOPACITY = 0;
#ifdef _DEBUG
		m_bFRESNELOPACITY = false;
#endif // _DEBUG
		m_nFRESNELOPACITY = 0;
#ifdef _DEBUG
		m_bDEPTHBLEND = false;
#endif // _DEBUG
		m_nDEPTHBLEND = 0;
#ifdef _DEBUG
		m_bVERTEXCOLOR = false;
#endif // _DEBUG
		m_nVERTEXCOLOR = 0;
#ifdef _DEBUG
		m_bFLOWMAP = false;
#endif // _DEBUG
		m_nFLOWMAP = 0;
#ifdef _DEBUG
		m_bFLOW_CHEAP = false;
#endif // _DEBUG
		m_nFLOW_CHEAP = 0;
#ifdef _DEBUG
		m_bREFRACT = false;
#endif // _DEBUG
		m_nREFRACT = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bADDITIVE && m_bDETAIL1 && m_bDETAIL1BLENDMODE && m_bDETAIL2 && m_bDETAIL2BLENDMODE && m_bTANGENTTOPACITY && m_bTANGENTSOPACITY && m_bFRESNELOPACITY && m_bDEPTHBLEND && m_bVERTEXCOLOR && m_bFLOWMAP && m_bFLOW_CHEAP && m_bREFRACT;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 32 * m_nADDITIVE ) + ( 64 * m_nDETAIL1 ) + ( 128 * m_nDETAIL1BLENDMODE ) + ( 256 * m_nDETAIL2 ) + ( 512 * m_nDETAIL2BLENDMODE ) + ( 1024 * m_nTANGENTTOPACITY ) + ( 2048 * m_nTANGENTSOPACITY ) + ( 4096 * m_nFRESNELOPACITY ) + ( 8192 * m_nDEPTHBLEND ) + ( 8192 * m_nVERTEXCOLOR ) + ( 16384 * m_nFLOWMAP ) + ( 32768 * m_nFLOW_CHEAP ) + ( 65536 * m_nREFRACT ) + 0;
	}
};
#define shaderStaticTest_solidenergy_ps30 psh_forgot_to_set_static_ADDITIVE + psh_forgot_to_set_static_DETAIL1 + psh_forgot_to_set_static_DETAIL1BLENDMODE + psh_forgot_to_set_static_DETAIL2 + psh_forgot_to_set_static_DETAIL2BLENDMODE + psh_forgot_to_set_static_TANGENTTOPACITY + psh_forgot_to_set_static_TANGENTSOPACITY + psh_forgot_to_set_static_FRESNELOPACITY + psh_forgot_to_set_static_DEPTHBLEND + psh_forgot_to_set_static_VERTEXCOLOR + psh_forgot_to_set_static_FLOWMAP + psh_forgot_to_set_static_FLOW_CHEAP + psh_forgot_to_set_static_REFRACT + 0
class solidenergy_ps30_Dynamic_Index
{
private:
	int m_nACTIVE;
#ifdef _DEBUG
	bool m_bACTIVE;
#endif
public:
	void SetACTIVE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nACTIVE = i;
#ifdef _DEBUG
		m_bACTIVE = true;
#endif
	}
	void SetACTIVE( bool i )
	{
		m_nACTIVE = i ? 1 : 0;
#ifdef _DEBUG
		m_bACTIVE = true;
#endif
	}
private:
	int m_nPOWERUP;
#ifdef _DEBUG
	bool m_bPOWERUP;
#endif
public:
	void SetPOWERUP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPOWERUP = i;
#ifdef _DEBUG
		m_bPOWERUP = true;
#endif
	}
	void SetPOWERUP( bool i )
	{
		m_nPOWERUP = i ? 1 : 0;
#ifdef _DEBUG
		m_bPOWERUP = true;
#endif
	}
private:
	int m_nVORTEX1;
#ifdef _DEBUG
	bool m_bVORTEX1;
#endif
public:
	void SetVORTEX1( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nVORTEX1 = i;
#ifdef _DEBUG
		m_bVORTEX1 = true;
#endif
	}
	void SetVORTEX1( bool i )
	{
		m_nVORTEX1 = i ? 1 : 0;
#ifdef _DEBUG
		m_bVORTEX1 = true;
#endif
	}
private:
	int m_nVORTEX2;
#ifdef _DEBUG
	bool m_bVORTEX2;
#endif
public:
	void SetVORTEX2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nVORTEX2 = i;
#ifdef _DEBUG
		m_bVORTEX2 = true;
#endif
	}
	void SetVORTEX2( bool i )
	{
		m_nVORTEX2 = i ? 1 : 0;
#ifdef _DEBUG
		m_bVORTEX2 = true;
#endif
	}
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
	solidenergy_ps30_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bACTIVE = false;
#endif // _DEBUG
		m_nACTIVE = 0;
#ifdef _DEBUG
		m_bPOWERUP = false;
#endif // _DEBUG
		m_nPOWERUP = 0;
#ifdef _DEBUG
		m_bVORTEX1 = false;
#endif // _DEBUG
		m_nVORTEX1 = 0;
#ifdef _DEBUG
		m_bVORTEX2 = false;
#endif // _DEBUG
		m_nVORTEX2 = 0;
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
		bool bAllDynamicVarsDefined = m_bACTIVE && m_bPOWERUP && m_bVORTEX1 && m_bVORTEX2 && m_bPIXELFOGTYPE;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nACTIVE ) + ( 2 * m_nPOWERUP ) + ( 4 * m_nVORTEX1 ) + ( 8 * m_nVORTEX2 ) + ( 16 * m_nPIXELFOGTYPE ) + 0;
	}
};
#define shaderDynamicTest_solidenergy_ps30 psh_forgot_to_set_dynamic_ACTIVE + psh_forgot_to_set_dynamic_POWERUP + psh_forgot_to_set_dynamic_VORTEX1 + psh_forgot_to_set_dynamic_VORTEX2 + psh_forgot_to_set_dynamic_PIXELFOGTYPE + 0
