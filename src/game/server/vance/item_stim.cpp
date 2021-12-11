#include "cbase.h"
#include "gamerules.h"
#include "vance_player.h"
#include "items.h"
#include "in_buttons.h"
#include "engine/IEngineSound.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CItemStim : public CItem
{
	DECLARE_CLASS( CItemStim, CItem );

public:

	void Spawn();
	void Precache();
	bool MyTouch( CBasePlayer *pPlayer );
};

LINK_ENTITY_TO_CLASS( item_stim, CItemStim );
PRECACHE_REGISTER( item_stim );

// Alias for temporary replacement
LINK_ENTITY_TO_CLASS( item_healthvial, CItemStim );
PRECACHE_REGISTER( item_healthvial );


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CItemStim::Spawn()
{
	BaseClass::Spawn();

	Precache();
	SetModel( "models/healthvial.mdl" );
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CItemStim::Precache()
{
	PrecacheModel("models/healthvial.mdl");

	PrecacheScriptSound( "Stim.Touch" );
}


//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pPlayer - 
// Output : 
//-----------------------------------------------------------------------------
bool CItemStim::MyTouch( CBasePlayer *pPlayer )
{
	CVancePlayer *pVancePlayer = static_cast<CVancePlayer *>( pPlayer );

	if ( pVancePlayer->GiveStim() )
	{
		CSingleUserRecipientFilter user( pPlayer );
		user.MakeReliable();

		UserMessageBegin( user, "ItemPickup" );
		WRITE_STRING( GetClassname() );
		MessageEnd();

		CPASAttenuationFilter filter( pPlayer, "Stim.Touch" );
		EmitSound( filter, pPlayer->entindex(), "Stim.Touch" );

		UTIL_Remove( this );
		return true;
	}

	return false;
}