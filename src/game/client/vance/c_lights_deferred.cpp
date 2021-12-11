#include "cbase.h"
#include "view_shared.h"
#include "c_light_manager.h"

#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class C_LightDeferred : public C_BaseEntity {
public:
    DECLARE_CLASS(C_LightDeferred, C_BaseEntity);

    DECLARE_CLIENTCLASS();

    ~C_LightDeferred();

    void OnDataChanged(DataUpdateType_t updateType);

    void ClientThink();

    virtual bool ShouldDraw() { return false; }

    virtual int DrawModel(int flags) { return 0; }

private:
    void UpdateLightData();

    CNetworkVector(m_LightColor);

    CNetworkVar(int, m_LightType);

    CNetworkVar(float, m_Range);

    CNetworkVar(float, m_Falloff);

    CNetworkVar(float, m_Attenuation0);

    CNetworkVar(float, m_Attenuation1);

    CNetworkVar(float, m_Attenuation2);

    CNetworkVar(float, m_Theta);

    CNetworkVar(float, m_Phi);

    LightDesc_t m_Light;
};

IMPLEMENT_CLIENTCLASS_DT(C_LightDeferred, DT_LightDeferred, CLightDeferred)
                    RecvPropVector(RECVINFO(m_LightColor)),
                    RecvPropInt(RECVINFO(m_LightType)),
                    RecvPropFloat(RECVINFO(m_Range)),
                    RecvPropFloat(RECVINFO(m_Falloff)),
                    RecvPropFloat(RECVINFO(m_Attenuation0)),
                    RecvPropFloat(RECVINFO(m_Attenuation1)),
                    RecvPropFloat(RECVINFO(m_Attenuation2)),
                    RecvPropFloat(RECVINFO(m_Theta)),
                    RecvPropFloat(RECVINFO(m_Phi)),
END_RECV_TABLE()

C_LightDeferred::~C_LightDeferred() {
    GetLightingManager()->RemoveLight(&m_Light);
}

void C_LightDeferred::OnDataChanged(DataUpdateType_t updateType) {
    UpdateLightData();
    if (updateType == DATA_UPDATE_CREATED) {
        GetLightingManager()->AddLight(&m_Light);
        SetNextClientThink(CLIENT_THINK_ALWAYS);
    }
}

void C_LightDeferred::ClientThink() {
    UpdateLightData();
}

void C_LightDeferred::UpdateLightData() {
    m_Light.m_Color = m_LightColor;
    m_Light.m_Type = (LightType_t) m_LightType.Get();
    m_Light.m_Range = m_Range;
    m_Light.m_Falloff = m_Falloff;
    m_Light.SetupOldStyleAttenuation(m_Attenuation2, m_Attenuation1, m_Attenuation0);
    m_Light.m_Theta = m_Theta;
    m_Light.m_Phi = m_Phi;
    m_Light.m_Position = GetAbsOrigin();
    AngleVectors(GetAbsAngles(), &m_Light.m_Direction);

    m_Light.m_ThetaDot = cos(m_Theta);
    m_Light.m_PhiDot = cos(m_Phi);
}