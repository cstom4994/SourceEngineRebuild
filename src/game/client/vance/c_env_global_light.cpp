//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Sunlight shadow control entity.
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "c_baseplayer.h"
#include "c_env_global_light.h"
#include "viewrender.h"
#include "renderparm.h"
#include "materialsystem/imesh.h"
#include "materialsystem/itexture.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialvar.h"
#include "materialsystem/imaterialsystem.h"
#include "vprof.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

C_GlobalLight *g_pCSMLight;

static ConVar csm_enabled("r_csm", "1", 0, "0 = off, 1 = on/force");
static ConVar r_csm_time("r_csm_time", "-1", 0, "-1 = use entity angles, everything else = force");

// Controls sun position according to time, month, and observer's latitude.
// Sun position computation based on Earth's orbital elements: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html
class CSunController {
public:
    enum month : int {
        January = 0,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    CSunController()
            : m_latitude(50.0f), m_month(June), m_eclipticObliquity(DEG2RAD(23.4f)), m_delta(0.0f) {
        m_northDir = {1.0f, 0.0f, 0.0f};
        m_sunDir = {0.0f, 0.0f, 1.0f};
        m_upDir = {0.0f, 0.0f, 1.0f};
    }

    void Update(float _time) {
        CalculateSunOrbit();
        UpdateSunPosition(_time - 12.0f);
    }

    Vector m_northDir;
    Vector m_sunDir;
    Vector m_upDir;
    float m_latitude;
    month m_month;

private:
    void CalculateSunOrbit() {
        float day = 30.0f * m_month + 15.0f;
        float lambda = 280.46f + 0.9856474f * day;
        lambda = DEG2RAD(lambda);
        m_delta = asin(sin(m_eclipticObliquity) * sin(lambda));
    }

    void UpdateSunPosition(float _hour) {
        const float latitude = DEG2RAD(m_latitude);
        const float hh = _hour * M_PI_F / 12.0f;
        const float azimuth = atan2f(
                sin(hh), cos(hh) * sin(latitude) - tan(m_delta) * cos(latitude)
        );

        const float altitude = asin(
                sin(latitude) * sin(m_delta) + cos(latitude) * cos(m_delta) * cos(hh)
        );

        const Quaternion rot0(m_upDir.x, m_upDir.y, m_upDir.z, -azimuth);
        Vector dir;

        VectorRotate(m_northDir, rot0, dir);
        const Vector uxd = CrossProduct(m_upDir, dir);

        const Quaternion rot1(uxd.x, uxd.y, uxd.z, altitude);
        VectorRotate(dir, rot1, m_sunDir);
    }

    float m_eclipticObliquity;
    float m_delta;
};

CSunController g_sunControl;


IMPLEMENT_CLIENTCLASS_DT(C_GlobalLight, DT_GlobalLight, CGlobalLight)
                    RecvPropVector(RECVINFO(m_shadowDirection)),
                    RecvPropBool(RECVINFO(m_bEnabled)),
                    RecvPropString(RECVINFO(m_TextureName)),
                    RecvPropVector(RECVINFO(m_LinearFloatLightColor)),
                    RecvPropVector(RECVINFO(m_LinearFloatAmbientColor)),
                    RecvPropFloat(RECVINFO(m_flColorTransitionTime)),
                    RecvPropFloat(RECVINFO(m_flSunDistance)),
                    RecvPropFloat(RECVINFO(m_flFOV)),
                    RecvPropFloat(RECVINFO(m_flNearZ)),
                    RecvPropFloat(RECVINFO(m_flNorthOffset)),
                    RecvPropBool(RECVINFO(m_bEnableShadows)),
                    RecvPropBool(RECVINFO(m_bEnableVolumetrics)),
                    RecvPropBool(RECVINFO(m_bEnableDynamicSky)),
                    RecvPropFloat(RECVINFO(m_flDayNightTimescale)),
                    RecvPropFloat(RECVINFO(m_fTime)),
END_RECV_TABLE()

C_GlobalLight::C_GlobalLight()
        : m_angSunAngles(vec3_angle), m_vecLight(vec3_origin), m_vecAmbient(vec3_origin),
          m_bCascadedShadowMappingEnabled(false), m_bEnableDynamicSky(false), m_flDayNightTimescale(1.0f) {
}

C_GlobalLight::~C_GlobalLight() {
    if (g_pCSMLight == this) {
        g_pCSMLight = NULL;
    }
}


bool C_GlobalLight::IsCascadedShadowMappingEnabled() const {
    const int iCSMCvarEnabled = csm_enabled.GetInt();
    return m_bCascadedShadowMappingEnabled && iCSMCvarEnabled >= 1;
}

bool C_GlobalLight::IsVolumetricsEnabled() const {
    return m_bEnableVolumetrics;
}

bool C_GlobalLight::IsDynamicSkyEnabled() const {
    return m_bEnableDynamicSky;
}

bool C_GlobalLight::UsesTimeForAngles() const {
    return m_bEnableTimeAngles;
}

float C_GlobalLight::DayNightTimescale() const {
    return m_flDayNightTimescale;
}

float C_GlobalLight::CurrentTime() const {
    if (r_csm_time.GetFloat() < 0.0f) {
        if (m_fTime < 0.0f)
            return gpGlobals->curtime * DayNightTimescale();
        else
            return m_fTime;
    } else {
        return r_csm_time.GetFloat();
    }
}

void C_GlobalLight::OnDataChanged(DataUpdateType_t updateType) {
    if (updateType == DATA_UPDATE_CREATED) {
        m_SpotlightTexture.Init(m_TextureName, TEXTURE_GROUP_OTHER, true);
    }
    if (g_pCSMLight == NULL) {
        g_pCSMLight = this;
    }

    BaseClass::OnDataChanged(updateType);
}

void C_GlobalLight::Spawn() {
    BaseClass::Spawn();

    m_bOldEnableShadows = m_bEnableShadows;

    SetNextClientThink(CLIENT_THINK_ALWAYS);
}

//------------------------------------------------------------------------------
// We don't draw...
//------------------------------------------------------------------------------
bool C_GlobalLight::ShouldDraw() {
    return false;
}

void C_GlobalLight::ClientThink() {
    if (!m_bEnabled) {
        m_bCascadedShadowMappingEnabled = m_bEnabled;
        return;
    }
    m_bCascadedShadowMappingEnabled = m_bEnabled;

    Vector vDirection = m_shadowDirection;
    if (IsDynamicSkyEnabled()) {
        if (UsesTimeForAngles()) {
            g_sunControl.Update(CurrentTime());
            vDirection = g_sunControl.m_sunDir;
        }
    }

    VectorNormalize(vDirection);

    QAngle angAngles;
    VectorAngles(vDirection, angAngles);

    m_angSunAngles = angAngles;
    m_vecLight = Vector(m_LinearFloatLightColor[0], m_LinearFloatLightColor[1], m_LinearFloatLightColor[2]);
    m_vecAmbient = Vector(m_LinearFloatAmbientColor[0], m_LinearFloatAmbientColor[1], m_LinearFloatAmbientColor[2]);

    BaseClass::ClientThink();
}