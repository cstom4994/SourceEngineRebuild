#include "cbase.h"
#include "viewrender.h"
#include "view_scene.h"
#include "rendertexture.h"
#include "util_shared.h"
#include "renderparm.h"
#include "iviewrender.h"
#include "vprof.h"

#include "VGuiMatSurface/IMatSystemSurface.h"
#include "vgui_controls/Controls.h"
#include "vgui_int.h"
#include "ienginevgui.h"
#include "view.h"
#include "viewdebug.h"
#include "iclientmode.h"

#include "vance/entities/c_env_skydome.h"
#include "rendering/c_light_manager.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern void
DrawOpaqueRenderable(IClientRenderable *pEnt, bool bTwoPass, ERenderDepthMode DepthMode, int nDefaultFlags = 0);

static Vector ConvertLightmapGammaToLinear(float *iColor4) {
    Vector vecColor;
    for (int i = 0; i < 3; ++i) {
        vecColor[i] = powf(iColor4[i] / 255.0f, 2.2f);
    }
    vecColor *= iColor4[3] / 255.0f;
    return vecColor;
}

class C_VanceViewRender : public CViewRender {
    DECLARE_CLASS(C_VanceViewRender, CViewRender
    );
public:
    C_VanceViewRender::C_VanceViewRender();

    C_VanceViewRender::~C_VanceViewRender();

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw);

private:
    IMaterial *m_matSkyDome;
};

static C_VanceViewRender g_ViewRender;

IViewRender *GetViewRenderInstance() {
    return &g_ViewRender;
}

//=================================================================================

C_VanceViewRender::C_VanceViewRender() {
    if (view != (IViewRender * ) & g_ViewRender || !view) {
        view = (IViewRender * ) & g_ViewRender;
    }
}

C_VanceViewRender::~C_VanceViewRender() {

}

void C_VanceViewRender::Init() {
    BaseClass::Init();
}

void C_VanceViewRender::Shutdown() {
    BaseClass::Shutdown();

    if (m_matSkyDome)
        m_matSkyDome->Release();
}

void C_VanceViewRender::RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) {

    GetLightingManager()->CommitLights();
    BaseClass::RenderView(view, nClearFlags, whatToDraw);

}