#ifndef PROJECTILE_BULLET_H
#define PROJECTILE_BULLET_H

#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"

class CProjectileBulletTrace : public CBaseEntity
{
	DECLARE_CLASS(CProjectileBulletTrace, CBaseEntity);
	DECLARE_DATADESC();
public:

	void	Spawn(void);

	static CProjectileBulletTrace* Create(const ProjectileBulletsInfo_t& info, Vector vecDir);

	unsigned int	PhysicsSolidMaskForEntity(void) const;

	void	BulletTouch(CBaseEntity *pOther);

	void	Hit(trace_t *pTrace, CBaseEntity *pOther);

protected:

	Vector m_vVelocity;
	Vector m_vDir;

	ProjectileBulletsInfo_t m_BulletsInfo;
};

#endif // PROJECTILE_BULLET_H