//

#ifndef MESHVK_H
#define MESHVK_H

#ifdef _WIN32
#pragma once
#endif

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include "localvktypes.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imesh.h"

class CIndexBufferVk;
class CVertexBufferVk;

// glm doesn't have built in function for vec3 * mat4 sadly
static glm::vec3 TransformVec3(glm::vec3 in, glm::mat4 projection)
{
    glm::vec4 temp = glm::vec4(in.x, in.y, in.z, 1.0);
    temp = temp * projection;
    return glm::vec3(temp.x, temp.y, temp.z) / temp.w;
}

//-----------------------------------------------------------------------------
//
// Backward compat mesh code; will go away soon
//
//-----------------------------------------------------------------------------
abstract_class CBaseMeshVk : public IMesh
{
  public:
    // constructor, destructor
    CBaseMeshVk();
    virtual ~CBaseMeshVk();

    // FIXME: Make this work! Unsupported methods of IIndexBuffer + IVertexBuffer
    virtual bool Lock(int nMaxIndexCount, bool bAppend, IndexDesc_t &desc)
    {
        Assert(0);
        return false;
    }
    virtual void Unlock(int nWrittenIndexCount, IndexDesc_t &desc) { Assert(0); }
    virtual void ModifyBegin(bool bReadOnly, int nFirstIndex, int nIndexCount, IndexDesc_t &desc) { Assert(0); }
    virtual void ModifyEnd(IndexDesc_t & desc) { Assert(0); }
    virtual void Spew(int nIndexCount, const IndexDesc_t &desc) { Assert(0); }
    virtual void ValidateData(int nIndexCount, const IndexDesc_t &desc) { Assert(0); }
    virtual bool Lock(int nVertexCount, bool bAppend, VertexDesc_t &desc)
    {
        Assert(0);
        return false;
    }
    virtual void Unlock(int nVertexCount, VertexDesc_t &desc) { Assert(0); }
    virtual void Spew(int nVertexCount, const VertexDesc_t &desc) { Assert(0); }
    virtual void ValidateData(int nVertexCount, const VertexDesc_t &desc) { Assert(0); }

    // Locks mesh for modifying
    void ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc);
    void ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc);
    void ModifyEnd(MeshDesc_t & desc);

    // Sets/gets the vertex format
    virtual void SetVertexFormat(VertexFormat_t format);
    virtual VertexFormat_t GetVertexFormat() const;

    // Sets/gets the morph format
    virtual void SetMorphFormat(MorphFormat_t format);
    virtual MorphFormat_t GetMorphFormat() const;
    // Am I using morph data?
    virtual bool IsUsingMorphData() const;
    bool IsUsingVertexID() const { return false /*g_pShaderAPI->GetBoundMaterial()->IsUsingVertexID()*/; }

    // Sets the material
    virtual void SetMaterial(IMaterial * pMaterial);

    // returns the # of vertices (static meshes only)
    int VertexCount() const { return 0; }

    void SetColorMesh(IMesh * pColorMesh, int nVertexOffsetInBytes) { Assert(0); }

    void SetFlexMesh(IMesh * pMesh, int nVertexOffsetInBytes) { Assert(pMesh == NULL && nVertexOffsetInBytes == 0); }

    void DisableFlexMesh() { Assert(0); }

    void MarkAsDrawn() {}

    bool HasColorMesh() const { return false; }
    bool HasFlexMesh() const { return false; }

    // Draws the mesh
    void DrawMesh();

    // Begins a pass
    void BeginPass();

	// Draws a single pass of the mesh
	virtual void RenderPass() = 0;

    // Spews the mesh data
    virtual void Spew(int nVertexCount, int nIndexCount, const MeshDesc_t &desc);

    // Call this in debug mode to make sure our data is good.
    virtual void ValidateData(int nVertexCount, int nIndexCount, const MeshDesc_t &desc);

    void Draw(CPrimList * pLists, int nLists);

    // Copy verts and/or indices to a mesh builder. This only works for temp meshes!
    virtual void CopyToMeshBuilder(int iStartVert, // Which vertices to copy.
                                   int nVerts,
                                   int iStartIndex, // Which indices to copy.
                                   int nIndices,
                                   int indexOffset, // This is added to each index.
                                   CMeshBuilder &builder);

    // returns the primitive type
    virtual MaterialPrimitiveType_t GetPrimitiveType() const = 0;

    // Returns the number of indices in a mesh..
    virtual int IndexCount() const = 0;

    // FIXME: Make this work!
    virtual MaterialIndexFormat_t IndexFormat() const { return MATERIAL_INDEX_FORMAT_16BIT; }

    // NOTE: For dynamic index buffers only!
    // Casts the memory of the dynamic index buffer to the appropriate type
    virtual void BeginCastBuffer(MaterialIndexFormat_t format) { Assert(0); }
    virtual void BeginCastBuffer(VertexFormat_t format) { Assert(0); }
    virtual void EndCastBuffer() { Assert(0); }
    virtual int GetRoomRemaining() const
    {
        Assert(0);
        return 0;
    }

    // returns a static vertex buffer...
    virtual CVertexBufferVk *GetVertexBuffer() { return 0; }
    virtual CIndexBufferVk *GetIndexBuffer() { return 0; }

    // Do I need to reset the vertex format?
    virtual bool NeedsVertexFormatReset(VertexFormat_t fmt) const;

    // Do I have enough room?
    virtual bool HasEnoughRoom(int nVertexCount, int nIndexCount) const;

    // Operation to do pre-lock
    virtual void PreLock() {}

    bool m_bMeshLocked;

    // Fix abstract class errors
    unsigned ComputeMemoryUsed() { return 0; }

  protected:
    bool DebugTrace() const;

    // The vertex format we're using...
    VertexFormat_t m_VertexFormat;

    // The morph format we're using
    MorphFormat_t m_MorphFormat;

#ifdef _DEBUG
    IMaterial *m_pMaterial;
    bool m_IsDrawing;
#endif
};

class CMeshVk : public CBaseMeshVk
{
  public:
    // constructor
    CMeshVk(const char *pTextureGroupName = "CMeshVk");
    virtual ~CMeshVk();

    // Locks/unlocks the mesh
    void LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);
    void UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);

    // Locks mesh for modifying
    void ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc);
    void ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc);
    void ModifyEnd(MeshDesc_t &desc);

    // returns the # of vertices (static meshes only)
    int VertexCount() const;

    // returns the # of indices
    virtual int IndexCount() const;

    // Sets up the vertex and index buffers
    void UseIndexBuffer(CIndexBufferVk *pBuffer);
    void UseVertexBuffer(CVertexBufferVk *pBuffer);

    // returns a static vertex buffer...
    CVertexBufferVk *GetVertexBuffer() { return m_pVertexBuffer; }
    CIndexBufferVk *GetIndexBuffer() { return m_pIndexBuffer; }

    void SetColorMesh(IMesh *pColorMesh, int nVertexOffsetInBytes);
    void SetFlexMesh(IMesh *pMesh, int nVertexOffsetInBytes);
    void DisableFlexMesh();

    bool HasColorMesh() const;
    bool HasFlexMesh() const;

    // Draws the mesh
    void Draw(int nFirstIndex, int nIndexCount);
    void Draw(CPrimList *pLists, int nLists);
    void DrawInternal(CPrimList *pLists, int nLists);

    // Draws a single pass
    void RenderPass();

    // Sets the primitive type
    void SetPrimitiveType(MaterialPrimitiveType_t type);
    MaterialPrimitiveType_t GetPrimitiveType() const;

    bool IsDynamic() const { return false; }

  protected:
    // Sets the render state.
    bool SetRenderState(int nVertexOffsetInBytes, int nFirstVertexIdx, VertexFormat_t vertexFormat = VERTEX_FORMAT_UNKNOWN);

    // Is the vertex format valid?
    bool IsValidVertexFormat(VertexFormat_t vertexFormat = VERTEX_FORMAT_UNKNOWN);

    // Locks/ unlocks the vertex buffer
    bool Lock(int nVertexCount, bool bAppend, VertexDesc_t &desc);
    void Unlock(int nVertexCount, VertexDesc_t &desc);

    // Locks/unlocks the index buffer
    // Pass in nFirstIndex=-1 to lock wherever the index buffer is. Pass in a value
    // >= 0 to specify where to lock.
    int Lock(bool bReadOnly, int nFirstIndex, int nIndexCount, IndexDesc_t &pIndices);
    void Unlock(int nIndexCount, IndexDesc_t &desc);

    // computes how many primitives we've got
    int NumPrimitives(int nVertexCount, int nIndexCount) const;

    // Debugging output...
    void SpewMaterialVerts();

    // Stream source setting methods
    void SetVertexIDStreamState();
    void SetColorStreamState();
    void SetVertexStreamState(int nVertOffsetInBytes);
    void SetIndexStreamState(int firstVertexIdx);

    void CheckIndices(CPrimList *pPrim, int numPrimitives);

    // The vertex and index buffers
    CVertexBufferVk *m_pVertexBuffer;
    CIndexBufferVk *m_pIndexBuffer;

    // The current color mesh (to be bound to stream 1)
    // The vertex offset allows use of a global, shared color mesh VB
    CMeshVk *m_pColorMesh;
    int m_nColorMeshVertOffsetInBytes;

    CVertexBufferVk *m_pFlexVertexBuffer;

    bool m_bHasFlexVerts;
    int m_nFlexVertOffsetInBytes;
    int m_flexVertCount;

    // Primitive type
    MaterialPrimitiveType_t m_Type;

    // Primitive mode
    VkPrimitiveTopology m_Mode;

    // Number of primitives
    uint16_t m_NumVertices;
    uint16_t m_NumIndices;

    // Is it locked?
    bool m_IsVBLocked;
    bool m_IsIBLocked;

    // Used in rendering sub-parts of the mesh
    static CPrimList *s_pPrims;
    static int s_nPrims;
    static unsigned int s_FirstVertex; // Gets reset during CMeshVk::DrawInternal
    static unsigned int s_NumVertices;
    int m_FirstIndex;

#if defined(CHECK_INDICES)
    void *m_LockIndexBuffer;
    int m_LockIndexBufferSize;
#endif
    const char *m_pTextureGroupName;

    friend class CMeshMgrVk;
};

//-----------------------------------------------------------------------------
// A little extra stuff for the dynamic version
//-----------------------------------------------------------------------------
class CDynamicMeshVk : public CMeshVk
{
  public:
    // constructor, destructor
    CDynamicMeshVk();
    virtual ~CDynamicMeshVk();

    // Initializes the dynamic mesh
    void Init(int nBufferId);

    // Sets the vertex format
    virtual void SetVertexFormat(VertexFormat_t format);

    // Resets the state in case of a task switch
    void Reset();

    // Do I have enough room in the buffer?
    bool HasEnoughRoom(int nVertexCount, int nIndexCount);

    // returns the # of indices
    int IndexCount() const;

    // Locks the mesh
    void LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);

    // Unlocks the mesh
    void UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);

    // Override vertex + index buffer
    void OverrideVertexBuffer(CVertexBufferVk *pStaticVertexBuffer);
    void OverrideIndexBuffer(CIndexBufferVk *pStaticIndexBuffer);

    // Do I need to reset the vertex format?
    bool NeedsVertexFormatReset(VertexFormat_t fmt) const;

    // Draws it
    void Draw(int nFirstIndex, int nIndexCount);
    void MarkAsDrawn() { m_HasDrawn = true; }
    // Simply draws what's been buffered up immediately, without state change
    void DrawSinglePassImmediately();

    // Operation to do pre-lock
    void PreLock();

    bool IsDynamic() const { return true; }

  private:
    // Resets buffering state
    void ResetVertexAndIndexCounts();

    // Buffer Id
    int m_nBufferId;

    // total queued vertices
    int m_TotalVertices;
    int m_TotalIndices;

    // the first vertex and index since the last draw
    int m_nFirstVertex;
    int m_FirstIndex;

    // Have we drawn since the last lock?
    bool m_HasDrawn;

    // Any overrides?
    bool m_VertexOverride;
    bool m_IndexOverride;
};

//-----------------------------------------------------------------------------
// A mesh that stores temporary vertex data in the correct format (for modification)
//-----------------------------------------------------------------------------
class CTempMeshVk : public CBaseMeshVk
{
  public:
    // constructor, destructor
    CTempMeshVk(bool isDynamic);
    virtual ~CTempMeshVk();

    // Sets the material
    virtual void SetVertexFormat(VertexFormat_t format);

    // Locks/unlocks the mesh
    void LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);
    void UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);

    // Locks mesh for modifying
    virtual void ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc);
    virtual void ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t &desc);
    virtual void ModifyEnd(MeshDesc_t &desc);

    // Number of indices + vertices
    int VertexCount() const;
    virtual int IndexCount() const;
    virtual bool IsDynamic() const;

    // Sets the primitive type
    void SetPrimitiveType(MaterialPrimitiveType_t type);
    MaterialPrimitiveType_t GetPrimitiveType() const;

    // Begins a pass
    void BeginPass();

    // Draws a single pass
    void RenderPass();

    // Draws the entire beast
    void Draw(int nFirstIndex, int nIndexCount);

    virtual void CopyToMeshBuilder(int iStartVert, // Which vertices to copy.
                                   int nVerts,
                                   int iStartIndex, // Which indices to copy.
                                   int nIndices,
                                   int indexOffset, // This is added to each index.
                                   CMeshBuilder &builder);

  private:
    // Selection mode
    void TestSelection();
    void ClipTriangle(glm::vec3 **ppVert, float zNear, glm::mat4 &proj);

    CDynamicMeshVk *GetDynamicMesh();

    CUtlVector<unsigned char, CUtlMemoryAligned<unsigned char, 32>> m_VertexData;
    CUtlVector<uint16_t> m_IndexData;

    uint16_t m_VertexSize;
    MaterialPrimitiveType_t m_Type;
    int m_LockedVerts;
    int m_LockedIndices;
    bool m_IsDynamic;

    // Used in rendering sub-parts of the mesh
    static unsigned int s_NumIndices;
    static unsigned int s_FirstIndex;

#ifdef _DEBUG
    bool m_Locked;
    bool m_InPass;
#endif
};

//-----------------------------------------------------------------------------
// This is a version that buffers up vertex data so we can blast through it later
//-----------------------------------------------------------------------------
class CBufferedMeshVk : public CBaseMeshVk
{
  public:
    // constructor, destructor
    CBufferedMeshVk();
    virtual ~CBufferedMeshVk();

    // checks to see if it was rendered..
    void ResetRendered();
    bool WasNotRendered() const;

    // Sets the mesh we're really going to draw into
    void SetMesh(IMesh *pMesh);
    const IMesh *GetMesh() const { return m_pMesh; }

    // Spews the mesh data
    virtual void Spew(int nVertexCount, int nIndexCount, const MeshDesc_t &spewDesc);

    // Sets the vertex format
    virtual void SetVertexFormat(VertexFormat_t format);
    virtual VertexFormat_t GetVertexFormat() const;

    // Sets the morph format
    virtual void SetMorphFormat(MorphFormat_t format);

    // Sets the material
    void SetMaterial(IMaterial *pMaterial);

    // returns the number of indices (should never be called!)
    virtual int IndexCount() const
    {
        Assert(0);
        return 0;
    }
    virtual MaterialIndexFormat_t IndexFormat() const
    {
        Assert(0);
        return MATERIAL_INDEX_FORMAT_16BIT;
    }
    virtual bool IsDynamic() const
    {
        Assert(0);
        return true;
    }
    virtual void BeginCastBuffer(MaterialIndexFormat_t format) { Assert(0); }
    virtual void EndCastBuffer() { Assert(0); }
    virtual int GetRoomRemaining() const
    {
        Assert(0);
        return 0;
    }

    // Locks the mesh
    void LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);
    void UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t &desc);

    // Sets the primitive type
    void SetPrimitiveType(MaterialPrimitiveType_t type);
    MaterialPrimitiveType_t GetPrimitiveType() const;

    void ValidateData(int nVertexCount, int nIndexCount, const MeshDesc_t &spewDesc);

    // Draws it
    void Draw(int nFirstIndex, int nIndexCount);

    // Renders a pass
    void RenderPass();

    // Flushes queued data
    void Flush();

    void SetFlexMesh(IMesh *pMesh, int nVertexOffsetInBytes);

  private:
    // The actual mesh we need to render....
    CBaseMeshVk *m_pMesh;

    // The index of the last vertex (for tristrip fixup)
    uint16_t m_LastIndex;

    // Extra padding indices for tristrips
    uint16_t m_ExtraIndices;

    // Am I currently flushing?
    bool m_IsFlushing;

    // has the dynamic mesh been rendered?
    bool m_WasRendered;

    // Do I need to flush?
    bool m_FlushNeeded;

#ifdef DEBUG_BUFFERED_MESHES
    // for debugging only
    bool m_BufferedStateSet;
    BufferedState_t m_BufferedState;
#endif
};

//-----------------------------------------------------------------------------
// Utility method for VertexDesc_t (don't want to expose it in public, in imesh.h)
//-----------------------------------------------------------------------------
inline void ComputeVertexDesc(unsigned char *pBuffer, VertexFormat_t vertexFormat, VertexDesc_t &desc)
{
    int i;
    int *pVertexSizesToSet[64];
    int nVertexSizesToSet = 0;
    static ALIGN32 ModelVertexDX8_t temp[4];
    float *dummyData = (float *)&temp; // should be larger than any CMeshBuilder command can set.

    // Determine which vertex compression type this format specifies (affects element sizes/decls):
    VertexCompressionType_t compression = CompressionType(vertexFormat);
    desc.m_CompressionType = compression;

    // We use fvf instead of flags here because we may pad out the fvf
    // vertex structure to optimize performance
    int offset = 0;
    // NOTE: At the moment, we assume that if you specify wrinkle, you also specify position
    Assert(((vertexFormat & VERTEX_WRINKLE) == 0) || ((vertexFormat & VERTEX_POSITION) != 0));
    if (vertexFormat & VERTEX_POSITION)
    {
        // UNDONE: compress position+wrinkle to SHORT4N, and roll the scale into the transform matrices
        desc.m_pPosition = reinterpret_cast<float *>(pBuffer);
        offset += GetVertexElementSize(VERTEX_ELEMENT_POSITION, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_Position;

        if (vertexFormat & VERTEX_WRINKLE)
        {
            desc.m_pWrinkle = reinterpret_cast<float *>(pBuffer + offset);
            offset += GetVertexElementSize(VERTEX_ELEMENT_WRINKLE, compression);
            pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_Wrinkle;
        }
        else
        {
            desc.m_pWrinkle = dummyData;
            desc.m_VertexSize_Wrinkle = 0;
        }
    }
    else
    {
        desc.m_pPosition = dummyData;
        desc.m_VertexSize_Position = 0;
        desc.m_pWrinkle = dummyData;
        desc.m_VertexSize_Wrinkle = 0;
    }

    // Bone weights/matrix indices
    desc.m_NumBoneWeights = NumBoneWeights(vertexFormat);

    Assert((desc.m_NumBoneWeights == 2) || (desc.m_NumBoneWeights == 0));

    // We assume that if you have any indices/weights, you have exactly two of them
    Assert(((desc.m_NumBoneWeights == 2) && ((vertexFormat & VERTEX_BONE_INDEX) != 0)) ||
           ((desc.m_NumBoneWeights == 0) && ((vertexFormat & VERTEX_BONE_INDEX) == 0)));

    if ((vertexFormat & VERTEX_BONE_INDEX) != 0)
    {
        if (desc.m_NumBoneWeights > 0)
        {
            Assert(desc.m_NumBoneWeights == 2);

            // Always exactly two weights
            desc.m_pBoneWeight = reinterpret_cast<float *>(pBuffer + offset);
            offset += GetVertexElementSize(VERTEX_ELEMENT_BONEWEIGHTS2, compression);
            pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_BoneWeight;
        }
        else
        {
            desc.m_pBoneWeight = dummyData;
            desc.m_VertexSize_BoneWeight = 0;
        }

        desc.m_pBoneMatrixIndex = pBuffer + offset;
        offset += GetVertexElementSize(VERTEX_ELEMENT_BONEINDEX, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_BoneMatrixIndex;
    }
    else
    {
        desc.m_pBoneWeight = dummyData;
        desc.m_VertexSize_BoneWeight = 0;

        desc.m_pBoneMatrixIndex = (unsigned char *)dummyData;
        desc.m_VertexSize_BoneMatrixIndex = 0;
    }

    if (vertexFormat & VERTEX_NORMAL)
    {
        desc.m_pNormal = reinterpret_cast<float *>(pBuffer + offset);
        // See PackNormal_[SHORT2|UBYTE4|HEND3N] in mathlib.h for the compression algorithm
        offset += GetVertexElementSize(VERTEX_ELEMENT_NORMAL, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_Normal;
    }
    else
    {
        desc.m_pNormal = dummyData;
        desc.m_VertexSize_Normal = 0;
    }

    if (vertexFormat & VERTEX_COLOR)
    {
        desc.m_pColor = pBuffer + offset;
        offset += GetVertexElementSize(VERTEX_ELEMENT_COLOR, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_Color;
    }
    else
    {
        desc.m_pColor = (unsigned char *)dummyData;
        desc.m_VertexSize_Color = 0;
    }

    if (vertexFormat & VERTEX_SPECULAR)
    {
        desc.m_pSpecular = pBuffer + offset;
        offset += GetVertexElementSize(VERTEX_ELEMENT_SPECULAR, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_Specular;
    }
    else
    {
        desc.m_pSpecular = (unsigned char *)dummyData;
        desc.m_VertexSize_Specular = 0;
    }

    // Set up texture coordinates
    for (i = 0; i < VERTEX_MAX_TEXTURE_COORDINATES; ++i)
    {
        // FIXME: compress texcoords to SHORT2N/SHORT4N, with a scale rolled into the texture transform
        VertexElement_t texCoordElements[4] = {VERTEX_ELEMENT_TEXCOORD1D_0, VERTEX_ELEMENT_TEXCOORD2D_0, VERTEX_ELEMENT_TEXCOORD3D_0,
                                               VERTEX_ELEMENT_TEXCOORD4D_0};
        int nSize = TexCoordSize(i, vertexFormat);
        if (nSize != 0)
        {
            desc.m_pTexCoord[i] = reinterpret_cast<float *>(pBuffer + offset);
            VertexElement_t texCoordElement = (VertexElement_t)(texCoordElements[nSize - 1] + i);
            offset += GetVertexElementSize(texCoordElement, compression);
            pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_TexCoord[i];
        }
        else
        {
            desc.m_pTexCoord[i] = dummyData;
            desc.m_VertexSize_TexCoord[i] = 0;
        }
    }

    // Binormal + tangent...
    // Note we have to put these at the end so the vertex is FVF + stuff at end
    if (vertexFormat & VERTEX_TANGENT_S)
    {
        // UNDONE: use normal compression here (use mem_dumpvballocs to see if this uses much memory)
        desc.m_pTangentS = reinterpret_cast<float *>(pBuffer + offset);
        offset += GetVertexElementSize(VERTEX_ELEMENT_TANGENT_S, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_TangentS;
    }
    else
    {
        desc.m_pTangentS = dummyData;
        desc.m_VertexSize_TangentS = 0;
    }

    if (vertexFormat & VERTEX_TANGENT_T)
    {
        // UNDONE: use normal compression here (use mem_dumpvballocs to see if this uses much memory)
        desc.m_pTangentT = reinterpret_cast<float *>(pBuffer + offset);
        offset += GetVertexElementSize(VERTEX_ELEMENT_TANGENT_T, compression);
        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_TangentT;
    }
    else
    {
        desc.m_pTangentT = dummyData;
        desc.m_VertexSize_TangentT = 0;
    }

    // User data..
    int userDataSize = UserDataSize(vertexFormat);
    if (userDataSize > 0)
    {
        desc.m_pUserData = reinterpret_cast<float *>(pBuffer + offset);
        VertexElement_t userDataElement = (VertexElement_t)(VERTEX_ELEMENT_USERDATA1 + (userDataSize - 1));
        // See PackNormal_[SHORT2|UBYTE4|HEND3N] in mathlib.h for the compression algorithm
        offset += GetVertexElementSize(userDataElement, compression);

        pVertexSizesToSet[nVertexSizesToSet++] = &desc.m_VertexSize_UserData;
    }
    else
    {
        desc.m_pUserData = dummyData;
        desc.m_VertexSize_UserData = 0;
    }

    // We always use vertex sizes which are half-cache aligned (16 bytes)
    // x360 compressed vertexes are not compatible with forced alignments
    bool bCacheAlign = (vertexFormat & VERTEX_FORMAT_USE_EXACT_FORMAT) == 0;
    if (bCacheAlign && (offset > 16))
    {
        offset = (offset + 0xF) & (~0xF);
    }
    desc.m_ActualVertexSize = offset;

    // HACK HACK:
    // Avoid division by 0 errors if this gets called with VERTEX_FORMAT_UNKNOWN
    if (desc.m_ActualVertexSize == 0)
    {
        desc.m_ActualVertexSize = 1;
    }

    // Now set the m_VertexSize for all the members that were actually valid.
    Assert(nVertexSizesToSet < sizeof(pVertexSizesToSet) / sizeof(pVertexSizesToSet[0]));
    for (int iElement = 0; iElement < nVertexSizesToSet; iElement++)
    {
        *pVertexSizesToSet[iElement] = offset;
    }
}

//-----------------------------------------------------------------------------
// Helpers with VertexDesc_t...
//-----------------------------------------------------------------------------
// FIXME: add compression-agnostic read-accessors (which decompress and return by value, checking
// desc.m_CompressionType)
inline glm::vec3 VertexPosition(VertexDesc_t const &desc, int vert)
{
    return *(glm::vec3 *)((unsigned char *)desc.m_pPosition + vert * desc.m_VertexSize_Position);
}

inline float VertexWrinkle(VertexDesc_t const &desc, int vert)
{
    return *(float *)((unsigned char *)desc.m_pWrinkle + vert * desc.m_VertexSize_Wrinkle);
}

inline float *VertexBoneWeight(VertexDesc_t const &desc, int vert)
{
    Assert(desc.m_CompressionType == VERTEX_COMPRESSION_NONE);
    return (float *)((unsigned char *)desc.m_pBoneWeight + vert * desc.m_VertexSize_BoneWeight);
}

inline unsigned char *VertexBoneIndex(VertexDesc_t const &desc, int vert)
{
    return (desc.m_pBoneMatrixIndex + vert * desc.m_VertexSize_BoneMatrixIndex);
}

inline glm::vec3 VertexNormal(VertexDesc_t const &desc, int vert)
{
    Assert(desc.m_CompressionType == VERTEX_COMPRESSION_NONE);
    return *(glm::vec3 *)((unsigned char *)desc.m_pNormal + vert * desc.m_VertexSize_Normal);
}

inline glm::vec<4, uint8_t> VertexColor(VertexDesc_t const &desc, int vert)
{
    return *(glm::vec<4, uint8_t> *)(desc.m_pColor + vert * desc.m_VertexSize_Color);
}

inline glm::vec2 VertexTexCoord(VertexDesc_t const &desc, int vert, int stage)
{
    return *(glm::vec2 *)((unsigned char *)desc.m_pTexCoord[stage] + vert * desc.m_VertexSize_TexCoord[stage]);
}

inline glm::vec3 VertexTangentS(VertexDesc_t const &desc, int vert)
{
    return *(glm::vec3 *)((unsigned char *)desc.m_pTangentS + vert * desc.m_VertexSize_TangentS);
}

inline glm::vec3 VertexTangentT(VertexDesc_t const &desc, int vert)
{
    return *(glm::vec3 *)((unsigned char *)desc.m_pTangentT + vert * desc.m_VertexSize_TangentT);
}

#endif // MESHVK_H