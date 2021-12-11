#include "cbase.h"
#include "screenspaceeffects.h"
#include "rendertexture.h"
#include "model_types.h"
#include "materialsystem/imaterialsystemhardwareconfig.h"
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/imaterialvar.h"
#include "cdll_client_int.h"
#include "materialsystem/itexture.h"
#include "keyvalues.h"
#include "ClientEffectPrecacheSystem.h"
#include "viewrender.h"
#include "view_scene.h"
#include "c_basehlplayer.h"
#include "tier0/vprof.h"
#include "view.h"
#include "hl2_gamerules.h"

#include "deferred_screenspace_effects.h"
#include "deferred_rt.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Specifically for Deferred lighting pass
//-----------------------------------------------------------------------------
static void DrawLightingPass(IMaterial *pMaterial, int x, int y, int w, int h, bool shouldScale = false) {
    ITexture *pTexture = GetFullFrameFrameBufferTexture(0);
    UpdateScreenEffectTexture(0, x, y, w, h, false);

    CMatRenderContextPtr pRenderContext(materials);

    pRenderContext->DrawScreenSpaceRectangle(pMaterial, x, y, w * (shouldScale ? (pTexture->GetActualWidth() / w) : 1),
                                             h * (shouldScale ? (pTexture->GetActualHeight() / h) : 1),
                                             x, y, x + w - 1, y + h - 1,
                                             w, h);
}

static void SetRenderTargetAndViewPort(ITexture *rt) {
    CMatRenderContextPtr pRenderContext(materials);
    pRenderContext->SetRenderTarget(rt);
    pRenderContext->Viewport(0, 0, rt->GetActualWidth(), rt->GetActualHeight());
}

void CFXAA::Init(void) {
    PrecacheMaterial("shaders/fxaa_luma");
    PrecacheMaterial("shaders/fxaa");

    m_Luma.Init(materials->FindMaterial("shaders/fxaa_luma", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_FXAA.Init(materials->FindMaterial("shaders/fxaa", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CFXAA::Shutdown(void) {
    m_Luma.Shutdown();
    m_FXAA.Shutdown();
}

ConVar r_post_fxaa("r_post_fxaa", "1", FCVAR_ARCHIVE);
ConVar r_post_fxaa_quality("r_post_fxaa_quality", "4", FCVAR_ARCHIVE,
                           "0 = Very Low, 1 = Low, 2 = Medium, 3 = High, 4 = Very High", true, 0, true, 4);

void CFXAA::Render(int x, int y, int w, int h) {
    VPROF("CFXAA::Render");

    if (!r_post_fxaa.GetBool() || (IsEnabled() == false))
        return;

    IMaterialVar *var;
    var = m_FXAA->FindVar("$QUALITY", NULL);
    var->SetIntValue(r_post_fxaa_quality.GetInt());

    CMatRenderContextPtr pRenderContext(materials);
    pRenderContext->OverrideDepthEnable(true, false);
    DrawScreenEffectMaterial(m_Luma, x, y, w, h);
    DrawScreenEffectMaterial(m_FXAA, x, y, w, h);
    pRenderContext->OverrideDepthEnable(false, true);
}

void CTonemap::Init(void) {
    PrecacheMaterial("shaders/tonemap");

    m_Tonemap.Init(materials->FindMaterial("shaders/tonemap", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CTonemap::Shutdown(void) {
    m_Tonemap.Shutdown();
}

ConVar r_post_tonemap("r_post_tonemap", "1", FCVAR_ARCHIVE);

void CTonemap::Render(int x, int y, int w, int h) {
    VPROF("CFXAA::Render");

    if (!r_post_tonemap.GetBool() || (IsEnabled() == false))
        return;

    DrawScreenEffectMaterial(m_Tonemap, x, y, w, h);
}

void CSSAO::Init(void) {
    PrecacheMaterial("shaders/ssgi");
    PrecacheMaterial("shaders/ssao_bilateralx");
    PrecacheMaterial("shaders/ssao_bilateraly");
    PrecacheMaterial("shaders/ssgi_combine");

    m_Normal.Init("_rt_Normals", TEXTURE_GROUP_RENDER_TARGET);
    m_SSAO.InitRenderTarget(ScreenWidth() / 2, ScreenHeight() / 2, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                            MATERIAL_RT_DEPTH_NONE, false, "_rt_SSAOFB");
    m_SSAOX.InitRenderTarget(ScreenWidth(), ScreenHeight(), RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                             MATERIAL_RT_DEPTH_NONE, false, "_rt_SSAOFBX");
    m_SSAOY.InitRenderTarget(ScreenWidth(), ScreenHeight(), RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                             MATERIAL_RT_DEPTH_NONE, false, "_rt_SSAOFBY");

    m_SSAO_Mat.Init(materials->FindMaterial("shaders/ssgi", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_SSAO_BilateralX.Init(materials->FindMaterial("shaders/ssao_bilateralx", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_SSAO_BilateralY.Init(materials->FindMaterial("shaders/ssao_bilateraly", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_SSAO_Combine.Init(materials->FindMaterial("shaders/ssgi_combine", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CSSAO::Shutdown(void) {
    m_SSAO.Shutdown();
}

ConVar r_post_ssao("r_post_ssao", "0", FCVAR_ARCHIVE);

void CSSAO::Render(int x, int y, int w, int h) {
    VPROF("CFXAA::Render");

    if (!r_post_ssao.GetBool() || (IsEnabled() == false))
        return;
    IMaterialVar *var;
    CMatRenderContextPtr pRenderContext(materials);

    UpdateScreenEffectTexture(0, x, y, w, h, false);
    pRenderContext->PushRenderTargetAndViewport(m_SSAO);
    DrawScreenEffectQuad(m_SSAO_Mat, m_SSAO->GetActualWidth(), m_SSAO->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    UpdateScreenEffectTexture(0, x, y, w, h, false);
    pRenderContext->PushRenderTargetAndViewport(m_SSAOX);
    DrawScreenEffectQuad(m_SSAO_BilateralX, m_SSAOX->GetActualWidth(), m_SSAOX->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    UpdateScreenEffectTexture(0, x, y, w, h, false);
    pRenderContext->PushRenderTargetAndViewport(m_SSAOY);
    DrawScreenEffectQuad(m_SSAO_BilateralY, m_SSAOY->GetActualWidth(), m_SSAOY->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    var = m_SSAO_Combine->FindVar("$AMOUNT", NULL);
    var->SetFloatValue(1.0f);
    DrawScreenEffectMaterial(m_SSAO_Combine, x, y, w, h);

    pRenderContext.SafeRelease();
}

void CUnsharpEffect::Init(void) {
    m_UnsharpBlurFB.InitRenderTarget(ScreenWidth() / 2, ScreenHeight() / 2, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                                     MATERIAL_RT_DEPTH_NONE, false, "_rt_UnsharpBlur");

    PrecacheMaterial("shaders/unsharp_blur");
    PrecacheMaterial("shaders/unsharp");

    m_UnsharpBlur.Init(materials->FindMaterial("shaders/unsharp_blur", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_Unsharp.Init(materials->FindMaterial("shaders/unsharp", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CUnsharpEffect::Shutdown(void) {
    m_UnsharpBlurFB.Shutdown();
    m_UnsharpBlur.Shutdown();
    m_Unsharp.Shutdown();
}

ConVar r_post_unsharp("r_post_unsharp", "1", FCVAR_ARCHIVE);
ConVar r_post_unsharp_debug("r_post_unsharp_debug", "0", FCVAR_CHEAT);
ConVar r_post_unsharp_strength("r_post_unsharp_strength", "0.3", FCVAR_CHEAT);
ConVar r_post_unsharp_blursize("r_post_unsharp_blursize", "5.0", FCVAR_CHEAT);

void CUnsharpEffect::Render(int x, int y, int w, int h) {
    VPROF("CUnsharpEffect::Render");

    if (!r_post_unsharp.GetBool() || (IsEnabled() == false))
        return;

    // Grab the render context
    CMatRenderContextPtr pRenderContext(materials);

    // Set to the proper rendering mode.
    pRenderContext->MatrixMode(MATERIAL_VIEW);
    pRenderContext->PushMatrix();
    pRenderContext->LoadIdentity();
    pRenderContext->MatrixMode(MATERIAL_PROJECTION);
    pRenderContext->PushMatrix();
    pRenderContext->LoadIdentity();

    IMaterialVar *var;
    var = m_UnsharpBlur->FindVar("$blursize", NULL);
    var->SetFloatValue(r_post_unsharp_blursize.GetFloat());

    if (r_post_unsharp_debug.GetBool()) {
        DrawScreenEffectMaterial(m_UnsharpBlur, x, y, w, h);
        return;
    }

    Rect_t actualRect;
    UpdateScreenEffectTexture(0, x, y, w, h, false, &actualRect);
    pRenderContext->PushRenderTargetAndViewport(m_UnsharpBlurFB);
    DrawScreenEffectQuad(m_UnsharpBlur, m_UnsharpBlurFB->GetActualWidth(), m_UnsharpBlurFB->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    //Restore our state
    pRenderContext->MatrixMode(MATERIAL_VIEW);
    pRenderContext->PopMatrix();
    pRenderContext->MatrixMode(MATERIAL_PROJECTION);
    pRenderContext->PopMatrix();

    var = m_Unsharp->FindVar("$fbblurtexture", NULL);
    var->SetTextureValue(m_UnsharpBlurFB);
    var = m_Unsharp->FindVar("$unsharpstrength", NULL);
    var->SetFloatValue(r_post_unsharp_strength.GetFloat());
    var = m_Unsharp->FindVar("$blursize", NULL);
    var->SetFloatValue(r_post_unsharp_blursize.GetFloat());

    DrawScreenEffectMaterial(m_Unsharp, x, y, w, h);
}

ConVar r_post_watereffects_underwater_chromaticoffset("r_post_watereffects_underwater_chromaticoffset", "1.0",
                                                      FCVAR_CHEAT);
ConVar r_post_watereffects_underwater_amount("r_post_watereffects_underwater_amount", "0.1", FCVAR_CHEAT);
ConVar r_post_watereffects_underwater_viscosity("r_post_watereffects_underwater_viscosity", "1.0", FCVAR_CHEAT);
ConVar r_post_watereffects_lerp_viscosity("r_post_watereffects_lerp_viscosity", "0.01", FCVAR_CHEAT);
ConVar r_post_watereffects_lerp_amount("r_post_watereffects_lerp_amount", "0.005", FCVAR_CHEAT);
ConVar r_post_watereffects_underwater_gaussianamount("r_post_watereffects_underwater_gaussianamount", "1.5",
                                                     FCVAR_CHEAT);

void CWaterEffects::Init(void) {
    fViscosity = 0.01;
    fAmount = 0;
    m_bUnderwater = false;

    PrecacheMaterial("shaders/chromaticDisp");
    PrecacheMaterial("shaders/screenwater");
    PrecacheMaterial("shaders/screen_blurx");
    PrecacheMaterial("shaders/screen_blury");

    m_ChromaticDisp.Init(materials->FindMaterial("shaders/chromaticDisp", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_WaterFX.Init(materials->FindMaterial("shaders/screenwater", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_BlurX.Init(materials->FindMaterial("shaders/screen_blurx", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_BlurY.Init(materials->FindMaterial("shaders/screen_blury", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CWaterEffects::Shutdown(void) {
    m_ChromaticDisp.Shutdown();
    m_WaterFX.Shutdown();
    m_BlurX.Shutdown();
    m_BlurY.Shutdown();
}

void CWaterEffects::SetParameters(KeyValues *params) {
    if (IsUnderwater())
        return;

    float in, temp;

    if (params->FindKey("amount")) {
        in = params->GetFloat("amount");
        temp = GetAmount();
        temp += in;
        if (temp > 0.1f)
            temp = 0.1f;

        SetAmount(temp);
    }

    if (params->FindKey("viscosity")) {
        in = params->GetFloat("viscosity");
        temp = GetViscosity();
        temp += in;
        if (temp > 1.0f)
            temp = 1.0f;

        SetViscosity(temp);
    }
}

ConVar r_post_watereffects("r_post_watereffects", "1", FCVAR_ARCHIVE);
ConVar r_post_watereffects_debug("r_post_watereffects_debug", "0", FCVAR_CHEAT);

void CWaterEffects::Render(int x, int y, int w, int h) {
    VPROF("CWaterEffects::Render");

    if (!r_post_watereffects.GetBool() || (IsEnabled() == false))
        return;

    C_BaseHLPlayer *pPlayer = (C_BaseHLPlayer *) C_BasePlayer::GetLocalPlayer();
    if (!pPlayer)
        return;

    IMaterialVar *var;

    if (pPlayer->GetWaterLevel() >= 3) {
        m_bUnderwater = true;
        fViscosity = r_post_watereffects_underwater_viscosity.GetFloat();
        fAmount = r_post_watereffects_underwater_amount.GetFloat();

        //Gaussian Blur the screen
        var = m_BlurX->FindVar("$BLURSIZE", NULL);
        var->SetFloatValue(r_post_watereffects_underwater_gaussianamount.GetFloat());
        var = m_BlurX->FindVar("$RESDIVISOR", NULL);
        var->SetIntValue(1);
        DrawScreenEffectMaterial(m_BlurX, x, y, w, h);
        var = m_BlurY->FindVar("$BLURSIZE", NULL);
        var->SetFloatValue(r_post_watereffects_underwater_gaussianamount.GetFloat());
        var = m_BlurY->FindVar("$RESDIVISOR", NULL);
        var->SetIntValue(1);
        DrawScreenEffectMaterial(m_BlurY, x, y, w, h);

        //Render Chromatic Dispersion
        var = m_ChromaticDisp->FindVar("$FOCUSOFFSET", NULL);
        var->SetFloatValue(r_post_watereffects_underwater_chromaticoffset.GetFloat());
        var = m_ChromaticDisp->FindVar("$radial", NULL);
        var->SetIntValue(0);
        DrawScreenEffectMaterial(m_ChromaticDisp, x, y, w, h);
    } else {
        m_bUnderwater = false;

        if (fViscosity != 0.01)
            fViscosity = FLerp(fViscosity, 0.01, r_post_watereffects_lerp_viscosity.GetFloat());

        if (fAmount != 0)
            fAmount = FLerp(fAmount, 0, r_post_watereffects_lerp_amount.GetFloat());

        if (fAmount < 0.01) {
            if (r_post_watereffects_debug.GetBool()) {
                DevMsg("Water Effects Stopped.\n");
            }
            return;
        }
    }

    var = m_WaterFX->FindVar("$AMOUNT", NULL);
    var->SetFloatValue(fAmount);
    var = m_WaterFX->FindVar("$VISCOSITY", NULL);
    var->SetFloatValue(fViscosity);
    DrawScreenEffectMaterial(m_WaterFX, x, y, w, h);

    if (r_post_watereffects_debug.GetBool()) {
        DevMsg("Water Amount: %.2f\n", fAmount);
        DevMsg("Water Viscosity: %.2f\n", fViscosity);
    }
}

extern void Generate8BitBloomTexture(IMatRenderContext *pRenderContext, float flBloomScale, int x, int y, int w, int h);

extern float GetBloomAmount();

void CBloom::Init(void) {
    PrecacheMaterial("shaders/bloom_sample");
    PrecacheMaterial("shaders/bloom_gaussianx");
    PrecacheMaterial("shaders/bloom_gaussiany");
    PrecacheMaterial("shaders/bloom_combine");
    PrecacheMaterial("shaders/bloom_downsample");

    m_BloomDS.InitRenderTarget(ScreenWidth() / 2, ScreenHeight() / 2, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA16161616F,
                               MATERIAL_RT_DEPTH_NONE, false, "_rt_BloomDS");
    m_BloomDS1.InitRenderTarget(ScreenWidth() / 4, ScreenHeight() / 4, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA16161616F,
                                MATERIAL_RT_DEPTH_NONE, false, "_rt_BloomDS1");
    m_BloomDS2.InitRenderTarget(ScreenWidth() / 8, ScreenHeight() / 8, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA16161616F,
                                MATERIAL_RT_DEPTH_NONE, false, "_rt_BloomDS2");
    m_BloomDS3.InitRenderTarget(ScreenWidth() / 16, ScreenHeight() / 16, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA16161616F,
                                MATERIAL_RT_DEPTH_NONE, false, "_rt_BloomDS3");

    m_BloomFB0.InitRenderTarget(ScreenWidth() / 2, ScreenHeight() / 2, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA16161616F,
                                MATERIAL_RT_DEPTH_NONE, false, "_rt_BloomFB0");
    m_BloomFB1.InitRenderTarget(ScreenWidth() / 2, ScreenHeight() / 2, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA16161616F,
                                MATERIAL_RT_DEPTH_NONE, false, "_rt_BloomFB1");

    m_BloomSample.Init(materials->FindMaterial("shaders/bloom_sample", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_GaussianX.Init(materials->FindMaterial("shaders/bloom_gaussianx", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_GaussianY.Init(materials->FindMaterial("shaders/bloom_gaussiany", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_BloomDownsample.Init(materials->FindMaterial("shaders/bloom_downsample", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_BloomCombine.Init(materials->FindMaterial("shaders/bloom_combine", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CBloom::Shutdown(void) {
    m_BloomFB0.Shutdown();
    m_BloomFB1.Shutdown();
    m_BloomDS.Shutdown();
    m_BloomDS1.Shutdown();
    m_BloomDS2.Shutdown();
    m_BloomDS3.Shutdown();

    m_BloomSample.Shutdown();
    m_GaussianX.Shutdown();
    m_GaussianY.Shutdown();
    m_BloomDownsample.Shutdown();
    m_BloomCombine.Shutdown();
}

ConVar r_post_bloom("r_post_bloom", "1", FCVAR_ARCHIVE);
ConVar r_post_bloom_amount("r_post_bloom_amount", "1", FCVAR_ARCHIVE);
ConVar r_post_bloom_gaussianamount("r_post_bloom_gaussianamount", "1", FCVAR_ARCHIVE);
ConVar r_post_bloom_exposure("r_post_bloom_exposure", "1", FCVAR_ARCHIVE);

void CBloom::Render(int x, int y, int w, int h) {
    VPROF("CBloom::Render");

    if (!r_post_bloom.GetBool() || (IsEnabled() == false))
        return;

    IMaterialVar *var;
    CMatRenderContextPtr pRenderContext(materials);

    Generate8BitBloomTexture(pRenderContext, GetBloomAmount(), x, y, w, h);

    //Gaussian Blur the screen
    var = m_GaussianX->FindVar("$BLURSIZE", NULL);
    var->SetFloatValue(r_post_bloom_gaussianamount.GetFloat());
    var = m_GaussianY->FindVar("$BLURSIZE", NULL);
    var->SetFloatValue(r_post_bloom_gaussianamount.GetFloat());

    var = m_BloomSample->FindVar("$C1_X", NULL);
    var->SetFloatValue(r_post_bloom_exposure.GetFloat());

    pRenderContext->PushRenderTargetAndViewport();
    SetRenderTargetAndViewPort(m_BloomDS);
    DrawScreenEffectQuad(m_BloomSample, m_BloomDS->GetActualWidth(), m_BloomDS->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    pRenderContext->PushRenderTargetAndViewport();
    SetRenderTargetAndViewPort(m_BloomFB0);
    DrawScreenEffectQuad(m_GaussianX, m_BloomFB0->GetActualWidth(), m_BloomFB0->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    pRenderContext->PushRenderTargetAndViewport();
    SetRenderTargetAndViewPort(m_BloomFB1);
    DrawScreenEffectQuad(m_GaussianY, m_BloomFB1->GetActualWidth(), m_BloomFB1->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    var = m_BloomDownsample->FindVar("$C1_X", NULL);
    var->SetFloatValue(1.0f);

    pRenderContext->PushRenderTargetAndViewport();
    SetRenderTargetAndViewPort(m_BloomDS1);
    DrawScreenEffectQuad(m_BloomDownsample, m_BloomDS1->GetActualWidth(), m_BloomDS1->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    pRenderContext->PushRenderTargetAndViewport();
    SetRenderTargetAndViewPort(m_BloomDS2);
    DrawScreenEffectQuad(m_BloomDownsample, m_BloomDS2->GetActualWidth(), m_BloomDS2->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    pRenderContext->PushRenderTargetAndViewport();
    SetRenderTargetAndViewPort(m_BloomDS3);
    DrawScreenEffectQuad(m_BloomDownsample, m_BloomDS3->GetActualWidth(), m_BloomDS3->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    var = m_BloomCombine->FindVar("$AMOUNT", NULL);
    var->SetFloatValue(GetBloomAmount() * r_post_bloom_amount.GetFloat());
    DrawScreenEffectMaterial(m_BloomCombine, x, y, w, h);
}

void CVolumetrics::Init(void) {
    PrecacheMaterial("shaders/volumetrics_combine");
    PrecacheMaterial("shaders/volumetrics_downsample");

    //m_VolumetricsFB0.InitRenderTarget(ScreenWidth() / 16, ScreenHeight() / 16, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888, MATERIAL_RT_DEPTH_NONE, false, "_rt_VolumetricsFB0");
    m_VolumetricsFB0.Init(materials->FindTexture("_rt_VolumetricsBuffer", TEXTURE_GROUP_RENDER_TARGET));
    m_VolumetricsCombine.Init(
            materials->FindMaterial("shaders/volumetrics_combine", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_VolumetricsSample.Init(
            materials->FindMaterial("shaders/volumetrics_downsample", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CVolumetrics::Shutdown(void) {
    m_VolumetricsFB0.Shutdown();
    m_VolumetricsCombine.Shutdown();
}

extern ConVar r_volumetrics;

void CVolumetrics::Render(int x, int y, int w, int h) {
    VPROF("CVolumetrics::Render");

    if (!r_volumetrics.GetBool() || (IsEnabled() == false))
        return;

    CMatRenderContextPtr pRenderContext(materials);

    IMaterialVar *var = m_VolumetricsCombine->FindVar("$C1_X", NULL);
    var->SetFloatValue(1.0f);

    DrawScreenEffectMaterial(m_VolumetricsCombine, x, y, w, h);
}

void CSSR::Init(void) {
    PrecacheMaterial("shaders/SSR");
    PrecacheMaterial("shaders/ssr_add");

    m_SSR.InitRenderTarget(ScreenWidth() / 2, ScreenHeight() / 2, RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                           MATERIAL_RT_DEPTH_NONE, false, "_rt_SSR");
    m_SSRX.InitRenderTarget(ScreenWidth(), ScreenHeight(), RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                            MATERIAL_RT_DEPTH_NONE, false, "_rt_SSRX");
    m_SSRY.InitRenderTarget(ScreenWidth(), ScreenHeight(), RT_SIZE_DEFAULT, IMAGE_FORMAT_RGBA8888,
                            MATERIAL_RT_DEPTH_NONE, false, "_rt_SSRY");

    m_SSR_Mat.Init(materials->FindMaterial("shaders/SSR", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_SSR_Add.Init(materials->FindMaterial("shaders/ssr_add", TEXTURE_GROUP_PIXEL_SHADERS, true));

    m_SSR_BilateralX.Init(materials->FindMaterial("shaders/ssr_bilateralx", TEXTURE_GROUP_PIXEL_SHADERS, true));
    m_SSR_BilateralY.Init(materials->FindMaterial("shaders/ssr_bilateraly", TEXTURE_GROUP_PIXEL_SHADERS, true));
}

void CSSR::Shutdown(void) {
    m_SSR.Shutdown();
    m_SSR_Mat.Shutdown();
    m_SSR_Add.Shutdown();
}

ConVar r_post_ssr("r_post_ssr", "0", FCVAR_ARCHIVE);
ConVar r_post_ssr_raystep("r_post_ssr_raystep", "1", FCVAR_ARCHIVE);
ConVar r_post_ssr_maxdepth("r_post_ssr_maxdepth", "1", FCVAR_ARCHIVE);
ConVar r_post_ssr_stepmul("r_post_ssr_stepmul", "1.0", FCVAR_ARCHIVE);

void CSSR::Render(int x, int y, int w, int h) {
    VPROF("CSSR::Render");

    if (!r_post_ssr.GetBool() || (IsEnabled() == false))
        return;

    CMatRenderContextPtr pRenderContext(materials);

    IMaterialVar *var;
    var = m_SSR_Mat->FindVar("$C1_X", NULL);
    var->SetFloatValue(r_post_ssr_raystep.GetFloat());
    var = m_SSR_Mat->FindVar("$C1_Y", NULL);
    var->SetFloatValue(r_post_ssr_maxdepth.GetFloat());
    var = m_SSR_Mat->FindVar("$C1_Z", NULL);
    var->SetFloatValue(r_post_ssr_stepmul.GetFloat());

    UpdateScreenEffectTexture(0, x, y, w, h, false);
    pRenderContext->PushRenderTargetAndViewport(m_SSR);
    DrawScreenEffectQuad(m_SSR_Mat, m_SSR->GetActualWidth(), m_SSR->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    UpdateScreenEffectTexture(0, x, y, w, h, false);
    pRenderContext->PushRenderTargetAndViewport(m_SSRX);
    DrawScreenEffectQuad(m_SSR_BilateralX, m_SSRX->GetActualWidth(), m_SSRX->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    UpdateScreenEffectTexture(0, x, y, w, h, false);
    pRenderContext->PushRenderTargetAndViewport(m_SSRY);
    DrawScreenEffectQuad(m_SSR_BilateralY, m_SSRY->GetActualWidth(), m_SSRY->GetActualHeight());
    pRenderContext->PopRenderTargetAndViewport();

    var = m_SSR_Add->FindVar("$C1_X", NULL);
    var->SetFloatValue(1.0f);

    DrawScreenEffectMaterial(m_SSR_Add, x, y, w, h);

    pRenderContext.SafeRelease();
}