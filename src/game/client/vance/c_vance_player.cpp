//============================ AdV Software, 2019 ============================//
//
//	Vance player entity
//
//============================================================================//

#include "cbase.h"
#include "c_vance_player.h"
#include "flashlighteffect.h"
#include "c_bobmodel.h"
#include "vance_viewmodel.h"
#include "view_scene.h"
#include "ivieweffects.h"
#include "prediction.h"
#include "view.h"

ConVar cl_viewpunch_power("cl_viewpunch_power", "0.4", 0, "", true, 0.0f, true, 1.0f);
ConVar cl_viewbob_enabled("cl_viewbob_enabled", "0");
ConVar cl_viewbob_speed("cl_viewbob_speed", "10");
ConVar cl_viewbob_height("cl_viewbob_height", "5");
ConVar cl_viewbob_viewmodel_add("cl_viewbob_viewmodel_add", "0.1");

ConVar cl_flashlight_lag_interp("cl_flashlight_lag_interp", "0.05", FCVAR_CHEAT);
extern ConVar r_flashlightfov;

extern void FormatViewModelAttachment(Vector &vOrigin, bool bInverse);

inline C_VancePlayer *ToVancePlayer(C_BaseEntity *pPlayer) {
    Assert(dynamic_cast<C_VancePlayer *>( pPlayer ) != NULL);
    return static_cast<C_VancePlayer *>( pPlayer );
}

IMPLEMENT_CLIENTCLASS_DT(C_VancePlayer, DT_Vance_Player, CVancePlayer)
                    RecvPropFloat(RECVINFO(m_flKickAnimLength)),
END_RECV_TABLE()

BEGIN_PREDICTION_DATA(C_VancePlayer)
END_PREDICTION_DATA()

C_VancePlayer::C_VancePlayer() :
        m_LagAnglesHistory("C_VancePlayer::CalcFlashlightLag") {
    m_vecLagAngles.Init();
    m_LagAnglesHistory.Setup(&m_vecLagAngles, 0);

    m_pBobViewModel = NULL;
    m_flBobModelAmount = 0.0f;
    m_angLastBobAngle = vec3_angle;
    m_vecLastBobPos = vec3_origin;
    m_fBobTime = 0.0f;
    m_fLastBobTime = 0.0f;
}


C_VancePlayer::~C_VancePlayer() {
    if (m_pBobViewModel)
        m_pBobViewModel->Release();
}

void C_VancePlayer::CalcFlashlightLag(Vector &vecForward, Vector &vecRight, Vector &vecUp) {
    QAngle angles;
    VectorAngles(vecForward, vecUp, angles);

    // Add an entry to the history.
    m_vecLagAngles = angles;
    m_LagAnglesHistory.NoteChanged(gpGlobals->curtime, cl_flashlight_lag_interp.GetFloat(), false);

    // Interpolate back 100ms.
    m_LagAnglesHistory.Interpolate(gpGlobals->curtime, cl_flashlight_lag_interp.GetFloat());

    // Now take the 100ms angle difference
    QAngle angleDiff = m_vecLagAngles - angles;
    angles += angleDiff;

    AngleVectors(angles, &vecForward, &vecRight, &vecUp);
}

float C_VancePlayer::GetFlashlightFOV() const {
    return r_flashlightfov.GetFloat();
}

//-----------------------------------------------------------------------------
// Purpose: Creates, destroys, and updates the flashlight effect as needed.
//-----------------------------------------------------------------------------
void C_VancePlayer::UpdateFlashlight() {
    // The dim light is the flashlight.
    if (IsEffectActive(EF_DIMLIGHT)) {
        // Make sure we're using the proper flashlight texture
        const char *pszTextureName = GetFlashlightTextureName();

        // Turned on the headlight; create it.
        if (pszTextureName) {
            FlashlightEffectManager().TurnOnFlashlight(index, pszTextureName, GetFlashlightFOV(),
                                                       GetFlashlightFarZ(), GetFlashlightLinearAtten());
        } else {
            FlashlightEffectManager().TurnOnFlashlight(index);
        }
    } else {
        // Turned off the flashlight; delete it.
        FlashlightEffectManager().TurnOffFlashlight();
    }

    QAngle angLightDir;
    Vector vecLightOrigin, vecForward, vecRight, vecUp;

    CBaseCombatWeapon *pWeapon = GetActiveWeapon();
    if (!IsSuitEquipped() && pWeapon) {
        C_BaseViewModel *pVM = GetViewModel();
        if (pVM) {
            // If we have a flashlight attachment, use that.
            int iFlashlightAttachment = pVM->LookupAttachment("flashlight");
            if (iFlashlightAttachment > 0) {
                pVM->GetAttachment(iFlashlightAttachment, vecLightOrigin, angLightDir);
            } else {
                // Looks like we don't have a flashlight attachment, let's settle with the muzzle.
                pVM->GetAttachment(1, vecLightOrigin, angLightDir);
            }

            ::FormatViewModelAttachment(vecLightOrigin, true);
        }

        AngleVectors(angLightDir, &vecForward, &vecRight, &vecUp);
    } else {
        EyeVectors(&vecForward, &vecRight, &vecUp);
        CalcFlashlightLag(vecForward, vecRight, vecUp);
        vecLightOrigin = EyePosition();
    }

    // Update the light with the new position and direction.
    FlashlightEffectManager().UpdateFlashlight(vecLightOrigin, vecForward, vecRight, vecUp, GetFlashlightFOV(),
                                               CastsFlashlightShadows(), GetFlashlightFarZ(),
                                               GetFlashlightLinearAtten(),
                                               GetFlashlightTextureName());
}

//-----------------------------------------------------------------------------
// Called when not in tactical mode. Allows view to be overriden for things like driving a tank.
//-----------------------------------------------------------------------------
void C_VancePlayer::OverrideView(CViewSetup *pSetup) {
    if (!this)
        return;

    if (!GetActiveWeapon())
        return;

    // shake derived from viewmodel
    CVanceViewModel *pViewModel = (CVanceViewModel *) GetViewModel();

    if (pViewModel != NULL
        && pViewModel->GetModelPtr() != NULL
        && pViewModel->GetWeapon() != NULL
            ) {
        if (m_pBobViewModel == NULL) {
            const char *pszName = modelinfo->GetModelName(pViewModel->GetModel());

            if (pszName && *pszName) {
                m_pBobViewModel = new C_BobModel();

                m_pBobViewModel->InitializeAsClientEntity(pszName, RENDER_GROUP_OTHER);
            }
        }

        if (m_pBobViewModel->GetModelIndex() != pViewModel->GetModelIndex()) {
            const char *pszName = modelinfo->GetModelName(pViewModel->GetModel());

            if (pszName && *pszName) {
                m_pBobViewModel->SetModel(pszName);

                m_pBobViewModel->SetAttachmentInfo(pViewModel->GetWeapon()->GetVanceWpnData());
            }
        }

        if (m_pBobViewModel->IsDirty()) {
            m_pBobViewModel->UpdateDefaultTransforms();
            m_pBobViewModel->SetDirty(false);
        }

        //extern void FormatViewModelAttachment( Vector &vOrigin, bool bInverse );

        if (!m_pBobViewModel->IsInvalid()) {
            m_pBobViewModel->SetSequence(pViewModel->GetSequence());
            m_pBobViewModel->SetCycle(pViewModel->GetCycle());

            QAngle ang;
            Vector pos;
            m_pBobViewModel->GetDeltaTransforms(ang, pos);
            m_angLastBobAngle = ang * 0.15f;
            m_vecLastBobPos = pos * 0.15f;
        }
    }

    float flGoalBobAmount = (m_pBobViewModel
                             && !m_pBobViewModel->IsInvalid()
                             && m_pBobViewModel->CanBobDuringActivity(GetActiveWeapon()->GetActivity()))
                            ? 1.0f : 0.0f;

    if (m_flBobModelAmount != flGoalBobAmount) {
        m_flBobModelAmount = Approach(flGoalBobAmount, m_flBobModelAmount, gpGlobals->frametime * 5.0f);
    }

    if (render->GetViewEntity() == entindex()) {
        pSetup->angles += m_angLastBobAngle
                          * m_flBobModelAmount;
        pSetup->origin += m_vecLastBobPos
                          * m_flBobModelAmount;
    }
}

C_BaseCombatWeapon *C_VancePlayer::GetDeployingWeapon(void) const {
    // If localplayer is in InEye spectator mode, return weapon on chased player.
    const C_BasePlayer *fromPlayer = this;
    if (fromPlayer == GetLocalPlayer() && GetObserverMode() == OBS_MODE_IN_EYE) {
        C_BaseEntity *target = GetObserverTarget();
        if (target && target->IsPlayer()) {
            fromPlayer = ToBasePlayer(target);
        }
    }

    return fromPlayer->C_BaseCombatCharacter::GetDeployingWeapon();
}

//=========================================================
// Autoaim
// set crosshair position to point to enemey
//=========================================================
Vector C_VancePlayer::GetAutoaimVector(float flScale) {
    // Never autoaim a predicted weapon (for now)
    Vector forward;
    AngleVectors(MainViewAngles() + m_Local.m_vecPunchAngle * (1.0f - cl_viewpunch_power.GetFloat()), &forward);
    return forward;
}

void C_VancePlayer::AddViewBob(Vector &eyeOrigin, QAngle &eyeAngles, bool calculate) {
    if (cl_viewbob_enabled.GetBool()) {
        float cycle;

        //Find the speed of the player
        float speed = GetLocalVelocity().Length2D();
        speed = clamp(speed, -320, 320);

        float bob_offset = 1.0f - RemapVal(speed, 0, 320, 0.0f, 1.0f);
        bob_offset *= bob_offset;
        bob_offset = 1.0f - bob_offset;

        // since bobtime and lastbobtime are static, it will add more to the values on every function call
        // this should prevent it
        if (calculate) {
            m_fBobTime += (gpGlobals->curtime - m_fLastBobTime) * bob_offset * cl_viewbob_speed.GetFloat();
            m_fLastBobTime = gpGlobals->curtime;
        }

        cycle = m_fBobTime;

        eyeOrigin.z += abs(sin(cycle)) * cl_viewbob_height.GetFloat() * bob_offset;
    }
}

void C_VancePlayer::CalcPlayerView(Vector &eyeOrigin, QAngle &eyeAngles, float &fov) {
    if (!prediction->InPrediction()) {
        // FIXME: Move into prediction
        view->DriftPitch();
    }

    VectorCopy(EyePosition(), eyeOrigin);
    VectorCopy(EyeAngles(), eyeAngles);

    if (!prediction->InPrediction()) {
        SmoothViewOnStairs(eyeOrigin);
    }

    // Snack off the origin before bob + water offset are applied
    Vector vecBaseEyePosition = eyeOrigin;

    CalcViewRoll(eyeAngles);

    // Apply punch angle
    VectorAdd(eyeAngles, m_Local.m_vecPunchAngle * cl_viewpunch_power.GetFloat(), eyeAngles);

    if (!prediction->InPrediction()) {
        // Shake it up baby!
        vieweffects->CalcShake();
        vieweffects->ApplyShake(eyeOrigin, eyeAngles, 1.0);
    }

    // Apply a smoothing offset to smooth out prediction errors.
    Vector vSmoothOffset;
    GetPredictionErrorSmoothingVector(vSmoothOffset);
    eyeOrigin += vSmoothOffset;
    m_flObserverChaseDistance = 0.0;

    AddViewBob(eyeOrigin, eyeAngles, true);

    // calc current FOV
    fov = GetFOV();
}

void C_VancePlayer::CalcViewModelView(const Vector &eyeOrigin, const QAngle &eyeAngles) {
    for (int i = 0; i < MAX_VIEWMODELS; i++) {
        CBaseViewModel *vm = GetViewModel(i);
        if (!vm)
            continue;

        QAngle punchedAngle;
        VectorAdd(eyeAngles, m_Local.m_vecPunchAngle * (1.0f - cl_viewpunch_power.GetFloat()), punchedAngle);

        Vector bobOffset = vec3_origin;
        QAngle blah;
        AddViewBob(bobOffset, blah);

        vm->CalcViewModelView(this, eyeOrigin + bobOffset * cl_viewbob_viewmodel_add.GetFloat(), punchedAngle);
    }
}
