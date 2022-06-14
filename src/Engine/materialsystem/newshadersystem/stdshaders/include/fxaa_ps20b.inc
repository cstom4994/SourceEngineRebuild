// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// defined $HDRTYPE && defined $HDRENABLED && !$HDRTYPE && $HDRENABLED
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $HDRTYPE && $LIGHTING_PREVIEW && $HDRTYPE != 0
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW

#ifndef FXAA_PS20B_H
#define FXAA_PS20B_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class fxaa_ps20b_Static_Index
{
public:
	fxaa_ps20b_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
	}

	int GetIndex() const
	{
		return 0;
	}
};

#define shaderStaticTest_fxaa_ps20b 1


class fxaa_ps20b_Dynamic_Index
{
	unsigned int m_nQUALITY : 3;
#ifdef _DEBUG
	bool m_bQUALITY : 1;
#endif	// _DEBUG
public:
	void SetQUALITY( int i )
	{
		Assert( i >= 0 && i <= 4 );
		m_nQUALITY = i;
#ifdef _DEBUG
		m_bQUALITY = true;
#endif	// _DEBUG
	}

	fxaa_ps20b_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nQUALITY = 0;
#ifdef _DEBUG
		m_bQUALITY = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bQUALITY );
		return ( 1 * m_nQUALITY ) + 0;
	}
};

#define shaderDynamicTest_fxaa_ps20b psh_forgot_to_set_dynamic_QUALITY


#endif	// FXAA_PS20B_H