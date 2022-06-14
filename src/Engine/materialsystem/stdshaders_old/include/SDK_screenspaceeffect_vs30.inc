// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#ifndef SDK_SCREENSPACEEFFECT_VS30_H
#define SDK_SCREENSPACEEFFECT_VS30_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class SDK_screenspaceeffect_vs30_Static_Index
{
	int m_nX360APPCHOOSER : 2;
public:
	void SetX360APPCHOOSER( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nX360APPCHOOSER = i;
	}

	SDK_screenspaceeffect_vs30_Static_Index()
	{
		m_nX360APPCHOOSER = 0;
	}

	int GetIndex()
	{
		return ( 1 * m_nX360APPCHOOSER ) + 0;
	}
};

#define shaderStaticTest_SDK_screenspaceeffect_vs30 1


class SDK_screenspaceeffect_vs30_Dynamic_Index
{
public:
	SDK_screenspaceeffect_vs30_Dynamic_Index()
	{
	}

	int GetIndex()
	{
		return 0;
	}
};

#define shaderDynamicTest_SDK_screenspaceeffect_vs30 1


#endif	// SDK_SCREENSPACEEFFECT_VS30_H