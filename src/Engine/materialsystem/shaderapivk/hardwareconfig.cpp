//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#include "hardwareconfig.h"
#include "materialsystem/materialsystem_config.h"
#include "shaderapi/ishaderutil.h"
#include "shaderapivk_global.h"
#include "shaderdevicevk.h"
#include "tier0/ICommandLine.h"
#include "tier1/convar.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
//
// Hardware Config!
//
//-----------------------------------------------------------------------------
static CHardwareConfig g_HardwareConfig;
CHardwareConfig *g_pHardwareConfig = &g_HardwareConfig;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CHardwareConfig, IMaterialSystemHardwareConfig, MATERIALSYSTEM_HARDWARECONFIG_INTERFACE_VERSION,
                                  g_HardwareConfig)

CHardwareConfig::CHardwareConfig()
{
    memset(&m_Caps, 0, sizeof(HardwareCaps_t));
    memset(&m_ActualCaps, 0, sizeof(HardwareCaps_t));
    memset(&m_UnOverriddenCaps, 0, sizeof(HardwareCaps_t));
    m_bHDREnabled = false;

    // FIXME: This is kind of a hack to deal with DX8 worldcraft startup.
    // We can at least have this much texture
    m_Caps.m_MaxTextureWidth = m_Caps.m_MaxTextureHeight = m_Caps.m_MaxTextureDepth = 256;
}

//-----------------------------------------------------------------------------
// Sets up the hardware caps given the specified DX level
//-----------------------------------------------------------------------------
void CHardwareConfig::SetupHardwareCaps(const HardwareCaps_t &actualCaps)
{
    memcpy(&m_Caps, &actualCaps, sizeof(HardwareCaps_t));
    memcpy(&m_UnOverriddenCaps, &actualCaps, sizeof(HardwareCaps_t));

    // Clamp num texture stages to 2, since it's only used for fixed function
    m_Caps.m_NumTextureStages = min(2, m_Caps.m_NumTextureStages);

    // Read dxsupport.cfg which has config overrides for particular cards.
    g_pShaderDeviceMgr->ReadHardwareCaps(m_Caps);

    // This is the spot to validate read in caps versus actual caps.
    if (m_Caps.m_MaxUserClipPlanes > m_ActualCaps.m_MaxUserClipPlanes)
    {
        m_Caps.m_MaxUserClipPlanes = m_ActualCaps.m_MaxUserClipPlanes;
    }
    if (m_Caps.m_MaxUserClipPlanes == 0)
    {
        m_Caps.m_UseFastClipping = true;
    }

    // 2b supports more lights than just 2.0
    if (m_Caps.m_SupportsPixelShaders_2_b)
    {
        m_Caps.m_MaxNumLights = MAX_NUM_LIGHTS;
    }
    else
    {
        m_Caps.m_MaxNumLights = MAX_NUM_LIGHTS - 2;
    }

    m_Caps.m_MaxNumLights = min(m_Caps.m_MaxNumLights, (int)MAX_NUM_LIGHTS);

    memcpy(&m_UnOverriddenCaps, &m_Caps, sizeof(HardwareCaps_t));
}

//-----------------------------------------------------------------------------
// Sets up the hardware caps given the specified DX level
//-----------------------------------------------------------------------------
void CHardwareConfig::SetupHardwareCaps(const ShaderDeviceInfo_t &mode, const HardwareCaps_t &actualCaps)
{
    memcpy(&m_ActualCaps, &actualCaps, sizeof(HardwareCaps_t));
    SetupHardwareCaps(actualCaps);
}

void CHardwareConfig::OverrideStreamOffsetSupport(bool bOverrideEnabled, bool bEnableSupport)
{
    if (bOverrideEnabled)
    {
        m_Caps.m_bSupportsStreamOffset = bEnableSupport;
        if (!m_ActualCaps.m_bSupportsStreamOffset)
        {
            m_Caps.m_bSupportsStreamOffset = false;
        }
    }
    else
    {
        // Go back to default
        m_Caps.m_bSupportsStreamOffset = m_UnOverriddenCaps.m_bSupportsStreamOffset;
    }
}

//-----------------------------------------------------------------------------
// Implementation of IMaterialSystemHardwareConfig
//-----------------------------------------------------------------------------
bool CHardwareConfig::HasDestAlphaBuffer() const
{
    if (!g_pShaderDevice)
        return false;
    return (g_pShaderDevice->GetBackBufferFormat() == IMAGE_FORMAT_BGRA8888);
}

bool CHardwareConfig::HasStencilBuffer() const { return StencilBufferBits() > 0; }

int CHardwareConfig::GetFrameBufferColorDepth() const
{
    if (!g_pShaderDevice)
        return 0;
    return ShaderUtil()->ImageFormatInfo(g_pShaderDevice->GetBackBufferFormat()).m_NumBytes;
}

int CHardwareConfig::GetSamplerCount() const { return m_Caps.m_NumSamplers; }

bool CHardwareConfig::HasSetDeviceGammaRamp() const { return m_Caps.m_HasSetDeviceGammaRamp; }

bool CHardwareConfig::SupportsCompressedTextures() const
{
    Assert(m_Caps.m_SupportsCompressedTextures != COMPRESSED_TEXTURES_NOT_INITIALIZED);
    return m_Caps.m_SupportsCompressedTextures == COMPRESSED_TEXTURES_ON;
}

VertexCompressionType_t CHardwareConfig::SupportsCompressedVertices() const { return m_Caps.m_SupportsCompressedVertices; }

bool CHardwareConfig::SupportsNormalMapCompression() const { return m_Caps.m_bSupportsNormalMapCompression; }

bool CHardwareConfig::SupportsBorderColor() const { return m_Caps.m_bSupportsBorderColor; }

bool CHardwareConfig::SupportsFetch4() const { return m_Caps.m_bSupportsFetch4; }

bool CHardwareConfig::SupportsVertexAndPixelShaders() const { return m_Caps.m_SupportsPixelShaders; }

bool CHardwareConfig::SupportsPixelShaders_1_4() const { return m_Caps.m_SupportsPixelShaders_1_4; }

bool CHardwareConfig::SupportsPixelShaders_2_0() const { return m_Caps.m_SupportsPixelShaders_2_0; }

bool CHardwareConfig::SupportsPixelShaders_2_b() const { return m_Caps.m_SupportsPixelShaders_2_b; }

bool CHardwareConfig::SupportsVertexShaders_2_0() const { return m_Caps.m_SupportsVertexShaders_2_0; }

bool CHardwareConfig::SupportsShaderModel_3_0() const { return m_Caps.m_SupportsShaderModel_3_0; }

// If you change these, make the corresponding change in common_ps_fxc.h
#define NVIDIA_PCF_POISSON 0
#define ATI_NOPCF 1
#define ATI_NO_PCF_FETCH4 2

int CHardwareConfig::GetShadowFilterMode() const
{
    if (!m_Caps.m_bSupportsShadowDepthTextures || !ShaderUtil()->GetConfig().ShadowDepthTexture())
        return 0;

    switch (m_Caps.m_ShadowDepthTextureFormat)
    {
    case IMAGE_FORMAT_NV_DST16:
    case IMAGE_FORMAT_NV_DST24:

        return NVIDIA_PCF_POISSON; // NVIDIA hardware bilinear PCF

    case IMAGE_FORMAT_ATI_DST16:
    case IMAGE_FORMAT_ATI_DST24:

        if (m_Caps.m_bSupportsFetch4)
            return ATI_NO_PCF_FETCH4; // ATI fetch4 depth texture sampling

        return ATI_NOPCF; // ATI vanilla depth texture sampling

    default:
        return 0;
    }

    return 0;
}

static ConVar
    r_shader_srgb("r_shader_srgb", "0", 0,
                  "-1 = use hardware caps. 0 = use hardware srgb. 1 = use shader srgb(software lookup)"); // -1=use caps 0=off 1=on

int CHardwareConfig::NeedsShaderSRGBConversion() const
{
    int cValue = r_shader_srgb.GetInt();
    switch (cValue)
    {
    case 0:
        return false;

    case 1:
        return true;

    default:
        return false;
    }
}

bool CHardwareConfig::UsesSRGBCorrectBlending() const
{
    int cValue = r_shader_srgb.GetInt();
    return cValue == 0;
}

static ConVar mat_disablehwmorph("mat_disablehwmorph", "0", 0, "Disables HW morphing for particular mods");
bool CHardwareConfig::HasFastVertexTextures() const
{
    static int bEnableFastVertexTextures = -1;
    static bool bDisableHWMorph = false;
    if (bEnableFastVertexTextures < 0)
    {
        bEnableFastVertexTextures = 1;
        if (CommandLine()->FindParm("-disallowhwmorph"))
        {
            bEnableFastVertexTextures = 0;
        }
        bDisableHWMorph = (mat_disablehwmorph.GetInt() != 0);
    }

    // JasonM - turned this off for Orange Box release...
    // return false;

    return bEnableFastVertexTextures != 0 && !bDisableHWMorph;
}

int CHardwareConfig::MaxHWMorphBatchCount() const { return ShaderUtil()->MaxHWMorphBatchCount(); }

int CHardwareConfig::MaximumAnisotropicLevel() const { return m_Caps.m_nMaxAnisotropy; }

int CHardwareConfig::MaxTextureWidth() const { return m_Caps.m_MaxTextureWidth; }

int CHardwareConfig::MaxTextureHeight() const { return m_Caps.m_MaxTextureHeight; }

int CHardwareConfig::TextureMemorySize() const { return m_Caps.m_TextureMemorySize; }

bool CHardwareConfig::SupportsOverbright() const { return m_Caps.m_SupportsOverbright; }

bool CHardwareConfig::SupportsCubeMaps() const { return m_Caps.m_SupportsCubeMaps; }

bool CHardwareConfig::SupportsMipmappedCubemaps() const { return m_Caps.m_SupportsMipmappedCubemaps; }

bool CHardwareConfig::SupportsNonPow2Textures() const { return m_Caps.m_SupportsNonPow2Textures; }

int CHardwareConfig::GetTextureStageCount() const { return m_Caps.m_NumTextureStages; }

int CHardwareConfig::NumVertexShaderConstants() const { return m_Caps.m_NumVertexShaderConstants; }

int CHardwareConfig::NumBooleanVertexShaderConstants() const { return m_Caps.m_NumBooleanVertexShaderConstants; }

int CHardwareConfig::NumIntegerVertexShaderConstants() const { return m_Caps.m_NumIntegerVertexShaderConstants; }

int CHardwareConfig::NumPixelShaderConstants() const { return m_Caps.m_NumPixelShaderConstants; }

int CHardwareConfig::NumBooleanPixelShaderConstants() const { return m_Caps.m_NumBooleanPixelShaderConstants; }

int CHardwareConfig::NumIntegerPixelShaderConstants() const { return m_Caps.m_NumIntegerPixelShaderConstants; }

int CHardwareConfig::MaxNumLights() const { return m_Caps.m_MaxNumLights; }

bool CHardwareConfig::SupportsHardwareLighting() const { return m_Caps.m_SupportsHardwareLighting; }

int CHardwareConfig::MaxBlendMatrices() const { return m_Caps.m_MaxBlendMatrices; }

int CHardwareConfig::MaxBlendMatrixIndices() const { return m_Caps.m_MaxBlendMatrixIndices; }

int CHardwareConfig::MaxTextureAspectRatio() const { return m_Caps.m_MaxTextureAspectRatio; }

int CHardwareConfig::MaxVertexShaderBlendMatrices() const { return m_Caps.m_MaxVertexShaderBlendMatrices; }

int CHardwareConfig::MaxUserClipPlanes() const { return m_Caps.m_MaxUserClipPlanes; }

bool CHardwareConfig::UseFastClipping() const { return m_Caps.m_UseFastClipping; }

int CHardwareConfig::MaxTextureDepth() const { return m_Caps.m_MaxTextureDepth; }

const char *CHardwareConfig::GetShaderDLLName() const
{
    return (m_Caps.m_pShaderDLL && m_Caps.m_pShaderDLL[0]) ? m_Caps.m_pShaderDLL : "DEFAULT";
}

bool CHardwareConfig::ReadPixelsFromFrontBuffer() const
{
    // GR - in DX 9.0a can blit from MSAA back buffer
    return false;
}

bool CHardwareConfig::PreferDynamicTextures() const { return m_Caps.m_PreferDynamicTextures; }

bool CHardwareConfig::SupportsHDRMode(HDRType_t nHDRType) const
{
    switch (nHDRType)
    {
    case HDR_TYPE_NONE:
        return true;

    case HDR_TYPE_INTEGER:
        return (m_Caps.m_MaxHDRType == HDR_TYPE_INTEGER) || (m_Caps.m_MaxHDRType == HDR_TYPE_FLOAT);

    case HDR_TYPE_FLOAT:
        return (m_Caps.m_MaxHDRType == HDR_TYPE_FLOAT);
    }
    return false;
}

#ifdef TF
bool CHardwareConfig::CanStretchRectFromTextures(void) const { return false; }
#endif

bool CHardwareConfig::HasProjectedBumpEnv() const { return m_Caps.m_HasProjectedBumpEnv; }

bool CHardwareConfig::SupportsSpheremapping() const { return m_Caps.m_bSupportsSpheremapping; }

bool CHardwareConfig::NeedsAAClamp() const { return false; }

bool CHardwareConfig::NeedsATICentroidHack() const { return m_Caps.m_bNeedsATICentroidHack; }

bool CHardwareConfig::SupportsColorOnSecondStream() const { return m_Caps.m_bColorOnSecondStream; }

bool CHardwareConfig::SupportsStaticPlusDynamicLighting() const { return true; }

bool CHardwareConfig::PreferReducedFillrate() const { return ShaderUtil()->GetConfig().ReduceFillrate(); }

bool CHardwareConfig::SpecifiesFogColorInLinearSpace() const { return m_Caps.m_bFogColorSpecifiedInLinearSpace; }

bool CHardwareConfig::SupportsSRGB() const { return m_Caps.m_SupportsSRGB; }

bool CHardwareConfig::IsAAEnabled() const
{
    return g_pShaderDevice ? g_pShaderDevice->IsAAEnabled() : false;
    //	bool bAntialiasing = ( m_PresentParameters.MultiSampleType != D3DMULTISAMPLE_NONE );
    //	return bAntialiasing;
}

int CHardwareConfig::GetVertexTextureCount() const { return m_Caps.m_nVertexTextureCount; }

int CHardwareConfig::GetMaxVertexTextureDimension() const { return m_Caps.m_nMaxVertexTextureDimension; }

HDRType_t CHardwareConfig::GetHDRType() const
{
    if (m_bHDREnabled)
        return m_Caps.m_HDRType;
    return HDR_TYPE_NONE;
}

HDRType_t CHardwareConfig::GetHardwareHDRType() const { return m_Caps.m_HDRType; }

bool CHardwareConfig::SupportsStreamOffset() const { return m_Caps.m_bSupportsStreamOffset; }

int CHardwareConfig::StencilBufferBits() const { return g_pShaderDevice ? g_pShaderDevice->StencilBufferBits() : 0; }

int CHardwareConfig::MaxViewports() const { return m_Caps.m_nMaxViewports; }

int CHardwareConfig::GetActualSamplerCount() const { return m_ActualCaps.m_NumSamplers; }

int CHardwareConfig::GetActualTextureStageCount() const { return m_ActualCaps.m_NumTextureStages; }

const char *CHardwareConfig::GetHWSpecificShaderDLLName() const
{
    return m_Caps.m_pShaderDLL && m_Caps.m_pShaderDLL[0] ? m_Caps.m_pShaderDLL : NULL;
}

bool CHardwareConfig::SupportsMipmapping() const { return m_Caps.m_SupportsMipmapping; }

bool CHardwareConfig::ActuallySupportsPixelShaders_2_b() const { return m_ActualCaps.m_SupportsPixelShaders_2_b; }