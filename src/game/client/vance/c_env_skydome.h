#ifndef C_SKYDOME_H
#define C_SKYDOME_H

#include "cbase.h"
#include "c_baseanimating.h"
#include "weapon_parse.h"
#include "baseentity_shared.h"

class C_SkyDome : public C_BaseAnimating {
    DECLARE_CLASS(C_SkyDome, C_BaseAnimating);
public:
    DECLARE_CLIENTCLASS();

    C_SkyDome();

    ~C_SkyDome();

    virtual int ObjectCaps() {
        return FCAP_DONT_SAVE;
    };

    virtual void Precache();

    virtual void Spawn();

    virtual void ClientThink();


    Vector m_vCurrentSunPos;
    Vector m_vCurrentWindSpeed;
    float m_flCurrentThickness;
    float m_flCurrentCoverage;

    CNetworkVector(m_vDesiredSunPos);

    CNetworkVector(m_vDesiredWindSpeed);

    CNetworkVar(float, m_flDesiredThickness);

    CNetworkVar(float, m_flDesiredCoverage);

    // Should this object cast shadows?
    virtual ShadowType_t ShadowCastType() { return SHADOWS_NONE; }

    virtual bool ShouldDraw() { return false; }

    virtual int DrawModel(int flags) { return BaseClass::DrawModel(flags); }

    virtual void FireEvent(const Vector &origin, const QAngle &angles, int event, const char *options) {}
};

extern C_SkyDome *GetSkyDome();

#endif