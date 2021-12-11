#include "cbase.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialvar.h"
#include "materialsystem/imaterialsystem.h"
#include "rendertexture.h"
#include "viewrender.h"
#include "vance/rendering/c_deferred_common.h"
#include "vance/rendering/c_light_manager.h"

class C_LightDeferred : public CBaseEntity {
    DECLARE_CLASS(C_LightDeferred, CBaseEntity
    );
public:
    DECLARE_CLIENTCLASS();

    C_LightDeferred();

    ~C_LightDeferred();

    virtual int ObjectCaps() {
        return FCAP_DONT_SAVE;
    };


    Vector m_vColor;
    Vector m_vPos;
    float m_flBrightness;
    float m_flRadius;

    virtual void OnDataChanged(DataUpdateType_t type);

    virtual void ApplyDataToLight();

    virtual void ClientThink();

    virtual bool ShouldDraw() { return false; }

    virtual int DrawModel(int flags) { return 0; }

    virtual void FireEvent(const Vector &origin, const QAngle &angles, int event, const char *options) {}

    def_light_t *m_light;
};

IMPLEMENT_CLIENTCLASS_DT(C_LightDeferred, DT_LightBasicDeferred, CLightDeferred
)

RecvPropVector(RECVINFO(m_vColor)),
        RecvPropVector(RECVINFO(m_vPos)),
        RecvPropFloat(RECVINFO(m_flBrightness)),
        RecvPropFloat(RECVINFO(m_flRadius)),
        END_RECV_TABLE()

C_LightDeferred::C_LightDeferred() {
}


C_LightDeferred::~C_LightDeferred() {
    if (m_light) {
        GetLightingManager()->RemoveLight(m_light);
        delete m_light;
    }

}

void C_LightDeferred::OnDataChanged(DataUpdateType_t type) {
    if (type == DATA_UPDATE_CREATED) {
        Assert(m_light == NULL);

        m_light = new def_light_t();

        ApplyDataToLight();

        GetLightingManager()->AddLight(m_light);

        SetNextClientThink(CLIENT_THINK_ALWAYS);
    } else {
        ApplyDataToLight();
    }

    return C_BaseEntity::OnDataChanged(type);
}

void C_LightDeferred::ApplyDataToLight() {
    m_light->col_diffuse = Vector4D(m_vColor.x, m_vColor.y, m_vColor.z, m_flBrightness);
    m_light->pos = Vector4D(GetRenderOrigin().x, GetRenderOrigin().y, GetRenderOrigin().z, m_flRadius);
}

void C_LightDeferred::ClientThink() {
    if (m_light == NULL)
        return;

    Vector curOrig = GetRenderOrigin();
    QAngle curAng = GetRenderAngles();

    if (VectorCompare(curOrig.Base(), m_light->pos.Base()) == 0 ||
        VectorCompare(curAng.Base(), m_light->direction.Base()) == 0) {
        ApplyDataToLight();
    }
}

class C_SpotLightDeferred : public C_LightDeferred {
    DECLARE_CLASS(C_SpotLightDeferred, C_LightDeferred
    );
public:
    DECLARE_CLIENTCLASS();

    C_SpotLightDeferred();

    ~C_SpotLightDeferred();


    Vector m_vDirection;
    float m_flRadiusInner;
    float m_flRadiusOuter;

    virtual void OnDataChanged(DataUpdateType_t type);

    virtual void ApplyDataToLight();

    virtual void ClientThink();

    virtual bool ShouldDraw() { return false; }

    virtual int DrawModel(int flags) { return 0; }

    virtual void FireEvent(const Vector &origin, const QAngle &angles, int event, const char *options) {}

    def_light_t *m_light;
};

IMPLEMENT_CLIENTCLASS_DT(C_SpotLightDeferred, DT_LightSpotDeferred, CSpotLightDeferred
)

RecvPropVector(RECVINFO(m_vDirection)),
        RecvPropVector(RECVINFO(m_vPos)),
        RecvPropVector(RECVINFO(m_vColor)),
        RecvPropFloat(RECVINFO(m_flBrightness)),
        RecvPropFloat(RECVINFO(m_flRadiusInner)),
        RecvPropFloat(RECVINFO(m_flRadiusOuter)),
        END_RECV_TABLE()

C_SpotLightDeferred::C_SpotLightDeferred() {
}


C_SpotLightDeferred::~C_SpotLightDeferred() {
    if (m_light) {
        GetLightingManager()->RemoveLight(m_light);
        delete m_light;
    }

}

void C_SpotLightDeferred::OnDataChanged(DataUpdateType_t type) {
    if (type == DATA_UPDATE_CREATED) {
        Assert(m_light == NULL);

        m_light = new def_light_t();

        ApplyDataToLight();

        GetLightingManager()->AddLight(m_light);

        SetNextClientThink(CLIENT_THINK_ALWAYS);
    } else {
        ApplyDataToLight();
    }


    return C_BaseEntity::OnDataChanged(type);
}

void C_SpotLightDeferred::ApplyDataToLight() {

    QAngle curAng = GetRenderAngles();
    Vector curDir;
    AngleVectors(curAng, &curDir);
    m_light->col_diffuse = Vector4D(m_vColor.x, m_vColor.y, m_vColor.z, m_flBrightness);
    m_light->pos = Vector4D(GetRenderOrigin().x, GetRenderOrigin().y, GetRenderOrigin().z,
                            cosf(DEG2RAD(m_flRadiusOuter)));
    m_light->direction = Vector4D(curDir.x, curDir.y, curDir.z, cosf(DEG2RAD(m_flRadiusInner)));
    m_light->ang = curAng;
    m_light->isSpot = true;
}

void C_SpotLightDeferred::ClientThink() {
    if (m_light == NULL)
        return;

    Vector curOrig = GetRenderOrigin();
    QAngle curAng = GetRenderAngles();

    if (VectorCompare(curOrig.Base(), m_light->pos.Base()) == 0 ||
        VectorCompare(curAng.Base(), m_light->direction.Base()) == 0) {
        ApplyDataToLight();
    }
}