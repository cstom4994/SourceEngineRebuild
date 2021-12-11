#ifndef VANCE_SCREENSPACEEFFECTS_H
#define VANCE_SCREENSPACEEFFECTS_H
#ifdef _WIN32
#pragma once
#endif

#include "ScreenSpaceEffects.h"

class CFXAA : public IScreenSpaceEffect {
public:
    CFXAA(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CMaterialReference m_Luma;
    CMaterialReference m_FXAA;
};

class CTonemap : public IScreenSpaceEffect {
public:
    CTonemap(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CMaterialReference m_Tonemap;
};

class CSSAO : public IScreenSpaceEffect {
public:
    CSSAO(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CTextureReference m_Normal;
    CTextureReference m_SSAO;
    CTextureReference m_SSAOX;
    CTextureReference m_SSAOY;

    CMaterialReference m_SSAO_Mat;
    CMaterialReference m_SSAO_BilateralX;
    CMaterialReference m_SSAO_BilateralY;
    CMaterialReference m_SSAO_Combine;
};

class CUnsharpEffect : public IScreenSpaceEffect {
public:
    CUnsharpEffect(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CTextureReference m_UnsharpBlurFB;
    CMaterialReference m_UnsharpBlur;
    CMaterialReference m_Unsharp;
};

class CWaterEffects : public IScreenSpaceEffect {
public:
    CWaterEffects(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params);

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

    virtual float GetViscosity() { return fViscosity; }

    virtual float GetAmount() { return fAmount; }

    virtual void SetViscosity(float fNewViscosity) { fViscosity = fNewViscosity; }

    virtual void SetAmount(float fNewAmount) { fAmount = fNewAmount; }

    virtual bool IsUnderwater() { return m_bUnderwater; }

private:
    bool m_bEnabled;
    bool m_bUnderwater;

    float fViscosity;
    float fAmount;

    CMaterialReference m_ChromaticDisp;
    CMaterialReference m_WaterFX;
    CMaterialReference m_BlurX;
    CMaterialReference m_BlurY;
};

class CBloom : public IScreenSpaceEffect {
public:
    CBloom(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CTextureReference m_BloomDS;
    CTextureReference m_BloomDS1;
    CTextureReference m_BloomDS2;
    CTextureReference m_BloomDS3;

    CTextureReference m_BloomFB0;
    CTextureReference m_BloomFB1;

    CMaterialReference m_BloomSample;
    CMaterialReference m_GaussianX;
    CMaterialReference m_GaussianY;
    CMaterialReference m_BloomDownsample;
    CMaterialReference m_BloomCombine;
};

class CVolumetrics : public IScreenSpaceEffect {
public:
    CVolumetrics(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CTextureReference m_VolumetricsFB0;

    CMaterialReference m_VolumetricsSample;
    CMaterialReference m_VolumetricsCombine;
};


class CSSR : public IScreenSpaceEffect {
public:
    CSSR(void) {};

    virtual void Init(void);

    virtual void Shutdown(void);

    virtual void SetParameters(KeyValues *params) {};

    virtual void Enable(bool bEnable) { m_bEnabled = bEnable; }

    virtual bool IsEnabled() { return m_bEnabled; }

    virtual void Render(int x, int y, int w, int h);

private:
    bool m_bEnabled;

    CTextureReference m_SSR;
    CTextureReference m_SSRX;
    CTextureReference m_SSRY;

    CMaterialReference m_SSR_BilateralX;
    CMaterialReference m_SSR_BilateralY;

    CMaterialReference m_SSR_Mat;
    CMaterialReference m_SSR_Add;
};

#endif