#include "shaderapi/ishaderutil.h"
#include "shadermanagervk.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// VK_TODO:
// a lot of the VkBlendOps and VkBlendFactors in this file are probably incorrect,
// or not equivalent to their dx counterparts.

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
static CShaderShadowVk g_ShaderShadowVk;
CShaderShadowVk *g_pShaderShadow = &g_ShaderShadowVk;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderShadowVk, IShaderShadow, SHADERSHADOW_INTERFACE_VERSION, g_ShaderShadowVk)

CShaderShadowVk::CShaderShadowVk()
{
    m_IsTranslucent = false;
    m_IsAlphaTested = false;
    m_bIsDepthWriteEnabled = true;
    m_bUsesVertexAndPixelShaders = false;
    m_HasConstantColor = false;
    memset(&m_ShadowState, 0, sizeof(m_ShadowState));
    memset(&m_TextureStage, 0, sizeof(m_TextureStage));
}

CShaderShadowVk::~CShaderShadowVk() {}

//-----------------------------------------------------------------------------
// Initialize render state
//-----------------------------------------------------------------------------
void CShaderShadowVk::Init()
{
    // Clear out the shadow state
    memset(&m_ShadowState, 0, sizeof(m_ShadowState));

    // No funky custom methods..
    m_CustomTextureStageState = false;

    // No constant color modulation
    m_HasConstantColor = false;
    m_HasConstantAlpha = false;
    m_HasVertexAlpha = false;

    m_ShadowShaderState.m_ModulateConstantColor = false;

    m_ShadowState.m_bDisableFogGammaCorrection = false;

    // By default we're using fixed function
    m_ShadowState.m_UsingFixedFunction = true;

    // Lighting off by default
    m_ShadowState.m_Lighting = false;

    // Pixel + vertex shaders
    m_ShadowShaderState.m_VertexShader = INVALID_SHADER;
    m_ShadowShaderState.m_PixelShader = INVALID_SHADER;
    m_ShadowShaderState.m_nStaticPshIndex = 0;
    m_ShadowShaderState.m_nStaticVshIndex = 0;
    m_ShadowShaderState.m_VertexUsage = 0;

    // Drawing nothing..
    m_DrawFlags = 0;

    // No alpha control
    m_AlphaPipe = false;

    // Vertex blending
    m_NumBlendVertices = 0;
    m_ShadowState.m_VertexBlendEnable = false;

    // NOTE: If you change these defaults, change the code in ComputeAggregateShadowState + CreateTransitionTableEntry
    int i;
    for (i = 0; i < MAX_TEXTURE_STAGES; ++i)
    {
        m_ShadowState.m_TextureStage[i].m_ColorOp = VK_BLEND_OP_ADD;
        m_ShadowState.m_TextureStage[i].m_ColorArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
        m_ShadowState.m_TextureStage[i].m_ColorArg2 = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_ADD;
        m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_ONE;
        m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_ZERO;
        m_ShadowState.m_TextureStage[i].m_TexCoordIndex = i;
    }

    for (i = 0; i < MAX_SAMPLERS; ++i)
    {
        m_ShadowState.m_SamplerState[i].m_TextureEnable = false;
        m_ShadowState.m_SamplerState[i].m_SRGBReadEnable = false;
        m_ShadowState.m_SamplerState[i].m_Fetch4Enable = false;
        // A *real* measure if the texture stage is being used.
        // we sometimes have to set the shadow state to not mirror this.
        m_SamplerState[i].m_TextureEnable = false;
    }
}

// Sets the default *shadow* state
void CShaderShadowVk::SetDefaultState()
{
    DepthFunc(SHADER_DEPTHFUNC_NEAREROREQUAL);
    EnableDepthWrites(true);
    EnableDepthTest(true);
    EnableColorWrites(true);
    EnableAlphaWrites(false);
    EnableAlphaTest(false);
    EnableLighting(false);
    EnableConstantColor(false);
    EnableBlending(false);
    BlendFunc(SHADER_BLEND_ONE, SHADER_BLEND_ZERO);
    BlendOp(SHADER_BLEND_OP_ADD);
    // GR - separate alpha
    EnableBlendingSeparateAlpha(false);
    BlendFuncSeparateAlpha(SHADER_BLEND_ONE, SHADER_BLEND_ZERO);
    BlendOpSeparateAlpha(SHADER_BLEND_OP_ADD);
    AlphaFunc(SHADER_ALPHAFUNC_GEQUAL, 0.7f);
    PolyMode(SHADER_POLYMODEFACE_FRONT_AND_BACK, SHADER_POLYMODE_FILL);
    EnableCulling(true);
    EnableAlphaToCoverage(false);
    EnablePolyOffset(SHADER_POLYOFFSET_DISABLE);
    EnableVertexBlend(false);
    EnableSpecular(false);
    EnableSRGBWrite(false);
    DrawFlags(SHADER_DRAW_POSITION);
    EnableCustomPixelPipe(false);
    CustomTextureStages(0);
    EnableAlphaPipe(false);
    EnableConstantAlpha(false);
    EnableVertexAlpha(false);
    SetVertexShader(NULL, 0);
    SetPixelShader(NULL, 0);
    FogMode(SHADER_FOGMODE_DISABLED);
    DisableFogGammaCorrection(false);
    SetDiffuseMaterialSource(SHADER_MATERIALSOURCE_MATERIAL);
    EnableStencil(false);
    StencilFunc(SHADER_STENCILFUNC_ALWAYS);
    StencilPassOp(SHADER_STENCILOP_KEEP);
    StencilFailOp(SHADER_STENCILOP_KEEP);
    StencilDepthFailOp(SHADER_STENCILOP_KEEP);
    StencilReference(0);
    StencilMask(0xFFFFFFFF);
    StencilWriteMask(0xFFFFFFFF);
    m_ShadowShaderState.m_VertexUsage = 0;

    int i;
    int nSamplerCount = MAX_SAMPLERS;
    for (i = 0; i < nSamplerCount; i++)
    {
        EnableTexture((Sampler_t)i, false);
        EnableSRGBRead((Sampler_t)i, false);
    }

    int nTextureStageCount = MAX_TEXTURE_STAGES;
    for (i = 0; i < nTextureStageCount; i++)
    {
        EnableTexGen((TextureStage_t)i, false);
        OverbrightValue((TextureStage_t)i, 1.0f);
        EnableTextureAlpha((TextureStage_t)i, false);
        CustomTextureOperation((TextureStage_t)i, SHADER_TEXCHANNEL_COLOR, SHADER_TEXOP_DISABLE, SHADER_TEXARG_TEXTURE,
                               SHADER_TEXARG_PREVIOUSSTAGE);
        CustomTextureOperation((TextureStage_t)i, SHADER_TEXCHANNEL_ALPHA, SHADER_TEXOP_DISABLE, SHADER_TEXARG_TEXTURE,
                               SHADER_TEXARG_PREVIOUSSTAGE);
    }
}

//-----------------------------------------------------------------------------
// Gets at the shadow state
//-----------------------------------------------------------------------------
const ShadowState_t &CShaderShadowVk::GetShadowState() { return m_ShadowState; }

const ShadowShaderState_t &CShaderShadowVk::GetShadowShaderState() { return m_ShadowShaderState; }

//-----------------------------------------------------------------------------
// Depth functions...
//-----------------------------------------------------------------------------
void CShaderShadowVk::DepthFunc(ShaderDepthFunc_t depthFunc)
{
    VkCompareOp zFunc;

    switch (depthFunc)
    {
    case SHADER_DEPTHFUNC_NEVER:
        zFunc = VK_COMPARE_OP_NEVER;
        break;
    case SHADER_DEPTHFUNC_NEARER:
        zFunc = VK_COMPARE_OP_LESS;
        break;
    case SHADER_DEPTHFUNC_EQUAL:
        zFunc = VK_COMPARE_OP_EQUAL;
        break;
    case SHADER_DEPTHFUNC_NEAREROREQUAL:
        zFunc = VK_COMPARE_OP_LESS_OR_EQUAL;
        break;
    case SHADER_DEPTHFUNC_FARTHER:
        zFunc = VK_COMPARE_OP_GREATER;
        break;
    case SHADER_DEPTHFUNC_NOTEQUAL:
        zFunc = VK_COMPARE_OP_NOT_EQUAL;
        break;
    case SHADER_DEPTHFUNC_FARTHEROREQUAL:
        zFunc = VK_COMPARE_OP_GREATER_OR_EQUAL;
        break;
    case SHADER_DEPTHFUNC_ALWAYS:
        zFunc = VK_COMPARE_OP_ALWAYS;
        break;
    default:
        zFunc = VK_COMPARE_OP_ALWAYS;
        Warning("DepthFunc: invalid param\n");
        break;
    }

    m_ShadowState.m_ZFunc = zFunc;
}

void CShaderShadowVk::EnableDepthWrites(bool bEnable) { m_ShadowState.m_ZWriteEnable = bEnable; }

void CShaderShadowVk::EnableDepthTest(bool bEnable) { m_ShadowState.m_ZEnable = bEnable ? true : false; }

void CShaderShadowVk::EnablePolyOffset(PolygonOffsetMode_t nOffsetMode) { m_ShadowState.m_ZBias = nOffsetMode; }

//-----------------------------------------------------------------------------
// Color write state
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableColorWrites(bool bEnable)
{
    if (bEnable)
    {
        m_ShadowState.m_ColorWriteEnable |= VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_R_BIT;
    }
    else
    {
        m_ShadowState.m_ColorWriteEnable &= ~(VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_R_BIT);
    }
}

void CShaderShadowVk::EnableAlphaWrites(bool bEnable)
{
    if (bEnable)
    {
        m_ShadowState.m_ColorWriteEnable |= VK_COLOR_COMPONENT_A_BIT;
    }
    else
    {
        m_ShadowState.m_ColorWriteEnable &= ~VK_COLOR_COMPONENT_A_BIT;
    }
}

//-----------------------------------------------------------------------------
// Alpha blending states
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableBlending(bool bEnable) { m_ShadowState.m_AlphaBlendEnable = bEnable; }

// GR - separate alpha
void CShaderShadowVk::EnableBlendingSeparateAlpha(bool bEnable) { m_ShadowState.m_SeparateAlphaBlendEnable = bEnable; }

void CShaderShadowVk::EnableAlphaTest(bool bEnable) { m_ShadowState.m_AlphaTestEnable = bEnable; }

void CShaderShadowVk::AlphaFunc(ShaderAlphaFunc_t alphaFunc, float alphaRef /* [0-1] */)
{
    VkCompareOp cmpFunc;

    switch (alphaFunc)
    {
    case SHADER_ALPHAFUNC_NEVER:
        cmpFunc = VK_COMPARE_OP_NEVER;
        break;
    case SHADER_ALPHAFUNC_LESS:
        cmpFunc = VK_COMPARE_OP_LESS;
        break;
    case SHADER_ALPHAFUNC_EQUAL:
        cmpFunc = VK_COMPARE_OP_EQUAL;
        break;
    case SHADER_ALPHAFUNC_LEQUAL:
        cmpFunc = VK_COMPARE_OP_LESS_OR_EQUAL;
        break;
    case SHADER_ALPHAFUNC_GREATER:
        cmpFunc = VK_COMPARE_OP_GREATER_OR_EQUAL;
        break;
    case SHADER_ALPHAFUNC_NOTEQUAL:
        cmpFunc = VK_COMPARE_OP_NOT_EQUAL;
        break;
    case SHADER_ALPHAFUNC_GEQUAL:
        cmpFunc = VK_COMPARE_OP_GREATER_OR_EQUAL;
        break;
    case SHADER_ALPHAFUNC_ALWAYS:
        cmpFunc = VK_COMPARE_OP_ALWAYS;
        break;
    default:
        Warning("AlphaFunc: invalid param\n");
        return;
    }

    m_AlphaFunc = cmpFunc;
    m_AlphaRef = (int)(alphaRef * 255);
}

VkBlendFactor CShaderShadowVk::BlendFuncValue(ShaderBlendFactor_t factor) const
{
    switch (factor)
    {
    case SHADER_BLEND_ZERO:
        return VK_BLEND_FACTOR_ZERO;

    case SHADER_BLEND_ONE:
        return VK_BLEND_FACTOR_ONE;

    case SHADER_BLEND_DST_COLOR:
        return VK_BLEND_FACTOR_DST_COLOR;

    case SHADER_BLEND_ONE_MINUS_DST_COLOR:
        return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;

    case SHADER_BLEND_SRC_ALPHA:
        return VK_BLEND_FACTOR_SRC_ALPHA;

    case SHADER_BLEND_ONE_MINUS_SRC_ALPHA:
        return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;

    case SHADER_BLEND_DST_ALPHA:
        return VK_BLEND_FACTOR_DST_ALPHA;

    case SHADER_BLEND_ONE_MINUS_DST_ALPHA:
        return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;

    case SHADER_BLEND_SRC_ALPHA_SATURATE:
        return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;

    case SHADER_BLEND_SRC_COLOR:
        return VK_BLEND_FACTOR_SRC_COLOR;

    case SHADER_BLEND_ONE_MINUS_SRC_COLOR:
        return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
    }

    Warning("BlendFunc: invalid factor\n");
    return VK_BLEND_FACTOR_ONE;
}

VkBlendOp CShaderShadowVk::BlendOpValue(ShaderBlendOp_t blendOp) const
{
    switch (blendOp)
    {
    case SHADER_BLEND_OP_ADD:
        return VK_BLEND_OP_ADD;

    case SHADER_BLEND_OP_SUBTRACT:
        return VK_BLEND_OP_SUBTRACT;

    case SHADER_BLEND_OP_REVSUBTRACT:
        return VK_BLEND_OP_REVERSE_SUBTRACT;

    case SHADER_BLEND_OP_MIN:
        return VK_BLEND_OP_MIN;

    case SHADER_BLEND_OP_MAX:
        return VK_BLEND_OP_MAX;
    }

    Warning("BlendOp: invalid op\n");
    return VK_BLEND_OP_ADD;
}

void CShaderShadowVk::BlendFunc(ShaderBlendFactor_t srcFactor, ShaderBlendFactor_t dstFactor)
{
    VkBlendFactor vkSrcFactor = BlendFuncValue(srcFactor);
    VkBlendFactor vkDstFactor = BlendFuncValue(dstFactor);
    m_SrcBlend = vkSrcFactor;
    m_DestBlend = vkDstFactor;
}

// GR - separate alpha blend
void CShaderShadowVk::BlendFuncSeparateAlpha(ShaderBlendFactor_t srcFactor, ShaderBlendFactor_t dstFactor)
{
    VkBlendFactor vkSrcFactor = BlendFuncValue(srcFactor);
    VkBlendFactor vkDstFactorr = BlendFuncValue(dstFactor);
    m_SrcBlendAlpha = vkSrcFactor;
    m_DestBlendAlpha = vkDstFactorr;
}

void CShaderShadowVk::BlendOp(ShaderBlendOp_t blendOp) { m_BlendOp = BlendOpValue(blendOp); }

void CShaderShadowVk::BlendOpSeparateAlpha(ShaderBlendOp_t blendOp) { m_BlendOpAlpha = BlendOpValue(blendOp); }

//-----------------------------------------------------------------------------
// Polygon fill mode states
//-----------------------------------------------------------------------------
void CShaderShadowVk::PolyMode(ShaderPolyModeFace_t face, ShaderPolyMode_t polyMode)
{
    // DX8 can't handle different modes on front and back faces
    // FIXME:	Assert( face == SHADER_POLYMODEFACE_FRONT_AND_BACK );
    if (face == SHADER_POLYMODEFACE_BACK)
        return;

    VkPolygonMode fillMode;
    switch (polyMode)
    {
    case SHADER_POLYMODE_POINT:
        fillMode = VK_POLYGON_MODE_POINT;
        break;
    case SHADER_POLYMODE_LINE:
        fillMode = VK_POLYGON_MODE_LINE;
        break;
    case SHADER_POLYMODE_FILL:
        fillMode = VK_POLYGON_MODE_FILL;
        break;
    default:
        Warning("PolyMode: invalid poly mode\n");
        return;
    }

    m_ShadowState.m_FillMode = fillMode;
}

//-----------------------------------------------------------------------------
// Backface cull states
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableCulling(bool bEnable) { m_ShadowState.m_CullEnable = bEnable; }

//-----------------------------------------------------------------------------
// Alpha to coverage
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableAlphaToCoverage(bool bEnable) { m_ShadowState.m_EnableAlphaToCoverage = bEnable; }

//-----------------------------------------------------------------------------
// Indicates we've got a constant color specified
//-----------------------------------------------------------------------------
bool CShaderShadowVk::HasConstantColor() const { return m_HasConstantColor; }

void CShaderShadowVk::EnableConstantColor(bool bEnable) { m_HasConstantColor = bEnable; }

//-----------------------------------------------------------------------------
// A simpler method of dealing with alpha modulation
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableAlphaPipe(bool bEnable) { m_AlphaPipe = bEnable; }

void CShaderShadowVk::EnableConstantAlpha(bool bEnable) { m_HasConstantAlpha = bEnable; }

void CShaderShadowVk::EnableVertexAlpha(bool bEnable) { m_HasVertexAlpha = bEnable; }

void CShaderShadowVk::EnableTextureAlpha(TextureStage_t stage, bool bEnable)
{
    if (stage < MAX_SAMPLERS)
    {
        m_TextureStage[stage].m_TextureAlphaEnable = bEnable;
    }
}

//-----------------------------------------------------------------------------
// Indicates we're going to light the model
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableLighting(bool bEnable) { m_ShadowState.m_Lighting = bEnable; }

//-----------------------------------------------------------------------------
// Enables specular lighting (lighting has also got to be enabled)
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableSpecular(bool bEnable) { m_ShadowState.m_SpecularEnable = bEnable; }

//-----------------------------------------------------------------------------
// Enables auto-conversion from linear to gamma space on write to framebuffer.
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableSRGBWrite(bool bEnable)
{
    if (g_pHardwareConfig->SupportsSRGB())
    {
        m_ShadowState.m_SRGBWriteEnable = bEnable;
    }
    else
    {
        m_ShadowState.m_SRGBWriteEnable = false;
    }
}

//-----------------------------------------------------------------------------
// Activate/deactivate skinning
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableVertexBlend(bool bEnable)
{
    // Activate/deactivate skinning. Indexed blending is automatically
    // enabled if it's available for this hardware. When blending is enabled,
    // we allocate enough room for 3 weights (max allowed)
    if ((g_pHardwareConfig->MaxBlendMatrices() > 0) || (!bEnable))
    {
        m_ShadowState.m_VertexBlendEnable = bEnable;
    }
}

//-----------------------------------------------------------------------------
// Texturemapping state
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableTexture(Sampler_t sampler, bool bEnable)
{
    if (sampler < MAX_SAMPLERS)
    {
        m_SamplerState[sampler].m_TextureEnable = bEnable;
    }
    else
    {
        Warning("Attempting to bind a texture to an invalid sampler (%d)!\n", sampler);
    }
}

void CShaderShadowVk::EnableSRGBRead(Sampler_t sampler, bool bEnable)
{
    if (!g_pHardwareConfig->SupportsSRGB())
    {
        m_ShadowState.m_SamplerState[sampler].m_SRGBReadEnable = false;
        return;
    }

    if (sampler < MAX_SAMPLERS)
    {
        m_ShadowState.m_SamplerState[sampler].m_SRGBReadEnable = bEnable;
    }
    else
    {
        Warning("Attempting set SRGBRead state on an invalid sampler (%d)!\n", sampler);
    }
}

void CShaderShadowVk::SetShadowDepthFiltering(Sampler_t stage)
{
#ifdef DX_TO_GL_ABSTRACTION
    if (stage < MAX_SAMPLERS)
    {
        m_ShadowState.m_SamplerState[stage].m_ShadowFilterEnable = true;
        return;
    }
#else
    if (!g_pHardwareConfig->SupportsFetch4())
    {
        m_ShadowState.m_SamplerState[stage].m_Fetch4Enable = false;
        return;
    }

    if (stage < MAX_SAMPLERS)
    {
        m_ShadowState.m_SamplerState[stage].m_Fetch4Enable = true;
        return;
    }
#endif

    Warning("Attempting set shadow filtering state on an invalid sampler (%d)!\n", stage);
}

//-----------------------------------------------------------------------------
// Binds texture coordinates to a particular stage...
//-----------------------------------------------------------------------------
void CShaderShadowVk::TextureCoordinate(TextureStage_t stage, int useTexCoord)
{
    if (stage < MAX_TEXTURE_STAGES)
    {
        m_TextureStage[stage].m_TexCoordinate = useTexCoord;

        // Need to recompute the texCoordIndex, since that's affected by this
        RecomputeTexCoordIndex(stage);
    }
}

//-----------------------------------------------------------------------------
// Automatic texture coordinate generation
//-----------------------------------------------------------------------------
void CShaderShadowVk::RecomputeTexCoordIndex(TextureStage_t stage)
{
    int texCoordIndex = m_TextureStage[stage].m_TexCoordinate;
    if (m_TextureStage[stage].m_TexGenEnable)
        texCoordIndex |= m_TextureStage[stage].m_TexCoordIndex;
    m_ShadowState.m_TextureStage[stage].m_TexCoordIndex = texCoordIndex;
}

//-----------------------------------------------------------------------------
// Automatic texture coordinate generation
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableTexGen(TextureStage_t stage, bool bEnable)
{
    if (stage >= MAX_TEXTURE_STAGES)
    {
        Assert(0);
        return;
    }

    m_TextureStage[stage].m_TexGenEnable = bEnable;
    RecomputeTexCoordIndex(stage);
}

//-----------------------------------------------------------------------------
// Automatic texture coordinate generation
//-----------------------------------------------------------------------------
void CShaderShadowVk::TexGen(TextureStage_t stage, ShaderTexGenParam_t param)
{
    // no-op, fixed-function remnant
}

//-----------------------------------------------------------------------------
// Overbrighting
//-----------------------------------------------------------------------------
void CShaderShadowVk::OverbrightValue(TextureStage_t stage, float value)
{
    if (g_pHardwareConfig->SupportsOverbright() && (stage < MAX_TEXTURE_STAGES))
    {
        m_TextureStage[stage].m_OverbrightVal = value;
    }
}

//-----------------------------------------------------------------------------
// alternate method of specifying per-texture unit stuff, more flexible and more complicated
// Can be used to specify different operation per channel (alpha/color)...
//-----------------------------------------------------------------------------
void CShaderShadowVk::EnableCustomPixelPipe(bool bEnable) { m_CustomTextureStageState = bEnable; }

void CShaderShadowVk::CustomTextureStages(int stageCount)
{
    m_CustomTextureStages = stageCount;
    Assert(stageCount <= MAX_TEXTURE_STAGES);
    if (stageCount > MAX_TEXTURE_STAGES)
        stageCount = MAX_TEXTURE_STAGES;
}

void CShaderShadowVk::CustomTextureOperation(TextureStage_t stage, ShaderTexChannel_t channel, ShaderTexOp_t op, ShaderTexArg_t arg1,
                                             ShaderTexArg_t arg2)
{
    m_TextureStage[stage].m_Op[channel] = op;
    m_TextureStage[stage].m_Arg[channel][0] = arg1;
    m_TextureStage[stage].m_Arg[channel][1] = arg2;
}

//-----------------------------------------------------------------------------
// Compute the vertex format from vertex descriptor flags
//-----------------------------------------------------------------------------
void CShaderShadowVk::VertexShaderVertexFormat(unsigned int nFlags, int nTexCoordCount, int *pTexCoordDimensions, int nUserDataSize)
{
    // Code that creates a Mesh should specify whether it contains bone weights+indices, *not* the shader.
    Assert((nFlags & VERTEX_BONE_INDEX) == 0);
    nFlags &= ~VERTEX_BONE_INDEX;

    // This indicates we're using a vertex shader
    nFlags |= VERTEX_FORMAT_VERTEX_SHADER;
    m_ShadowShaderState.m_VertexUsage = g_pMeshMgr->ComputeVertexFormat(nFlags, nTexCoordCount, pTexCoordDimensions, 0, nUserDataSize);
    m_ShadowState.m_UsingFixedFunction = false;

    // Avoid an error if vertex stream 0 is too narrow
    if (g_pMeshMgr->VertexFormatSize(m_ShadowShaderState.m_VertexUsage) <= 16)
    {
        // FIXME: this is only necessary because we
        //          (a) put the flex normal/position stream in ALL vertex decls
        //          (b) bind stream 0's VB to stream 2 if there is no actual flex data
        //        ...it would be far more sensible to not add stream 2 to all vertex decls.
        static bool bComplained = false;
        if (!bComplained)
        {
            Warning("ERROR: shader asking for a too-narrow vertex format - you will see errors if running with debug D3D DLLs!\n\tPadding "
                    "the vertex format with extra texcoords\n\tWill not warn again.\n");
            bComplained = true;
        }
        // All vertex formats should contain position...
        Assert(nFlags & VERTEX_POSITION);
        nFlags |= VERTEX_POSITION;
        // This error should occur only if we have zero texcoords, or if we have a single, 1-D texcoord
        Assert((nTexCoordCount == 0) || ((nTexCoordCount == 1) && pTexCoordDimensions && (pTexCoordDimensions[0] == 1)));
        nTexCoordCount = 1;
        m_ShadowShaderState.m_VertexUsage = g_pMeshMgr->ComputeVertexFormat(nFlags, nTexCoordCount, NULL, 0, nUserDataSize);
    }
}

//-----------------------------------------------------------------------------
// Compute the vertex format from vertex descriptor flags
//-----------------------------------------------------------------------------
void CShaderShadowVk::SetMorphFormat(MorphFormat_t flags) { m_ShadowShaderState.m_MorphUsage = flags; }

//-----------------------------------------------------------------------------
// Pixel and vertex shader methods
//-----------------------------------------------------------------------------
void CShaderShadowVk::SetVertexShader(const char *pFileName, int nStaticVshIndex)
{
    char debugLabel[500] = "";

    m_ShadowShaderState.m_VertexShader = g_pShaderManager->CreateVertexShader(pFileName, nStaticVshIndex, debugLabel);
    m_ShadowShaderState.m_nStaticVshIndex = nStaticVshIndex;
}

void CShaderShadowVk::SetPixelShader(const char *pFileName, int nStaticPshIndex)
{
    char debugLabel[500] = "";

    m_ShadowShaderState.m_PixelShader = g_pShaderManager->CreatePixelShader(pFileName, nStaticPshIndex, debugLabel);
    m_ShadowShaderState.m_nStaticPshIndex = nStaticPshIndex;
}

//-----------------------------------------------------------------------------
// NOTE: See Version 5 of this file for NVidia 8-stage shader stuff
//-----------------------------------------------------------------------------
inline bool CShaderShadowVk::IsUsingTextureCoordinates(Sampler_t sampler) const { return m_SamplerState[sampler].m_TextureEnable; }

inline VkBlendOp CShaderShadowVk::OverbrightBlendValue(TextureStage_t stage)
{
    VkBlendOp colorop;
    if (m_TextureStage[stage].m_OverbrightVal < 2.0F)
        colorop = VK_BLEND_OP_MULTIPLY_EXT;
    else if (m_TextureStage[stage].m_OverbrightVal < 4.0F)
        colorop = VK_BLEND_OP_MULTIPLY_EXT;
    else
        colorop = VK_BLEND_OP_MULTIPLY_EXT;
    return colorop;
}

static inline VkBlendFactor ComputeArg(ShaderTexArg_t arg)
{
    switch (arg)
    {
    case SHADER_TEXARG_TEXTURE:
        return VK_BLEND_FACTOR_SRC_COLOR;

    case SHADER_TEXARG_ZERO:
        return VK_BLEND_FACTOR_ZERO;

    case SHADER_TEXARG_ONE:
        return VK_BLEND_FACTOR_ONE;

    case SHADER_TEXARG_TEXTUREALPHA:
        return VK_BLEND_FACTOR_SRC_ALPHA;

    case SHADER_TEXARG_INVTEXTUREALPHA:
        return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;

    case SHADER_TEXARG_NONE:
    case SHADER_TEXARG_VERTEXCOLOR:
    case SHADER_TEXARG_SPECULARCOLOR:
        return VK_BLEND_FACTOR_SRC_COLOR;

    case SHADER_TEXARG_CONSTANTCOLOR:
        return VK_BLEND_FACTOR_CONSTANT_COLOR;

    case SHADER_TEXARG_PREVIOUSSTAGE:
        return VK_BLEND_FACTOR_SRC_COLOR;
    }

    Assert(0);
    return VK_BLEND_FACTOR_ONE;
}

static inline VkBlendOp ComputeOp(ShaderTexOp_t op)
{
    switch (op)
    {
    case SHADER_TEXOP_MODULATE:
    case SHADER_TEXOP_MODULATE2X:
    case SHADER_TEXOP_MODULATE4X:
        return VK_BLEND_OP_MULTIPLY_EXT;

    case SHADER_TEXOP_SELECTARG1:
        return VK_BLEND_OP_SRC_EXT;

    case SHADER_TEXOP_SELECTARG2:
        return VK_BLEND_OP_DST_EXT;

    case SHADER_TEXOP_ADD:
        return VK_BLEND_OP_ADD;

    case SHADER_TEXOP_SUBTRACT:
        return VK_BLEND_OP_SUBTRACT;

    case SHADER_TEXOP_ADDSIGNED2X:
    case SHADER_TEXOP_BLEND_CONSTANTALPHA:
    case SHADER_TEXOP_BLEND_PREVIOUSSTAGEALPHA:
    case SHADER_TEXOP_BLEND_TEXTUREALPHA:
    case SHADER_TEXOP_MODULATECOLOR_ADDALPHA:
    case SHADER_TEXOP_MODULATEINVCOLOR_ADDALPHA:
    case SHADER_TEXOP_DOTPRODUCT3:
    case SHADER_TEXOP_DISABLE:
        return VK_BLEND_OP_ADD;
    }

    Assert(0);
    return VK_BLEND_OP_MULTIPLY_EXT;
}

void CShaderShadowVk::ConfigureCustomFVFVertexShader(unsigned int flags)
{
    int i;
    for (i = 0; i < m_CustomTextureStages; ++i)
    {
        m_ShadowState.m_TextureStage[i].m_ColorArg1 = ComputeArg(m_TextureStage[i].m_Arg[0][0]);
        m_ShadowState.m_TextureStage[i].m_ColorArg2 = ComputeArg(m_TextureStage[i].m_Arg[0][1]);
        m_ShadowState.m_TextureStage[i].m_AlphaArg1 = ComputeArg(m_TextureStage[i].m_Arg[1][0]);
        m_ShadowState.m_TextureStage[i].m_AlphaArg2 = ComputeArg(m_TextureStage[i].m_Arg[1][1]);
        m_ShadowState.m_TextureStage[i].m_ColorOp = ComputeOp(m_TextureStage[i].m_Op[0]);
        m_ShadowState.m_TextureStage[i].m_AlphaOp = ComputeOp(m_TextureStage[i].m_Op[1]);
    }

    // Deal with texture stage 1 -> n
    for (i = m_CustomTextureStages; i < MAX_TEXTURE_STAGES; ++i)
    {
        m_ShadowState.m_TextureStage[i].m_ColorArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
        m_ShadowState.m_TextureStage[i].m_ColorArg2 = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_ONE;
        m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_ZERO;
        m_ShadowState.m_TextureStage[i].m_ColorOp = VK_BLEND_OP_ADD;
        m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_ADD;
    }
}

//-----------------------------------------------------------------------------
// Sets up the alpha texture stage state
//-----------------------------------------------------------------------------
void CShaderShadowVk::ConfigureAlphaPipe(unsigned int flags)
{
    // Are we using color?
    bool isUsingVertexAlpha = m_HasVertexAlpha && ((flags & SHADER_DRAW_COLOR) != 0);
    bool isUsingConstantAlpha = m_HasConstantAlpha;

    int lastTextureStage = MAX_TEXTURE_STAGES - 1;
    while (lastTextureStage >= 0)
    {
        if (m_TextureStage[lastTextureStage].m_TextureAlphaEnable)
            break;
        --lastTextureStage;
    }

    for (int i = 0; i < MAX_TEXTURE_STAGES; ++i)
    {
        m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_ADD;
        if (m_TextureStage[i].m_TextureAlphaEnable)
        {
            if (i == 0)
            {
                m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
                m_ShadowState.m_TextureStage[i].m_AlphaArg2 =
                    isUsingConstantAlpha ? VK_BLEND_FACTOR_CONSTANT_ALPHA : VK_BLEND_FACTOR_DST_ALPHA;
                if (!isUsingConstantAlpha && !isUsingVertexAlpha)
                    m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_SRC_EXT;
                if (isUsingConstantAlpha)
                    isUsingConstantAlpha = false;
                else if (isUsingVertexAlpha)
                    isUsingVertexAlpha = false;
            }
            else
            {
                // Deal with texture stage 0
                m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
                m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_DST_ALPHA;
            }
        }
        else
        {
            // Blat out unused stages
            if ((i > lastTextureStage) && !isUsingVertexAlpha && !isUsingConstantAlpha)
            {
                m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
                m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_DST_ALPHA;
                m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_DST_EXT;
                continue;
            }

            // No texture coordinates; try to fold in vertex or constant alpha
            if (i == 0)
            {
                m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_DST_COLOR;
                if (isUsingVertexAlpha)
                {
                    m_ShadowState.m_TextureStage[i].m_AlphaOp = isUsingConstantAlpha ? VK_BLEND_OP_MULTIPLY_EXT : VK_BLEND_OP_DST_EXT;
                }
                else
                {
                    m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_SRC_EXT;
                }
                isUsingVertexAlpha = false;
                isUsingConstantAlpha = false;
            }
            else
            {
                m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
                if (isUsingConstantAlpha)
                {
                    m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                    isUsingConstantAlpha = false;
                }
                else if (isUsingVertexAlpha)
                {
                    m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_DST_COLOR;
                    isUsingVertexAlpha = false;
                }
                else
                {
                    m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_DST_COLOR;
                    m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_SRC_EXT;
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
// Sets up the texture stage state
//-----------------------------------------------------------------------------
void CShaderShadowVk::ConfigureFVFVertexShader(unsigned int flags)
{
    // For non-modulation, we can't really use the path below...
    if (m_CustomTextureStageState)
    {
        ConfigureCustomFVFVertexShader(flags);
        return;
    }

    // Deal with texture stage 0
    m_ShadowState.m_TextureStage[0].m_ColorArg1 = VK_BLEND_FACTOR_SRC_COLOR;
    m_ShadowState.m_TextureStage[0].m_ColorArg2 = VK_BLEND_FACTOR_DST_COLOR;
    m_ShadowState.m_TextureStage[0].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_COLOR;
    m_ShadowState.m_TextureStage[0].m_AlphaArg2 = VK_BLEND_FACTOR_DST_COLOR;

    // Are we using color?
    bool isUsingVertexColor = (flags & SHADER_DRAW_COLOR) != 0;
    // bool isUsingConstantColor = (flags & SHADER_HAS_CONSTANT_COLOR) != 0;
    bool isUsingConstantColor = false;

    // Are we using texture coordinates?
    if (IsUsingTextureCoordinates(SHADER_SAMPLER0))
    {
        if (isUsingVertexColor)
        {
            m_ShadowState.m_TextureStage[0].m_ColorOp = OverbrightBlendValue(SHADER_TEXTURE_STAGE0);
            m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_MULTIPLY_EXT;
        }
        else
        {
            // Just blend in the constant color here, and don't blend it in below
            m_ShadowState.m_TextureStage[0].m_ColorArg2 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[0].m_AlphaArg2 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
            isUsingConstantColor = false;

            m_ShadowState.m_TextureStage[0].m_ColorOp = OverbrightBlendValue(SHADER_TEXTURE_STAGE0);
            m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_MULTIPLY_EXT;
        }
    }
    else
    {
        // Are we using color?
        if (isUsingVertexColor)
        {
            // Color, but no texture
            if (m_TextureStage[0].m_OverbrightVal < 2.0f)
            {
                // Use diffuse * constant color, if we have a constant color
                if (isUsingConstantColor)
                {
                    m_ShadowState.m_TextureStage[0].m_ColorArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                    m_ShadowState.m_TextureStage[0].m_AlphaArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                    m_ShadowState.m_TextureStage[0].m_ColorOp = OverbrightBlendValue((TextureStage_t)0);
                    m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_MULTIPLY_EXT;

                    // This'll make sure we don't apply the constant color again below
                    isUsingConstantColor = false;
                }
                else
                {
                    m_ShadowState.m_TextureStage[0].m_ColorOp = VK_BLEND_OP_DST_EXT;
                    m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_DST_EXT;
                }
            }
            else if (m_TextureStage[0].m_OverbrightVal < 4.0f)
            {
                // Produce diffuse + diffuse
                m_ShadowState.m_TextureStage[0].m_ColorArg1 = VK_BLEND_FACTOR_DST_COLOR;
                m_ShadowState.m_TextureStage[0].m_ColorOp = VK_BLEND_OP_ADD;
                m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_DST_EXT;
            }
            else
            {
                // no 4x overbright yet!
                Assert(0);
            }
        }
        else
        {
            // No texture, no color
            if (isUsingConstantColor)
            {
                m_ShadowState.m_TextureStage[0].m_ColorArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                m_ShadowState.m_TextureStage[0].m_AlphaArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                m_ShadowState.m_TextureStage[0].m_ColorOp = VK_BLEND_OP_SRC_EXT;
                m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_SRC_EXT;

                // This'll make sure we don't apply the constant color again below
                isUsingConstantColor = false;
            }
            else
            {
                // Deal with texture stage 0
                m_ShadowState.m_TextureStage[0].m_ColorArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                m_ShadowState.m_TextureStage[0].m_AlphaArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                m_ShadowState.m_TextureStage[0].m_ColorOp = VK_BLEND_OP_SRC_EXT;
                m_ShadowState.m_TextureStage[0].m_AlphaOp = VK_BLEND_OP_SRC_EXT;
            }
        }
    }

    // Deal with texture stage 1 -> n
    int lastUsedTextureStage = 0;
    for (int i = 1; i < MAX_TEXTURE_STAGES; ++i)
    {
        m_ShadowState.m_TextureStage[i].m_ColorArg1 = VK_BLEND_FACTOR_SRC_COLOR;
        m_ShadowState.m_TextureStage[i].m_ColorArg2 = VK_BLEND_FACTOR_DST_COLOR;
        m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_ALPHA;
        m_ShadowState.m_TextureStage[i].m_AlphaArg2 = VK_BLEND_FACTOR_DST_ALPHA;

        // Not doing anything? Disable the stage
        if (!IsUsingTextureCoordinates((Sampler_t)i))
        {
            if (m_TextureStage[i].m_OverbrightVal < 2.0f)
            {
                m_ShadowState.m_TextureStage[i].m_ColorOp = VK_BLEND_OP_DST_EXT;
                m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_DST_EXT;
            }
            else
            {
                // Here, we're modulating. Add in the constant color if we need to...
                m_ShadowState.m_TextureStage[i].m_ColorArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
                m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;

                m_ShadowState.m_TextureStage[i].m_ColorOp = OverbrightBlendValue((TextureStage_t)i);
                m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_MULTIPLY_EXT;

                isUsingConstantColor = false;
                lastUsedTextureStage = i;
            }
        }
        else
        {
            // Here, we're modulating. Keep track of the last modulation stage,
            // cause the constant color modulation comes in the stage after that
            lastUsedTextureStage = i;
            m_ShadowState.m_TextureStage[i].m_ColorOp = OverbrightBlendValue((TextureStage_t)i);
            m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_MULTIPLY_EXT;
        }
    }

    // massive amounts of suck: gotta overbright here if we really
    // wanted to overbright stage0 but couldn't because of the add.
    // This isn't totally correct, but there's no way around putting it here
    // because we can't texture out of stage2 on low or medium end hardware
    m_ShadowShaderState.m_ModulateConstantColor = false;
    if (isUsingConstantColor)
    {
        ++lastUsedTextureStage;

        if (isUsingConstantColor && (lastUsedTextureStage >= MAX_TEXTURE_STAGES))
        {
            // This is the case where we'd want to modulate in a particular texture
            // stage, but we can't because there aren't enough. In this case, we're gonna
            // need to do the modulation in the per-vertex color.
            m_ShadowShaderState.m_ModulateConstantColor = true;
        }
        else
        {
            AssertOnce(lastUsedTextureStage < 2);

            // Here, we've got enough texture stages to do the modulation
            m_ShadowState.m_TextureStage[lastUsedTextureStage].m_ColorArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[lastUsedTextureStage].m_ColorArg2 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[lastUsedTextureStage].m_AlphaArg1 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[lastUsedTextureStage].m_AlphaArg2 = VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[lastUsedTextureStage].m_ColorOp = VK_BLEND_OP_MULTIPLY_EXT;
            m_ShadowState.m_TextureStage[lastUsedTextureStage].m_AlphaOp = VK_BLEND_OP_MULTIPLY_EXT;
        }
    }

    // Overwrite the alpha stuff if we asked to independently control it
    if (m_AlphaPipe)
    {
        ConfigureAlphaPipe(flags);
    }
}

//-----------------------------------------------------------------------------
// Makes sure we report if we're getting garbage.
//-----------------------------------------------------------------------------
void CShaderShadowVk::DrawFlags(unsigned int flags)
{
    m_DrawFlags = flags;
    m_ShadowState.m_UsingFixedFunction = true;
}

//-----------------------------------------------------------------------------
// Compute texture coordinates
//-----------------------------------------------------------------------------
void CShaderShadowVk::ConfigureTextureCoordinates(unsigned int flags)
{
    // default...
    for (int i = 0; i < MAX_TEXTURE_STAGES; ++i)
    {
        TextureCoordinate((TextureStage_t)i, i);
    }

    if (flags & SHADER_DRAW_TEXCOORD0)
    {
        Assert((flags & SHADER_DRAW_LIGHTMAP_TEXCOORD0) == 0);
        TextureCoordinate(SHADER_TEXTURE_STAGE0, 0);
    }
    else if (flags & SHADER_DRAW_LIGHTMAP_TEXCOORD0)
    {
        TextureCoordinate(SHADER_TEXTURE_STAGE0, 1);
    }
    else if (flags & SHADER_DRAW_SECONDARY_TEXCOORD0)
    {
        TextureCoordinate(SHADER_TEXTURE_STAGE0, 2);
    }

    if (flags & SHADER_DRAW_TEXCOORD1)
    {
        Assert((flags & SHADER_DRAW_LIGHTMAP_TEXCOORD1) == 0);
        TextureCoordinate(SHADER_TEXTURE_STAGE1, 0);
    }
    else if (flags & SHADER_DRAW_LIGHTMAP_TEXCOORD1)
    {
        TextureCoordinate(SHADER_TEXTURE_STAGE1, 1);
    }
    else if (flags & SHADER_DRAW_SECONDARY_TEXCOORD1)
    {
        TextureCoordinate(SHADER_TEXTURE_STAGE1, 2);
    }
}

//-----------------------------------------------------------------------------
// Converts draw flags into vertex format
//-----------------------------------------------------------------------------
VertexFormat_t CShaderShadowVk::FlagsToVertexFormat(int flags) const
{
    // Flags -1 occurs when there's an error condition;
    // we'll just give em the max space and let them fill it in.
    int formatFlags = 0;
    int texCoordSize[VERTEX_MAX_TEXTURE_COORDINATES] = {0, 0, 0, 0, 0, 0, 0, 0};
    int userDataSize = 0;
    int numBones = 0;

    // Flags -1 occurs when there's an error condition;
    // we'll just give em the max space and let them fill it in.
    if (flags == -1)
    {
        formatFlags = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_COLOR | VERTEX_TANGENT_S | VERTEX_TANGENT_T;
        texCoordSize[0] = texCoordSize[1] = texCoordSize[2] = 2;
    }
    else
    {
        if (flags & SHADER_DRAW_POSITION)
            formatFlags |= VERTEX_POSITION;

        if (flags & SHADER_DRAW_NORMAL)
            formatFlags |= VERTEX_NORMAL;

        if (flags & SHADER_DRAW_COLOR)
            formatFlags |= VERTEX_COLOR;

        if (flags & SHADER_DRAW_SPECULAR)
            formatFlags |= VERTEX_SPECULAR;

        if (flags & SHADER_TEXCOORD_MASK)
        {
            // normal texture coords into texture 0
            texCoordSize[0] = 2;
        }

        if (flags & SHADER_LIGHTMAP_TEXCOORD_MASK)
        {
            // lightmaps go into texcoord 1
            texCoordSize[1] = 2;
        }

        if (flags & SHADER_SECONDARY_TEXCOORD_MASK)
        {
            // any texgen, or secondary texture coordinate is put into texcoord 2
            texCoordSize[2] = 2;
        }
    }

    // Hardware skinning...	always store space for up to 3 bones
    // and always assume index blend enabled if available
    if (m_ShadowState.m_VertexBlendEnable)
    {
        if (g_pHardwareConfig->MaxBlendMatrixIndices() > 0)
            formatFlags |= VERTEX_BONE_INDEX;

        if (g_pHardwareConfig->MaxBlendMatrices() > 2)
            numBones = 2; // the third bone weight is implied
        else
            numBones = g_pHardwareConfig->MaxBlendMatrices() - 1;
    }

    return g_pMeshMgr->ComputeVertexFormat(formatFlags, VERTEX_MAX_TEXTURE_COORDINATES, texCoordSize, numBones, userDataSize);
}

//-----------------------------------------------------------------------------
// Computes shadow state based on bunches of other parameters
//-----------------------------------------------------------------------------
void CShaderShadowVk::ComputeAggregateShadowState()
{
    unsigned int flags = 0;

    // Initialize the texture stage usage; this may get changed later
    for (int i = 0; i < MAX_SAMPLERS; ++i)
    {
        m_ShadowState.m_SamplerState[i].m_TextureEnable = IsUsingTextureCoordinates((Sampler_t)i);

        // Deal with the alpha pipe
        if (m_ShadowState.m_UsingFixedFunction && m_AlphaPipe)
        {
            if (m_TextureStage[i].m_TextureAlphaEnable)
            {
                m_ShadowState.m_SamplerState[i].m_TextureEnable = true;
            }
        }
    }

    // Always use the same alpha src + dest if it's disabled
    // NOTE: This is essential for stateblocks to work
    if (m_ShadowState.m_AlphaBlendEnable)
    {
        m_ShadowState.m_SrcBlend = m_SrcBlend;
        m_ShadowState.m_DestBlend = m_DestBlend;
        m_ShadowState.m_BlendOp = m_BlendOp;
    }
    else
    {
        m_ShadowState.m_SrcBlend = VK_BLEND_FACTOR_ONE;
        m_ShadowState.m_DestBlend = VK_BLEND_FACTOR_ZERO;
        m_ShadowState.m_BlendOp = VK_BLEND_OP_ADD;
    }

    // GR
    if (m_ShadowState.m_SeparateAlphaBlendEnable)
    {
        m_ShadowState.m_SrcBlendAlpha = m_SrcBlendAlpha;
        m_ShadowState.m_DestBlendAlpha = m_DestBlendAlpha;
        m_ShadowState.m_BlendOpAlpha = m_BlendOpAlpha;
    }
    else
    {
        m_ShadowState.m_SrcBlendAlpha = VK_BLEND_FACTOR_ONE;
        m_ShadowState.m_DestBlendAlpha = VK_BLEND_FACTOR_ZERO;
        m_ShadowState.m_BlendOpAlpha = VK_BLEND_OP_ADD;
    }

    // Use the same func if it's disabled
    if (m_ShadowState.m_AlphaTestEnable)
    {
        // If alpha test is enabled, just use the values set
        m_ShadowState.m_AlphaFunc = m_AlphaFunc;
        m_ShadowState.m_AlphaRef = m_AlphaRef;
    }
    else
    {
        // A default value
        m_ShadowState.m_AlphaFunc = VK_COMPARE_OP_GREATER_OR_EQUAL;
        m_ShadowState.m_AlphaRef = 0;

        // If not alpha testing and doing a standard alpha blend, force on alpha testing
        if (m_ShadowState.m_AlphaBlendEnable)
        {
            if ((m_ShadowState.m_SrcBlend == VK_BLEND_FACTOR_SRC_ALPHA) &&
                (m_ShadowState.m_DestBlend == VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA))
            {
                m_ShadowState.m_AlphaFunc = VK_COMPARE_OP_GREATER_OR_EQUAL;
                m_ShadowState.m_AlphaRef = 1;
            }
        }
    }
    if (m_ShadowState.m_UsingFixedFunction)
    {
        flags = m_DrawFlags;

        // VK_TODO: this doesn't seem to exist in sdk13

        // We need to take this bad boy into account
        // if (HasConstantColor())
        //    flags |= SHADER_HAS_CONSTANT_COLOR;

        // We need to take lighting into account..
        if (m_ShadowState.m_Lighting)
            flags |= SHADER_DRAW_NORMAL;

        if (m_ShadowState.m_Lighting)
            flags |= SHADER_DRAW_COLOR;

        // Look for inconsistency in the shadow state (can't have texgen &
        // SHADER_DRAW_TEXCOORD or SHADER_DRAW_SECONDARY_TEXCOORD0 on the same stage)
        if (flags & (SHADER_DRAW_TEXCOORD0 | SHADER_DRAW_SECONDARY_TEXCOORD0))
        {
            Assert((m_ShadowState.m_TextureStage[0].m_TexCoordIndex & 0xFFFF0000) == 0);
        }
        if (flags & (SHADER_DRAW_TEXCOORD1 | SHADER_DRAW_SECONDARY_TEXCOORD1))
        {
            Assert((m_ShadowState.m_TextureStage[1].m_TexCoordIndex & 0xFFFF0000) == 0);
        }
        if (flags & (SHADER_DRAW_TEXCOORD2 | SHADER_DRAW_SECONDARY_TEXCOORD2))
        {
            Assert((m_ShadowState.m_TextureStage[2].m_TexCoordIndex & 0xFFFF0000) == 0);
        }
        if (flags & (SHADER_DRAW_TEXCOORD3 | SHADER_DRAW_SECONDARY_TEXCOORD3))
        {
            Assert((m_ShadowState.m_TextureStage[3].m_TexCoordIndex & 0xFFFF0000) == 0);
        }

        // Vertex usage has already been set for pixel + vertex shaders
        m_ShadowShaderState.m_VertexUsage = FlagsToVertexFormat(flags);

        // Configure the texture stages
        ConfigureFVFVertexShader(flags);
    }
    else
    {
        // Pixel shaders, disable everything so as to prevent unnecessary state changes....
        for (int i = 0; i < MAX_TEXTURE_STAGES; ++i)
        {
            m_ShadowState.m_TextureStage[i].m_ColorArg1 = VK_BLEND_FACTOR_SRC_COLOR;
            m_ShadowState.m_TextureStage[i].m_ColorArg2 = (i == 0) ? VK_BLEND_FACTOR_DST_COLOR : VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[i].m_AlphaArg1 = VK_BLEND_FACTOR_SRC_COLOR;
            m_ShadowState.m_TextureStage[i].m_AlphaArg2 = (i == 0) ? VK_BLEND_FACTOR_DST_COLOR : VK_BLEND_FACTOR_CONSTANT_ALPHA;
            m_ShadowState.m_TextureStage[i].m_ColorOp = VK_BLEND_OP_DST_EXT;
            m_ShadowState.m_TextureStage[i].m_AlphaOp = VK_BLEND_OP_DST_EXT;
            m_ShadowState.m_TextureStage[i].m_TexCoordIndex = i;
        }
        m_ShadowState.m_Lighting = false;
        m_ShadowState.m_SpecularEnable = false;
        m_ShadowState.m_VertexBlendEnable = false;
        m_ShadowShaderState.m_ModulateConstantColor = false;
    }

    // Compute texture coordinates
    ConfigureTextureCoordinates(flags);

    // Alpha to coverage
    if (m_ShadowState.m_EnableAlphaToCoverage)
    {
        // Only allow this to be enabled if blending is disabled and testing is enabled
        if ((m_ShadowState.m_AlphaBlendEnable == true) || (m_ShadowState.m_AlphaTestEnable == false))
        {
            m_ShadowState.m_EnableAlphaToCoverage = false;
        }
    }
}

void CShaderShadowVk::FogMode(ShaderFogMode_t fogMode)
{
    Assert(fogMode >= 0 && fogMode < SHADER_FOGMODE_NUMFOGMODES);
    m_ShadowState.m_FogMode = fogMode;
}

void CShaderShadowVk::DisableFogGammaCorrection(bool bDisable) { m_ShadowState.m_bDisableFogGammaCorrection = bDisable; }

void CShaderShadowVk::SetDiffuseMaterialSource(ShaderMaterialSource_t materialSource)
{
    // COMPILE_TIME_ASSERT((int)D3DMCS_MATERIAL == (int)SHADER_MATERIALSOURCE_MATERIAL);
    // COMPILE_TIME_ASSERT((int)D3DMCS_COLOR1 == (int)SHADER_MATERIALSOURCE_COLOR1);
    // COMPILE_TIME_ASSERT((int)D3DMCS_COLOR2 == (int)SHADER_MATERIALSOURCE_COLOR2);
    Assert(materialSource == SHADER_MATERIALSOURCE_MATERIAL || materialSource == SHADER_MATERIALSOURCE_COLOR1 ||
           materialSource == SHADER_MATERIALSOURCE_COLOR2);
    m_ShadowState.m_DiffuseMaterialSource = materialSource;
}