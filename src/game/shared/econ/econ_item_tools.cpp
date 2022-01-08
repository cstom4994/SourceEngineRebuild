﻿//========= Copyright Valve Corporation, All rights reserved. ============//
#include "cbase.h"
#include "game_item_schema.h"
#include "econ_item_interface.h"
#include "econ_item_tools.h"
#include "econ_item_constants.h"
#include "econ_dynamic_recipe.h"
#include "schemainitutils.h"



bool BStringsEqual( const char *pszA, const char *pszB )
{
	if ( pszA == NULL )
		return pszB == NULL;

	if ( pszB == NULL )
		return false;

	return !V_strcmp( pszA, pszB );
}

const unsigned int g_CapabilityApplicationMap[] =
{
															// if we have a tool that has this capability...
	// ...then we check to see if the tool target has
	// this capability

	ITEM_CAP_PAINTABLE,										// ITEM_CAP_PAINTABLE
	ITEM_CAP_NAMEABLE,										// ITEM_CAP_NAMEABLE
	ITEM_CAP_DECODABLE,										// ITEM_CAP_DECODABLE
	0,														// ITEM_CAP_UNUSED; was ITEM_CAP_CAN_MOD_SOCKET
	ITEM_CAP_CAN_CUSTOMIZE_TEXTURE,							// ITEM_CAP_CAN_CUSTOMIZE_TEXTURE
	0,														// ITEM_CAP_USABLE
	0,														// ITEM_CAP_USABLE_GC
	ITEM_CAP_CAN_GIFT_WRAP,									// ITEM_CAP_CAN_GIFT_WRAP
	0,														// ITEM_CAP_USABLE_OUT_OF_GAME
	ITEM_CAP_CAN_COLLECT,									// ITEM_CAP_CAN_COLLECT
	0,														// ITEM_CAP_CAN_CRAFT_COUNT
	0,														// ITEM_CAP_CAN_CRAFT_MARK
	ITEM_CAP_PAINTABLE_TEAM_COLORS | ITEM_CAP_PAINTABLE,	// ITEM_CAP_PAINTABLE_TEAM_COLORS
	0,														// ITEM_CAP_CAN_BE_RESTORED
	ITEM_CAP_CAN_USE_STRANGE_PARTS,							// ITEM_CAP_CAN_USE_STRANGE_PARTS
	ITEM_CAP_CAN_CARD_UPGRADE,								// ITEM_CAP_CAN_CARD_UPGRADE
	ITEM_CAP_CAN_STRANGIFY,									// ITEM_CAP_CAN_STRANGIFY
	ITEM_CAP_CAN_KILLSTREAKIFY,								// ITEM_CAP_CAN_KILLSTREAKIFY
	ITEM_CAP_CAN_CONSUME,									// ITEM_CAP_CAN_CONSUME
	ITEM_CAP_CAN_SPELLBOOK_PAGE,							// ITEM_CAP_CAN_SPELLBOOK_PAGE
	ITEM_CAP_HAS_SLOTS,										// ITEM_CAP_HAS_SLOTS
	ITEM_CAP_DUCK_UPGRADABLE,								// ITEM_CAP_DUCK_UPGRADABLE
	ITEM_CAP_CAN_UNUSUALIFY,								// ITEM_CAP_CAN_UNUSUALIFY
};

COMPILE_TIME_ASSERT( ARRAYSIZE( g_CapabilityApplicationMap ) == NUM_ITEM_CAPS );

//---------------------------------------------------------------------------------------
// Purpose:
//---------------------------------------------------------------------------------------
bool IEconTool::ShouldDisplayQuantity( const IEconItemInterface *pTool ) const
{
	Assert( pTool );

	const GameItemDefinition_t *pItemDef = pTool->GetItemDefinition();
	if ( !pItemDef )
		return false;

	static CSchemaAttributeDefHandle pAttrDef_UnlimitedQuantity( "unlimited quantity" );
	if ( pTool->FindAttribute( pAttrDef_UnlimitedQuantity ) )
		return false;

	if ( pTool->GetQuantity() >= 0 )
	{
		if ( (pItemDef->GetCapabilities() & ITEM_CAP_USABLE_GC) != 0 )
			return true;

		if ( pItemDef->IsTool() )
			return true;
	}

	return false;
}

//---------------------------------------------------------------------------------------
// Purpose:
//---------------------------------------------------------------------------------------
CEconTool_WrappedGift::CEconTool_WrappedGift( const char *pszTypeName, const char *pszUseString, item_capabilities_t unCapabilities, KeyValues *pUsageKV )
	: IEconTool( pszTypeName, pszUseString, NULL, unCapabilities )
	, m_pszDeliveredGiftItemDefName( NULL )
	, m_pDeliveredGiftItemDef( NULL )
	, m_bIsGlobalGift( false )
	, m_bIsDirectGift( false )
{
	if ( pUsageKV )
	{
		m_bIsGlobalGift = pUsageKV->GetBool( "target_type_global", false );
		m_pszDeliveredGiftItemDefName = pUsageKV->GetString( "delivered_gift_item_def", NULL );
		m_bIsDirectGift = pUsageKV->GetBool( "is_direct_gift", false );
	}
}

//---------------------------------------------------------------------------------------
// Purpose:
//---------------------------------------------------------------------------------------
bool CEconTool_WrappedGift::BFinishInitialization()
{
	// Now that we've finished parsing our definitions, look for a match.
	if ( m_pszDeliveredGiftItemDefName )
	{
		m_pDeliveredGiftItemDef = GetItemSchema()->GetItemDefinitionByName( m_pszDeliveredGiftItemDefName );
	}

	// We're done with this value.
	m_pszDeliveredGiftItemDefName = NULL;

	return IEconTool::BFinishInitialization();
}

//---------------------------------------------------------------------------------------
// Purpose:
//---------------------------------------------------------------------------------------
CEconTool_GiftWrap::CEconTool_GiftWrap( const char *pszTypeName, const char *pszUseString, item_capabilities_t unCapabilities, KeyValues *pUsageKV )
	: IEconTool( pszTypeName, NULL, NULL, unCapabilities )
	, m_pszWrappedGiftItemDefName( NULL )
	, m_pWrappedGiftItemDef( NULL )
{
	if ( pUsageKV )
	{
		m_pszWrappedGiftItemDefName = pUsageKV->GetString( "wrapped_gift_item_def", NULL );
	}
}

//---------------------------------------------------------------------------------------
// Purpose:
//---------------------------------------------------------------------------------------
bool CEconTool_GiftWrap::BFinishInitialization()
{
	// Now that we've finished parsing our definitions, look for a match.
	if ( m_pszWrappedGiftItemDefName )
	{
		m_pWrappedGiftItemDef = GetItemSchema()->GetItemDefinitionByName( m_pszWrappedGiftItemDefName );
	}

	// We're done with this value.
	m_pszWrappedGiftItemDefName = NULL;

	return m_pWrappedGiftItemDef != NULL
		&& IEconTool::BFinishInitialization();
}

//---------------------------------------------------------------------------------------
// Purpose:
//---------------------------------------------------------------------------------------
bool CEconTool_GiftWrap::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	if ( pToolSubject->GetQuality() == AE_SELFMADE ||
		 pToolSubject->GetQuality() == AE_COMMUNITY ||
		 pToolSubject->GetQuality() == AE_CUSTOMIZED ||
		 pToolSubject->GetQuality() == AE_NORMAL )
	{
		return false;
	}

	// If an item is currently trade restricted, other flags don't matter (I think).
	if ( ( pToolSubject->GetUntradabilityFlags() & k_Untradability_Temporary ) != 0 )
		return false;

	// One item still has the gift wrap cap, which is the engagement ring ( Something Special For Someone Special (Tool) ).
	// However, the can_gift_wrap cap shouldn't overcome temporary trade restrictions.
	static CSchemaAttributeDefHandle pAttrDef_ToolNeedsGiftwrap( "tool needs giftwrap" );

	const bool cbSubjectNeedsGiftWrap = pToolSubject->FindAttribute( pAttrDef_ToolNeedsGiftwrap );
	const bool cbSubjectCanTrade = pToolSubject->IsTradable();
	const bool cbSubjectCanProceed = cbSubjectNeedsGiftWrap || cbSubjectCanTrade;
 
	if ( !cbSubjectCanProceed )
		return false;

	static CSchemaAttributeDefHandle pAttrDef_CannotGiftwrap( "cannot giftwrap" );
	if ( pToolSubject->FindAttribute( pAttrDef_CannotGiftwrap ) )
		return false;

	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

CEconTool_StrangeCountTransfer::CEconTool_StrangeCountTransfer( const char *pszTypeName, item_capabilities_t unCapabilities ) 
	: IEconTool( pszTypeName, NULL, NULL, unCapabilities )
{
#ifdef CLIENT_DLL
	m_pItemSrc = NULL;
	m_pItemDest = NULL;
#endif // CLIENT_DLL
}

bool CEconTool_StrangeCountTransfer::AreItemsEligibleForStrangeCountTransfer( const IEconItemInterface *pItem1, const IEconItemInterface *pItem2 )
{
	if ( !pItem1 || !pItem2 )
		return false;

	const char *pItem1Xifier = pItem1->GetItemDefinition()->GetXifierRemapClass();
	const char *pItem2Xifier = pItem2->GetItemDefinition()->GetXifierRemapClass();

	// if no xifier class, check if the item defs are the same
	if ( !pItem1Xifier || !pItem2Xifier )
	{
		if ( pItem1->GetItemDefinition() != pItem2->GetItemDefinition() )
		{
			return false;
		}
	}
	else if ( V_stricmp( pItem1Xifier, pItem2Xifier ) != 0 )
	{
		return false;
	}
	
	// Item defs are compatabible, are there attributes? Check strange
	// Check if they are both strange (have kill eater). Quality is less important
	if ( !BIsItemStrange( pItem1) || !BIsItemStrange( pItem2 ) )
		return false;

	return true;
}


bool CEconTool_StrangePart::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	// Abort if for some reason we don't know what type of attribute we're trying to track.
	static CSchemaAttributeDefHandle pAttrDef_StrangePartCounterID( "strange part new counter ID" );

	float flNewScoreType;
	if ( !FindAttribute_UnsafeBitwiseCast<attrib_value_t>( pTool, pAttrDef_StrangePartCounterID, &flNewScoreType ) )
		return false;

	// Make sure we're "strange" in that we have at least one attribute tracking scores. We can't
	// explicitly test for quality here because now we can have strange vintages, etc.
	if ( GetKillEaterAttrCount() <= 0 )
		return false;

	if ( !pToolSubject->FindAttribute( GetKillEaterAttr_Score( 0 ) ) )
		return false;

	// Make sure the target item doesn't already have the property this tool is trying to
	// apply, unless that counter is restricted, in which case we allow a second stat to be
	// added with the same value.
	for ( int i = 0; i < GetKillEaterAttrCount(); i++ )
	{
		float flScoreType;
		if ( FindAttribute_UnsafeBitwiseCast<attrib_value_t>( pToolSubject, GetKillEaterAttr_Type( i ), &flScoreType ) &&	// if we have a counter in this slot...
			 RoundFloatToInt( flScoreType ) == RoundFloatToInt( flNewScoreType ) &&		// ...and it's counting the same thing...
			 !pToolSubject->FindAttribute( GetKillEaterAttr_Restriction( i ) ) )		// ...and that counter isn't restricted
		{
			return false;
		}
	}

	// Make sure we have at least one empty customizable attribute slot.
	bool bFoundEmptyAttributeSlot = false;

	for ( int i = 0; i < GetKillEaterAttrCount(); i++ )
	{
		// Ignore non-user-customizable attributes.
		if ( !GetKillEaterAttr_IsUserCustomizable( i ) )
			continue;

		// We expect to have both or neither of a user-customizable attribute. If this isn't the
		// case the later logic will be wrong.
		const bool bFoundTypeAttribute = pToolSubject->FindAttribute( GetKillEaterAttr_Type( i ) );
		Assert( bFoundTypeAttribute == pToolSubject->FindAttribute( GetKillEaterAttr_Score( i ) ) );

		if ( !bFoundTypeAttribute )
		{
			bFoundEmptyAttributeSlot = true;
			break;
		}
	}

	if ( !bFoundEmptyAttributeSlot )
		return false;

	// Check to make sure the definition of the item we're trying to apply to has the tags we need
	// to match and doesn't have any tags that we need to avoid. We use these to avoid tracking
	// damage done for a medigun, etc.
	const GameItemDefinition_t *pSubjectItemDef = pToolSubject->GetItemDefinition();
	if ( !pSubjectItemDef )
		return false;

#if defined( TF_DLL ) || defined( TF_GC_DLL ) || defined( PONDER_CLIENT_DLL )
	// Strange Cosmetics can take on any part
	if ( pSubjectItemDef->GetDefaultLoadoutSlot() == LOADOUT_POSITION_MISC )
	{
		return true;
	}
#endif

	FOR_EACH_VEC( m_RequiredTags.GetTagsList(), i )
	{
		if ( !pSubjectItemDef->HasEconTag( m_RequiredTags.GetTagsList()[i] ) )
			return false;
	}

	FOR_EACH_VEC( m_RequiredMissingTags.GetTagsList(), i )
	{
		if ( pSubjectItemDef->HasEconTag( m_RequiredMissingTags.GetTagsList()[i] ) )
			return false;
	}
	
	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

static const char *s_pszStrangeRestrictionTypes[] =
{
	"",										// kStrangeEventRestriction_None
	"victim_account_id",					// kStrangeEventRestriction_VictimSteamAccount
#if defined( TF_DLL ) || defined( TF_GC_DLL ) || defined( PONDER_CLIENT_DLL )
	"map",									// kStrangeEventRestriction_Map
	"competitive",							// kStrangeEventRestriction_Competitive
#endif // defined( TF_DLL ) || defined( TF_GC_DLL ) || defined( PONDER_CLIENT_DLL )
};

COMPILE_TIME_ASSERT( ARRAYSIZE( s_pszStrangeRestrictionTypes ) == kStrangeEventRestrictionCount );

CEconTool_StrangePartRestriction::CEconTool_StrangePartRestriction( const char *pszTypeName, const char *pszUseString, item_capabilities_t unCapabilities, KeyValues *pUsageKV )
	: IEconTool( pszTypeName, pszUseString, NULL, unCapabilities )
	, m_eRestrictionType( kStrangeEventRestriction_None )				// default-initialize to failure
	, m_unRestrictionValue( (unsigned int)-1 )
{
	Assert( pUsageKV != NULL );

	// Parse our restriction type from a string. Anything invalid here will be handled below in the IsValid()
	// check.
	const int iRestrictionType = StringFieldToInt( pUsageKV->GetString( "restriction_type", "" ), &s_pszStrangeRestrictionTypes[0], ARRAYSIZE( s_pszStrangeRestrictionTypes ) );
	if ( iRestrictionType > 0 )
	{
		m_eRestrictionType = (strange_event_restriction_t)iRestrictionType;
	}

	// We'll use this value later from inside BFinishInitialization(). We may have to look at other
	// values from parts of the schema that haven't been parsed yet, like map or item names.
	m_pszRestrictionValue = pUsageKV->GetString( "restriction_value", NULL );
}

bool CEconTool_StrangePartRestriction::BFinishInitialization()
{
	// Run different parsers based on our restriction type.
	switch ( m_eRestrictionType )
	{
		// We don't expect anything for our sub-value when dealing with Steam accounts. Asserting based on
		// bad data is dumb but we don't really have any way of sending an error all the way up the tree.
		case kStrangeEventRestriction_None:
		case kStrangeEventRestriction_VictimSteamAccount:
			if ( m_pszRestrictionValue )
				return false;
			
			m_unRestrictionValue = 0;
			break;

#if defined( TF_DLL ) || defined( TF_GC_DLL ) || defined( PONDER_CLIENT_DLL )
		case kStrangeEventRestriction_Map:
		{
			if ( !m_pszRestrictionValue )
				return false;

			const MapDef_t *pSchemaMap = GetItemSchema()->GetMasterMapDefByName( m_pszRestrictionValue );
			if ( !pSchemaMap )
				return false;

			m_unRestrictionValue = pSchemaMap->m_nDefIndex;
		}
		break;
		case kStrangeEventRestriction_Competitive:
		{
			if (!m_pszRestrictionValue)
				return false;

			// Season string to int
			m_unRestrictionValue = V_atoi(m_pszRestrictionValue);
		}
		break;
#endif // defined( TF_DLL ) || defined( TF_GC_DLL ) || defined( PONDER_CLIENT_DLL )

		default:
			AssertMsg1( false, "CEconTool_StrangePartRestriction() doesn't understand how to parse restriction type %i.", m_eRestrictionType );
			return false;
	}

	// We're done with this value now.
	m_pszRestrictionValue = NULL;

	return m_eRestrictionType != kStrangeEventRestriction_None
		&& m_unRestrictionValue != (unsigned int)-1
		&& IEconTool::BFinishInitialization();
}

bool CEconTool_StrangePartRestriction::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pTool->GetItemDefinition() );
	Assert( pToolSubject );

	if ( !IEconTool::CanApplyTo( pTool, pToolSubject ) )
		return false;

	// Abort if for some reason we don't know what type of restriction we're trying to apply.
	if ( m_eRestrictionType == kStrangeEventRestriction_None )
		return false;

	// Abort if we don't have our tool information. We'll need this below to avoid duplicating
	// scores/restrictions.
	const CEconTool_StrangePartRestriction *pToolRestriction = pTool->GetItemDefinition()->GetTypedEconTool<CEconTool_StrangePartRestriction>();
	if ( !pToolRestriction )
		return false;

	// Make sure we're "strange" in that we have at least one attribute tracking scores. We can't
	// explicitly test for quality here because now we can have strange vintages, etc.
	if ( GetKillEaterAttrCount() <= 0 )
		return false;

	if ( !pToolSubject->FindAttribute( GetKillEaterAttr_Score( 0 ) ) )
		return false;
	
	// Look through all of the strange attributes on this item. We're looking for a slot that
	// has a score that we're tracking where that score doesn't already have a restriction.
	// If we find one, we can restrict that particular slot as long as doing so wouldn't generate
	// a duplicate score (ie., "soldier kills on Hightower"). We don't need to enumerate them
	// here, just find existence/nonexistence of at least one valid target.
	for ( int i = 0; i < GetKillEaterAttrCount(); i++ )
	{
		if ( GetItemSchema()->BCanStrangeFilterApplyToStrangeSlotInItem( pToolRestriction->GetRestrictionType(), pToolRestriction->GetRestrictionValue(), pToolSubject, i, NULL ) )
			return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CEconTool_ItemDynamicRecipe::CEconTool_ItemDynamicRecipe( const char *pszTypeName, const char *pszUseString, item_capabilities_t unCapabilities, KeyValues *pUsageKV )
	: IEconTool( pszTypeName, pszUseString, NULL, unCapabilities )
{
	COMPILE_TIME_ASSERT( sizeof( attrib_value_t ) == sizeof( uint32 ) );
	COMPILE_TIME_ASSERT( sizeof( attrib_value_t ) == sizeof( float ) );

	if ( pUsageKV )
	{
		BInitFromKV( pUsageKV, &m_vecErrors );
	}
}

const char* CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::m_pszUseParentNameIdentifier = "use_parents_item_def";

//-----------------------------------------------------------------------------
// Purpose: Make sure each of our components are fully formed.  Return false
//			if any components fail BFinishInitialization_Internal()
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::BFinishInitialization()
{
	CBaseRecipeComponent::ComponentAttribVector_t attribVec;

	FOR_EACH_VEC( m_vecComponents, i )
	{
		m_vecComponents[i]->BFinishInitialization_Internal( &m_vecErrors, &attribVec );	
	}

	// Emit any errors we've accumulated during initialization
	FOR_EACH_VEC( m_vecErrors, i )
	{
#ifdef GC_DLL
		EmitError( SPEW_GC, "%s\n", m_vecErrors[i].Get() );
#else
		AssertMsg1( 0, "%s\n", m_vecErrors[i].Get() );
#endif
	}

	if( m_vecErrors.Count() > 0 )
		return false;

	// Make sure we have at least one item required
	return IEconTool::BFinishInitialization();
}

//-----------------------------------------------------------------------------
// Purpose: Iterate through attributes on pTool to see if any can accept pToolSubject.
//			Return true if any attributes match.
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	// Iterate through all the attributes on the tool and see if the subject item matches
	// any of the recipe component attributes
	CRecipeComponentMatchingIterator matchingIterator( pTool, pToolSubject );
	pTool->IterateAttributes( &matchingIterator );

	const CUtlVector< const CEconItemAttributeDefinition* >& vecMatchingAttribs = matchingIterator.GetMatchingComponentInputs();
	// No matches, can't apply!
	if( vecMatchingAttribs.Count() == 0 )
	{
		return false;
	}

	return true;
}

CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::CBaseRecipeComponent( bool bIsOutput, const CBaseRecipeComponent* pParent ) 
	: m_bIsOutput( bIsOutput )
	, m_flChanceOfApplying( 1.f )
	, m_pParent( pParent )
	, m_flTotalWeights( 0.f )
	, m_eQuality( AE_UNDEFINED )
	, m_attributesMatchingType( ATTRIBUTES_MATCH_NONE )
{}

CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::~CBaseRecipeComponent()
{
	m_vecAdditionalComponents.PurgeAndDeleteElements();
}

//-----------------------------------------------------------------------------
// Purpose:	 Roll chance of component applying to the tool
//-----------------------------------------------------------------------------
#ifdef GC_DLL
int CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::RollCount() const
{
	if( m_vecCountChances.Count() == 0 )
		return 1;

	float flRand = RandomFloat( 0.f, 1.f ) * m_flTotalWeights;
	float flAccum = 0.f;

	// Go through and see which counts gets rolled
	FOR_EACH_VEC( m_vecCountChances, i )
	{
		const CountChance_t& countChance = m_vecCountChances[i];

		flAccum += countChance.m_flChance;
		if ( flRand <= flAccum )
		{
			// Winner!  Roll within its range
			return RandomInt( countChance.m_nMinCount, countChance.m_nMaxCount );
		}
	}

	AssertMsg( 0, "Failed to generate a count for recipe component.  Defaulting to 1" );
	return 1;
}

bool CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::RollChanceOfApplying() const
{
	// Guaranteed!
	if( m_flChanceOfApplying == 1.f )
		return true;

	return RandomFloat() < m_flChanceOfApplying;
}
#endif

//-----------------------------------------------------------------------------
// Purpose: Set chance for attributes to apply.
//-----------------------------------------------------------------------------
void CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::SetChanceOfApplying( float flChance )
{
	Assert( flChance >= 0.f && flChance <= 1.f );
	clamp( flChance, 0.f, 1.f );
	m_flChanceOfApplying = flChance;
}

bool CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::BFinishInitialization_Internal( CUtlVector<CUtlString>* pVecErrors, ComponentAttribVector_t* pAttribVec  )
{
	FOR_EACH_VEC( m_vecAdditionalComponents, i )
	{
		SCHEMA_INIT_SUBSTEP( m_vecAdditionalComponents[i]->BFinishInitialization_Internal( pVecErrors, pAttribVec ) );
	}

	return SCHEMA_INIT_SUCCESS();
}

void CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::GetIsGuaranteed( int &nFlags ) const
{
	// If we've got a 100% chance of applying, or we're the root (no parent) then we
	// can mark ourselves as guaranteed and continue to check our children to see if
	// any of them are guaranteed as well.
	if ( m_flChanceOfApplying == 1.f || !m_pParent )
	{
		nFlags |= GetIsOutput() ? GUARANTEED_OUTPUT : GUARANTEED_INPUT;

		FOR_EACH_VEC( m_vecAdditionalComponents, i )
		{
			m_vecAdditionalComponents[i]->GetIsGuaranteed( nFlags );
		}
	}
}


CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentDefinedItem::CDynamicRecipeComponentDefinedItem( bool bIsOutput, const CBaseRecipeComponent* pParent )
	: CBaseRecipeComponent( bIsOutput, pParent )
{}

CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentDefinedItem::~CDynamicRecipeComponentDefinedItem()
{}

//-----------------------------------------------------------------------------
// Purpose: Make sure m_strName refers to an actual item def.  Return false
//			if it doesn not.  Child components are allowed to have "use_parents_item_def"
//			as their item name.
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentDefinedItem::BFinishInitialization_Internal( CUtlVector<CUtlString>* pVecErrors, ComponentAttribVector_t* pAttribVec )
{
	// Go through and make sure we have a bit of information that let's us describe an item
	bool bAnyDataSet = false;

	// Item def?
	if ( m_pParent == NULL && GetItemSchema()->GetItemDefinitionByName( m_strName ) )
	{
		bAnyDataSet = true;
	}
	else if ( BStringsEqual( m_strName, m_pszUseParentNameIdentifier ) || GetItemSchema()->GetItemDefinitionByName( m_strName ) )
	{
		bAnyDataSet = true;
	}

	// Quality?
	if ( m_eQuality != AE_UNDEFINED )
	{
		bAnyDataSet = true;
	}

	// Attributes?
	if ( m_vecDynamicAttributes.Count() )
	{
		bAnyDataSet = true;
	}

	// We better have one of the above
	SCHEMA_INIT_CHECK( bAnyDataSet, "Not enough data to describe component" );

#ifdef GC_DLL
	// Get next available attrib def for defining the item
	CEconItemAttributeDefinition* pAttribDef = GetNextAvailableAttributeWithBaseName( GetAttributeName(), pAttribVec );
	SCHEMA_INIT_CHECK( pAttribDef, "Too many potential components" );
	if( pAttribDef )
	{
		pAttribVec->AddToTail( pAttribDef );
	}
#endif

	SCHEMA_INIT_SUBSTEP( BaseClass::BFinishInitialization_Internal( pVecErrors, pAttribVec ) );

	return SCHEMA_INIT_SUCCESS();
}

//-----------------------------------------------------------------------------
// Purpose: Parse out our item definition name and quality.  Return false if 
//			either does not exist
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentDefinedItem::ParseKV( KeyValues *pKV, CUtlVector<CUtlString> *pVecErrors )
{
	bool bNoItemDef = !!pKV->FindKey( "no_item_def" );
	bool bItemName = !!pKV->FindKey( "item_name" );

	// Make sure only one of the above is set
	SCHEMA_INIT_CHECK( bNoItemDef != bItemName,
						"Both \"no_item_def\" and \"item_name\" specified in component." );

	// Make sure at least one of the above is set
	SCHEMA_INIT_CHECK( bNoItemDef || bItemName,
						"Neither \"no_item_def\" or \"item_name\" specified in component." );

	// If they specified an item name, then we need to grab it
	if ( bItemName )
	{
		m_strName = pKV->GetString( "item_name", NULL );
	}

	return BaseClass::ParseKV( pKV, pVecErrors );
}

//-----------------------------------------------------------------------------
// Purpose: Convert ourselves into an attribute.  Return false if our encoded
//			attributes exceed the allocated space for attributes
//-----------------------------------------------------------------------------
#ifdef GC_DLL
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentDefinedItem::AddRecipeComponentAsAttribute( CEconItem *pItem, const CEconGameAccount *pGameAccount ) const
{
	// Check if we should even apply
	if( !RollChanceOfApplying() )
		return true;

	// Gather up all the current attributes on the item
	ComponentAttribVector_t attribVec;
	CRecipeComponentMatchingIterator matchingIterator( pItem, NULL );
	pItem->IterateAttributes( &matchingIterator );
	attribVec.AddVectorToTail( matchingIterator.GetMatchingComponentInputs() );
	attribVec.AddVectorToTail( matchingIterator.GetMatchingComponentOutputs() );

	// Get next available attrib def for defining the item
	const CEconItemAttributeDefinition* pAttribDef = GetNextAvailableAttributeWithBaseName( GetAttributeName(), &attribVec );
	if( !pAttribDef )
		return false;

	uint32 nFlags = 0;
	CAttribute_DynamicRecipeComponent typedValue;

	// Check if our item name is specified to use our parent's
	const char* pszItemDefName = m_strName;
	if ( m_strName && m_strName[0] )
	{
		if( BStringsEqual( m_pszUseParentNameIdentifier, pszItemDefName ) && m_pParent )
		{
			// It's only possible to have another CDynamicRecipeComponentDefinedItem as a parent
			const CDynamicRecipeComponentDefinedItem* pParentDefinedItemComponent = dynamic_cast< const CDynamicRecipeComponentDefinedItem* >( m_pParent );
			AssertMsg( pParentDefinedItemComponent, "Parent attribute passed into defined item component is not a defined item component" );
			if( !pParentDefinedItemComponent )
			{
				return false;
			}
			// Adopt our parent's item name
			pszItemDefName = pParentDefinedItemComponent->m_strName;
		}
	
		// Make sure this item def exists
		CEconItemDefinition* pItemDef = GetItemSchema()->GetItemDefinitionByName( pszItemDefName );
		AssertMsg1( pItemDef, "No item def named %s found when applying defined item component", pszItemDefName );
		if( !pItemDef )
		{
			return false;
		}

		// Set the item def
		typedValue.set_def_index( (uint32)pItemDef->GetDefinitionIndex() );
		nFlags |= DYNAMIC_RECIPE_FLAG_PARAM_ITEM_DEF_SET;
	}

	// Set the quality, if we're supposed to
	if ( m_eQuality != AE_UNDEFINED )
	{
		typedValue.set_item_quality( (uint32)m_eQuality );
		nFlags |= DYNAMIC_RECIPE_FLAG_PARAM_QUALITY_SET;
	}

	nFlags |= m_bIsOutput ? DYNAMIC_RECIPE_FLAG_IS_OUTPUT : 0;

	if ( m_attributesMatchingType == ATTRIBUTES_MATCH_ALL )
	{
		nFlags |= DYNAMIC_RECIPE_FLAG_PARAM_ATTRIBUTE_SET_ALL;
	}
	else if ( m_attributesMatchingType == ATTRIBUTES_MATCH_ANY )
	{
		nFlags |= DYNAMIC_RECIPE_FLAG_PARAM_ATTRIBUTE_SET_ANY;
	}

	// Make sure any of the flags (besides the output flag) is set
	if ( ( nFlags & ~DYNAMIC_RECIPE_FLAG_IS_OUTPUT ) == 0 )
	{
		AssertMsg(0, "Created component without any data flags set!" );
		return false;
	}
	
	typedValue.set_component_flags( nFlags );
	typedValue.set_num_required( RollCount() );
	typedValue.set_num_fulfilled( 0 );

	// Write out attribute all attribute indexes and values, separated by what we expect to be an invalid character sequence
	CUtlString strAttribs;
	FOR_EACH_VEC( m_vecDynamicAttributes, i )
	{
		if( i != 0 ) 
		{
			strAttribs.Append( g_pszAttrEncodeSeparator );
		}
		// Convert all of our attributes into a string.
		strAttribs.Append( CFmtStr( "%d", m_vecDynamicAttributes[i].m_AttrIndex ) );
		strAttribs.Append( g_pszAttrEncodeSeparator );
		strAttribs.Append( m_vecDynamicAttributes[i].m_strAttrData.Get() );
	}

	// Make sure we're not too long
	if( strAttribs.Length() >= 1024 )
	{
		AssertMsg1( 0, "String-encoded attributes exceeds 1024 characters, when encoding component %s", m_strName.Get() );
		return false;
	}

	// Set it in there!
	typedValue.set_attributes_string( strAttribs.Get() );

	// Check to see if we're about to create a duplicate.  There's no need to spend another
	// attribute to describe the same item.  Let's instead just increase the count on the
	// already-existing attribute.
	FOR_EACH_VEC( attribVec, i )
	{
		CAttribute_DynamicRecipeComponent existingValue;
		if( pItem->FindAttribute( attribVec[i], &existingValue ) )
		{
			if( typedValue.def_index()			== existingValue.def_index() &&
				typedValue.item_quality()		== existingValue.item_quality() &&
				typedValue.component_flags()			== existingValue.component_flags() &&
				typedValue.attributes_string()	== existingValue.attributes_string() )
			{
				pAttribDef = attribVec[i];
				existingValue.set_num_required( existingValue.num_required() + typedValue.num_required() );
				typedValue = existingValue;
				break;
			}
		}
	}
	

	pItem->SetDynamicAttributeValue( pAttribDef, typedValue );

	// Go through and add any additional components that depend on this component
	FOR_EACH_VEC( m_vecAdditionalComponents, i )
	{
		CBaseRecipeComponent* pAdditionalComponent = m_vecAdditionalComponents[i];
		pAdditionalComponent->AddRecipeComponentAsAttribute( pItem, pGameAccount );
	}

	return true;
}

#endif

CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::CDynamicRecipeComponentLootList( bool bIsOutput, const CBaseRecipeComponent* pParent )
	: CEconTool_ItemDynamicRecipe::CBaseRecipeComponent( bIsOutput, pParent )
#ifdef GC_DLL
	, m_eUniqueness( UNIQUE_AMONG_NOTHING )
#endif
{}



CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::~CDynamicRecipeComponentLootList()
{}

//-----------------------------------------------------------------------------
// Purpose: Make sure m_strName actually refers to a lootlist
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::BFinishInitialization_Internal( CUtlVector<CUtlString>* pVecErrors, ComponentAttribVector_t* pAttribVec )
{
	// The game doesn't have all of the lootlists
#ifdef GC_DLL
	SCHEMA_INIT_CHECK( GEconItemSchema().GetLootListByName( m_strName ),
					   "CDynamicRecipeComponentLootList has invalid loot list: %s", m_strName.Get() );

	// Get next available attrib def for defining the item
	CEconItemAttributeDefinition* pAttribDef = GetNextAvailableAttributeWithBaseName( GetAttributeName(), pAttribVec );
	SCHEMA_INIT_CHECK( pAttribDef, "Too many potential recipe components!" );
	if( pAttribDef )
	{
		pAttribVec->AddToTail( pAttribDef );
	}

	// Inputs are not allowed to be marked UNIQUE_AMONG_OUTPUTS.  Rather, mark the outputs UNIQUE_AMONG_INPUTS
	SCHEMA_INIT_CHECK( !(m_eUniqueness == UNIQUE_AMONG_OUTPUTS && !GetIsOutput() ), "Input component marked to be unique among inputs.  Not supported!" );
#endif

	// Skip defined item
	SCHEMA_INIT_SUBSTEP( BaseClass::BFinishInitialization_Internal( pVecErrors, pAttribVec ) );

	return SCHEMA_INIT_SUCCESS();
}

//-----------------------------------------------------------------------------
// Purpose: Parse in our lootlist name and quality.  Return false if either doesn't exist
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::ParseKV( KeyValues *pKV, CUtlVector<CUtlString> *pVecErrors )
{
	const char* pszLootListName = pKV->GetString( "lootlist_name" );
	SCHEMA_INIT_CHECK( pszLootListName != NULL,
					   "Missing lootlist name in lootlist recipe component" );

	m_strName = pszLootListName;

	bool bBaseResult = BaseClass::ParseKV( pKV, pVecErrors );

#ifdef GC_DLL
	// By default, outputs try to avoid rolling as input, and inputs dont try to avoid anything
	m_eUniqueness = GetIsOutput() ? UNIQUE_AMONG_INPUTS : UNIQUE_AMONG_NOTHING;
	const char* pszUniqueness = pKV->GetString( "uniqueness" );
	if ( !V_stricmp( "unique_among_inputs", pszUniqueness ) )
	{
		m_eUniqueness = UNIQUE_AMONG_INPUTS;
	}
	else if ( !V_stricmp( "unique_among_outputs", pszUniqueness ) )
	{
		m_eUniqueness = UNIQUE_AMONG_OUTPUTS;
	}
	else if ( !V_stricmp( "unique_among_everything", pszUniqueness ) )
	{
		m_eUniqueness = UNIQUE_AMONG_EVERYTHING;
	}
#endif

	return bBaseResult;
}


//-----------------------------------------------------------------------------
// Purpose:	Roll our item definition, then call our base to convert ourselves into an attribute
//-----------------------------------------------------------------------------
#ifdef GC_DLL
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::AddRecipeComponentAsAttribute( CEconItem *pItem, const CEconGameAccount *pGameAccount ) const
{
	// Check if we should even apply
	if( !RollChanceOfApplying() )
		return true;

	// See if there's any item defs we should try to avoid
	CRecipeComponentInputDefIndexIterator inputIterator( m_eUniqueness );
	pItem->IterateAttributes( &inputIterator );

	const char* pszItemDefName = NULL;
	// Roll the item and any additional attributes
	CUtlVector< StringEncodedAttribute_t > vecLootlistGeneratedAttributes;
	if (!RollLootlistItemAndAttributes( vecLootlistGeneratedAttributes, &pszItemDefName, &inputIterator.GetMatchingComponentInputs(), pGameAccount ) )
	{
		return false;
	}
	vecLootlistGeneratedAttributes.AddVectorToTail( m_vecDynamicAttributes );

	// Create a temporary defined item component based on the lootlist roll
	CDynamicRecipeComponentDefinedItem definedItem( m_bIsOutput, this );
	definedItem.m_eQuality = m_eQuality;
	definedItem.m_strName = pszItemDefName;
	definedItem.m_attributesMatchingType = m_attributesMatchingType;
	definedItem.m_vecDynamicAttributes = vecLootlistGeneratedAttributes;
	definedItem.m_vecCountChances = m_vecCountChances;
	definedItem.m_flTotalWeights = m_flTotalWeights;

	// Write out this defined item
	definedItem.AddRecipeComponentAsAttribute( pItem, pGameAccount );

	// Create any additional components that depend on this component existing
	FOR_EACH_VEC( m_vecAdditionalComponents, i )
	{
		CBaseRecipeComponent* pAdditionalComponent = m_vecAdditionalComponents[i];
		// Update the parent to be the item we generated
		pAdditionalComponent->SetParent( &definedItem );
		pAdditionalComponent->AddRecipeComponentAsAttribute( pItem, pGameAccount );
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:	Roll our item definition, then call our base to convert ourselves into an attribute
//-----------------------------------------------------------------------------
class CAttributeToStringIterator : public IEconItemUntypedAttributeIterator
{
public:
	CAttributeToStringIterator( CUtlVector< CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::StringEncodedAttribute_t >& vecAdditionalAttribs, CEconItem* pItem )
		: m_vecAdditionalAttribs( vecAdditionalAttribs )
		, m_pItem( pItem )
	{}

	virtual bool OnIterateAttributeValueUntyped( const CEconItemAttributeDefinition *pAttrDef )
	{
		const CEconItem::attribute_t *pAttrInternalData = m_pItem->FindDynamicAttributeInternal( pAttrDef );

		// Only export attributes that we have dynamic data for.
		if ( pAttrInternalData )
		{
			const ISchemaAttributeType *pAttrType = pAttrDef->GetAttributeType();
			Assert( pAttrType );

			// Set the definition index
			auto& attrib = m_vecAdditionalAttribs[ m_vecAdditionalAttribs.AddToTail() ];
			attrib.m_AttrIndex = pAttrDef->GetDefinitionIndex();

			// Convert the value to a string
			std::string sAttrValue;
			pAttrType->ConvertEconAttributeValueToString( pAttrDef, pAttrInternalData->m_value, &sAttrValue );

			Assert( sAttrValue.length() > 0 );
			attrib.m_strAttrData.Set( sAttrValue.c_str() );
		}

		return true;
	}
	
private:

	CUtlVector< CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::StringEncodedAttribute_t >& m_vecAdditionalAttribs;
	CEconItem* m_pItem;
};

//-----------------------------------------------------------------------------
// Purpose: Roll our item definition.  This will give us a list of item definition.  From this list
//			we take the first one and set our item def name and quality to be its.  We then take any
//			attributes that it may have rolled and add them to our attributes as well.  Return false
//			if any of these steps fail.
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CDynamicRecipeComponentLootList::RollLootlistItemAndAttributes( CUtlVector< StringEncodedAttribute_t >& vecAdditionalAttribs
																								, const char** pszDefName
																								, const CUtlVector< item_definition_index_t > *pVecAvoidItemDefs
																								, const CEconGameAccount *pGameAccount ) const
{
	const CEconLootListDefinition* pLootList = GEconItemSchema().GetLootListByName( m_strName );

	if( !pLootList )
	{
		AssertMsg1( 0, "Lootlist %s not found when adding dynamic attribute", m_strName.Get() );
		return false;
	}

	CUtlVector<CEconItem *> vecRolledItems;
	// Roll our items
	CDefaultUniformRandomStream RandomStream;
	if ( !pLootList->BGenerateSingleRollRandomItems( pGameAccount, false, &vecRolledItems ) )
	{
		AssertMsg1( 0, "Error generating item defs from lootlist \"%s\"", m_strName.Get() );
		return false;
	}

	// We're just going to use the first one
	CEconItem* pGeneratedItem = vecRolledItems.Head();

	// Set our name and quality
	(*pszDefName) = pGeneratedItem->GetItemDefinition()->GetDefinitionName();
	const_cast<CDynamicRecipeComponentLootList*>(this)->m_eQuality = (EEconItemQuality)pGeneratedItem->GetQuality();

	// Sniff and encode the attributes
	CAttributeToStringIterator attrToString( vecAdditionalAttribs, pGeneratedItem );
	pGeneratedItem->IterateAttributes( &attrToString );

	// Cleanup
	for( auto pItem : vecRolledItems )
	{
		delete pItem;
	}

	return true;
}

#endif


//-----------------------------------------------------------------------------
// Purpose: Delete all the things
//-----------------------------------------------------------------------------
CEconTool_ItemDynamicRecipe::~CEconTool_ItemDynamicRecipe()
{
	m_vecComponents.PurgeAndDeleteElements();
}

CEconTool_ItemDynamicRecipe::CRecipeComponentInputDefIndexIterator::CRecipeComponentInputDefIndexIterator( EItemDefUniqueness_t eUniqueness )
	: m_eUniqueness( eUniqueness )
{}

bool CEconTool_ItemDynamicRecipe::CRecipeComponentInputDefIndexIterator::OnIterateAttributeValue( const CEconItemAttributeDefinition *pAttrDef, const CAttribute_DynamicRecipeComponent& value )
{
	// We dont care
	if ( m_eUniqueness == CEconTool_ItemDynamicRecipe::UNIQUE_AMONG_NOTHING )
		return true;

	// Only check against outputs
	if ( m_eUniqueness == CEconTool_ItemDynamicRecipe::UNIQUE_AMONG_OUTPUTS && !( value.component_flags() & DYNAMIC_RECIPE_FLAG_IS_OUTPUT ) )
		return true;

	// Only check against inputs
	if ( m_eUniqueness == CEconTool_ItemDynamicRecipe::UNIQUE_AMONG_INPUTS && value.component_flags() & DYNAMIC_RECIPE_FLAG_IS_OUTPUT )
		return true;

	// Add this item def if we haven't seen it
	if ( m_vecInputItemDefs.Find( value.def_index() ) == m_vecInputItemDefs.InvalidIndex() )
	{
		m_vecInputItemDefs.AddToTail( value.def_index() );
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Parse all of our inputs then outputs
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::BInitFromKV( KeyValues *pKVDef, CUtlVector<CUtlString> *pVecErrors )
{
	// Parse the components blocks
	SCHEMA_INIT_SUBSTEP( CBaseRecipeComponent::ParseComponentsBlock( pKVDef, m_vecComponents, pVecErrors, NULL ) );

	// Sort the component vector such that inputs go first
	struct RecipeComponentSorter
	{
		static int SortRecipeComponentVector( CEconTool_ItemDynamicRecipe::CBaseRecipeComponent* const *pComponent1, CEconTool_ItemDynamicRecipe::CBaseRecipeComponent* const *pComponent2 )
		{
			return (*pComponent1)->GetIsOutput() && !(*pComponent2)->GetIsOutput();
		}
	};

	m_vecComponents.Sort( &RecipeComponentSorter::SortRecipeComponentVector );
	
#ifdef GC_DLL
	int nFlags = 0;
	FOR_EACH_VEC( m_vecComponents, i )
	{
		m_vecComponents[i]->GetIsGuaranteed( nFlags );
	}

	SCHEMA_INIT_CHECK( nFlags & GUARANTEED_OUTPUT, "No guaranteed outputs for dynamic recipe" );
	SCHEMA_INIT_CHECK( nFlags & GUARANTEED_INPUT, "No guaranteed inputs for dynamic recipe" );
#endif

	return SCHEMA_INIT_SUCCESS();
}

//-----------------------------------------------------------------------------
// Purpose: Parse the component blocks, determining if this component is an input or output
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::ParseComponentsBlock( KeyValues *pKV, CUtlVector<CBaseRecipeComponent*>& vecComponents, CUtlVector<CUtlString> *pVecErrors, const CBaseRecipeComponent* pParent )
{
	// The components block doesn't exist on the client

	KeyValues *pKVComponents = pKV->FindKey( "components" );
#ifdef GC_DLL
	SCHEMA_INIT_CHECK( pKVComponents || pParent, "Failed to parse components block in dynamic recipe" );
#endif
	if ( pKVComponents )
	{
		// There's duplicate code when we read in like this, but it makes the
		// item defs much easier to read

		// Parse all the inputs
		KeyValues *pKVParameters = pKVComponents->FindKey( "input" );
		if( pKVParameters )
		{
			ParseComponents( pKVParameters, vecComponents, false, pVecErrors, pParent );
		}

#ifdef GC_DLL
		// Parse all the outputs
		pKVParameters = pKVComponents->FindKey( "output" );
		if( pKVParameters )
		{
			ParseComponents( pKVParameters, vecComponents, true, pVecErrors, pParent );
		}
#endif
	}



	return SCHEMA_INIT_SUCCESS();
}

//-----------------------------------------------------------------------------
// Purpose: Create the appropriate component types and have them parse themselves.
//			Returns true if at least one of the components parsed has a 100% chance
//			of applying, and we don't have a parent
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::ParseComponents( KeyValues *pKV, CUtlVector<CBaseRecipeComponent*>& vecComponents, bool bIsOutput, CUtlVector<CUtlString> *pVecErrors, const CBaseRecipeComponent* pParent )
{
	// Go through each entry in the tool
	KeyValues *pEntry = pKV->GetFirstSubKey();
	while( pEntry )
	{
		// Find which type is being specified.
		CBaseRecipeComponent *pComponent = NULL;
		if( pEntry->FindKey( "lootlist_name" ) )
		{
			pComponent = vecComponents[vecComponents.AddToTail( new CDynamicRecipeComponentLootList( bIsOutput, pParent ) )];
		}
		else if ( pEntry->FindKey( "item_name" ) || pEntry->FindKey( "no_item_def" ) )
		{
			pComponent = vecComponents[vecComponents.AddToTail( new CDynamicRecipeComponentDefinedItem( bIsOutput, pParent ) )];
		}
		else
		{
			SCHEMA_INIT_CHECK( false, "Unrecognized recipe component type!" );
		}

		// Now that we've got the right type, parse!
		if( pComponent )
		{
			pComponent->ParseKV( pEntry, pVecErrors );
		}

		pEntry = pEntry->GetNextKey();
	}

	return SCHEMA_INIT_SUCCESS();
}

//-----------------------------------------------------------------------------
// Purpose: Parse in all of the attributes for this component.  Attributes have
//			already been parsed in, so we can immediately check if the attribute exists.
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::ParseKV( KeyValues *pKV, CUtlVector<CUtlString> *pVecErrors )
{
	// Get the quality string
	const char* pszQuality = pKV->GetString( "quality", NULL );
	if ( pszQuality )
	{
		// Convert the quality string to a item quality
		m_eQuality = EconQuality_GetQualityFromString( pszQuality );
		SCHEMA_INIT_CHECK( m_eQuality != AE_UNDEFINED, "Invalid item quality \"%s\" specified for component \"%s\"", pszQuality, m_strName.Get() );
	}

	const char* pszAttributesMatchingType = pKV->GetString( "attributes_matching_type", NULL );
	if ( pszAttributesMatchingType )
	{
		if ( !V_stricmp( pszAttributesMatchingType, "all" ) )
		{
			m_attributesMatchingType = ATTRIBUTES_MATCH_ALL;
		}
		else if ( !V_stricmp( pszAttributesMatchingType, "any" ) )
		{
			m_attributesMatchingType = ATTRIBUTES_MATCH_ANY;
		}
		else
		{
			SCHEMA_INIT_CHECK( 0, "Invalid attributes_matching_type \"%s\"", pszAttributesMatchingType );
		}
	}

	// Parse all of our attributes
	KeyValues* pKVAttribs = pKV->FindKey( "attributes" );
	if( pKVAttribs )
	{
		FOR_EACH_SUBKEY( pKVAttribs, pKVAttribute )
		{
			static_attrib_t staticAttrib;
			
			SCHEMA_INIT_SUBSTEP( staticAttrib.BInitFromKV_SingleLine( "attributes", pKVAttribute, pVecErrors ) );

			const CEconItemAttributeDefinition * pAttrDef = staticAttrib.GetAttributeDefinition();
			SCHEMA_INIT_CHECK( pAttrDef != NULL, "Attribute index %i not found when specifying dynamic recipe", staticAttrib.iDefIndex );

			StringEncodedAttribute_t& attrib = m_vecDynamicAttributes[ m_vecDynamicAttributes.AddToTail() ];
			attrib.m_AttrIndex = pAttrDef->GetDefinitionIndex();
			attrib.m_strAttrData = pKVAttribs->GetString( pKVAttribute->GetName(), "" );

			Assert( !attrib.m_strAttrData.IsEmpty() );
		}
	}

	// Get our chance of applying.  Default to 100%
	float flChance = pKV->GetFloat( "chance", 1.f );
	// Make sure it's in the range (0,1]
	SCHEMA_INIT_CHECK( flChance > 0.f && flChance <= 1.f, "Recipe component chance to apply out of bounds: %f", flChance );
	SetChanceOfApplying( flChance );

	// Read in the "counts" block if it exists
	KeyValues *pKVCounts = pKV->FindKey( "counts" );
	if( pKVCounts )
	{
		// Read check count entry
		FOR_EACH_SUBKEY( pKVCounts, pKVEntry )
		{
			// Split out count range of the format "#-#", or just "#"
			CUtlStringList vecCount;
			const char* pszCount = pKVEntry->GetName();
			V_SplitString( pszCount, "-", vecCount );
			SCHEMA_INIT_CHECK( vecCount.Count() == 1 || vecCount.Count() == 2, "Malformed count value: %s", pszCount );
		
			CountChance_t& countChance = m_vecCountChances[ m_vecCountChances.AddToTail() ];

			// Add up the chances
			countChance.m_flChance = (float)pKVEntry->GetInt();
			m_flTotalWeights += countChance.m_flChance;
			// Set the min and the max.  If no max is specifid, then max is the min
			countChance.m_nMinCount = V_atoi( vecCount[0] );
			countChance.m_nMaxCount = vecCount.Count() > 1 ? V_atoi( vecCount[1] ) : countChance.m_nMinCount;
			// Make sure max >= min and min > 0
			SCHEMA_INIT_CHECK( countChance.m_nMaxCount >= countChance.m_nMinCount, "Recipe component count max is less than the min: %s", pszCount );
			SCHEMA_INIT_CHECK( countChance.m_nMinCount > 0, "Recipe component count min less than 0: %s", pszCount );
		}
	}

	// Init any components we may have in us
	SCHEMA_INIT_CHECK( ParseComponentsBlock( pKV, m_vecAdditionalComponents, pVecErrors, this ), "Failed to parse nested components block in dynamic recipe" );

	return SCHEMA_INIT_SUCCESS();
}


#ifdef GC_DLL
//-----------------------------------------------------------------------------
// Purpose:	This tool will apply recipe components as attributes.  Go through each
//			of our attributes, roll to see if it applies, and convert it to an attribute
//			and add it to the item if we do.  Return false if we ever fail.
//-----------------------------------------------------------------------------
bool CEconTool_ItemDynamicRecipe::BGenerateDynamicAttributes( CEconItem* pItem, const CEconGameAccount *pGameAccount ) const
{
	// Go through our inputs and write them out into attributes
	FOR_EACH_VEC( m_vecComponents, i )
	{
		if( !m_vecComponents[i]->AddRecipeComponentAsAttribute( pItem, pGameAccount ) )
				return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Scan the item for numbered attributes with the passed in base name.
//			Return the attribute of the next available index or NULL if there are
//			none available
//-----------------------------------------------------------------------------
CEconItemAttributeDefinition* CEconTool_ItemDynamicRecipe::CBaseRecipeComponent::GetNextAvailableAttributeWithBaseName( const char* pszBaseAttribName, ComponentAttribVector_t* pAttribVec )
{
	Assert( pAttribVec );
	if( !pAttribVec )
		return NULL;

	CEconItemAttributeDefinition *pAttribDef = NULL;
	int i=1;
	while( pAttribDef == NULL )
	{
		const char* pszAttribName = CFmtStr( "%s %d", pszBaseAttribName, i++ );

		CEconItemAttributeDefinition *pTempAttribDef = GEconItemSchema().GetAttributeDefinitionByName( pszAttribName );

		// Check to see if this attribute we're talking about even exists
		if( !pTempAttribDef )
		{
			return NULL;
		}

		// Check if the vector doesn't have this attribute.  If not, it's available
		if( pAttribVec->Find( pTempAttribDef ) == pAttribVec->InvalidIndex() )
		{
			pAttribDef = pTempAttribDef;
		}
	}

	return pAttribDef;
}
#endif

//-----------------------------------------------------------------------------
bool CEconTool_Xifier::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	const CEconItemDefinition *pSubjectItemDef = pToolSubject->GetItemDefinition();
	if ( !pSubjectItemDef )
		return false;

	// Check to make sure the definition of the item we're trying to apply to has the tags we need to match.
	FOR_EACH_VEC( m_RequiredTags.GetTagsList(), i )
	{
		if ( !pSubjectItemDef->HasEconTag( m_RequiredTags.GetTagsList()[i] ) )
			return false;
	}

	// If this xifier has target restrictions, ensure our subject is one of them
	if ( m_ItemDefTargetRestrictions.Count() > 0 )
	{
		bool bPassed = false;
		FOR_EACH_VEC( m_ItemDefTargetRestrictions, i )
		{
			const CEconItemDefinition *pTargetItemDef = GetItemSchema()->GetItemDefinition( m_ItemDefTargetRestrictions[i] );
			if ( ItemDefMatch( pSubjectItemDef, pTargetItemDef ) )
			{
				bPassed = true;
				break;
			}
		}
		
		if ( bPassed == false )
			return false;
	}

	// if rarity restriction, target needs rarity of this or lower
	if ( m_ItemRarityRestriction != k_unItemRarity_Any )
	{
		uint8 unSubjectRarity = pToolSubject->GetItemDefinition()->GetRarity();
		if ( unSubjectRarity == k_unItemRarity_Any || unSubjectRarity == 0 || unSubjectRarity > m_ItemRarityRestriction )
			return false;

		// needs to be equippable
		static CSchemaAttributeDefHandle pAttribDef_StatModule( "weapon_uses_stattrak_module" );
		if ( !pToolSubject->FindAttribute( pAttribDef_StatModule ) )
			return false;
	}

	// Check if we have a restriction as an attribute
	static CSchemaAttributeDefHandle pAttribDef_ToolTargetItem( "tool target item" );
	float value;
	if ( FindAttribute_UnsafeBitwiseCast<attrib_value_t>( pTool, pAttribDef_ToolTargetItem, &value ) )
	{
		const CEconItemDefinition *pTargetDef =  GetItemSchema()->GetItemDefinition( value );

		// Check for a match (might have NULL here for target definition but that's safe to pass in)
		if ( !ItemDefMatch( pSubjectItemDef, pTargetDef ) )
		{
			return false;
		}
	}

	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

//-----------------------------------------------------------------------------
bool CEconTool_Xifier::ItemDefMatch( const CEconItemDefinition* pTargetItemDef, const CEconItemDefinition* pSubjectItemDef ) const
{
	if ( pTargetItemDef && pSubjectItemDef )
	{
		// Item def match counts
		if ( pTargetItemDef == pSubjectItemDef )
			return true;

		// If these item defs have the same XifierRemapClass then they are allowed to match as well
		if ( pTargetItemDef->GetXifierRemapClass() && *pTargetItemDef->GetXifierRemapClass() 
			&& pSubjectItemDef->GetXifierRemapClass() && *pSubjectItemDef->GetXifierRemapClass() )
		{
			if (BStringsEqual(pSubjectItemDef->GetXifierRemapClass(), pTargetItemDef->GetXifierRemapClass()))
				return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
bool CEconTool_Strangifier::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	// Do not allow for already strange items
	if ( pToolSubject->GetQuality() == AE_STRANGE )
		return false;

	// Go over the attributes of the item, if it has any strange attributes the item is strange and don't apply
	for ( int i = 0; i < GetKillEaterAttrCount(); i++ )
	{
		if ( pToolSubject->FindAttribute( GetKillEaterAttr_Score( i ) ) )
		{
			return false;
		}
	}

	// Default rules
	return CEconTool_Xifier::CanApplyTo( pTool, pToolSubject );
}

//-----------------------------------------------------------------------------
bool CEconTool_KillStreakifier::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	// Make sure the item doesn't already have an effect
	static CSchemaAttributeDefHandle pAttribDef_KillStreakEffect( "killstreak tier" );
	float flEffectIndex = 0.0;
	if ( FindAttribute_UnsafeBitwiseCast<attrib_value_t>( pToolSubject, pAttribDef_KillStreakEffect, &flEffectIndex ) )
		return false;

	// Default rules
	return CEconTool_Xifier::CanApplyTo( pTool, pToolSubject );
}

//-----------------------------------------------------------------------------
bool CEconTool_Festivizer::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	const CEconItemDefinition *pSubjectItemDef = pToolSubject->GetItemDefinition();
	if ( !pSubjectItemDef )
		return false;

	// Make sure the item doesn't already have an effect
	static CSchemaAttributeDefHandle pAttribDef_Festivizer( "is_festivized" );
	if ( FindAttribute( pToolSubject, pAttribDef_Festivizer ) )
		return false;

	// Default rules
	return CEconTool_Xifier::CanApplyTo( pTool, pToolSubject );
}

bool CEconTool_Unusualifier::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	// don't stomp item that's already unusual
	if ( pToolSubject->GetQuality() == AE_UNUSUAL )
		return false;

	// Default rules
	return CEconTool_Xifier::CanApplyTo( pTool, pToolSubject );
}

//-----------------------------------------------------------------------------
bool CEconTool_ItemEaterRecharger::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	const CEconItemDefinition *pSubjectItemDef = pToolSubject->GetItemDefinition();
	if ( !pSubjectItemDef )
		return false;

	// Check to make sure the definition of the item we're trying to apply to has the tags we need to match.
	FOR_EACH_VEC( m_RequiredTags.GetTagsList(), i )
	{
		if ( !pSubjectItemDef->HasEconTag( m_RequiredTags.GetTagsList()[i] ) )
			return false;
	}

	// If this eater has target restrictions, ensure our subject is one of them
	if ( m_ItemDefTargetRestrictions.Count() > 0 )
	{
		bool bPassed = false;
		item_definition_index_t iSubject = pSubjectItemDef->GetDefinitionIndex();
		FOR_EACH_VEC( m_ItemDefTargetRestrictions, i )
		{
			if ( m_ItemDefTargetRestrictions[i] == iSubject )
			{
				bPassed = true;
				break;
			}
		}

		if ( bPassed == false )
			return false;
	}

	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

//-----------------------------------------------------------------------------
int CEconTool_ItemEaterRecharger::GetChargesForItemDefId( item_definition_index_t defIndex ) const
{
	FOR_EACH_VEC( m_ItemDefTargetRestrictions, i )
	{
		if ( m_ItemDefTargetRestrictions[i] == defIndex )
		{
			return m_ItemDefTargetChargeValues[i];
		}
	}
	return 0;
}

bool CEconTool_UpgradeCard::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	const CEconItemDefinition *pSubjectItemDef = pToolSubject->GetItemDefinition();
	if ( !pSubjectItemDef )
		return false;

	// Abort if we're trying to apply to a base item.
	if ( pSubjectItemDef->IsBaseItem() )
		return false;

	// Abort if for some reason we don't know what type of attribute we would attach.
	if ( m_vecAttributes.Count() <= 0 )
		return false;

	// Make sure that none of the attributes we're going to try to apply already exist on the item. We don't
	// allow double-stacking the same attribute partially for balance purposes, but also because the database
	// back-end doesn't support two attributes of the same type on the same item.
	FOR_EACH_VEC( m_vecAttributes, i )
	{
		if ( pToolSubject->FindAttribute( m_vecAttributes[i].m_pAttrDef ) )
			return false;
	}

	// Make sure the item that we're thinking of applying to has enough room to have another card's
	// worth of items attached. We do this in sort of a roundabout way, by having the attributes themselves
	// know whether they came from a card or not.
	CCountUserGeneratedAttributeIterator countIterator;
	pToolSubject->IterateAttributes( &countIterator );

	if ( countIterator.GetCount() >= GetMaxCardUpgradesPerItem() )
		return false;

	// Check to make sure the definition of the item we're trying to apply to has the tags we need
	// to match.
	FOR_EACH_VEC( m_RequiredTags.GetTagsList(), i )
	{
		if ( !pSubjectItemDef->HasEconTag( m_RequiredTags.GetTagsList()[i] ) )
			return false;
	}

	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

bool CEconTool_ClassTransmogrifier::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	const GameItemDefinition_t *pSubjectItemDef = pToolSubject->GetItemDefinition();
	if ( !pSubjectItemDef )
		return false;

	// Abort if we're trying to apply to a base item.
	if ( pSubjectItemDef->IsBaseItem() )
		return false;

	// Abort if we're trying to apply to a Self-Made or Community item
	if ( pToolSubject->GetQuality() == AE_SELFMADE ||
		 pToolSubject->GetQuality() == AE_COMMUNITY )
	{
		return false;
	}

	// Abort if we somehow got here before we know what class we were trying to produce items for.
	if ( m_iClass <= 0 || m_iClass >= LOADOUT_COUNT )
		return false;

	// Check to make sure the definition of the item we're trying to apply to has the tags we need
	// to match.
	FOR_EACH_VEC( m_RequiredTags.GetTagsList(), i )
	{
		if ( !pSubjectItemDef->HasEconTag( m_RequiredTags.GetTagsList()[i] ) )
			return false;
	}

	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

//-----------------------------------------------------------------------------
bool CEconTool_DuckToken::CanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject ) const
{
	Assert( pTool );
	Assert( pToolSubject );

	static CSchemaAttributeDefHandle pAttrDef_DuckBadgeLevel( "duck badge level" );
	uint32 unOldBadgeLevel = 0;
	if ( !FindAttribute( pToolSubject, pAttrDef_DuckBadgeLevel, &unOldBadgeLevel ) )
		return false;

	if ( unOldBadgeLevel >= 5 )
		return false;

	// Default rules
	return IEconTool::CanApplyTo( pTool, pToolSubject );
}

//---------------------------------------------------------------------------------------
// Purpose: given a tool and an item to apply the tool's effects upon, return true if the
//			tool is allowed to affect the subject. This is used on the client for UI and
//			on the GC for actual application validity testing.
//---------------------------------------------------------------------------------------
/* static */ bool CEconSharedToolSupport::ToolCanApplyTo( const IEconItemInterface *pTool, const IEconItemInterface *pToolSubject )
{
	if ( pTool == NULL || pToolSubject == NULL )
		return false;

	const GameItemDefinition_t *pToolDef = pTool->GetItemDefinition();
	if ( pToolDef == NULL )
		return false;

	// If we have a tool that's in escrow it can't be used on anything.
	static CSchemaAttributeDefHandle pAttrib_ToolEscrowUntil( "tool escrow until date" );
	if ( pTool->FindAttribute( pAttrib_ToolEscrowUntil ) )
		return false;

	if ( pToolSubject->IsTemporaryItem() )
		return false;

	// Cannot modify preview items. Should be caught by temporary-item check above.
	Assert( pToolSubject->GetOrigin() != kEconItemOrigin_PreviewItem );

	const GameItemDefinition_t *pToolSubjectDef = pToolSubject->GetItemDefinition();
	if ( pToolSubjectDef == NULL )
		return false;

	if ( !ToolCanApplyToDefinition( pToolDef, pToolSubjectDef ) )
		return false;

	// If we can apply to the definition then we should be known to have valid tool data.
	// If our tool has no tool metadata then we don't allow it to be applied to anything.
	const IEconTool *pEconTool = pToolDef->GetEconTool();
	Assert( pEconTool );

	return pEconTool->CanApplyTo( pTool, pToolSubject );
}

/* static */ bool CEconSharedToolSupport::ToolCanApplyToDefinition( const GameItemDefinition_t *pToolDef, const GameItemDefinition_t *pToolSubjectDef )
{
	if ( !pToolDef || !pToolSubjectDef || !pToolDef->IsTool() )
	{
		// not a tool
		return false;
	}

	// If our tool has no tool metadata then we don't allow it to be applied to anything.
	const IEconTool *pEconTool = pToolDef->GetEconTool();
	if ( !pEconTool )
		return false;

	unsigned int unToolUsageCaps = 0;
	if ( pEconTool->GetCapabilities() )
	{
		for ( unsigned int i = 0; i < NUM_ITEM_CAPS; i++ )
		{
			if ( pEconTool->GetCapabilities() & (1 << i) )
			{
				unToolUsageCaps |= g_CapabilityApplicationMap[i];
			}
		}
	}
	
	// Check for base applicability of this tool to this object.
	if ( (unToolUsageCaps & pToolSubjectDef->GetCapabilities()) == 0 )
		return false;

	// check to see if either the tool or the tool target have usage restriction
	const IEconTool *pSubjectEconTool = pToolSubjectDef->GetEconTool();

	if ( pSubjectEconTool )
	{
		// If this tool can apply to anything then we don't care about the checks below
		// making sure restrictions match.
		const char *pszToolRestriction = BStringsEqual( pEconTool->GetUsageRestriction(), "any" )
									   ? pSubjectEconTool->GetUsageRestriction()
									   : pEconTool->GetUsageRestriction();

		if ( !BStringsEqual( pszToolRestriction, pSubjectEconTool->GetUsageRestriction() ) )
			return false;
	}

	return true;
}

// WARNING
// DO NOT USE THIS CODE IF YOUR TOOL HAS Attribute restrictions like "tool_target_item" or similar restriction attributes
/* static */ bool CEconSharedToolSupport::ToolCanApplyToBaseItem( const GameItemDefinition_t *pToolDef, const GameItemDefinition_t *pToolSubjectDef )
{
	if ( !pToolSubjectDef )
		return false;

	// We are targetting the "Upgradeable" version of a base item and not a base item itself
	if ( pToolSubjectDef->IsBaseItem() || pToolSubjectDef->IsHidden() || pToolSubjectDef->GetQuality() == AE_NORMAL || Q_strnicmp( pToolSubjectDef->GetDefinitionName(), "Upgradeable ", 12 ) )
		return false;

	return ToolCanApplyToDefinition( pToolDef, pToolSubjectDef );
}
