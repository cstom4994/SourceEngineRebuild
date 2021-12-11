//

#ifndef SHADERSHADOWVK_H
#define SHADERSHADOWVK_H

#ifdef _WIN32
#pragma once
#include <windows.h>
#endif

#include "localvktypes.h"
#include "shaderapi/ishadershadow.h"

class CShaderShadowVk : public IShaderShadow
{
  public:
    CShaderShadowVk();
    virtual ~CShaderShadowVk();

    // Initialize render state
    void Init();

    // Sets the default *shadow* state
    void SetDefaultState();

    // Methods related to depth buffering
    void DepthFunc(ShaderDepthFunc_t depthFunc);
    void EnableDepthWrites(bool bEnable);
    void EnableDepthTest(bool bEnable);
    void EnablePolyOffset(PolygonOffsetMode_t nOffsetMode);

    // Methods related to stencil. obsolete
    virtual void EnableStencil(bool bEnable) {}
    virtual void StencilFunc(ShaderStencilFunc_t stencilFunc) {}
    virtual void StencilPassOp(ShaderStencilOp_t stencilOp) {}
    virtual void StencilFailOp(ShaderStencilOp_t stencilOp) {}
    virtual void StencilDepthFailOp(ShaderStencilOp_t stencilOp) {}
    virtual void StencilReference(int nReference) {}
    virtual void StencilMask(int nMask) {}
    virtual void StencilWriteMask(int nMask) {}

    // Suppresses/activates color writing
    void EnableColorWrites(bool bEnable);
    void EnableAlphaWrites(bool bEnable);

    // Methods related to alpha blending
    void EnableBlending(bool bEnable);

    void BlendFunc(ShaderBlendFactor_t srcFactor, ShaderBlendFactor_t dstFactor);
    void BlendOp(ShaderBlendOp_t blendOp);
    void BlendOpSeparateAlpha(ShaderBlendOp_t blendOp);

    // Alpha testing
    void EnableAlphaTest(bool bEnable);
    void AlphaFunc(ShaderAlphaFunc_t alphaFunc, float alphaRef /* [0-1] */);

    // Wireframe/filled polygons
    void PolyMode(ShaderPolyModeFace_t face, ShaderPolyMode_t polyMode);

    // Back face culling
    void EnableCulling(bool bEnable);

    // constant color
    void EnableConstantColor(bool bEnable);

    // Indicates we're going to light the model
    void EnableLighting(bool bEnable);

    // Indicates specular lighting is going to be used
    void EnableSpecular(bool bEnable);

    // Convert from linear to gamma color space on writes to frame buffer.
    void EnableSRGBWrite(bool bEnable);

    // Convert from gamma to linear on texture fetch.
    void EnableSRGBRead(Sampler_t stage, bool bEnable);

    // Set up appropriate shadow filtering state (such as Fetch4 on ATI)
    void SetShadowDepthFiltering(Sampler_t stage);

    // Computes the vertex format
    virtual void VertexShaderVertexFormat(unsigned int nFlags, int nTexCoordCount, int *pTexCoordDimensions, int nUserDataSize);

    // Pixel and vertex shader methods
    virtual void SetVertexShader(const char *pFileName, int nStaticVshIndex);
    virtual void SetPixelShader(const char *pFileName, int nStaticPshIndex);

    // Indicates we're going to be using the ambient cube
    void EnableAmbientLightCubeOnStage0(bool bEnable);

    // Activate/deactivate skinning
    void EnableVertexBlend(bool bEnable);

    // per texture unit stuff
    void OverbrightValue(TextureStage_t stage, float value);
    void EnableTexture(Sampler_t stage, bool bEnable);
    void EnableTexGen(TextureStage_t stage, bool bEnable);
    void TexGen(TextureStage_t stage, ShaderTexGenParam_t param);
    void TextureCoordinate(TextureStage_t stage, int useCoord);

    // alternate method of specifying per-texture unit stuff, more flexible and more complicated
    // Can be used to specify different operation per channel (alpha/color)...
    void EnableCustomPixelPipe(bool bEnable);
    void CustomTextureStages(int stageCount);
    void CustomTextureOperation(TextureStage_t stage, ShaderTexChannel_t channel, ShaderTexOp_t op, ShaderTexArg_t arg1,
                                ShaderTexArg_t arg2);

    // indicates what per-vertex data we're providing
    virtual void DrawFlags(unsigned int drawFlags);

    // A simpler method of dealing with alpha modulation
    void EnableAlphaPipe(bool bEnable);
    void EnableConstantAlpha(bool bEnable);
    void EnableVertexAlpha(bool bEnable);
    void EnableTextureAlpha(TextureStage_t stage, bool bEnable);

    // helper functions
    void EnableSphereMapping(TextureStage_t stage, bool bEnable);

    // Last call to be make before snapshotting
    void ComputeAggregateShadowState();

    // Gets at the shadow state
    const ShadowState_t &GetShadowState();
    const ShadowShaderState_t &GetShadowShaderState();

    // GR - Separate alpha blending
    void EnableBlendingSeparateAlpha(bool bEnable);
    void BlendFuncSeparateAlpha(ShaderBlendFactor_t srcFactor, ShaderBlendFactor_t dstFactor);

    void FogMode(ShaderFogMode_t fogMode);
    void DisableFogGammaCorrection(bool bDisable);

    void SetDiffuseMaterialSource(ShaderMaterialSource_t materialSource);
    virtual void SetMorphFormat(MorphFormat_t flags);

    // Alpha to coverage
    void EnableAlphaToCoverage(bool bEnable);

    bool m_IsTranslucent;
    bool m_IsAlphaTested;
    bool m_bIsDepthWriteEnabled;
    bool m_bUsesVertexAndPixelShaders;

  private:
    struct ShadowTextureStageState_t
    {
        int m_TexCoordIndex;
        int m_TexCoordinate;
        float m_OverbrightVal;
        ShaderTexArg_t m_Arg[2][2];
        ShaderTexOp_t m_Op[2];
        unsigned char m_TexGenEnable : 1;
        unsigned char m_TextureAlphaEnable : 1;
    };

    // Computes the blend factor
    VkBlendFactor BlendFuncValue(ShaderBlendFactor_t factor) const;

    // Computes the blend op
    VkBlendOp BlendOpValue(ShaderBlendOp_t blendOp) const;

    // Configures the FVF vertex shader
    void ConfigureFVFVertexShader(unsigned int flags);
    void ConfigureCustomFVFVertexShader(unsigned int flags);

    // Configures our texture indices
    void ConfigureTextureCoordinates(unsigned int flags);

    // Returns a blend value based on overbrighting
    VkBlendOp OverbrightBlendValue(TextureStage_t stage);

    // Computes a vertex format for the draw flags
    VertexFormat_t FlagsToVertexFormat(int flags) const;

    // Indicates we've got a constant color specified
    bool HasConstantColor() const;

    // Configures the alpha pipe
    void ConfigureAlphaPipe(unsigned int flags);

    // returns true if we're using texture coordinates at a given stage
    bool IsUsingTextureCoordinates(Sampler_t stage) const;

    // Recomputes the tex coord index
    void RecomputeTexCoordIndex(TextureStage_t stage);

    // Separate alpha control?
    bool m_AlphaPipe;

    // Constant color state
    bool m_HasConstantColor;
    bool m_HasConstantAlpha;

    // Vertex color state
    bool m_HasVertexAlpha;

    // funky custom method of specifying shader state
    bool m_CustomTextureStageState;

    // Number of stages used by the custom pipeline
    int m_CustomTextureStages;

    // Number of bones...
    int m_NumBlendVertices;

    // Draw flags
    int m_DrawFlags;

    // Alpha blending...
    VkBlendFactor m_SrcBlend;
    VkBlendFactor m_DestBlend;
    VkBlendOp m_BlendOp;

    // GR - Separate alpha blending...
    VkBlendFactor m_SrcBlendAlpha;
    VkBlendFactor m_DestBlendAlpha;
    VkBlendOp m_BlendOpAlpha;

    // Alpha testing
    VkCompareOp m_AlphaFunc;
    int m_AlphaRef;

    // Stencil
    VkCompareOp m_StencilFunc;
    int m_StencilRef;
    int m_StencilMask;
    DWORD m_StencilFail;
    DWORD m_StencilZFail;
    DWORD m_StencilPass;
    int m_StencilWriteMask;

    // The current shadow state
    ShadowState_t m_ShadowState;
    ShadowShaderState_t m_ShadowShaderState;

    // State info stores with each texture stage
    ShadowTextureStageState_t m_TextureStage[MAX_TEXTURE_STAGES];
    SamplerState_t m_SamplerState[MAX_SAMPLERS];
};

extern CShaderShadowVk *g_pShaderShadow;

#endif // SHADERSHADOWVK_H