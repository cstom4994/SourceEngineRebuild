// Copyright(c) 2019 - 2021, KaoruXun All rights reserved.

#pragma once

#include "rccpp_invoke.h"

#include "cdll_int.h"
#include "engine/ienginesound.h"
#include "ienginevgui.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "ivrenderview.h"
#include "view_shared.h"
#include "GameUI/IGameUI.h"
#include "vgui_controls/AnimationController.h"
#include "VGuiMatSurface/IMatSystemSurface.h"
#include "materialsystem/imaterialsystem.h"

extern IMatSystemSurface *g_pMatSystemSurface;

class RCCPP : public IRCCPP
{
public:
	virtual void Initialize(CreateInterfaceFn AppFactory);
	virtual void Shutdown();

	virtual void OnInitialize();
	virtual void OnShutdown();
	virtual void OnUpdate();
	virtual void OnLevelInitializePreEntity();
	virtual void OnLevelInitializePostEntity();
	virtual void OnLevelShutdown();

	virtual bool IsInLevel();
	virtual bool IsInBackgroundLevel();
	virtual bool IsInMultiplayer();
	virtual bool IsInLoading();

	virtual void SetView(const CViewSetup& ViewSetup);
	virtual void SetFrustum(VPlane* Plane);
	virtual void SetMaskTexture(ITexture* Texture);
	virtual void SetRenderContext(IMatRenderContext* Context);

	virtual wchar_t* ConvertToLocalizedString(const char* Text);

	virtual Vector2D GetViewport() const;
	virtual vgui::VPANEL GetRootPanel() const;

	virtual float GetTime() const { return Plat_FloatTime(); }
	virtual CViewSetup GetView() const { return View; }
	virtual VPlane* GetFrustum() const { return Frustum; }
	virtual ITexture* GetMaskTexture() const { return MaskTexture; }
	virtual IMatRenderContext* GetRenderContext() const { return RenderContext; }

	virtual IVEngineClient* GetEngineClient() const { return EngineClient; }
	virtual IEngineVGui* GetEngineVGui() const { return EngineVGui; }
	virtual IVRenderView* GetRenderView() const { return RenderView; }


private:
	CViewSetup View;
	VPlane* Frustum;
	ITexture* MaskTexture;
	IMatRenderContext* RenderContext;

	IVEngineClient* EngineClient;
	IEngineVGui* EngineVGui;
	IVRenderView* RenderView;
};

extern RCCPP& GetRCCPP();