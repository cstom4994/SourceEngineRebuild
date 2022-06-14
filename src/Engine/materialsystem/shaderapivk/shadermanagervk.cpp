#include "shadermanagervk.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "KeyValues.h"
#include "convar.h"
#include "datacache/idatacache.h"
#include "filesystem.h"
#include "filesystem/IQueuedLoader.h"
#include "localvktypes.h"
#include "materialsystem/IShader.h"
#include "materialsystem/shader_vcs_version.h"
#include "shaderdevicevk.h"
#include "tier0/dbg.h"
#include "tier0/icommandline.h"
#include "tier1/diff.h"
#include "tier1/lzmaDecoder.h"
#include "tier1/utlbuffer.h"
#include "tier1/utllinkedlist.h"
#include "tier1/utlsymbol.h"
#include "tier1/utlvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//#define DISASSEMBLE_SPIRV

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
static CShaderManagerVk g_ShaderManagerVk;
CShaderManagerVk *g_pShaderManager = &g_ShaderManagerVk;

//-----------------------------------------------------------------------------
// Constructor, destructor
//-----------------------------------------------------------------------------
CShaderManagerVk::CShaderManagerVk()
    : m_ShaderSymbolTable(0, 32, true /* caseInsensitive */), m_VertexShaderDict(32), m_PixelShaderDict(32), m_ShaderFileCache(32)
{
}

CShaderManagerVk::~CShaderManagerVk() {}

//-----------------------------------------------------------------------------
// Initialization, shutdown
//-----------------------------------------------------------------------------
void CShaderManagerVk::Init() { glslang::InitializeProcess(); }

void CShaderManagerVk::Shutdown()
{
    DestroyAllShaders();
    glslang::FinalizeProcess();
}

//-----------------------------------------------------------------------------
// Compiles shaders
//-----------------------------------------------------------------------------
IShaderBuffer *CShaderManagerVk::CompileShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion)
{
    EShLanguage stage = EShLangVertex; // VK_TODO: Handle pixel shaders
    glslang::TProgram &program = *new glslang::TProgram;
    glslang::TShader *shader = new glslang::TShader(stage);
    TBuiltInResource Resources = DefaultTBuiltInResource;
    EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules | EShMsgReadHlsl | EShMsgHlslLegalization);
    const char *pShaderStrings[1];
    pShaderStrings[0] = pProgram;

    shader->setStrings(pShaderStrings, 1);

    if (!shader->parse(&Resources, 110, false, messages))
    {
        Warning(shader->getInfoLog());
        Warning(shader->getInfoDebugLog());
        return nullptr;
    }

    program.addShader(shader);
    if (!program.link(messages))
    {
        Warning(program.getInfoLog());
        Warning(program.getInfoDebugLog());
        return nullptr;
    }

    stage = EShLangVertex; // VK_FIXME: Gets changed by program.link() for some reason
    auto *spirv = new std::vector<uint32_t>;
    auto *logger = new spv::SpvBuildLogger;
    auto *spvOptions = new glslang::SpvOptions;

#ifdef DEBUG
    spvOptions->generateDebugInfo = true;
    spvOptions->stripDebugInfo = false;
    spvOptions->disableOptimizer = true;
    spvOptions->optimizeSize = false;
    spvOptions->disassemble = false;
    spvOptions->validate = true;
#else
    spvOptions->generateDebugInfo = false;
    spvOptions->stripDebugInfo = true;
    spvOptions->disableOptimizer = false;
    spvOptions->optimizeSize = true;
    spvOptions->disassemble = false;
#endif

    const glslang::TIntermediate *intermediate = program.getIntermediate(stage);
    if (!intermediate)
    {
        Warning(program.getInfoLog());
        Warning(program.getInfoDebugLog());
        return nullptr;
    }

    // VK_FIXME: stack corrupt
    glslang::GlslangToSpv(*intermediate, *spirv, logger, spvOptions);

#ifdef DISASSEMBLE_SPIRV
    std::ostringstream stream;
    spv::Disassemble(stream, *spirv);
    Msg(stream.str().c_str());
#endif

    auto *pShaderBuffer = new CShaderBuffer<std::vector<uint32_t>>(spirv);

    delete &program;
    delete shader;
    delete spvOptions;
    delete logger;

    return pShaderBuffer;
}

VertexShaderHandle_t CShaderManagerVk::CreateVertexShader(IShaderBuffer *pShaderBuffer)
{
    const uint32_t *code = (uint32_t *)pShaderBuffer->GetBits();
    const size_t size = pShaderBuffer->GetSize() * sizeof(uint32_t);

    VkShaderModule shaderModule = g_pShaderDevice->CreateShaderModule(code, size);

    s_NumVertexShadersCreated++;

    VertexShaderIndex_t i = m_RawVertexShaderDict.AddToTail(shaderModule);
    return (VertexShaderHandle_t)i;
}

void CShaderManagerVk::DestroyVertexShader(VertexShaderHandle_t hShader)
{
    if (hShader == VERTEX_SHADER_HANDLE_INVALID)
        return;

    auto i = (VertexShaderIndex_t)hShader;
    VkShaderModule shaderModule = m_RawVertexShaderDict[i];
    vkDestroyShaderModule(g_pShaderDevice->GetVkDevice(), shaderModule, g_pAllocCallbacks);

    m_RawVertexShaderDict.Remove(i);
}

PixelShaderHandle_t CShaderManagerVk::CreatePixelShader(IShaderBuffer *pShaderBuffer)
{
    const uint32_t *code = (uint32_t *)pShaderBuffer->GetBits();
    const size_t size = pShaderBuffer->GetSize() * sizeof(uint32_t);

    VkShaderModule shaderModule = g_pShaderDevice->CreateShaderModule(code, size);

    s_NumPixelShadersCreated++;

    PixelShaderIndex_t i = m_RawPixelShaderDict.AddToTail(shaderModule);
    return (PixelShaderHandle_t)i;
}

void CShaderManagerVk::DestroyPixelShader(PixelShaderHandle_t hShader)
{
    if (hShader == PIXEL_SHADER_HANDLE_INVALID)
        return;

    auto i = (PixelShaderIndex_t)hShader;
    VkShaderModule shaderModule = m_RawPixelShaderDict[i];
    vkDestroyShaderModule(g_pShaderDevice->GetVkDevice(), shaderModule, g_pAllocCallbacks);

    m_RawPixelShaderDict.Remove(i);
}

//-----------------------------------------------------------------------------
// Open the shader file, optionally gets the header
//-----------------------------------------------------------------------------
FileHandle_t CShaderManagerVk::OpenFileAndLoadHeader(const char *pFileName, ShaderHeader_t *pHeader)
{
    FileHandle_t fp = g_pFullFileSystem->Open(pFileName, "rb", "GAME");
    if (fp == FILESYSTEM_INVALID_HANDLE)
    {
        return FILESYSTEM_INVALID_HANDLE;
    }

    if (pHeader)
    {
        // read the header
        g_pFullFileSystem->Read(pHeader, sizeof(ShaderHeader_t), fp);

        switch (pHeader->m_nVersion)
        {
        case 4:
            // version with combos done as diffs vs a reference combo
            // vsh/psh or older fxc
            break;

        case 5:
        case 6:
            // version with optimal dictionary and compressed combo block
            break;

        default:
            Assert(0);
            Warning("Shader %s is the wrong version %d, expecting %d\n", pFileName, pHeader->m_nVersion, SHADER_VCS_VERSION_NUMBER);
            g_pFullFileSystem->Close(fp);
            return FILESYSTEM_INVALID_HANDLE;
        }
    }

    return fp;
}

//---------------------------------------------------------------------------------------------------------
// Writes text files named for looked-up shaders.  Used by GL shader translator to dump code for debugging
//---------------------------------------------------------------------------------------------------------
void CShaderManagerVk::WriteTranslatedFile(ShaderLookup_t *pLookup, int dynamicCombo, char *pFileContents, char *pFileExtension)
{
    const char *pName = m_ShaderSymbolTable.String(pLookup->m_Name);
    int nNumChars = V_strlen(pFileContents);

    CUtlBuffer tempBuffer;
    tempBuffer.SetBufferType(true, false);
    tempBuffer.EnsureCapacity(nNumChars);
    memcpy((char *)tempBuffer.Base(), pFileContents, nNumChars);
    tempBuffer.SeekPut(CUtlBuffer::SEEK_CURRENT, nNumChars);

    char filename[MAX_PATH];
    sprintf(filename, "%s_%d_%d.%s", pName, pLookup->m_nStaticIndex, dynamicCombo, pFileExtension);
    g_pFullFileSystem->WriteFile(filename, "DEFAULT_WRITE_PATH", tempBuffer);
}

//-----------------------------------------------------------------------------
// Loads all shaders
//-----------------------------------------------------------------------------
bool CShaderManagerVk::LoadAndCreateShaders(ShaderLookup_t &lookup, bool bVertexShader, char *debugLabel)
{
    const char *pName = m_ShaderSymbolTable.String(lookup.m_Name);

    // find it in the cache
    // a cache hit prevents costly i/o for static components, i.e. header, ref combo, etc.
    ShaderFileCache_t fileCacheLookup;
    fileCacheLookup.m_Name = lookup.m_Name;
    fileCacheLookup.m_bVertexShader = bVertexShader;
    int fileCacheIndex = m_ShaderFileCache.Find(fileCacheLookup);
    if (fileCacheIndex == m_ShaderFileCache.InvalidIndex())
    {
        // not found, create a new entry
        fileCacheIndex = m_ShaderFileCache.AddToTail();
    }

    lookup.m_hShaderFileCache = fileCacheIndex;

    // fetch from cache
    ShaderFileCache_t *pFileCache = &m_ShaderFileCache[fileCacheIndex];
    ShaderHeader_t *pHeader = &pFileCache->m_Header;

    FileHandle_t hFile = FILESYSTEM_INVALID_HANDLE;
    if (pFileCache->IsValid())
    {
        // using cached header, just open file, no read of header needed
        hFile = OpenFileAndLoadHeader(m_ShaderSymbolTable.String(pFileCache->m_Filename), NULL);
        if (hFile == FILESYSTEM_INVALID_HANDLE)
        {
            // shouldn't happen
            Assert(0);
            return false;
        }
    }
    else
    {
        V_memset(pHeader, 0, sizeof(ShaderHeader_t));

        // try the vsh/psh dir first
        char filename[MAX_PATH];
        Q_snprintf(filename, MAX_PATH, "shaders\\%s\\%s" SHADER_FNAME_EXTENSION, bVertexShader ? "vsh" : "psh", pName);
        hFile = OpenFileAndLoadHeader(filename, pHeader);
        if (hFile == FILESYSTEM_INVALID_HANDLE)
        {
            // next, try the fxc dir
            Q_snprintf(filename, MAX_PATH, "shaders\\fxc\\%s" SHADER_FNAME_EXTENSION, pName);
            hFile = OpenFileAndLoadHeader(filename, pHeader);
            if (hFile == FILESYSTEM_INVALID_HANDLE)
            {
                lookup.m_Flags |= SHADER_FAILED_LOAD;
                Warning("Couldn't load %s shader %s\n", bVertexShader ? "vertex" : "pixel", pName);
                return false;
            }
        }

        lookup.m_Flags = pHeader->m_nFlags;

        pFileCache->m_Name = lookup.m_Name;
        pFileCache->m_Filename = m_ShaderSymbolTable.AddString(filename);
        pFileCache->m_bVertexShader = bVertexShader;

        if (pFileCache->IsOldVersion())
        {
            int referenceComboSize = ((ShaderHeader_t_v4 *)pHeader)->m_nDiffReferenceSize;
            if (referenceComboSize)
            {
                // cache the reference combo
                pFileCache->m_ReferenceCombo.EnsureCapacity(referenceComboSize);
                g_pFullFileSystem->Read(pFileCache->m_ReferenceCombo.Base(), referenceComboSize, hFile);
            }
        }
        else
        {
            // cache the dictionary
            pFileCache->m_StaticComboRecords.EnsureCount(pHeader->m_nNumStaticCombos);
            g_pFullFileSystem->Read(pFileCache->m_StaticComboRecords.Base(), pHeader->m_nNumStaticCombos * sizeof(StaticComboRecord_t),
                                    hFile);
            if (pFileCache->IsVersion6())
            {
                // read static combo alias records
                int nNumDups;
                g_pFullFileSystem->Read(&nNumDups, sizeof(nNumDups), hFile);
                if (nNumDups)
                {
                    pFileCache->m_StaticComboDupRecords.EnsureCount(nNumDups);
                    g_pFullFileSystem->Read(pFileCache->m_StaticComboDupRecords.Base(), nNumDups * sizeof(StaticComboAliasRecord_t), hFile);
                }
            }
        }
    }

    // FIXME: should make lookup and ShaderStaticCombos_t are pool allocated.
    int i;
    lookup.m_ShaderStaticCombos.m_nCount = pHeader->m_nDynamicCombos;
    lookup.m_ShaderStaticCombos.m_pHardwareShaders = new HardwareShader_t[pHeader->m_nDynamicCombos];
    for (i = 0; i < pHeader->m_nDynamicCombos; i++)
    {
        lookup.m_ShaderStaticCombos.m_pHardwareShaders[i] = INVALID_HARDWARE_SHADER;
    }

    int nStartingOffset = 0;
    int nEndingOffset = 0;

    if (pFileCache->IsOldVersion())
    {
        int nDictionaryOffset = sizeof(ShaderHeader_t) + ((ShaderHeader_t_v4 *)pHeader)->m_nDiffReferenceSize;

        // read in shader's dynamic combos directory
        lookup.m_pComboDictionary = new ShaderDictionaryEntry_t[pHeader->m_nDynamicCombos];
        g_pFullFileSystem->Seek(hFile, nDictionaryOffset + lookup.m_nStaticIndex * sizeof(ShaderDictionaryEntry_t), FILESYSTEM_SEEK_HEAD);
        g_pFullFileSystem->Read(lookup.m_pComboDictionary, pHeader->m_nDynamicCombos * sizeof(ShaderDictionaryEntry_t), hFile);

        // want single read of all this shader's dynamic combos into a target buffer
        // shaders are written sequentially, determine starting offset and length
        for (i = 0; i < pHeader->m_nDynamicCombos; i++)
        {
            if (lookup.m_pComboDictionary[i].m_Offset == -1)
            {
                // skipped
                continue;
            }

            // ensure offsets are in fact sequentially ascending
            Assert(lookup.m_pComboDictionary[i].m_Offset >= nStartingOffset && lookup.m_pComboDictionary[i].m_Size >= 0);

            if (!nStartingOffset)
            {
                nStartingOffset = lookup.m_pComboDictionary[i].m_Offset;
            }
            nEndingOffset = lookup.m_pComboDictionary[i].m_Offset + lookup.m_pComboDictionary[i].m_Size;
        }
        if (!nStartingOffset)
        {
            g_pFullFileSystem->Close(hFile);
            Warning("Shader '%s' - All dynamic combos skipped. This is bad!\n", m_ShaderSymbolTable.String(pFileCache->m_Filename));
            return false;
        }
    }
    else
    {
        int nStaticComboIdx = pFileCache->FindCombo(lookup.m_nStaticIndex / pFileCache->m_Header.m_nDynamicCombos);
        if (nStaticComboIdx == -1)
        {
            g_pFullFileSystem->Close(hFile);
            lookup.m_Flags |= SHADER_FAILED_LOAD;
            Warning("Shader '%s' - Couldn't load combo %d of shader (dyn=%d)\n", m_ShaderSymbolTable.String(pFileCache->m_Filename),
                    lookup.m_nStaticIndex, pFileCache->m_Header.m_nDynamicCombos);
            return false;
        }

        nStartingOffset = pFileCache->m_StaticComboRecords[nStaticComboIdx].m_nFileOffset;
        nEndingOffset = pFileCache->m_StaticComboRecords[nStaticComboIdx + 1].m_nFileOffset;
    }

    // align offsets for unbuffered optimal i/o - fastest i/o possible
    unsigned nOffsetAlign, nSizeAlign, nBufferAlign;
    g_pFullFileSystem->GetOptimalIOConstraints(hFile, &nOffsetAlign, &nSizeAlign, &nBufferAlign);
    unsigned int nAlignedOffset = AlignValue((nStartingOffset - nOffsetAlign) + 1, nOffsetAlign);
    unsigned int nAlignedBytesToRead = AlignValue(nEndingOffset - nAlignedOffset, nSizeAlign);

    // used for adjusting provided buffer to actual data
    lookup.m_nDataOffset = nStartingOffset - nAlignedOffset;

    bool bOK = true;

    // printf("\n CShaderManagerVk::LoadAndCreateShaders - reading %d bytes from file offset %d", nAlignedBytesToRead, nAlignedOffset);
    // single optimal read of all dynamic combos into monolithic buffer
    uint8 *pOptimalBuffer = (uint8 *)g_pFullFileSystem->AllocOptimalReadBuffer(hFile, nAlignedBytesToRead, nAlignedOffset);
    g_pFullFileSystem->Seek(hFile, nAlignedOffset, FILESYSTEM_SEEK_HEAD);
    g_pFullFileSystem->Read(pOptimalBuffer, nAlignedBytesToRead, hFile);

    if (pFileCache->IsOldVersion())
    {
        // bOK = CreateDynamicCombos_Ver4(&lookup, pOptimalBuffer);
        bOK = false;
    }

    g_pFullFileSystem->FreeOptimalReadBuffer(pOptimalBuffer);

    g_pFullFileSystem->Close(hFile);

    if (!bOK)
    {
        lookup.m_Flags |= SHADER_FAILED_LOAD;
    }

    return bOK;
}

//-----------------------------------------------------------------------------
// Creates and destroys vertex shaders
//-----------------------------------------------------------------------------
VertexShader_t CShaderManagerVk::CreateVertexShader(const char *pFileName, int nStaticVshIndex, char *debugLabel)
{
    MEM_ALLOC_CREDIT();

    if (!pFileName)
    {
        return INVALID_SHADER;
    }

    VertexShader_t shader;
    ShaderLookup_t lookup;
    lookup.m_Name = m_ShaderSymbolTable.AddString(pFileName);
    lookup.m_nStaticIndex = nStaticVshIndex;
    shader = m_VertexShaderDict.Find(lookup);
    if (shader == m_VertexShaderDict.InvalidIndex())
    {
        // printf("\nCShaderManager::CreateVertexShader( filename = %s, staticVshIndex = %d - not in cache", pFileName, nStaticVshIndex );

        shader = m_VertexShaderDict.AddToTail(lookup);
        if (!LoadAndCreateShaders(m_VertexShaderDict[shader], true, debugLabel))
        {
            return INVALID_SHADER;
        }
    }
    m_VertexShaderDict[shader].IncRefCount();
    return shader;
}

//-----------------------------------------------------------------------------
// Create pixel shader
//-----------------------------------------------------------------------------
PixelShader_t CShaderManagerVk::CreatePixelShader(const char *pFileName, int nStaticPshIndex, char *debugLabel)
{
    MEM_ALLOC_CREDIT();

    if (!pFileName)
    {
        return INVALID_SHADER;
    }

    PixelShader_t shader;
    ShaderLookup_t lookup;
    lookup.m_Name = m_ShaderSymbolTable.AddString(pFileName);
    lookup.m_nStaticIndex = nStaticPshIndex;
    shader = m_PixelShaderDict.Find(lookup);
    if (shader == m_PixelShaderDict.InvalidIndex())
    {
        shader = m_PixelShaderDict.AddToTail(lookup);
        if (!LoadAndCreateShaders(m_PixelShaderDict[shader], false, debugLabel))
        {
            return INVALID_SHADER;
        }
    }
    m_PixelShaderDict[shader].IncRefCount();
    return shader;
}

//-----------------------------------------------------------------------------
// Clear the refCounts to zero
//-----------------------------------------------------------------------------
void CShaderManagerVk::ClearVertexAndPixelShaderRefCounts()
{
    for (VertexShader_t vshIndex = m_VertexShaderDict.Head(); vshIndex != m_VertexShaderDict.InvalidIndex();
         vshIndex = m_VertexShaderDict.Next(vshIndex))
    {
        m_VertexShaderDict[vshIndex].m_nRefCount = 0;
    }

    for (PixelShader_t pshIndex = m_PixelShaderDict.Head(); pshIndex != m_PixelShaderDict.InvalidIndex();
         pshIndex = m_PixelShaderDict.Next(pshIndex))
    {
        m_PixelShaderDict[pshIndex].m_nRefCount = 0;
    }
}

//-----------------------------------------------------------------------------
// Destroy all shaders that have no reference
//-----------------------------------------------------------------------------
void CShaderManagerVk::PurgeUnusedVertexAndPixelShaders()
{
    // iterate vertex shaders
    for (VertexShader_t vshIndex = m_VertexShaderDict.Head(); vshIndex != m_VertexShaderDict.InvalidIndex();)
    {
        Assert(m_VertexShaderDict[vshIndex].m_nRefCount >= 0);

        // Get the next one before we potentially delete the current one.
        VertexShader_t next = m_VertexShaderDict.Next(vshIndex);
        if (m_VertexShaderDict[vshIndex].m_nRefCount <= 0)
        {
            DestroyVertexShader(vshIndex);
        }
        vshIndex = next;
    }

    // iterate pixel shaders
    for (PixelShader_t pshIndex = m_PixelShaderDict.Head(); pshIndex != m_PixelShaderDict.InvalidIndex();)
    {
        Assert(m_PixelShaderDict[pshIndex].m_nRefCount >= 0);

        // Get the next one before we potentially delete the current one.
        PixelShader_t next = m_PixelShaderDict.Next(pshIndex);
        if (m_PixelShaderDict[pshIndex].m_nRefCount <= 0)
        {
            DestroyPixelShader(pshIndex);
        }
        pshIndex = next;
    }
}

void *CShaderManagerVk::GetCurrentVertexShader() { return (void *)m_HardwareVertexShader; }

void *CShaderManagerVk::GetCurrentPixelShader() { return (void *)m_HardwarePixelShader; }

//-----------------------------------------------------------------------------
// The low-level dx call to set the vertex shader state
//-----------------------------------------------------------------------------
void CShaderManagerVk::SetVertexShaderState(HardwareShader_t shader, DataCacheHandle_t hCachedShader)
{
    if (m_HardwareVertexShader != shader)
    {
        // g_pShaderDevice->SetVertexShader((IDirect3DVertexShader9 *)shader);
        m_HardwareVertexShader = shader;
    }
}

void CShaderManagerVk::BindVertexShader(VertexShaderHandle_t hVertexShader)
{
    auto hHardwareShader = (HardwareShader_t *)m_RawVertexShaderDict[(VertexShaderIndex_t)hVertexShader];
    SetVertexShaderState(hHardwareShader);
}

//-----------------------------------------------------------------------------
// Sets a particular vertex shader as the current shader
//-----------------------------------------------------------------------------
void CShaderManagerVk::SetVertexShader(VertexShader_t shader)
{
    // Determine which vertex shader to use...
    if (shader == INVALID_SHADER)
    {
        SetVertexShaderState(0);
        return;
    }

    int vshIndex = m_nVertexShaderIndex;
    Assert(vshIndex >= 0);
    if (vshIndex < 0)
    {
        vshIndex = 0;
    }

    ShaderLookup_t &vshLookup = m_VertexShaderDict[shader];
    //	Warning( "vsh: %s static: %d dynamic: %d\n", m_ShaderSymbolTable.String( vshLookup.m_Name ),
    //		vshLookup.m_nStaticIndex, m_nVertexShaderIndex );

    if (vshLookup.m_Flags & SHADER_FAILED_LOAD)
    {
        Assert(0);
        return;
    }

    Assert(vshIndex < vshLookup.m_ShaderStaticCombos.m_nCount);
    HardwareShader_t dxshader = vshLookup.m_ShaderStaticCombos.m_pHardwareShaders[vshIndex];

    Assert(dxshader);

    if (!dxshader)
    {
        Error("!!!!!Using invalid shader combo!!!!!  Consult a programmer and tell them to build debug materialsystem.dll and "
              "stdshader*.dll.  Run with \"mat_bufferprimitives 0\" and look for CMaterial in the call stack and see what m_pDebugName is. "
              " You are likely using a shader combo that has been skipped.\n");
    }

    SetVertexShaderState(dxshader);
}

//-----------------------------------------------------------------------------
// The low-level dx call to set the pixel shader state
//-----------------------------------------------------------------------------
void CShaderManagerVk::SetPixelShaderState(HardwareShader_t shader, DataCacheHandle_t hCachedShader)
{
    if (m_HardwarePixelShader != shader)
    {
        // g_pShaderDevice->SetPixelShader((IDirect3DPixelShader *)shader);
        m_HardwarePixelShader = shader;
    }
}

void CShaderManagerVk::BindPixelShader(PixelShaderHandle_t hPixelShader)
{
    auto hHardwareShader = (HardwareShader_t *)m_RawPixelShaderDict[(PixelShaderIndex_t)hPixelShader];
    SetPixelShaderState(hHardwareShader);
}

//-----------------------------------------------------------------------------
// Sets a particular pixel shader as the current shader
//-----------------------------------------------------------------------------
void CShaderManagerVk::SetPixelShader(PixelShader_t shader)
{
    if (shader == INVALID_SHADER)
    {
        SetPixelShaderState(0);
        return;
    }

    int pshIndex = m_nPixelShaderIndex;
    Assert(pshIndex >= 0);
    ShaderLookup_t &pshLookup = m_PixelShaderDict[shader];
    //	Warning( "psh: %s static: %d dynamic: %d\n", m_ShaderSymbolTable.String( pshLookup.m_Name ),
    //		pshLookup.m_nStaticIndex, m_nPixelShaderIndex );

    if (pshLookup.m_Flags & SHADER_FAILED_LOAD)
    {
        Assert(0);
        return;
    }

    HardwareShader_t dxshader = pshLookup.m_ShaderStaticCombos.m_pHardwareShaders[pshIndex];

    AssertMsg(dxshader != INVALID_HARDWARE_SHADER, "Failed to set pixel shader.");
    SetPixelShaderState(dxshader);
}

//-----------------------------------------------------------------------------
// Resets the shader state
//-----------------------------------------------------------------------------
void CShaderManagerVk::ResetShaderState()
{
    // This will force the calls to SetVertexShader + SetPixelShader to actually set the state
    m_HardwareVertexShader = (HardwareShader_t)-1;
    m_HardwarePixelShader = (HardwareShader_t)-1;

    SetVertexShader(INVALID_SHADER);
    SetPixelShader(INVALID_SHADER);
}

//-----------------------------------------------------------------------------
// Destroy a particular vertex shader
//-----------------------------------------------------------------------------
void CShaderManagerVk::DestroyVertexShader(VertexShader_t shader)
{
    ShaderStaticCombos_t &combos = m_VertexShaderDict[shader].m_ShaderStaticCombos;
    int i;
    for (i = 0; i < combos.m_nCount; i++)
    {
        if (combos.m_pHardwareShaders[i] != INVALID_HARDWARE_SHADER)
        {
        }
    }
    delete[] combos.m_pHardwareShaders;
    combos.m_pHardwareShaders = NULL;

    if (combos.m_pCreationData != NULL)
    {
        delete[] combos.m_pCreationData;
        combos.m_pCreationData = NULL;
    }

    m_VertexShaderDict.Remove(shader);
}

//-----------------------------------------------------------------------------
// Destroy a particular pixel shader
//-----------------------------------------------------------------------------
void CShaderManagerVk::DestroyPixelShader(PixelShader_t pixelShader)
{
    ShaderStaticCombos_t &combos = m_PixelShaderDict[pixelShader].m_ShaderStaticCombos;
    int i;
    for (i = 0; i < combos.m_nCount; i++)
    {
        if (combos.m_pHardwareShaders[i] != INVALID_HARDWARE_SHADER)
        {
        }
    }
    delete[] combos.m_pHardwareShaders;
    combos.m_pHardwareShaders = NULL;

    if (combos.m_pCreationData != NULL)
    {
        delete[] combos.m_pCreationData;
        combos.m_pCreationData = NULL;
    }

    m_PixelShaderDict.Remove(pixelShader);
}

//-----------------------------------------------------------------------------
// Destroys all shaders
//-----------------------------------------------------------------------------
void CShaderManagerVk::DestroyAllShaders(void)
{
    for (VertexShader_t vshIndex = m_VertexShaderDict.Head(); vshIndex != m_VertexShaderDict.InvalidIndex();)
    {
        Assert(m_VertexShaderDict[vshIndex].m_nRefCount >= 0);
        VertexShader_t next = m_VertexShaderDict.Next(vshIndex);
        DestroyVertexShader(vshIndex);
        vshIndex = next;
    }

    for (PixelShader_t pshIndex = m_PixelShaderDict.Head(); pshIndex != m_PixelShaderDict.InvalidIndex();)
    {
        Assert(m_PixelShaderDict[pshIndex].m_nRefCount >= 0);
        PixelShader_t next = m_PixelShaderDict.Next(pshIndex);
        DestroyPixelShader(pshIndex);
        pshIndex = next;
    }

    // invalidate the file cache
    m_ShaderFileCache.Purge();
}

//-----------------------------------------------------------------------------
// print all vertex and pixel shaders along with refcounts to the console
//-----------------------------------------------------------------------------
void CShaderManagerVk::SpewVertexAndPixelShaders(void)
{
    // only spew a populated shader file cache
    Msg("\nShader File Cache:\n");
    for (int cacheIndex = m_ShaderFileCache.Head(); cacheIndex != m_ShaderFileCache.InvalidIndex();
         cacheIndex = m_ShaderFileCache.Next(cacheIndex))
    {
        ShaderFileCache_t *pCache = &m_ShaderFileCache[cacheIndex];
        Msg("Total Combos:%9d Static:%9d Dynamic:%7d SeekTable:%7d Ver:%d '%s'\n", pCache->m_Header.m_nTotalCombos,
            pCache->m_Header.m_nTotalCombos / pCache->m_Header.m_nDynamicCombos, pCache->m_Header.m_nDynamicCombos,
            pCache->IsOldVersion() ? 0 : pCache->m_Header.m_nNumStaticCombos, pCache->m_Header.m_nVersion,
            m_ShaderSymbolTable.String(pCache->m_Filename));
    }
    Msg("\n");

    // spew vertex shader dictionary
    int totalVertexShaders = 0;
    int totalVertexShaderSets = 0;
    for (VertexShader_t vshIndex = m_VertexShaderDict.Head(); vshIndex != m_VertexShaderDict.InvalidIndex();
         vshIndex = m_VertexShaderDict.Next(vshIndex))
    {
        const ShaderLookup_t &lookup = m_VertexShaderDict[vshIndex];
        const char *pName = m_ShaderSymbolTable.String(lookup.m_Name);
        Msg("vsh 0x%8.8x: static combo:%9d dynamic combos:%6d refcount:%4d \"%s\"\n", vshIndex, (int)lookup.m_nStaticIndex,
            (int)lookup.m_ShaderStaticCombos.m_nCount, lookup.m_nRefCount, pName);
        totalVertexShaders += lookup.m_ShaderStaticCombos.m_nCount;
        totalVertexShaderSets++;
    }

    // spew pixel shader dictionary
    int totalPixelShaders = 0;
    int totalPixelShaderSets = 0;
    for (PixelShader_t pshIndex = m_PixelShaderDict.Head(); pshIndex != m_PixelShaderDict.InvalidIndex();
         pshIndex = m_PixelShaderDict.Next(pshIndex))
    {
        const ShaderLookup_t &lookup = m_PixelShaderDict[pshIndex];
        const char *pName = m_ShaderSymbolTable.String(lookup.m_Name);
        Msg("psh 0x%8.8x: static combo:%9d dynamic combos:%6d refcount:%4d \"%s\"\n", pshIndex, (int)lookup.m_nStaticIndex,
            (int)lookup.m_ShaderStaticCombos.m_nCount, lookup.m_nRefCount, pName);
        totalPixelShaders += lookup.m_ShaderStaticCombos.m_nCount;
        totalPixelShaderSets++;
    }

    Msg("Total unique vertex shaders: %d\n", totalVertexShaders);
    Msg("Total vertex shader sets: %d\n", totalVertexShaderSets);
    Msg("Total unique pixel shaders: %d\n", totalPixelShaders);
    Msg("Total pixel shader sets: %d\n", totalPixelShaderSets);
}

CON_COMMAND(mat_spewvertexandpixelshaders, "Print all vertex and pixel shaders currently loaded to the console")
{
    g_pShaderManager->SpewVertexAndPixelShaders();
}

const char *CShaderManagerVk::GetActiveVertexShaderName() { return ""; }

const char *CShaderManagerVk::GetActivePixelShaderName() { return ""; }

CON_COMMAND(mat_shadercount, "display count of all shaders and reset that count")
{
    Warning("Num Pixel Shaders = %d Vertex Shaders=%d\n", s_NumPixelShadersCreated, s_NumVertexShadersCreated);
    s_NumVertexShadersCreated = 0;
    s_NumPixelShadersCreated = 0;
}
