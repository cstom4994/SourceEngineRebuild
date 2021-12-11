#ifndef I_DEFERRED_EXT_H
#define I_DEFERRED_EXT_H

#ifdef CLIENT_DLL
#include "interface.h"
#else
#include "tier1/interface.h"
#endif

#include "../../public/mathlib/vector4d.h"
#include "../../public/mathlib/vmatrix.h"
#include "materialsystem/itexture.h"

struct lightData_Global_t
{
	lightData_Global_t()
	{
		bEnabled = false;
		bShadow = false;
		vecLight.Init(0, 0, 1);

		light.Init();
		ambient.Init();
		sizes.Init();
	};

	Vector4D light, ambient, sizes;
	bool bEnabled;
	bool bShadow;
	Vector vecLight;
};

#include "tier0/memdbgoff.h"

class IDeferredExtension : public IBaseInterface
{
public:

	virtual void CommitCommonData(const Vector& origin, const Vector& fwd, const float& zNear, const float& zFar, const float& curtime, const VMatrix& matView, const VMatrix& matProj, const VMatrix& matFrustum, const VMatrix& matInverseFrustum) = 0;

	virtual void CommitLightData_Global(const lightData_Global_t &data) = 0;
};

#define DEFERRED_EXTENSION_VERSION "DeferredExtensionVersion002"

#if defined(STDSHADER_DX9_DLL_EXPORT) || defined(STDSHADER)

class CDeferredExtension : public IDeferredExtension
{
public:
	CDeferredExtension();
	~CDeferredExtension();

	virtual void CommitCommonData(const Vector& origin, const Vector& fwd, const float& zNear, const float& zFar, const float& curtime,
								  const VMatrix& matView, const VMatrix& matProj, const VMatrix& matFrustum, const VMatrix& matInverseFrustum);
	virtual void CommitZScale(const float& zScale);

	virtual void CommitLightData_Global(const lightData_Global_t& data);
	inline const lightData_Global_t &GetLightData_Global();

	inline float* GetOriginBase();
	inline float* GetForwardBase();
	inline float* GetViewInvBase();
	inline float* GetProjInvBase();
	inline const float& GetZDistNear();
	inline const float& GetZDistFar();
	inline float GetZScale();
	inline float GetCurrentTime();
private:

	lightData_Global_t m_globalLight;

	Vector4D m_vecOrigin;
	Vector4D m_vecForward;
public:
	VMatrix m_matView;
	VMatrix m_matProj;
	VMatrix m_matViewInv;
	VMatrix m_matProjInv;
private:
	float m_flZDists[3];
	float m_flFOV;
	float m_curTime;
	Vector m_vEyePos;
};

const lightData_Global_t &CDeferredExtension::GetLightData_Global()
{
	return m_globalLight;
}


const float& CDeferredExtension::GetZDistNear()
{
	return m_flZDists[0];
}
const float& CDeferredExtension::GetZDistFar()
{
	return m_flZDists[1];
}
float CDeferredExtension::GetZScale()
{
	return m_flZDists[2];
}
float* CDeferredExtension::GetOriginBase()
{
	return m_vecOrigin.Base();
}
float* CDeferredExtension::GetForwardBase()
{
	return m_vecForward.Base();
}
float* CDeferredExtension::GetViewInvBase()
{
	return m_matViewInv.Base();
}
float* CDeferredExtension::GetProjInvBase()
{
	return m_matProjInv.Base();
}
float CDeferredExtension::GetCurrentTime()
{
	return m_curTime;
}

#endif

#ifdef CLIENT_DLL
bool ConnectDeferredExt();
void ShutdownDeferredExt();

extern IDeferredExtension *GetDeferredExt();
#else
extern CDeferredExtension __g_defExt;
FORCEINLINE CDeferredExtension *GetDeferredExt()
{
	return &__g_defExt;
}
#endif

#endif