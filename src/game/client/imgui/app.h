#pragma once

#include "interface.h"
#include "cdll_int.h"
#include "engine/ienginesound.h"
#include "ienginevgui.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "ivrenderview.h"
#include "view_shared.h"
#include "vgui_controls/AnimationController.h"
#include "VGuiMatSurface/IMatSystemSurface.h"
#include "materialsystem/imaterialsystem.h"

class ITexture;

class Vector;

// I would just merge this into CSteamAppLoader, but it makes such a mess
class CImGuiSourceApp {
public:
    void Init(CreateInterfaceFn AppFactory);

    void Destroy();

    void DrawFrame();

private:

    ITexture *m_pWhiteTexture;

    float m_lastFrameTime;

    Vector *m_ambientLightColors;

    CViewSetup View;
    VPlane* Frustum;
    ITexture* MaskTexture;
    IMatRenderContext* RenderContext;

    IVEngineClient* EngineClient;
    IEngineSound* EngineSound;
    IEngineVGui* EngineVGui;
    ISoundEmitterSystemBase* SoundEmitterSystemBase;
    IVRenderView* RenderView;
    IMaterialSystem* MaterialSystem;
    IMatSystemSurface* MaterialSystemSurface;
};