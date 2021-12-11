//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"
#include "shareddefs.h"
#include "materialsystem/imesh.h"
#include "materialsystem/imaterial.h"
#include "view.h"
#include "iviewrender.h"
#include "view_shared.h"
#include "texture_group_names.h"
#include "tier0/icommandline.h"
#include "vprof.h"
#include "c_light_manager.h"

#include "c_env_projectedtexture.h"

#include "materialsystem/itexture.h"
#include "view_scene.h"
#include "viewrender.h"
#include "debugoverlay_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

float C_EnvProjectedTexture::m_flVisibleBBoxMinHeight = -FLT_MAX;

extern ConVar mat_slopescaledepthbias_shadowmap;
static ConVar mat_depthbias_shadowmap(	"mat_depthbias_shadowmap", "0.00001", FCVAR_CHEAT  );
static ConVar r_projtex_filtersize( "r_projtex_filtersize", "1.0", 0 );

static ConVar r_volumetrics_enabled("r_volumetrics_enabled", "1", FCVAR_ARCHIVE);

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
IMPLEMENT_CLIENTCLASS_DT( C_EnvProjectedTexture, DT_EnvProjectedTexture, CEnvProjectedTexture )
	RecvPropEHandle( RECVINFO( m_hTargetEntity )	),
	RecvPropBool(	 RECVINFO( m_bState )			),
	RecvPropBool(	 RECVINFO( m_bAlwaysUpdate )	),
	RecvPropFloat(	 RECVINFO( m_flLightFOV )		),
	RecvPropBool(	 RECVINFO( m_bEnableShadows )	),
	RecvPropBool(	 RECVINFO( m_bLightOnlyTarget ) ),
	RecvPropBool(	 RECVINFO( m_bLightWorld )		),
	RecvPropBool(	 RECVINFO( m_bCameraSpace )		),

	RecvPropBool(	RECVINFO( m_bEnableVolumetrics)	),
	RecvPropBool(	RECVINFO( m_bEnableVolumetricsLOD)),
	RecvPropFloat(	RECVINFO( m_flVolumetricsFadeDistance)),
	RecvPropInt(	RECVINFO( m_iVolumetricsQuality)),
	RecvPropFloat(	RECVINFO( m_flVolumetricsQualityBias)),
	RecvPropFloat(	RECVINFO( m_flVolumetricsMultiplier)),

	RecvPropVector(	 RECVINFO( m_LinearFloatLightColor )		),
	RecvPropInt(	 RECVINFO( m_nLinear )	),
	RecvPropInt(	 RECVINFO( m_nQuadratic )	),
	RecvPropInt(	 RECVINFO( m_nConstant )	),

	RecvPropFloat(	 RECVINFO( m_flAmbient )		),
	RecvPropString(  RECVINFO( m_SpotlightTextureName ) ),
	RecvPropInt(	 RECVINFO( m_nSpotlightTextureFrame ) ),
	RecvPropFloat(	 RECVINFO( m_flNearZ )	),
	RecvPropFloat(	 RECVINFO( m_flFarZ )	),
	RecvPropInt(	 RECVINFO( m_nShadowQuality )	),
END_RECV_TABLE()

C_EnvProjectedTexture::C_EnvProjectedTexture( void )
{
	m_LightHandle = CLIENTSHADOW_INVALID_HANDLE;
}

C_EnvProjectedTexture::~C_EnvProjectedTexture( void )
{
	ShutDownLightHandle();
}

void C_EnvProjectedTexture::ShutDownLightHandle( void )
{
	// Clear out the light
	if( m_LightHandle != CLIENTSHADOW_INVALID_HANDLE )
	{
		g_pClientShadowMgr->DestroyFlashlight( m_LightHandle );
		m_LightHandle = CLIENTSHADOW_INVALID_HANDLE;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : updateType - 
//-----------------------------------------------------------------------------
void C_EnvProjectedTexture::OnDataChanged( DataUpdateType_t updateType )
{
	if ( updateType == DATA_UPDATE_CREATED )
	{
		m_SpotlightTexture.Init( m_SpotlightTextureName, TEXTURE_GROUP_OTHER, true );
	}

	m_bForceUpdate = true;
	UpdateLight(false);
	BaseClass::OnDataChanged( updateType );
}

void C_EnvProjectedTexture::UpdateOnRemove()
{
	RemoveVolumetrics();

	BaseClass::UpdateOnRemove();
}

void C_EnvProjectedTexture::UpdateLight(bool bForceUpdate)
{
	VPROF( "C_EnvProjectedTexture::UpdateLight" );
	bool bVisible = true;

	if (bForceUpdate)
	{
		m_bForceUpdate = true;
	}

	if ( !m_bForceUpdate )
	{
		bVisible = IsBBoxVisible();
	}

	if ( m_bState == false || !bVisible )
	{
		ShutDownLightHandle();
		RemoveVolumetrics();
		return;
	}

	if ( m_LightHandle == CLIENTSHADOW_INVALID_HANDLE || m_hTargetEntity != NULL || m_bForceUpdate )
	{
		Vector vForward, vRight, vUp, vPos = GetAbsOrigin();

		if ( m_hTargetEntity != NULL )
		{
			if ( m_bCameraSpace )
			{
				const QAngle& angles = GetLocalAngles();

				C_BasePlayer* pPlayer = C_BasePlayer::GetLocalPlayer();
				if ( pPlayer )
				{
					const QAngle playerAngles = pPlayer->GetAbsAngles();

					Vector vPlayerForward, vPlayerRight, vPlayerUp;
					AngleVectors( playerAngles, &vPlayerForward, &vPlayerRight, &vPlayerUp );

					matrix3x4_t	mRotMatrix;
					AngleMatrix( angles, mRotMatrix );

					VectorITransform( vPlayerForward, mRotMatrix, vForward );
					VectorITransform( vPlayerRight, mRotMatrix, vRight );
					VectorITransform( vPlayerUp, mRotMatrix, vUp );

					float dist = ( m_hTargetEntity->GetAbsOrigin() - GetAbsOrigin() ).Length();
					vPos = m_hTargetEntity->GetAbsOrigin() - vForward * dist;

					VectorNormalize( vForward );
					VectorNormalize( vRight );
					VectorNormalize( vUp );
				}
			}
			else
			{
				// VXP: Fixing targeting
				Vector vecToTarget;
				QAngle vecAngles;
				if ( m_hTargetEntity == NULL )
				{
					vecAngles = GetAbsAngles();
				}
				else
				{
					vecToTarget = m_hTargetEntity->GetAbsOrigin() - GetAbsOrigin();
					VectorAngles( vecToTarget, vecAngles );
				}
				AngleVectors( vecAngles, &vForward, &vRight, &vUp );
			}
		}
		else
		{
			AngleVectors( GetAbsAngles(), &vForward, &vRight, &vUp );
		}

		m_FlashlightState.m_fHorizontalFOVDegrees = m_flLightFOV;
		m_FlashlightState.m_fVerticalFOVDegrees = m_flLightFOV;

		m_FlashlightState.m_vecLightOrigin = vPos;
		BasisToQuaternion( vForward, vRight, vUp, m_FlashlightState.m_quatOrientation );

		// quickly check the proposed light's bbox against the view frustum to determine whether we
		// should bother to create it, if it doesn't exist, or cull it, if it does.
#pragma message( "OPTIMIZATION: this should be made SIMD" )
		// get the half-widths of the near and far planes, 
		// based on the FOV which is in degrees. Remember that
		// on planet Valve, x is forward, y left, and z up. 
		const float tanHalfAngle = tan( m_flLightFOV * ( M_PI / 180.0f ) * 0.5f );
		const float halfWidthNear = tanHalfAngle * m_flNearZ;
		const float halfWidthFar = tanHalfAngle * m_flFarZ;
		// now we can build coordinates in local space: the near rectangle is eg 
		// (0, -halfWidthNear, -halfWidthNear), (0,  halfWidthNear, -halfWidthNear), 
		// (0,  halfWidthNear,  halfWidthNear), (0, -halfWidthNear,  halfWidthNear)

		VectorAligned vNearRect[ 4 ] = {
			VectorAligned( m_flNearZ, -halfWidthNear, -halfWidthNear ), VectorAligned( m_flNearZ,  halfWidthNear, -halfWidthNear ),
			VectorAligned( m_flNearZ,  halfWidthNear,  halfWidthNear ), VectorAligned( m_flNearZ, -halfWidthNear,  halfWidthNear )
		};

		VectorAligned vFarRect[ 4 ] = {
			VectorAligned( m_flFarZ, -halfWidthFar, -halfWidthFar ), VectorAligned( m_flFarZ,  halfWidthFar, -halfWidthFar ),
			VectorAligned( m_flFarZ,  halfWidthFar,  halfWidthFar ), VectorAligned( m_flFarZ, -halfWidthFar,  halfWidthFar )
		};

		matrix3x4_t matOrientation( vForward, -vRight, vUp, vPos );

		enum
		{
			kNEAR = 0,
			kFAR = 1,
		};
		VectorAligned vOutRects[ 2 ][ 4 ];

		for ( int i = 0; i < 4; ++i )
		{
			VectorTransform( vNearRect[ i ].Base(), matOrientation, vOutRects[ 0 ][ i ].Base() );
		}
		for ( int i = 0; i < 4; ++i )
		{
			VectorTransform( vFarRect[ i ].Base(), matOrientation, vOutRects[ 1 ][ i ].Base() );
		}

		// now take the min and max extents for the bbox, and see if it is visible.
		Vector mins = **vOutRects;
		Vector maxs = **vOutRects;
		for ( int i = 1; i < 8; ++i )
		{
			VectorMin( mins, *( *vOutRects + i ), mins );
			VectorMax( maxs, *( *vOutRects + i ), maxs );
		}

#if 0 //for debugging the visibility frustum we just calculated
		NDebugOverlay::Triangle( vOutRects[ 0 ][ 0 ], vOutRects[ 0 ][ 1 ], vOutRects[ 0 ][ 2 ], 255, 0, 0, 100, true, 0.0f ); //first tri
		NDebugOverlay::Triangle( vOutRects[ 0 ][ 2 ], vOutRects[ 0 ][ 1 ], vOutRects[ 0 ][ 0 ], 255, 0, 0, 100, true, 0.0f ); //make it double sided
		NDebugOverlay::Triangle( vOutRects[ 0 ][ 2 ], vOutRects[ 0 ][ 3 ], vOutRects[ 0 ][ 0 ], 255, 0, 0, 100, true, 0.0f ); //second tri
		NDebugOverlay::Triangle( vOutRects[ 0 ][ 0 ], vOutRects[ 0 ][ 3 ], vOutRects[ 0 ][ 2 ], 255, 0, 0, 100, true, 0.0f ); //make it double sided

		NDebugOverlay::Triangle( vOutRects[ 1 ][ 0 ], vOutRects[ 1 ][ 1 ], vOutRects[ 1 ][ 2 ], 0, 0, 255, 100, true, 0.0f ); //first tri
		NDebugOverlay::Triangle( vOutRects[ 1 ][ 2 ], vOutRects[ 1 ][ 1 ], vOutRects[ 1 ][ 0 ], 0, 0, 255, 100, true, 0.0f ); //make it double sided
		NDebugOverlay::Triangle( vOutRects[ 1 ][ 2 ], vOutRects[ 1 ][ 3 ], vOutRects[ 1 ][ 0 ], 0, 0, 255, 100, true, 0.0f ); //second tri
		NDebugOverlay::Triangle( vOutRects[ 1 ][ 0 ], vOutRects[ 1 ][ 3 ], vOutRects[ 1 ][ 2 ], 0, 0, 255, 100, true, 0.0f ); //make it double sided

		NDebugOverlay::Box( vec3_origin, mins, maxs, 0, 255, 0, 100, 0.0f );
#endif

		bVisible = IsBBoxVisible( mins, maxs );
		if ( !bVisible )
		{
			// Spotlight's extents aren't in view
			if ( m_LightHandle != CLIENTSHADOW_INVALID_HANDLE )
			{
				ShutDownLightHandle();
			}

			return;
		}

		/*state.m_fQuadraticAtten = r_projtex_quadratic.GetInt(); //0
		state.m_fLinearAtten = r_projtex_linear.GetInt(); //100
		state.m_fConstantAtten = r_projtex_constant.GetInt(); //0*/

		m_FlashlightState.m_fQuadraticAtten = m_nQuadratic; //0
		m_FlashlightState.m_fLinearAtten = m_nLinear; //100
		m_FlashlightState.m_fConstantAtten = m_nConstant;

		m_FlashlightState.m_Color[ 0 ] = m_LinearFloatLightColor.x;
		m_FlashlightState.m_Color[ 1 ] = m_LinearFloatLightColor.y;
		m_FlashlightState.m_Color[ 2 ] = m_LinearFloatLightColor.z;
		m_FlashlightState.m_Color[ 3 ] = 0.0f; // fixme: need to make ambient work m_flAmbient;
		m_FlashlightState.m_NearZ = m_flNearZ;
		m_FlashlightState.m_FarZ = m_flFarZ;
		//state.m_flShadowSlopeScaleDepthBias = mat_slopescaledepthbias_shadowmap.GetFloat();
		m_FlashlightState.m_flShadowSlopeScaleDepthBias = 4.0f;
		//state.m_flShadowDepthBias = mat_depthbias_shadowmap.GetFloat();
		m_FlashlightState.m_flShadowDepthBias = 0.00001f;
		m_FlashlightState.m_bEnableShadows = m_bEnableShadows;
		//state.m_pSpotlightTexture = materials->FindTexture( m_SpotlightTextureName, TEXTURE_GROUP_OTHER, false );
		m_FlashlightState.m_pSpotlightTexture = m_SpotlightTexture;
		m_FlashlightState.m_nSpotlightTextureFrame = m_nSpotlightTextureFrame;

		m_FlashlightState.m_flShadowAtten = 0.0f; // kind of like a fade out for the shadows
		m_FlashlightState.m_nShadowQuality = m_nShadowQuality; // Allow entity to affect shadow quality

		m_FlashlightState.m_flShadowFilterSize = r_projtex_filtersize.GetFloat();

		if ( m_LightHandle == CLIENTSHADOW_INVALID_HANDLE )
		{
			m_LightHandle = g_pClientShadowMgr->CreateFlashlight(m_FlashlightState);

			if ( m_LightHandle != CLIENTSHADOW_INVALID_HANDLE )
			{
				m_bForceUpdate = false;
			}
		}
		else
		{
			if ( m_hTargetEntity != NULL || m_bForceUpdate == true )
			{
				g_pClientShadowMgr->UpdateFlashlightState( m_LightHandle, m_FlashlightState);
			}

			//g_pClientShadowMgr->UpdateFlashlightState( m_LightHandle, state );
			m_bForceUpdate = false;
		}

		g_pClientShadowMgr->GetFrustumExtents( m_LightHandle, m_vecExtentsMin, m_vecExtentsMax );

		m_vecExtentsMin = m_vecExtentsMin - GetAbsOrigin();
		m_vecExtentsMax = m_vecExtentsMax - GetAbsOrigin();
	}

	if ( m_bLightOnlyTarget )
	{
		g_pClientShadowMgr->SetFlashlightTarget( m_LightHandle, m_hTargetEntity );
	}
	else
	{
		g_pClientShadowMgr->SetFlashlightTarget( m_LightHandle, NULL );
	}

	g_pClientShadowMgr->SetFlashlightLightWorld( m_LightHandle, m_bLightWorld );

	//if ( !m_bForceUpdate )
	//{
		g_pClientShadowMgr->UpdateProjectedTexture( m_LightHandle, true );
	//}

	if (m_bEnableVolumetrics && m_bEnableShadows)
	{
		CViewSetup setup;
		GetShadowViewSetup(setup);

		VMatrix world2View, view2Proj, world2Proj, world2Pixels;
		render->GetMatricesForView(setup, &world2View, &view2Proj, &world2Proj, &world2Pixels);
		VMatrix proj2world;
		MatrixInverseGeneral(world2Proj, proj2world);

		Vector fwd, right, up;
		AngleVectors(setup.angles, &fwd, &right, &up);

		Vector nearFarPlane[8];
		Vector3DMultiplyPositionProjective(proj2world, Vector(-1, -1, 1), nearFarPlane[0]);
		Vector3DMultiplyPositionProjective(proj2world, Vector(1, -1, 1), nearFarPlane[1]);
		Vector3DMultiplyPositionProjective(proj2world, Vector(1, 1, 1), nearFarPlane[2]);
		Vector3DMultiplyPositionProjective(proj2world, Vector(-1, 1, 1), nearFarPlane[3]);

		Vector3DMultiplyPositionProjective(proj2world, Vector(-1, -1, 0), nearFarPlane[4]);
		Vector3DMultiplyPositionProjective(proj2world, Vector(1, -1, 0), nearFarPlane[5]);
		Vector3DMultiplyPositionProjective(proj2world, Vector(1, 1, 0), nearFarPlane[6]);
		Vector3DMultiplyPositionProjective(proj2world, Vector(-1, 1, 0), nearFarPlane[7]);

		m_vecRenderBoundsMin.Init(MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT);
		m_vecRenderBoundsMax.Init(MIN_COORD_FLOAT, MIN_COORD_FLOAT, MIN_COORD_FLOAT);

		for (int i = 0; i < 8; i++)
		{
			m_vecRenderBoundsMin.x = Min(m_vecRenderBoundsMin.x, nearFarPlane[i].x);
			m_vecRenderBoundsMin.y = Min(m_vecRenderBoundsMin.y, nearFarPlane[i].y);
			m_vecRenderBoundsMin.z = Min(m_vecRenderBoundsMin.z, nearFarPlane[i].z);
			m_vecRenderBoundsMax.x = Max(m_vecRenderBoundsMax.x, nearFarPlane[i].x);
			m_vecRenderBoundsMax.y = Max(m_vecRenderBoundsMax.y, nearFarPlane[i].y);
			m_vecRenderBoundsMax.z = Max(m_vecRenderBoundsMax.z, nearFarPlane[i].z);
		}

		UpdateVolumetricsState();
	}
}

void C_EnvProjectedTexture::Simulate( void )
{
	UpdateLight(GetMoveParent() != NULL);

	BaseClass::Simulate();
	//return true;
}

bool C_EnvProjectedTexture::IsBBoxVisible( Vector vecExtentsMin, Vector vecExtentsMax )
{
	// Z position clamped to the min height (but must be less than the max)
	float flVisibleBBoxMinHeight = MIN( vecExtentsMax.z - 1.0f, m_flVisibleBBoxMinHeight );
	vecExtentsMin.z = MAX( vecExtentsMin.z, flVisibleBBoxMinHeight );

	// Check if the bbox is in the view
	return !engine->CullBox( vecExtentsMin, vecExtentsMax );
}


void C_EnvProjectedTexture::UpdateVolumetricsState()
{
	if (!m_bState ||
		!m_bEnableVolumetrics ||
		!r_volumetrics_enabled.GetBool() ||
		m_LightHandle == CLIENTSHADOW_INVALID_HANDLE)
	{
		return;
	}

	ITexture* pDepthTexture = NULL;
	const ShadowHandle_t shadowHandle = g_pClientShadowMgr->GetShadowHandle(m_LightHandle);
	const int iNumActiveDepthTextures = g_pClientShadowMgr->GetNumShadowDepthtextures();
	for (int i = 0; i < iNumActiveDepthTextures; i++)
	{
		if (g_pClientShadowMgr->GetShadowDepthHandle(i) == shadowHandle)
		{
			pDepthTexture = g_pClientShadowMgr->GetShadowDepthTex(i);
			break;
		}
	}

	if (pDepthTexture == NULL)
	{
		return;
	}

	CViewSetup setup;
	GetShadowViewSetup(setup);

	VMatrix world2View, view2Proj, world2Proj, world2Pixels;
	render->GetMatricesForView(setup, &world2View, &view2Proj, &world2Proj, &world2Pixels);

	VMatrix tmp, shadowToUnit;
	MatrixBuildScale(tmp, 1.0f / 2, 1.0f / -2, 1.0f);
	tmp[0][3] = tmp[1][3] = 0.5f;
	MatrixMultiply(tmp, world2Proj, shadowToUnit);

	m_volumelight.angles = setup.angles;
	m_volumelight.origin = setup.origin;
	m_volumelight.depth = pDepthTexture;
	m_volumelight.spotWorldToTex = shadowToUnit;
	m_volumelight.state = &m_FlashlightState;
	m_volumelight.intensity = m_flVolumetricsMultiplier;
	m_volumelight.handle = &m_LightHandle;

	if (GetLightingManager()->GetLightNumber(&m_volumelight) == -1)
	{
		GetLightingManager()->AddLight(&m_volumelight);
	}

	return;
}

void C_EnvProjectedTexture::RemoveVolumetrics()
{
	GetLightingManager()->RemoveLight(&m_volumelight);
}

void C_EnvProjectedTexture::GetShadowViewSetup(CViewSetup& setup)
{
	setup.origin = m_FlashlightState.m_vecLightOrigin;
	QuaternionAngles(m_FlashlightState.m_quatOrientation, setup.angles);
	setup.fov = m_flLightFOV;
	setup.zFar = m_flFarZ;
	setup.zNear = m_flNearZ;
	setup.m_bOrtho = false;
	setup.m_flAspectRatio = 1.0f;
	setup.x = setup.y = 0;
	setup.width = m_FlashlightState.m_pSpotlightTexture ? m_FlashlightState.m_pSpotlightTexture->GetActualWidth() : 512;
	setup.height = m_FlashlightState.m_pSpotlightTexture ? m_FlashlightState.m_pSpotlightTexture->GetActualHeight() : 512;
}