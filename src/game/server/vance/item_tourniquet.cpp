#include "cbase.h"
#include "gamerules.h"
#include "vance_player.h"
#include "items.h"
#include "in_buttons.h"
#include "engine/IEngineSound.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CItemTourniquet : public CItem
{
	DECLARE_CLASS( CItemTourniquet, CItem );

public:

	void Spawn();
	void Precache();
	bool MyTouch( CBasePlayer *pPlayer );
};

LINK_ENTITY_TO_CLASS( item_tourniquet, CItemTourniquet );
PRECACHE_REGISTER( item_tourniquet );


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CItemTourniquet::Spawn()
{
	BaseClass::Spawn();

	Precache();
	SetModel( "models/healthvial.mdl" );
	SetRenderColor( 255, 0, 0 );
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CItemTourniquet::Precache()
{
	PrecacheModel("models/healthvial.mdl");

	PrecacheScriptSound( "Tourniquet.Touch" );
}


//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pPlayer - 
// Output : 
//-----------------------------------------------------------------------------
bool CItemTourniquet::MyTouch( CBasePlayer *pPlayer )
{
	CVancePlayer *pVancePlayer = static_cast<CVancePlayer *>( pPlayer );

	if ( pVancePlayer->GiveTourniquet() )
	{
		CSingleUserRecipientFilter user( pPlayer );
		user.MakeReliable();

		UserMessageBegin( user, "ItemPickup" );
		WRITE_STRING( GetClassname() );
		MessageEnd();

		CPASAttenuationFilter filter( pPlayer, "Tourniquet.Touch" );
		EmitSound( filter, pPlayer->entindex(), "Tourniquet.Touch" );

		UTIL_Remove( this );
		return true;
	}

	return false;
}