#include "cbase.h"
#include "basehlcombatweapon.h"
#include "beam_shared.h"
#include "in_buttons.h"
#include "ai_basenpc.h"
#include "ehandle.h"

class CWeaponHackTool : public CBaseHLCombatWeapon
{
	DECLARE_CLASS(CWeaponHackTool, CBaseHLCombatWeapon);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
public:

	void	Precache(void);
	void	PrimaryAttack(void);

	void	ItemPostFrame(void);

	bool	CanHolster(void);
	bool	IsAllowedToSwitch(void);

	void	HackThink(void);

private:

	float m_flNextPrimaryAttack;

	bool m_bShock;
	CNetworkVar(bool, m_bHacking);
	CNetworkHandle(CBaseAnimating, m_hTarget);
};

LINK_ENTITY_TO_CLASS(weapon_hacktool, CWeaponHackTool);

BEGIN_DATADESC(CWeaponHackTool)
DEFINE_THINKFUNC(HackThink),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CWeaponHackTool, DT_WeaponHackTool)
SendPropEHandle(SENDINFO(m_hTarget)),
SendPropBool(SENDINFO(m_bHacking)),
END_SEND_TABLE()

void CWeaponHackTool::Precache(void)
{
	BaseClass::Precache();

	PrecacheParticleSystem("Advisor_Psychic_Beam");
	PrecacheScriptSound("AlyxEMP.Charge");
	PrecacheScriptSound("AlyxEMP.Discharge");
}

void CWeaponHackTool::PrimaryAttack(void)
{
	bool bFail = true;

	if (!m_bHacking)
	{
		CBasePlayer *pPlayer = ToBasePlayer(GetOwner());

		Vector vStart = pPlayer->EyePosition();

		Vector vDir;
		AngleVectors(pPlayer->EyeAngles(), &vDir);

		Vector vEnd = vStart + (vDir * MAX_TRACE_LENGTH);

		trace_t tr;
		UTIL_TraceLine(vStart, vEnd, MASK_SOLID, GetOwner(), COLLISION_GROUP_NONE, &tr);

		CBaseAnimating *pEnt = tr.m_pEnt->GetBaseAnimating();
		if (!pEnt)
		{
			EmitSound("HL2Player.UseDeny");
			m_flNextPrimaryAttack = gpGlobals->curtime + 0.15f;
			return;
		}

		if (pEnt->IsHackable() && !pEnt->IsHacked())
		{
			m_hTarget = pEnt;
			m_bHacking = true;

			EmitSound("AlyxEMP.Charge");

			SendWeaponAnim(ACT_VM_SECONDARYATTACK);

			SetThink(&CWeaponHackTool::HackThink);
			SetNextThink(gpGlobals->curtime + 0.6f);

			bFail = false;
		}
		else if (pEnt->IsCombatCharacter())
		{
			CBaseCombatCharacter *pEnemy = pEnt->MyCombatCharacterPointer();
			if (pEnemy->GetDefaultRelationshipDisposition(CLASS_PLAYER) < D_LI)
			{
				m_hTarget = pEnt;

				m_bHacking = true;
				m_bShock = true;

				EmitSound("AlyxEMP.Charge");

				SendWeaponAnim(ACT_VM_PRIMARYATTACK);

				SetThink(&CWeaponHackTool::HackThink);
				SetNextThink(gpGlobals->curtime + 0.6f);

				CTakeDamageInfo info(this, GetOwner(), vec3_origin, tr.endpos, 10.0f, DMG_SHOCK);
				info.SetDamagePosition(tr.endpos);
				pEnemy->DispatchTraceAttack(info, vec3_origin, &tr);

				bFail = false;
			}
		}
	}

	if (bFail)
	{
		EmitSound("HL2Player.UseDeny");
	}

	m_flNextPrimaryAttack = gpGlobals->curtime + 0.15f;
}

void CWeaponHackTool::ItemPostFrame(void)
{
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());

	if ((pPlayer->m_afButtonPressed & IN_ATTACK) && m_flNextPrimaryAttack <= gpGlobals->curtime)
	{
		PrimaryAttack();
	}
}

bool CWeaponHackTool::CanHolster(void)
{
	return m_bHacking ? false : BaseClass::CanHolster();
}

bool CWeaponHackTool::IsAllowedToSwitch(void)
{
	return m_bHacking ? false : BaseClass::IsAllowedToSwitch();
}

void CWeaponHackTool::HackThink(void)
{
	if (V_strcmp(m_hTarget->GetClassname(), "npc_rollermine") == 0)
	{
		INPCInteractive *pInteractive = dynamic_cast<INPCInteractive *>(m_hTarget.Get());
		if (pInteractive)
		{
			pInteractive->NotifyInteraction(nullptr); // rollermines can already be hacked by doing this
		}
	}
	
	if (!m_bShock)
	{
		m_hTarget->Hack();
	}

	EmitSound("AlyxEMP.Discharge");
	m_bHacking = false;
	m_bShock = false;

	SetNextThink(TICK_NEVER_THINK);
}