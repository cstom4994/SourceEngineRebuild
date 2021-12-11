#include "cbase.h"
#include "c_env_skydome.h"

#include "proxyentity.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialvar.h"
#include "materialsystem/imaterialsystem.h"
#include "rendertexture.h"
#include "viewrender.h"
#include "fmtstr.h"
#include "mathlib\mathlib.h"
#include <KeyValues.h>

ConVarRef cl_sky_sunpos("cl_sky_sunpos");
ConVarRef cl_sky_windspeed("cl_sky_windspeed");
ConVarRef cl_sky_thickness("cl_sky_thickness");
ConVarRef cl_sky_coverage("cl_sky_coverage");
ConVar cl_skydome("cl_skydome", "1");


C_SkyDome *g_pSkyDome;

C_SkyDome *GetSkyDome() {
    return cl_skydome.GetBool() ? g_pSkyDome : NULL;
}


C_SkyDome::C_SkyDome() {
    if (!g_pSkyDome)
        g_pSkyDome = this;

    m_vCurrentSunPos = vec3_origin;
    m_vCurrentWindSpeed = vec3_origin;
    m_flCurrentThickness = 0.0f;
    m_flCurrentThickness = 0.0f;
}


C_SkyDome::~C_SkyDome() {
    if (g_pSkyDome == this) {
        g_pSkyDome = NULL;
    }
}

void C_SkyDome::Precache() {
    PrecacheModel("models/effects/skydome.mdl");
}

void C_SkyDome::Spawn() {
    Precache();
    SetModel("models/effects/skydome.mdl");

    SetNextClientThink(CLIENT_THINK_ALWAYS);
}


void C_SkyDome::ClientThink() {
    BaseClass::ClientThink();

    if (m_vCurrentSunPos != m_vDesiredSunPos) {
        VectorLerp(m_vCurrentSunPos, m_vDesiredSunPos, 0.1f);
    }

    if (m_vCurrentWindSpeed != m_vDesiredWindSpeed) {
        VectorLerp(m_vCurrentWindSpeed, m_vDesiredWindSpeed, 0.1f);

    }

    if (m_flCurrentThickness != m_flDesiredThickness) {
        Lerp(0.1f, float(m_flCurrentThickness), float(m_flDesiredThickness));

    }

    if (m_flCurrentCoverage != m_flDesiredCoverage) {
        Lerp(0.1f, float(m_flCurrentCoverage), float(m_flDesiredCoverage));

    }

    if (cl_sky_sunpos.IsValid())
        cl_sky_sunpos.SetValue(
                VarArgs("%f %f %f %f", m_vCurrentSunPos.x, m_vCurrentSunPos.y, m_vCurrentSunPos.z, 5.0f));
    if (cl_sky_windspeed.IsValid())
        cl_sky_windspeed.SetValue(
                VarArgs("%f %f %f %f", m_vCurrentWindSpeed.x, m_vCurrentWindSpeed.y, m_vCurrentWindSpeed.z, 10.0f));

    if (cl_sky_thickness.IsValid())
        cl_sky_thickness.SetValue(VarArgs("%f", m_flCurrentThickness));
    if (cl_sky_coverage.IsValid())
        cl_sky_coverage.SetValue(VarArgs("%f", m_flCurrentCoverage));

}

IMPLEMENT_CLIENTCLASS_DT(C_SkyDome, DT_SkyDome, CSkyDome)
                    RecvPropVector(RECVINFO(m_vDesiredSunPos)),
                    RecvPropVector(RECVINFO(m_vDesiredWindSpeed)),
                    RecvPropFloat(RECVINFO(m_flDesiredThickness)),
                    RecvPropFloat(RECVINFO(m_flDesiredCoverage)),
END_RECV_TABLE()