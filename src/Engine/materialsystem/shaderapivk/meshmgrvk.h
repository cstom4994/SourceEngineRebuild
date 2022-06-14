//

#ifndef MESHMGRVK_H
#define MESHMGRVK_H

#ifdef _WIN32
#pragma once
#endif

#include "indexbuffervk.h"
#include "materialsystem/imesh.h"
#include "meshvk.h"
#include "shaderapi/IShaderDevice.h"
#include "vertexbuffervk.h"

// VK_TODO: The num of used streams is always 1,
// see implementation of CMeshMgr::BindVertexBuffer.
// Everything using this should be cleaned up.
#define MAX_VK_STREAMS 1

static unsigned int g_nScratchIndexBuffer = 0; // shove indices into this if you don't actually want indices

class CMeshMgrVk
{
  public:
    // constructor, destructor
    CMeshMgrVk();
    virtual ~CMeshMgrVk();

    // Initialize, shutdown
    void Init();
    void Shutdown();

    // Task switch...
    void ReleaseBuffers();
    void RestoreBuffers();

    // Releases all dynamic vertex buffers
    void DestroyVertexBuffers();

    // Flushes the dynamic mesh
    void Flush();

    // Flushes the vertex buffers
    void DiscardVertexBuffers();

    // Creates, destroys static meshes
    IMesh *CreateStaticMesh(VertexFormat_t vertexFormat, const char *pTextureBudgetGroup, IMaterial *pMaterial = NULL);
    void DestroyStaticMesh(IMesh *pMesh);

    // Gets at the dynamic mesh	(spoofs it though)
    IMesh *GetDynamicMesh(IMaterial *pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount, bool buffered,
                          IMesh *pVertexOverride, IMesh *pIndexOverride);

    // Do we need to specify the stream here in the case of locking multiple dynamic VBs on different streams?
    IVertexBuffer *GetDynamicVertexBuffer(int streamID, VertexFormat_t vertexFormat, bool bBuffered = true);
    IIndexBuffer *GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered = true);
    void BindVertexBuffer(int streamID, IVertexBuffer *pVertexBuffer, int nOffsetInBytes, int nFirstVertex,
                          int nVertexCount, VertexFormat_t fmt, int nRepetitions = 1);
    void BindIndexBuffer(IIndexBuffer *pIndexBuffer, int nOffsetInBytes);
    void Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount);
    // ------------ End ----------------------------
    void RenderPassWithVertexAndIndexBuffers(void);

    VertexFormat_t GetCurrentVertexFormat(void) const { return m_CurrentVertexFormat; }

    // Gets at the *actual* dynamic mesh
    IMesh *GetActualDynamicMesh(VertexFormat_t vertexFormat);
    IMesh *GetFlexMesh();

    // Computes vertex format from a list of ingredients
    VertexFormat_t ComputeVertexFormat(unsigned int flags, int numTexCoords, int *pTexCoordDimensions,
                                       int numBoneWeights, int userDataSize) const;

    // Use fat vertices (for tools)
    virtual void UseFatVertices(bool bUseFat);

    // Returns the number of vertices we can render using the dynamic mesh
    virtual void GetMaxToRender(IMesh *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices);
    virtual int GetMaxVerticesToRender(IMaterial *pMaterial);
    virtual int GetMaxIndicesToRender();

    // Returns a vertex buffer appropriate for the flags
    CVertexBufferVk *FindOrCreateVertexBuffer(int nDynamicBufferId, VertexFormat_t fmt);
    CIndexBufferVk *GetDynamicIndexBuffer();

    // Is the mesh dynamic?
    bool IsDynamicMesh(IMesh *pMesh) const;
    bool IsBufferedDynamicMesh(IMesh *pMesh) const;

    // Is the vertex buffer dynamic?
    bool IsDynamicVertexBuffer(IVertexBuffer *pVertexBuffer) const;

    // Is the index buffer dynamic?
    bool IsDynamicIndexBuffer(IIndexBuffer *pIndexBuffer) const;

    // Returns the vertex size
    int VertexFormatSize(VertexFormat_t vertexFormat) const { return CVertexBufferVk::VertexSize(); }

    // Computes the vertex buffer pointers
    void ComputeVertexDescription(unsigned char *pBuffer, VertexFormat_t vertexFormat, MeshDesc_t &desc) const;

    // Returns the number of buffers...
    int BufferCount() const { return 0; }

    CVertexBufferVk *GetVertexIDBuffer();

    IVertexBuffer *GetDynamicVertexBuffer(IMaterial *pMaterial, bool buffered = true);
    IIndexBuffer *GetDynamicIndexBuffer(IMaterial *pMaterial, bool buffered = true);
    virtual void MarkUnusedVertexFields(unsigned int nFlags, int nTexCoordCount, bool *pUnusedTexCoords);

    int UnusedVertexFields() const { return m_nUnusedVertexFields; }
    int UnusedTextureCoords() const { return m_nUnusedTextureCoords; }

  private:
    void SetVertexIDStreamState();
    void SetColorStreamState();
    void SetVertexStreamState(int nVertOffsetInBytes, int nVertexStride);
    void SetIndexStreamState(int firstVertexIdx);
    bool SetRenderState(int nVertexOffsetInBytes, int nFirstVertexIdx, VertexFormat_t vertexFormat, int nVertexStride);

    struct VertexBufferLookup_t
    {
        CVertexBufferVk *m_pBuffer;
        int m_VertexSize;
    };

    void CopyStaticMeshIndexBufferToTempMeshIndexBuffer(CTempMeshVk *pDstIndexMesh, CMeshVk *pSrcIndexMesh);

    // Cleans up the class
    void CleanUp();

    // Creates, destroys the vertexID buffer
    void CreateVertexIDBuffer();
    void DestroyVertexIDBuffer();

    // Fills a vertexID buffer
    void FillVertexIDBuffer(CVertexBufferVk *pVertexIDBuffer, int nCount);

    // The dynamic index buffer
    CIndexBufferVk *m_pDynamicIndexBuffer;

    // A static vertexID buffer
    CVertexBufferVk *m_pVertexIDBuffer;

    // The dynamic vertex buffers
    CUtlVector<VertexBufferLookup_t> m_DynamicVertexBuffers;

    // The buffered mesh
    CBufferedMeshVk m_BufferedMesh;

    // The current dynamic mesh
    CDynamicMeshVk m_DynamicMesh;
    CDynamicMeshVk m_DynamicFlexMesh;

    // The current dynamic vertex buffer
    CVertexBufferVk m_DynamicVertexBuffer;

    // The current dynamic index buffer
    CIndexBufferVk m_DynamicIndexBuffer;

    // The dynamic mesh temp version (for shaders that modify vertex data)
    // VK_TODO: do we need temp meshes?
    CTempMeshVk m_DynamicTempMesh;

    // Am I buffering or not?
    bool m_BufferedMode;

    // Using fat vertices?
    bool m_bUseFatVertices;

    CVertexBufferVk *m_pCurrentVertexBuffer;
    VertexFormat_t m_CurrentVertexFormat;
    int m_pVertexBufferOffset[MAX_VK_STREAMS];
    int m_pCurrentVertexStride[MAX_VK_STREAMS];
    int m_pFirstVertex[MAX_VK_STREAMS];
    int m_pVertexCount[MAX_VK_STREAMS];
    CIndexBufferVk *m_pCurrentIndexBuffer;
    int m_nIndexBufferOffset;
    MaterialPrimitiveType_t m_PrimitiveType;
    int m_nFirstIndex;
    int m_nNumIndices;

    unsigned int m_nUnusedVertexFields;
    unsigned int m_nUnusedTextureCoords;
};

//-----------------------------------------------------------------------------
// Tracks stream state and queued data
//-----------------------------------------------------------------------------
// VK_TODO: we shouldn't need states, can we clean this up?
// support for multiple streams isn't implemented either, MAX_VK_STREAMS wont do anything.
static CIndexBufferVk *g_pLastIndex = NULL;
static VkBuffer *g_pLastIndexBuffer = NULL;
static CVertexBufferVk *g_pLastVertex = NULL;
static VkBuffer *g_pLastVertexBuffer = NULL;
static int g_nLastVertOffsetInBytes = 0;
static int g_nLastVertStride = 0;
static int g_LastVertexIdx = -1;
static CMeshVk *g_pLastColorMesh = NULL;
static int g_nLastColorMeshVertOffsetInBytes = 0;
static bool g_bUsingVertexID = false;
static VertexFormat_t g_LastVertexFormat = 0;

//-----------------------------------------------------------------------------
// Helpers to count texture coordinates
//-----------------------------------------------------------------------------
static int NumTextureCoordinates(VertexFormat_t vertexFormat)
{
    int nTexCoordCount = 0;
    for (int i = 0; i < VERTEX_MAX_TEXTURE_COORDINATES; ++i)
    {
        if (TexCoordSize(i, vertexFormat) == 0)
            continue;
        ++nTexCoordCount;
    }
    return nTexCoordCount;
}

//-----------------------------------------------------------------------------
// Makes sure that the render state is always set next time
//-----------------------------------------------------------------------------
static void ResetMeshRenderState()
{
    g_pLastIndex = 0;
    g_pLastIndexBuffer = 0;
    g_pLastVertex = 0;
    g_nLastVertOffsetInBytes = 0;
    g_pLastColorMesh = 0;
    g_nLastColorMeshVertOffsetInBytes = 0;
    g_LastVertexIdx = -1;
    g_bUsingVertexID = false;
    g_LastVertexFormat = 0;
}

//-----------------------------------------------------------------------------
// Makes sure that the render state is always set next time
//-----------------------------------------------------------------------------
static void ResetIndexBufferRenderState()
{
    g_pLastIndex = 0;
    g_pLastIndexBuffer = 0;
    g_LastVertexIdx = -1;
}

extern CMeshMgrVk *g_pMeshMgr;
inline CMeshMgrVk *MeshMgr() { return g_pMeshMgr; }

#endif // MESHMGRVK_H