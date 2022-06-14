//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
// Utility class for building command buffers into memory
//===========================================================================//

#ifndef COMMANDBUILDER_H
#define COMMANDBUILDER_H

#ifndef COMMANDBUFFER_H
#include "shaderapi/commandbuffer.h"
#endif

#include "BaseVSShader.h"
#include "shaderapi/ishaderapi.h"
#include "../IShaderSystem.h"
#include "../shaderlib/shaderDLL_Global.h"
#include "cpp_shader_constant_register_map.h"

#ifdef _WIN32
#pragma once
#endif

extern ConVar mat_fullbright;

template<int N> class CFixedCommandStorageBuffer
{
public:
	uint8 m_Data[N];

	uint8 *m_pDataOut;
#ifdef DBGFLAG_ASSERT
	size_t m_nNumBytesRemaining;
#endif
	
	FORCEINLINE CFixedCommandStorageBuffer( void )
	{
		m_pDataOut = m_Data;
#ifdef DBGFLAG_ASSERT
		m_nNumBytesRemaining = N;
#endif

	}

	FORCEINLINE void EnsureCapacity( size_t sz )
	{
		Assert( m_nNumBytesRemaining >= sz );
	}

	template<class T> FORCEINLINE void Put( T const &nValue )
	{
		EnsureCapacity( sizeof( T ) );
		*( reinterpret_cast<T *>( m_pDataOut ) ) = nValue;
		m_pDataOut += sizeof( nValue );
#ifdef DBGFLAG_ASSERT
		m_nNumBytesRemaining -= sizeof( nValue );
#endif
	}

	FORCEINLINE void PutInt( int nValue )
	{
		Put( nValue );
	}

	FORCEINLINE void PutFloat( float nValue )
	{
		Put( nValue );
	}

	FORCEINLINE void PutPtr( void * pPtr )
	{
		Put( pPtr );
	}

	FORCEINLINE void PutMemory( const void *pMemory, size_t nBytes )
	{
		EnsureCapacity( nBytes );
		memcpy( m_pDataOut, pMemory, nBytes );
		m_pDataOut += nBytes;
	}

	FORCEINLINE uint8 *Base( void )
	{
		return m_Data;
	}

	FORCEINLINE void Reset( void )
	{
		m_pDataOut = m_Data;
#ifdef DBGFLAG_ASSERT
		m_nNumBytesRemaining = N;
#endif
	}

	FORCEINLINE size_t Size( void ) const
	{
		return m_pDataOut - m_Data;
	}

	FORCEINLINE uint8 *Copy()
	{
		const int size = Size();
		uint8 *tmp = new uint8[size];
		Q_memcpy( tmp, m_Data, size );
		return  tmp;
	}
};

//-----------------------------------------------------------------------------
// Used by SetPixelShaderFlashlightState
//-----------------------------------------------------------------------------
struct CBCmdSetPixelShaderFlashlightState_t
{
	Sampler_t m_LightSampler;
	Sampler_t m_DepthSampler;
	Sampler_t m_ShadowNoiseSampler;
	int m_nColorConstant;
	int m_nAttenConstant;
	int m_nOriginConstant;
	int m_nDepthTweakConstant;
	int m_nScreenScaleConstant;
	int m_nWorldToTextureConstant;
	bool m_bFlashlightNoLambert;
	bool m_bSinglePassFlashlight;
};

template<class S> class CCommandBufferBuilder
{
public:
	S m_Storage;

	FORCEINLINE void End( void )
	{
		m_Storage.PutInt( CBCMD_END );
	}


	FORCEINLINE IMaterialVar *Param( int nVar ) const
	{
		return CBaseShader::s_ppParams[nVar];
	}

	FORCEINLINE void SetPixelShaderConstants( int nFirstConstant, int nConstants )
	{
		m_Storage.PutInt( CBCMD_SET_PIXEL_SHADER_FLOAT_CONST );
		m_Storage.PutInt( nFirstConstant );
		m_Storage.PutInt( nConstants );
	}

	FORCEINLINE void OutputConstantData( float const *pSrcData )
	{
		m_Storage.PutFloat( pSrcData[0] );
		m_Storage.PutFloat( pSrcData[1] );
		m_Storage.PutFloat( pSrcData[2] );
		m_Storage.PutFloat( pSrcData[3] );
	}

	FORCEINLINE void OutputConstantData4( float flVal0, float flVal1, float flVal2, float flVal3 )
	{
		m_Storage.PutFloat( flVal0 );
		m_Storage.PutFloat( flVal1 );
		m_Storage.PutFloat( flVal2 );
		m_Storage.PutFloat( flVal3 );
	}

	FORCEINLINE void SetPixelShaderConstant( int nFirstConstant, float const *pSrcData, int nNumConstantsToSet )
	{
		SetPixelShaderConstants( nFirstConstant, nNumConstantsToSet );
		m_Storage.PutMemory( pSrcData, 4 * sizeof( float ) * nNumConstantsToSet );
	}

	FORCEINLINE void SetPixelShaderConstant( int nFirstConstant, int nVar )
	{
		SetPixelShaderConstant( nFirstConstant, Param( nVar )->GetVecValue() );
	}

	void SetPixelShaderConstantGammaToLinear( int pixelReg, int constantVar )
	{
		float val[4];
		Param(constantVar)->GetVecValue( val, 3 );
		val[0] = val[0] > 1.0f ? val[0] : GammaToLinear( val[0] );
		val[1] = val[1] > 1.0f ? val[1] : GammaToLinear( val[1] );
		val[2] = val[2] > 1.0f ? val[2] : GammaToLinear( val[2] );
		val[3] = 1.0;
		SetPixelShaderConstant( pixelReg, val );
	}

	FORCEINLINE void SetPixelShaderConstant( int nFirstConstant, float const *pSrcData )
	{
		SetPixelShaderConstants( nFirstConstant, 1 );
		OutputConstantData( pSrcData );
	}


	FORCEINLINE void SetPixelShaderConstant1( int nFirstConstant, float flVal0 )
	{
		SetPixelShaderConstant4( nFirstConstant, flVal0, 0, 0, 0 );
	}

	FORCEINLINE void SetPixelShaderConstant2( int nFirstConstant, float flVal0, float flVal1 )
	{
		SetPixelShaderConstant4( nFirstConstant, flVal0, flVal1, 0, 0 );
	}

	FORCEINLINE void SetPixelShaderConstant3( int nFirstConstant, float flVal0, float flVal1, float flVal2 )
	{
		SetPixelShaderConstant4( nFirstConstant, flVal0, flVal1, flVal2, 0 );
	}

	FORCEINLINE void SetPixelShaderConstant4( int nFirstConstant, float flVal0, float flVal1, float flVal2, float flVal3 )
	{
		SetPixelShaderConstants( nFirstConstant, 1 );
		OutputConstantData4( flVal0, flVal1, flVal2, flVal3 );
	}

	FORCEINLINE void SetPixelShaderConstant_W( int pixelReg, int constantVar, float fWValue )
	{
		if ( constantVar != -1 )
		{
			float val[3];
			Param(constantVar)->GetVecValue( val, 3);
			SetPixelShaderConstant4( pixelReg, val[0], val[1], val[2], fWValue );
		}
	}

	FORCEINLINE void SetVertexShaderConstant( int nFirstConstant, float const *pSrcData )
	{
		m_Storage.PutInt( CBCMD_SET_VERTEX_SHADER_FLOAT_CONST );
		m_Storage.PutInt( nFirstConstant );
		m_Storage.PutInt( 1 );
		OutputConstantData( pSrcData );
	}

	FORCEINLINE void SetVertexShaderConstant( int nFirstConstant, float const *pSrcData, int nConsts )
	{
		m_Storage.PutInt( CBCMD_SET_VERTEX_SHADER_FLOAT_CONST );
		m_Storage.PutInt( nFirstConstant );
		m_Storage.PutInt( nConsts );
		m_Storage.PutMemory( pSrcData, 4 * nConsts * sizeof( float ) );
	}


	FORCEINLINE void SetVertexShaderConstant4( int nFirstConstant, float flVal0, float flVal1, float flVal2, float flVal3 )
	{
		m_Storage.PutInt( CBCMD_SET_VERTEX_SHADER_FLOAT_CONST );
		m_Storage.PutInt( nFirstConstant );
		m_Storage.PutInt( 1 );
		m_Storage.PutFloat( flVal0 );
		m_Storage.PutFloat( flVal1 );
		m_Storage.PutFloat( flVal2 );
		m_Storage.PutFloat( flVal3 );
	}

	void SetVertexShaderTextureTransform( int vertexReg, int transformVar )
	{
		Vector4D transformation[2];
		IMaterialVar* pTransformationVar = Param( transformVar );
		if (pTransformationVar && (pTransformationVar->GetType() == MATERIAL_VAR_TYPE_MATRIX))
		{
			const VMatrix &mat = pTransformationVar->GetMatrixValue();
			transformation[0].Init( mat[0][0], mat[0][1], mat[0][2], mat[0][3] );
			transformation[1].Init( mat[1][0], mat[1][1], mat[1][2], mat[1][3] );
		}
		else
		{
			transformation[0].Init( 1.0f, 0.0f, 0.0f, 0.0f );
			transformation[1].Init( 0.0f, 1.0f, 0.0f, 0.0f );
		}
		SetVertexShaderConstant( vertexReg, transformation[0].Base(), 2 ); 
	}


	void SetVertexShaderTextureScaledTransform( int vertexReg, int transformVar, int scaleVar )
	{
		Vector4D transformation[2];
		IMaterialVar* pTransformationVar = Param( transformVar );
		if (pTransformationVar && (pTransformationVar->GetType() == MATERIAL_VAR_TYPE_MATRIX))
		{
			const VMatrix &mat = pTransformationVar->GetMatrixValue();
			transformation[0].Init( mat[0][0], mat[0][1], mat[0][2], mat[0][3] );
			transformation[1].Init( mat[1][0], mat[1][1], mat[1][2], mat[1][3] );
		}
		else
		{
			transformation[0].Init( 1.0f, 0.0f, 0.0f, 0.0f );
			transformation[1].Init( 0.0f, 1.0f, 0.0f, 0.0f );
		}

		Vector2D scale( 1, 1 );
		IMaterialVar* pScaleVar = Param( scaleVar );
		if (pScaleVar)
		{
			if (pScaleVar->GetType() == MATERIAL_VAR_TYPE_VECTOR)
				pScaleVar->GetVecValue( scale.Base(), 2 );
			else if (pScaleVar->IsDefined())
				scale[0] = scale[1] = pScaleVar->GetFloatValue();
		}

		// Apply the scaling
		transformation[0][0] *= scale[0];
		transformation[0][1] *= scale[1];
		transformation[1][0] *= scale[0];
		transformation[1][1] *= scale[1];
		transformation[0][3] *= scale[0];
		transformation[1][3] *= scale[1];
		SetVertexShaderConstant( vertexReg, transformation[0].Base(), 2 ); 
	}

	FORCEINLINE void SetEnvMapTintPixelShaderDynamicState( int pixelReg, int tintVar )
	{
		if( g_pConfig->bShowSpecular && mat_fullbright.GetInt() != 2 )
		{
			SetPixelShaderConstant( pixelReg, Param( tintVar)->GetVecValue() );
		}
		else
		{
			SetPixelShaderConstant4( pixelReg, 0.0, 0.0, 0.0, 0.0 );
		}
	}

	FORCEINLINE void SetEnvMapTintPixelShaderDynamicStateGammaToLinear( int pixelReg, int tintVar, float flAlphaValue = 1.0 )
	{
		if( ( tintVar != -1 ) && g_pConfig->bShowSpecular && mat_fullbright.GetInt() != 2 )
		{
			float color[4];
			color[3] = flAlphaValue;
			Param( tintVar)->GetLinearVecValue( color, 3 );
			SetPixelShaderConstant( pixelReg, color );
		}
		else
		{
			SetPixelShaderConstant4( pixelReg, 0.0, 0.0, 0.0, flAlphaValue );
		}
	}

	FORCEINLINE void StoreEyePosInPixelShaderConstant( int nConst )
	{
		m_Storage.PutInt( CBCMD_STORE_EYE_POS_IN_PSCONST );
		m_Storage.PutInt( nConst );
	}

	FORCEINLINE void CommitPixelShaderLighting( int nConst )
	{
		m_Storage.PutInt( CBCMD_COMMITPIXELSHADERLIGHTING );
		m_Storage.PutInt( nConst );
	}

	FORCEINLINE void SetPixelShaderStateAmbientLightCube( int nConst )
	{
		m_Storage.PutInt( CBCMD_SETPIXELSHADERSTATEAMBIENTLIGHTCUBE );
		m_Storage.PutInt( nConst );
	}

	FORCEINLINE void SetAmbientCubeDynamicStateVertexShader( void )
	{
		m_Storage.PutInt( CBCMD_SETAMBIENTCUBEDYNAMICSTATEVERTEXSHADER );
	}

	FORCEINLINE void SetPixelShaderFogParams( int nReg )
	{
		m_Storage.PutInt( CBCMD_SETPIXELSHADERFOGPARAMS );
		m_Storage.PutInt( nReg );
	}

	FORCEINLINE void BindStandardTexture( Sampler_t nSampler, StandardTextureId_t nTextureId )
	{
		m_Storage.PutInt( CBCMD_BIND_STANDARD_TEXTURE );
		m_Storage.PutInt( nSampler );
		m_Storage.PutInt( nTextureId );
	}


	FORCEINLINE void BindTexture( Sampler_t nSampler, ShaderAPITextureHandle_t hTexture )
	{
		Assert( hTexture != INVALID_SHADERAPI_TEXTURE_HANDLE );
		if ( hTexture != INVALID_SHADERAPI_TEXTURE_HANDLE )
		{
			m_Storage.PutInt( CBCMD_BIND_SHADERAPI_TEXTURE_HANDLE );
			m_Storage.PutInt( nSampler );
			m_Storage.PutInt( hTexture );
		}
	}

	FORCEINLINE void BindTexture( CBaseVSShader *pShader, Sampler_t nSampler, int nTextureVar, int nFrameVar = -1 )
	{
		ShaderAPITextureHandle_t hTexture = pShader->GetShaderAPITextureBindHandle( nTextureVar, nFrameVar );
		BindTexture( nSampler, hTexture );
	}

	FORCEINLINE void BindTexture(Sampler_t nSampler, ITexture* pTexture, int iFrame = 0)
	{
		ShaderAPITextureHandle_t hTexture = GetShaderSystem()->GetShaderAPITextureBindHandle(pTexture, iFrame);
		BindTexture(nSampler, hTexture);
	}

	FORCEINLINE void BindMultiTexture( CBaseVSShader *pShader, Sampler_t nSampler1, Sampler_t nSampler2, int nTextureVar, int nFrameVar )
	{
		ShaderAPITextureHandle_t hTexture = pShader->GetShaderAPITextureBindHandle( nTextureVar, nFrameVar, 0 );
		BindTexture( nSampler1, hTexture );
		hTexture = pShader->GetShaderAPITextureBindHandle( nTextureVar, nFrameVar, 1 );
		BindTexture( nSampler2, hTexture );
	}

	FORCEINLINE void SetPixelShaderIndex( int nIndex )
	{
		m_Storage.PutInt( CBCMD_SET_PSHINDEX );
		m_Storage.PutInt( nIndex );
	}

	FORCEINLINE void SetVertexShaderIndex( int nIndex )
	{
		m_Storage.PutInt( CBCMD_SET_VSHINDEX );
		m_Storage.PutInt( nIndex );
	}

	FORCEINLINE void SetDepthFeatheringPixelShaderConstant( int iConstant, float fDepthBlendScale )
	{
		m_Storage.PutInt( CBCMD_SET_DEPTH_FEATHERING_CONST );
		m_Storage.PutInt( iConstant );
		m_Storage.PutFloat( fDepthBlendScale );
	}

	FORCEINLINE void SetVertexShaderFlashlightState( int iConstant )
	{
		m_Storage.PutInt( CBCMD_SET_VERTEX_SHADER_FLASHLIGHT_STATE );
		m_Storage.PutInt( iConstant );
	}

	FORCEINLINE void SetPixelShaderFlashlightState( const CBCmdSetPixelShaderFlashlightState_t &state )
	{
		m_Storage.PutInt( CBCMD_SET_PIXEL_SHADER_FLASHLIGHT_STATE );
		m_Storage.PutInt( state.m_LightSampler );
		m_Storage.PutInt( state.m_DepthSampler );
		m_Storage.PutInt( state.m_ShadowNoiseSampler );
		m_Storage.PutInt( state.m_nColorConstant );
		m_Storage.PutInt( state.m_nAttenConstant );
		m_Storage.PutInt( state.m_nOriginConstant );
		m_Storage.PutInt( state.m_nDepthTweakConstant );
		m_Storage.PutInt( state.m_nScreenScaleConstant );
		m_Storage.PutInt( state.m_nWorldToTextureConstant );
		m_Storage.PutInt( state.m_bFlashlightNoLambert );
		m_Storage.PutInt( state.m_bSinglePassFlashlight );
	}

	FORCEINLINE void SetFlashLightColorFromState(FlashlightState_t const& state, IShaderDynamicAPI* pShaderAPI, int nPSRegister = 28, bool bFlashlightNoLambert = false)
	{
		// Old code
		//float flToneMapScale = ( pShaderAPI->GetToneMappingScaleLinear() ).x;
		//float flFlashlightScale = 1.0f / flToneMapScale;

		// Fix to old code to keep flashlight from ever getting brighter than 1.0
		//float flToneMapScale = ( pShaderAPI->GetToneMappingScaleLinear() ).x;
		//if ( flToneMapScale < 1.0f )
		//	flToneMapScale = 1.0f;
		//float flFlashlightScale = 1.0f / flToneMapScale;

		// Force flashlight to 25% bright always
		float flFlashlightScale = 0.25f;

		if (!g_pHardwareConfig->GetHDREnabled())
		{
			// Non-HDR path requires 2.0 flashlight
			flFlashlightScale = 2.0f;
		}

		// DX10 requires some hackery due to sRGB/blend ordering change from DX9
		if (g_pHardwareConfig->UsesSRGBCorrectBlending())
		{
			flFlashlightScale *= 2.5f; // Magic number that works well on the NVIDIA 8800
		}

		if (g_pShaderExtension)
		{
			const flashlightData_t* pData = g_pShaderExtension->GetState(state);
			if (pData)
			{
				flFlashlightScale *= pData->m_fBrightnessScale;
			}
		}

		// Generate pixel shader constant
		float const* pFlashlightColor = state.m_Color;
		float vPsConst[4] = { flFlashlightScale * pFlashlightColor[0], flFlashlightScale * pFlashlightColor[1], flFlashlightScale * pFlashlightColor[2], pFlashlightColor[3] };
		vPsConst[3] = bFlashlightNoLambert ? 2.0f : 0.0f; // This will be added to N.L before saturate to force a 1.0 N.L term

		// Red flashlight for testing
		//vPsConst[0] = 0.5f; vPsConst[1] = 0.0f; vPsConst[2] = 0.0f;

		SetPixelShaderConstant(nPSRegister, (float*)vPsConst);
	}

	FORCEINLINE void SetPixelShaderUberLightState( int iEdge0Const, const float* edge0Data, int iEdge1Const, const float* edge1Data, int iEdgeOOWConst, const float* edgeOOWData,
												   int iShearRoundConst, const float* roundConst, int iAABBConst, const float* aabbData, int iWorldToLightConst, const float* worldToLightMatrix )
	{
		SetPixelShaderConstant( iEdge0Const, edge0Data );
		SetPixelShaderConstant( iEdge1Const, edge1Data );
		SetPixelShaderConstant( iEdgeOOWConst, edgeOOWData );
		SetPixelShaderConstant( iShearRoundConst, roundConst );
		SetPixelShaderConstant( iAABBConst, aabbData );
		SetPixelShaderConstant( iWorldToLightConst, worldToLightMatrix, 4 );
	}

	FORCEINLINE bool SetupUberlightFromState(FlashlightState_t const& state)
	{
		if (!g_pShaderExtension)
			return false;

		const flashlightData_t* pData = g_pShaderExtension->GetState(state);
		if (!pData)
			return false;
		const UberlightState_t& uberlightState = pData->uber;

		if (!uberlightState.m_bEnabled)
			return false;

		// Set uberlight shader parameters as function of user controls from UberlightState_t
		const Vector4D vSmoothEdge0(0.0f, uberlightState.m_fCutOn - uberlightState.m_fNearEdge, uberlightState.m_fCutOff, 0.0f);
		const Vector4D vSmoothEdge1(0.0f, uberlightState.m_fCutOn, uberlightState.m_fCutOff + uberlightState.m_fFarEdge, 0.0f);
		const Vector4D vSmoothOneOverW(0.0f, 1.0f / uberlightState.m_fNearEdge, 1.0f / uberlightState.m_fFarEdge, 0.0f);
		const Vector4D vShearRound(uberlightState.m_fShearx, uberlightState.m_fSheary, 2.0f / uberlightState.m_fRoundness, -uberlightState.m_fRoundness / 2.0f);
		const Vector4D vaAbB(uberlightState.m_fWidth, uberlightState.m_fWidth + uberlightState.m_fWedge, uberlightState.m_fHeight, uberlightState.m_fHeight + uberlightState.m_fHedge);

		QAngle angles;
		QuaternionAngles(state.m_quatOrientation, angles);

		// World to Light's View matrix
		matrix3x4_t viewMatrix;
		AngleMatrix(angles, state.m_vecLightOrigin, viewMatrix);
		MatrixInvert(viewMatrix, viewMatrix);
		const VMatrix m(viewMatrix);

		SetPixelShaderUberLightState(PSREG_UBERLIGHT_SMOOTH_EDGE_0, vSmoothEdge0.Base(),
			PSREG_UBERLIGHT_SMOOTH_EDGE_1, vSmoothEdge1.Base(), PSREG_UBERLIGHT_SMOOTH_EDGE_OOW, vSmoothOneOverW.Base(),
			PSREG_UBERLIGHT_SHEAR_ROUND, vShearRound.Base(), PSREG_UBERLIGHT_AABB, vaAbB.Base(),
			PSREG_UBERLIGHT_WORLD_TO_LIGHT, m.Base());
		return true;
	}

	FORCEINLINE void SetVertexShaderNearAndFarZ( int iRegNum )
	{
		m_Storage.PutInt( CBCMD_SET_VERTEX_SHADER_NEARZFARZ_STATE );
		m_Storage.PutInt( iRegNum );
	}

	FORCEINLINE void Goto( uint8 *pCmdBuf )
	{
		m_Storage.PutInt( CBCMD_JUMP );
		m_Storage.PutPtr( pCmdBuf );
	}

	FORCEINLINE void Call( uint8 *pCmdBuf )
	{
		m_Storage.PutInt( CBCMD_JSR );
		m_Storage.PutPtr( pCmdBuf );
	}

	FORCEINLINE void Reset( void )
	{
		m_Storage.Reset();
	}

	FORCEINLINE size_t Size( void ) const
	{
		return m_Storage.Size();
	}

	FORCEINLINE uint8 *Base( void )
	{
		return m_Storage.Base();
	}

	FORCEINLINE uint8 *Copy( void )
	{
		return m_Storage.Copy();
	}
};


#endif // commandbuilder_h
