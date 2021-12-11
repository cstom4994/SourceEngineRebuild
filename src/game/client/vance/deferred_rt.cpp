
#include "cbase.h"
#include "deferred_rt.h"
#include "viewrender.h"

#include "materialsystem/itexture.h"

#include "tier0/memdbgon.h"

static CTextureReference g_tex_Albedo;
static CTextureReference g_tex_Position;
static CTextureReference g_tex_Normal;
static CTextureReference g_tex_MR;
static CTextureReference g_tex_Light;

static int iWidth;
static int iHeight;


/* RT Names
 */
#define DEFRTNAME_GBUFFER0 "_rt_defAlbedo"
#define DEFRTNAME_GBUFFER1 "_rt_defPosition"
#define DEFRTNAME_GBUFFER2 "_rt_defNormal"
#define DEFRTNAME_GBUFFER3 "_rt_defMR"
#define DEFRTNAME_GBUFFER4 "_rt_defLightPass"

static float g_flDepthScalar = 65536.0f;

float GetDepthMapDepthResolution(float zDelta) {
    return zDelta / g_flDepthScalar;
}

void GetGBufferResolution(int &iW, int &iH) {
    iW = iWidth;
    iH = iHeight;
    return;
}

void DefRTsOnModeChanged() {
    InitDeferredRTs();
}

static void ShutDownDeferredRTs() {
    g_tex_Albedo.Shutdown();
    g_tex_Position.Shutdown();
    g_tex_Normal.Shutdown();
    g_tex_MR.Shutdown();
    g_tex_Light.Shutdown();
}

void InitDeferredRTs(bool bInitial) {
    if (!bInitial) {
        materials->BeginRenderTargetAllocation(); // HAHAHAHA. No.
        ShutDownDeferredRTs();
    }
    const ImageFormat fmt_gbuffer0 = IMAGE_FORMAT_RGB888;
    const ImageFormat fmt_gbuffer1 = IMAGE_FORMAT_RGBA32323232F;
    const ImageFormat fmt_gbuffer2 = IMAGE_FORMAT_RGBA16161616F;
    const ImageFormat fmt_gbuffer3 = IMAGE_FORMAT_RGBA16161616F;
    const ImageFormat fmt_gbuffer4 = IMAGE_FORMAT_RGBA16161616F;

    const unsigned int gbufferFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT;

    materials->BeginRenderTargetAllocation();

    //if (bInitial)
    {
        int iW, iH;
        materials->GetBackBufferDimensions(iW, iH);
        if (!bInitial) {
            iW = view->GetViewSetup()->width;
            iH = view->GetViewSetup()->height;
        }
        iWidth = iW;
        iHeight = iH;
        g_tex_Albedo.Init(materials->CreateNamedRenderTargetTextureEx2(DEFRTNAME_GBUFFER0,
                                                                       iW, iH,
                                                                       RT_SIZE_NO_CHANGE,
                                                                       fmt_gbuffer0,
                                                                       MATERIAL_RT_DEPTH_SHARED,
                                                                       gbufferFlags, 0));

        g_tex_Position.Init(materials->CreateNamedRenderTargetTextureEx2(DEFRTNAME_GBUFFER1,
                                                                         iW, iH,
                                                                         RT_SIZE_NO_CHANGE,
                                                                         fmt_gbuffer1,
                                                                         MATERIAL_RT_DEPTH_SHARED,
                                                                         gbufferFlags, 0));

        g_tex_Normal.Init(materials->CreateNamedRenderTargetTextureEx2(DEFRTNAME_GBUFFER2,
                                                                       iW, iH,
                                                                       RT_SIZE_NO_CHANGE,
                                                                       fmt_gbuffer2,
                                                                       MATERIAL_RT_DEPTH_SHARED,
                                                                       gbufferFlags, 0));

        g_tex_MR.Init(materials->CreateNamedRenderTargetTextureEx2(DEFRTNAME_GBUFFER3,
                                                                   iW, iH,
                                                                   RT_SIZE_NO_CHANGE,
                                                                   fmt_gbuffer3,
                                                                   MATERIAL_RT_DEPTH_SHARED,
                                                                   gbufferFlags, 0));

        g_tex_Light.Init(materials->CreateNamedRenderTargetTextureEx2(DEFRTNAME_GBUFFER4,
                                                                      iW, iH,
                                                                      RT_SIZE_NO_CHANGE,
                                                                      fmt_gbuffer4,
                                                                      MATERIAL_RT_DEPTH_SHARED,
                                                                      gbufferFlags, 0));

    }

    materials->EndRenderTargetAllocation();
}

ITexture *GetDefRT_MR() {
    return g_tex_MR;
}

ITexture *GetDefRT_PosNormal(bool position) {
    if (position)
        return g_tex_Position;
    else
        return g_tex_Normal;
}

ITexture *GetDefRT_Albedo() {
    return g_tex_Albedo;
}

ITexture *GetDefRT_Light() {
    return g_tex_Light;
}
