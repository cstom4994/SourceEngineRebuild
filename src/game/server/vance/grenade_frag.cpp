﻿//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "basegrenade_shared.h"
#include "grenade_frag.h"
#include "Sprite.h"
#include "SpriteTrail.h"
#include "soundent.h"
#include "projectile_bullet.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define FRAG_GRENADE_BLIP_FREQUENCY			1.0f
#define FRAG_GRENADE_BLIP_FAST_FREQUENCY	0.3f

#define FRAG_GRENADE_GRACE_TIME_AFTER_PICKUP 1.5f
#define FRAG_GRENADE_WARN_TIME 1.5f

const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.2f;

ConVar sk_plr_dmg_fraggrenade	( "sk_plr_dmg_fraggrenade","0");
ConVar sk_npc_dmg_fraggrenade	( "sk_npc_dmg_fraggrenade","0");
ConVar sk_fraggrenade_radius	( "sk_fraggrenade_radius", "0");

#define GRENADE_MODEL "models/Weapons/w_grenade.mdl"

class CGrenadeFrag : public CBaseGrenade
{
	DECLARE_CLASS( CGrenadeFrag, CBaseGrenade );

#if !defined( CLIENT_DLL )
	DECLARE_DATADESC();
#endif
					
	~CGrenadeFrag( void );

public:
	void	Spawn( void );
	void	OnRestore( void );
	void Explode(trace_t* pTrace, int bitsDamageType);
	void	Precache( void );
	bool	CreateVPhysics( void );
	void	CreateEffects( void );
	void	SetTimer( float detonateDelay, float warnDelay );
	void	SetVelocity( const Vector &velocity, const AngularImpulse &angVelocity );
	int		OnTakeDamage( const CTakeDamageInfo &inputInfo );
	void	BlipSound() { EmitSound( "Grenade.Blip" ); }
	void	DelayThink();
	void	VPhysicsUpdate( IPhysicsObject *pPhysics );
	void	OnPhysGunPickup( CBasePlayer *pPhysGunUser, PhysGunPickup_t reason );
	void	SetCombineSpawned( bool combineSpawned ) { m_combineSpawned = combineSpawned; }
	bool	IsCombineSpawned( void ) const { return m_combineSpawned; }
	void	SetPunted( bool punt ) { m_punted = punt; }
	bool	WasPunted( void ) const { return m_punted; }

	// this function only used in episodic.
#if defined(HL2_EPISODIC) && 0 // FIXME: HandleInteraction() is no longer called now that base grenade derives from CBaseAnimating
	bool	HandleInteraction(int interactionType, void *data, CBaseCombatCharacter* sourceEnt);
#endif 

	void	InputSetTimer( inputdata_t &inputdata );

protected:
	CHandle<CSprite>		m_pMainGlow;
	CHandle<CSpriteTrail>	m_pGlowTrail;

	float	m_flNextBlipTime;
	bool	m_inSolid;
	bool	m_combineSpawned;
	bool	m_punted;
};

LINK_ENTITY_TO_CLASS( npc_grenade_frag, CGrenadeFrag );

BEGIN_DATADESC( CGrenadeFrag )

	// Fields
	DEFINE_FIELD( m_pMainGlow, FIELD_EHANDLE ),
	DEFINE_FIELD( m_pGlowTrail, FIELD_EHANDLE ),
	DEFINE_FIELD( m_flNextBlipTime, FIELD_TIME ),
	DEFINE_FIELD( m_inSolid, FIELD_BOOLEAN ),
	DEFINE_FIELD( m_combineSpawned, FIELD_BOOLEAN ),
	DEFINE_FIELD( m_punted, FIELD_BOOLEAN ),
	
	// Function Pointers
	DEFINE_THINKFUNC( DelayThink ),

	// Inputs
	DEFINE_INPUTFUNC( FIELD_FLOAT, "SetTimer", InputSetTimer ),

END_DATADESC()


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CGrenadeFrag::~CGrenadeFrag( void )
{
}

void CGrenadeFrag::Spawn( void )
{
	Precache( );

	SetModel( GRENADE_MODEL );

	if( GetOwnerEntity() && GetOwnerEntity()->IsPlayer() )
	{
		m_flDamage		= sk_plr_dmg_fraggrenade.GetFloat();
		m_DmgRadius		= sk_fraggrenade_radius.GetFloat();
	}
	else
	{
		m_flDamage		= sk_npc_dmg_fraggrenade.GetFloat();
		m_DmgRadius		= sk_fraggrenade_radius.GetFloat();
	}

	m_takedamage	= DAMAGE_YES;
	m_iHealth		= 1;

	SetSize( -Vector(4,4,4), Vector(4,4,4) );
	SetCollisionGroup( COLLISION_GROUP_WEAPON );
	CreateVPhysics();

	BlipSound();
	m_flNextBlipTime = gpGlobals->curtime + FRAG_GRENADE_BLIP_FREQUENCY;

	AddSolidFlags( FSOLID_NOT_STANDABLE );

	m_combineSpawned	= false;
	m_punted			= false;

	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CGrenadeFrag::OnRestore( void )
{
	// If we were primed and ready to detonate, put FX on us.
	if (m_flDetonateTime > 0)
		CreateEffects();

	BaseClass::OnRestore();
}

ConVar vance_grenade_shrapnel_velocity("vance_grenade_shrapnel_velocity", "6000", FCVAR_CHEAT);
ConVar sk_grenade_shrapnel_dmg("sk_grenade_shrapnel_dmg", "5", FCVAR_CHEAT);

#if 0
// Generated by the calculate_shrapnel_directions program...
static const Vector s_ShrapnelDirections[150] =
{
	{ -1.000000, -1.000000, -1.000000 },
	{ -0.986049, -0.986049, -0.986049 },
	{ -0.973633, -0.973633, -0.973633 },
	{ -0.959507, -0.959507, -0.959507 },
	{ -0.946246, -0.946246, -0.946246 },
	{ -0.934303, -0.934303, -0.934303 },
	{ -0.920705, -0.920705, -0.920705 },
	{ -0.906775, -0.906775, -0.906775 },
	{ -0.894315, -0.894315, -0.894315 },
	{ -0.879858, -0.879858, -0.879858 },
	{ -0.867334, -0.867334, -0.867334 },
	{ -0.853629, -0.853629, -0.853629 },
	{ -0.839433, -0.839433, -0.839433 },
	{ -0.827063, -0.827063, -0.827063 },
	{ -0.812422, -0.812422, -0.812422 },
	{ -0.800715, -0.800715, -0.800715 },
	{ -0.785942, -0.785942, -0.785942 },
	{ -0.772646, -0.772646, -0.772646 },
	{ -0.759777, -0.759777, -0.759777 },
	{ -0.747072, -0.747072, -0.747072 },
	{ -0.733582, -0.733582, -0.733582 },
	{ -0.720888, -0.720888, -0.720888 },
	{ -0.707115, -0.707115, -0.707115 },
	{ -0.692951, -0.692951, -0.692951 },
	{ -0.680030, -0.680030, -0.680030 },
	{ -0.666730, -0.666730, -0.666730 },
	{ -0.652844, -0.652844, -0.652844 },
	{ -0.640230, -0.640230, -0.640230 },
	{ -0.626522, -0.626522, -0.626522 },
	{ -0.613883, -0.613883, -0.613883 },
	{ -0.599966, -0.599966, -0.599966 },
	{ -0.586976, -0.586976, -0.586976 },
	{ -0.573350, -0.573350, -0.573350 },
	{ -0.559990, -0.559990, -0.559990 },
	{ -0.547384, -0.547384, -0.547384 },
	{ -0.533727, -0.533727, -0.533727 },
	{ -0.519067, -0.519067, -0.519067 },
	{ -0.505912, -0.505912, -0.505912 },
	{ -0.493951, -0.493951, -0.493951 },
	{ -0.480049, -0.480049, -0.480049 },
	{ -0.466203, -0.466203, -0.466203 },
	{ -0.453196, -0.453196, -0.453196 },
	{ -0.439556, -0.439556, -0.439556 },
	{ -0.426931, -0.426931, -0.426931 },
	{ -0.413299, -0.413299, -0.413299 },
	{ -0.400791, -0.400791, -0.400791 },
	{ -0.386568, -0.386568, -0.386568 },
	{ -0.373583, -0.373583, -0.373583 },
	{ -0.360088, -0.360088, -0.360088 },
	{ -0.347071, -0.347071, -0.347071 },
	{ -0.333941, -0.333941, -0.333941 },
	{ -0.320205, -0.320205, -0.320205 },
	{ -0.307612, -0.307612, -0.307612 },
	{ -0.294232, -0.294232, -0.294232 },
	{ -0.279314, -0.279314, -0.279314 },
	{ -0.267271, -0.267271, -0.267271 },
	{ -0.254113, -0.254113, -0.254113 },
	{ -0.239118, -0.239118, -0.239118 },
	{ -0.227386, -0.227386, -0.227386 },
	{ -0.212917, -0.212917, -0.212917 },
	{ -0.200495, -0.200495, -0.200495 },
	{ -0.187545, -0.187545, -0.187545 },
	{ -0.173912, -0.173912, -0.173912 },
	{ -0.160971, -0.160971, -0.160971 },
	{ -0.146162, -0.146162, -0.146162 },
	{ -0.134186, -0.134186, -0.134186 },
	{ -0.119608, -0.119608, -0.119608 },
	{ -0.107202, -0.107202, -0.107202 },
	{ -0.093076, -0.093076, -0.093076 },
	{ -0.079074, -0.079074, -0.079074 },
	{ -0.067287, -0.067287, -0.067287 },
	{ -0.052343, -0.052343, -0.052343 },
	{ -0.040805, -0.040805, -0.040805 },
	{ -0.026791, -0.026791, -0.026791 },
	{ -0.012544, -0.012544, -0.012544 },
	{ 0.000538, 0.000538, 0.000538 },
	{ 0.013589, 0.013589, 0.013589 },
	{ 0.026599, 0.026599, 0.026599 },
	{ 0.040710, 0.040710, 0.040710 },
	{ 0.053775, 0.053775, 0.053775 },
	{ 0.066035, 0.066035, 0.066035 },
	{ 0.080810, 0.080810, 0.080810 },
	{ 0.093543, 0.093543, 0.093543 },
	{ 0.106369, 0.106369, 0.106369 },
	{ 0.120481, 0.120481, 0.120481 },
	{ 0.133716, 0.133716, 0.133716 },
	{ 0.146819, 0.146819, 0.146819 },
	{ 0.160229, 0.160229, 0.160229 },
	{ 0.173669, 0.173669, 0.173669 },
	{ 0.186805, 0.186805, 0.186805 },
	{ 0.199217, 0.199217, 0.199217 },
	{ 0.213822, 0.213822, 0.213822 },
	{ 0.225825, 0.225825, 0.225825 },
	{ 0.240640, 0.240640, 0.240640 },
	{ 0.253151, 0.253151, 0.253151 },
	{ 0.266669, 0.266669, 0.266669 },
	{ 0.280476, 0.280476, 0.280476 },
	{ 0.294251, 0.294251, 0.294251 },
	{ 0.306267, 0.306267, 0.306267 },
	{ 0.319131, 0.319131, 0.319131 },
	{ 0.333553, 0.333553, 0.333553 },
	{ 0.347418, 0.347418, 0.347418 },
	{ 0.359210, 0.359210, 0.359210 },
	{ 0.372914, 0.372914, 0.372914 },
	{ 0.386992, 0.386992, 0.386992 },
	{ 0.399758, 0.399758, 0.399758 },
	{ 0.413352, 0.413352, 0.413352 },
	{ 0.426731, 0.426731, 0.426731 },
	{ 0.439012, 0.439012, 0.439012 },
	{ 0.453579, 0.453579, 0.453579 },
	{ 0.467161, 0.467161, 0.467161 },
	{ 0.480571, 0.480571, 0.480571 },
	{ 0.494245, 0.494245, 0.494245 },
	{ 0.506415, 0.506415, 0.506415 },
	{ 0.520903, 0.520903, 0.520903 },
	{ 0.532993, 0.532993, 0.532993 },
	{ 0.545930, 0.545930, 0.545930 },
	{ 0.560194, 0.560194, 0.560194 },
	{ 0.572363, 0.572363, 0.572363 },
	{ 0.586901, 0.586901, 0.586901 },
	{ 0.599338, 0.599338, 0.599338 },
	{ 0.612972, 0.612972, 0.612972 },
	{ 0.627271, 0.627271, 0.627271 },
	{ 0.640222, 0.640222, 0.640222 },
	{ 0.652623, 0.652623, 0.652623 },
	{ 0.666174, 0.666174, 0.666174 },
	{ 0.679132, 0.679132, 0.679132 },
	{ 0.692938, 0.692938, 0.692938 },
	{ 0.706289, 0.706289, 0.706289 },
	{ 0.719269, 0.719269, 0.719269 },
	{ 0.734124, 0.734124, 0.734124 },
	{ 0.746897, 0.746897, 0.746897 },
	{ 0.759457, 0.759457, 0.759457 },
	{ 0.772832, 0.772832, 0.772832 },
	{ 0.785774, 0.785774, 0.785774 },
	{ 0.799854, 0.799854, 0.799854 },
	{ 0.814116, 0.814116, 0.814116 },
	{ 0.825917, 0.825917, 0.825917 },
	{ 0.839094, 0.839094, 0.839094 },
	{ 0.854163, 0.854163, 0.854163 },
	{ 0.867559, 0.867559, 0.867559 },
	{ 0.880684, 0.880684, 0.880684 },
	{ 0.892852, 0.892852, 0.892852 },
	{ 0.907576, 0.907576, 0.907576 },
	{ 0.920171, 0.920171, 0.920171 },
	{ 0.934224, 0.934224, 0.934224 },
	{ 0.945681, 0.945681, 0.945681 },
	{ 0.960572, 0.960572, 0.960572 },
	{ 0.972778, 0.972778, 0.972778 },
	{ 0.986503, 0.986503, 0.986503 },
};

static void Cmd_VisualiseGrenadeFragmentations()
{
	static const Vector x(1, 0, 0);
	static const Vector z(0, 0, 1);

	VMatrix rotation;
	MatrixRotate(rotation, x, RandomFloat(0, 360));
	MatrixRotate(rotation, z, RandomFloat(0, 360));

	CBasePlayer* pPlayer = UTIL_GetCommandClient();
	Vector vecDir;
	AngleVectors(pPlayer->EyeAngles(), &vecDir);

	Vector vecAbsStart = pPlayer->EyePosition();
	trace_t tr;
	UTIL_TraceLine(vecAbsStart, vecAbsStart + (vecDir * MAX_TRACE_LENGTH), MASK_SOLID, pPlayer, COLLISION_GROUP_NONE, &tr);
	vecAbsStart = tr.endpos;

	for (int i = 0; i < ARRAYSIZE(s_ShrapnelDirections); i++)
	{
		VectorRotate(s_ShrapnelDirections[i], rotation.As3x4(), vecDir);

		Vector vecAbsEnd = vecAbsStart + (vecDir * MAX_TRACE_LENGTH);

		UTIL_TraceLine(vecAbsStart, vecAbsEnd, MASK_BULLETSCANTOUCH, NULL, COLLISION_GROUP_PROJECTILE, &tr);
		DebugDrawLine(vecAbsStart, tr.endpos, 0, 0, 255, false, 10.0f);
	}
}
ConCommand visualise_grenade_fragmentations("visualise_grenade_fragmentations", Cmd_VisualiseGrenadeFragmentations);
// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CGrenadeFrag::Explode(trace_t* pTrace, int bitsDamageType)
{
	BaseClass::Explode(pTrace, bitsDamageType);

	static const Vector x(1, 0, 0);
//	static const Vector y(0, 1, 0);
	static const Vector z(0, 0, 1);

	VMatrix rotation;
	MatrixRotate(rotation, x, RandomFloat(0, 360));
	MatrixRotate(rotation, z, RandomFloat(0, 360));

	for (int i = 0; i < ARRAYSIZE(s_ShrapnelDirections); i++)
	{
		Vector direction = s_ShrapnelDirections[i];
		VectorRotate(s_ShrapnelDirections[i], rotation.As3x4(), direction);

		ProjBulletInfo_t info(1, GetAbsOrigin(), direction, VECTOR_CONE_PRECALCULATED,
			DMG_BULLET, false, vance_grenade_shrapnel_velocity.GetFloat());
		CProjectileBullet::Create(info);
	}
}
#else
ConVar vance_grenade_fragmentations("vance_grenade_fragmentations", "150", FCVAR_CHEAT);

// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CGrenadeFrag::Explode(trace_t* pTrace, int bitsDamageType)
{
	BaseClass::Explode(pTrace, bitsDamageType);

	for (int i = 0; i < vance_grenade_fragmentations.GetInt(); i++)
	{
		Vector direction(
			RandomFloat(-1, 1),
			RandomFloat(-1, 1),
			RandomFloat(-1, 1)
		);

		ProjBulletInfo_t info(1, GetAbsOrigin(), direction, VECTOR_CONE_PRECALCULATED,
			DMG_BULLET, false, vance_grenade_shrapnel_velocity.GetFloat());
		CProjectileBullet::Create(info);
	}
}
#endif

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CGrenadeFrag::CreateEffects( void )
{
	// Start up the eye glow
	m_pMainGlow = CSprite::SpriteCreate( "sprites/redglow1.vmt", GetLocalOrigin(), false );

	int	nAttachment = LookupAttachment( "fuse" );

	if ( m_pMainGlow != NULL )
	{
		m_pMainGlow->FollowEntity( this );
		m_pMainGlow->SetAttachment( this, nAttachment );
		m_pMainGlow->SetTransparency( kRenderGlow, 255, 255, 255, 200, kRenderFxNoDissipation );
		m_pMainGlow->SetScale( 0.2f );
		m_pMainGlow->SetGlowProxySize( 4.0f );
	}

	// Start up the eye trail
	m_pGlowTrail	= CSpriteTrail::SpriteTrailCreate( "sprites/bluelaser1.vmt", GetLocalOrigin(), false );

	if ( m_pGlowTrail != NULL )
	{
		m_pGlowTrail->FollowEntity( this );
		m_pGlowTrail->SetAttachment( this, nAttachment );
		m_pGlowTrail->SetTransparency( kRenderTransAdd, 255, 0, 0, 255, kRenderFxNone );
		m_pGlowTrail->SetStartWidth( 8.0f );
		m_pGlowTrail->SetEndWidth( 1.0f );
		m_pGlowTrail->SetLifeTime( 0.5f );
	}
}

bool CGrenadeFrag::CreateVPhysics()
{
	// Create the object in the physics system
	VPhysicsInitNormal( SOLID_BBOX, 0, false );
	return true;
}

// this will hit only things that are in newCollisionGroup, but NOT in collisionGroupAlreadyChecked
class CTraceFilterCollisionGroupDelta : public CTraceFilterEntitiesOnly
{
public:
	// It does have a base, but we'll never network anything below here..
	DECLARE_CLASS_NOBASE( CTraceFilterCollisionGroupDelta );
	
	CTraceFilterCollisionGroupDelta( const IHandleEntity *passentity, int collisionGroupAlreadyChecked, int newCollisionGroup )
		: m_pPassEnt(passentity), m_collisionGroupAlreadyChecked( collisionGroupAlreadyChecked ), m_newCollisionGroup( newCollisionGroup )
	{
	}
	
	virtual bool ShouldHitEntity( IHandleEntity *pHandleEntity, int contentsMask )
	{
		if ( !PassServerEntityFilter( pHandleEntity, m_pPassEnt ) )
			return false;
		CBaseEntity *pEntity = EntityFromEntityHandle( pHandleEntity );

		if ( pEntity )
		{
			if ( g_pGameRules->ShouldCollide( m_collisionGroupAlreadyChecked, pEntity->GetCollisionGroup() ) )
				return false;
			if ( g_pGameRules->ShouldCollide( m_newCollisionGroup, pEntity->GetCollisionGroup() ) )
				return true;
		}

		return false;
	}

protected:
	const IHandleEntity *m_pPassEnt;
	int		m_collisionGroupAlreadyChecked;
	int		m_newCollisionGroup;
};

void CGrenadeFrag::VPhysicsUpdate( IPhysicsObject *pPhysics )
{
	BaseClass::VPhysicsUpdate( pPhysics );
	Vector vel;
	AngularImpulse angVel;
	pPhysics->GetVelocity( &vel, &angVel );
	
	Vector start = GetAbsOrigin();
	// find all entities that my collision group wouldn't hit, but COLLISION_GROUP_NONE would and bounce off of them as a ray cast
	CTraceFilterCollisionGroupDelta filter( this, GetCollisionGroup(), COLLISION_GROUP_NONE );
	trace_t tr;

	// UNDONE: Hull won't work with hitboxes - hits outer hull.  But the whole point of this test is to hit hitboxes.
#if 0
	UTIL_TraceHull( start, start + vel * gpGlobals->frametime, CollisionProp()->OBBMins(), CollisionProp()->OBBMaxs(), CONTENTS_HITBOX|CONTENTS_MONSTER|CONTENTS_SOLID, &filter, &tr );
#else
	UTIL_TraceLine( start, start + vel * gpGlobals->frametime, CONTENTS_HITBOX|CONTENTS_MONSTER|CONTENTS_SOLID, &filter, &tr );
#endif
	if ( tr.startsolid )
	{
		if ( !m_inSolid )
		{
			// UNDONE: Do a better contact solution that uses relative velocity?
			vel *= -GRENADE_COEFFICIENT_OF_RESTITUTION; // bounce backwards
			pPhysics->SetVelocity( &vel, NULL );
		}
		m_inSolid = true;
		return;
	}
	m_inSolid = false;
	if ( tr.DidHit() )
	{
		Vector dir = vel;
		VectorNormalize(dir);
		// send a tiny amount of damage so the character will react to getting bonked
		CTakeDamageInfo info( this, GetThrower(), pPhysics->GetMass() * vel, GetAbsOrigin(), 0.1f, DMG_CRUSH );
		tr.m_pEnt->TakeDamage( info );

		// reflect velocity around normal
		vel = -2.0f * tr.plane.normal * DotProduct(vel,tr.plane.normal) + vel;
		
		// absorb 80% in impact
		vel *= GRENADE_COEFFICIENT_OF_RESTITUTION;
		angVel *= -0.5f;
		pPhysics->SetVelocity( &vel, &angVel );
	}
}


void CGrenadeFrag::Precache( void )
{
	PrecacheModel( GRENADE_MODEL );

	PrecacheScriptSound( "Grenade.Blip" );

	PrecacheModel( "sprites/redglow1.vmt" );
	PrecacheModel( "sprites/bluelaser1.vmt" );

	BaseClass::Precache();
}

void CGrenadeFrag::SetTimer( float detonateDelay, float warnDelay )
{
	m_flDetonateTime = gpGlobals->curtime + detonateDelay;
	m_flWarnAITime = gpGlobals->curtime + warnDelay;
	SetThink( &CGrenadeFrag::DelayThink );
	SetNextThink( gpGlobals->curtime );

	CreateEffects();
}

void CGrenadeFrag::OnPhysGunPickup( CBasePlayer *pPhysGunUser, PhysGunPickup_t reason )
{
	SetThrower( pPhysGunUser );

#ifdef HL2MP
	SetTimer( FRAG_GRENADE_GRACE_TIME_AFTER_PICKUP, FRAG_GRENADE_GRACE_TIME_AFTER_PICKUP / 2);

	BlipSound();
	m_flNextBlipTime = gpGlobals->curtime + FRAG_GRENADE_BLIP_FAST_FREQUENCY;
	m_bHasWarnedAI = true;
#else
	if( IsX360() )
	{
		// Give 'em a couple of seconds to aim and throw. 
		SetTimer( 2.0f, 1.0f);
		BlipSound();
		m_flNextBlipTime = gpGlobals->curtime + FRAG_GRENADE_BLIP_FAST_FREQUENCY;
	}
#endif

#ifdef HL2_EPISODIC
	SetPunted( true );
#endif

	BaseClass::OnPhysGunPickup( pPhysGunUser, reason );
}

void CGrenadeFrag::DelayThink() 
{
	if( gpGlobals->curtime > m_flDetonateTime )
	{
		Detonate();
		return;
	}

	if( !m_bHasWarnedAI && gpGlobals->curtime >= m_flWarnAITime )
	{
#if !defined( CLIENT_DLL )
		CSoundEnt::InsertSound ( SOUND_DANGER, GetAbsOrigin(), 400, 1.5, this );
#endif
		m_bHasWarnedAI = true;
	}
	
	if( gpGlobals->curtime > m_flNextBlipTime )
	{
		BlipSound();
		
		if( m_bHasWarnedAI )
		{
			m_flNextBlipTime = gpGlobals->curtime + FRAG_GRENADE_BLIP_FAST_FREQUENCY;
		}
		else
		{
			m_flNextBlipTime = gpGlobals->curtime + FRAG_GRENADE_BLIP_FREQUENCY;
		}
	}

	SetNextThink( gpGlobals->curtime + 0.1 );
}

void CGrenadeFrag::SetVelocity( const Vector &velocity, const AngularImpulse &angVelocity )
{
	IPhysicsObject *pPhysicsObject = VPhysicsGetObject();
	if ( pPhysicsObject )
	{
		pPhysicsObject->AddVelocity( &velocity, &angVelocity );
	}
}

int CGrenadeFrag::OnTakeDamage( const CTakeDamageInfo &inputInfo )
{
	// Manually apply vphysics because BaseCombatCharacter takedamage doesn't call back to CBaseEntity OnTakeDamage
	VPhysicsTakeDamage( inputInfo );

	// Grenades only suffer blast damage and burn damage.
	if( !(inputInfo.GetDamageType() & (DMG_BLAST|DMG_BURN) ) )
		return 0;

	return BaseClass::OnTakeDamage( inputInfo );
}

#if defined(HL2_EPISODIC) && 0 // FIXME: HandleInteraction() is no longer called now that base grenade derives from CBaseAnimating
extern int	g_interactionBarnacleVictimGrab; ///< usually declared in ai_interactions.h but no reason to haul all of that in here.
extern int g_interactionBarnacleVictimBite;
extern int g_interactionBarnacleVictimReleased;
bool CGrenadeFrag::HandleInteraction(int interactionType, void *data, CBaseCombatCharacter* sourceEnt)
{
	// allow fragnades to be grabbed by barnacles. 
	if ( interactionType == g_interactionBarnacleVictimGrab )
	{
		// give the grenade another five seconds seconds so the player can have the satisfaction of blowing up the barnacle with it
		float timer = m_flDetonateTime - gpGlobals->curtime + 5.0f;
		SetTimer( timer, timer - FRAG_GRENADE_WARN_TIME );

		return true;
	}
	else if ( interactionType == g_interactionBarnacleVictimBite )
	{
		// detonate the grenade immediately 
		SetTimer( 0, 0 );
		return true;
	}
	else if ( interactionType == g_interactionBarnacleVictimReleased )
	{
		// take the five seconds back off the timer.
		float timer = MAX(m_flDetonateTime - gpGlobals->curtime - 5.0f,0.0f);
		SetTimer( timer, timer - FRAG_GRENADE_WARN_TIME );
		return true;
	}
	else
	{
		return BaseClass::HandleInteraction( interactionType, data, sourceEnt );
	}
}
#endif

void CGrenadeFrag::InputSetTimer( inputdata_t &inputdata )
{
	SetTimer( inputdata.value.Float(), inputdata.value.Float() - FRAG_GRENADE_WARN_TIME );
}

CBaseGrenade *Fraggrenade_Create( const Vector &position, const QAngle &angles, const Vector &velocity, const AngularImpulse &angVelocity, CBaseEntity *pOwner, float timer, bool combineSpawned )
{
	// Don't set the owner here, or the player can't interact with grenades he's thrown
	CGrenadeFrag *pGrenade = (CGrenadeFrag *)CBaseEntity::Create( "npc_grenade_frag", position, angles, pOwner );
	
	pGrenade->SetTimer( timer, timer - FRAG_GRENADE_WARN_TIME );
	pGrenade->SetVelocity( velocity, angVelocity );
	pGrenade->SetThrower( ToBaseCombatCharacter( pOwner ) );
	pGrenade->m_takedamage = DAMAGE_EVENTS_ONLY;
	pGrenade->SetCombineSpawned( combineSpawned );

	return pGrenade;
}

bool Fraggrenade_WasPunted( const CBaseEntity *pEntity )
{
	const CGrenadeFrag *pFrag = dynamic_cast<const CGrenadeFrag *>( pEntity );
	if ( pFrag )
	{
		return pFrag->WasPunted();
	}

	return false;
}

bool Fraggrenade_WasCreatedByCombine( const CBaseEntity *pEntity )
{
	const CGrenadeFrag *pFrag = dynamic_cast<const CGrenadeFrag *>( pEntity );
	if ( pFrag )
	{
		return pFrag->IsCombineSpawned();
	}

	return false;
}