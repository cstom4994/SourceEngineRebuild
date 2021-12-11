//============================ AdV Software, 2019 ============================//
//
//	Vance player entity
//
//============================================================================//

#ifndef C_VANCE_PLAYER_H
#define C_VANCE_PLAYER_H

#include "c_basehlplayer.h"
#include "flashlighteffect.h"
#include "c_bobmodel.h"

class C_VancePlayer : public C_BaseHLPlayer {
    DECLARE_CLASS(C_VancePlayer, C_BaseHLPlayer);

    DECLARE_CLIENTCLASS();
DECLARE_PREDICTABLE();

public:
    C_VancePlayer();

    ~C_VancePlayer();

    virtual void UpdateFlashlight();

    virtual const char *GetFlashlightTextureName() const { return "effects/flashlight002"; }

    virtual float GetFlashlightFOV() const;

    virtual float GetFlashlightFarZ() const { return 750.0f; }

    virtual float GetFlashlightLinearAtten() const { return 100.0f; }

    virtual bool CastsFlashlightShadows() { return true; }

    void CalcFlashlightLag(Vector &vecForward, Vector &vecRight, Vector &vecUp);

    virtual void OverrideView(CViewSetup *pSetup);

    C_BaseCombatWeapon *GetDeployingWeapon() const;

    virtual ShadowType_t ShadowCastType() { return SHADOWS_RENDER_TO_TEXTURE_DYNAMIC; }

    float GetKickAnimationLength() { return m_flKickAnimLength; }

    virtual Vector GetAutoaimVector(float flScale);

protected:

    void AddViewBob(Vector &eyeOrigin, QAngle &eyeAngles, bool calculate = false);

    virtual void CalcPlayerView(Vector &eyeOrigin, QAngle &eyeAngles, float &fov);

    virtual void CalcViewModelView(const Vector &eyeOrigin, const QAngle &eyeAngles);

private:
    C_BobModel *m_pBobViewModel;
    float m_flBobModelAmount;
    QAngle m_angLastBobAngle;
    Vector m_vecLastBobPos;

    float m_fBobTime;
    float m_fLastBobTime;

    float m_flKickAnimLength;
    QAngle m_vecLagAngles;
    CInterpolatedVar<QAngle> m_LagAnglesHistory;
};

#endif // C_VANCE_PLAYER_H