#include "meshmgrvk.h"
#include "convar.h"
#include "indexbuffervk.h"
#include "shaderapivk.h"
#include "vprof.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
static CMeshMgrVk g_MeshManagerVk;
CMeshMgrVk *g_pMeshMgr = &g_MeshManagerVk;

//-----------------------------------------------------------------------------
//
// Mesh manager implementation
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Constructor, destructor
//-----------------------------------------------------------------------------
CMeshMgrVk::CMeshMgrVk()
    : m_pDynamicIndexBuffer(0), m_DynamicTempMesh(true), m_pVertexIDBuffer(0), m_pCurrentVertexBuffer(NULL), m_CurrentVertexFormat(0),
      m_pCurrentIndexBuffer(NULL),
      m_DynamicIndexBuffer(SHADER_BUFFER_TYPE_DYNAMIC, MATERIAL_INDEX_FORMAT_16BIT, INDEX_BUFFER_SIZE, "dynamic", false),
      m_DynamicVertexBuffer(SHADER_BUFFER_TYPE_DYNAMIC, VERTEX_FORMAT_UNKNOWN, 0, "dynamic", false)
{
    m_bUseFatVertices = false;
    m_nIndexBufferOffset = 0;
    memset(m_pVertexBufferOffset, 0, sizeof(m_pVertexBufferOffset));
    memset(m_pCurrentVertexStride, 0, sizeof(m_pCurrentVertexStride));
    memset(m_pFirstVertex, 0, sizeof(m_pFirstVertex));
    memset(m_pVertexCount, 0, sizeof(m_pVertexCount));
    m_nUnusedVertexFields = 0;
    m_nUnusedTextureCoords = 0;
}

CMeshMgrVk::~CMeshMgrVk() {}

//-----------------------------------------------------------------------------
// Initialize, shutdown
//-----------------------------------------------------------------------------
void CMeshMgrVk::Init()
{
    m_DynamicMesh.Init(0);
    m_DynamicFlexMesh.Init(1);

    // VK_TODO: is this needed? already initialized in constructor..
    // The dynamic index buffer
    m_pDynamicIndexBuffer = (CIndexBufferVk *)g_pShaderDevice->CreateIndexBuffer(SHADER_BUFFER_TYPE_DYNAMIC, MATERIAL_INDEX_FORMAT_UNKNOWN,
                                                                                 INDEX_BUFFER_SIZE, "dynamic");

    // If we're running in vs3.0, allocate a vertexID buffer
    CreateVertexIDBuffer();
}

void CMeshMgrVk::Shutdown() { CleanUp(); }

//-----------------------------------------------------------------------------
// Task switch...
//-----------------------------------------------------------------------------
void CMeshMgrVk::ReleaseBuffers()
{
    CleanUp();
    m_DynamicMesh.Reset();
    m_DynamicFlexMesh.Reset();
}

void CMeshMgrVk::RestoreBuffers() { Init(); }

//-----------------------------------------------------------------------------
// Cleans up vertex and index buffers
//-----------------------------------------------------------------------------
void CMeshMgrVk::CleanUp()
{
    if (m_pDynamicIndexBuffer)
    {
        delete m_pDynamicIndexBuffer;
        m_pDynamicIndexBuffer = 0;
    }

    DestroyVertexBuffers();

    // If we're running in vs3.0, allocate a vertexID buffer
    DestroyVertexIDBuffer();
}

//-----------------------------------------------------------------------------
// Fills a vertexID buffer
//-----------------------------------------------------------------------------
void CMeshMgrVk::FillVertexIDBuffer(CVertexBufferVk *pVertexIDBuffer, int nCount)
{
    // Fill the buffer with the values 0->(nCount-1)
    VertexDesc_t desc;
    ComputeVertexDesc(nullptr, pVertexIDBuffer->GetVertexFormat(), desc);
    pVertexIDBuffer->Lock(nCount, false, desc);
    float *pBuffer = (float*)pVertexIDBuffer->GetVertexMemory();
    for (int i = 0; i < nCount; ++i)
    {
        *pBuffer++ = (float)i;
    }
    pVertexIDBuffer->Unlock(nCount, desc);
}

//-----------------------------------------------------------------------------
// Creates, destroys the vertexID buffer
//-----------------------------------------------------------------------------
void CMeshMgrVk::CreateVertexIDBuffer()
{
    DestroyVertexIDBuffer();

    // if (g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.HasFastVertexTextures())
    if (g_pHardwareConfig->HasFastVertexTextures())
    {
        m_pVertexIDBuffer = (CVertexBufferVk *)g_pShaderDevice->CreateVertexBuffer(
            SHADER_BUFFER_TYPE_STATIC, VERTEX_FORMAT_UNKNOWN, (int)VERTEX_BUFFER_SIZE, TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER);
        FillVertexIDBuffer(m_pVertexIDBuffer, VERTEX_BUFFER_SIZE);
    }
}

void CMeshMgrVk::DestroyVertexIDBuffer()
{
    if (m_pVertexIDBuffer)
    {
        delete m_pVertexIDBuffer;
        m_pVertexIDBuffer = NULL;
    }
}

CVertexBufferVk *CMeshMgrVk::GetVertexIDBuffer() { return m_pVertexIDBuffer; }

//-----------------------------------------------------------------------------
// Unused vertex fields
//-----------------------------------------------------------------------------
void CMeshMgrVk::MarkUnusedVertexFields(unsigned int nFlags, int nTexCoordCount, bool *pUnusedTexCoords)
{
    m_nUnusedVertexFields = nFlags;
    m_nUnusedTextureCoords = 0;
    for (int i = 0; i < nTexCoordCount; ++i)
    {
        if (pUnusedTexCoords[i])
        {
            m_nUnusedTextureCoords |= (1 << i);
        }
    }
}

//-----------------------------------------------------------------------------
// Is the mesh dynamic?
//-----------------------------------------------------------------------------
bool CMeshMgrVk::IsDynamicMesh(IMesh *pMesh) const { return (pMesh == &m_DynamicMesh) || (pMesh == &m_DynamicFlexMesh); }

bool CMeshMgrVk::IsBufferedDynamicMesh(IMesh *pMesh) const { return (pMesh == &m_BufferedMesh); }

bool CMeshMgrVk::IsDynamicVertexBuffer(IVertexBuffer *pVertexBuffer) const { return (pVertexBuffer == &m_DynamicVertexBuffer); }

bool CMeshMgrVk::IsDynamicIndexBuffer(IIndexBuffer *pIndexBuffer) const { return (pIndexBuffer == &m_DynamicIndexBuffer); }

//-----------------------------------------------------------------------------
// Discards the dynamic vertex and index buffer
//-----------------------------------------------------------------------------
void CMeshMgrVk::DiscardVertexBuffers()
{
    VPROF_BUDGET("CMeshMgrVk::DiscardVertexBuffers", VPROF_BUDGETGROUP_SWAP_BUFFERS);
    // This shouldn't be necessary, but it seems to be on GeForce 2
    // It helps when running WC and the engine simultaneously.
    ResetMeshRenderState();

    if (!g_pShaderDevice->IsDeactivated())
    {
        // VK_TODO
        for (int i = m_DynamicVertexBuffers.Count(); --i >= 0;)
        {
            // m_DynamicVertexBuffers[i].m_pBuffer->FlushAtFrameStart();
        }
        // m_pDynamicIndexBuffer->FlushAtFrameStart();
    }
}

//-----------------------------------------------------------------------------
// Releases all dynamic vertex buffers
//-----------------------------------------------------------------------------
void CMeshMgrVk::DestroyVertexBuffers()
{
    for (int i = m_DynamicVertexBuffers.Count(); --i >= 0;)
    {
        if (m_DynamicVertexBuffers[i].m_pBuffer)
        {
            delete m_DynamicVertexBuffers[i].m_pBuffer;
        }
    }
    m_DynamicVertexBuffers.RemoveAll();
    m_DynamicMesh.Reset();
    m_DynamicFlexMesh.Reset();
}

//-----------------------------------------------------------------------------
// Flushes the dynamic mesh
//-----------------------------------------------------------------------------
void CMeshMgrVk::Flush() { m_BufferedMesh.Flush(); }

//-----------------------------------------------------------------------------
// Creates, destroys static meshes
//-----------------------------------------------------------------------------
IMesh *CMeshMgrVk::CreateStaticMesh(VertexFormat_t format, const char *pTextureBudgetGroup, IMaterial *pMaterial)
{
    // FIXME: Use a fixed-size allocator
    CMeshVk *pNewMesh = new CMeshVk(pTextureBudgetGroup);
    pNewMesh->SetVertexFormat(format);
    if (pMaterial != NULL)
    {
        pNewMesh->SetMorphFormat(pMaterial->GetMorphFormat());
        pNewMesh->SetMaterial(pMaterial);
    }
    return pNewMesh;
}

void CMeshMgrVk::DestroyStaticMesh(IMesh *pMesh)
{
    // Don't destroy the dynamic mesh!
    Assert(!IsDynamicMesh(pMesh));
    CBaseMeshVk *pMeshImp = static_cast<CBaseMeshVk *>(pMesh);
    if (pMeshImp)
    {
        delete pMeshImp;
    }
}

//-----------------------------------------------------------------------------
// Gets at the *real* dynamic mesh
//-----------------------------------------------------------------------------
IMesh *CMeshMgrVk::GetActualDynamicMesh(VertexFormat_t format)
{
    m_DynamicMesh.SetVertexFormat(format);
    return &m_DynamicMesh;
}

//-----------------------------------------------------------------------------
// Copy a static mesh index buffer to a dynamic mesh index buffer
//-----------------------------------------------------------------------------
void CMeshMgrVk::CopyStaticMeshIndexBufferToTempMeshIndexBuffer(CTempMeshVk *pDstIndexMesh, CMeshVk *pSrcIndexMesh)
{
    Assert(!pSrcIndexMesh->IsDynamic());
    int nIndexCount = pSrcIndexMesh->IndexCount();

    CMeshBuilder dstMeshBuilder;
    dstMeshBuilder.Begin(pDstIndexMesh, pSrcIndexMesh->GetPrimitiveType(), 0, nIndexCount);
    CIndexBufferVk *srcIndexBuffer = pSrcIndexMesh->GetIndexBuffer();
    IndexDesc_t temp;
    srcIndexBuffer->Lock(nIndexCount, false, temp);
    uint16_t *srcIndexArray = srcIndexBuffer->GetIndexMemory();
    for (int i = 0; i < nIndexCount; i++)
    {
        dstMeshBuilder.Index(srcIndexArray[i]);
        dstMeshBuilder.AdvanceIndex();
    }
    srcIndexBuffer->Unlock(0, temp);
    dstMeshBuilder.End();
}

IMesh *CMeshMgrVk::GetFlexMesh()
{
    // if (g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.SupportsPixelShaders_2_b())
    if (g_pHardwareConfig->SupportsPixelShaders_2_b())
    {
        // FIXME: Kinda ugly size.. 28 bytes
        m_DynamicFlexMesh.SetVertexFormat(VERTEX_POSITION | VERTEX_NORMAL | VERTEX_WRINKLE | VERTEX_FORMAT_USE_EXACT_FORMAT);
    }
    else
    {
        // Same size as a pair of float3s (24 bytes)
        m_DynamicFlexMesh.SetVertexFormat(VERTEX_POSITION | VERTEX_NORMAL | VERTEX_FORMAT_USE_EXACT_FORMAT);
    }
    return &m_DynamicFlexMesh;
}

//-----------------------------------------------------------------------------
// Gets at the dynamic mesh
//-----------------------------------------------------------------------------
IMesh *CMeshMgrVk::GetDynamicMesh(IMaterial *pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount, bool buffered,
                                  IMesh *pVertexOverride, IMesh *pIndexOverride)
{
    // VK_TODO: do we need buffered meshes at all? disable for now
    buffered = false;

    // Assert( (pMaterial == NULL) || ((IMaterial *)pMaterial)->IsRealTimeVersion() );

    // Can't be buffered if we're overriding the buffers
    if (pVertexOverride || pIndexOverride)
    {
        buffered = false;
    }

    // When going from buffered to unbuffered mode, need to flush..
    if ((m_BufferedMode != buffered) && m_BufferedMode)
    {
        m_BufferedMesh.SetMesh(0);
    }
    m_BufferedMode = buffered;

    IMaterial *pMatInternal = static_cast<IMaterial *>(pMaterial);

    bool needTempMesh = ShaderAPI()->IsInSelectionMode();

    CBaseMeshVk *pMesh;

    if (needTempMesh)
    {
        // These haven't been implemented yet for temp meshes!
        // I'm not a hundred percent sure how to implement them; it would
        // involve a lock and a copy at least, which would stall the entire
        // rendering pipeline.
        Assert(!pVertexOverride);

        if (pIndexOverride)
        {
            CopyStaticMeshIndexBufferToTempMeshIndexBuffer(&m_DynamicTempMesh, (CMeshVk *)pIndexOverride);
        }
        pMesh = &m_DynamicTempMesh;
    }
    else
    {
        pMesh = &m_DynamicMesh;
    }

    if (m_BufferedMode)
    {
        Assert(!m_BufferedMesh.WasNotRendered());
        m_BufferedMesh.SetMesh(pMesh);
        pMesh = &m_BufferedMesh;
    }

    if (!pVertexOverride)
    {
        // Remove VERTEX_FORMAT_COMPRESSED from the material's format (dynamic meshes don't
        // support compression, and all materials should support uncompressed verts too)
        // VK_TODO: GetVertexFormat
        // VertexFormat_t materialFormat = pMatInternal->GetVertexFormat() & ~VERTEX_FORMAT_COMPRESSED;
        VertexFormat_t materialFormat = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_COLOR;
        VertexFormat_t fmt = (vertexFormat != 0) ? vertexFormat : materialFormat;
        if (vertexFormat != 0)
        {
            int nVertexFormatBoneWeights = NumBoneWeights(vertexFormat);
            if (nHWSkinBoneCount < nVertexFormatBoneWeights)
            {
                nHWSkinBoneCount = nVertexFormatBoneWeights;
            }
        }

        // Force the requested number of bone weights
        fmt &= ~VERTEX_BONE_WEIGHT_MASK;
        if (nHWSkinBoneCount > 0)
        {
            fmt |= VERTEX_BONEWEIGHT(2);
            fmt |= VERTEX_BONE_INDEX;
        }

        pMesh->SetVertexFormat(fmt);
    }
    else
    {
        CBaseMeshVk *pBaseMesh = static_cast<CBaseMeshVk *>(pVertexOverride);
        pMesh->SetVertexFormat(pBaseMesh->GetVertexFormat());
    }
    pMesh->SetMorphFormat(pMatInternal->GetMorphFormat());
    pMesh->SetMaterial(pMatInternal);

    // Note this works because we're guaranteed to not be using a buffered mesh
    // when we have overrides on
    // FIXME: Make work for temp meshes
    if (pMesh == &m_DynamicMesh)
    {
        CBaseMeshVk *pBaseVertex = static_cast<CBaseMeshVk *>(pVertexOverride);
        if (pBaseVertex)
        {
            m_DynamicMesh.OverrideVertexBuffer(pBaseVertex->GetVertexBuffer());
        }

        CBaseMeshVk *pBaseIndex = static_cast<CBaseMeshVk *>(pIndexOverride);
        if (pBaseIndex)
        {
            Assert(pBaseIndex->GetIndexBuffer());
            m_DynamicMesh.OverrideIndexBuffer(pBaseIndex->GetIndexBuffer());
        }
    }

    return pMesh;
}

//-----------------------------------------------------------------------------
// Used to construct vertex data
//-----------------------------------------------------------------------------
void CMeshMgrVk::ComputeVertexDescription(unsigned char *pBuffer, VertexFormat_t vertexFormat, MeshDesc_t &desc) const
{
    ComputeVertexDesc(pBuffer, vertexFormat, (VertexDesc_t &)desc);
}

//-----------------------------------------------------------------------------
// Computes the vertex format
//-----------------------------------------------------------------------------
VertexFormat_t CMeshMgrVk::ComputeVertexFormat(unsigned int flags, int nTexCoordArraySize, int *pTexCoordDimensions, int numBoneWeights,
                                               int userDataSize) const
{
    // Construct a bitfield that makes sense and is unique from the standard FVF formats
    VertexFormat_t fmt = flags & ~VERTEX_FORMAT_USE_EXACT_FORMAT;

    // if (g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.SupportsCompressedVertices() == VERTEX_COMPRESSION_NONE)
    if (g_pHardwareConfig->SupportsCompressedVertices() == VERTEX_COMPRESSION_NONE)
    {
        // Vertex compression is disabled - make sure all materials
        // say "No!" to compressed verts ( tested in IsValidVertexFormat() )
        fmt &= ~VERTEX_FORMAT_COMPRESSED;
    }

    // This'll take 3 bits at most
    Assert(numBoneWeights <= 4);

    if (numBoneWeights > 0)
    {
        fmt |= VERTEX_BONEWEIGHT(2); // Always exactly two weights
    }

    // Size is measured in # of floats
    Assert(userDataSize <= 4);
    fmt |= VERTEX_USERDATA_SIZE(userDataSize);

    // NOTE: If pTexCoordDimensions isn't specified, then nTexCoordArraySize
    // is interpreted as meaning that we have n 2D texcoords in the first N texcoord slots
    nTexCoordArraySize = std::min(nTexCoordArraySize, (int)VERTEX_MAX_TEXTURE_COORDINATES);
    for (int i = 0; i < nTexCoordArraySize; ++i)
    {
        if (pTexCoordDimensions)
        {
            Assert(pTexCoordDimensions[i] >= 0 && pTexCoordDimensions[i] <= 4);
            fmt |= VERTEX_TEXCOORD_SIZE((TextureStage_t)i, pTexCoordDimensions[i]);
        }
        else
        {
            fmt |= VERTEX_TEXCOORD_SIZE((TextureStage_t)i, 2);
        }
    }

    return fmt;
}

//-----------------------------------------------------------------------------
// Use fat vertices (for tools)
//-----------------------------------------------------------------------------
void CMeshMgrVk::UseFatVertices(bool bUseFat) { m_bUseFatVertices = bUseFat; }

//-----------------------------------------------------------------------------
// Returns the number of vertices we can render using the dynamic mesh
//-----------------------------------------------------------------------------
void CMeshMgrVk::GetMaxToRender(IMesh *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices)
{
    *pMaxVerts = 65535;
    *pMaxIndices = 65535;
    // VK_TODO: is this needed?
    /*
    CBaseMeshVk *pBaseMesh = static_cast<CBaseMeshVk *>(pMesh);
    if (!pBaseMesh)
    {
        *pMaxVerts = 0;
        *pMaxIndices = m_pDynamicIndexBuffer->IndexCount();
        return;
    }

    if (IsBufferedDynamicMesh(pMesh))
    {
        pBaseMesh = (CBaseMeshVk *)static_cast<CBufferedMeshVk *>(pBaseMesh)->GetMesh();
        pMesh = pBaseMesh;
    }

    // Static mesh? Max you can use is 65535
    if (!IsDynamicMesh(pMesh))
    {
        *pMaxVerts = 65535;
        *pMaxIndices = 65535;
        return;
    }

    CVertexBufferVk *pVertexBuffer = pBaseMesh->GetVertexBuffer();
    CIndexBufferVk *pIndexBuffer = pBaseMesh->GetIndexBuffer();

    if (!pVertexBuffer)
    {
        *pMaxVerts = 0;
        *pMaxIndices = 0;
        return;
    }

    if (!bMaxUntilFlush)
    {
        *pMaxVerts = ShaderAPI()->GetCurrentDynamicVBSize() / pVertexBuffer->VertexSize();
        if (*pMaxVerts > 65535)
        {
            *pMaxVerts = 65535;
        }
        *pMaxIndices = pIndexBuffer ? pIndexBuffer->IndexCount() : 0;
        return;
    }

    *pMaxVerts = pVertexBuffer->NumVerticesUntilFlush();
    *pMaxIndices = pIndexBuffer ? pIndexBuffer->IndexCount() - pIndexBuffer->IndexPosition() : 0;
    if (*pMaxVerts == 0)
    {
        *pMaxVerts = ShaderAPI()->GetCurrentDynamicVBSize() / pVertexBuffer->VertexSize();
    }
    if (*pMaxVerts > 65535)
    {
        *pMaxVerts = 65535;
    }
    if (*pMaxIndices == 0)
    {
        *pMaxIndices = pIndexBuffer ? pIndexBuffer->IndexCount() : 0;
    }
    */
}

int CMeshMgrVk::GetMaxVerticesToRender(IMaterial *pMaterial)
{
    // Assert( (pMaterial == NULL) || ((IMaterial *)pMaterial)->IsRealTimeVersion() );

    // Be conservative, assume no compression (in here, we don't know if the caller will used a compressed VB or not)
    // FIXME: allow the caller to specify which compression type should be used to compute size from the vertex format
    //        (this can vary between multiple VBs/Meshes using the same material)
    VertexFormat_t fmt = pMaterial->GetVertexFormat() & ~VERTEX_FORMAT_COMPRESSED;
    int nMaxVerts = ShaderAPI()->GetCurrentDynamicVBSize() / VertexFormatSize(fmt);
    if (nMaxVerts > 65535)
    {
        nMaxVerts = 65535;
    }
    return nMaxVerts;
}

int CMeshMgrVk::GetMaxIndicesToRender() { return INDEX_BUFFER_SIZE; }

//-----------------------------------------------------------------------------
// Returns a vertex buffer appropriate for the flags
//-----------------------------------------------------------------------------
CVertexBufferVk *CMeshMgrVk::FindOrCreateVertexBuffer(int nDynamicBufferId, VertexFormat_t vertexFormat)
{
    int vertexSize = VertexFormatSize(vertexFormat);

    while (m_DynamicVertexBuffers.Count() <= nDynamicBufferId)
    {
        // create the single 1MB dynamic vb that will be shared amongst all consumers
        // the correct thing is to use the largest expected vertex format size of max elements, but this
        // creates an undesirably large buffer - instead create the buffer we want, and fix consumers that bork
        // NOTE: GetCurrentDynamicVBSize returns a smaller value during level transitions
        int nBufferMemory = ShaderAPI()->GetCurrentDynamicVBSize();
        int nIndex = m_DynamicVertexBuffers.AddToTail();
        m_DynamicVertexBuffers[nIndex].m_VertexSize = 0;
        m_DynamicVertexBuffers[nIndex].m_pBuffer =
            (CVertexBufferVk *)g_pShaderDevice->CreateVertexBuffer(SHADER_BUFFER_TYPE_DYNAMIC, vertexFormat, 0, "dynamic");
    }

    if (m_DynamicVertexBuffers[nDynamicBufferId].m_VertexSize != vertexSize)
    {
        // provide caller with dynamic vb in expected format
        // NOTE: GetCurrentDynamicVBSize returns a smaller value during level transitions
        int nBufferMemory = ShaderAPI()->GetCurrentDynamicVBSize();
        m_DynamicVertexBuffers[nDynamicBufferId].m_VertexSize = vertexSize;
        m_DynamicVertexBuffers[nDynamicBufferId].m_pBuffer->ChangeConfiguration(vertexSize, nBufferMemory);

        // size changed means stream stride needs update
        // mark cached stream state as invalid to reset stream
        if (nDynamicBufferId == 0)
        {
            g_pLastVertex = NULL;
        }
    }

    return m_DynamicVertexBuffers[nDynamicBufferId].m_pBuffer;
}

CIndexBufferVk *CMeshMgrVk::GetDynamicIndexBuffer() { return m_pDynamicIndexBuffer; }

IVertexBuffer *CMeshMgrVk::GetDynamicVertexBuffer(IMaterial *pMaterial, bool buffered)
{
    Assert(0);
    return NULL;
    //	return ( IMeshDX8 * )GetDynamicMesh( pMaterial, buffered, NULL, NULL );
}

IIndexBuffer *CMeshMgrVk::GetDynamicIndexBuffer(IMaterial *pMaterial, bool buffered)
{
    Assert(0);
    return NULL;
    //	return ( IMeshDX8 * )GetDynamicMesh( pMaterial, buffered, NULL, NULL );
}

// Do we need to specify the stream here in the case of locking multiple dynamic VBs on different streams?
IVertexBuffer *CMeshMgrVk::GetDynamicVertexBuffer(int streamID, VertexFormat_t vertexFormat, bool bBuffered)
{
    if (CompressionType(vertexFormat) != VERTEX_COMPRESSION_NONE)
    {
        // UNDONE: support compressed dynamic meshes if needed (pro: less VB memory, con: time spent compressing)
        DebuggerBreak();
        return NULL;
    }

    // MESHFIXME
#if 0
	if ( ( m_BufferedMode != bBuffered ) && m_BufferedMode )
	{
		m_BufferedIndexBuffer.SetIndexBuffer( NULL );
	}
#endif

    m_BufferedMode = bBuffered;
    Assert(!m_BufferedMode); // MESHFIXME: don't deal with buffered VBs yet.

    bool needTempMesh = ShaderAPI()->IsInSelectionMode();

#ifdef DRAW_SELECTION
    if (g_bDrawSelection)
    {
        needTempMesh = true;
    }
#endif

    Assert(!needTempMesh); // MESHFIXME: don't support temp meshes here yet.

    CVertexBufferVk *pVertexBuffer;

    if (needTempMesh)
    {
        Assert(0); // MESHFIXME: don't do this yet.
                   //		pVertexBuffer = &m_DynamicTempVertexBuffer;
        pVertexBuffer = NULL;
    }
    else
    {
        pVertexBuffer = &m_DynamicVertexBuffer;
    }

    if (m_BufferedMode)
    {
        Assert(0); // don't support this yet.
#if 0
		Assert( !m_BufferedMesh.WasNotRendered() );
		m_BufferedMesh.SetMesh( pMesh );
		pMesh = &m_BufferedMesh;
#endif
    }

    return pVertexBuffer;
}

IIndexBuffer *CMeshMgrVk::GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered)
{
    m_BufferedMode = bBuffered;

    Assert(!m_BufferedMode);

#ifdef _DEBUG
    bool needTempMesh =
#endif
        ShaderAPI()->IsInSelectionMode();

    Assert(!needTempMesh); // don't handle this yet. MESHFIXME

    CIndexBufferVk *pIndexBuffer = &m_DynamicIndexBuffer;
    return pIndexBuffer;
}

void CMeshMgrVk::SetVertexIDStreamState()
{
    // MESHFIXME : This path is only used for the new index/vertex buffer interfaces.
    bool bUsingVertexID = false; // IsUsingVertexID();
    //	if ( bUsingVertexID != g_bUsingVertexID )
    {
        if (bUsingVertexID)
        {
            // NOTE: Morphing doesn't work with dynamic buffers!!! BLEAH
            // It's because the indices (which are not 0 based for dynamic buffers)
            // are accessing both the vertexID buffer + the regular vertex buffer.
            // This *might* be fixable with baseVertexIndex?
            Assert(!m_pCurrentVertexBuffer->IsDynamic());

            CVertexBufferVk *pVertexIDBuffer = g_pMeshMgr->GetVertexIDBuffer();

            pVertexIDBuffer->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());
        }

        g_bUsingVertexID = bUsingVertexID;
    }
}

void CMeshMgrVk::SetColorStreamState()
{
    g_pLastColorMesh = NULL;
    g_nLastColorMeshVertOffsetInBytes = 0;
}

void CMeshMgrVk::SetVertexStreamState(int nVertOffsetInBytes, int nVertexStride)
{
    // Calls in here assume shader support...
    // if (g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.SupportsVertexAndPixelShaders())
    if (g_pHardwareConfig->SupportsVertexAndPixelShaders())
    {
        // HACK...point stream 2 at the same VB which is bound to stream 0...
        Assert(m_pCurrentVertexBuffer && m_pCurrentVertexBuffer->GetVkBuffer());

        // cFlexScale.x masks flex in vertex shader
        float c[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        ShaderAPI()->SetVertexShaderConstant(VERTEX_SHADER_FLEXSCALE, c, 1);
    }

    // MESHFIXME : This path is only used for the new index/vertex buffer interfaces.
    if (g_pLastVertex || (g_pLastVertexBuffer != m_pCurrentVertexBuffer->GetVkBuffer()) ||
        (g_nLastVertOffsetInBytes != nVertOffsetInBytes) || (g_nLastVertStride != nVertexStride))
    {
        Assert(m_pCurrentVertexBuffer && m_pCurrentVertexBuffer->GetVkBuffer());

        m_pCurrentVertexBuffer->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());

        g_pLastVertex = NULL;
        g_nLastVertStride = nVertexStride;
        g_pLastVertexBuffer = m_pCurrentVertexBuffer->GetVkBuffer();
        g_nLastVertOffsetInBytes = nVertOffsetInBytes;
    }
}

bool CMeshMgrVk::SetRenderState(int nVertexOffsetInBytes, int nFirstVertexIdx, VertexFormat_t vertexFormat, int nVertexStride)
{
    // Can't set the state if we're deactivated
    if (g_pShaderDevice->IsDeactivated())
    {
        ResetMeshRenderState();
        return false;
    }

    SetVertexIDStreamState();
    SetColorStreamState();
    SetVertexStreamState(nVertexOffsetInBytes, nVertexStride);
    SetIndexStreamState(nFirstVertexIdx);

    return true;
}

void CMeshMgrVk::BindVertexBuffer(int nStreamID, IVertexBuffer *pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount,
                                  VertexFormat_t fmt, int nRepetitions)
{
    // FIXME: Multiple stream support isn't implemented yet
    // VK_TODO: is this relevant? is MAX_VK_STREAMS relevant??
    Assert(nStreamID == 0);

    m_pCurrentVertexBuffer = static_cast<CVertexBufferVk *>(pVertexBuffer);
    m_CurrentVertexFormat = fmt;
    m_pVertexBufferOffset[nStreamID] = nOffsetInBytes;
    m_pCurrentVertexStride[nStreamID] = m_pCurrentVertexBuffer->VertexSize();
    m_pFirstVertex[nStreamID] = nFirstVertex;
    m_pVertexCount[nStreamID] = nVertexCount, m_pVertexIDBuffer = NULL;
}

void CMeshMgrVk::BindIndexBuffer(IIndexBuffer *pIndexBuffer, int nOffsetInBytes)
{
    m_pCurrentIndexBuffer = static_cast<CIndexBufferVk *>(pIndexBuffer);
    m_nIndexBufferOffset = nOffsetInBytes;
}

void CMeshMgrVk::Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount)
{
    // MESHFIXME : This path is only used for the new index/vertex buffer interfaces.
    // make sure we aren't using a morph stream for this path.
    //	Assert( !IsUsingMorphData() );
    //	Assert( !m_pColorMesh );

    SetRenderState(m_pVertexBufferOffset[0], /* nFirstVertexIdx */ 0, m_CurrentVertexFormat, m_pCurrentVertexStride[0]);

    m_PrimitiveType = MATERIAL_TRIANGLES;
    Assert(primitiveType == MATERIAL_TRIANGLES);

    m_nFirstIndex = nFirstIndex;
    m_nNumIndices = nIndexCount;

    // VK_TODO
    // ShaderAPI()->DrawWithVertexAndIndexBuffers();
}

void CMeshMgrVk::RenderPassWithVertexAndIndexBuffers(void)
{
    VPROF("CShaderAPIDVk::RenderPassWithVertexAndIndexBuffers");

    Assert(m_PrimitiveType != MATERIAL_HETEROGENOUS);

    // VK_TODO
    Assert(0);
}

// VK_TODO: duplicated in CMeshVk
//-----------------------------------------------------------------------------
void CMeshMgrVk::SetIndexStreamState(int firstVertexIdx)
{
    CIndexBufferVk *pIndexBuffer = assert_cast<CIndexBufferVk *>(m_pCurrentIndexBuffer);
    VkBuffer *pVkBuffer = pIndexBuffer ? pIndexBuffer->GetVkBuffer() : nullptr;
    if (g_pLastIndex || g_pLastIndexBuffer != pVkBuffer)
    {
        // VK_TODO
        // g_pShaderDevice->SetIndices(pVkBuffer);
        pIndexBuffer->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());

        g_pLastIndexBuffer = pVkBuffer;
        g_pLastIndex = NULL;
        g_LastVertexIdx = -1;
    }
}