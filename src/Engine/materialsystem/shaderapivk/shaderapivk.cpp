#include "shaderapivk.h"
#include <ICommandLine.h>
#include <glm/gtc/type_ptr.hpp>
#include "meshmgrvk.h"
#include "shaderapi/ishaderutil.h"
#include "shaderapivk_global.h"
#include "shadermanagervk.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define MAX_LIGHTS 128

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
static CShaderAPIVk g_ShaderAPIVk;
CShaderAPIVk *g_pShaderAPI = &g_ShaderAPIVk;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderAPIVk, IShaderAPI, SHADERAPI_INTERFACE_VERSION, g_ShaderAPIVk)

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderAPIVk, IDebugTextureInfo, DEBUG_TEXTURE_INFO_VERSION, g_ShaderAPIVk)

CShaderAPIVk::CShaderAPIVk()
{
    for (int i = 0; i < NUM_MATRIX_MODES; i++)
    {
        m_MatrixStack[i].LoadIdentity();
    }

    m_nDynamicVBSize = DYNAMIC_VERTEX_BUFFER_MEMORY;
}

CShaderAPIVk::~CShaderAPIVk()
{
    if (m_DynamicState.m_pVectorVertexShaderConstant)
    {
        delete[] m_DynamicState.m_pVectorVertexShaderConstant;
        m_DynamicState.m_pVectorVertexShaderConstant = NULL;
    }

    if (m_DynamicState.m_pBooleanVertexShaderConstant)
    {
        delete[] m_DynamicState.m_pBooleanVertexShaderConstant;
        m_DynamicState.m_pBooleanVertexShaderConstant = NULL;
    }

    if (m_DynamicState.m_pIntegerVertexShaderConstant)
    {
        delete[] m_DynamicState.m_pIntegerVertexShaderConstant;
        m_DynamicState.m_pIntegerVertexShaderConstant = NULL;
    }

    if (m_DynamicState.m_pVectorPixelShaderConstant)
    {
        delete[] m_DynamicState.m_pVectorPixelShaderConstant;
        m_DynamicState.m_pVectorPixelShaderConstant = NULL;
    }

    if (m_DynamicState.m_pBooleanPixelShaderConstant)
    {
        delete[] m_DynamicState.m_pBooleanPixelShaderConstant;
        m_DynamicState.m_pBooleanPixelShaderConstant = NULL;
    }

    if (m_DynamicState.m_pIntegerPixelShaderConstant)
    {
        delete[] m_DynamicState.m_pIntegerPixelShaderConstant;
        m_DynamicState.m_pIntegerPixelShaderConstant = NULL;
    }

    if (m_pDebugTextureList)
    {
        m_pDebugTextureList->deleteThis();
        m_pDebugTextureList = NULL;
    }
}

bool CShaderAPIVk::OnDeviceInit()
{
    // AcquireInternalRenderTargets();

    // g_pHardwareConfig->CapsForEdit().m_TextureMemorySize = g_pShaderDeviceMgr->GetVidMemBytes( m_nAdapter );

    // Initialize the shader manager
    g_pShaderManager->Init();

    // Initialize the shader shadow
    // g_pShaderShadow->Init();

    // Initialize the mesh manager
    g_pMeshMgr->Init();

    bool bToolsMode = CommandLine()->CheckParm("-tools") != NULL;

    // Use fat vertices when running in tools
    g_pMeshMgr->UseFatVertices(bToolsMode);

    // Initialize the transition table.
    // m_TransitionTable.Init();

    // Initialize the render state
    InitRenderState();

    // Clear the z and color buffers
    ClearBuffers(true, true, true, -1, -1);

    // AllocFrameSyncObjects();
    // AllocNonInteractiveRefreshObjects();

    return true;
}

void CShaderAPIVk::OnDeviceShutdown()
{
    if (g_pShaderDevice->IsDeactivated())
        return;

    // Deallocate all textures
    // DeleteAllTextures();

    // Release render targets
    // ReleaseInternalRenderTargets();

    // Free objects that are used for frame syncing.
    // FreeFrameSyncObjects();
    // FreeNonInteractiveRefreshObjects();

    for (int i = 0; i < NUM_MATRIX_MODES; ++i)
    {
        m_MatrixStack[i] = MatrixStack();
    }

    // Shutdown the transition table.
    // m_TransitionTable.Shutdown();

    g_pMeshMgr->Shutdown();

    g_pShaderManager->Shutdown();

    // ReleaseAllVertexDecl( );
}

void CShaderAPIVk::GetMaxToRender(IMesh *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices)
{
    g_pMeshMgr->GetMaxToRender(pMesh, bMaxUntilFlush, pMaxVerts, pMaxIndices);
}

int CShaderAPIVk::GetMaxVerticesToRender(IMaterial *pMaterial) { return g_pMeshMgr->GetMaxVerticesToRender(pMaterial); }

int CShaderAPIVk::GetMaxIndicesToRender() { return g_pMeshMgr->GetMaxIndicesToRender(); }

void CShaderAPIVk::SetStencilEnable(bool onoff) {}

void CShaderAPIVk::SetStencilFailOperation(StencilOperation_t op) {}

void CShaderAPIVk::SetStencilZFailOperation(StencilOperation_t op) {}

void CShaderAPIVk::SetStencilPassOperation(StencilOperation_t op) {}

void CShaderAPIVk::SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) {}

void CShaderAPIVk::SetStencilReferenceValue(int ref) {}

void CShaderAPIVk::SetStencilTestMask(uint32 msk) {}

void CShaderAPIVk::SetStencilWriteMask(uint32 msk) {}

void CShaderAPIVk::ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) {}

void CShaderAPIVk::DisableAllLocalLights() {}

int CShaderAPIVk::CompareSnapshots(StateSnapshot_t snapshot0, StateSnapshot_t snapshot1) { return 0; }

IMesh *CShaderAPIVk::GetFlexMesh()
{
    return g_pMeshMgr->GetFlexMesh();
}

void CShaderAPIVk::SetFlashlightStateEx(const FlashlightState_t &state, const VMatrix &worldToTexture, ITexture *pFlashlightDepthTexture) {}

bool CShaderAPIVk::SupportsMSAAMode(int nMSAAMode) { return false; }

bool CShaderAPIVk::OwnGPUResources(bool bEnable) { return false; }

void CShaderAPIVk::GetFogDistances(float *fStart, float *fEnd, float *fFogZ) {}

void CShaderAPIVk::BeginPIXEvent(unsigned long color, const char *szName) {}

void CShaderAPIVk::EndPIXEvent() {}

void CShaderAPIVk::SetPIXMarker(unsigned long color, const char *szName) {}

void CShaderAPIVk::EnableAlphaToCoverage() {}

void CShaderAPIVk::DisableAlphaToCoverage() {}

void CShaderAPIVk::ComputeVertexDescription(unsigned char *pBuffer, VertexFormat_t vertexFormat, MeshDesc_t &desc) const
{
    g_pMeshMgr->ComputeVertexDescription(pBuffer, vertexFormat, desc);
}

bool CShaderAPIVk::SupportsShadowDepthTextures(void) { return false; }

void CShaderAPIVk::SetDisallowAccess(bool) {}

void CShaderAPIVk::EnableShaderShaderMutex(bool) {}

void CShaderAPIVk::ShaderLock()
{
    // no-op
}

void CShaderAPIVk::ShaderUnlock()
{
    // no-op
}

ImageFormat CShaderAPIVk::GetShadowDepthTextureFormat(void) { return ImageFormat(); }

bool CShaderAPIVk::SupportsFetch4(void) { return false; }

void CShaderAPIVk::SetShadowDepthBiasFactors(float fShadowSlopeScaleDepthBias, float fShadowDepthBias) {}

void CShaderAPIVk::BindVertexBuffer(int nStreamID, IVertexBuffer *pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount,
                                    VertexFormat_t fmt, int nRepetitions)
{
    g_pMeshMgr->BindVertexBuffer(nStreamID, pVertexBuffer, nOffsetInBytes, nFirstVertex, nVertexCount, fmt, nRepetitions);
}

void CShaderAPIVk::BindIndexBuffer(IIndexBuffer *pIndexBuffer, int nOffsetInBytes)
{
    g_pMeshMgr->BindIndexBuffer(pIndexBuffer, nOffsetInBytes);
}

void CShaderAPIVk::Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount)
{
    // VK_TODO
}

void CShaderAPIVk::PerformFullScreenStencilOperation(void) {}

void CShaderAPIVk::SetScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor) {}

bool CShaderAPIVk::SupportsCSAAMode(int nNumSamples, int nQualityLevel) { return false; }

void CShaderAPIVk::InvalidateDelayedShaderConstants(void) {}

float CShaderAPIVk::GammaToLinear_HardwareSpecific(float fGamma) const { return 0.0f; }

float CShaderAPIVk::LinearToGamma_HardwareSpecific(float fLinear) const { return 0.0f; }

void CShaderAPIVk::SetLinearToGammaConversionTextures(ShaderAPITextureHandle_t hSRGBWriteEnabledTexture,
                                                      ShaderAPITextureHandle_t hIdentityTexture)
{
}

ImageFormat CShaderAPIVk::GetNullTextureFormat(void) { return ImageFormat(); }

void CShaderAPIVk::BindVertexTexture(VertexTextureSampler_t nSampler, ShaderAPITextureHandle_t textureHandle) {}

void CShaderAPIVk::EnableHWMorphing(bool bEnable) {}

void CShaderAPIVk::SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t *pWeights) {}

void CShaderAPIVk::FogMaxDensity(float flMaxDensity) {}

void CShaderAPIVk::CreateTextures(ShaderAPITextureHandle_t *pHandles, int count, int width, int height, int depth,
                                  ImageFormat dstImageFormat, int numMipLevels, int numCopies, int flags, const char *pDebugName,
                                  const char *pTextureGroupName)
{
    for (int k = 0; k < count; ++k)
        pHandles[k] = 0;
}

void CShaderAPIVk::AcquireThreadOwnership() {}

void CShaderAPIVk::ReleaseThreadOwnership() {}

bool CShaderAPIVk::SupportsNormalMapCompression() const { return false; }

void CShaderAPIVk::EnableBuffer2FramesAhead(bool bEnable) {}

void CShaderAPIVk::SetDepthFeatheringPixelShaderConstant(int iConstant, float fDepthBlendScale) {}

void CShaderAPIVk::PrintfVA(char *fmt, va_list vargs) {}

void CShaderAPIVk::Printf(PRINTF_FORMAT_STRING const char *fmt, ...) {}

float CShaderAPIVk::Knob(char *knobname, float *setvalue) { return 0.0f; }

void CShaderAPIVk::OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable) {}

void CShaderAPIVk::OverrideColorWriteEnable(bool bOverrideEnable, bool bColorWriteEnable) {}

void CShaderAPIVk::ClearBuffersObeyStencilEx(bool bClearColor, bool bClearAlpha, bool bClearDepth) {}

void CShaderAPIVk::CopyRenderTargetToScratchTexture(ShaderAPITextureHandle_t srcRt, ShaderAPITextureHandle_t dstTex, Rect_t *pSrcRect,
                                                    Rect_t *pDstRect)
{
}

void CShaderAPIVk::LockRect(void **pOutBits, int *pOutPitch, ShaderAPITextureHandle_t texHandle, int mipmap, int x, int y, int w, int h,
                            bool bWrite, bool bRead)
{
}

void CShaderAPIVk::UnlockRect(ShaderAPITextureHandle_t texHandle, int mipmap) {}

void CShaderAPIVk::GetLightmapDimensions(int *w, int *h) { ShaderUtil()->GetLightmapDimensions(w, h); }

MaterialFogMode_t CShaderAPIVk::GetSceneFogMode() { return MATERIAL_FOG_NONE; }

void CShaderAPIVk::MatrixMode(MaterialMatrixMode_t matrixMode)
{
    // NOTE!!!!!!
    // The only time that m_MatrixMode is used is for texture matrices.  Do not use
    // it for anything else unless you change this code!
    if (matrixMode >= MATERIAL_TEXTURE0 && matrixMode <= MATERIAL_TEXTURE7)
    {
        m_MatrixMode = (matrixMode - MATERIAL_TEXTURE0 + 16 /*+ D3DTS_TEXTURE0*/);
    }
    else
    {
        m_MatrixMode = -1;
    }

    m_CurrStack = matrixMode;
}

void CShaderAPIVk::PushMatrix() {}

void CShaderAPIVk::PopMatrix() {}

void CShaderAPIVk::LoadMatrix(float *m)
{
    bool isIdentity = true;
    for (int i = 0; i < 16; i++)
    {
        float offset = 0.0f;
        if (i % 5 == 0)
        {
            offset = -1.0f;
        }

        if (fabs(m[i] + offset) >= 1e-3)
        {
            isIdentity = false;
            break;
        }
    }

    if (isIdentity)
    {
        LoadIdentity();
        return;
    }

    if (MatrixIsChanging())
    {
        glm::mat4x4 mat = glm::make_mat4x4(m);
        m_MatrixStack[m_CurrStack].LoadMatrix(mat);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::GetMatrix(MaterialMatrixMode_t matrixMode, float *dst)
{
    memcpy(dst, glm::value_ptr(GetTransform(matrixMode)), sizeof(float) * 16);
}

void CShaderAPIVk::LoadIdentity()
{
    if (MatrixIsChanging(TRANSFORM_IS_IDENTITY))
    {
        m_MatrixStack[m_CurrStack].LoadIdentity();
        UpdateMatrixTransform(TRANSFORM_IS_IDENTITY);
    }
}

void CShaderAPIVk::LoadCameraToWorld()
{
    if (MatrixIsChanging(TRANSFORM_IS_CAMERA_TO_WORLD))
    {
        glm::mat4x4 inv = glm::inverse(GetTransform(MATERIAL_VIEW));

        // Kill translation
        inv[3][0] = inv[3][1] = inv[3][2] = 0.0f;

        m_MatrixStack[m_CurrStack].LoadMatrix(inv);
        UpdateMatrixTransform(TRANSFORM_IS_CAMERA_TO_WORLD);
    }
}

void CShaderAPIVk::Ortho(double left, double right, double bottom, double top, double zNear, double zFar)
{
    if (MatrixIsChanging())
    {
        // FIXME: This is being used incorrectly! Should read:
        // D3DXMatrixOrthoOffCenterRH( &matrix, left, right, bottom, top, zNear, zFar );
        // Which is certainly why we need these extra -1 scales in y. Bleah

        // NOTE: The camera can be imagined as the following diagram:
        //		/z
        //	   /
        //	  /____ x	Z is going into the screen
        //	  |
        //	  |
        //	  |y
        //
        // (0,0,z) represents the upper-left corner of the screen.
        // Our projection transform needs to transform from this space to a LH coordinate
        // system that looks thusly:
        //
        //	y|  /z
        //	 | /
        //	 |/____ x	Z is going into the screen
        //
        // Where x,y lies between -1 and 1, and z lies from 0 to 1
        // This is because the viewport transformation from projection space to pixels
        // introduces a -1 scale in the y coordinates
        //		D3DXMatrixOrthoOffCenterLH( &matrix, left, right, bottom, top, zNear, zFar );

        glm::mat4x4 matrix = glm::orthoRH(left, right, top, bottom, zNear, zFar);
        m_MatrixStack[m_CurrStack].MultMatrixLocal(matrix);
        Assert(m_CurrStack == MATERIAL_PROJECTION);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::PerspectiveX(double fovx, double aspect, double zNear, double zFar)
{
    if (MatrixIsChanging())
    {
        float width = 2 * zNear * tan(fovx * M_PI / 360.0);
        float height = width / aspect;
        Assert(m_CurrStack == MATERIAL_PROJECTION);
        glm::mat4x4 rh = glm::perspectiveFovRH(glm::radians((float)fovx), width, height, (float)zNear, (float)zFar);
        m_MatrixStack[m_CurrStack].MultMatrixLocal(rh);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::PerspectiveOffCenterX(double fovx, double aspect, double zNear, double zFar, double bottom, double top, double left,
                                         double right)
{
    PerspectiveX(fovx, aspect, zNear, zFar);
    // VK_TODO
    /*
    if (MatrixIsChanging())
    {
        float width = 2 * zNear * tan( fovx * M_PI / 360.0 );
        float height = width / aspect;

        // bottom, top, left, right are 0..1 so convert to -1..1
        float flFrontPlaneLeft   = -(width/2.0f)  * (1.0f - left)   + left   * (width/2.0f);
        float flFrontPlaneRight  = -(width/2.0f)  * (1.0f - right)  + right  * (width/2.0f);
        float flFrontPlaneBottom = -(height/2.0f) * (1.0f - bottom) + bottom * (height/2.0f);
        float flFrontPlaneTop    = -(height/2.0f) * (1.0f - top)    + top    * (height/2.0f);

        Assert( m_CurrStack == MATERIAL_PROJECTION );
        D3DXMATRIX rh;
        D3DXMatrixPerspectiveOffCenterRH( &rh, flFrontPlaneLeft, flFrontPlaneRight, flFrontPlaneBottom, flFrontPlaneTop, zNear, zFar );
        m_pMatrixStack[m_CurrStack]->MultMatrixLocal(&rh);
        UpdateMatrixTransform();
    }
    */
}

void CShaderAPIVk::PickMatrix(int x, int y, int width, int height)
{
    // VK_TODO
}

void CShaderAPIVk::MultMatrix(float *m)
{
    if (MatrixIsChanging())
    {
        m_MatrixStack[m_CurrStack].MultMatrix(glm::make_mat4x4(m));
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::MultMatrixLocal(float *m)
{
    if (MatrixIsChanging())
    {
        m_MatrixStack[m_CurrStack].MultMatrixLocal(glm::make_mat4x4(m));
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::Rotate(float angle, float x, float y, float z)
{
    if (MatrixIsChanging())
    {
        glm::vec3 axis = glm::vec3(x, y, z);
        m_MatrixStack[m_CurrStack].RotateAxisLocal(axis, M_PI * angle / 180.0f);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::Translate(float x, float y, float z)
{
    if (MatrixIsChanging())
    {
        glm::vec3 translation = glm::vec3(x, y, z);
        m_MatrixStack[m_CurrStack].TranslateLocal(translation);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::Scale(float x, float y, float z)
{
    if (MatrixIsChanging())
    {
        glm::vec3 scale = glm::vec3(x, y, z);
        m_MatrixStack[m_CurrStack].ScaleLocal(scale);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::ScaleXY(float x, float y)
{
    if (MatrixIsChanging())
    {
        glm::vec3 scale = glm::vec3(x, y, 1.0f);
        m_MatrixStack[m_CurrStack].ScaleLocal(scale);
        UpdateMatrixTransform();
    }
}

void CShaderAPIVk::Color3f(float r, float g, float b) {}

void CShaderAPIVk::Color3fv(float const *pColor) {}

void CShaderAPIVk::Color4f(float r, float g, float b, float a) {}

void CShaderAPIVk::Color4fv(float const *pColor) {}

void CShaderAPIVk::Color3ub(unsigned char r, unsigned char g, unsigned char b) {}

void CShaderAPIVk::Color3ubv(unsigned char const *pColor) {}

void CShaderAPIVk::Color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}

void CShaderAPIVk::Color4ubv(unsigned char const *pColor) {}

void CShaderAPIVk::SetVertexShaderConstant(int var, float const *pVec, int numConst, bool bForce) {}

void CShaderAPIVk::SetPixelShaderConstant(int var, float const *pVec, int numConst, bool bForce) {}

int CShaderAPIVk::GetCurrentNumBones() const { return 0; }

int CShaderAPIVk::GetCurrentLightCombo() const { return 0; }

MaterialFogMode_t CShaderAPIVk::GetCurrentFogType() const { return MATERIAL_FOG_NONE; }

//-----------------------------------------------------------------------------
// the current camera position in world space.
//-----------------------------------------------------------------------------
void CShaderAPIVk::GetWorldSpaceCameraPosition(float *pPos) const { memcpy(pPos, m_WorldSpaceCameraPosition.Base(), sizeof(float[3])); }

void CShaderAPIVk::CacheWorldSpaceCameraPosition()
{
    glm::mat4x4 view = GetTransform(MATERIAL_VIEW);
    m_WorldSpaceCameraPosition[0] = -(view[3][0] * view[0][0] + view[3][1] * view[0][1] + view[3][2] * view[0][2]);
    m_WorldSpaceCameraPosition[1] = -(view[3][0] * view[1][0] + view[3][1] * view[1][1] + view[3][2] * view[1][2]);
    m_WorldSpaceCameraPosition[2] = -(view[3][0] * view[2][0] + view[3][1] * view[2][1] + view[3][2] * view[2][2]);
    m_WorldSpaceCameraPosition[3] = 1.0f;

    // Protect against zero, as some pixel shaders will divide by this in CalcWaterFogAlpha() in common_ps_fxc.h
    if (fabs(m_WorldSpaceCameraPosition[2]) <= 0.00001f)
    {
        m_WorldSpaceCameraPosition[2] = 0.01f;
    }
}

//-----------------------------------------------------------------------------
// Computes a matrix which includes the poly offset given an initial projection matrix
//-----------------------------------------------------------------------------
void CShaderAPIVk::ComputePolyOffsetMatrix(const glm::mat4x4 &matProjection, glm::mat4x4 &matProjectionOffset)
{
    // We never need to do this on hardware that can handle zbias
    if (g_pHardwareConfig->Caps().m_ZBiasAndSlopeScaledDepthBiasSupported)
        return;

    float offsetVal = -1.0f * (m_DesiredState.m_Viewport.maxDepth - m_DesiredState.m_Viewport.minDepth) / 16384.0f;

    glm::mat4x4 offset;
    glm::translate(offset, glm::vec3(0.0f, 0.0f, offsetVal));
    matProjectionOffset = matProjection * offset;
}

//-----------------------------------------------------------------------------
// Caches off the poly-offset projection matrix
//-----------------------------------------------------------------------------
void CShaderAPIVk::CachePolyOffsetProjectionMatrix()
{
    ComputePolyOffsetMatrix(GetTransform(MATERIAL_PROJECTION), m_CachedPolyOffsetProjectionMatrix);
}

glm::mat4x4 CShaderAPIVk::GetProjectionMatrix() { return m_CachedPolyOffsetProjectionMatrix; }

//-----------------------------------------------------------------------------
// Performs a flush on the matrix state	if necessary
//-----------------------------------------------------------------------------
bool CShaderAPIVk::MatrixIsChanging(TransformType_t type)
{
    if (g_pShaderDevice->IsDeactivated())
    {
        return false;
    }

    // early out if the transform is already one of our standard types
    if ((type != TRANSFORM_IS_GENERAL) && (type == m_DynamicState.m_TransformType[m_CurrStack]))
        return false;

    // Only flush state if we're changing something other than a texture transform
    int textureMatrix = m_CurrStack - MATERIAL_TEXTURE0;
    if ((textureMatrix < 0) || (textureMatrix >= NUM_TEXTURE_TRANSFORMS))
        FlushBufferedPrimitivesInternal();

    return true;
}

//-----------------------------------------------------------------------------
// Mark all user clip planes as being dirty
//-----------------------------------------------------------------------------
void CShaderAPIVk::MarkAllUserClipPlanesDirty()
{
    m_DynamicState.m_UserClipPlaneChanged |= (1 << g_pHardwareConfig->MaxUserClipPlanes()) - 1;
    m_DynamicState.m_bFastClipPlaneChanged = true;
}

#ifdef TF
void CShaderAPIVk::TexLodClamp(int finest) {}

void CShaderAPIVk::TexLodBias(float bias) {}

void CShaderAPIVk::CopyTextureToTexture(ShaderAPITextureHandle_t srcTex, ShaderAPITextureHandle_t dstTex) {}
#endif

void CShaderAPIVk::SetTextureTransformDimension(TextureStage_t textureStage, int dimension, bool projected) {}

void CShaderAPIVk::DisableTextureTransform(TextureStage_t textureStage) {}

void CShaderAPIVk::SetBumpEnvMatrix(TextureStage_t textureStage, float m00, float m01, float m10, float m11) {}

//-----------------------------------------------------------------------------
// Sets the actual matrix state
//-----------------------------------------------------------------------------
void CShaderAPIVk::UpdateMatrixTransform(TransformType_t type)
{
    int textureMatrix = m_CurrStack - MATERIAL_TEXTURE0;
    if ((textureMatrix >= 0) && (textureMatrix < NUM_TEXTURE_TRANSFORMS))
    {
        // NOTE: Flush shouldn't happen here because we
        // expect that texture transforms will be set within the shader

        // FIXME: We only want to use D3DTTFF_COUNT3 for cubemaps
        // D3DTFF_COUNT2 is used for non-cubemaps. Of course, if there's
        // no performance penalty for COUNT3, we should just use that.
        /*
         * VK_TODO
        D3DTEXTURETRANSFORMFLAGS transformFlags;
        transformFlags = (type == TRANSFORM_IS_IDENTITY) ? D3DTTFF_DISABLE : D3DTTFF_COUNT3;

        if (TextureStage(textureMatrix).m_TextureTransformFlags != transformFlags )
        {
            SetTextureStageState( textureMatrix, D3DTSS_TEXTURETRANSFORMFLAGS, transformFlags );
            TextureStage(textureMatrix).m_TextureTransformFlags = transformFlags;
        }
        */
    }

    m_DynamicState.m_TransformType[m_CurrStack] = type;
    m_DynamicState.m_TransformChanged[m_CurrStack] = STATE_CHANGED;

    if (m_CurrStack == MATERIAL_VIEW)
    {
        CacheWorldSpaceCameraPosition();
    }

    if (m_CurrStack == MATERIAL_PROJECTION)
    {
        CachePolyOffsetProjectionMatrix();
    }

    // Any time the view or projection matrix changes, the user clip planes need recomputing....
    // Assuming we're not overriding the user clip transform
    if ((m_CurrStack == MATERIAL_PROJECTION) || ((m_CurrStack == MATERIAL_VIEW) && (!m_DynamicState.m_bUserClipTransformOverride)))
    {
        MarkAllUserClipPlanesDirty();
    }

    // Set the state if it's a texture transform
    if ((m_CurrStack >= MATERIAL_TEXTURE0) && (m_CurrStack <= MATERIAL_TEXTURE7))
    {
        // VK_TODO
        // SetTransform(m_MatrixMode, &GetTransform(m_CurrStack));
    }
}

void CShaderAPIVk::SetVertexShaderIndex(int vshIndex) { g_pShaderManager->SetVertexShaderIndex(vshIndex); }

void CShaderAPIVk::SetPixelShaderIndex(int pshIndex) { g_pShaderManager->SetPixelShaderIndex(pshIndex); }

void CShaderAPIVk::GetBackBufferDimensions(int &width, int &height) const { g_pShaderDevice->GetBackBufferDimensions(width, height); }

int CShaderAPIVk::GetMaxLights() const { return MAX_LIGHTS; }

const LightDesc_t &CShaderAPIVk::GetLight(int lightNum) const
{
    static LightDesc_t light;
    return light;
}

void CShaderAPIVk::SetPixelShaderFogParams(int reg) {}

void CShaderAPIVk::SetVertexShaderStateAmbientLightCube() {}

void CShaderAPIVk::SetPixelShaderStateAmbientLightCube(int pshReg, bool bForceToBlack) {}

void CShaderAPIVk::CommitPixelShaderLighting(int pshReg) {}

CMeshBuilder *CShaderAPIVk::GetVertexModifyBuilder() { return 0; }

bool CShaderAPIVk::InFlashlightMode() const { return ShaderUtil()->InFlashlightMode(); }

const FlashlightState_t &CShaderAPIVk::GetFlashlightState(VMatrix &worldToTexture) const { return *new FlashlightState_t; }

bool CShaderAPIVk::InEditorMode() const { return ShaderUtil()->InEditorMode(); }

MorphFormat_t CShaderAPIVk::GetBoundMorphFormat() { return ShaderUtil()->GetBoundMorphFormat(); }

//-----------------------------------------------------------------------------
// Compute fill rate
//-----------------------------------------------------------------------------
void CShaderAPIVk::ComputeFillRate()
{
    static unsigned char *pBuf = 0;

    int width, height;
    g_pShaderDevice->GetWindowSize(width, height);
    // Snapshot; look at total # pixels drawn...
    if (!pBuf)
    {
        int memSize = ShaderUtil()->GetMemRequired(width, height, 1, IMAGE_FORMAT_RGB888, false) + 4;

        pBuf = (unsigned char *)malloc(memSize);
    }

    ReadPixels(0, 0, width, height, pBuf, IMAGE_FORMAT_RGB888);

    int mask = 0xFF;
    int count = 0;
    unsigned char *pRead = pBuf;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int val = *(int *)pRead;
            count += (val & mask);
            pRead += 3;
        }
    }
}

// We hit somefin in selection mode
void CShaderAPIVk::RegisterSelectionHit(float minz, float maxz)
{
    if (minz < 0)
        minz = 0;
    if (maxz > 1)
        maxz = 1;
    if (m_SelectionMinZ > minz)
        m_SelectionMinZ = minz;
    if (m_SelectionMaxZ < maxz)
        m_SelectionMaxZ = maxz;
}

void CShaderAPIVk::BindStandardTexture(Sampler_t sampler, StandardTextureId_t id) {}

ITexture *CShaderAPIVk::GetRenderTargetEx(int nRenderTargetID) { return ShaderUtil()->GetRenderTargetEx(nRenderTargetID); }

void CShaderAPIVk::SetToneMappingScaleLinear(const Vector &scale) {}

const Vector &CShaderAPIVk::GetToneMappingScaleLinear() const { return *new Vector(0.0f, 0.0f, 0.0f); }

float CShaderAPIVk::GetLightMapScaleFactor() const { return 1.0f; }

void CShaderAPIVk::LoadBoneMatrix(int boneIndex, const float *m) {}

void CShaderAPIVk::GetDXLevelDefaults(uint &max_dxlevel, uint &recommended_dxlevel) {}

const FlashlightState_t &CShaderAPIVk::GetFlashlightStateEx(VMatrix &worldToTexture, ITexture **pFlashlightDepthTexture) const
{
    return *new FlashlightState_t;
}

float CShaderAPIVk::GetAmbientLightCubeLuminance() { return 1.0f; }

void CShaderAPIVk::GetDX9LightState(LightState_t *state) const
{
    state->m_nNumLights = 0;
    state->m_bAmbientLight = false;
    state->m_bStaticLightTexel = false;
    state->m_bStaticLightVertex = false;
}

int CShaderAPIVk::GetPixelFogCombo() { return 0; }

void CShaderAPIVk::BindStandardVertexTexture(VertexTextureSampler_t sampler, StandardTextureId_t id) {}

bool CShaderAPIVk::IsHWMorphingEnabled() const { return true; }

void CShaderAPIVk::GetStandardTextureDimensions(int *pWidth, int *pHeight, StandardTextureId_t id) {}

void CShaderAPIVk::SetBooleanVertexShaderConstant(int var, BOOL const *pVec, int numBools, bool bForce) {}

void CShaderAPIVk::SetIntegerVertexShaderConstant(int var, int const *pVec, int numIntVecs, bool bForce) {}

void CShaderAPIVk::SetBooleanPixelShaderConstant(int var, BOOL const *pVec, int numBools, bool bForce) {}

void CShaderAPIVk::SetIntegerPixelShaderConstant(int var, int const *pVec, int numIntVecs, bool bForce) {}

bool CShaderAPIVk::ShouldWriteDepthToDestAlpha() const { return false; }

void CShaderAPIVk::PushDeformation(DeformationBase_t const *Deformation) {}

void CShaderAPIVk::PopDeformation() {}

int CShaderAPIVk::GetNumActiveDeformations() const { return 0; }

int CShaderAPIVk::GetPackedDeformationInformation(int nMaskOfUnderstoodDeformations, float *pConstantValuesOut, int nBufferSize,
                                                  int nMaximumDeformations, int *pNumDefsOut) const
{
    return 0;
}

void CShaderAPIVk::MarkUnusedVertexFields(unsigned nFlags, int nTexCoordCount, bool *pUnusedTexCoords) {}

void CShaderAPIVk::ExecuteCommandBuffer(uint8 *pCmdBuffer) {}

void CShaderAPIVk::SetStandardTextureHandle(StandardTextureId_t nId, ShaderAPITextureHandle_t nHandle) {}

void CShaderAPIVk::GetCurrentColorCorrection(ShaderColorCorrectionInfo_t *pInfo) {}

void CShaderAPIVk::SetPSNearAndFarZ(int pshReg) {}

void CShaderAPIVk::EnableDebugTextureList(bool bEnable) { m_bEnableDebugTextureList = bEnable; }

void CShaderAPIVk::EnableGetAllTextures(bool bEnable) {}

KeyValues *CShaderAPIVk::GetDebugTextureList() { return m_pDebugTextureList; }

int CShaderAPIVk::GetTextureMemoryUsed(TextureMemoryType eTextureMemory) { return 0; }

bool CShaderAPIVk::IsDebugTextureListFresh(int numFramesAllowed /* = 1 */)
{
    return (m_nDebugDataExportFrame <= m_CurrentFrame) && (m_nDebugDataExportFrame >= m_CurrentFrame - numFramesAllowed);
}

bool CShaderAPIVk::SetDebugTextureRendering(bool bEnable)
{
    bool bVal = m_bDebugTexturesRendering;
    m_bDebugTexturesRendering = bEnable;
    return bVal;
}

void CShaderAPIVk::SetViewports(int nCount, const ShaderViewport_t *pViewports)
{
    Assert(nCount == 1 && pViewports[0].m_nVersion == SHADER_VIEWPORT_VERSION);
    if (nCount != 1)
        return;

    VkViewport viewport;
    viewport.x = pViewports[0].m_nTopLeftX;
    viewport.y = pViewports[0].m_nTopLeftY;
    viewport.width = pViewports[0].m_nWidth;
    viewport.height = pViewports[0].m_nHeight;
    viewport.minDepth = pViewports[0].m_flMinZ;
    viewport.maxDepth = pViewports[0].m_flMaxZ;

    // Clamp the viewport to the current render target...
    if (!m_UsingTextureRenderTarget)
    {
        // Clamp to both the back buffer and the window, if it is resizing
        int nMaxWidth = 0, nMaxHeight = 0;
        GetBackBufferDimensions(nMaxWidth, nMaxHeight);
        if (g_pShaderDevice->GetCurrentViewport()->IsResizing())
        {
            RECT viewRect;
            GetClientRect((HWND)g_pShaderDevice->GetCurrentViewHandle(), &viewRect);
            int nWindowWidth = viewRect.right - viewRect.left;
            int nWindowHeight = viewRect.bottom - viewRect.top;
            nMaxWidth = min(nWindowWidth, nMaxWidth);
            nMaxHeight = min(nWindowHeight, nMaxHeight);
        }

        // Dimensions can freak out on app exit, so at least make sure the viewport is positive
        if ((viewport.width > (unsigned int)nMaxWidth) && (nMaxWidth > 0))
        {
            viewport.width = nMaxWidth;
        }

        // Dimensions can freak out on app exit, so at least make sure the viewport is positive
        if ((viewport.height > (unsigned int)nMaxHeight) && (nMaxHeight > 0))
        {
            viewport.height = nMaxHeight;
        }
    }
    else
    {
        if (viewport.width > (unsigned int)m_ViewportMaxWidth)
        {
            viewport.width = m_ViewportMaxWidth;
        }
        if (viewport.height > (unsigned int)m_ViewportMaxHeight)
        {
            viewport.height = m_ViewportMaxHeight;
        }
    }

    // FIXME: Once we extract buffered primitives out, we can directly fill in desired state
    // and avoid the memcmp and copy
    if (memcmp(&m_DesiredState.m_Viewport, &viewport, sizeof(VkViewport)))
    {
        if (!g_pShaderDevice->IsDeactivated())
        {
            // State changed... need to flush the dynamic buffer
            FlushBufferedPrimitives();
        }

        memcpy(&m_DesiredState.m_Viewport, &viewport, sizeof(VkViewport));
    }
}

int CShaderAPIVk::GetViewports(ShaderViewport_t *pViewports, int nMax) const
{
    if (!pViewports || nMax == 0)
        return 1;

    pViewports[0].m_nTopLeftX = m_DesiredState.m_Viewport.x;
    pViewports[0].m_nTopLeftY = m_DesiredState.m_Viewport.y;
    pViewports[0].m_nWidth = m_DesiredState.m_Viewport.width;
    pViewports[0].m_nHeight = m_DesiredState.m_Viewport.height;
    pViewports[0].m_flMinZ = m_DesiredState.m_Viewport.minDepth;
    pViewports[0].m_flMaxZ = m_DesiredState.m_Viewport.maxDepth;
    return 1;
}

void CShaderAPIVk::ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil, int renderTargetWidth, int renderTargetHeight) {}

void CShaderAPIVk::ClearColor3ub(unsigned char r, unsigned char g, unsigned char b)
{
    g_pShaderDevice->GetCurrentViewport()->SetClearColor({r / 255.0f, g / 255.0f, b / 255.0f, 1.0f});
}

void CShaderAPIVk::ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    g_pShaderDevice->GetCurrentViewport()->SetClearColor({r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f});
}

void CShaderAPIVk::BindVertexShader(VertexShaderHandle_t hVertexShader) { g_pShaderManager->BindVertexShader(hVertexShader); }

void CShaderAPIVk::BindGeometryShader(GeometryShaderHandle_t hGeometryShader) { Assert(hGeometryShader == GEOMETRY_SHADER_HANDLE_INVALID); }

void CShaderAPIVk::BindPixelShader(PixelShaderHandle_t hPixelShader) { g_pShaderManager->BindPixelShader(hPixelShader); }

void CShaderAPIVk::SetRasterState(const ShaderRasterState_t &state) {}

bool CShaderAPIVk::SetMode(void *hWnd, int nAdapter, const ShaderDeviceInfo_t &info)
{
    CreateInterfaceFn result = g_pShaderDeviceMgr->SetMode(hWnd, nAdapter, info);
    return result != NULL;
}

void CShaderAPIVk::ChangeVideoMode(const ShaderDeviceInfo_t &info)
{
    int nAdapter = g_pShaderDeviceMgr->GetCurrentAdapter();
    void *hWnd = g_pShaderDevice->GetCurrentViewHandle();
    g_pShaderDeviceMgr->SetMode(hWnd, nAdapter, info);
}

StateSnapshot_t CShaderAPIVk::TakeSnapshot()
{
    StateSnapshot_t id = 0;
    if (g_pShaderShadow->m_IsTranslucent)
        id |= TRANSLUCENT;
    if (g_pShaderShadow->m_IsAlphaTested)
        id |= ALPHATESTED;
    if (g_pShaderShadow->m_bUsesVertexAndPixelShaders)
        id |= VERTEX_AND_PIXEL_SHADERS;
    if (g_pShaderShadow->m_bIsDepthWriteEnabled)
        id |= DEPTHWRITE;
    return id;
}

void CShaderAPIVk::TexMinFilter(ShaderTexFilterMode_t texFilterMode) {}

void CShaderAPIVk::TexMagFilter(ShaderTexFilterMode_t texFilterMode) {}

void CShaderAPIVk::TexWrap(ShaderTexCoordComponent_t coord, ShaderTexWrapMode_t wrapMode) {}

void CShaderAPIVk::CopyRenderTargetToTexture(ShaderAPITextureHandle_t textureHandle) {}

void CShaderAPIVk::Bind(IMaterial *pMaterial)
{
    IMaterialInternal *pMatInt = static_cast<IMaterialInternal *>(pMaterial);

    bool bMaterialChanged;
    if (m_pMaterial && pMatInt && m_pMaterial->InMaterialPage() && pMatInt->InMaterialPage())
    {
        bMaterialChanged = (m_pMaterial->GetMaterialPage() != pMatInt->GetMaterialPage());
    }
    else
    {
        bMaterialChanged =
            (m_pMaterial != pMatInt) || (m_pMaterial && m_pMaterial->InMaterialPage()) || (pMatInt && pMatInt->InMaterialPage());
    }

    if (bMaterialChanged)
    {
        FlushBufferedPrimitives();
        m_pMaterial = pMatInt;
    }
}

void CShaderAPIVk::FlushBufferedPrimitives()
{
    if (ShaderUtil())
    {
        if (!ShaderUtil()->OnFlushBufferedPrimitives())
        {
            return;
        }
    }
    FlushBufferedPrimitivesInternal();
}

void CShaderAPIVk::FlushBufferedPrimitivesInternal()
{
    // This shouldn't happen in the inner rendering loop!
    Assert(m_pRenderMesh == nullptr);

    // NOTE: We've gotta store off the matrix mode because
    // it'll get reset by the default state application caused by the flush
    int tempStack = m_CurrStack;
    int tempMatrixMode = m_MatrixMode;

    g_pMeshMgr->Flush();

    m_CurrStack = tempStack;
    m_MatrixMode = tempMatrixMode;
}

IMesh *CShaderAPIVk::GetDynamicMesh(IMaterial *pMaterial, int nHWSkinBoneCount, bool bBuffered, IMesh *pVertexOverride,
                                    IMesh *pIndexOverride)
{
    return g_pMeshMgr->GetDynamicMesh(pMaterial, VERTEX_FORMAT_UNKNOWN, nHWSkinBoneCount, bBuffered, pVertexOverride, pIndexOverride);
}

IMesh *CShaderAPIVk::GetDynamicMeshEx(IMaterial *pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount, bool bBuffered,
                                      IMesh *pVertexOverride, IMesh *pIndexOverride)
{
    return g_pMeshMgr->GetDynamicMesh(pMaterial, vertexFormat, nHWSkinBoneCount, bBuffered, pVertexOverride, pIndexOverride);
}

bool CShaderAPIVk::IsTranslucent(StateSnapshot_t id) const { return (id & TRANSLUCENT) != 0; }

bool CShaderAPIVk::IsAlphaTested(StateSnapshot_t id) const { return (id & ALPHATESTED) != 0; }

bool CShaderAPIVk::UsesVertexAndPixelShaders(StateSnapshot_t id) const { return (id & VERTEX_AND_PIXEL_SHADERS) != 0; }

bool CShaderAPIVk::IsDepthWriteEnabled(StateSnapshot_t id) const { return (id & DEPTHWRITE) != 0; }

VertexFormat_t CShaderAPIVk::ComputeVertexFormat(int numSnapshots, StateSnapshot_t *pIds) const { return 0; }

VertexFormat_t CShaderAPIVk::ComputeVertexUsage(int numSnapshots, StateSnapshot_t *pIds) const { return 0; }

void CShaderAPIVk::DrawMesh(CBaseMeshVk *pMesh)
{
    VPROF("CShaderAPIVk::DrawMesh");
    m_pRenderMesh = pMesh;
    VertexFormat_t vertexFormat = m_pRenderMesh->GetVertexFormat();
    SetVertexDecl(vertexFormat, m_pRenderMesh->HasColorMesh(), m_pRenderMesh->HasFlexMesh(), m_pMaterial->IsUsingVertexID());
    Assert(m_pRenderMesh && m_pMaterial);
    // VK_FIXME
    // m_pMaterial->DrawMesh(CompressionType(vertexFormat));
    BeginPass(0);
    RenderPass(0, 0);
    m_pRenderMesh = nullptr;
}

void CShaderAPIVk::ModifyVertexData() {}

void CShaderAPIVk::BeginPass(StateSnapshot_t snapshot)
{
    VPROF("CShaderAPIVk::BeginPass");
    if (g_pShaderDevice->IsDeactivated())
        return;

    m_nCurrentSnapshot = snapshot;

    // FIXME: This only does anything with temp meshes, so don't bother yet for the new code.
    if (m_pRenderMesh)
    {
        m_pRenderMesh->BeginPass();
    }
}

void CShaderAPIVk::RenderPass(int nPass, int nPassCount)
{
    if (g_pShaderDevice->IsDeactivated())
        return;

    Assert(m_nCurrentSnapshot != -1);

    // m_TransitionTable.UseSnapshot( m_nCurrentSnapshot );
    // CommitPerPassStateChanges( m_nCurrentSnapshot );

    if (m_pRenderMesh)
    {
        m_pRenderMesh->RenderPass();
    }
    else
    {
        g_pMeshMgr->RenderPassWithVertexAndIndexBuffers();
    }
    m_nCurrentSnapshot = -1;
}

void CShaderAPIVk::SetNumBoneWeights(int numBones) {}

void CShaderAPIVk::SetLight(int lightNum, const LightDesc_t &desc) {}

void CShaderAPIVk::SetLightingOrigin(Vector vLightingOrigin) {}

void CShaderAPIVk::SetAmbientLight(float r, float g, float b) {}

void CShaderAPIVk::SetAmbientLightCube(Vector4D cube[6]) {}

void CShaderAPIVk::ShadeMode(ShaderShadeMode_t mode) {}

void CShaderAPIVk::CullMode(MaterialCullMode_t cullMode)
{
    VkCullModeFlags newCullMode;
    VkFrontFace newFrontFace;
    switch (cullMode)
    {
    // Note: MaterialCullMode_t in Source Engine determines which faces SHOULD be culled.
    case MATERIAL_CULLMODE_CCW:
        // Cull counterclockwise winding polys
        newCullMode = VK_CULL_MODE_FRONT_BIT;
        newFrontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        break;

    case MATERIAL_CULLMODE_CW:
        // Culls clockwise winding polys
        newCullMode = VK_CULL_MODE_FRONT_BIT;
        newFrontFace = VK_FRONT_FACE_CLOCKWISE;
        break;

    default:
        Warning("CullMode: invalid cullMode\n");
        return;
    }

    if (m_DynamicState.m_DesiredCullMode != newCullMode || m_DynamicState.m_DesiredFrontFace)
    {
        FlushBufferedPrimitives();
        m_DynamicState.m_DesiredCullMode = newCullMode;
        m_DynamicState.m_DesiredFrontFace = newFrontFace;
        SetCullModeState(m_DynamicState.m_bCullEnabled, m_DynamicState.m_DesiredCullMode, m_DynamicState.m_DesiredFrontFace);
    }
}

void CShaderAPIVk::SetCullModeState(bool bEnable, VkCullModeFlags desiredCullMode, VkFrontFace desiredFrontFace)
{
    VkCullModeFlags cullMode = bEnable ? desiredCullMode : VK_CULL_MODE_NONE;
    if (cullMode != m_DynamicState.m_CullMode)
    {
        // SetRenderStateConstMacro( this, D3DRS_CULLMODE, cullMode );
        m_DynamicState.m_CullMode = cullMode;
    }
    m_DynamicState.m_FrontFace = desiredFrontFace;
}

VkCullModeFlags CShaderAPIVk::GetCullMode() const
{
    if (!m_pMaterial || m_pMaterial->GetMaterialVarFlag(MATERIAL_VAR_NOCULL))
        return VK_CULL_MODE_NONE;
    return m_DynamicState.m_DesiredCullMode;
}

VkFrontFace CShaderAPIVk::GetFrontFace() const { return m_DynamicState.m_DesiredFrontFace; }

void CShaderAPIVk::ApplyCullEnable(bool bEnable)
{
    m_DynamicState.m_bCullEnabled = bEnable;
    SetCullModeState(m_DynamicState.m_bCullEnabled, m_DynamicState.m_DesiredCullMode, m_DynamicState.m_DesiredFrontFace);
}

void CShaderAPIVk::ForceDepthFuncEquals(bool bEnable) {}

void CShaderAPIVk::OverrideDepthEnable(bool bEnable, bool bDepthEnable) {}

void CShaderAPIVk::SetHeightClipZ(float z)
{
    if (z != m_DynamicState.m_HeightClipZ)
    {
        FlushBufferedPrimitives();
        m_DynamicState.m_HeightClipZ = z;
        // VK_TODO
        // UpdateVertexShaderFogParams();
        // UpdateFastClipUserClipPlane();
        m_DynamicState.m_TransformChanged[MATERIAL_PROJECTION] |= STATE_CHANGED_VERTEX_SHADER | STATE_CHANGED_FIXED_FUNCTION;
    }
}

void CShaderAPIVk::SetHeightClipMode(MaterialHeightClipMode_t heightClipMode)
{
    if (heightClipMode != m_DynamicState.m_HeightClipMode)
    {
        FlushBufferedPrimitives();
        m_DynamicState.m_HeightClipMode = heightClipMode;
        // VK_TODO
        // UpdateVertexShaderFogParams();
        // UpdateFastClipUserClipPlane();
        m_DynamicState.m_TransformChanged[MATERIAL_PROJECTION] |= STATE_CHANGED_VERTEX_SHADER | STATE_CHANGED_FIXED_FUNCTION;
    }
}

void CShaderAPIVk::SetClipPlane(int index, const float *pPlane)
{
    Assert(index < g_pHardwareConfig->MaxUserClipPlanes() && index >= 0);

    // NOTE: The plane here is specified in *world space*
    // NOTE: This is done because they assume Ax+By+Cz+Dw = 0 (where w = 1 in real space)
    // while we use Ax+By+Cz=D

    glm::vec4 plane;
    plane.x = pPlane[0];
    plane.y = pPlane[1];
    plane.z = pPlane[2];
    plane.w = -pPlane[3];

    if (plane != m_DynamicState.m_UserClipPlaneWorld[index])
    {
        FlushBufferedPrimitives();

        m_DynamicState.m_UserClipPlaneChanged |= (1 << index);
        m_DynamicState.m_UserClipPlaneWorld[index] = plane;
    }
}

void CShaderAPIVk::EnableClipPlane(int index, bool bEnable)
{
    Assert(index < g_pHardwareConfig->MaxUserClipPlanes() && index >= 0);
    if ((m_DynamicState.m_UserClipPlaneEnabled & (1 << index) ? true : false) != bEnable)
    {
        FlushBufferedPrimitives();
        if (bEnable)
        {
            m_DynamicState.m_UserClipPlaneEnabled |= (1 << index);
        }
        else
        {
            m_DynamicState.m_UserClipPlaneEnabled &= ~(1 << index);
        }
        // VK_TODO
        // SetRenderStateConstMacro( this, D3DRS_CLIPPLANEENABLE, m_DynamicState.m_UserClipPlaneEnabled );
    }
}

void CShaderAPIVk::SetSkinningMatrices() {}

ImageFormat CShaderAPIVk::GetNearestSupportedFormat(ImageFormat fmt, bool bFilteringRequired) const { return fmt; }

ImageFormat CShaderAPIVk::GetNearestRenderTargetFormat(ImageFormat fmt) const { return fmt; }

bool CShaderAPIVk::DoRenderTargetsNeedSeparateDepthBuffer() const { return false; }

ShaderAPITextureHandle_t CShaderAPIVk::CreateTexture(int width, int height, int depth, ImageFormat dstImageFormat, int numMipLevels,
                                                     int numCopies, int flags, const char *pDebugName, const char *pTextureGroupName)
{
    return 0;
}

void CShaderAPIVk::DeleteTexture(ShaderAPITextureHandle_t textureHandle) {}

ShaderAPITextureHandle_t CShaderAPIVk::CreateDepthTexture(ImageFormat renderTargetFormat, int width, int height, const char *pDebugName,
                                                          bool bTexture)
{
    return 0;
}

bool CShaderAPIVk::IsTexture(ShaderAPITextureHandle_t textureHandle) { return true; }

bool CShaderAPIVk::IsTextureResident(ShaderAPITextureHandle_t textureHandle) { return true; }

void CShaderAPIVk::ModifyTexture(ShaderAPITextureHandle_t textureHandle) {}

void CShaderAPIVk::TexImage2D(int level, int cubeFaceID, ImageFormat dstFormat, int zOffset, int width, int height, ImageFormat srcFormat,
                              bool bSrcIsTiled, void *imageData)
{
}

void CShaderAPIVk::TexSubImage2D(int level, int cubeFaceID, int xOffset, int yOffset, int zOffset, int width, int height,
                                 ImageFormat srcFormat, int srcStride, bool bSrcIsTiled, void *imageData)
{
}

void CShaderAPIVk::TexImageFromVTF(IVTFTexture *pVTF, int iVTFFrame) {}

bool CShaderAPIVk::TexLock(int level, int cubeFaceID, int xOffset, int yOffset, int width, int height, CPixelWriter &writer)
{
    return true;
}

void CShaderAPIVk::TexUnlock() {}

void CShaderAPIVk::TexSetPriority(int priority) {}

void CShaderAPIVk::BindTexture(Sampler_t sampler, ShaderAPITextureHandle_t textureHandle) {}

void CShaderAPIVk::SetRenderTarget(ShaderAPITextureHandle_t colorTextureHandle, ShaderAPITextureHandle_t depthTextureHandle) {}

void CShaderAPIVk::ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) {}

void CShaderAPIVk::ReadPixels(int x, int y, int width, int height, unsigned char *data, ImageFormat dstFormat) {}

void CShaderAPIVk::ReadPixels(Rect_t *pSrcRect, Rect_t *pDstRect, unsigned char *data, ImageFormat dstFormat, int nDstStride) {}

void CShaderAPIVk::FlushHardware() {}

void CShaderAPIVk::BeginFrame()
{
    if (m_bResetRenderStateNeeded)
    {
        ResetRenderState(false);
        m_bResetRenderStateNeeded = false;
    }

    ++m_CurrentFrame;
    m_nTextureMemoryUsedLastFrame = 0;
}

void CShaderAPIVk::EndFrame()
{
    // VK_TODO
    // ExportTextureList();
}

int CShaderAPIVk::SelectionMode(bool selectionMode) { return 0; }

void CShaderAPIVk::SelectionBuffer(unsigned int *pBuffer, int size) {}

void CShaderAPIVk::ClearSelectionNames() {}

void CShaderAPIVk::LoadSelectionName(int name) {}

void CShaderAPIVk::PushSelectionName(int name) {}

void CShaderAPIVk::PopSelectionName() {}

void CShaderAPIVk::ForceHardwareSync() {}

void CShaderAPIVk::ClearSnapshots()
{
    FlushBufferedPrimitives();
    // VK_TODO
    // m_TransitionTable.Reset();
    InitRenderState();
}

void CShaderAPIVk::FogStart(float fStart) {}

void CShaderAPIVk::FogEnd(float fEnd) {}

void CShaderAPIVk::SetFogZ(float fogZ) {}

void CShaderAPIVk::SceneFogColor3ub(unsigned char r, unsigned char g, unsigned char b) {}

void CShaderAPIVk::GetSceneFogColor(unsigned char *rgb) {}

void CShaderAPIVk::SceneFogMode(MaterialFogMode_t fogMode) {}

bool CShaderAPIVk::CanDownloadTextures() const
{
    if (g_pShaderDevice->IsDeactivated())
        return false;

    return g_pShaderDevice->GetCurrentViewport() != VK_NULL_HANDLE;
}

//-----------------------------------------------------------------------------
// Initialize vertex and pixel shaders
//-----------------------------------------------------------------------------
void CShaderAPIVk::InitVertexAndPixelShaders()
{
    // Allocate space for the pixel and vertex shader constants...
    if (g_pHardwareConfig->Caps().m_SupportsPixelShaders)
    {
        // pixel shaders
        {
            if (m_DynamicState.m_pVectorPixelShaderConstant)
            {
                delete[] m_DynamicState.m_pVectorPixelShaderConstant;
            }
            m_DynamicState.m_pVectorPixelShaderConstant = new Vector4D[g_pHardwareConfig->Caps().m_NumPixelShaderConstants];

            if (m_DesiredState.m_pVectorPixelShaderConstant)
            {
                delete[] m_DesiredState.m_pVectorPixelShaderConstant;
            }
            m_DesiredState.m_pVectorPixelShaderConstant = new Vector4D[g_pHardwareConfig->Caps().m_NumPixelShaderConstants];

            if (m_DynamicState.m_pBooleanPixelShaderConstant)
            {
                delete[] m_DynamicState.m_pBooleanPixelShaderConstant;
            }
            m_DynamicState.m_pBooleanPixelShaderConstant = new BOOL[g_pHardwareConfig->Caps().m_NumBooleanPixelShaderConstants];

            if (m_DesiredState.m_pBooleanPixelShaderConstant)
            {
                delete[] m_DesiredState.m_pBooleanPixelShaderConstant;
            }
            m_DesiredState.m_pBooleanPixelShaderConstant = new BOOL[g_pHardwareConfig->Caps().m_NumBooleanPixelShaderConstants];

            if (m_DynamicState.m_pIntegerPixelShaderConstant)
            {
                delete[] m_DynamicState.m_pIntegerPixelShaderConstant;
            }
            m_DynamicState.m_pIntegerPixelShaderConstant = new IntVector4D[g_pHardwareConfig->Caps().m_NumIntegerPixelShaderConstants];

            if (m_DesiredState.m_pIntegerPixelShaderConstant)
            {
                delete[] m_DesiredState.m_pIntegerPixelShaderConstant;
            }
            m_DesiredState.m_pIntegerPixelShaderConstant = new IntVector4D[g_pHardwareConfig->Caps().m_NumIntegerPixelShaderConstants];

            // force reset vector pixel constants
            int i;
            for (i = 0; i < g_pHardwareConfig->Caps().m_NumPixelShaderConstants; ++i)
            {
                m_DesiredState.m_pVectorPixelShaderConstant[i].Init();
            }
            SetPixelShaderConstant(0, m_DesiredState.m_pVectorPixelShaderConstant[0].Base(),
                                   g_pHardwareConfig->Caps().m_NumPixelShaderConstants, true);

            // force reset boolean pixel constants
            int nNumBooleanPixelShaderConstants = g_pHardwareConfig->Caps().m_NumBooleanPixelShaderConstants;
            if (nNumBooleanPixelShaderConstants)
            {
                for (i = 0; i < nNumBooleanPixelShaderConstants; ++i)
                {
                    m_DesiredState.m_pBooleanPixelShaderConstant[i] = 0;
                }
                SetBooleanPixelShaderConstant(0, m_DesiredState.m_pBooleanPixelShaderConstant, nNumBooleanPixelShaderConstants, true);
            }

            // force reset integer pixel constants
            int nNumIntegerPixelShaderConstants = g_pHardwareConfig->Caps().m_NumIntegerPixelShaderConstants;
            if (nNumIntegerPixelShaderConstants)
            {
                for (i = 0; i < nNumIntegerPixelShaderConstants; ++i)
                {
                    m_DesiredState.m_pIntegerPixelShaderConstant[i].Init();
                }
                SetIntegerPixelShaderConstant(0, m_DesiredState.m_pIntegerPixelShaderConstant[0].Base(), nNumIntegerPixelShaderConstants,
                                              true);
            }
        }

        // vertex shaders
        {
            if (m_DynamicState.m_pVectorVertexShaderConstant)
            {
                delete[] m_DynamicState.m_pVectorVertexShaderConstant;
            }
            m_DynamicState.m_pVectorVertexShaderConstant = new Vector4D[g_pHardwareConfig->Caps().m_NumVertexShaderConstants];

            if (m_DesiredState.m_pVectorVertexShaderConstant)
            {
                delete[] m_DesiredState.m_pVectorVertexShaderConstant;
            }
            m_DesiredState.m_pVectorVertexShaderConstant = new Vector4D[g_pHardwareConfig->Caps().m_NumVertexShaderConstants];

            if (m_DynamicState.m_pBooleanVertexShaderConstant)
            {
                delete[] m_DynamicState.m_pBooleanVertexShaderConstant;
            }
            m_DynamicState.m_pBooleanVertexShaderConstant = new BOOL[g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants];

            if (m_DesiredState.m_pBooleanVertexShaderConstant)
            {
                delete[] m_DesiredState.m_pBooleanVertexShaderConstant;
            }
            m_DesiredState.m_pBooleanVertexShaderConstant = new BOOL[g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants];

            if (m_DynamicState.m_pIntegerVertexShaderConstant)
            {
                delete[] m_DynamicState.m_pIntegerVertexShaderConstant;
            }
            m_DynamicState.m_pIntegerVertexShaderConstant = new IntVector4D[g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants];

            if (m_DesiredState.m_pIntegerVertexShaderConstant)
            {
                delete[] m_DesiredState.m_pIntegerVertexShaderConstant;
            }
            m_DesiredState.m_pIntegerVertexShaderConstant = new IntVector4D[g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants];

            // force reset vector vertex constants
            int i;
            for (i = 0; i < g_pHardwareConfig->Caps().m_NumVertexShaderConstants; ++i)
            {
                m_DesiredState.m_pVectorVertexShaderConstant[i].Init();
            }
            SetVertexShaderConstant(0, m_DesiredState.m_pVectorVertexShaderConstant[0].Base(),
                                    g_pHardwareConfig->Caps().m_NumVertexShaderConstants, true);

            // force reset boolean vertex constants
            for (i = 0; i < g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants; ++i)
            {
                m_DesiredState.m_pBooleanVertexShaderConstant[i] = 0;
            }
            SetBooleanVertexShaderConstant(0, m_DesiredState.m_pBooleanVertexShaderConstant,
                                           g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants, true);

            // force reset integer vertex constants
            for (i = 0; i < g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants; ++i)
            {
                m_DesiredState.m_pIntegerVertexShaderConstant[i].Init();
            }
            SetIntegerVertexShaderConstant(0, m_DesiredState.m_pIntegerVertexShaderConstant[0].Base(),
                                           g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants, true);
        }

        SetStandardVertexShaderConstants(OVERBRIGHT);
    }

    // Set up the vertex and pixel shader stuff
    g_pShaderManager->ResetShaderState();
}

//-----------------------------------------------------------------------------
// Initialize render state
//-----------------------------------------------------------------------------
void CShaderAPIVk::InitRenderState()
{
    // Set the default shadow state
    g_pShaderShadow->SetDefaultState();

    // Grab a snapshot of this state; we'll be using it to set the board
    // state to something well defined.
    // VK_TODO
    // m_TransitionTable.TakeDefaultStateSnapshot();

    if (!g_pShaderDevice->IsDeactivated())
    {
        ResetRenderState();
    }
}

void CShaderAPIVk::QueueResetRenderState() { m_bResetRenderStateNeeded = true; }

void CShaderAPIVk::ResetRenderState(bool bFullReset)
{
    // VK_TODO: implement rest of this function
    if (!CanDownloadTextures())
    {
        QueueResetRenderState();
        return;
    }

    // m_bResettingRenderState = true;

    OwnGPUResources(true);

    // ResetDXRenderState();

    // We're not currently rendering anything
    // m_nCurrentSnapshot = -1;

    m_CachedPolyOffsetProjectionMatrix = glm::mat4();
    m_CachedFastClipProjectionMatrix = glm::mat4();
    m_CachedFastClipPolyOffsetProjectionMatrix = glm::mat4();
    m_UsingTextureRenderTarget = false;

    // m_SceneFogColor[0] = 0;
    // m_SceneFogColor[1] = 0;
    // m_SceneFogColor[2] = 0;
    // m_SceneFogMode = MATERIAL_FOG_NONE;

    // This is state that isn't part of the snapshot per-se, because we
    // don't need it when it's actually time to render. This just helps us
    // to construct the shadow state.
    m_DynamicState.m_ClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

    if (bFullReset)
    {
        InitVertexAndPixelShaders();
    }
    else
    {
        // just need to dirty the dynamic state, desired state gets copied into below
        Q_memset(m_DynamicState.m_pVectorPixelShaderConstant, 0, g_pHardwareConfig->Caps().m_NumPixelShaderConstants * sizeof(Vector4D));
        Q_memset(m_DynamicState.m_pBooleanPixelShaderConstant, 0,
                 g_pHardwareConfig->Caps().m_NumBooleanPixelShaderConstants * sizeof(BOOL));
        Q_memset(m_DynamicState.m_pIntegerPixelShaderConstant, 0,
                 g_pHardwareConfig->Caps().m_NumIntegerPixelShaderConstants * sizeof(IntVector4D));

        Q_memset(m_DynamicState.m_pVectorVertexShaderConstant, 0, g_pHardwareConfig->Caps().m_NumVertexShaderConstants * sizeof(Vector4D));
        Q_memset(m_DynamicState.m_pBooleanVertexShaderConstant, 0,
                 g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants * sizeof(BOOL));
        Q_memset(m_DynamicState.m_pIntegerVertexShaderConstant, 0,
                 g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants * sizeof(IntVector4D));

        SetStandardVertexShaderConstants(OVERBRIGHT);
    }

    // Set the default compressed depth range written to dest alpha. Only need to compress it for 8bit alpha to get a useful gradient.
    m_DynamicState.m_DestAlphaDepthRange = (g_pHardwareConfig->GetHDRType() == HDR_TYPE_FLOAT) ? 8192.0f : 192.0f;

    m_CachedAmbientLightCube = STATE_CHANGED;

    // Set the constant color
    m_DynamicState.m_ConstantColor = 0xFFFFFFFF;
    Color4ub(255, 255, 255, 255);

    // Ambient light color
    m_DynamicState.m_Ambient = 0;
    // SetSupportedRenderState(D3DRS_AMBIENT, m_DynamicState.m_Ambient);

    // Fog
    // m_VertexShaderFogParams[0] = m_VertexShaderFogParams[1] = 0.0f;
    m_WorldSpaceCameraPosition.Init(0, 0, 0.01f, 0); // Don't let z be zero, as some pixel shaders will divide by this
    m_DynamicState.m_FogColor = 0xFFFFFFFF;
    m_DynamicState.m_PixelFogColor[0] = m_DynamicState.m_PixelFogColor[1] = m_DynamicState.m_PixelFogColor[2] =
        m_DynamicState.m_PixelFogColor[3] = 0.0f;
    m_DynamicState.m_bFogGammaCorrectionDisabled = false;
    m_DynamicState.m_FogEnable = false;
    m_DynamicState.m_SceneFog = MATERIAL_FOG_NONE;
    m_DynamicState.m_FogMode = FOG_NONE;
    m_DynamicState.m_FogStart = -1;
    m_DynamicState.m_FogEnd = -1;
    m_DynamicState.m_FogMaxDensity = -1.0f;
    m_DynamicState.m_FogZ = 0.0f;

    // SetSupportedRenderState(D3DRS_FOGCOLOR, m_DynamicState.m_FogColor);
    // SetSupportedRenderState(D3DRS_FOGENABLE, m_DynamicState.m_FogEnable);
    // SetSupportedRenderState(D3DRS_FOGTABLEMODE, D3DFOG_NONE);
    // SetSupportedRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
    // SetSupportedRenderState(D3DRS_RANGEFOGENABLE, false);

    FogStart(0);
    FogEnd(0);
    FogMaxDensity(1.0f);

    m_DynamicState.m_bSRGBWritesEnabled = false;

    // Set the cull mode
    m_DynamicState.m_bCullEnabled = true;
    m_DynamicState.m_CullMode = VK_CULL_MODE_BACK_BIT;
    m_DynamicState.m_DesiredCullMode = VK_CULL_MODE_BACK_BIT;
    // SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    // No shade mode yet
    m_DynamicState.m_ShadeMode = SHADE_FLAT;
    ShadeMode(SHADER_SMOOTH);

    m_DynamicState.m_bHWMorphingEnabled = false;

    // Skinning...
    m_DynamicState.m_NumBones = 0;
    m_DynamicState.m_VertexBlend = 0;
    // SetSupportedRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
    // SetSupportedRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);

    // No normal normalization
    m_DynamicState.m_NormalizeNormals = false;
    // SetSupportedRenderState(D3DRS_NORMALIZENORMALS, m_DynamicState.m_NormalizeNormals);

    // bool bAntialiasing = (m_PresentParameters.MultiSampleType != D3DMULTISAMPLE_NONE);
    // if (g_pHardwareConfig->GetHDRType() == HDR_TYPE_FLOAT)
    //{
    //    bAntialiasing = false;
    //}
    // SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, bAntialiasing);

    // Anisotropic filtering is disabled by default
    if (bFullReset)
    {
        SetAnisotropicLevel(1);
    }

    int i;
    /*
    for (i = 0; i < g_pHardwareConfig->ActualCaps().m_NumTextureStages; ++i)
    {
        TextureStage(i).m_TextureTransformFlags = D3DTTFF_DISABLE;
        TextureStage(i).m_BumpEnvMat00 = 1.0f;
        TextureStage(i).m_BumpEnvMat01 = 0.0f;
        TextureStage(i).m_BumpEnvMat10 = 0.0f;
        TextureStage(i).m_BumpEnvMat11 = 1.0f;

        SetTextureStageState(i, D3DTSS_TEXTURETRANSFORMFLAGS, TextureStage(i).m_TextureTransformFlags);
        SetTextureStageState(i, D3DTSS_BUMPENVMAT00, *((LPDWORD)(&TextureStage(i).m_BumpEnvMat00)));
        SetTextureStageState(i, D3DTSS_BUMPENVMAT01, *((LPDWORD)(&TextureStage(i).m_BumpEnvMat01)));
        SetTextureStageState(i, D3DTSS_BUMPENVMAT10, *((LPDWORD)(&TextureStage(i).m_BumpEnvMat10)));
        SetTextureStageState(i, D3DTSS_BUMPENVMAT11, *((LPDWORD)(&TextureStage(i).m_BumpEnvMat11)));
    }

    for (i = 0; i < g_pHardwareConfig->ActualCaps().m_NumSamplers; ++i)
    {
        SamplerState(i).m_BoundTexture = INVALID_SHADERAPI_TEXTURE_HANDLE;
        SamplerState(i).m_UTexWrap = D3DTADDRESS_WRAP;
        SamplerState(i).m_VTexWrap = D3DTADDRESS_WRAP;
        SamplerState(i).m_WTexWrap = D3DTADDRESS_WRAP;
        SamplerState(i).m_MagFilter = D3DTEXF_POINT;
        SamplerState(i).m_MinFilter = D3DTEXF_POINT;
        SamplerState(i).m_MipFilter = D3DTEXF_NONE;
        SamplerState(i).m_FinestMipmapLevel = 0;
        SamplerState(i).m_LodBias = 0.0f;
        SamplerState(i).m_TextureEnable = false;
        SamplerState(i).m_SRGBReadEnable = false;

        // Just some initial state...
        Dx9Device()->SetTexture(i, 0);

        SetSamplerState(i, D3DSAMP_ADDRESSU, SamplerState(i).m_UTexWrap);
        SetSamplerState(i, D3DSAMP_ADDRESSV, SamplerState(i).m_VTexWrap);
        SetSamplerState(i, D3DSAMP_ADDRESSW, SamplerState(i).m_WTexWrap);
        SetSamplerState(i, D3DSAMP_MINFILTER, SamplerState(i).m_MinFilter);
        SetSamplerState(i, D3DSAMP_MAGFILTER, SamplerState(i).m_MagFilter);
        SetSamplerState(i, D3DSAMP_MIPFILTER, SamplerState(i).m_MipFilter);
        SetSamplerState(i, D3DSAMP_MAXMIPLEVEL, SamplerState(i).m_FinestMipmapLevel);
        SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, SamplerState(i).m_LodBias);

        SetSamplerState(i, D3DSAMP_BORDERCOLOR, RGB(0, 0, 0));
    }

    // FIXME!!!!! : This barfs with the debug runtime on 6800.
    for (i = 0; i < g_pHardwareConfig->ActualCaps().m_nVertexTextureCount; i++)
    {
        m_DynamicState.m_VertexTextureState[i].m_BoundTexture = INVALID_SHADERAPI_TEXTURE_HANDLE;
        Dx9Device()->SetTexture(D3DVERTEXTEXTURESAMPLER0 + i, NULL);

        m_DynamicState.m_VertexTextureState[i].m_UTexWrap = D3DTADDRESS_CLAMP;
        m_DynamicState.m_VertexTextureState[i].m_VTexWrap = D3DTADDRESS_CLAMP;
        //		m_DynamicState.m_VertexTextureState[i].m_WTexWrap = D3DTADDRESS_CLAMP;
        m_DynamicState.m_VertexTextureState[i].m_MinFilter = D3DTEXF_POINT;
        m_DynamicState.m_VertexTextureState[i].m_MagFilter = D3DTEXF_POINT;
        m_DynamicState.m_VertexTextureState[i].m_MipFilter = D3DTEXF_POINT;
        SetSamplerState(D3DVERTEXTEXTURESAMPLER0 + i, D3DSAMP_ADDRESSU, m_DynamicState.m_VertexTextureState[i].m_UTexWrap);
        SetSamplerState(D3DVERTEXTEXTURESAMPLER0 + i, D3DSAMP_ADDRESSV, m_DynamicState.m_VertexTextureState[i].m_VTexWrap);
        //		SetSamplerState( D3DVERTEXTEXTURESAMPLER0 + i, D3DSAMP_ADDRESSW, m_DynamicState.m_VertexTextureState[i].m_WTexWrap );
        SetSamplerState(D3DVERTEXTEXTURESAMPLER0 + i, D3DSAMP_MINFILTER, m_DynamicState.m_VertexTextureState[i].m_MinFilter);
        SetSamplerState(D3DVERTEXTEXTURESAMPLER0 + i, D3DSAMP_MAGFILTER, m_DynamicState.m_VertexTextureState[i].m_MagFilter);
        SetSamplerState(D3DVERTEXTEXTURESAMPLER0 + i, D3DSAMP_MIPFILTER, m_DynamicState.m_VertexTextureState[i].m_MipFilter);
    }
    */

    m_DynamicState.m_NumLights = 0;
    for (i = 0; i < MAX_NUM_LIGHTS; ++i)
    {
        m_DynamicState.m_LightEnable[i] = false;
        m_DynamicState.m_LightChanged[i] = STATE_CHANGED;
        m_DynamicState.m_LightEnableChanged[i] = STATE_CHANGED;
    }

    for (i = 0; i < NUM_MATRIX_MODES; ++i)
    {
        // By setting this to *not* be identity, we force an update...
        m_DynamicState.m_TransformType[i] = TRANSFORM_IS_GENERAL;
        m_DynamicState.m_TransformChanged[i] = STATE_CHANGED;
    }

    // set the board state to match the default state
    // m_TransitionTable.UseDefaultState();

    // Set the default render state
    SetDefaultState();

    // Constant for all time
    // SetSupportedRenderState(D3DRS_CLIPPING, TRUE);
    // SetSupportedRenderState(D3DRS_LOCALVIEWER, TRUE);
    // SetSupportedRenderState(D3DRS_POINTSCALEENABLE, FALSE);
    // SetSupportedRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    // SetSupportedRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2);
    // SetSupportedRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    // SetSupportedRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    // SetSupportedRenderState(D3DRS_COLORVERTEX, TRUE); // This defaults to true anyways. . .

    // Set a default identity material.
    // SetDefaultMaterial();

    if (bFullReset)
    {
        // Set the modelview matrix to identity too
        for (i = 0; i < NUM_MODEL_TRANSFORMS; ++i)
        {
            SetIdentityMatrix(m_boneMatrix[i]);
        }
        MatrixMode(MATERIAL_VIEW);
        LoadIdentity();
        MatrixMode(MATERIAL_PROJECTION);
        LoadIdentity();
    }

    m_DynamicState.m_Viewport.x = m_DynamicState.m_Viewport.y = m_DynamicState.m_Viewport.width = m_DynamicState.m_Viewport.height =
        0xFFFFFFFF;
    m_DynamicState.m_Viewport.minDepth = m_DynamicState.m_Viewport.maxDepth = 0.0;

    // Be sure scissoring is off
    // m_DynamicState.m_RenderState[D3DRS_SCISSORTESTENABLE] = FALSE;
    // SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    m_DynamicState.m_ScissorRect.left = -1;
    m_DynamicState.m_ScissorRect.top = -1;
    m_DynamicState.m_ScissorRect.right = -1;
    m_DynamicState.m_ScissorRect.bottom = -1;

    // SetHeightClipMode( MATERIAL_HEIGHTCLIPMODE_DISABLE );
    EnableFastClip(false);
    float fFakePlane[4];
    unsigned int iFakePlaneVal = 0xFFFFFFFF;
    fFakePlane[0] = fFakePlane[1] = fFakePlane[2] = fFakePlane[3] = *((float *)&iFakePlaneVal);
    SetFastClipPlane(fFakePlane); // doing this to better wire up plane change detection

    float zero[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    // Make sure that our state is dirty.
    m_DynamicState.m_UserClipPlaneEnabled = 0;
    m_DynamicState.m_UserClipPlaneChanged = 0;
    m_DynamicState.m_UserClipLastUpdatedUsingFixedFunction = false;
    for (i = 0; i < g_pHardwareConfig->MaxUserClipPlanes(); i++)
    {
        // Make sure that our state is dirty.
        m_DynamicState.m_UserClipPlaneWorld[i][0] = -1.0f;
        m_DynamicState.m_UserClipPlaneProj[i][0] = -9999.0f;
        m_DynamicState.m_UserClipPlaneEnabled |= (1 << i);
        SetClipPlane(i, zero);
        EnableClipPlane(i, false);
        Assert(m_DynamicState.m_UserClipPlaneEnabled == 0);
    }
    Assert(m_DynamicState.m_UserClipPlaneChanged == ((1 << g_pHardwareConfig->MaxUserClipPlanes()) - 1));

    m_DynamicState.m_FastClipEnabled = false;
    m_DynamicState.m_bFastClipPlaneChanged = true;

    // User clip override
    m_DynamicState.m_bUserClipTransformOverride = false;
    m_DynamicState.m_UserClipTransform = glm::mat4();

    // Viewport defaults to the window size
    RECT windowRect;
    GetClientRect((HWND)g_pShaderDevice->GetCurrentViewHandle(), &windowRect);

    ShaderViewport_t viewport;
    viewport.Init(windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    SetViewports(1, &viewport);

    // No render mesh
    m_pRenderMesh = 0;

    // Reset cached vertex decl
    m_DynamicState.m_pVertexDecl = NULL;

    // Reset the render target to be the normal backbuffer
    // AcquireInternalRenderTargets();
    SetRenderTarget();

    // Maintain vertex + pixel shader constant buffers
    Vector4D *pVectorPixelShaderConstants = m_DesiredState.m_pVectorPixelShaderConstant;
    int *pBooleanPixelShaderConstants = m_DesiredState.m_pBooleanPixelShaderConstant;
    IntVector4D *pIntegerPixelShaderConstants = m_DesiredState.m_pIntegerPixelShaderConstant;
    Vector4D *pVectorVertexShaderConstants = m_DesiredState.m_pVectorVertexShaderConstant;
    int *pBooleanVertexShaderConstants = m_DesiredState.m_pBooleanVertexShaderConstant;
    IntVector4D *pIntegerVertexShaderConstants = m_DesiredState.m_pIntegerVertexShaderConstant;
    // VK_FIXME: assigning null to Vector4D* will fail assert
    /*
    m_DesiredState = m_DynamicState;
    m_DesiredState.m_pVectorPixelShaderConstant = pVectorPixelShaderConstants;
    m_DesiredState.m_pBooleanPixelShaderConstant = pBooleanPixelShaderConstants;
    m_DesiredState.m_pIntegerPixelShaderConstant = pIntegerPixelShaderConstants;
    m_DesiredState.m_pVectorVertexShaderConstant = pVectorVertexShaderConstants;
    m_DesiredState.m_pBooleanVertexShaderConstant = pBooleanVertexShaderConstants;
    m_DesiredState.m_pIntegerVertexShaderConstant = pIntegerVertexShaderConstants;
    */
    if (g_pHardwareConfig->Caps().m_SupportsPixelShaders)
    {
        if (!bFullReset)
        {
            // Full resets init the values to defaults. Normal resets just leave them dirty.
            if (g_pHardwareConfig->Caps().m_NumVertexShaderConstants != 0)
                SetVertexShaderConstant(0, m_DesiredState.m_pVectorVertexShaderConstant[0].Base(),
                                        IsX360() ? 217 : g_pHardwareConfig->Caps().m_NumVertexShaderConstants,
                                        true); // 217 on X360 to play nice with fast blatting code

            if (g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants != 0)
                SetIntegerVertexShaderConstant(0, (int *)m_DesiredState.m_pIntegerVertexShaderConstant,
                                               g_pHardwareConfig->Caps().m_NumIntegerVertexShaderConstants, true);

            if (g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants != 0)
                SetBooleanVertexShaderConstant(0, m_DesiredState.m_pBooleanVertexShaderConstant,
                                               g_pHardwareConfig->Caps().m_NumBooleanVertexShaderConstants, true);

            if (g_pHardwareConfig->Caps().m_NumPixelShaderConstants != 0)
                SetPixelShaderConstant(0, m_DesiredState.m_pVectorPixelShaderConstant[0].Base(),
                                       g_pHardwareConfig->Caps().m_NumPixelShaderConstants, true);

            if (g_pHardwareConfig->Caps().m_NumIntegerPixelShaderConstants != 0)
                SetIntegerPixelShaderConstant(0, (int *)m_DesiredState.m_pIntegerPixelShaderConstant,
                                              g_pHardwareConfig->Caps().m_NumIntegerPixelShaderConstants, true);

            if (g_pHardwareConfig->Caps().m_NumBooleanPixelShaderConstants != 0)
                SetBooleanPixelShaderConstant(0, m_DesiredState.m_pBooleanPixelShaderConstant,
                                              g_pHardwareConfig->Caps().m_NumBooleanPixelShaderConstants, true);
        }
    }

    // m_bResettingRenderState = false;
}

void CShaderAPIVk::SetDefaultState()
{
    // NOTE: This used to be in the material system, but I want to avoid all the per pass/batch
    // virtual function calls.
    int numTextureStages = g_pHardwareConfig->GetTextureStageCount();

    // FIXME: This is a brutal hack. We only need to load these transforms for fixed-function
    // hardware. Cap the max here to 4.
    if (IsPC())
    {
        numTextureStages = min(numTextureStages, 4);
        int i;
        for (i = 0; i < numTextureStages; i++)
        {
            DisableTextureTransform((TextureStage_t)i);
            MatrixMode((MaterialMatrixMode_t)(MATERIAL_TEXTURE0 + i));
            LoadIdentity();
        }
    }
    MatrixMode(MATERIAL_MODEL);

    Color4ub(255, 255, 255, 255);
    ShadeMode(SHADER_SMOOTH);
    SetVertexShaderIndex();
    SetPixelShaderIndex();

    g_pMeshMgr->MarkUnusedVertexFields(0, 0, NULL);
}

int CShaderAPIVk::GetCurrentDynamicVBSize(void) { return m_nDynamicVBSize; }

void CShaderAPIVk::DestroyVertexBuffers(bool bExitingLevel)
{
    g_pMeshMgr->DestroyVertexBuffers();
    // After a map is shut down, we switch to using smaller dynamic VBs
    // (VGUI shouldn't need much), so that we have more memory free during map loading
    m_nDynamicVBSize = bExitingLevel ? DYNAMIC_VERTEX_BUFFER_MEMORY_SMALL : DYNAMIC_VERTEX_BUFFER_MEMORY;
}

void CShaderAPIVk::SetVertexDecl(VertexFormat_t vertexFormat, bool bHasColorMesh, bool bUsingFlex, bool bUsingMorph)
{
    // VK_TODO
}

void CShaderAPIVk::EvictManagedResources() {}

void CShaderAPIVk::SetAnisotropicLevel(int nAnisotropyLevel) {}

void CShaderAPIVk::SetStandardVertexShaderConstants(float fOverbright) {}

ShaderAPIOcclusionQuery_t CShaderAPIVk::CreateOcclusionQueryObject(void) { return ShaderAPIOcclusionQuery_t(); }

void CShaderAPIVk::DestroyOcclusionQueryObject(ShaderAPIOcclusionQuery_t) {}

void CShaderAPIVk::BeginOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) {}

void CShaderAPIVk::EndOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) {}

int CShaderAPIVk::OcclusionQuery_GetNumPixelsRendered(ShaderAPIOcclusionQuery_t hQuery, bool bFlush) { return 0; }

void CShaderAPIVk::SetFlashlightState(const FlashlightState_t &state, const VMatrix &worldToTexture) {}

void CShaderAPIVk::ClearVertexAndPixelShaderRefCounts() {}

void CShaderAPIVk::PurgeUnusedVertexAndPixelShaders() {}

void CShaderAPIVk::DXSupportLevelChanged() {}

void CShaderAPIVk::EnableUserClipTransformOverride(bool bEnable) {}

void CShaderAPIVk::UserClipTransform(const VMatrix &worldToView) {}

MorphFormat_t CShaderAPIVk::ComputeMorphFormat(int numSnapshots, StateSnapshot_t *pIds) const { return MorphFormat_t(); }

void CShaderAPIVk::SetRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t colorTextureHandle,
                                     ShaderAPITextureHandle_t depthTextureHandle)
{
}

void CShaderAPIVk::CopyRenderTargetToTextureEx(ShaderAPITextureHandle_t textureHandle, int nRenderTargetID, Rect_t *pSrcRect,
                                               Rect_t *pDstRect)
{
}

void CShaderAPIVk::CopyTextureToRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t textureHandle, Rect_t *pSrcRect,
                                               Rect_t *pDstRect)
{
}

void CShaderAPIVk::HandleDeviceLost() {}

void CShaderAPIVk::EnableLinearColorSpaceFrameBuffer(bool bEnable) {}

void CShaderAPIVk::SetFullScreenTextureHandle(ShaderAPITextureHandle_t h) { m_hFullScreenTexture = h; }

void CShaderAPIVk::SetFloatRenderingParameter(int parm_number, float value) {}

void CShaderAPIVk::SetIntRenderingParameter(int parm_number, int value) {}

void CShaderAPIVk::SetVectorRenderingParameter(int parm_number, Vector const &value) {}

float CShaderAPIVk::GetFloatRenderingParameter(int parm_number) const { return 0.0f; }

int CShaderAPIVk::GetIntRenderingParameter(int parm_number) const { return 0; }

Vector CShaderAPIVk::GetVectorRenderingParameter(int parm_number) const { return Vector(); }

void CShaderAPIVk::SetFastClipPlane(const float *pPlane) {}

void CShaderAPIVk::EnableFastClip(bool bEnable) {}