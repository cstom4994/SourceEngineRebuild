//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//===========================================================================//

#ifndef LOCALVKTYPES_H
#define LOCALVKTYPES_H

#ifdef _WIN32
#pragma once
#include <windows.h>
#endif

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <materialsystem/IShader.h>
#include <vector>
#include "hardwareconfig.h"
#include "vulkanimpl.h"

typedef void *HardwareShader_t;

//-----------------------------------------------------------------------------
// The vertex and pixel shader type
//-----------------------------------------------------------------------------
typedef int VertexShader_t;
typedef int PixelShader_t;

//-----------------------------------------------------------------------------
// Bitpattern for an invalid shader
//-----------------------------------------------------------------------------
#define INVALID_SHADER (0xFFFFFFFF)
#define INVALID_HARDWARE_SHADER (NULL)

enum VertexShaderLightTypes_t
{
    LIGHT_NONE = -1,
    LIGHT_SPOT = 0,
    LIGHT_POINT = 1,
    LIGHT_DIRECTIONAL = 2,
    LIGHT_STATIC = 3,
    LIGHT_AMBIENTCUBE = 4,
};

typedef struct LIGHT
{
    VertexShaderLightTypes_t Type;
    glm::vec4 Diffuse;
    glm::vec4 Specular;
    glm::vec4 Ambient;
    glm::vec3 Position;
    glm::vec3 Direction;
    float Range;
    float Falloff;
    float Attenuation0;
    float Attenuation1;
    float Attenuation2;
    float Theta;
    float Phi;
} LIGHT;

typedef enum SHADEMODE
{
    SHADE_FLAT = 1,
    SHADE_GOURAUD = 2,
    SHADE_PHONG = 3
} SHADEMODE;

typedef enum FOGMODE
{
    FOG_NONE = 0,
    FOG_EXP = 1,
    FOG_EXP2 = 2,
    FOG_LINEAR = 3
} FOGMODE;

enum TransformType_t
{
    TRANSFORM_IS_IDENTITY = 0,
    TRANSFORM_IS_CAMERA_TO_WORLD,
    TRANSFORM_IS_GENERAL,
};

enum TransformDirtyBits_t
{
    STATE_CHANGED_VERTEX_SHADER = 0x1,
    STATE_CHANGED_FIXED_FUNCTION = 0x2,
    STATE_CHANGED = 0x3
};

enum
{
    // VK_TODO:
    // what's the vk equivalent of D3DRENDERSTATETYPE?
    MAX_NUM_RENDERSTATES = (209 + 1)
};

enum
{
    MAX_SAMPLERS = 16,
    MAX_TEXTURE_STAGES = 16,
};

//-----------------------------------------------------------------------------
// Some important enumerations
//-----------------------------------------------------------------------------
enum
{
    MAX_VERTEX_TEXTURE_COUNT = 4,
};

//-----------------------------------------------------------------------------
// State related to vertex textures
//-----------------------------------------------------------------------------
struct VertexTextureState_t
{
    ShaderAPITextureHandle_t m_BoundTexture;
    VkSamplerAddressMode m_UTexWrap;
    VkSamplerAddressMode m_VTexWrap;
    VkFilter m_MagFilter;
    VkFilter m_MinFilter;
    VkFilter m_MipFilter;
};

//-----------------------------------------------------------------------------
// These board states change with high frequency; are not shadowed
//-----------------------------------------------------------------------------
struct TextureStageState_t
{
    VkSamplerCreateFlags m_TextureTransformFlags;
    float m_BumpEnvMat00;
    float m_BumpEnvMat01;
    float m_BumpEnvMat10;
    float m_BumpEnvMat11;
};

struct SamplerState_t
{
    ShaderAPITextureHandle_t m_BoundTexture;
    VkSamplerAddressMode m_UTexWrap;
    VkSamplerAddressMode m_VTexWrap;
    VkSamplerAddressMode m_WTexWrap;
    VkFilter m_MagFilter;
    VkFilter m_MinFilter;
    VkFilter m_MipFilter;
    int m_nAnisotropicLevel;
    bool m_TextureEnable;
    bool m_SRGBReadEnable;
};

struct DynamicState_t
{
    // Constant color
    unsigned int m_ConstantColor;

    // Normalize normals?
    bool m_NormalizeNormals;

    // Viewport state
    VkViewport m_Viewport;

    // Transform state
    glm::mat4x4 m_Transform[NUM_MATRIX_MODES];
    unsigned char m_TransformType[NUM_MATRIX_MODES];
    unsigned char m_TransformChanged[NUM_MATRIX_MODES];

    // Ambient light color
    unsigned long m_Ambient;
    LIGHT m_Lights[MAX_NUM_LIGHTS];
    LightDesc_t m_LightDescs[MAX_NUM_LIGHTS];
    bool m_LightEnable[MAX_NUM_LIGHTS];
    Vector4D m_AmbientLightCube[6];
    unsigned char m_LightChanged[MAX_NUM_LIGHTS];
    unsigned char m_LightEnableChanged[MAX_NUM_LIGHTS];
    VertexShaderLightTypes_t m_LightType[MAX_NUM_LIGHTS];
    Vector m_vLightingOrigin;
    int m_NumLights;

    // Shade mode
    SHADEMODE m_ShadeMode;

    // Clear color
    VkClearValue m_ClearColor;

    // Fog
    unsigned long m_FogColor;
    float m_PixelFogColor[4];
    bool m_bFogGammaCorrectionDisabled;
    bool m_FogEnable;
    MaterialFogMode_t m_SceneFog;
    FOGMODE m_FogMode;
    float m_FogStart;
    float m_FogEnd;
    float m_FogZ;
    float m_FogMaxDensity;

    float m_HeightClipZ;
    MaterialHeightClipMode_t m_HeightClipMode;

    // user clip planes
    int m_UserClipPlaneEnabled;
    int m_UserClipPlaneChanged;
    glm::vec4 m_UserClipPlaneWorld[MAXUSERCLIPPLANES];
    glm::vec4 m_UserClipPlaneProj[MAXUSERCLIPPLANES];
    bool m_UserClipLastUpdatedUsingFixedFunction;

    bool m_FastClipEnabled;
    bool m_bFastClipPlaneChanged;
    glm::vec4 m_FastClipPlane;

    // Used when overriding the user clip plane
    bool m_bUserClipTransformOverride;
    glm::mat4x4 m_UserClipTransform;

    // Cull mode
    VkCullModeFlags m_DesiredCullMode;
    VkCullModeFlags m_CullMode;
    VkFrontFace m_DesiredFrontFace;
    VkFrontFace m_FrontFace;
    bool m_bCullEnabled;

    // Skinning
    int m_VertexBlend;
    int m_NumBones;

    // Pixel and vertex shader constants...
    Vector4D *m_pVectorVertexShaderConstant;
    BOOL *m_pBooleanVertexShaderConstant;
    IntVector4D *m_pIntegerVertexShaderConstant;
    Vector4D *m_pVectorPixelShaderConstant;
    BOOL *m_pBooleanPixelShaderConstant;
    IntVector4D *m_pIntegerPixelShaderConstant;

    // Texture stage state
    TextureStageState_t m_TextureStage[MAX_TEXTURE_STAGES];
    SamplerState_t m_SamplerState[MAX_SAMPLERS];

    // Vertex texture stage state
    VertexTextureState_t m_VertexTextureState[MAX_VERTEX_TEXTURE_COUNT];

    unsigned long m_RenderState[MAX_NUM_RENDERSTATES];

    RECT m_ScissorRect;

    VkVertexInputAttributeDescription *m_pVertexDecl;

    bool m_bSRGBWritesEnabled;
    bool m_bHWMorphingEnabled;

    float m_DestAlphaDepthRange; // Dest alpha writes compress the depth to get better results. This holds the default
                                 // setting that can be overriden with r_destalpharange

    DynamicState_t() {}

  private:
    DynamicState_t(DynamicState_t const &);
};

//-----------------------------------------------------------------------------
// A structure maintaining the shadowed board state
//-----------------------------------------------------------------------------
struct TextureStageShadowState_t
{
    // State shadowing affects these
    VkBlendOp m_ColorOp;
    VkBlendFactor m_ColorArg1;
    VkBlendFactor m_ColorArg2;
    VkBlendOp m_AlphaOp;
    VkBlendFactor m_AlphaArg1;
    VkBlendFactor m_AlphaArg2;
    int m_TexCoordIndex;
};

struct SamplerShadowState_t
{
    bool m_TextureEnable : 1;
    bool m_SRGBReadEnable : 1;
    bool m_Fetch4Enable : 1;
    bool m_ShadowFilterEnable : 1;
};

struct ShadowState_t
{
    // Depth buffering state
    VkCompareOp m_ZFunc;
    // VK_TODO
    // D3DZBUFFERTYPE m_ZEnable;
    bool m_ZEnable;

    // Write enable
    VkColorComponentFlags m_ColorWriteEnable;

    // Fill mode
    VkPolygonMode m_FillMode;

    // Alpha state
    VkBlendFactor m_SrcBlend;
    VkBlendFactor m_DestBlend;
    VkBlendOp m_BlendOp;

    // Separate alpha blend state
    VkBlendFactor m_SrcBlendAlpha;
    VkBlendFactor m_DestBlendAlpha;
    VkBlendOp m_BlendOpAlpha;

    VkCompareOp m_AlphaFunc;
    int m_AlphaRef;

    // Texture stage state
    TextureStageShadowState_t m_TextureStage[MAX_TEXTURE_STAGES];

    // Sampler state
    SamplerShadowState_t m_SamplerState[MAX_SAMPLERS];

    ShaderFogMode_t m_FogMode;

    // VK_TODO
    // D3DMATERIALCOLORSOURCE m_DiffuseMaterialSource;
    int m_DiffuseMaterialSource;

    unsigned char m_ZWriteEnable : 1;
    unsigned char m_ZBias : 2;
    // Cull State?
    unsigned char m_CullEnable : 1;
    // Lighting in hardware?
    unsigned char m_Lighting : 1;
    unsigned char m_SpecularEnable : 1;
    unsigned char m_AlphaBlendEnable : 1;
    unsigned char m_AlphaTestEnable : 1;

    // Fixed function?
    unsigned char m_UsingFixedFunction : 1;
    // Vertex blending?
    unsigned char m_VertexBlendEnable : 1;
    // Auto-convert from linear to gamma upon writing to the frame buffer?
    unsigned char m_SRGBWriteEnable : 1;
    // Seperate Alpha Blend?
    unsigned char m_SeparateAlphaBlendEnable : 1;
    // Stencil?
    unsigned char m_StencilEnable : 1;

    unsigned char m_bDisableFogGammaCorrection : 1;

    unsigned char m_EnableAlphaToCoverage : 1;

    unsigned char m_Reserved : 1;
    unsigned short m_nReserved2;
};

//-----------------------------------------------------------------------------
// These are part of the "shadow" since they describe the shading algorithm
// but aren't actually captured in the state transition table
// because it would produce too many transitions
//-----------------------------------------------------------------------------
struct ShadowShaderState_t
{
    // The vertex + pixel shader group to use...
    VertexShader_t m_VertexShader;
    PixelShader_t m_PixelShader;

    // The static vertex + pixel shader indices
    int m_nStaticVshIndex;
    int m_nStaticPshIndex;

    // Vertex data used by this snapshot
    // Note that the vertex format actually used will be the
    // aggregate of the vertex formats used by all snapshots in a material
    VertexFormat_t m_VertexUsage;

    // Morph data used by this snapshot
    // Note that the morph format actually used will be the
    // aggregate of the morph formats used by all snapshots in a material
    MorphFormat_t m_MorphUsage;

    // Modulate constant color into the vertex color
    bool m_ModulateConstantColor;

    bool m_nReserved[3];
};

struct MatrixStack
{
    std::vector<glm::mat4x4> matrices;
    int currentMatrix = -1;

    // Load matrix into current position in stack
    void LoadMatrix(glm::mat4x4 mat)
    {
        if (currentMatrix == -1)
        {
            Push(mat);
            return;
        }
        matrices[currentMatrix] = mat;
    }

    // Load identity matrix into current position in stack
    void LoadIdentity() { LoadMatrix(glm::mat4()); }

    // Get matrix on top of stack
    glm::mat4x4 GetTop() { return matrices[matrices.size() - 1]; }

    // Removes top-most matrix from the stack
    glm::mat4x4 Pop()
    {
        glm::mat4x4 mat = GetTop();
        matrices.pop_back();
#pragma push_macro("max")
#pragma push_macro("min")
#undef max
#undef min
        currentMatrix = std::max(0, std::min(currentMatrix, (int)matrices.size() - 1));
#pragma pop_macro("max")
#pragma pop_macro("min")
        return mat;
    }

    // Add matrix to top of the stack
    int Push(glm::mat4x4 mat)
    {
        matrices.push_back(mat);
        currentMatrix = (int)matrices.size() - 1;
        return matrices.size();
    }

    void MultMatrix(glm::mat4x4 mat) { matrices[currentMatrix] = matrices[currentMatrix] * mat; }

    void MultMatrixLocal(glm::mat4x4 mat) { matrices[currentMatrix] = mat * matrices[currentMatrix]; }

    void RotateAxisLocal(glm::vec3 axis, float angle)
    {
        glm::mat4x4 tmp = glm::rotate(angle, axis);
        matrices[currentMatrix] = tmp * matrices[currentMatrix];
    }

    void TranslateLocal(glm::vec3 translation)
    {
        glm::mat4x4 tmp = glm::translate(translation);
        matrices[currentMatrix] = tmp * matrices[currentMatrix];
    }

    void ScaleLocal(glm::vec3 scale)
    {
        glm::mat4x4 tmp = glm::scale(scale);
        matrices[currentMatrix] = tmp * matrices[currentMatrix];
    }
};

struct UniformBufferObject
{
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct ModelVertexVk_t
{
    glm::vec3 m_vecPosition;
    glm::vec2 m_flBoneWeights;
    unsigned int m_nBoneIndices;
    glm::vec3 m_vecNormal;
    glm::vec<4, uint8_t> m_nColor; // ARGB
    glm::vec2 m_vecTexCoord;
    glm::vec4 m_vecUserData;
};

#endif // LOCALVKTYPES_H