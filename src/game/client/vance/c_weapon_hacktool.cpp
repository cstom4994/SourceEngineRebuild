#include "cbase.h"
#include "c_basehlcombatweapon.h"
#include "particles_new.h"

class C_WeaponHackTool : public C_BaseHLCombatWeapon {
    DECLARE_CLASS(C_WeaponHackTool, C_BaseHLCombatWeapon);

    DECLARE_CLIENTCLASS();
public:

    void OnDataChanged(DataUpdateType_t updateType);

private:

    CNewParticleEffect *m_pEffect;

    bool m_bHackingLastUpdate;

    CNetworkVar(bool, m_bHacking);

    CNetworkHandle(C_BaseAnimating, m_hTarget);
};

LINK_ENTITY_TO_CLASS(weapon_hacktool, C_WeaponHackTool);

IMPLEMENT_CLIENTCLASS_DT(C_WeaponHackTool, DT_WeaponHackTool, CWeaponHackTool)
                    RecvPropEHandle(RECVINFO(m_hTarget)),
                    RecvPropBool(RECVINFO(m_bHacking)),
END_RECV_TABLE()

void C_WeaponHackTool::OnDataChanged(DataUpdateType_t updateType) {
    if (updateType == DATA_UPDATE_DATATABLE_CHANGED) {
        if (m_bHacking == true && m_bHackingLastUpdate == false) {
            m_pEffect = ParticleProp()->Create("Advisor_Psychic_Beam", PATTACH_ABSORIGIN_FOLLOW,
                                               LookupAttachment("muzzle"));

            if (m_hTarget)
                ParticleProp()->AddControlPoint(m_pEffect, 1, m_hTarget, PATTACH_ABSORIGIN_FOLLOW);
        } else if (m_bHacking == false && m_bHackingLastUpdate == true) {
            m_pEffect->SetRemoveFlag();
        }
    }

    m_bHackingLastUpdate = m_bHacking;
}