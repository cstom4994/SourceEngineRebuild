//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef C_ENVPROJECTED_TEXTURE_H
#define C_ENVPROJECTED_TEXTURE_H
#ifdef _WIN32
#pragma once
#endif

#include "c_baseentity.h"
#include "basetypes.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class C_EnvProjectedTexture : public C_BaseEntity
{
	DECLARE_CLASS( C_EnvProjectedTexture, C_BaseEntity );
public:
	DECLARE_CLIENTCLASS();

	virtual void OnDataChanged( DataUpdateType_t updateType );
	void	ShutDownLightHandle( void );

	virtual void Simulate();

	void	UpdateLight( bool bForceUpdate );

	C_EnvProjectedTexture();
	~C_EnvProjectedTexture();

	static void SetVisibleBBoxMinHeight( float flVisibleBBoxMinHeight ) { m_flVisibleBBoxMinHeight = flVisibleBBoxMinHeight; }
	static float GetVisibleBBoxMinHeight( void ) { return m_flVisibleBBoxMinHeight; }
	static C_EnvProjectedTexture *Create( );

	virtual void UpdateOnRemove();

	virtual bool					IsTransparent() { return false; }
	virtual bool					IsTwoPass() { return false; }

	virtual void GetRenderBoundsWorldspace(Vector& mins, Vector& maxs)
	{
		if (m_bEnableVolumetrics)
		{
			mins = m_vecRenderBoundsMin;
			maxs = m_vecRenderBoundsMax;
		}
		else
		{
			BaseClass::GetRenderBoundsWorldspace(mins, maxs);
		}
	}

	virtual void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		if (m_bEnableVolumetrics)
		{
			mins = m_vecRenderBoundsMin - GetAbsOrigin();
			maxs = m_vecRenderBoundsMax - GetAbsOrigin();
		}
		else
		{
			BaseClass::GetRenderBounds(mins, maxs);
		}
	}

	virtual bool ShouldDraw(void) { return false; }

	virtual bool ShouldReceiveProjectedTextures(int flags) { return false; }

private:
	inline bool IsBBoxVisible( void );
	bool IsBBoxVisible( Vector vecExtentsMin,
						Vector vecExtentsMax );

	void GetShadowViewSetup(CViewSetup& setup);
	void UpdateVolumetricsState();
	void RemoveVolumetrics();

	Vector m_vecRenderBoundsMin, m_vecRenderBoundsMax;
	FlashlightState_t	m_FlashlightState;
	ClientShadowHandle_t m_LightHandle;
	bool m_bForceUpdate;

	EHANDLE	m_hTargetEntity;

	bool		m_bState;
	bool		m_bAlwaysUpdate;
	float		m_flLightFOV;
	bool		m_bEnableShadows;
	bool		m_bLightOnlyTarget;
	bool		m_bLightWorld;
	bool		m_bCameraSpace;

	Vector		m_LinearFloatLightColor;
	int			m_nLinear;
	int			m_nQuadratic;
	int			m_nConstant;

	float		m_flAmbient;
	float		m_flNearZ;
	float		m_flFarZ;
	char		m_SpotlightTextureName[MAX_PATH];
	CTextureReference	m_SpotlightTexture;
	int			m_nSpotlightTextureFrame;
	int			m_nShadowQuality;

	float m_fNearEdge;
	float m_fFarEdge;
	float m_fCutOn;
	float m_fCutOff;
	float m_fShearx;
	float m_fSheary;
	float m_fWidth;
	float m_fWedge;
	float m_fHeight;
	float m_fHedge;
	float m_fRoundness;
	
	Vector	m_vecExtentsMin;
	Vector	m_vecExtentsMax;

	static float m_flVisibleBBoxMinHeight;

	bool m_bEnableVolumetrics;
	bool m_bEnableVolumetricsLOD;
	float m_flVolumetricsFadeDistance;
	int m_iVolumetricsQuality;
	float m_flVolumetricsMultiplier;
	float m_flVolumetricsQualityBias;
	int m_iCurrentVolumetricsSubDiv;
	volume_light_t m_volumelight;
};

bool C_EnvProjectedTexture::IsBBoxVisible( void )
{
	return IsBBoxVisible( GetAbsOrigin() + m_vecExtentsMin, GetAbsOrigin() + m_vecExtentsMax );
}

#endif // C_ENV_PROJECTED_TEXTURE_H