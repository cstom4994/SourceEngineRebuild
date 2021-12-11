//

#ifndef SHADERMANAGERVK_H
#define SHADERMANAGERVK_H

#ifdef _WIN32
#pragma once
#endif

#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "KeyValues.h"
#include "datacache/idatacache.h"
#include "filesystem.h"
#include "filesystem/IQueuedLoader.h"
#include "hardwareconfig.h"
#include "localvktypes.h"
#include "materialsystem/shader_vcs_version.h"
#include "meshmgrvk.h"
#include "shaderdevicevk.h"
#include "shadershadowvk.h"
#include "tier0/dbg.h"
#include "tier1/utlbuffer.h"
#include "tier1/utldict.h"
#include "tier1/utllinkedlist.h"
#include "tier1/utlsymbol.h"
#include "tier1/utlvector.h"

#pragma push_macro("max")
#pragma push_macro("min")
#undef max
#undef min
#include "spirv-headers/GLSL.std.450.h"
//#include "SPIRV/disassemble.h"
#include "glslang/Public/ShaderLang.h"
#include "glslang/SPIRV/GlslangToSpv.h"
#pragma pop_macro("max")
#pragma pop_macro("min")

//-----------------------------------------------------------------------------
// Vertex + pixel shader manager
//-----------------------------------------------------------------------------
abstract_class IShaderManager
{
  protected:
    // The current vertex and pixel shader index
    int m_nVertexShaderIndex;
    int m_nPixelShaderIndex;

  public:
    // Initialize, shutdown
    virtual void Init() = 0;
    virtual void Shutdown() = 0;

    // Compiles vertex shaders
    virtual IShaderBuffer *CompileShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion) = 0;

    // New version of these methods	[dx10 port]
    virtual VertexShaderHandle_t CreateVertexShader(IShaderBuffer * pShaderBuffer) = 0;
    virtual void DestroyVertexShader(VertexShaderHandle_t hShader) = 0;
    virtual PixelShaderHandle_t CreatePixelShader(IShaderBuffer * pShaderBuffer) = 0;
    virtual void DestroyPixelShader(PixelShaderHandle_t hShader) = 0;

    // Creates vertex, pixel shaders
    virtual VertexShader_t CreateVertexShader(const char *pVertexShaderFile, int nStaticVshIndex = 0, char *debugLabel = NULL) = 0;
    virtual PixelShader_t CreatePixelShader(const char *pPixelShaderFile, int nStaticPshIndex = 0, char *debugLabel = NULL) = 0;

    // Sets which dynamic version of the vertex + pixel shader to use
    FORCEINLINE void SetVertexShaderIndex(int vshIndex);
    FORCEINLINE void SetPixelShaderIndex(int pshIndex);

    // Sets the vertex + pixel shader render state
    virtual void SetVertexShader(VertexShader_t shader) = 0;
    virtual void SetPixelShader(PixelShader_t shader) = 0;

    // Resets the vertex + pixel shader state
    virtual void ResetShaderState() = 0;

    // Returns the current vertex + pixel shaders
    virtual void *GetCurrentVertexShader() = 0;
    virtual void *GetCurrentPixelShader() = 0;

    virtual void ClearVertexAndPixelShaderRefCounts() = 0;
    virtual void PurgeUnusedVertexAndPixelShaders() = 0;

    // The low-level dx call to set the vertex shader state
    virtual void BindVertexShader(VertexShaderHandle_t shader) = 0;
    virtual void BindPixelShader(PixelShaderHandle_t shader) = 0;
};

//-----------------------------------------------------------------------------
//
// Methods related to setting vertex + pixel shader state
//
//-----------------------------------------------------------------------------
FORCEINLINE void IShaderManager::SetVertexShaderIndex(int vshIndex) { m_nVertexShaderIndex = vshIndex; }

FORCEINLINE void IShaderManager::SetPixelShaderIndex(int pshIndex) { m_nPixelShaderIndex = pshIndex; }

#define MAX_BONES 3

// debugging aid
#define MAX_SHADER_HISTORY 16

#define SHADER_FNAME_EXTENSION ".vcs"

static const char *GetLightTypeName(VertexShaderLightTypes_t type)
{
    static const char *s_VertexShaderLightTypeNames[] = {
        "LIGHT_NONE", "LIGHT_SPOT", "LIGHT_POINT", "LIGHT_DIRECTIONAL", "LIGHT_STATIC", "LIGHT_AMBIENTCUBE",
    };
    return s_VertexShaderLightTypeNames[type + 1];
}

//-----------------------------------------------------------------------------
// Used to find unique shaders
//-----------------------------------------------------------------------------
static int s_NumPixelShadersCreated = 0;
static int s_NumVertexShadersCreated = 0;

//-----------------------------------------------------------------------------
// The lovely low-level dx call to create a vertex shader
//-----------------------------------------------------------------------------
static HardwareShader_t CreateD3DVertexShader(DWORD *pByteCode, int numBytes, const char *pShaderName, char *debugLabel = NULL)
{
    if (!pByteCode)
    {
        Assert(0);
        return INVALID_HARDWARE_SHADER;
    }

    // Compute the vertex specification
    HardwareShader_t hShader;

    // HRESULT hr = g_pShaderDevice->CreateVertexShader(pByteCode, (IDirect3DVertexShader9 **)&hShader);
    HRESULT hr = -1;

    if (FAILED(hr))
    {
        Assert(0);
        hShader = INVALID_HARDWARE_SHADER;
    }
    else
    {
        s_NumVertexShadersCreated++;
    }
    return hShader;
}

//-----------------------------------------------------------------------------
// The lovely low-level dx call to create a pixel shader
//-----------------------------------------------------------------------------
static HardwareShader_t CreateD3DPixelShader(DWORD *pByteCode, unsigned int nCentroidMask, int numBytes, const char *pShaderName,
                                             char *debugLabel = NULL)
{
    if (!pByteCode)
        return INVALID_HARDWARE_SHADER;

    HardwareShader_t shader;

    // HRESULT hr = g_pShaderDevice->CreatePixelShader(pByteCode, (IDirect3DPixelShader9 **)&shader);
    HRESULT hr = -1;

    if (FAILED(hr))
    {
        Assert(0);
        shader = INVALID_HARDWARE_SHADER;
    }
    else
    {
        s_NumPixelShadersCreated++;
    }

    return shader;
}

template <class T> int BinarySearchCombos(uint32 nStaticComboID, int nCombos, T const *pRecords)
{
    // Use binary search - data is sorted
    int nLowerIdx = 1;
    int nUpperIdx = nCombos;
    for (;;)
    {
        if (nUpperIdx < nLowerIdx)
            return -1;

        int nMiddleIndex = (nLowerIdx + nUpperIdx) / 2;
        uint32 nProbe = pRecords[nMiddleIndex - 1].m_nStaticComboID;
        if (nStaticComboID < nProbe)
        {
            nUpperIdx = nMiddleIndex - 1;
        }
        else
        {
            if (nStaticComboID > nProbe)
                nLowerIdx = nMiddleIndex + 1;
            else
                return nMiddleIndex - 1;
        }
    }
}

inline int FindShaderStaticCombo(uint32 nStaticComboID, const ShaderHeader_t &header, StaticComboRecord_t *pRecords)
{
    if (header.m_nVersion < 5)
        return -1;

    return BinarySearchCombos(nStaticComboID, header.m_nNumStaticCombos, pRecords);
}

// cache redundant i/o fetched components of the vcs files
struct ShaderFileCache_t
{
    CUtlSymbol m_Name;
    CUtlSymbol m_Filename;
    ShaderHeader_t m_Header;
    bool m_bVertexShader;

    // valid for diff version only - contains the microcode used as the reference for diff algorithm
    CUtlBuffer m_ReferenceCombo;

    // valid for ver5 only - contains the directory
    CUtlVector<StaticComboRecord_t> m_StaticComboRecords;
    CUtlVector<StaticComboAliasRecord_t> m_StaticComboDupRecords;

    ShaderFileCache_t()
    {
        // invalid until version established
        m_Header.m_nVersion = 0;
    }

    bool IsValid() const { return m_Header.m_nVersion != 0; }

    bool IsOldVersion() const { return m_Header.m_nVersion < 5; }

    int IsVersion6() const { return (m_Header.m_nVersion == 6); }

    int FindCombo(uint32 nStaticComboID)
    {
        int nSearchAliases = BinarySearchCombos(nStaticComboID, m_StaticComboDupRecords.Count(), m_StaticComboDupRecords.Base());
        if (nSearchAliases != -1)
            nStaticComboID = m_StaticComboDupRecords[nSearchAliases].m_nSourceStaticCombo;
        return FindShaderStaticCombo(nStaticComboID, m_Header, m_StaticComboRecords.Base());
    }

    bool operator==(const ShaderFileCache_t &a) const { return m_Name == a.m_Name && m_bVertexShader == a.m_bVertexShader; }
};

//-----------------------------------------------------------------------------
// Vertex + pixel shader manager
//-----------------------------------------------------------------------------
class CShaderManagerVk : public IShaderManager
{
  public:
    CShaderManagerVk();
    virtual ~CShaderManagerVk();

    // Methods of IShaderManager
    virtual void Init();
    virtual void Shutdown();
    virtual IShaderBuffer *CompileShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion);
    virtual VertexShaderHandle_t CreateVertexShader(IShaderBuffer *pShaderBuffer);
    virtual void DestroyVertexShader(VertexShaderHandle_t hShader);
    virtual PixelShaderHandle_t CreatePixelShader(IShaderBuffer *pShaderBuffer);
    virtual void DestroyPixelShader(PixelShaderHandle_t hShader);
    virtual VertexShader_t CreateVertexShader(const char *pVertexShaderFile, int nStaticVshIndex = 0, char *debugLabel = NULL);
    virtual PixelShader_t CreatePixelShader(const char *pPixelShaderFile, int nStaticPshIndex = 0, char *debugLabel = NULL);
    virtual void SetVertexShader(VertexShader_t shader);
    virtual void SetPixelShader(PixelShader_t shader);
    virtual void BindVertexShader(VertexShaderHandle_t shader);
    virtual void BindPixelShader(PixelShaderHandle_t shader);
    virtual void *GetCurrentVertexShader();
    virtual void *GetCurrentPixelShader();
    virtual void ResetShaderState();
    void FlushShaders();
    virtual void ClearVertexAndPixelShaderRefCounts();
    virtual void PurgeUnusedVertexAndPixelShaders();
    void SpewVertexAndPixelShaders();
    const char *GetActiveVertexShaderName();
    const char *GetActivePixelShaderName();

  private:
    typedef CUtlFixedLinkedList<VkShaderModule *>::IndexType_t VertexShaderIndex_t;
    typedef CUtlFixedLinkedList<VkShaderModule *>::IndexType_t PixelShaderIndex_t;

    struct ShaderStaticCombos_t
    {
        int m_nCount;

        // Can't use CUtlVector here since you CUtlLinkedList<CUtlVector<>> doesn't work.
        HardwareShader_t *m_pHardwareShaders;
        struct ShaderCreationData_t
        {
            CUtlVector<uint8> ByteCode;
            uint32 iCentroidMask;
        };

        ShaderCreationData_t *m_pCreationData;
    };

    struct ShaderLookup_t
    {
        CUtlSymbol m_Name;
        int m_nStaticIndex;
        ShaderStaticCombos_t m_ShaderStaticCombos;
        DWORD m_Flags;
        int m_nRefCount;
        unsigned int m_hShaderFileCache;

        // for queued loading, bias an aligned optimal buffer forward to correct location
        int m_nDataOffset;

        // diff version, valid during load only
        ShaderDictionaryEntry_t *m_pComboDictionary;

        ShaderLookup_t()
        {
            m_Flags = 0;
            m_nRefCount = 0;
            m_ShaderStaticCombos.m_nCount = 0;
            m_ShaderStaticCombos.m_pHardwareShaders = 0;
            m_ShaderStaticCombos.m_pCreationData = 0;
            m_pComboDictionary = NULL;
        }
        void IncRefCount() { m_nRefCount++; }
        bool operator==(const ShaderLookup_t &a) const { return m_Name == a.m_Name && m_nStaticIndex == a.m_nStaticIndex; }
    };

  private:
    // The low-level dx call to set the vertex shader state
    void SetVertexShaderState(HardwareShader_t shader, DataCacheHandle_t hCachedShader = DC_INVALID_HANDLE);

    // The low-level dx call to set the pixel shader state
    void SetPixelShaderState(HardwareShader_t shader, DataCacheHandle_t hCachedShader = DC_INVALID_HANDLE);

    // Destroys all shaders
    void DestroyAllShaders();

    // Destroy a particular vertex shader
    void DestroyVertexShader(VertexShader_t shader);
    // Destroy a particular pixel shader
    void DestroyPixelShader(PixelShader_t shader);

    bool LoadAndCreateShaders(ShaderLookup_t &lookup, bool bVertexShader, char *debugLabel = NULL);
    FileHandle_t OpenFileAndLoadHeader(const char *pFileName, ShaderHeader_t *pHeader);

    void WriteTranslatedFile(ShaderLookup_t *pLookup, int dynamicCombo, char *pFileContents, char *pFileExtension);

    CUtlFixedLinkedList<ShaderLookup_t> m_VertexShaderDict;
    CUtlFixedLinkedList<ShaderLookup_t> m_PixelShaderDict;

    CUtlSymbolTable m_ShaderSymbolTable;

    // The current vertex and pixel shader
    HardwareShader_t m_HardwareVertexShader;
    HardwareShader_t m_HardwarePixelShader;

    CUtlFixedLinkedList<VkShaderModule> m_RawVertexShaderDict;
    CUtlFixedLinkedList<VkShaderModule> m_RawPixelShaderDict;

    CUtlFixedLinkedList<ShaderFileCache_t> m_ShaderFileCache;
};

extern CShaderManagerVk *g_pShaderManager;

// Copied from glslang/StandAlone/ResourceLimits.cpp
// VK_TOOD: make sure this is reasonable
const TBuiltInResource DefaultTBuiltInResource = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /* .limits = */
    {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
    }};

#endif // SHADERMANAGERVK_H