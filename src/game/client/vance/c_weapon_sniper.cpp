//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//
#include "cbase.h"
#include "vance_baseweapon_shared.h"
#include "iviewrender_beams.h"
#include "c_weapon__stubs.h"
#include "materialsystem/imaterial.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar vance_sniper_scope_speed("vance_sniper_scope_speed", "1.5", FCVAR_REPLICATED);

float easeInOutBack(float x) {
    const float c1 = 1.70158f;
    const float c2 = c1 * 1.525f;

    return x < 0.5
           ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
           : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

class C_WeaponSniper : public C_BaseVanceWeapon {
    DECLARE_CLASS(C_WeaponSniper, C_BaseVanceWeapon);
public:
    DECLARE_CLIENTCLASS();
DECLARE_PREDICTABLE();

    virtual void CalcIronsight(Vector &origin, QAngle &angles) {
        // bad bad, but im lazy
        if (m_bScoped) {
            if (m_flScope < 1.0f)
                m_flScope += gpGlobals->frametime * vance_sniper_scope_speed.GetFloat();
            else
                m_flScope = 1.0f;
        } else {
            if (m_flScope > 0.0f)
                m_flScope -= gpGlobals->frametime * vance_sniper_scope_speed.GetFloat();
            else
                m_flScope = 0.0f;
        }

        Vector forward, right, up;
        AngleVectors(GetOwner()->EyeAngles(), &forward, &right, &up);

        Vector offset = vec3_origin;
        offset += forward * GetVanceWpnData().vIronsightOffset.x;
        offset += right * GetVanceWpnData().vIronsightOffset.y;
        offset += up * GetVanceWpnData().vIronsightOffset.z;

        float spline = easeInOutBack(m_flScope);
        float curve = SmoothCurve(m_flScope);

        origin += offset * spline;
        angles.z -= curve * 15.0f * ((int) m_bScoped * 2 - 1) * (m_bScoped ? 1.0f : 0.5f);
        origin.z -= curve * 1.5f;
    }


private:
    CNetworkVar(bool, m_bScoped);
    float m_flScope;
};


STUB_WEAPON_CLASS_IMPLEMENT(weapon_sniper, C_WeaponSniper);

IMPLEMENT_CLIENTCLASS_DT(C_WeaponSniper, DT_WeaponSniper, CWeaponSniper)
                    RecvPropBool(RECVINFO(m_bScoped)),
END_RECV_TABLE()

