//

#ifndef SHADERAPIVK_H
#define SHADERAPIVK_H

#ifdef _WIN32
#pragma once
#include <windows.h>
#endif

// VK_FIXME: changing the order of imports here will lead to
// errors with IDebugTextureInfo function overrides.

// clang-format off
#include "localvktypes.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialinternal.h"
#include "meshvk.h"
#include "shaderapi/ishaderapi.h"
#include "shaderdevicevk.h"
#include "shadershadowvk.h"
#include "materialsystem/idebugtextureinfo.h"
#include "utlstack.h"
// clang-format on

class CShaderAPIVk : public IShaderAPI, public IDebugTextureInfo
{
  public:
    CShaderAPIVk();
    ~CShaderAPIVk();

    bool OnDeviceInit();
    void OnDeviceShutdown();

    // Viewport methods
    void SetViewports(int nCount, const ShaderViewport_t *pViewports) override;
    int GetViewports(ShaderViewport_t *pViewports, int nMax) const override;

    // Buffer clearing
    void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil, int renderTargetWidth, int renderTargetHeight) override;
    void ClearColor3ub(unsigned char r, unsigned char g, unsigned char b) override;
    void ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;

    // Methods related to binding shaders
    void BindVertexShader(VertexShaderHandle_t hVertexShader) override;
    void BindGeometryShader(GeometryShaderHandle_t hGeometryShader) override;
    void BindPixelShader(PixelShaderHandle_t hPixelShader) override;

    // Methods related to state objects
    void SetRasterState(const ShaderRasterState_t &state) override;

    // Sets the mode...
    bool SetMode(void *hWnd, int nAdapter, const ShaderDeviceInfo_t &info) override;

    void ChangeVideoMode(const ShaderDeviceInfo_t &info) override;

    // Returns the snapshot id for the shader state
    StateSnapshot_t TakeSnapshot() override;

    void TexMinFilter(ShaderTexFilterMode_t texFilterMode) override;
    void TexMagFilter(ShaderTexFilterMode_t texFilterMode) override;
    void TexWrap(ShaderTexCoordComponent_t coord, ShaderTexWrapMode_t wrapMode) override;

    void CopyRenderTargetToTexture(ShaderAPITextureHandle_t textureHandle) override;

    // Binds a particular material to render with
    void Bind(IMaterial *pMaterial) override;

    // Flushes any primitives that are buffered
    void FlushBufferedPrimitives() override;
    void FlushBufferedPrimitivesInternal();

    // Gets the dynamic mesh; note that you've got to render the mesh
    // before calling this function a second time. Clients should *not*
    // call DestroyStaticMesh on the mesh returned by this call.
    IMesh *GetDynamicMesh(IMaterial *pMaterial, int nHWSkinBoneCount, bool bBuffered = true, IMesh *pVertexOverride = nullptr,
                          IMesh *pIndexOverride = nullptr) override;
    IMesh *GetDynamicMeshEx(IMaterial *pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount, bool bBuffered = true,
                            IMesh *pVertexOverride = nullptr, IMesh *pIndexOverride = nullptr) override;

    // Methods to ask about particular state snapshots
    bool IsTranslucent(StateSnapshot_t id) const override;
    bool IsAlphaTested(StateSnapshot_t id) const override;
    bool UsesVertexAndPixelShaders(StateSnapshot_t id) const override;
    bool IsDepthWriteEnabled(StateSnapshot_t id) const override;

    // Gets the vertex format for a set of snapshot ids
    VertexFormat_t ComputeVertexFormat(int numSnapshots, StateSnapshot_t *pIds) const override;

    // What fields in the vertex do we actually use?
    VertexFormat_t ComputeVertexUsage(int numSnapshots, StateSnapshot_t *pIds) const override;

    // Draws the mesh
    void DrawMesh(CBaseMeshVk *pMesh);

    // modifies the vertex data when necessary
    void ModifyVertexData();

    // Begins a rendering pass
    void BeginPass(StateSnapshot_t snapshot) override;

    // Renders a single pass of a material
    void RenderPass(int nPass, int nPassCount) override;

    // Set the number of bone weights
    void SetNumBoneWeights(int numBones) override;

    // Sets the lights
    void SetLight(int lightNum, const LightDesc_t &desc) override;

    // Lighting origin for the current model
    void SetLightingOrigin(Vector vLightingOrigin) override;

    void SetAmbientLight(float r, float g, float b) override;
    void SetAmbientLightCube(Vector4D cube[6]) override;

    // The shade mode
    void ShadeMode(ShaderShadeMode_t mode) override;

    // The cull mode
    void CullMode(MaterialCullMode_t cullMode) override;
    void SetCullModeState(bool bEnable, VkCullModeFlags desiredCullMode, VkFrontFace desiredFrontFace);
    void ApplyCullEnable(bool bEnable);
    VkCullModeFlags GetCullMode() const;
    VkFrontFace GetFrontFace() const;

    // Force writes only when z matches. . . useful for stenciling things out
    // by rendering the desired Z values ahead of time.
    void ForceDepthFuncEquals(bool bEnable) override;

    // Forces Z buffering to be on or off
    void OverrideDepthEnable(bool bEnable, bool bDepthEnable) override;

    void SetHeightClipZ(float z) override;
    void SetHeightClipMode(enum MaterialHeightClipMode_t heightClipMode) override;

    void SetClipPlane(int index, const float *pPlane) override;
    void EnableClipPlane(int index, bool bEnable) override;

    // Put all the model matrices into vertex shader constants.
    void SetSkinningMatrices() override;

    // Returns the nearest supported format
    ImageFormat GetNearestSupportedFormat(ImageFormat fmt, bool bFilteringRequired = true) const override;
    ImageFormat GetNearestRenderTargetFormat(ImageFormat fmt) const override;

    // When AA is enabled, render targets are not AA and require a separate
    // depth buffer.
    bool DoRenderTargetsNeedSeparateDepthBuffer() const override;

    // Texture management methods
    // For CreateTexture also see CreateTextures below
    ShaderAPITextureHandle_t CreateTexture(int width, int height, int depth, ImageFormat dstImageFormat, int numMipLevels, int numCopies,
                                           int flags, const char *pDebugName, const char *pTextureGroupName) override;

    void DeleteTexture(ShaderAPITextureHandle_t textureHandle) override;

    ShaderAPITextureHandle_t CreateDepthTexture(ImageFormat renderTargetFormat, int width, int height, const char *pDebugName,
                                                bool bTexture) override;

    bool IsTexture(ShaderAPITextureHandle_t textureHandle) override;
    bool IsTextureResident(ShaderAPITextureHandle_t textureHandle) override;

    // Indicates we're going to be modifying this texture
    // TexImage2D, TexSubImage2D, TexWrap, TexMinFilter, and TexMagFilter
    // all use the texture specified by this function.
    void ModifyTexture(ShaderAPITextureHandle_t textureHandle) override;

    void TexImage2D(int level, int cubeFaceID, ImageFormat dstFormat, int zOffset, int width, int height, ImageFormat srcFormat,
                    bool bSrcIsTiled, // NOTE: for X360 only
                    void *imageData) override;

    void TexSubImage2D(int level, int cubeFaceID, int xOffset, int yOffset, int zOffset, int width, int height, ImageFormat srcFormat,
                       int srcStride,
                       bool bSrcIsTiled, // NOTE: for X360 only
                       void *imageData) override;

    void TexImageFromVTF(IVTFTexture *pVTF, int iVTFFrame) override;

    // An alternate (and faster) way of writing image data
    // (locks the current Modify Texture). Use the pixel writer to write the data
    // after Lock is called
    // Doesn't work for compressed textures
    bool TexLock(int level, int cubeFaceID, int xOffset, int yOffset, int width, int height, CPixelWriter &writer) override;
    void TexUnlock() override;

    // These are bound to the texture
    void TexSetPriority(int priority) override;

    // Sets the texture state
    void BindTexture(Sampler_t sampler, ShaderAPITextureHandle_t textureHandle) override;

    // Set the render target to a texID.
    // Set to SHADER_RENDERTARGET_BACKBUFFER if you want to use the regular framebuffer.
    // Set to SHADER_RENDERTARGET_DEPTHBUFFER if you want to use the regular z buffer.
    void SetRenderTarget(ShaderAPITextureHandle_t colorTextureHandle = SHADER_RENDERTARGET_BACKBUFFER,
                         ShaderAPITextureHandle_t depthTextureHandle = SHADER_RENDERTARGET_DEPTHBUFFER) override;

    // stuff that isn't to be used from within a shader
    void ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) override;
    void ReadPixels(int x, int y, int width, int height, unsigned char *data, ImageFormat dstFormat) override;
    void ReadPixels(Rect_t *pSrcRect, Rect_t *pDstRect, unsigned char *data, ImageFormat dstFormat, int nDstStride) override;

    void FlushHardware() override;

    // Use this to begin and end the frame
    void BeginFrame() override;
    void EndFrame() override;

    // Selection mode methods
    int SelectionMode(bool selectionMode) override;
    void SelectionBuffer(unsigned int *pBuffer, int size) override;
    void ClearSelectionNames() override;
    void LoadSelectionName(int name) override;
    void PushSelectionName(int name) override;
    void PopSelectionName() override;

    // Force the hardware to finish whatever it's doing
    void ForceHardwareSync() override;

    // Used to clear the transition table when we know it's become invalid.
    void ClearSnapshots() override;

    void FogStart(float fStart) override;
    void FogEnd(float fEnd) override;
    void SetFogZ(float fogZ) override;
    // Scene fog state.
    void SceneFogColor3ub(unsigned char r, unsigned char g, unsigned char b) override;
    void GetSceneFogColor(unsigned char *rgb) override;
    void SceneFogMode(MaterialFogMode_t fogMode) override;

    // Can we download textures?
    bool CanDownloadTextures() const override;

    // Initializes vertex and pixel shaders
    void InitVertexAndPixelShaders();

    // Initializes the render state
    void InitRenderState();

    // Queue render state reset next frame
    void QueueResetRenderState();

    // Resets the render state
    void ResetRenderState(bool bFullReset = true) override;

    // We use smaller dynamic VBs during level transitions, to free up memory
    int GetCurrentDynamicVBSize(void) override;
    void DestroyVertexBuffers(bool bExitingLevel = false) override;

    void SetVertexDecl(VertexFormat_t vertexFormat, bool bHasColorMesh, bool bUsingFlex, bool bUsingMorph);

    void EvictManagedResources() override;

    // Level of anisotropic filtering
    void SetAnisotropicLevel(int nAnisotropyLevel) override;

    // For debugging and building recording files. This will stuff a token into the recording file,
    // then someone doing a playback can watch for the token.
    void SyncToken(const char *pToken) override {}

    // Setup standard vertex shader constants (that don't change)
    // This needs to be called anytime that overbright changes.
    void SetStandardVertexShaderConstants(float fOverbright) override;

    //
    // Occlusion query support
    //

    // Allocate and delete query objects.
    ShaderAPIOcclusionQuery_t CreateOcclusionQueryObject(void) override;
    void DestroyOcclusionQueryObject(ShaderAPIOcclusionQuery_t) override;

    // Bracket drawing with begin and end so that we can get counts next frame.
    void BeginOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) override;
    void EndOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) override;

    // OcclusionQuery_GetNumPixelsRendered
    //	Get the number of pixels rendered between begin and end on an earlier frame.
    //	Calling this in the same frame is a huge perf hit!
    // Returns iQueryResult:
    //	iQueryResult >= 0					-	iQueryResult is the number of pixels rendered
    //	OCCLUSION_QUERY_RESULT_PENDING		-	query results are not available yet
    //	OCCLUSION_QUERY_RESULT_ERROR		-	query failed
    // Use OCCLUSION_QUERY_FINISHED( iQueryResult ) to test if query finished.
    int OcclusionQuery_GetNumPixelsRendered(ShaderAPIOcclusionQuery_t hQuery, bool bFlush = false) override;

    void SetFlashlightState(const FlashlightState_t &state, const VMatrix &worldToTexture) override;

    void ClearVertexAndPixelShaderRefCounts() override;
    void PurgeUnusedVertexAndPixelShaders() override;

    // Called when the dx support level has changed
    void DXSupportLevelChanged() override;

    // By default, the material system applies the VIEW and PROJECTION matrices	to the user clip
    // planes (which are specified in world space) to generate projection-space user clip planes
    // Occasionally (for the particle system in hl2, for example), we want to override that
    // behavior and explictly specify a View transform for user clip planes. The PROJECTION
    // will be mutliplied against this instead of the normal VIEW matrix.
    void EnableUserClipTransformOverride(bool bEnable) override;
    void UserClipTransform(const VMatrix &worldToView) override;

    // ----------------------------------------------------------------------------------
    // Everything after this point added after HL2 shipped.
    // ----------------------------------------------------------------------------------

    // What fields in the morph do we actually use?
    MorphFormat_t ComputeMorphFormat(int numSnapshots, StateSnapshot_t *pIds) const override;

    // Set the render target to a texID.
    // Set to SHADER_RENDERTARGET_BACKBUFFER if you want to use the regular framebuffer.
    // Set to SHADER_RENDERTARGET_DEPTHBUFFER if you want to use the regular z buffer.
    void SetRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t colorTextureHandle = SHADER_RENDERTARGET_BACKBUFFER,
                           ShaderAPITextureHandle_t depthTextureHandle = SHADER_RENDERTARGET_DEPTHBUFFER) override;

    void CopyRenderTargetToTextureEx(ShaderAPITextureHandle_t textureHandle, int nRenderTargetID, Rect_t *pSrcRect = NULL,
                                     Rect_t *pDstRect = NULL) override;
    void CopyTextureToRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t textureHandle, Rect_t *pSrcRect = NULL,
                                     Rect_t *pDstRect = NULL) override;

    // For dealing with device lost in cases where SwapBuffers isn't called all the time (Hammer)
    void HandleDeviceLost() override;

    void EnableLinearColorSpaceFrameBuffer(bool bEnable) override;

    // Lets the shader know about the full-screen texture so it can
    void SetFullScreenTextureHandle(ShaderAPITextureHandle_t h) override;

    // Rendering parameters control special drawing modes withing the material system, shader
    // system, shaders, and engine. renderparm.h has their definitions.
    void SetFloatRenderingParameter(int parm_number, float value) override;
    void SetIntRenderingParameter(int parm_number, int value) override;
    void SetVectorRenderingParameter(int parm_number, Vector const &value) override;

    float GetFloatRenderingParameter(int parm_number) const override;
    int GetIntRenderingParameter(int parm_number) const override;
    Vector GetVectorRenderingParameter(int parm_number) const override;

    void SetFastClipPlane(const float *pPlane) override;
    void EnableFastClip(bool bEnable) override;

    // Returns the number of vertices + indices we can render using the dynamic mesh
    // Passing true in the second parameter will return the max # of vertices + indices
    // we can use before a flush is provoked and may return different values
    // if called multiple times in succession.
    // Passing false into the second parameter will return
    // the maximum possible vertices + indices that can be rendered in a single batch
    void GetMaxToRender(IMesh *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices) override;

    // Returns the max number of vertices we can render for a given material
    int GetMaxVerticesToRender(IMaterial *pMaterial) override;
    int GetMaxIndicesToRender() override;

    // stencil methods
    void SetStencilEnable(bool onoff) override;
    void SetStencilFailOperation(StencilOperation_t op) override;
    void SetStencilZFailOperation(StencilOperation_t op) override;
    void SetStencilPassOperation(StencilOperation_t op) override;
    void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) override;
    void SetStencilReferenceValue(int ref) override;
    void SetStencilTestMask(uint32 msk) override;
    void SetStencilWriteMask(uint32 msk) override;
    void ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) override;

    // disables all local lights
    void DisableAllLocalLights() override;
    int CompareSnapshots(StateSnapshot_t snapshot0, StateSnapshot_t snapshot1) override;

    IMesh *GetFlexMesh() override;

    void SetFlashlightStateEx(const FlashlightState_t &state, const VMatrix &worldToTexture, ITexture *pFlashlightDepthTexture) override;

    bool SupportsMSAAMode(int nMSAAMode) override;

    bool OwnGPUResources(bool bEnable) override;

    // get fog distances entered with FogStart(), FogEnd(), and SetFogZ()
    void GetFogDistances(float *fStart, float *fEnd, float *fFogZ) override;

    // Hooks for firing PIX events from outside the Material System...
    void BeginPIXEvent(unsigned long color, const char *szName) override;
    void EndPIXEvent() override;
    void SetPIXMarker(unsigned long color, const char *szName) override;

    // Enables and disables for Alpha To Coverage
    void EnableAlphaToCoverage() override;
    void DisableAlphaToCoverage() override;

    // Computes the vertex buffer pointers
    void ComputeVertexDescription(unsigned char *pBuffer, VertexFormat_t vertexFormat, MeshDesc_t &desc) const override;

    bool SupportsShadowDepthTextures(void) override;

    void SetDisallowAccess(bool) override;
    void EnableShaderShaderMutex(bool) override;
    void ShaderLock() override;
    void ShaderUnlock() override;

    ImageFormat GetShadowDepthTextureFormat(void) override;

    bool SupportsFetch4(void) override;
    void SetShadowDepthBiasFactors(float fShadowSlopeScaleDepthBias, float fShadowDepthBias) override;

    // ------------ New Vertex/Index Buffer interface ----------------------------
    void BindVertexBuffer(int nStreamID, IVertexBuffer *pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount,
                          VertexFormat_t fmt, int nRepetitions = 1) override;
    void BindIndexBuffer(IIndexBuffer *pIndexBuffer, int nOffsetInBytes) override;
    void Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount) override;
    // ------------ End ----------------------------

    // Apply stencil operations to every pixel on the screen without disturbing depth or color buffers
    void PerformFullScreenStencilOperation(void) override;

    void SetScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor) override;

    // nVidia CSAA modes, different from SupportsMSAAMode()
    bool SupportsCSAAMode(int nNumSamples, int nQualityLevel) override;

    // Notifies the shaderapi to invalidate the current set of delayed constants because we just finished a draw pass.
    // Either actual or not.
    void InvalidateDelayedShaderConstants(void) override;

    // Gamma<->Linear conversions according to the video hardware we're running on
    float GammaToLinear_HardwareSpecific(float fGamma) const override;
    float LinearToGamma_HardwareSpecific(float fLinear) const override;

    // Set's the linear->gamma conversion textures to use for this hardware for both srgb writes enabled and
    // disabled(identity)
    void SetLinearToGammaConversionTextures(ShaderAPITextureHandle_t hSRGBWriteEnabledTexture,
                                            ShaderAPITextureHandle_t hIdentityTexture) override;

    ImageFormat GetNullTextureFormat(void) override;

    void BindVertexTexture(VertexTextureSampler_t nSampler, ShaderAPITextureHandle_t textureHandle) override;

    // Enables hardware morphing
    void EnableHWMorphing(bool bEnable) override;

    // Sets flexweights for rendering
    void SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t *pWeights) override;

    void FogMaxDensity(float flMaxDensity) override;

    // Create a multi-frame texture (equivalent to calling "CreateTexture" multiple times, but more efficient)
    void CreateTextures(ShaderAPITextureHandle_t *pHandles, int count, int width, int height, int depth, ImageFormat dstImageFormat,
                        int numMipLevels, int numCopies, int flags, const char *pDebugName, const char *pTextureGroupName) override;

    void AcquireThreadOwnership() override;
    void ReleaseThreadOwnership() override;

    bool SupportsNormalMapCompression() const override;

    // Only does anything on XBox360. This is useful to eliminate stalls
    void EnableBuffer2FramesAhead(bool bEnable) override;

    void SetDepthFeatheringPixelShaderConstant(int iConstant, float fDepthBlendScale) override;

    // debug logging
    // only implemented in some subclasses
    void PrintfVA(char *fmt, va_list vargs) override;
    void Printf(PRINTF_FORMAT_STRING const char *fmt, ...) override;
    float Knob(char *knobname, float *setvalue = NULL) override;
    // Allows us to override the alpha write setting of a material
    void OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable) override;
    void OverrideColorWriteEnable(bool bOverrideEnable, bool bColorWriteEnable) override;

    // extended clear buffers function with alpha independent from color
    void ClearBuffersObeyStencilEx(bool bClearColor, bool bClearAlpha, bool bClearDepth) override;

    // Allows copying a render target to another texture by specifying them both.
    void CopyRenderTargetToScratchTexture(ShaderAPITextureHandle_t srcRt, ShaderAPITextureHandle_t dstTex, Rect_t *pSrcRect = NULL,
                                          Rect_t *pDstRect = NULL) override;

    // Allows locking and unlocking of very specific surface types.
    void LockRect(void **pOutBits, int *pOutPitch, ShaderAPITextureHandle_t texHandle, int mipmap, int x, int y, int w, int h, bool bWrite,
                  bool bRead) override;
    void UnlockRect(ShaderAPITextureHandle_t texHandle, int mipmap) override;

    // ---------- Dynamic Shader API ------------
    // returns the current time in seconds....
    double CurrentTime() const override
    {
        // FIXME: Return game time instead of real time!
        // Or eliminate this altogether and put it into a material var
        // (this is used by vertex modifiers in shader code at the moment)
        return Plat_FloatTime();
    };

    // Gets the lightmap dimensions
    void GetLightmapDimensions(int *w, int *h) override;

    // Scene fog state.
    // This is used by the shaders for picking the proper vertex shader for fogging based on dynamic state.
    MaterialFogMode_t GetSceneFogMode() override;

    // stuff related to matrix stacks
    void MatrixMode(MaterialMatrixMode_t matrixMode) override;
    void PushMatrix() override;
    void PopMatrix() override;
    void LoadMatrix(float *m) override;
    void MultMatrix(float *m) override;
    void MultMatrixLocal(float *m) override;
    void GetMatrix(MaterialMatrixMode_t matrixMode, float *dst) override;
    void LoadIdentity(void) override;
    void LoadCameraToWorld(void) override;
    void Ortho(double left, double right, double bottom, double top, double zNear, double zFar) override;
    void PerspectiveX(double fovx, double aspect, double zNear, double zFar) override;
    void PickMatrix(int x, int y, int width, int height) override;
    void Rotate(float angle, float x, float y, float z) override;
    void Translate(float x, float y, float z) override;
    void Scale(float x, float y, float z) override;
    void ScaleXY(float x, float y) override;

    // Sets the color to modulate by
    void Color3f(float r, float g, float b) override;
    void Color3fv(float const *pColor) override;
    void Color4f(float r, float g, float b, float a) override;
    void Color4fv(float const *pColor) override;

    void Color3ub(unsigned char r, unsigned char g, unsigned char b) override;
    void Color3ubv(unsigned char const *pColor) override;
    void Color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
    void Color4ubv(unsigned char const *pColor) override;

    // Sets the constant register for vertex and pixel shaders
    void SetVertexShaderConstant(int var, float const *pVec, int numConst = 1, bool bForce = false) override;
    void SetPixelShaderConstant(int var, float const *pVec, int numConst = 1, bool bForce = false) override;

    // Sets the default *dynamic* state
    void SetDefaultState() override;

    // Get the current camera position in world space.
    void GetWorldSpaceCameraPosition(float *pPos) const override;

    int GetCurrentNumBones(void) const override;
    int GetCurrentLightCombo(void) const override;

    MaterialFogMode_t GetCurrentFogType(void) const override;

    // Flushes the matrix state, returns false if we don't need to
    // do any more work
    bool MatrixIsChanging(TransformType_t type = TRANSFORM_IS_GENERAL);

    // Updates the matrix transform state
    void UpdateMatrixTransform(TransformType_t type = TRANSFORM_IS_GENERAL);

    // fixme: move this to shadow state
    void SetTextureTransformDimension(TextureStage_t textureStage, int dimension, bool projected) override;
    void DisableTextureTransform(TextureStage_t textureStage) override;
    void SetBumpEnvMatrix(TextureStage_t textureStage, float m00, float m01, float m10, float m11) override;

    int GetCurrentFrameCounter(void) const { return m_CurrentFrame; }

    // Sets the vertex and pixel shaders
    void SetVertexShaderIndex(int vshIndex = -1) override;
    void SetPixelShaderIndex(int pshIndex = 0) override;

    // Get the dimensions of the back buffer.
    void GetBackBufferDimensions(int &width, int &height) const override;

    // FIXME: The following 6 methods used to live in IShaderAPI
    // and were moved for stdshader_dx8. Let's try to move them back!

    // Get the lights
    int GetMaxLights(void) const override;
    const LightDesc_t &GetLight(int lightNum) const override;

    void SetPixelShaderFogParams(int reg) override;

    // Render state for the ambient light cube
    void SetVertexShaderStateAmbientLightCube() override;
    void SetPixelShaderStateAmbientLightCube(int pshReg, bool bForceToBlack = false) override;
    void CommitPixelShaderLighting(int pshReg) override;

    // Use this to get the mesh builder that allows us to modify vertex data
    CMeshBuilder *GetVertexModifyBuilder() override;
    bool InFlashlightMode() const override;
    const FlashlightState_t &GetFlashlightState(VMatrix &worldToTexture) const override;
    bool InEditorMode() const override;

    // Gets the bound morph's vertex format; returns 0 if no morph is bound
    MorphFormat_t GetBoundMorphFormat() override;

    // Measures fill rate
    void ComputeFillRate();

    // Selection mode methods
    bool IsInSelectionMode() { return m_InSelectionMode; }

    // We hit somefin in selection mode
    void RegisterSelectionHit(float minz, float maxz);

    // Get the currently bound material
    IMaterial *GetBoundMaterial() { return m_pMaterial; }

    // Binds a standard texture
    void BindStandardTexture(Sampler_t sampler, StandardTextureId_t id) override;

    ITexture *GetRenderTargetEx(int nRenderTargetID) override;

    void SetToneMappingScaleLinear(const Vector &scale) override;
    const Vector &GetToneMappingScaleLinear(void) const override;
    float GetLightMapScaleFactor(void) const override;

    void LoadBoneMatrix(int boneIndex, const float *m) override;

    void PerspectiveOffCenterX(double fovx, double aspect, double zNear, double zFar, double bottom, double top, double left,
                               double right) override;

    void GetDXLevelDefaults(uint &max_dxlevel, uint &recommended_dxlevel) override;

    const FlashlightState_t &GetFlashlightStateEx(VMatrix &worldToTexture, ITexture **pFlashlightDepthTexture) const override;

    float GetAmbientLightCubeLuminance() override;

    void GetDX9LightState(LightState_t *state) const override;
    int GetPixelFogCombo() override; // 0 is either range fog, or no fog simulated with rigged range fog values. 1 is height fog

    void BindStandardVertexTexture(VertexTextureSampler_t sampler, StandardTextureId_t id) override;

    // Is hardware morphing enabled?
    bool IsHWMorphingEnabled() const override;

    void GetStandardTextureDimensions(int *pWidth, int *pHeight, StandardTextureId_t id) override;

    void SetBooleanVertexShaderConstant(int var, BOOL const *pVec, int numBools = 1, bool bForce = false) override;
    void SetIntegerVertexShaderConstant(int var, int const *pVec, int numIntVecs = 1, bool bForce = false) override;
    void SetBooleanPixelShaderConstant(int var, BOOL const *pVec, int numBools = 1, bool bForce = false) override;
    void SetIntegerPixelShaderConstant(int var, int const *pVec, int numIntVecs = 1, bool bForce = false) override;

    // Are we in a configuration that needs access to depth data through the alpha channel later?
    bool ShouldWriteDepthToDestAlpha(void) const override;

    // deformations
    void PushDeformation(DeformationBase_t const *Deformation) override;
    void PopDeformation() override;
    int GetNumActiveDeformations() const override;

    // for shaders to set vertex shader constants. returns a packed state which can be used to set
    // the dynamic combo. returns # of active deformations
    int GetPackedDeformationInformation(int nMaskOfUnderstoodDeformations, float *pConstantValuesOut, int nBufferSize,
                                        int nMaximumDeformations, int *pNumDefsOut) const override;

    // This lets the lower level system that certain vertex fields requested
    // in the shadow state aren't actually being read given particular state
    // known only at dynamic state time. It's here only to silence warnings.
    void MarkUnusedVertexFields(unsigned int nFlags, int nTexCoordCount, bool *pUnusedTexCoords) override;

    void ExecuteCommandBuffer(uint8 *pCmdBuffer) override;

    // interface for mat system to tell shaderapi about standard texture handles
    void SetStandardTextureHandle(StandardTextureId_t nId, ShaderAPITextureHandle_t nHandle) override;

    // Interface for mat system to tell shaderapi about color correction
    void GetCurrentColorCorrection(ShaderColorCorrectionInfo_t *pInfo) override;

    void SetPSNearAndFarZ(int pshReg) override;

    // -------- Debug Texture Info ---------
    // Use this to turn on the mode where it builds the debug texture list.
    // At the end of the next frame, GetDebugTextureList() will return a valid list of the textures.
    void EnableDebugTextureList(bool bEnable) override;

    // If this is on, then it will return all textures that exist, not just the ones that were bound in the last frame.
    // It is required to enable debug texture list to get this.
    void EnableGetAllTextures(bool bEnable) override;

    // Use this to get the results of the texture list.
    // Do NOT release the KeyValues after using them.
    // There will be a bunch of subkeys, each with these values:
    //    Name   - the texture's filename
    //    Binds  - how many times the texture was bound
    //    Format - ImageFormat of the texture
    //    Width  - Width of the texture
    //    Height - Height of the texture
    // It is required to enable debug texture list to get this.
    KeyValues *GetDebugTextureList() override;

    // This returns how much memory was used.
    int GetTextureMemoryUsed(TextureMemoryType eTextureMemory) override;

    // Use this to determine if texture debug info was computed within last numFramesAllowed frames.
    bool IsDebugTextureListFresh(int numFramesAllowed = 1) override;

    // Enable debug texture rendering when texture binds should not count towards textures
    // used during a frame. Returns the old state of debug texture rendering flag to use
    // it for restoring the mode.
    bool SetDebugTextureRendering(bool bEnable) override;

    void ComputePolyOffsetMatrix(const glm::mat4x4 &matProjection, glm::mat4x4 &matProjectionOffset);

    // Compute and save the world space camera position.
    void CacheWorldSpaceCameraPosition();

    // Compute and save the projection matrix with polyoffset built in if we need it.
    void CachePolyOffsetProjectionMatrix();

    glm::mat4x4 GetProjectionMatrix();

    // Mark all user clip planes as being dirty
    void MarkAllUserClipPlanesDirty();

    // Gets at a particular transform
    glm::mat4x4 GetTransform(int i) { return m_MatrixStack[i].GetTop(); }

#ifdef TF
    void TexLodClamp(int finest) override;

    void TexLodBias(float bias) override;

    void CopyTextureToTexture( ShaderAPITextureHandle_t srcTex, ShaderAPITextureHandle_t dstTex ) override;
#endif

  private:
    ShaderAPITextureHandle_t m_hFullScreenTexture;
    ShaderAPITextureHandle_t m_hLinearToGammaTableTexture;
    ShaderAPITextureHandle_t m_hLinearToGammaTableIdentityTexture;

    //
    // State needed at the time of rendering (after snapshots have been applied)
    //

    MatrixStack m_MatrixStack[NUM_MATRIX_MODES];
    matrix3x4_t m_boneMatrix[NUM_MODEL_TRANSFORMS];
    int m_maxBoneLoaded;

    // Current matrix mode
    /*D3DTRANSFORMSTATETYPE*/ int m_MatrixMode;
    int m_CurrStack;

    // The current camera position in world space.
    Vector4D m_WorldSpaceCameraPosition;

    // The current projection matrix with polyoffset baked into it.
    glm::mat4x4 m_CachedPolyOffsetProjectionMatrix;
    glm::mat4x4 m_CachedFastClipProjectionMatrix;
    glm::mat4x4 m_CachedFastClipPolyOffsetProjectionMatrix;

    // The texture stage state that changes frequently
    DynamicState_t m_DynamicState;

    // The *desired* dynamic state. Most dynamic state is committed into actual hardware state
    // at either per-pass or per-material time.	This can also be used to force the hardware
    // to match the desired state after returning from alt-tab.
    DynamicState_t m_DesiredState;

    // Render data
    CBaseMeshVk *m_pRenderMesh;
    int m_nDynamicVBSize;
    IMaterialInternal *m_pMaterial;

    // Selection name stack
    CUtlStack<int> m_SelectionNames;
    bool m_InSelectionMode;
    unsigned int *m_pSelectionBufferEnd;
    unsigned int *m_pSelectionBuffer;
    unsigned int *m_pCurrSelectionRecord;
    float m_SelectionMinZ;
    float m_SelectionMaxZ;
    int m_NumHits;

    // Shadow depth bias states
    float m_fShadowSlopeScaleDepthBias;
    float m_fShadowDepthBias;

    bool m_bReadPixelsEnabled;

    // Render-to-texture stuff...
    bool m_UsingTextureRenderTarget;

    int m_ViewportMaxWidth;
    int m_ViewportMaxHeight;

    ShaderAPITextureHandle_t m_hCachedRenderTarget;
    bool m_bUsingSRGBRenderTarget;

    // Ambient cube map ok?
    int m_CachedAmbientLightCube;

    // The current frame
    int m_CurrentFrame;

    bool m_bEnableDebugTextureList;
    bool m_bDebugGetAllTextures;
    bool m_bDebugTexturesRendering;
    KeyValues *m_pDebugTextureList;
    int m_nTextureMemoryUsedLastFrame, m_nTextureMemoryUsedTotal;
    int m_nTextureMemoryUsedPicMip1, m_nTextureMemoryUsedPicMip2;
    int m_nDebugDataExportFrame;

    bool m_bResetRenderStateNeeded;

    StateSnapshot_t m_nCurrentSnapshot;

    enum
    {
        TRANSLUCENT = 0x1,
        ALPHATESTED = 0x2,
        VERTEX_AND_PIXEL_SHADERS = 0x4,
        DEPTHWRITE = 0x8,
    };
};

extern CShaderAPIVk *g_pShaderAPI;

inline CShaderAPIVk *ShaderAPI() { return g_pShaderAPI; }

#endif // SHADERAPIVK_H