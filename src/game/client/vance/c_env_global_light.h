#ifndef C_GLOBAL_LIGHT_H
#define C_GLOBAL_LIGHT_H

#include "c_baseentity.h"

//------------------------------------------------------------------------------
// Purpose : Sunlights shadow control entity
//------------------------------------------------------------------------------
class C_GlobalLight : public C_BaseEntity {
public:
    DECLARE_CLASS(C_GlobalLight, C_BaseEntity);

    DECLARE_CLIENTCLASS();

    C_GlobalLight();

    virtual ~C_GlobalLight();

    void OnDataChanged(DataUpdateType_t updateType);

    void Spawn();

    bool ShouldDraw();

    void ClientThink();

    bool IsCascadedShadowMappingEnabled() const;

    bool IsVolumetricsEnabled() const;

    bool IsDynamicSkyEnabled() const;

    bool UsesTimeForAngles() const;

    float DayNightTimescale() const;

    float CurrentTime() const;

    void GetShadowMappingConstants(QAngle &angSunAngles, Vector &vecLight, Vector &vecAmbient) const {
        angSunAngles = m_angSunAngles;
        vecLight = m_vecLight;
        vecAmbient = m_vecAmbient;
    }

private:
    QAngle m_angSunAngles;
    Vector m_vecLight;
    Vector m_vecAmbient;
    bool m_bCascadedShadowMappingEnabled;
    Vector m_shadowDirection;
    bool m_bEnabled;
    char m_TextureName[MAX_PATH];
    CTextureReference m_SpotlightTexture;
    Vector m_LinearFloatLightColor;
    Vector m_LinearFloatAmbientColor;
    Vector m_CurrentLinearFloatLightColor;
    float m_flCurrentLinearFloatLightAlpha;
    float m_flColorTransitionTime;
    float m_flSunDistance;
    float m_flFOV;
    float m_flNearZ;
    float m_flNorthOffset;
    bool m_bEnableShadows;
    bool m_bOldEnableShadows;

    bool m_bEnableVolumetrics;
    bool m_bEnableDynamicSky;
    bool m_bEnableTimeAngles;
    float m_flDayNightTimescale;
    float m_fTime;
};

extern C_GlobalLight *g_pCSMLight;

#endif // !C_GLOBAL_LIGHT_H