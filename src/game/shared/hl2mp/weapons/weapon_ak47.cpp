
#include "cbase.h"
#include "npcevent.h"
#include "in_buttons.h"
#include "weapon_ak47.h"

#ifdef CLIENT_DLL

#include "c_hl2mp_player.h"

#else

#include "hl2mp_player.h"

#endif


IMPLEMENT_NETWORKCLASS_ALIASED(WeaponAK47, DT_WeaponAK47)

BEGIN_NETWORK_TABLE(CWeaponAK47, DT_WeaponAK47)
#ifdef CLIENT_DLL
                    RecvPropInt(RECVINFO(m_iBurst)),
                    RecvPropBool(RECVINFO(m_bInZoom)),
                    RecvPropTime(RECVINFO(m_flAttackEnds)),
                    RecvPropInt(RECVINFO(m_iStance)),
#else
                    SendPropInt(  SENDINFO(m_iBurst)),
                    SendPropBool(SENDINFO(m_bInZoom)),
                    SendPropTime(SENDINFO(m_flAttackEnds)),
                    SendPropInt(SENDINFO(m_iStance)),
#endif
END_NETWORK_TABLE ()

BEGIN_PREDICTION_DATA(CWeaponAK47)

END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS(weapon_AK47, CWeaponAK47);
PRECACHE_WEAPON_REGISTER(weapon_AK47);

acttable_t CWeaponAK47::m_acttable[] =
        {
                {ACT_MP_STAND_IDLE,                ACT_HL2MP_IDLE_AR2,                 false},
                {ACT_MP_CROUCH_IDLE,               ACT_HL2MP_IDLE_CROUCH_AR2,          false},
                {ACT_MP_RUN,                       ACT_HL2MP_RUN_AR2,                  false},
                {ACT_MP_CROUCHWALK,                ACT_HL2MP_WALK_CROUCH_AR2,          false},
                {ACT_MP_ATTACK_STAND_PRIMARYFIRE,  ACT_HL2MP_GESTURE_RANGE_ATTACK_AR2, false},
                {ACT_MP_ATTACK_CROUCH_PRIMARYFIRE, ACT_HL2MP_GESTURE_RANGE_ATTACK_AR2, false},
                {ACT_MP_RELOAD_STAND,              ACT_HL2MP_GESTURE_RELOAD_AR2,       false},
                {ACT_MP_RELOAD_CROUCH,             ACT_HL2MP_GESTURE_RELOAD_AR2,       false},
                {ACT_MP_JUMP,                      ACT_HL2MP_JUMP_AR2,                 false},
        };
IMPLEMENT_ACTTABLE(CWeaponAK47);

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponAK47::CWeaponAK47() {
    m_iBurst = BURST;
    m_iStance = 10;
    m_fMinRange1 = 1;
    m_fMaxRange1 = 1500;
    m_fMinRange2 = 1;
    m_fMaxRange2 = 200;
    m_bFiresUnderwater = false;
}

//-----------------------------------------------------------------------------
// Purpose: Required for caching the entity during loading
//-----------------------------------------------------------------------------
void CWeaponAK47::Precache() {
    BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: The gun is empty, plays a clicking noise with a dryfire anim
//-----------------------------------------------------------------------------
void CWeaponAK47::DryFire() {
    WeaponSound(EMPTY);
    SendWeaponAnim(ACT_VM_DRYFIRE);
    m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
}

//-----------------------------------------------------------------------------
// Purpose: This happens if you click and hold the primary fire button
//-----------------------------------------------------------------------------
void CWeaponAK47::PrimaryAttack() {
    // Do we have any bullets left from the current burst cycle?
    if (m_iBurst != 0) {
        CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
        if (!pPlayer)
            return;

        WeaponSound(SINGLE);
        pPlayer->DoMuzzleFlash();

        SendWeaponAnim(ACT_VM_PRIMARYATTACK);
        pPlayer->SetAnimation(PLAYER_ATTACK1);
        ToHL2MPPlayer(pPlayer)->SetAnimation(PLAYER_ATTACK1);

        // Each time the player fires the gun, reset the view punch
        CBasePlayer *pOwner = ToBasePlayer(GetOwner());
        if (pOwner)
            pOwner->ViewPunchReset();

        BaseClass::PrimaryAttack();

        // We fired one shot, decrease the number of bullets available for this burst cycle
        m_iBurst--;
        m_flNextPrimaryAttack = gpGlobals->curtime + ROF;
        m_flAttackEnds = gpGlobals->curtime + SequenceDuration();
    }
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponAK47::ItemPreFrame() {
    GetStance();

    BaseClass::ItemPreFrame();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponAK47::ItemBusyFrame() {
    // Allow zoom toggling even when we're reloading
    CheckZoomToggle();

    BaseClass::ItemBusyFrame();
}

//-----------------------------------------------------------------------------
// Purpose: Allows firing as fast as the button is pressed
//-----------------------------------------------------------------------------
void CWeaponAK47::ItemPostFrame() {
    BaseClass::ItemPostFrame();

    if (m_bInReload)
        return;

    CBasePlayer *pOwner = ToBasePlayer(GetOwner());
    if (pOwner == NULL)
        return;

    if (pOwner->m_nButtons & IN_ATTACK) {
        if (m_flAttackEnds < gpGlobals->curtime)
            SendWeaponAnim(ACT_VM_IDLE);
    } else {
        // The firing cycle ended. Reset the burst counter to the max value
        m_iBurst = BURST;
        if ((pOwner->m_nButtons & IN_ATTACK) && (m_flNextPrimaryAttack < gpGlobals->curtime) && (m_iClip1 <= 0))
            DryFire();
    }

    CheckZoomToggle();

    // Check the character's current stance for the accuracy calculation
    GetStance();
}

//-----------------------------------------------------------------------------
// Purpose: If we have bullets left then play the attack anim otherwise idle
// Output : int
//-----------------------------------------------------------------------------
Activity CWeaponAK47::GetPrimaryAttackActivity() {
    if (m_iBurst != 0)
        return ACT_VM_PRIMARYATTACK;
    else
        return ACT_VM_IDLE;
}

//-----------------------------------------------------------------------------
// Purpose: The gun is being reloaded 
//-----------------------------------------------------------------------------
bool CWeaponAK47::Reload() {
    bool fRet = DefaultReload(GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD);
    if (fRet) {
        WeaponSound(RELOAD);
        ToHL2MPPlayer(GetOwner())->SetAnimation(PLAYER_RELOAD);

        // Reset the burst counter to the default
        m_iBurst = BURST;
    }
    return fRet;
}

//-----------------------------------------------------------------------------
// Purpose: Put away the gun and disable zoom if needed
//-----------------------------------------------------------------------------
bool CWeaponAK47::Holster(CBaseCombatWeapon *pSwitchingTo /*= NULL*/ ) {
    if (m_bInZoom)
        ToggleZoom();

    return BaseClass::Holster(pSwitchingTo);
}

//-----------------------------------------------------------------------------
// Purpose: Calculate the view kick
//-----------------------------------------------------------------------------
void CWeaponAK47::AddViewKick() {
    CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
    if (pPlayer == NULL)
        return;

    int iSeed = CBaseEntity::GetPredictionRandomSeed() & 255;
    RandomSeed(iSeed);

    QAngle viewPunch;

    viewPunch.x = random->RandomFloat(0.25f, 0.5f);
    viewPunch.y = random->RandomFloat(-.6f, .6f);
    viewPunch.z = 0.0f;

    // Add it to the view punch
    pPlayer->ViewPunch(viewPunch);
}

//-----------------------------------------------------------------------------
// Purpose: Toggle the zoom by changing the client's FOV
//-----------------------------------------------------------------------------
void CWeaponAK47::ToggleZoom() {
    CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
    if (pPlayer == NULL)
        return;

#ifndef CLIENT_DLL
    if (m_bInZoom) {
        // Narrowing the field of view here is what gives us the zoomed effect
        if (pPlayer->SetFOV(this, 0, 0.2f))
            m_bInZoom = false;
    } else {
        if (pPlayer->SetFOV(this, 45, 0.1f))
            m_bInZoom = true;
    }
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Toggle the zoom if the Sec attack button was pressed
//-----------------------------------------------------------------------------
void CWeaponAK47::CheckZoomToggle() {
    CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
    if (pPlayer && (pPlayer->m_afButtonPressed & IN_ATTACK2))
        ToggleZoom();
}

//-----------------------------------------------------------------------------
// Purpose: Get the current stance/status of the player
//----------------------------------------------------------------------------- 
void CWeaponAK47::GetStance() {
    CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
    if (pPlayer == NULL)
        return;

    m_iStance = E_STAND;

    // Movement based stance
    if (pPlayer->m_nButtons & IN_DUCK)
        m_iStance = E_DUCK;
    if (pPlayer->m_nButtons & IN_FORWARD)
        m_iStance = E_MOVE;
    if (pPlayer->m_nButtons & IN_BACK)
        m_iStance = E_MOVE;
    if (pPlayer->m_nButtons & IN_MOVERIGHT)
        m_iStance = E_MOVE;
    if (pPlayer->m_nButtons & IN_MOVELEFT)
        m_iStance = E_MOVE;
    if (pPlayer->m_nButtons & IN_RUN)
        m_iStance = E_RUN;
    if (pPlayer->m_nButtons & IN_SPEED)
        m_iStance = E_RUN;
    if (pPlayer->m_nButtons & IN_JUMP)
        m_iStance = E_JUMP;

    // Health based status
    if (pPlayer->GetHealth() < 25)
        m_iStance = E_INJURED;
    if (pPlayer->GetHealth() < 10)
        m_iStance = E_DYING;
}