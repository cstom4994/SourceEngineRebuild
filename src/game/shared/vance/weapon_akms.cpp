//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		AKMS with overheating
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "npcevent.h"
#include "vance_baseweapon_shared.h"

#ifdef GAME_DLL

#include "basecombatweapon.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "soundent.h"
#include "game.h"

#endif
#ifdef CLIENT_DLL
#include "c_weapon__stubs.h"
#endif

#include "gamerules.h"
#include "in_buttons.h"
#include "vstdlib/random.h"
#include "gamestats.h"
#include "saverestore.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar sk_akms_damage("sk_akms_damage", "15", FCVAR_REPLICATED);

extern short g_sModelIndexSmoke;


// SERVER
#ifdef GAME_DLL

class CWeaponAKMS : public CVanceMachineGun {
    DECLARE_CLASS(CWeaponAKMS, CVanceMachineGun);
DECLARE_SERVERCLASS();
public:
    CWeaponAKMS();

    virtual void PrimaryAttack();

    virtual void ItemPostFrame();

    virtual void ItemBusyFrame();

    virtual void ItemHolsterFrame();

    virtual Activity GetPrimaryAttackActivity();

    void ManageHeat();


protected:
    //bool m_bJammed;
    bool m_bCoolingDown;

    CNetworkVar(bool, m_bSmoking);
    int m_iHeat;
    float m_flCooldownTime;
    float m_flPerCooldownTime;
};

LINK_ENTITY_TO_CLASS(weapon_akms, CWeaponAKMS);
PRECACHE_WEAPON_REGISTER(weapon_akms);

IMPLEMENT_SERVERCLASS_ST(CWeaponAKMS, DT_WeaponAKMS)

                    SendPropBool(SENDINFO(m_bSmoking)),

END_SEND_TABLE()

CWeaponAKMS::CWeaponAKMS() {
    //m_bJammed = false;
    m_bCoolingDown = true;
    m_bSmoking = false;
    m_iHeat = 0;
    m_flCooldownTime = gpGlobals->curtime;
    m_flPerCooldownTime = gpGlobals->curtime;
}


void CWeaponAKMS::PrimaryAttack() {
    if (m_iClip1 <= 0) {
        WeaponSound(EMPTY);
        SendWeaponAnim(ACT_VM_DRYFIRE);
        return;
    }

    CBasePlayer *pOwner = ToBasePlayer(GetOwner());

    if (!pOwner) {
        return;
    }

    m_iHeat++;
    m_bCoolingDown = false;
    m_flCooldownTime = gpGlobals->curtime + 3.0f;


    pOwner->ViewPunchReset();

    CSoundEnt::InsertSound(SOUND_COMBAT | SOUND_CONTEXT_GUNFIRE, pOwner->GetAbsOrigin(), SOUNDENT_VOLUME_MACHINEGUN,
                           0.2, pOwner, SOUNDENT_CHANNEL_WEAPON, pOwner->GetEnemy());
    Vector vecShootOrigin = pOwner->Weapon_ShootPosition();
    QAngle angShootDir = pOwner->EyeAngles();
    Vector vecShootDir;
    AngleVectors(angShootDir, &vecShootDir);

    FireBulletProjectiles(1, vecShootOrigin, vecShootDir, VECTOR_CONE_2DEGREES, MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 1,
                          entindex(), -1, sk_akms_damage.GetInt());
    pOwner->DoMuzzleFlash();
    WeaponSound(SINGLE);
    SendWeaponAnim(GetPrimaryAttackActivity());
    //pOwner->ViewPunch(QAngle(-3, random->RandomFloat(-1, 1), 0));
    DoMachineGunKick(pOwner, 0.3f, 10.0f, std::max(1.0f, m_fFireDuration * 1.75f), 5.0f);
    m_iClip1 = m_iClip1 - 1;

    m_nShotsFired++;
    m_iPrimaryAttacks++;
    gamestats->Event_WeaponFired(pOwner, true, GetClassname());

    if (m_iHeat > 32) {
        int chance = random->RandomInt(1, 3);
        if (chance == 1) {
            SendWeaponAnim(ACT_VM_RETRACT);
            m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
            return;
        }
    }

    m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate();

}


Activity CWeaponAKMS::GetPrimaryAttackActivity(void) {

    if (m_nShotsFired < 3)
        return ACT_VM_PRIMARYATTACK;

    if (m_nShotsFired < 10)
        return ACT_VM_RECOIL1;

    if (m_nShotsFired < 20)
        return ACT_VM_RECOIL2;

    return ACT_VM_RECOIL3;
}


void CWeaponAKMS::ItemPostFrame() {
    BaseClass::ItemPostFrame();
    ManageHeat();
}

void CWeaponAKMS::ItemBusyFrame() {
    BaseClass::ItemBusyFrame();
    ManageHeat();
}

void CWeaponAKMS::ItemHolsterFrame() {
    BaseClass::ItemHolsterFrame();
    ManageHeat();
}


/*void CWeaponAKMS::StartSmoking()
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	CSingleUserRecipientFilter filter(pOwner);
	Vector pos;
	QAngle ang;
	CBaseViewModel* pVM = pOwner->GetViewModel();
	if (!pVM)
	{
		return;
	}
	pVM->GetAttachment("smoke", pos, ang);
	te->Smoke(filter, 0.0f, &pos, g_sModelIndexSmoke, 2.5f, 10);
}*/


void CWeaponAKMS::ManageHeat() {
    if (m_flCooldownTime < gpGlobals->curtime) {
        m_bCoolingDown = true;
    }
    if (m_bCoolingDown && m_flPerCooldownTime < gpGlobals->curtime && m_iHeat > 0) {
        m_flPerCooldownTime = gpGlobals->curtime + 0.1f;
        m_iHeat--;
    }
    if (m_iHeat > 25) {
        m_bSmoking = true;
    } else {
        m_bSmoking = false;
    }
}

#else
class C_WeaponAKMS : public C_BaseVanceWeapon
{
    DECLARE_CLASS(C_WeaponAKMS, C_BaseVanceWeapon);
public:
    DECLARE_CLIENTCLASS();
    DECLARE_PREDICTABLE();
    C_WeaponAKMS();
    virtual void Spawn();
    virtual void Precache();
    virtual void OnDataChanged(DataUpdateType_t update);
    virtual void UpdateOnRemove();
    void HandleSmoking();
protected:
    CNetworkVar(bool, m_bSmoking);
    HPARTICLEFFECT m_pSmoke;
};

STUB_WEAPON_CLASS_IMPLEMENT(weapon_akms, C_WeaponAKMS);

IMPLEMENT_CLIENTCLASS_DT(C_WeaponAKMS, DT_WeaponAKMS, CWeaponAKMS)
RecvPropBool(RECVINFO(m_bSmoking)),
END_RECV_TABLE()


C_WeaponAKMS::C_WeaponAKMS()
{
    m_pSmoke = NULL;
}

void C_WeaponAKMS::Spawn()
{
    BaseClass::Spawn();
}

void C_WeaponAKMS::Precache()
{
    PrecacheParticleSystem("muzzle_akms_smoke");
}

void C_WeaponAKMS::OnDataChanged(DataUpdateType_t update)
{
    if (update == DATA_UPDATE_DATATABLE_CHANGED)
    {
        HandleSmoking();
    }
}

void C_WeaponAKMS::UpdateOnRemove()
{
    if (!m_pSmoke)
    {
        return;
    }
    ParticleMgr()->RemoveEffect(m_pSmoke);
    m_pSmoke = NULL;
}

void C_WeaponAKMS::HandleSmoking()
{
    /*if (m_iHeat > 25)
    {
        CBasePlayer* pOwner = ToBasePlayer(GetOwner());
        if (!pOwner)
        {
            return;
        }
        CBaseAnimating* pVM = pOwner->GetViewModel();
        if (!pVM)
        {
            return;
        }
        if (!m_pSmoke)
        {
            m_pSmoke = pVM->ParticleProp()->Create("muzzle_akms_smoke", PATTACH_POINT_FOLLOW, "smoke");
        }
        m_pSmoke->StartEmission();
    }
    else if (m_pSmoke && m_iHeat < 25)
    {
        m_pSmoke->StopEmission();
    }*/
    CBasePlayer* pOwner = ToBasePlayer(GetOwner());
    if (!pOwner)
    {
        return;
    }
    CBaseAnimating* pVM = pOwner->GetViewModel();
    if (!pVM)
    {
        return;
    }
    if (!m_pSmoke && m_bSmoking)
    {
        m_pSmoke = pVM->ParticleProp()->Create("muzzle_akms_smoke", PATTACH_POINT_FOLLOW, "smoke");
    }
    else if (m_pSmoke && !m_bSmoking)
    {
        m_pSmoke->StopEmission();
    }
}
#endif