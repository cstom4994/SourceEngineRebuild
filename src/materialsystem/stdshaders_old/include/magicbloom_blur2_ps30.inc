// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// defined $HDRTYPE && defined $HDRENABLED && !$HDRTYPE && $HDRENABLED
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $HDRTYPE && $LIGHTING_PREVIEW && $HDRTYPE != 0
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW

#ifndef MAGICBLOOM_BLUR2_PS30_H
#define MAGICBLOOM_BLUR2_PS30_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class magicbloom_blur2_ps30_Static_Index
{
public:
	magicbloom_blur2_ps30_Static_Index()
	{
	}

	int GetIndex()
	{
		return 0;
	}
};

#define shaderStaticTest_magicbloom_blur2_ps30 1


class magicbloom_blur2_ps30_Dynamic_Index
{
public:
	magicbloom_blur2_ps30_Dynamic_Index()
	{
	}

	int GetIndex()
	{
		return 0;
	}
};

#define shaderDynamicTest_magicbloom_blur2_ps30 1


#endif	// MAGICBLOOM_BLUR2_PS30_H