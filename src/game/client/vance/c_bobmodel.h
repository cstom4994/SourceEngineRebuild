#ifndef C_BOBMODEL_H
#define C_BOBMODEL_H

#include "c_baseanimating.h"
#include "vance_weapon_parse.h"
#include "baseentity_shared.h"

class C_BobModel : public C_BaseAnimating {
    DECLARE_CLASS(C_BobModel, C_BaseAnimating);
public:
    C_BobModel();

    virtual int ObjectCaps() {
        return FCAP_DONT_SAVE;
    };

    virtual bool ShouldDraw() { return true; }

    virtual int DrawModel(int flags) { return 0; }

    virtual void FireEvent(const Vector &origin, const QAngle &angles, int event, const char *options) {}

    virtual CStudioHdr *OnNewModel();

    bool IsDirty() const;

    void SetDirty(bool bDirty);

    bool IsInvalid() const;

    void UpdateDefaultTransforms();

    void GetDeltaTransforms(QAngle &angDelta, Vector &posDelta);

    void SetAttachmentInfo(const VanceWeaponInfo_t &info);

    bool CanBobDuringActivity(Activity act);

private:
    bool GetTransforms(Vector &pos, QAngle &ang);

    bool m_bDirty;
    bool m_bInvalid;

    QAngle m_angIdle;
    Vector m_posIdle;

    int m_iBoneFollow;
    int m_iAttachmentFollow;

    float m_flScale;
    float m_flReferenceCycle;

    bool m_bActivate;

    QAngle m_angOrientation;
    QAngle m_angOffset;
};


#endif