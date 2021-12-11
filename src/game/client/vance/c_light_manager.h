#ifndef C_LIGHT_MANAGER_H
#define C_LIGHT_MANAGER_H

#include "igamesystem.h"
#include "UtlVector.h"
#include "../../public/mathlib/vector4d.h"

#define DEFLIGHT_SPOT_ZNEAR 8.0f
#define DEFLIGHT_SPOT_RESOLUTION 1024

struct volume_light_t {
    volume_light_t() {
    }

    FlashlightState_t *state;
    VMatrix spotWorldToTex;
    ITexture *depth;
    QAngle angles;
    Vector origin;
    float intensity;
    ClientShadowHandle_t *handle;
};

class CLightingManager : public CAutoGameSystemPerFrame {
    typedef CAutoGameSystemPerFrame BaseClass;
public:
    CLightingManager::CLightingManager() : BaseClass("LightingManagerSystem") {
    }

    ~CLightingManager() {};


    void AddLight(volume_light_t *l);

    bool RemoveLight(volume_light_t *l);

    void AddLight(LightDesc_t *l);

    bool RemoveLight(LightDesc_t *l);

    volume_light_t *GetLight(int l) { return m_hVolumetricLights[l]; };

    int GetLightNumber(volume_light_t *l) { return m_hVolumetricLights.Find(l); };

    IMesh *GetViewVolumetrics() { return m_meshViewVolumetrics; };

    void ClearVolumetricsMesh();

    int CountLight() { return m_hVolumetricLights.Count(); };

    void PrepareShadowLights();

    void RenderLights(const CViewSetup &view);

    void RenderVolumetrics(const CViewSetup &view);

    void CommitLights();

    void FlushLights();

    void SetRenderConstants(const VMatrix &ScreenToWorld,
                            const CViewSetup &setup);

    // Called before rendering
    //virtual void PreRender() { CommitLights(); }
    virtual void LevelInitPreEntity();

private:
    void RebuildVolumetricMesh();

    CUtlVector<volume_light_t *> m_hVolumetricLights;
    CUtlVector<LightDesc_t *> m_hLights;
    CMaterialReference m_matVolumetricsMaterial;
    CMaterialReference m_matLightMaterial;
    IMesh *m_meshViewVolumetrics;
    IMesh *m_meshLightCube;

    VMatrix m_matScreenToWorld;
    Vector m_vecViewOrigin;
    Vector m_vecForward;
    CViewSetup m_view;
    float m_flzNear;
};

extern CLightingManager *GetLightingManager();

#endif