//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: spawn and think functions for editor-placed lights
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "mathlib/lightdesc.h"
#include "lights_deferred.h"
#include "world.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( light_deferred, CLightDeferred);

BEGIN_DATADESC(CLightDeferred)

	DEFINE_FIELD( m_iCurrentFade, FIELD_CHARACTER),
	DEFINE_FIELD( m_iTargetFade, FIELD_CHARACTER),

	DEFINE_FIELD(m_LightColor, FIELD_VECTOR),
	DEFINE_FIELD(m_LightType, FIELD_INTEGER),
	DEFINE_FIELD(m_Range, FIELD_FLOAT),
	DEFINE_FIELD(m_Falloff, FIELD_FLOAT),
	DEFINE_FIELD(m_Attenuation0, FIELD_FLOAT),
	DEFINE_FIELD(m_Attenuation1, FIELD_FLOAT),
	DEFINE_FIELD(m_Attenuation2, FIELD_FLOAT),
	DEFINE_FIELD(m_Theta, FIELD_FLOAT),
	DEFINE_FIELD(m_Phi, FIELD_FLOAT),

	DEFINE_KEYFIELD( m_iStyle, FIELD_INTEGER, "style" ),
	DEFINE_KEYFIELD( m_iDefaultStyle, FIELD_INTEGER, "defaultstyle" ),
	DEFINE_KEYFIELD( m_iszPattern, FIELD_STRING, "pattern" ),


	// Fuctions
	DEFINE_FUNCTION( FadeThink ),

	// Inputs
	DEFINE_INPUTFUNC( FIELD_STRING, "SetPattern", InputSetPattern ),
	DEFINE_INPUTFUNC( FIELD_STRING, "FadeToPattern", InputFadeToPattern ),
	DEFINE_INPUTFUNC( FIELD_VOID,	"Toggle", InputToggle ),
	DEFINE_INPUTFUNC( FIELD_VOID,	"TurnOn", InputTurnOn ),
	DEFINE_INPUTFUNC( FIELD_VOID,	"TurnOff", InputTurnOff ),

END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CLightDeferred, DT_LightDeferred)
SendPropVector(SENDINFO(m_LightColor)),
SendPropInt(SENDINFO(m_LightType)),
SendPropFloat(SENDINFO(m_Range)),
SendPropFloat(SENDINFO(m_Falloff)),
SendPropFloat(SENDINFO(m_Attenuation0)),
SendPropFloat(SENDINFO(m_Attenuation1)),
SendPropFloat(SENDINFO(m_Attenuation2)),
SendPropFloat(SENDINFO(m_Theta)),
SendPropFloat(SENDINFO(m_Phi)),
END_SEND_TABLE()

extern void UTIL_ColorStringToLinearFloatColor(Vector& color, const char* pString);

//
// Cache user-entity-field values until spawn is called.
//
bool CLightDeferred::KeyValue( const char *szKeyName, const char *szValue )
{
	if (FStrEq(szKeyName, "pitch"))
	{
		QAngle angles = GetAbsAngles();
		angles.x = atof(szValue);
		SetAbsAngles( angles );
	}
	else if (FStrEq(szKeyName, "lighttype"))
	{
		if (atoi(szValue) == 1)
			m_LightType = MATERIAL_LIGHT_SPOT;
		else
			m_LightType = MATERIAL_LIGHT_POINT;
	}
	else if (FStrEq(szKeyName, "_light"))
	{
		Vector tmp;
		UTIL_ColorStringToLinearFloatColor(tmp, szValue);
		m_LightColor = tmp;
	}
	else if (FStrEq(szKeyName, "_inner_cone"))
	{
		m_Theta = DEG2RAD(atof(szValue));
	}
	else if (FStrEq(szKeyName, "_cone"))
	{
		m_Phi = DEG2RAD(atof(szValue));
	}
	else if (FStrEq(szKeyName, "_exponent"))
	{
		m_Falloff = atof(szValue);
	}
	else if (FStrEq(szKeyName, "_constant_attn"))
	{
		m_Attenuation0 = atof(szValue);
	}
	else if (FStrEq(szKeyName, "_linear_attn"))
	{
		m_Attenuation1 = atof(szValue);
	}
	else if (FStrEq(szKeyName, "_quadratic_attn"))
	{
		m_Attenuation2 = atof(szValue);
	}
	else
	{
		return BaseClass::KeyValue( szKeyName, szValue );
	}

	return true;
}

// Light entity
// If targeted, it will toggle between on or off.
void CLightDeferred::Spawn( void )
{
	if (m_iStyle >= 32)
	{
		if ( m_iszPattern == NULL_STRING && m_iDefaultStyle > 0 )
		{
			m_iszPattern = MAKE_STRING(GetDefaultLightstyleString(m_iDefaultStyle));
		}

		if (FBitSet(m_spawnflags, SF_LIGHT_START_OFF))
			engine->LightStyle(m_iStyle, "a");
		else if (m_iszPattern != NULL_STRING)
			engine->LightStyle(m_iStyle, (char *)STRING( m_iszPattern ));
		else
			engine->LightStyle(m_iStyle, "m");
	}
}


void CLightDeferred::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
	if (m_iStyle >= 32)
	{
		if ( !ShouldToggle( useType, !FBitSet(m_spawnflags, SF_LIGHT_START_OFF) ) )
			return;

		Toggle();
	}
}

//-----------------------------------------------------------------------------
// Purpose: Turn the light on
//-----------------------------------------------------------------------------
void CLightDeferred::TurnOn( void )
{
	if ( m_iszPattern != NULL_STRING )
	{
		engine->LightStyle( m_iStyle, (char *) STRING( m_iszPattern ) );
	}
	else
	{
		engine->LightStyle( m_iStyle, "m" );
	}

	CLEARBITS( m_spawnflags, SF_LIGHT_START_OFF );
}

//-----------------------------------------------------------------------------
// Purpose: Turn the light off
//-----------------------------------------------------------------------------
void CLightDeferred::TurnOff( void )
{
	engine->LightStyle( m_iStyle, "a" );
	SETBITS( m_spawnflags, SF_LIGHT_START_OFF );
}

//-----------------------------------------------------------------------------
// Purpose: Toggle the light on/off
//-----------------------------------------------------------------------------
void CLightDeferred::Toggle( void )
{
	//Toggle it
	if ( FBitSet( m_spawnflags, SF_LIGHT_START_OFF ) )
	{
		TurnOn();
	}
	else
	{
		TurnOff();
	}
}

//-----------------------------------------------------------------------------
// Purpose: Handle the "turnon" input handler
// Input  : &inputdata - 
//-----------------------------------------------------------------------------
void CLightDeferred::InputTurnOn( inputdata_t &inputdata )
{
	TurnOn();
}

//-----------------------------------------------------------------------------
// Purpose: Handle the "turnoff" input handler
// Input  : &inputdata - 
//-----------------------------------------------------------------------------
void CLightDeferred::InputTurnOff( inputdata_t &inputdata )
{
	TurnOff();
}

//-----------------------------------------------------------------------------
// Purpose: Handle the "toggle" input handler
// Input  : &inputdata - 
//-----------------------------------------------------------------------------
void CLightDeferred::InputToggle( inputdata_t &inputdata )
{
	Toggle();
}

//-----------------------------------------------------------------------------
// Purpose: Input handler for setting a light pattern
//-----------------------------------------------------------------------------
void CLightDeferred::InputSetPattern( inputdata_t &inputdata )
{
	m_iszPattern = inputdata.value.StringID();
	engine->LightStyle(m_iStyle, (char *)STRING( m_iszPattern ));

	// Light is on if pattern is set
	CLEARBITS(m_spawnflags, SF_LIGHT_START_OFF);
}


//-----------------------------------------------------------------------------
// Purpose: Input handler for fading from first value in old pattern to 
//			first value in new pattern
//-----------------------------------------------------------------------------
void CLightDeferred::InputFadeToPattern( inputdata_t &inputdata )
{
	m_iCurrentFade	= (STRING(m_iszPattern))[0];
	m_iTargetFade	= inputdata.value.String()[0];
	m_iszPattern	= inputdata.value.StringID();
	SetThink(&CLightDeferred::FadeThink);
	SetNextThink( gpGlobals->curtime );

	// Light is on if pattern is set
	CLEARBITS(m_spawnflags, SF_LIGHT_START_OFF);
}


//------------------------------------------------------------------------------
// Purpose : Fade light to new starting pattern value then stop thinking
//------------------------------------------------------------------------------
void CLightDeferred::FadeThink(void)
{
	if (m_iCurrentFade < m_iTargetFade)
	{
		m_iCurrentFade++;
	}
	else if (m_iCurrentFade > m_iTargetFade)
	{
		m_iCurrentFade--;
	}

	// If we're done fading instantiate our light pattern and stop thinking
	if (m_iCurrentFade == m_iTargetFade)
	{
		engine->LightStyle(m_iStyle, (char *)STRING( m_iszPattern ));
		SetNextThink( TICK_NEVER_THINK );
	}
	// Otherwise instantiate our current fade value and keep thinking
	else
	{
		char sCurString[2];
		sCurString[0] = m_iCurrentFade;
		sCurString[1] = 0;
		engine->LightStyle(m_iStyle, sCurString);

		// UNDONE: Consider making this settable war to control fade speed
		SetNextThink( gpGlobals->curtime + 0.1f );
	}
}