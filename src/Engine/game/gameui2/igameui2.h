/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#pragma once

#if defined(GAMEUI2_DLL)
#include "tier1/interface.h"
#else
#include "interface.h"
#endif // GAMEUI2_DLL

#include "vgui/VGUI.h"
#include "mathlib/vector.h"
#include "ivrenderview.h"

abstract_class IGameUI2 : public IBaseInterface
{
public:
	virtual void Initialize(CreateInterfaceFn AppFactory) = 0;
	virtual void Shutdown() = 0;

	virtual void OnInitialize() = 0;
	virtual void OnShutdown() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnLevelInitializePreEntity() = 0;
	virtual void OnLevelInitializePostEntity() = 0;
	virtual void OnLevelShutdown() = 0;

	virtual bool IsInLevel() = 0;
	virtual bool IsInBackgroundLevel() = 0;
	virtual bool IsInMultiplayer() = 0;
	virtual bool IsInLoading() = 0;

	virtual void SetView(const CViewSetup& ViewSetup) = 0;
	virtual void SetFrustum(VPlane* Plane) = 0;
	virtual void SetMaskTexture(ITexture* Texture) = 0;
	virtual void SetRenderContext(IMatRenderContext* Context) = 0;
};

#define GAMEUI2_DLL_INTERFACE_VERSION "GAMEUI2_V006"