//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef NPC_ASSASSIN_H
#define NPC_ASSASSIN_H
#ifdef _WIN32
#pragma once
#endif

#include "ai_basenpc.h"
#include "soundent.h"

ConVar sk_assassin_health("sk_assassin_health", "50");

//=========================================================
// monster-specific schedule types
//=========================================================
enum
{
	SCHED_ASSASSIN_EXPOSED = LAST_SHARED_SCHEDULE,// cover was blown.
	SCHED_ASSASSIN_JUMP,	// fly through the air
	SCHED_ASSASSIN_JUMP_ATTACK,	// fly through the air and shoot
	SCHED_ASSASSIN_JUMP_LAND, // hit and run away
	SCHED_ASSASSIN_FAIL,
	SCHED_ASSASSIN_TAKE_COVER_FROM_ENEMY1,
	SCHED_ASSASSIN_TAKE_COVER_FROM_ENEMY2,
	SCHED_ASSASSIN_TAKE_COVER_FROM_BEST_SOUND,
	SCHED_ASSASSIN_HIDE,
	SCHED_ASSASSIN_HUNT,
};


//=========================================================
// monster-specific tasks
//=========================================================

enum
{
	TASK_ASSASSIN_FALL_TO_GROUND = LAST_SHARED_TASK + 1, // falling and waiting to hit ground
};


//=========================================================
// Monster's Anim Events Go Here
//=========================================================
#define		ASSASSIN_AE_SHOOT1	1
#define		ASSASSIN_AE_SHOOT2	2
#define		ASSASSIN_AE_KICK	3
#define		ASSASSIN_AE_GRENADE	4
#define		ASSASSIN_AE_JUMP	5


#define MEMORY_BADJUMP	bits_MEMORY_CUSTOM1

class CNPC_HAssassin : public CAI_BaseNPC
{
	DECLARE_CLASS(CNPC_HAssassin, CAI_BaseNPC);

public:
	void Spawn(void);
	void Precache(void);

	int  TranslateSchedule(int scheduleType);

	void HandleAnimEvent(animevent_t* pEvent);
	float MaxYawSpeed() { return 360.0f; }

	void Shoot(int hand);

	int  MeleeAttack1Conditions(float flDot, float flDist);
	int	 RangeAttack1Conditions(float flDot, float flDist);
	int	 RangeAttack2Conditions(float flDot, float flDist);

	int	 SelectSchedule(void);

	void RunTask(const Task_t* pTask);
	void StartTask(const Task_t* pTask);

	Class_T	Classify(void);

	int GetSoundInterests(void);

	void RunAI(void);

	float m_flLastShot;
	float m_flDiviation;

	float m_flNextJump;
	Vector m_vecJumpVelocity;

	float m_flNextGrenadeCheck;
	Vector	m_vecTossVelocity;
	bool	m_fThrowGrenade;

	int		m_iTargetRanderamt;

	int		m_iFrustration;

	int		m_iAmmoType;

public:
	DECLARE_DATADESC();
	DEFINE_CUSTOM_AI;

};


#endif // NPC_ASSASSIN_H
