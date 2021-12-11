#include "meshvk.h"
#include "materialsystem/materialsystem_config.h"
#include "meshmgrvk.h"
#include "shaderapi/ishaderutil.h"
#include "shaderapivk.h"
#include "shaderapivk_global.h"
#include "shaderdevicevk.h"
#include "vprof.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
//
// Base mesh
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

CBaseMeshVk::CBaseMeshVk() : m_VertexFormat(0)
{
    m_bMeshLocked = false;
#ifdef _DEBUG
    m_IsDrawing = false;
    m_pMaterial = 0;
#endif
}

CBaseMeshVk::~CBaseMeshVk() {}

//-----------------------------------------------------------------------------
// For debugging...
//-----------------------------------------------------------------------------
bool CBaseMeshVk::DebugTrace() const
{
    //#ifdef _DEBUG
    //    if (m_pMaterial)
    //        return m_pMaterial->PerformDebugTrace();
    //#endif

    return false;
}

void CBaseMeshVk::SetMaterial(IMaterial *pMaterial)
{
#ifdef _DEBUG
    m_pMaterial = static_cast<IMaterial *>(pMaterial);
#endif
}

//-----------------------------------------------------------------------------
// Sets, gets the vertex format
//-----------------------------------------------------------------------------
void CBaseMeshVk::SetVertexFormat(VertexFormat_t format) { m_VertexFormat = format; }

VertexFormat_t CBaseMeshVk::GetVertexFormat() const { return m_VertexFormat; }

//-----------------------------------------------------------------------------
// Sets/gets the morph format
//-----------------------------------------------------------------------------
void CBaseMeshVk::SetMorphFormat(MorphFormat_t format) { m_MorphFormat = format; }

MorphFormat_t CBaseMeshVk::GetMorphFormat() const { return m_MorphFormat; }

//-----------------------------------------------------------------------------
// Am I using morph data?
//-----------------------------------------------------------------------------
bool CBaseMeshVk::IsUsingMorphData() const
{
    // We're not using a morph unless the bound morph is a superset of what the rendermesh needs
    MorphFormat_t morphFormat = GetMorphFormat();
    if (!morphFormat)
        return false;

    return ((morphFormat & ShaderUtil()->GetBoundMorphFormat()) == morphFormat);
}

//-----------------------------------------------------------------------------
// Do I need to reset the vertex format?
//-----------------------------------------------------------------------------
bool CBaseMeshVk::NeedsVertexFormatReset(VertexFormat_t fmt) const { return m_VertexFormat != fmt; }

//-----------------------------------------------------------------------------
// Do I have enough room?
//-----------------------------------------------------------------------------
bool CBaseMeshVk::HasEnoughRoom(int nVertexCount, int nIndexCount) const
{
    // by default, we do
    return true;
}

//-----------------------------------------------------------------------------
// Locks mesh for modifying
//-----------------------------------------------------------------------------
void CBaseMeshVk::ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc)
{
    // for the time being, disallow for most cases
    Assert(0);
}

void CBaseMeshVk::ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc)
{
    // for the time being, disallow for most cases
    Assert(0);
}

void CBaseMeshVk::ModifyEnd(MeshDesc_t &desc)
{
    // for the time being, disallow for most cases
    Assert(0);
}

//-----------------------------------------------------------------------------
// Begins a pass
//-----------------------------------------------------------------------------
void CBaseMeshVk::BeginPass() {}

//-----------------------------------------------------------------------------
// Sets the render state and gets the drawing going
//-----------------------------------------------------------------------------
inline void CBaseMeshVk::DrawMesh()
{
#ifdef _DEBUG
    // Make sure we're not drawing...
    Assert(!m_IsDrawing);
    m_IsDrawing = true;
#endif

    // This is going to cause RenderPass to get called a bunch
    ShaderAPI()->DrawMesh(this);

#ifdef _DEBUG
    m_IsDrawing = false;
#endif
}

//-----------------------------------------------------------------------------
// Spews the mesh data
//-----------------------------------------------------------------------------
void CBaseMeshVk::Spew(int nVertexCount, int nIndexCount, const MeshDesc_t &spewDesc)
{
#ifdef _DEBUG
    if (m_pMaterial)
    {
        Plat_DebugString((const char *)m_pMaterial->GetName());
        Plat_DebugString("\n");
    }
#endif // _DEBUG

    // This is needed so buffering can just use this
    VertexFormat_t fmt = m_VertexFormat;

    // Set up the vertex descriptor
    MeshDesc_t desc = spewDesc;

    char tempbuf[256];
    char *temp = tempbuf;
    sprintf(tempbuf, "\nVerts: (Vertex Format %llx)\n", fmt);
    Plat_DebugString(tempbuf);

    // PrintVertexFormat( fmt );

    int numBoneWeights = NumBoneWeights(fmt);
    for (int i = 0; i < nVertexCount; ++i)
    {
        temp += sprintf(temp, "[%4d] ", i + desc.m_nFirstVertex);
        if (fmt & VERTEX_POSITION)
        {
            glm::vec3 pos = VertexPosition(desc, i);
            temp += sprintf(temp, "P %8.2f %8.2f %8.2f ", pos[0], pos[1], pos[2]);
        }

        if (fmt & VERTEX_WRINKLE)
        {
            float flWrinkle = VertexWrinkle(desc, i);
            temp += sprintf(temp, "Wr %8.2f ", flWrinkle);
        }

        if (numBoneWeights > 0)
        {
            temp += sprintf(temp, "BW ");
            float *pWeight = VertexBoneWeight(desc, i);
            for (int j = 0; j < numBoneWeights; ++j)
            {
                temp += sprintf(temp, "%1.2f ", pWeight[j]);
            }
        }
        if (fmt & VERTEX_BONE_INDEX)
        {
            unsigned char *pIndex = VertexBoneIndex(desc, i);
            temp += sprintf(temp, "BI %d %d %d %d ", (int)pIndex[0], (int)pIndex[1], (int)pIndex[2], (int)pIndex[3]);
            Assert(pIndex[0] < 16);
            Assert(pIndex[1] < 16);
            Assert(pIndex[2] < 16);
            Assert(pIndex[3] < 16);
        }

        if (fmt & VERTEX_NORMAL)
        {
            glm::vec3 normal = VertexNormal(desc, i);
            temp += sprintf(temp, "N %1.2f %1.2f %1.2f ", normal[0], normal[1], normal[2]);
        }

        if (fmt & VERTEX_COLOR)
        {
            glm::vec<4, uint8_t> pColor = VertexColor(desc, i);
            temp += sprintf(temp, "C b %3d g %3d r %3d a %3d ", pColor[0], pColor[1], pColor[2], pColor[3]);
        }

        for (int j = 0; j < VERTEX_MAX_TEXTURE_COORDINATES; ++j)
        {
            if (TexCoordSize(j, fmt) > 0)
            {
                glm::vec2 texcoord = VertexTexCoord(desc, i, j);
                temp += sprintf(temp, "T%d %.2f %.2f ", j, texcoord[0], texcoord[1]);
            }
        }

        if (fmt & VERTEX_TANGENT_S)
        {
            glm::vec3 tangentS = VertexTangentS(desc, i);
            temp += sprintf(temp, "S %1.2f %1.2f %1.2f ", tangentS[0], tangentS[1], tangentS[2]);
        }

        if (fmt & VERTEX_TANGENT_T)
        {
            glm::vec3 tangentT = VertexTangentT(desc, i);
            temp += sprintf(temp, "T %1.2f %1.2f %1.2f ", tangentT[0], tangentT[1], tangentT[2]);
        }

        sprintf(temp, "\n");
        Plat_DebugString(tempbuf);
        temp = tempbuf;
    }

    sprintf(tempbuf, "\nIndices: %d\n", nIndexCount);
    Plat_DebugString(tempbuf);
    for (int i = 0; i < nIndexCount; ++i)
    {
        temp += sprintf(temp, "%d ", (int)desc.m_pIndices[i]);
        if ((i & 0x0F) == 0x0F)
        {
            sprintf(temp, "\n");
            Plat_DebugString(tempbuf);
            tempbuf[0] = '\0';
            temp = tempbuf;
        }
    }
    sprintf(temp, "\n");
    Plat_DebugString(tempbuf);
}

void CBaseMeshVk::ValidateData(int nVertexCount, int nIndexCount, const MeshDesc_t &spewDesc) {}

void CBaseMeshVk::Draw(CPrimList *pLists, int nLists) {}

// Copy verts and/or indices to a mesh builder. This only works for temp meshes!
void CBaseMeshVk::CopyToMeshBuilder(int iStartVert, // Which vertices to copy.
                                    int nVerts,
                                    int iStartIndex, // Which indices to copy.
                                    int nIndices,
                                    int indexOffset, // This is added to each index.
                                    CMeshBuilder &builder)
{
}

//-----------------------------------------------------------------------------
//
// static mesh
//
//-----------------------------------------------------------------------------

CPrimList *CMeshVk::s_pPrims;
int CMeshVk::s_nPrims;
unsigned int CMeshVk::s_FirstVertex;
unsigned int CMeshVk::s_NumVertices;

//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
CMeshVk::CMeshVk(const char *pTextureGroupName)
{
    m_pTextureGroupName = pTextureGroupName;
    m_Type = MATERIAL_TRIANGLES;
    m_Mode = ComputeMode(m_Type);

    m_bHasFlexVerts = false;
    m_pFlexVertexBuffer = nullptr;
    m_nFlexVertOffsetInBytes = 0;
    m_nColorMeshVertOffsetInBytes = 0;
    m_pIndexBuffer = nullptr;
    m_pVertexBuffer = nullptr;
    m_pColorMesh = nullptr;

    m_NumVertices = 0;
    m_NumIndices = 0;
    m_FirstIndex = 0;
    m_flexVertCount = 0;

    m_IsVBLocked = false;
    m_IsIBLocked = false;
}

CMeshVk::~CMeshVk()
{
    // Don't release the vertex buffer
    if (!g_pMeshMgr->IsDynamicMesh(this))
    {
        if (m_pVertexBuffer)
        {
            delete m_pVertexBuffer;
        }
        if (m_pIndexBuffer)
        {
            delete m_pIndexBuffer;
        }
    }
}

void CMeshVk::SetFlexMesh(IMesh *pMesh, int nVertexOffsetInBytes)
{
    if (!ShaderUtil()->OnSetFlexMesh(this, pMesh, nVertexOffsetInBytes))
        return;

    m_nFlexVertOffsetInBytes = nVertexOffsetInBytes; // Offset into dynamic mesh (in bytes)

    if (pMesh)
    {
        m_flexVertCount = pMesh->VertexCount();
        pMesh->MarkAsDrawn();

        CBaseMeshVk *pBaseMesh = static_cast<CBaseMeshVk *>(pMesh);
        m_pFlexVertexBuffer = pBaseMesh->GetVertexBuffer();

        m_bHasFlexVerts = true;
    }
    else
    {
        m_flexVertCount = 0;
        m_pFlexVertexBuffer = NULL;
        m_bHasFlexVerts = false;
    }
}

void CMeshVk::DisableFlexMesh() { CMeshVk::SetFlexMesh(NULL, 0); }

bool CMeshVk::HasFlexMesh() const { return m_bHasFlexVerts; }

void CMeshVk::SetColorMesh(IMesh *pColorMesh, int nVertexOffsetInBytes)
{
    if (!ShaderUtil()->OnSetColorMesh(this, pColorMesh, nVertexOffsetInBytes))
        return;

    m_pColorMesh = (CMeshVk *)pColorMesh; // dangerous conversion! garymcthack
    m_nColorMeshVertOffsetInBytes = nVertexOffsetInBytes;
    Assert(m_pColorMesh || (nVertexOffsetInBytes == 0));

#ifdef _DEBUG
    if (pColorMesh)
    {
        int nVertexCount = VertexCount();
        int numVertsColorMesh = m_pColorMesh->VertexCount();
        Assert(numVertsColorMesh >= nVertexCount);
    }
#endif
}

bool CMeshVk::HasColorMesh() const { return (m_pColorMesh != NULL); }

//-----------------------------------------------------------------------------
// Locks/ unlocks the vertex buffer
//-----------------------------------------------------------------------------
bool CMeshVk::Lock(int nVertexCount, bool bAppend, VertexDesc_t &desc)
{
    Assert(!m_IsVBLocked);

    // Just give the app crap buffers to fill up while we're suppressed...
    if (g_pShaderDevice->IsDeactivated() || (nVertexCount == 0))
    {
        // Set up the vertex descriptor
        ComputeVertexDesc(nullptr, 0, desc);
        desc.m_nFirstVertex = 0;
        return false;
    }

    // Static vertex buffer case
    if (!m_pVertexBuffer)
    {
        int size = g_pMeshMgr->VertexFormatSize(m_VertexFormat);
        m_pVertexBuffer = (CVertexBufferVk *)g_pShaderDevice->CreateVertexBuffer(SHADER_BUFFER_TYPE_STATIC, m_VertexFormat, nVertexCount,
                                                                                 m_pTextureGroupName);
    }

    // Lock it baby
    int nMaxVerts, nMaxIndices;
    g_pMeshMgr->GetMaxToRender(this, false, &nMaxVerts, &nMaxIndices);
    if (!g_pHardwareConfig->SupportsStreamOffset())
    {
        // Without stream offset, we can't use VBs greater than 65535 verts (due to our using 16-bit indices)
        Assert(nVertexCount <= nMaxVerts);
    }

    // unsigned char *pVertexMemory = m_pVertexBuffer->Lock( nVertexCount, bAppend, desc);
    m_pVertexBuffer->Lock(nVertexCount, bAppend, desc);

    /*
    if ( !pVertexMemory )
    {
        if ( nVertexCount > nMaxVerts )
        {
            Assert( 0 );
            Error( "Too many verts for a dynamic vertex buffer (%d>%d) Tell a programmer to up VERTEX_BUFFER_SIZE.\n",
                ( int )nVertexCount, ( int )nMaxVerts );
        }
        else
        {
            // Check if paged pool is in critical state ( < 5% free )
            PAGED_POOL_INFO_t ppi;
            if ( ( SYSCALL_SUCCESS == Plat_GetPagedPoolInfo( &ppi ) ) &&
                 ( ( ppi.numPagesFree * 20 ) < ( ppi.numPagesUsed + ppi.numPagesFree ) ) )
            {
                Error( "Out of OS Paged Pool Memory! For more information, please
    see\nhttp://support.steampowered.com/cgi-bin/steampowered.cfg/php/enduser/std_adp.php?p_faqid=150\n" );
            }
            else
            {
                Assert( 0 );
                Error( "failed to lock vertex buffer in CMeshDX8::LockVertexBuffer\n" );
            }
        }
        CVertexBufferBase::ComputeVertexDescription( 0, 0, desc );
        return false;
    }
    */

	// Set up the vertex descriptor
    ComputeVertexDesc(m_pVertexBuffer->GetVertexMemory(), m_VertexFormat, desc);
	
    m_IsVBLocked = true;
    return true;
}

void CMeshVk::Unlock(int nVertexCount, VertexDesc_t &desc)
{
    if (!m_IsVBLocked)
        return;

    m_pVertexBuffer->Unlock(nVertexCount, desc);
    m_IsVBLocked = false;
}

//-----------------------------------------------------------------------------
// Locks/unlocks the index buffer
//-----------------------------------------------------------------------------
int CMeshVk::Lock(bool bReadOnly, int nFirstIndex, int nIndexCount, IndexDesc_t &desc)
{
    Assert(!m_IsIBLocked);

    // Just give the app crap buffers to fill up while we're suppressed...
    if (g_pShaderDevice->IsDeactivated() || (nIndexCount == 0))
    {
        // Set up a bogus index descriptor
        desc.m_pIndices = (uint16_t *)(&g_nScratchIndexBuffer);
        desc.m_nIndexSize = 0;
        desc.m_nFirstIndex = 0;
        desc.m_nOffset = 0;
        return 0;
    }

    // Static vertex buffer case
    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = (CIndexBufferVk *)g_pShaderDevice->CreateIndexBuffer(SHADER_BUFFER_TYPE_STATIC, MATERIAL_INDEX_FORMAT_UNKNOWN,
                                                                              nIndexCount, m_pTextureGroupName);
    }

    // desc.m_pIndices = m_pIndexBuffer->Lock(bReadOnly, nIndexCount, startIndex, nFirstIndex);
    m_pIndexBuffer->Lock(nIndexCount, false, desc);
    if (!desc.m_pIndices)
    {
        desc.m_pIndices = (uint16_t *)(&g_nScratchIndexBuffer);
        desc.m_nIndexSize = 0;
        desc.m_nFirstIndex = 0;
        desc.m_nOffset = 0;

        // VK_TODO
        /*
        // Check if paged pool is in critical state ( < 5% free )
        PAGED_POOL_INFO_t ppi;
        if ( ( SYSCALL_SUCCESS == Plat_GetPagedPoolInfo( &ppi ) ) &&
            ( ( ppi.numPagesFree * 20 ) < ( ppi.numPagesUsed + ppi.numPagesFree ) ) )
        {
            Error( "Out of OS Paged Pool Memory! For more information, please
        see\nhttp://support.steampowered.com/cgi-bin/steampowered.cfg/php/enduser/std_adp.php?p_faqid=150\n" );
        }
        else
        {
            Assert( 0 );
            Error( "failed to lock index buffer in CMeshDX8::LockIndexBuffer\n" );
        }
        */

        return 0;
    }

    m_IsIBLocked = true;
    return desc.m_nFirstIndex;
}

void CMeshVk::Unlock(int nIndexCount, IndexDesc_t &desc)
{
    if (!m_IsIBLocked)
        return;

    m_pIndexBuffer->Unlock(nIndexCount, desc);
    m_IsIBLocked = false;
}

//-----------------------------------------------------------------------------
// Locks/unlocks the entire mesh
//-----------------------------------------------------------------------------
void CMeshVk::LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    Assert(!m_bMeshLocked);

    Lock(nVertexCount, false, *static_cast<VertexDesc_t *>(&desc));
    if (m_Type != MATERIAL_POINTS)
    {
        Lock(false, -1, nIndexCount, *static_cast<IndexDesc_t *>(&desc));
    }
    else
    {
        desc.m_pIndices = (uint16_t *)(&g_nScratchIndexBuffer);
        desc.m_nIndexSize = 0;
    }

    CBaseMeshVk::m_bMeshLocked = true;
}

void CMeshVk::UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    Assert(m_bMeshLocked);

    Unlock(nVertexCount, *static_cast<VertexDesc_t *>(&desc));
    if (m_Type != MATERIAL_POINTS)
    {
        Unlock(nIndexCount, *static_cast<IndexDesc_t *>(&desc));
    }

    m_NumVertices = nVertexCount;
    m_NumIndices = nIndexCount;

    CBaseMeshVk::m_bMeshLocked = false;
}

//-----------------------------------------------------------------------------
// Locks mesh for modifying
//-----------------------------------------------------------------------------
void CMeshVk::ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc)
{
    m_pVertexBuffer->Lock(nVertexCount, false, *static_cast<VertexDesc_t *>(&desc));
    ComputeVertexDesc(m_pVertexBuffer->GetVertexMemory(), m_VertexFormat, desc);
    m_IsVBLocked = true;
    desc.m_nFirstVertex = nFirstVertex;
}

void CMeshVk::ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc)
{
    ModifyBeginEx(false, nFirstVertex, nVertexCount, nFirstIndex, nIndexCount, desc);
}

void CMeshVk::ModifyEnd(MeshDesc_t &desc)
{
    Unlock(0, *static_cast<IndexDesc_t *>(&desc));
    Unlock(0, *static_cast<VertexDesc_t *>(&desc));
}

//-----------------------------------------------------------------------------
// returns the # of vertices (static meshes only)
//-----------------------------------------------------------------------------
int CMeshVk::VertexCount() const { return m_pVertexBuffer ? m_pVertexBuffer->VertexCount() : 0; }

//-----------------------------------------------------------------------------
// returns the # of indices
//-----------------------------------------------------------------------------
int CMeshVk::IndexCount() const { return m_pIndexBuffer ? m_pIndexBuffer->IndexCount() : 0; }

//-----------------------------------------------------------------------------
// Sets up the vertex and index buffers
//-----------------------------------------------------------------------------
void CMeshVk::UseIndexBuffer(CIndexBufferVk *pBuffer) { m_pIndexBuffer = pBuffer; }

void CMeshVk::UseVertexBuffer(CVertexBufferVk *pBuffer) { m_pVertexBuffer = pBuffer; }

//-----------------------------------------------------------------------------
// Sets the primitive type
//-----------------------------------------------------------------------------
void CMeshVk::SetPrimitiveType(MaterialPrimitiveType_t type)
{
    Assert(type != MATERIAL_INSTANCED_QUADS);
    if (!ShaderUtil()->OnSetPrimitiveType(this, type))
    {
        return;
    }

    m_Type = type;
    m_Mode = ComputeMode(type);
}

MaterialPrimitiveType_t CMeshVk::GetPrimitiveType() const { return m_Type; }

//-----------------------------------------------------------------------------
// Computes the number of primitives we're gonna draw
//-----------------------------------------------------------------------------
int CMeshVk::NumPrimitives(int nVertexCount, int nIndexCount) const
{
    switch (m_Mode)
    {
    case VK_PRIMITIVE_TOPOLOGY_POINT_LIST:
        return nVertexCount;

    case VK_PRIMITIVE_TOPOLOGY_LINE_LIST:
        return nIndexCount / 2;

    case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST:
        return nIndexCount / 3;

    case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP:
        return nIndexCount - 2;

    default:
        // invalid, baby!
        Assert(0);
    }

    return 0;
}

//-----------------------------------------------------------------------------
// Checks if it's a valid format
//-----------------------------------------------------------------------------
#ifdef _DEBUG
static void OutputVertexFormat(VertexFormat_t format)
{
    // FIXME: this is a duplicate of the function in meshdx8.cpp
    VertexCompressionType_t compressionType = CompressionType(format);

    if (format & VERTEX_POSITION)
    {
        Warning("VERTEX_POSITION|");
    }
    if (format & VERTEX_NORMAL)
    {
        if (compressionType == VERTEX_COMPRESSION_ON)
            Warning("VERTEX_NORMAL[COMPRESSED]|");
        else
            Warning("VERTEX_NORMAL|");
    }
    if (format & VERTEX_COLOR)
    {
        Warning("VERTEX_COLOR|");
    }
    if (format & VERTEX_SPECULAR)
    {
        Warning("VERTEX_SPECULAR|");
    }
    if (format & VERTEX_TANGENT_S)
    {
        Warning("VERTEX_TANGENT_S|");
    }
    if (format & VERTEX_TANGENT_T)
    {
        Warning("VERTEX_TANGENT_T|");
    }
    if (format & VERTEX_BONE_INDEX)
    {
        Warning("VERTEX_BONE_INDEX|");
    }
    if (format & VERTEX_FORMAT_VERTEX_SHADER)
    {
        Warning("VERTEX_FORMAT_VERTEX_SHADER|");
    }
    Warning("\nBone weights: %d (%s)\n", NumBoneWeights(format),
            (CompressionType(format) == VERTEX_COMPRESSION_ON ? "compressed" : "uncompressed"));
    Warning("user data size: %d (%s)\n", UserDataSize(format),
            (CompressionType(format) == VERTEX_COMPRESSION_ON ? "compressed" : "uncompressed"));
    Warning("num tex coords: %d\n", NumTextureCoordinates(format));
    // NOTE: This doesn't print texcoord sizes.
}
#endif

bool CMeshVk::IsValidVertexFormat(VertexFormat_t vertexFormat)
{
    // FIXME: Make this a debug-only check on say 6th July 2007 (after a week or so's testing)
    //        (i.e. avoid the 360 release build perf. hit for when we ship)
    bool bCheckCompression = (m_VertexFormat & VERTEX_FORMAT_COMPRESSED) &&
                             ((vertexFormat == VERTEX_FORMAT_UNKNOWN) || ((vertexFormat & VERTEX_FORMAT_COMPRESSED) == 0));

    if (bCheckCompression || IsPC() || IsDebug())
    {
        IMaterial *pMaterial = ShaderAPI()->GetBoundMaterial();
        Assert(pMaterial);

        // the material format should match the vertex usage, unless another format is passed in
        if (vertexFormat == VERTEX_FORMAT_UNKNOWN)
        {
            vertexFormat = pMaterial->GetVertexFormat() & ~(VERTEX_FORMAT_VERTEX_SHADER | VERTEX_FORMAT_USE_EXACT_FORMAT);

            // Blat out unused fields
            vertexFormat &= ~g_pMeshMgr->UnusedVertexFields();
            int nUnusedTextureCoords = g_pMeshMgr->UnusedTextureCoords();
            for (int i = 0; i < VERTEX_MAX_TEXTURE_COORDINATES; ++i)
            {
                if (nUnusedTextureCoords & (1 << i))
                {
                    vertexFormat &= ~VERTEX_TEXCOORD_MASK(i);
                }
            }
        }
        else
        {
            vertexFormat &= ~(VERTEX_FORMAT_VERTEX_SHADER | VERTEX_FORMAT_USE_EXACT_FORMAT);
        }

        bool bIsValid = ((VERTEX_FORMAT_FIELD_MASK & vertexFormat) & (VERTEX_FORMAT_FIELD_MASK & ~m_VertexFormat)) == 0;

        if (m_VertexFormat & VERTEX_FORMAT_COMPRESSED)
        {
            // We shouldn't get compressed verts if this material doesn't support them!
            if ((vertexFormat & VERTEX_FORMAT_COMPRESSED) == 0)
            {
                static int numWarnings = 0;
                if (numWarnings++ == 0)
                {
                    // NOTE: ComputeVertexFormat() will make sure no materials support VERTEX_FORMAT_COMPRESSED
                    //       if vertex compression is disabled in the config

                    // if (g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.SupportsCompressedVertices() ==
                    if (g_pHardwareConfig->SupportsCompressedVertices() == VERTEX_COMPRESSION_NONE)
                        Warning("ERROR: Compressed vertices in use but vertex compression is disabled (or not "
                                "supported on this hardware)!\n");
                    else
                        Warning("ERROR: Compressed vertices in use but material does not support them!\n");
                }
                Assert(0);
                bIsValid = false;
            }
        }

        bIsValid = bIsValid && UserDataSize(m_VertexFormat) >= UserDataSize(vertexFormat);

        for (int i = 0; i < VERTEX_MAX_TEXTURE_COORDINATES; i++)
        {
            if (TexCoordSize(i, m_VertexFormat) < TexCoordSize(i, vertexFormat))
            {
                bIsValid = false;
            }
        }

        // NOTE: It can totally be valid to have more weights than the current number of bones.
        // The -1 here is because if we have N bones, we can have only (N-1) weights,
        // since the Nth is implied (the weights sum to 1).
        int nWeightCount = NumBoneWeights(m_VertexFormat);
        bIsValid = bIsValid && (nWeightCount >= (g_pShaderAPI->GetCurrentNumBones() - 1));

#ifdef _DEBUG
        if (!bIsValid)
        {
            Warning("Material Format:");
            if (g_pShaderAPI->GetCurrentNumBones() > 0)
            {
                vertexFormat |= VERTEX_BONE_INDEX;
                vertexFormat &= ~VERTEX_BONE_WEIGHT_MASK;
                vertexFormat |= VERTEX_BONEWEIGHT(2);
            }

            OutputVertexFormat(vertexFormat);
            Warning("Mesh Format:");
            OutputVertexFormat(m_VertexFormat);
        }
#endif
        return bIsValid;
    }

    return true;
}

//-----------------------------------------------------------------------------
// Stream source setting methods
//-----------------------------------------------------------------------------
void CMeshVk::SetVertexIDStreamState()
{
    // FIXME: this method duplicates the code in CMeshMgr::SetVertexIDStreamState

    bool bUsingVertexID = IsUsingVertexID();
    if (bUsingVertexID != g_bUsingVertexID)
    {
        if (bUsingVertexID)
        {
            // NOTE: Morphing doesn't work with dynamic buffers!!! BLEAH
            // It's because the indices (which are not 0 based for dynamic buffers)
            // are accessing both the vertexID buffer + the regular vertex buffer.
            // This *might* be fixable with baseVertexIndex?

            // NOTE: At the moment, vertex id is only used for hw morphing. I've got it
            // set up so that a shader that supports hw morphing always says it uses vertex id.
            // If we ever use vertex id for something other than hw morphing, we're going
            // to have to revisit how those shaders say they want to use vertex id
            // or  fix this some other way
            Assert(!g_pShaderAPI->IsHWMorphingEnabled() || !m_pVertexBuffer->IsDynamic());

            CVertexBufferVk *pVertexIDBuffer = g_pMeshMgr->GetVertexIDBuffer();

            pVertexIDBuffer->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());
        }
        g_bUsingVertexID = bUsingVertexID;
    }
}

void CMeshVk::SetColorStreamState()
{
    if ((m_pColorMesh != g_pLastColorMesh) || (m_nColorMeshVertOffsetInBytes != g_nLastColorMeshVertOffsetInBytes))
    {
        if (m_pColorMesh)
        {
            m_pColorMesh->GetVertexBuffer()->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());
        }
        g_pLastColorMesh = m_pColorMesh;
        g_nLastColorMeshVertOffsetInBytes = m_nColorMeshVertOffsetInBytes;
    }
}

void CMeshVk::SetVertexStreamState(int nVertOffsetInBytes)
{
    // Calls in here assume shader support...
    // if (g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.SupportsVertexAndPixelShaders())
    if (g_pHardwareConfig->SupportsVertexAndPixelShaders())
    {
        if (HasFlexMesh())
        {
            // cFlexScale.x masks flex in vertex shader
            float c[4] = {1.0f,
                          // g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.SupportsPixelShaders_2_b() ? 1.0f : 0.0f,
                          g_pHardwareConfig->SupportsPixelShaders_2_b() ? 1.0f : 0.0f, 0.0f, 0.0f};
            ShaderAPI()->SetVertexShaderConstant(VERTEX_SHADER_FLEXSCALE, c, 1);
        }
        else
        {
            Assert(nVertOffsetInBytes == 0);
            Assert(m_pVertexBuffer);

            // HACK...point stream 2 at the same VB which is bound to stream 0...
            // NOTE: D3D debug DLLs will RIP if stream 0 has a smaller stride than the largest
            //       offset in the stream 2 vertex decl elements (which are position(12)+wrinkle(4)+normal(12))
            // If this fires, go find the material/shader which is requesting a really 'thin'
            // stream 0 vertex, and fatten it up slightly (e.g. add a D3DCOLOR element)
            int minimumStreamZeroStride = 4 * sizeof(float);
            Assert(m_pVertexBuffer->VertexSize() >= minimumStreamZeroStride);
            if (m_pVertexBuffer->VertexSize() < minimumStreamZeroStride)
            {
                static bool bWarned = false;
                if (!bWarned)
                {
                    Warning("Shader specifying too-thin vertex format, should be at least %d bytes! (Supressing "
                            "furthur warnings)\n",
                            minimumStreamZeroStride);
                    bWarned = true;
                }
            }

            // cFlexScale.x masks flex in vertex shader
            float c[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            ShaderAPI()->SetVertexShaderConstant(VERTEX_SHADER_FLEXSCALE, c, 1);
        }
    }

    // MESHFIXME: Make sure this jives between the mesh/ib/vb version.
    if ((g_pLastVertex != m_pVertexBuffer) || (g_nLastVertOffsetInBytes != nVertOffsetInBytes))
    {
        Assert(m_pVertexBuffer);

        m_pVertexBuffer->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());

        g_pLastVertex = m_pVertexBuffer;
        g_nLastVertOffsetInBytes = nVertOffsetInBytes;
    }
}

void CMeshVk::SetIndexStreamState(int firstVertexIdx)
{
    if ((g_pLastIndexBuffer != NULL) || (g_pLastIndex != m_pIndexBuffer) || (firstVertexIdx != g_LastVertexIdx))
    {
        Assert(m_pIndexBuffer);

        // VK_TODO
        // g_pShaderDevice->SetIndices(m_pIndexBuffer->GetInterface());
        m_pIndexBuffer->HandlePerFrameTextureStats(ShaderAPI()->GetCurrentFrameCounter());
        m_FirstIndex = firstVertexIdx;

        g_pLastIndex = m_pIndexBuffer;
        g_pLastIndexBuffer = NULL;
        g_LastVertexIdx = firstVertexIdx;
    }
}

bool CMeshVk::SetRenderState(int nVertexOffsetInBytes, int nFirstVertexIdx, VertexFormat_t vertexFormat)
{
    // Can't set the state if we're deactivated
    if (g_pShaderDevice->IsDeactivated())
    {
        ResetMeshRenderState();
        return false;
    }

    g_LastVertexFormat = vertexFormat;

    SetVertexIDStreamState();
    SetColorStreamState();
    SetVertexStreamState(nVertexOffsetInBytes);
    SetIndexStreamState(nFirstVertexIdx);

    return true;
}

//-----------------------------------------------------------------------------
// Draws the static mesh
//-----------------------------------------------------------------------------
void CMeshVk::Draw(int nFirstIndex, int nIndexCount)
{
    if (!ShaderUtil()->OnDrawMesh(this, nFirstIndex, nIndexCount))
    {
        MarkAsDrawn();
        return;
    }

    CPrimList primList;
    if (nFirstIndex == -1 || nIndexCount == 0)
    {
        primList.m_FirstIndex = 0;
        primList.m_NumIndices = m_NumIndices;
    }
    else
    {
        primList.m_FirstIndex = nFirstIndex;
        primList.m_NumIndices = nIndexCount;
    }
    DrawInternal(&primList, 1);
}

void CMeshVk::Draw(CPrimList *pLists, int nLists)
{
    if (!ShaderUtil()->OnDrawMesh(this, pLists, nLists))
    {
        MarkAsDrawn();
        return;
    }

    DrawInternal(pLists, nLists);
}

void CMeshVk::DrawInternal(CPrimList *pLists, int nLists)
{
    // Make sure there's something to draw..
    int i;
    for (i = 0; i < nLists; i++)
    {
        if (pLists[i].m_NumIndices > 0)
            break;
    }
    if (i == nLists)
        return;

    // can't do these in selection mode!
    Assert(!ShaderAPI()->IsInSelectionMode());

    if (!SetRenderState(0, 0))
        return;

    s_pPrims = pLists;
    s_nPrims = nLists;

#ifdef _DEBUG
    for (i = 0; i < nLists; ++i)
    {
        Assert(pLists[i].m_NumIndices > 0);
    }
#endif

    s_FirstVertex = 0;
    s_NumVertices = m_pVertexBuffer->VertexCount();

    DrawMesh();
}

//-----------------------------------------------------------------------------
// Actually does the dirty deed of rendering
//-----------------------------------------------------------------------------
void CMeshVk::RenderPass()
{
    VPROF("CMeshVk::RenderPass");

    Assert(m_Type != MATERIAL_HETEROGENOUS);

    // make sure the vertex format is a superset of the current material's
    // vertex format...
    if (!IsValidVertexFormat(g_LastVertexFormat))
    {
        Warning("Material %s does not support vertex format used by the mesh (maybe missing fields or mismatched "
                "vertex compression?), mesh will not be rendered. Grab a programmer!\n",
                ShaderAPI()->GetBoundMaterial()->GetName());
        return;
    }

    for (int iPrim = 0; iPrim < s_nPrims; iPrim++)
    {
        CPrimList *pPrim = &s_pPrims[iPrim];

        if (pPrim->m_NumIndices == 0)
            continue;

        g_pShaderDevice->DrawMesh(this);
        // VK_TODO
        /*
        if ((m_Type == MATERIAL_POINTS) || (m_Type == MATERIAL_INSTANCED_QUADS))
        {
            // (For point/instanced-quad lists, we don't actually fill in indices, but we treat it as
            // though there are indices for the list up until here).
            g_pShaderDevice->DrawPrimitive(m_Mode, s_FirstVertex, pPrim->m_NumIndices);
        }
        else
        {
            int numPrimitives = NumPrimitives(s_NumVertices, pPrim->m_NumIndices);

            {
                VPROF("g_pShaderDeviceVk->DrawIndexedPrimitive");
                VPROF_INCREMENT_COUNTER("DrawIndexedPrimitive", 1);
                VPROF_INCREMENT_COUNTER("numPrimitives", numPrimitives);

                g_pShaderDevice->DrawIndexedPrimitive(
                    m_Mode, // Member of the VkPrimitiveTopology enumerated type, describing the type of primitive to
                            // render. D3DPT_POINTLIST is not supported with this method.

                    m_FirstIndex, // Offset from the start of the vertex buffer to the first vertex index. An index of 0
                                  // in the index buffer refers to this location in the vertex buffer.

                    s_FirstVertex, // Minimum vertex index for vertices used during this call. This is a zero based
                                   // index relative to BaseVertexIndex. The first Vertex in the vertexbuffer that we
                                   // are currently using for the current batch.

                    s_NumVertices, // Number of vertices used during this call. The first vertex is located at index:
                                   // BaseVertexIndex + MinIndex.

                    pPrim->m_FirstIndex, // Index of the first index to use when accesssing the vertex buffer. Beginning
                                         // at StartIndex to index vertices from the vertex buffer.

                    numPrimitives); // Number of primitives to render. The number of vertices used is a function of the
                                    // primitive count and the primitive type.
            }
        }
        */
    }
}

//-----------------------------------------------------------------------------
//
// Dynamic mesh implementation
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
CDynamicMeshVk::CDynamicMeshVk() : CMeshVk("CDynamicMeshVk")
{
    m_nBufferId = 0;
    ResetVertexAndIndexCounts();
}

CDynamicMeshVk::~CDynamicMeshVk() {}

//-----------------------------------------------------------------------------
// Initializes the dynamic mesh
//-----------------------------------------------------------------------------
void CDynamicMeshVk::Init(int nBufferId) { m_nBufferId = nBufferId; }

//-----------------------------------------------------------------------------
// Resets buffering state
//-----------------------------------------------------------------------------
void CDynamicMeshVk::ResetVertexAndIndexCounts()
{
    m_TotalVertices = m_TotalIndices = 0;
    m_FirstIndex = m_nFirstVertex = -1;
    m_HasDrawn = false;
}

//-----------------------------------------------------------------------------
// Resets the state in case of a task switch
//-----------------------------------------------------------------------------
void CDynamicMeshVk::Reset()
{
    m_VertexFormat = 0;
    m_pVertexBuffer = 0;
    m_pIndexBuffer = 0;
    ResetVertexAndIndexCounts();

    // Force the render state to be updated next time
    ResetMeshRenderState();
}

//-----------------------------------------------------------------------------
// Sets the vertex format associated with the dynamic mesh
//-----------------------------------------------------------------------------
void CDynamicMeshVk::SetVertexFormat(VertexFormat_t format)
{
    if (g_pShaderDevice->IsDeactivated())
        return;

    if (CompressionType(format) != VERTEX_COMPRESSION_NONE)
    {
        // UNDONE: support compressed dynamic meshes if needed (pro: less VB memory, con: CMeshBuilder gets slower)
        Warning("ERROR: dynamic meshes cannot use compressed vertices!\n");
        Assert(0);
        format &= ~VERTEX_FORMAT_COMPRESSED;
    }

    if ((format != m_VertexFormat) || m_VertexOverride || m_IndexOverride)
    {
        m_VertexFormat = format;
        UseVertexBuffer(g_pMeshMgr->FindOrCreateVertexBuffer(m_nBufferId, format));

        if (m_nBufferId == 0)
        {
            UseIndexBuffer(g_pMeshMgr->GetDynamicIndexBuffer());
        }

        m_VertexOverride = m_IndexOverride = false;
    }
}

void CDynamicMeshVk::OverrideVertexBuffer(CVertexBufferVk *pVertexBuffer)
{
    UseVertexBuffer(pVertexBuffer);
    m_VertexOverride = true;
}

void CDynamicMeshVk::OverrideIndexBuffer(CIndexBufferVk *pIndexBuffer)
{
    UseIndexBuffer(pIndexBuffer);
    m_IndexOverride = true;
}

//-----------------------------------------------------------------------------
// Do I need to reset the vertex format?
//-----------------------------------------------------------------------------
bool CDynamicMeshVk::NeedsVertexFormatReset(VertexFormat_t fmt) const
{
    return m_VertexOverride || m_IndexOverride || (m_VertexFormat != fmt);
}

//-----------------------------------------------------------------------------
// Locks/unlocks the entire mesh
//-----------------------------------------------------------------------------
bool CDynamicMeshVk::HasEnoughRoom(int nVertexCount, int nIndexCount)
{
    if (g_pShaderDevice->IsDeactivated())
        return false;

    if (!m_pVertexBuffer)
    {
        m_pVertexBuffer = (CVertexBufferVk *)g_pShaderDevice->CreateVertexBuffer(SHADER_BUFFER_TYPE_DYNAMIC, m_VertexFormat, nVertexCount,
                                                                                 m_pTextureGroupName);
    }

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = (CIndexBufferVk *)g_pShaderDevice->CreateIndexBuffer(SHADER_BUFFER_TYPE_DYNAMIC, MATERIAL_INDEX_FORMAT_UNKNOWN,
                                                                              nVertexCount, m_pTextureGroupName);
    }

    // We need space in both the vertex and index buffer
    return m_pVertexBuffer->HasEnoughRoom(nVertexCount) && m_pIndexBuffer->HasEnoughRoom(nIndexCount);
}

//-----------------------------------------------------------------------------
// returns the number of indices in the mesh
//-----------------------------------------------------------------------------
int CDynamicMeshVk::IndexCount() const { return m_TotalIndices; }

//-----------------------------------------------------------------------------
// Operation to do pre-lock	(only called for buffered meshes)
//-----------------------------------------------------------------------------
void CDynamicMeshVk::PreLock()
{
    if (m_HasDrawn)
    {
        // Start again then
        ResetVertexAndIndexCounts();
    }
}

//-----------------------------------------------------------------------------
// Locks/unlocks the entire mesh
//-----------------------------------------------------------------------------
void CDynamicMeshVk::LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    ShaderUtil()->SyncMatrices();

    PreLock();

    if (m_VertexOverride)
    {
        nVertexCount = 0;
    }

    if (m_IndexOverride)
    {
        nIndexCount = 0;
    }

    Lock(nVertexCount, false, *static_cast<VertexDesc_t *>(&desc));
    if (m_nFirstVertex < 0)
    {
        m_nFirstVertex = desc.m_nFirstVertex;
    }

    // When we're using a static index buffer or a flex mesh, the indices assume vertices start at 0
    if (m_IndexOverride || HasFlexMesh())
    {
        desc.m_nFirstVertex -= m_nFirstVertex;
    }

    // Don't add indices for points; DrawIndexedPrimitive not supported for them.
    if (m_Type == MATERIAL_POINTS)
    {
        desc.m_pIndices = (uint16_t *)(&g_nScratchIndexBuffer);
        desc.m_nIndexSize = 0;
    }
    else
    {
        int nFirstIndex = Lock(false, -1, nIndexCount, *static_cast<IndexDesc_t *>(&desc));
        if (m_FirstIndex < 0)
        {
            m_FirstIndex = nFirstIndex;
        }
    }

    CBaseMeshVk::m_bMeshLocked = true;
}

//-----------------------------------------------------------------------------
// Unlocks the mesh
//-----------------------------------------------------------------------------
void CDynamicMeshVk::UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    m_TotalVertices += nVertexCount;
    m_TotalIndices += nIndexCount;

    if (DebugTrace())
    {
        Spew(nVertexCount, nIndexCount, desc);
    }

    CMeshVk::UnlockMesh(nVertexCount, nIndexCount, desc);
}

//-----------------------------------------------------------------------------
// Draws it
//-----------------------------------------------------------------------------
void CDynamicMeshVk::Draw(int nFirstIndex, int nIndexCount)
{
    if (!ShaderUtil()->OnDrawMesh(this, nFirstIndex, nIndexCount))
    {
        MarkAsDrawn();
        return;
    }

    VPROF("CDynamicMeshVk::Draw");

    m_HasDrawn = true;

    if (m_IndexOverride || m_VertexOverride ||
        ((m_TotalVertices > 0) && (m_TotalIndices > 0 || m_Type == MATERIAL_POINTS || m_Type == MATERIAL_INSTANCED_QUADS)))
    {
        Assert(!m_IsDrawing);

        // only have a non-zero first vertex when we are using static indices
        int nFirstVertex = m_VertexOverride ? 0 : m_nFirstVertex;
        int actualFirstVertex = m_IndexOverride ? nFirstVertex : 0;
        int nVertexOffsetInBytes = HasFlexMesh() ? nFirstVertex * g_pMeshMgr->VertexFormatSize(GetVertexFormat()) : 0;
        int baseIndex = m_IndexOverride ? 0 : m_FirstIndex;

        // Overriding with the dynamic index buffer, preserve state!
        if (m_IndexOverride && m_pIndexBuffer == g_pMeshMgr->GetDynamicIndexBuffer())
        {
            Assert(m_pIndexBuffer);
            baseIndex = m_FirstIndex;
        }

        VertexFormat_t fmt = m_VertexOverride ? GetVertexFormat() : VERTEX_FORMAT_UNKNOWN;
        if (!SetRenderState(nVertexOffsetInBytes, actualFirstVertex, fmt))
            return;

        // Draws a portion of the mesh
        int numVertices = m_VertexOverride ? m_pVertexBuffer->VertexCount() : m_TotalVertices;
        if ((nFirstIndex != -1) && (nIndexCount != 0))
        {
            nFirstIndex += baseIndex;
        }
        else
        {
            // by default we draw the whole thing
            nFirstIndex = baseIndex;
            if (m_IndexOverride)
            {
                nIndexCount = m_pIndexBuffer->IndexCount();
                Assert(nIndexCount != 0);
            }
            else
            {
                nIndexCount = m_TotalIndices;
                // Fake out the index count	if we're drawing points/instanced-quads
                if ((m_Type == MATERIAL_POINTS) || (m_Type == MATERIAL_INSTANCED_QUADS))
                {
                    nIndexCount = m_TotalVertices;
                }
                Assert(nIndexCount != 0);
            }
        }

        // Fix up nFirstVertex to indicate the first vertex used in the data
        if (!HasFlexMesh())
        {
            actualFirstVertex = nFirstVertex - actualFirstVertex;
        }

        s_FirstVertex = actualFirstVertex;
        s_NumVertices = numVertices;

        // Build a primlist with 1 element..
        CPrimList prim;
        prim.m_FirstIndex = nFirstIndex;
        prim.m_NumIndices = nIndexCount;
        Assert(nIndexCount != 0);
        s_pPrims = &prim;
        s_nPrims = 1;

        // VK_TODO: Why is this needed?
        // IndexCount() returns wrong value without this...
        m_TotalIndices = nIndexCount;

        DrawMesh();

        s_pPrims = NULL;
    }
}

//-----------------------------------------------------------------------------
// This is useful when we need to dynamically modify data; just set the
// render state and draw the pass immediately
//-----------------------------------------------------------------------------
void CDynamicMeshVk::DrawSinglePassImmediately()
{
    if ((m_TotalVertices > 0) || (m_TotalIndices > 0))
    {
        Assert(!m_IsDrawing);

        // Set the render state
        if (SetRenderState(0, 0))
        {
            s_FirstVertex = m_nFirstVertex;
            s_NumVertices = m_TotalVertices;

            // Make a temporary PrimList to hold the indices.
            CPrimList prim(m_FirstIndex, m_TotalIndices);
            Assert(m_TotalIndices != 0);
            s_pPrims = &prim;
            s_nPrims = 1;

            // Render it
            RenderPass();
        }

        // We're done with our data
        ResetVertexAndIndexCounts();
    }
}

//-----------------------------------------------------------------------------
//
// A mesh that stores temporary vertex data in the correct format (for modification)
//
//-----------------------------------------------------------------------------
// Used in rendering sub-parts of the mesh
unsigned int CTempMeshVk::s_NumIndices;
unsigned int CTempMeshVk::s_FirstIndex;

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
CTempMeshVk::CTempMeshVk(bool isDynamic) : m_VertexSize(0xFFFF), m_IsDynamic(isDynamic)
{
#ifdef _DEBUG
    m_Locked = false;
    m_InPass = false;
#endif
}

CTempMeshVk::~CTempMeshVk() {}

//-----------------------------------------------------------------------------
// Is the temp mesh dynamic?
//-----------------------------------------------------------------------------
bool CTempMeshVk::IsDynamic() const { return m_IsDynamic; }

//-----------------------------------------------------------------------------
// Sets the vertex format
//-----------------------------------------------------------------------------
void CTempMeshVk::SetVertexFormat(VertexFormat_t format)
{
    CBaseMeshVk::SetVertexFormat(format);
    m_VertexSize = g_pMeshMgr->VertexFormatSize(format);
}

//-----------------------------------------------------------------------------
// returns the # of vertices (static meshes only)
//-----------------------------------------------------------------------------
int CTempMeshVk::VertexCount() const { return m_VertexSize ? m_VertexData.Count() / m_VertexSize : 0; }

//-----------------------------------------------------------------------------
// returns the # of indices
//-----------------------------------------------------------------------------
int CTempMeshVk::IndexCount() const { return m_IndexData.Count(); }

void CTempMeshVk::ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc)
{
    Assert(!m_Locked);

    m_LockedVerts = nVertexCount;
    m_LockedIndices = nIndexCount;

    if (nVertexCount > 0)
    {
        int vertexByteOffset = m_VertexSize * nFirstVertex;

        // Lock it baby
        unsigned char *pVertexMemory = &m_VertexData[vertexByteOffset];

        // Compute the vertex index..
        desc.m_nFirstVertex = vertexByteOffset / m_VertexSize;

        // Set up the mesh descriptor
        g_pMeshMgr->ComputeVertexDescription(pVertexMemory, m_VertexFormat, desc);
    }
    else
    {
        desc.m_nFirstVertex = 0;
        // Set up the mesh descriptor
        g_pMeshMgr->ComputeVertexDescription(0, 0, desc);
    }

    if (m_Type != MATERIAL_POINTS && nIndexCount > 0)
    {
        desc.m_pIndices = &m_IndexData[nFirstIndex];
        desc.m_nIndexSize = 1;
    }
    else
    {
        desc.m_pIndices = (uint16_t *)(&g_nScratchIndexBuffer);
        desc.m_nIndexSize = 0;
    }

#ifdef _DEBUG
    m_Locked = true;
#endif
}

void CTempMeshVk::ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc)
{
    ModifyBeginEx(false, nFirstVertex, nVertexCount, nFirstIndex, nIndexCount, desc);
}

void CTempMeshVk::ModifyEnd(MeshDesc_t &desc)
{
#ifdef _DEBUG
    Assert(m_Locked);
    m_Locked = false;
#endif
}

//-----------------------------------------------------------------------------
// Locks/unlocks the mesh
//-----------------------------------------------------------------------------
void CTempMeshVk::LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    ShaderUtil()->SyncMatrices();

    Assert(!m_Locked);

    m_LockedVerts = nVertexCount;
    m_LockedIndices = nIndexCount;

    if (nVertexCount > 0)
    {
        int vertexByteOffset = m_VertexData.AddMultipleToTail(m_VertexSize * nVertexCount);

        // Lock it baby
        unsigned char *pVertexMemory = &m_VertexData[vertexByteOffset];

        // Compute the vertex index..
        desc.m_nFirstVertex = vertexByteOffset / m_VertexSize;

        // Set up the mesh descriptor
        g_pMeshMgr->ComputeVertexDescription(pVertexMemory, m_VertexFormat, desc);
    }
    else
    {
        desc.m_nFirstVertex = 0;
        // Set up the mesh descriptor
        g_pMeshMgr->ComputeVertexDescription(0, 0, desc);
    }

    if (m_Type != MATERIAL_POINTS && nIndexCount > 0)
    {
        int nFirstIndex = m_IndexData.AddMultipleToTail(nIndexCount);
        desc.m_pIndices = &m_IndexData[nFirstIndex];
        desc.m_nIndexSize = 1;
    }
    else
    {
        desc.m_pIndices = (uint16_t *)(&g_nScratchIndexBuffer);
        desc.m_nIndexSize = 0;
    }

#ifdef _DEBUG
    m_Locked = true;
#endif

    CBaseMeshVk::m_bMeshLocked = true;
}

void CTempMeshVk::UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    Assert(m_Locked);

    // Remove unused vertices and indices
    int verticesToRemove = m_LockedVerts - nVertexCount;
    if (verticesToRemove != 0)
    {
        m_VertexData.RemoveMultiple(m_VertexData.Count() - verticesToRemove, verticesToRemove);
    }

    int indicesToRemove = m_LockedIndices - nIndexCount;
    if (indicesToRemove != 0)
    {
        m_IndexData.RemoveMultiple(m_IndexData.Count() - indicesToRemove, indicesToRemove);
    }

#ifdef _DEBUG
    m_Locked = false;
#endif

    CBaseMeshVk::m_bMeshLocked = false;
}

//-----------------------------------------------------------------------------
// Sets the primitive type
//-----------------------------------------------------------------------------
void CTempMeshVk::SetPrimitiveType(MaterialPrimitiveType_t type)
{
    Assert((type != MATERIAL_INSTANCED_QUADS));
    m_Type = type;
}

MaterialPrimitiveType_t CTempMeshVk::GetPrimitiveType() const { return m_Type; }

//-----------------------------------------------------------------------------
// Gets the dynamic mesh
//-----------------------------------------------------------------------------
CDynamicMeshVk *CTempMeshVk::GetDynamicMesh() { return static_cast<CDynamicMeshVk *>(g_pMeshMgr->GetActualDynamicMesh(m_VertexFormat)); }

//-----------------------------------------------------------------------------
// Draws the entire mesh
//-----------------------------------------------------------------------------
void CTempMeshVk::Draw(int nFirstIndex, int nIndexCount)
{
    if (!ShaderUtil()->OnDrawMesh(this, nFirstIndex, nIndexCount))
    {
        MarkAsDrawn();
        return;
    }

    if (m_VertexData.Count() > 0)
    {
        if (!g_pShaderDevice->IsDeactivated())
        {
            if (!ShaderAPI()->IsInSelectionMode())
            {
                s_FirstIndex = nFirstIndex;
                s_NumIndices = nIndexCount;

                DrawMesh();

                // This assertion fails if a BeginPass() call was not matched by
                // a RenderPass() call
                Assert(!m_InPass);
            }
            else
            {
                TestSelection();
            }
        }

        // Clear out the data if this temp mesh is a dynamic one...
        if (m_IsDynamic)
        {
            m_VertexData.RemoveAll();
            m_IndexData.RemoveAll();
        }
    }
}

void CTempMeshVk::CopyToMeshBuilder(int iStartVert, // Which vertices to copy.
                                    int nVerts,
                                    int iStartIndex, // Which indices to copy.
                                    int nIndices,
                                    int indexOffset, // This is added to each index.
                                    CMeshBuilder &builder)
{
    int startOffset = iStartVert * m_VertexSize;
    int endOffset = (iStartVert + nVerts) * m_VertexSize;
    Assert(startOffset >= 0 && startOffset <= m_VertexData.Count());
    Assert(endOffset >= 0 && endOffset <= m_VertexData.Count() && endOffset >= startOffset);
    if (endOffset > startOffset)
    {
        // FIXME: make this a method of CMeshBuilder (so the 'Position' pointer accessor can be removed)
        //        make sure it takes a VertexFormat_t parameter for src/dest match validation
        memcpy((void *)builder.Position(), &m_VertexData[startOffset], endOffset - startOffset);
        builder.AdvanceVertices(nVerts);
    }

    for (int i = 0; i < nIndices; ++i)
    {
        builder.Index(m_IndexData[iStartIndex + i] + indexOffset);
        builder.AdvanceIndex();
    }
}

//-----------------------------------------------------------------------------
// Selection mode helper functions
//-----------------------------------------------------------------------------
static void ComputeModelToView(glm::mat4 &modelToView)
{
    // Get the modelview matrix...
    glm::mat4 world, view;
    ShaderAPI()->GetMatrix(MATERIAL_MODEL, (float *)&world);
    ShaderAPI()->GetMatrix(MATERIAL_VIEW, (float *)&view);
    modelToView = glm::matrixCompMult(world, view);
}

static float ComputeCullFactor()
{
    // VkCullModeFlagBits cullMode = ShaderAPI()->GetCullMode();
    VkCullModeFlagBits cullMode = VK_CULL_MODE_BACK_BIT;
    if (ShaderAPI()->GetBoundMaterial()->GetMaterialVarFlag(MATERIAL_VAR_NOCULL))
        cullMode = VK_CULL_MODE_NONE;

    float cullFactor;
    switch (cullMode)
    {
    // VK_TODO: is this correct?

    // case D3DCULL_CCW:
    case VK_CULL_MODE_FRONT_BIT:
        cullFactor = -1.0f;
        break;

    // case D3DCULL_CW:
    case VK_CULL_MODE_BACK_BIT:
        cullFactor = 1.0f;
        break;

    default:
        cullFactor = 0.0f;
        break;
    };

    return cullFactor;
}

//-----------------------------------------------------------------------------
// Clip to viewport
//-----------------------------------------------------------------------------
static int g_NumClipVerts;
static glm::vec3 g_ClipVerts[16];

static bool PointInsidePlane(glm::vec3 *pVert, int normalInd, float val, bool nearClip)
{
    if ((val > 0) || nearClip)
        return (val - (*pVert)[normalInd] >= 0);
    else
        return ((*pVert)[normalInd] - val >= 0);
}

static void IntersectPlane(glm::vec3 *pStart, glm::vec3 *pEnd, int normalInd, float val, glm::vec3 *pOutVert)
{
    glm::vec3 dir = *pEnd - *pStart;
    Assert(dir[normalInd] != 0.0f);
    float t = (val - (*pStart)[normalInd]) / dir[normalInd];
    pOutVert->x = pStart->x + dir.x * t;
    pOutVert->y = pStart->y + dir.y * t;
    pOutVert->z = pStart->z + dir.z * t;

    // Avoid any precision problems.
    (*pOutVert)[normalInd] = val;
}

static int ClipTriangleAgainstPlane(glm::vec3 **ppVert, int nVertexCount, glm::vec3 **ppOutVert, int normalInd, float val,
                                    bool nearClip = false)
{
    // Ye Olde Sutherland-Hodgman clipping algorithm
    int numOutVerts = 0;
    glm::vec3 *pStart = ppVert[nVertexCount - 1];
    bool startInside = PointInsidePlane(pStart, normalInd, val, nearClip);
    for (int i = 0; i < nVertexCount; ++i)
    {
        glm::vec3 *pEnd = ppVert[i];
        bool endInside = PointInsidePlane(pEnd, normalInd, val, nearClip);
        if (endInside)
        {
            if (!startInside)
            {
                IntersectPlane(pStart, pEnd, normalInd, val, &g_ClipVerts[g_NumClipVerts]);
                ppOutVert[numOutVerts++] = &g_ClipVerts[g_NumClipVerts++];
            }
            ppOutVert[numOutVerts++] = pEnd;
        }
        else
        {
            if (startInside)
            {
                IntersectPlane(pStart, pEnd, normalInd, val, &g_ClipVerts[g_NumClipVerts]);
                ppOutVert[numOutVerts++] = &g_ClipVerts[g_NumClipVerts++];
            }
        }
        pStart = pEnd;
        startInside = endInside;
    }

    return numOutVerts;
}

void CTempMeshVk::ClipTriangle(glm::vec3 **ppVert, float zNear, glm::mat4 &projection)
{
    int i;
    int nVertexCount = 3;
    glm::vec3 **ppClipVert1;
    glm::vec3 **ppClipVert2;

    g_NumClipVerts = 0;

    // Clip against the near plane in view space to prevent negative w.
    // Clip against each plane
    nVertexCount = ClipTriangleAgainstPlane(ppVert, nVertexCount, ppClipVert1, 2, zNear, true);
    if (nVertexCount < 3)
        return;

    // Sucks that I have to do this, but I have to clip near plane in view space
    // Clipping in projection space is screwy when w < 0
    // Transform the clipped points into projection space
    Assert(g_NumClipVerts <= 2);
    for (i = 0; i < nVertexCount; ++i)
    {
        if (ppClipVert1[i] == &g_ClipVerts[0])
        {
            // VK_TODO: glm doesn't like vec3 * mat4
            g_ClipVerts[0] = TransformVec3(*ppClipVert1[i], projection);
        }
        else if (ppClipVert1[i] == &g_ClipVerts[1])
        {
            g_ClipVerts[1] = TransformVec3(*ppClipVert1[i], projection);
        }
        else
        {
            g_ClipVerts[g_NumClipVerts] = TransformVec3(*ppClipVert1[i], projection);
            ppClipVert1[i] = &g_ClipVerts[g_NumClipVerts];
            ++g_NumClipVerts;
        }
    }

    nVertexCount = ClipTriangleAgainstPlane(ppClipVert1, nVertexCount, ppClipVert2, 2, 1.0f);
    if (nVertexCount < 3)
        return;

    nVertexCount = ClipTriangleAgainstPlane(ppClipVert2, nVertexCount, ppClipVert1, 0, 1.0f);
    if (nVertexCount < 3)
        return;

    nVertexCount = ClipTriangleAgainstPlane(ppClipVert1, nVertexCount, ppClipVert2, 0, -1.0f);
    if (nVertexCount < 3)
        return;

    nVertexCount = ClipTriangleAgainstPlane(ppClipVert2, nVertexCount, ppClipVert1, 1, 1.0f);
    if (nVertexCount < 3)
        return;

    nVertexCount = ClipTriangleAgainstPlane(ppClipVert1, nVertexCount, ppClipVert2, 1, -1.0f);
    if (nVertexCount < 3)
        return;

    // Compute closest and furthest verts
    float minz = ppClipVert2[0]->z;
    float maxz = ppClipVert2[0]->z;
    for (i = 1; i < nVertexCount; ++i)
    {
        if (ppClipVert2[i]->z < minz)
            minz = ppClipVert2[i]->z;
        else if (ppClipVert2[i]->z > maxz)
            maxz = ppClipVert2[i]->z;
    }

    ShaderAPI()->RegisterSelectionHit(minz, maxz);
}

//-----------------------------------------------------------------------------
// Selection mode
//-----------------------------------------------------------------------------
void CTempMeshVk::TestSelection()
{
    // Note that this doesn't take into account any vertex modification
    // done in a vertex shader. Also it doesn't take into account any clipping
    // done in hardware

    // Blow off points and lines; they don't matter
    if ((m_Type != MATERIAL_TRIANGLES) && (m_Type != MATERIAL_TRIANGLE_STRIP))
        return;

    glm::mat4 modelToView, projection;
    ComputeModelToView(modelToView);
    ShaderAPI()->GetMatrix(MATERIAL_PROJECTION, (float *)&projection);
    float zNear = -projection[3][2] / projection[2][2];

    glm::vec3 *pPos[3];
    glm::vec3 edge[2];

    int numTriangles;
    if (m_Type == MATERIAL_TRIANGLES)
        numTriangles = m_IndexData.Count() / 3;
    else
        numTriangles = m_IndexData.Count() - 2;

    float cullFactor = ComputeCullFactor();

    // Makes the lovely loop simpler
    if (m_Type == MATERIAL_TRIANGLE_STRIP)
        cullFactor *= -1.0f;

    // We'll need some temporary memory to tell us if we're transformed the vert
    int nVertexCount = m_VertexData.Count() / m_VertexSize;
    static CUtlVector<unsigned char> transformedVert;
    int transformedVertSize = (nVertexCount + 7) >> 3;
    transformedVert.RemoveAll();
    transformedVert.EnsureCapacity(transformedVertSize);
    transformedVert.AddMultipleToTail(transformedVertSize);
    memset(transformedVert.Base(), 0, transformedVertSize);

    int indexPos;
    for (int i = 0; i < numTriangles; ++i)
    {
        // Get the three indices
        if (m_Type == MATERIAL_TRIANGLES)
        {
            indexPos = i * 3;
        }
        else
        {
            Assert(m_Type == MATERIAL_TRIANGLE_STRIP);
            cullFactor *= -1.0f;
            indexPos = i;
        }

        // BAH. Gotta clip to the near clip plane in view space to prevent
        // negative w coords; negative coords throw off the projection-space clipper.

        // Get the three positions in view space
        int inFrontIdx = -1;
        for (int j = 0; j < 3; ++j)
        {
            int index = m_IndexData[indexPos];
            glm::vec3 *pPosition = (glm::vec3 *)&m_VertexData[index * m_VertexSize];
            if ((transformedVert[index >> 3] & (1 << (index & 0x7))) == 0)
            {
                *pPosition = TransformVec3(*pPosition, modelToView);
                transformedVert[index >> 3] |= (1 << (index & 0x7));
            }

            pPos[j] = pPosition;
            if (pPos[j]->z < 0.0f)
                inFrontIdx = j;
            ++indexPos;
        }

        // all points are behind the camera
        if (inFrontIdx < 0)
            continue;

        // backface cull....
        edge[0] = *pPos[1] - *pPos[0];
        edge[1] = *pPos[2] - *pPos[0];
        glm::vec3 normal = edge[0] - edge[1];
        const float dot = glm::dot(normal, *pPos[inFrontIdx]);
        if (dot * cullFactor > 0.0f)
            continue;

        // Clip to viewport
        ClipTriangle(pPos, zNear, projection);
    }
}

//-----------------------------------------------------------------------------
// Begins a render pass
//-----------------------------------------------------------------------------
void CTempMeshVk::BeginPass()
{
    Assert(!m_InPass);

#ifdef _DEBUG
    m_InPass = true;
#endif

    CMeshBuilder *pMeshBuilder = ShaderAPI()->GetVertexModifyBuilder();

    CDynamicMeshVk *pMesh = GetDynamicMesh();

    int nIndexCount;
    int nFirstIndex;
    if ((s_FirstIndex == -1) && (s_NumIndices == 0))
    {
        nIndexCount = m_IndexData.Count();
        nFirstIndex = 0;
    }
    else
    {
        nIndexCount = s_NumIndices;
        nFirstIndex = s_FirstIndex;
    }

    int i;
    int nVertexCount = m_VertexData.Count() / m_VertexSize;
    pMeshBuilder->Begin(pMesh, m_Type, nVertexCount, nIndexCount);

    // Copy in the vertex data...
    // Note that since we pad the vertices, it's faster for us to simply
    // copy the fields we're using...
    Assert(pMeshBuilder->BaseVertexData());
    memcpy(pMeshBuilder->BaseVertexData(), m_VertexData.Base(), m_VertexData.Count());
    pMeshBuilder->AdvanceVertices(m_VertexData.Count() / m_VertexSize);

    for (i = 0; i < nIndexCount; ++i)
    {
        pMeshBuilder->Index(m_IndexData[nFirstIndex + i]);
        pMeshBuilder->AdvanceIndex();
    }

    // NOTE: The client is expected to modify the data after this call is made
    pMeshBuilder->Reset();
}

//-----------------------------------------------------------------------------
// Draws a single pass
//-----------------------------------------------------------------------------
void CTempMeshVk::RenderPass()
{
    Assert(m_InPass);

#ifdef _DEBUG
    m_InPass = false;
#endif

    // Have the shader API modify the vertex data as it needs
    // This vertex data is modified based on state set by the material
    ShaderAPI()->ModifyVertexData();

    // Done building the mesh
    ShaderAPI()->GetVertexModifyBuilder()->End();

    // Have the dynamic mesh render a single pass...
    GetDynamicMesh()->DrawSinglePassImmediately();
}

//-----------------------------------------------------------------------------
//
// Buffered mesh implementation
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

CBufferedMeshVk::CBufferedMeshVk() : m_IsFlushing(false), m_WasRendered(true)
{
    m_pMesh = NULL;
#ifdef DEBUG_BUFFERED_STATE
    m_BufferedStateSet = false;
#endif
}

CBufferedMeshVk::~CBufferedMeshVk() {}

//-----------------------------------------------------------------------------
// Sets the mesh
//-----------------------------------------------------------------------------
void CBufferedMeshVk::SetMesh(IMesh *pMesh)
{
    if (m_pMesh != pMesh)
    {
        ShaderAPI()->FlushBufferedPrimitives();
        m_pMesh = (CBaseMeshVk *)pMesh;
    }
}

//-----------------------------------------------------------------------------
// Spews the mesh data
//-----------------------------------------------------------------------------
void CBufferedMeshVk::Spew(int nVertexCount, int nIndexCount, const MeshDesc_t &spewDesc)
{
    if (m_pMesh)
    {
        m_pMesh->Spew(nVertexCount, nIndexCount, spewDesc);
    }
}

//-----------------------------------------------------------------------------
// Sets the material
//-----------------------------------------------------------------------------
void CBufferedMeshVk::SetVertexFormat(VertexFormat_t format)
{
    Assert(m_pMesh);
    if (m_pMesh->NeedsVertexFormatReset(format))
    {
        ShaderAPI()->FlushBufferedPrimitives();
        m_pMesh->SetVertexFormat(format);
    }
}

void CBufferedMeshVk::SetMorphFormat(MorphFormat_t format)
{
    Assert(m_pMesh);
    m_pMesh->SetMorphFormat(format);
}

VertexFormat_t CBufferedMeshVk::GetVertexFormat() const
{
    Assert(m_pMesh);
    return m_pMesh->GetVertexFormat();
}

void CBufferedMeshVk::SetMaterial(IMaterial *pMaterial)
{
#if _DEBUG
    Assert(m_pMesh);
    m_pMesh->SetMaterial(pMaterial);
#endif
}

void CBufferedMeshVk::ValidateData(int nVertexCount, int nIndexCount, const MeshDesc_t &spewDesc)
{
#if _DEBUG
    Assert(m_pMesh);
    m_pMesh->ValidateData(nVertexCount, nIndexCount, spewDesc);
#endif
}

//-----------------------------------------------------------------------------
// Sets the flex mesh to render with this mesh
//-----------------------------------------------------------------------------
void CBufferedMeshVk::SetFlexMesh(IMesh *pMesh, int nVertexOffsetInBytes)
{
    // FIXME: Probably are situations where we don't need to flush,
    // but this is going to look different in a very short while, so I'm not going to bother
    ShaderAPI()->FlushBufferedPrimitives();
    m_pMesh->SetFlexMesh(pMesh, nVertexOffsetInBytes);
}

//-----------------------------------------------------------------------------
// checks to see if it was rendered..
//-----------------------------------------------------------------------------
void CBufferedMeshVk::ResetRendered() { m_WasRendered = false; }

bool CBufferedMeshVk::WasNotRendered() const { return !m_WasRendered; }

//-----------------------------------------------------------------------------
// "Draws" it
//-----------------------------------------------------------------------------
void CBufferedMeshVk::Draw(int nFirstIndex, int nIndexCount)
{
    if (!ShaderUtil()->OnDrawMesh(this, nFirstIndex, nIndexCount))
    {
        m_WasRendered = true;
        MarkAsDrawn();
        return;
    }

    Assert(!m_IsFlushing && !m_WasRendered);

    // Gotta draw all of the buffered mesh
    Assert((nFirstIndex == -1) && (nIndexCount == 0));

    // No need to draw it more than once...
    m_WasRendered = true;

    // We've got something to flush
    m_FlushNeeded = true;

    // Less than 0 indices indicates we were using a standard buffer
    if (m_pMesh->HasFlexMesh() || !ShaderUtil()->GetConfig().bBufferPrimitives)
    {
        ShaderAPI()->FlushBufferedPrimitives();
    }
}

//-----------------------------------------------------------------------------
// Sets the primitive mode
//-----------------------------------------------------------------------------

void CBufferedMeshVk::SetPrimitiveType(MaterialPrimitiveType_t type)
{
    Assert((type != MATERIAL_INSTANCED_QUADS));
    Assert(type != MATERIAL_HETEROGENOUS);

    if (type != GetPrimitiveType())
    {
        ShaderAPI()->FlushBufferedPrimitives();
        m_pMesh->SetPrimitiveType(type);
    }
}

MaterialPrimitiveType_t CBufferedMeshVk::GetPrimitiveType() const { return m_pMesh->GetPrimitiveType(); }

//-----------------------------------------------------------------------------
// Locks/unlocks the entire mesh
//-----------------------------------------------------------------------------
void CBufferedMeshVk::LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    ShaderUtil()->SyncMatrices();

    Assert(m_pMesh);
    Assert(m_WasRendered);

    // Do some pre-lock processing
    m_pMesh->PreLock();

    // for tristrips, gotta make degenerate ones...
    m_ExtraIndices = 0;
    bool tristripFixup = (m_pMesh->IndexCount() != 0) && (m_pMesh->GetPrimitiveType() == MATERIAL_TRIANGLE_STRIP);
    if (tristripFixup)
    {
        m_ExtraIndices = (m_pMesh->IndexCount() & 0x1) != 0 ? 3 : 2;
        nIndexCount += m_ExtraIndices;
    }

    // Flush if we gotta
    if (!m_pMesh->HasEnoughRoom(nVertexCount, nIndexCount))
    {
        ShaderAPI()->FlushBufferedPrimitives();
    }

    m_pMesh->LockMesh(nVertexCount, nIndexCount, desc);

    //	This is taken care of in the function above.
    //	CBaseMeshVk::m_bMeshLocked = true;

    // Deal with fixing up the tristrip..
    if (tristripFixup && desc.m_nIndexSize)
    {
        char buf[32];
        if (DebugTrace())
        {
            if (m_ExtraIndices == 3)
                sprintf(buf, "Link Index: %d %d\n", m_LastIndex, m_LastIndex);
            else
                sprintf(buf, "Link Index: %d\n", m_LastIndex);
            Plat_DebugString(buf);
        }
        *desc.m_pIndices++ = m_LastIndex;
        if (m_ExtraIndices == 3)
        {
            *desc.m_pIndices++ = m_LastIndex;
        }

        // Leave room for the last padding index
        ++desc.m_pIndices;
    }

    m_WasRendered = false;
}

//-----------------------------------------------------------------------------
// Locks/unlocks the entire mesh
//-----------------------------------------------------------------------------
void CBufferedMeshVk::UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc)
{
    Assert(m_pMesh);

    // Gotta fix up the first index to batch strips reasonably
    if ((m_pMesh->GetPrimitiveType() == MATERIAL_TRIANGLE_STRIP) && desc.m_nIndexSize)
    {
        if (m_ExtraIndices > 0)
        {
            *(desc.m_pIndices - 1) = *desc.m_pIndices;

            if (DebugTrace())
            {
                char buf[32];
                sprintf(buf, "Link Index: %d\n", *desc.m_pIndices);
                Plat_DebugString(buf);
            }
        }

        // Remember the last index for next time
        m_LastIndex = desc.m_pIndices[nIndexCount - 1];

        nIndexCount += m_ExtraIndices;
    }

    m_pMesh->UnlockMesh(nVertexCount, nIndexCount, desc);

    //	This is taken care of in the function above.
    //	CBaseMeshVk::m_bMeshLocked = false;
}

//-----------------------------------------------------------------------------
// Renders a pass
//-----------------------------------------------------------------------------

void CBufferedMeshVk::RenderPass()
{
    // this should never be called!
    Assert(0);
}

//-----------------------------------------------------------------------------
// Flushes queued data
//-----------------------------------------------------------------------------

void CBufferedMeshVk::Flush()
{
    // If you are hitting this assert you are causing a flush between a
    // meshbuilder begin/end and you are more than likely losing rendering data.
    AssertOnce(!CBaseMeshVk::m_bMeshLocked);

    if (m_pMesh && !m_IsFlushing && m_FlushNeeded)
    {
        VPROF("CBufferedMeshVk::Flush");

        m_IsFlushing = true;

        // Actually draws the data using the mesh's material
        static_cast<IMesh *>(m_pMesh)->Draw();

        m_IsFlushing = false;
        m_FlushNeeded = false;

        m_pMesh->SetFlexMesh(NULL, 0);
    }
}