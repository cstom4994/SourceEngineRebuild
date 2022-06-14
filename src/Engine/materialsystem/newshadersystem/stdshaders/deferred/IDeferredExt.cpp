
#include "IDeferredExt.h"

CDeferredExtension __g_defExt;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CDeferredExtension, IDeferredExtension, DEFERRED_EXTENSION_VERSION, __g_defExt);

CDeferredExtension::CDeferredExtension()
{
}

CDeferredExtension::~CDeferredExtension()
{
}

void CDeferredExtension::CommitLightData_Global(const lightData_Global_t &data)
{
	m_globalLight = data;
}

void CDeferredExtension::CommitCommonData(const Vector& origin,
	const Vector& fwd,
	const float& zNear, const float& zFar,
	const float& curTime,
	const VMatrix& matView,
	const VMatrix& matProj,
	const VMatrix& matViewInv,
	const VMatrix& matProjInv
)
{
	m_vecOrigin = Vector4D(origin.x, origin.y, origin.z, 0.0f);
	m_vecForward = Vector4D(fwd.x, fwd.y, fwd.z, 0.0f);
	m_matViewInv = matViewInv;
	m_matProjInv = matProjInv;
	m_matView = matView;
	m_matProj = matProj;
	m_flZDists[0] = zNear;
	m_flZDists[1] = zFar;
	m_curTime = curTime;
}

void CDeferredExtension::CommitZScale(const float& zFar)
{
	m_flZDists[2] = zFar;
}