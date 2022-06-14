#pragma once

#include "vphysics_interface.h"

struct surfacesoundnames2_t
{
	unsigned short	walkStepLeft;
	unsigned short	walkStepRight;
	unsigned short	runStepLeft;
	unsigned short	runStepRight;

	unsigned short	stepJump;
	unsigned short	stepLand;
};

struct surfacesoundhandles2_t
{
	short	walkStepLeft;
	short	walkStepRight;
	short	runStepLeft;
	short	runStepRight;

	short	stepJump;
	short	stepLand;
};

//-----------------------------------------------------------------------------
// Purpose: Each different material has an entry like this
//-----------------------------------------------------------------------------
struct surfacedata2_t
{
	surfacesoundnames2_t		sounds;		// names of linked sounds
	surfacesoundhandles2_t		soundhandles;

	surfacedata2_t() { memset(this, 0, sizeof(surfacedata2_t)); }
};

struct surfacedataall_t
{
	surfacedata_t* pOld;
	surfacedata2_t* pNew;

	surfacedataall_t()
	{
		pOld = nullptr;
		pNew = nullptr;
	}
};

class ISPPSurfacePropsExtension : public IPhysicsSurfaceProps
{
public:
	virtual surfacedata2_t* GetSurfaceData2(int surfaceDataIndex) = 0;
	virtual surfacedataall_t GetSurfaceDataBoth(int surfaceDataIndex) = 0;
	// Get a string from surfacedata2
	virtual const char* GetString2(unsigned short stringTableIndex) const = 0;
};

#define SPP_SURFACEPROPS_INTERFACE_VERSION	"SPPSurfacePropsExt001"