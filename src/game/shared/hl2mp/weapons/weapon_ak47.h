//
// Created by KaoruXun
//

#ifndef WEAPON_AK47_H
#define WEAPON_AK47_H


#include "weapon_hl2mpbasehlmpcombatweapon.h"

// Modify this to alter the rate of fire
#define ROF 0.075f // RPS, 60sec/800 rounds = 0.075

// The gun will fire up to this number of bullets while you hold the fire button
// If you set it to 1 the gun will be semi-auto. If you set it to 3 the gun will fire three-round bursts
#define BURST 500

#ifdef CLIENT_DLL
#define CWeaponAK47 C_WeaponAK47
#endif

//-----------------------------------------------------------------------------
// CWeaponAK47
//-----------------------------------------------------------------------------
class CWeaponAK47 : public CBaseHL2MPCombatWeapon {
public:
    DECLARE_CLASS(CWeaponAK47, CBaseHL2MPCombatWeapon);

    CWeaponAK47();

    DECLARE_NETWORKCLASS();
    DECLARE_PREDICTABLE();

    void Precache();

    void ItemPostFrame();

    void ItemPreFrame();

    void ItemBusyFrame();

    void PrimaryAttack();

    void AddViewKick();

    void DryFire();

    void GetStance();

    bool Holster(CBaseCombatWeapon *pSwitchingTo = NULL); // Required so that you un-zoom when switching weapons
    Activity GetPrimaryAttackActivity();

    virtual bool Reload();

    int GetMinBurst() { return 2; }

    int GetMaxBurst() { return 5; }

    float GetFireRate() { return ROF; }

    // Modify this part to control the general accuracy of the gun
    virtual const Vector &GetBulletSpread() {
        Vector cone = VECTOR_CONE_1DEGREES;

        // If you don't need stance and health dependent accuracy, you can just remove this
        if (m_iStance == E_DUCK)
            cone = VECTOR_CONE_1DEGREES;
        if (m_iStance == E_STAND)
            cone = VECTOR_CONE_2DEGREES;
        if (m_iStance == E_MOVE)
            cone = VECTOR_CONE_3DEGREES;
        if (m_iStance == E_RUN)
            cone = VECTOR_CONE_4DEGREES;
        if (m_iStance == E_INJURED)
            cone = VECTOR_CONE_3DEGREES;
        if (m_iStance == E_JUMP)
            cone = VECTOR_CONE_4DEGREES;
        if (m_iStance == E_DYING)
            cone = VECTOR_CONE_10DEGREES;

        // This part simulates recoil. Each successive shot will have increased spread
        if (m_iBurst != BURST) {
            for (int i = m_iBurst; i < BURST; i++) {
                cone += VECTOR_CONE_1DEGREES;
            }
        }

        // This part is the zoom modifier. If zoomed in, lower the bullet spread
        if (m_bInZoom)
            cone -= VECTOR_CONE_1DEGREES;

        return cone;
    }

    void ToggleZoom();

    void CheckZoomToggle();

    DECLARE_ACTTABLE();

private:
    CNetworkVar(int, m_iBurst);

    CNetworkVar(bool, m_bInZoom);

    CNetworkVar(float, m_flAttackEnds);

    CNetworkVar(int, m_iStance);

private:
    CWeaponAK47(const CWeaponAK47 &);
};

#endif //INVADEENGINE_WEAPON_AK47_H
