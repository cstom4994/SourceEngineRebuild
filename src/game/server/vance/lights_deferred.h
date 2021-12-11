//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef LIGHTS_H
#define LIGHTS_H
#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CLightDeferred : public CPointEntity
{
public:
	DECLARE_CLASS(CLightDeferred, CPointEntity );

	bool	KeyValue( const char *szKeyName, const char *szValue );
	void	Spawn( void );
	void	FadeThink( void );
	void	Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
	
	void	TurnOn( void );
	void	TurnOff( void );
	void	Toggle( void );

	// Input handlers
	void	InputSetPattern( inputdata_t &inputdata );
	void	InputFadeToPattern( inputdata_t &inputdata );

	void	InputToggle( inputdata_t &inputdata );
	void	InputTurnOn( inputdata_t &inputdata );
	void	InputTurnOff( inputdata_t &inputdata );

	int  UpdateTransmitState() { return SetTransmitState(FL_EDICT_ALWAYS); }
	virtual int	ObjectCaps(void) { return BaseClass::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

private:
	int		m_iStyle;
	int		m_iDefaultStyle;
	string_t m_iszPattern;
	char	m_iCurrentFade;
	char	m_iTargetFade;

	CNetworkVector(m_LightColor);
	CNetworkVar(int, m_LightType);
	CNetworkVar(float, m_Range);
	CNetworkVar(float, m_Falloff);
	CNetworkVar(float, m_Attenuation0);
	CNetworkVar(float, m_Attenuation1);
	CNetworkVar(float, m_Attenuation2);
	CNetworkVar(float, m_Theta);
	CNetworkVar(float, m_Phi);
};

#endif // LIGHTS_H
