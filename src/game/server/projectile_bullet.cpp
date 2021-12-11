#include "cbase.h"
#include "projectile_bullet.h"
#include "soundent.h"
#include "basehlcombatweapon.h"
#include "ammodef.h"
#include "vance_shareddefs.h"

LINK_ENTITY_TO_CLASS(projectile_bullet_trace, CProjectileBulletTrace);

BEGIN_DATADESC(CProjectileBulletTrace)
	DEFINE_FUNCTION(BulletTouch),
END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CProjectileBulletTrace::Spawn(void)
{
	SetSolid(SOLID_BBOX);
	SetSolidFlags(FSOLID_CUSTOMBOXTEST); // don't actually collide with anything, let BulletTouch handle 'collision'
	SetMoveType(MOVETYPE_FLY);
	AddEFlags(EFL_SERVER_ONLY); // no reason for this to exist on the client

	SetSize(-Vector(m_BulletsInfo.m_flBulletSize), Vector(m_BulletsInfo.m_flBulletSize));

	SetCollisionGroup(COLLISION_GROUP_PROJECTILE); // don't collide with other bullets

	// Setup attributes.
	m_takedamage = DAMAGE_NO;
	SetGravity(0.0f);

	SetTouch(&CProjectileBulletTrace::BulletTouch);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CProjectileBulletTrace* CProjectileBulletTrace::Create(const ProjectileBulletsInfo_t& info, Vector vecDir)
{
	QAngle angles;
	VectorAngles(vecDir, angles);

	Assert(info.m_pAttacker);

	CProjectileBulletTrace* pBullet = static_cast<CProjectileBulletTrace*>(
		CBaseEntity::CreateNoSpawn("projectile_bullet_trace", info.m_vecSrc, angles, info.m_pAttacker));

	if (!pBullet)
		return NULL;

	pBullet->m_BulletsInfo = info;

	Vector vecVelocity = vecDir * info.m_flBulletSpeed;
	pBullet->SetAbsVelocity(vecVelocity);
	pBullet->m_vVelocity = vecVelocity;
	pBullet->m_vDir = vecDir;

	pBullet->Spawn();

	return pBullet;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
unsigned int CProjectileBulletTrace::PhysicsSolidMaskForEntity(void) const
{ 
	return MASK_BULLETSCANTOUCH;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CProjectileBulletTrace::BulletTouch(CBaseEntity *pOther)
{
	// Verify a correct "other."
	Assert(pOther);
	if (pOther->IsSolidFlagSet(FSOLID_NOT_SOLID)) // If the brush isn't solid, don't touch it
		return;

	if (pOther == m_BulletsInfo.m_pAdditionalIgnoreEnt)
		return;

	// Handle hitting skybox (disappear).
	const trace_t *pTrace = &CBaseEntity::GetTouchTrace();
	if (pTrace->surface.flags & SURF_SKY) // Disappear when hitting the skybox
	{
		UTIL_Remove(this);
		return;
	}

	if (pTrace->contents & CONTENTS_WATER)
	{
		SetAbsVelocity(GetAbsVelocity() * 0.4f);
	}

	trace_t trace;
	memcpy(&trace, pTrace, sizeof(trace_t));
	Hit(&trace, pOther);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CProjectileBulletTrace::Hit(trace_t *pTrace, CBaseEntity *pOther)
{
	// Invisible.
	SetModelName(NULL_STRING);
	AddSolidFlags(FSOLID_NOT_SOLID);
	m_takedamage = DAMAGE_NO;

	// Pull out a bit.
	if (pTrace->fraction != 1.0)
	{
		SetAbsOrigin(pTrace->endpos + (pTrace->plane.normal * 1.0f));
	}

	Vector vecOrigin = GetAbsOrigin();

	int soundEntChannel = (m_BulletsInfo.m_nFlags & FIRE_BULLETS_TEMPORARY_DANGER_SOUND) ? SOUNDENT_CHANNEL_BULLET_IMPACT : SOUNDENT_CHANNEL_UNSPECIFIED;
	CSoundEnt::InsertSound(SOUND_BULLET_IMPACT, pTrace->endpos, 200, 0.5, this, soundEntChannel);

	if (!pOther->IsPlayer())
	{
		UTIL_ImpactTrace( pTrace, DMG_BULLET );
	}

	float damage = m_BulletsInfo.m_flDamage;
	if (m_BulletsInfo.m_pAttacker && damage == 0.0)
	{
		damage = g_pGameRules->GetAmmoDamage( m_BulletsInfo.m_pAttacker, pOther, m_BulletsInfo.m_iAmmoType );
	}

	CTakeDamageInfo info( this, m_BulletsInfo.m_pAttacker, vec3_origin, vecOrigin, 10.0f, DMG_BULLET );
	info.ScaleDamageForce(m_BulletsInfo.m_flDamageForceScale);

	// Calculate Bullet Force
	info.SetDamagePosition(pTrace->endpos);
	Vector vecForce = m_BulletsInfo.m_vecDirShooting;
	VectorNormalize(vecForce);
	vecForce *= GetAmmoDef()->DamageForce(m_BulletsInfo.m_iAmmoType);
	vecForce *= phys_pushscale.GetFloat();
	info.SetDamageForce(vecForce);

	pOther->DispatchTraceAttack(info, m_BulletsInfo.m_vecDirShooting, pTrace);

	UTIL_Remove(this);
}