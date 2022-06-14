//

#ifndef VERTEXBUFFERVK_H
#define VERTEXBUFFERVK_H

#ifdef _WIN32
#pragma once
#endif

#include "localvktypes.h"
#include "materialsystem/imesh.h"
#include "shaderapi/IShaderDevice.h"
#include "vertexvk.h"
#include "vprof.h"
#include "vulkanimpl.h"

//-----------------------------------------------------------------------------
// Important enumerations
//-----------------------------------------------------------------------------
enum
{
    VERTEX_BUFFER_SIZE = (1024 + 512) * 1024,
    MAX_QUAD_INDICES = 16384,
};

class CVertexBufferVk : public IVertexBuffer
{
    typedef IVertexBuffer BaseClass;

    // Methods of IVertexBuffer
  public:
    virtual int VertexCount() const;
    virtual VertexFormat_t GetVertexFormat() const;
    virtual bool IsDynamic() const;
    virtual void BeginCastBuffer(VertexFormat_t format);
    virtual void EndCastBuffer();
    virtual int GetRoomRemaining() const;
    virtual bool Lock(int nVertexCount, bool bAppend, VertexDesc_t &desc);
    virtual void Unlock(int nVertexCount, VertexDesc_t &desc);
    virtual void Spew(int nVertexCount, const VertexDesc_t &desc);
    virtual void ValidateData(int nVertexCount, const VertexDesc_t &desc);

    // constructor
    CVertexBufferVk(ShaderBufferType_t type, VertexFormat_t fmt, int vertexCount, const char *pBudgetGroupName,
                    bool destination);
    virtual ~CVertexBufferVk();

    // Allocates, deallocates the index buffer
    bool Allocate();
    void Free();

    // Returns the vertex size
    static int VertexSize() { return sizeof(Vertex); }

    // Only used by dynamic buffers, indicates the next lock should perform a discard.
    void Flush();

    // Returns the VkBuffer
    VkBuffer *GetVkBuffer();

    // Used to measure how much static buffer memory is touched each frame
    void HandlePerFrameTextureStats(int nFrame);

    // Returns the number of vertices we have enough room for
    int NumVerticesUntilFlush() const { return (m_nBufferSize - m_nVertexCount * VertexSize()) / VertexSize(); }

    bool HasEnoughRoom(int vertexCount) const { return vertexCount <= GetRoomRemaining(); };

    // used to alter the characteristics after creation
    // allows one dynamic vb to be shared for multiple formats
    void ChangeConfiguration(int vertexSize, int totalSize)
    {
        Assert(m_bIsDynamic && !m_bIsLocked && vertexSize);
        m_nVertexSize = vertexSize;
        m_nVertexCount = m_nBufferSize / vertexSize;
    }

    unsigned char *GetVertexMemory() { return (unsigned char *)m_pVertexMemory.data(); }

    VkDeviceSize GetBufferSize() { return m_nBufferSize; }

  protected:
    VkBuffer *m_pVertexBuffer;
    VertexFormat_t m_VertexFormat;
    VkDeviceMemory *m_pVertexBufferMemory;
    std::vector<Vertex> m_Vertices;
    std::vector<ModelVertexVk_t> m_pVertexMemory;
    int m_nVertexCount;
    int m_nVertexSize;
    VkDeviceSize m_nBufferSize;
    int m_nFirstUnwrittenOffset; // Used only for dynamic buffers, indicates where it's safe to write (nooverwrite)

    // Is it locked?
    bool m_bIsLocked : 1;
    bool m_bIsDynamic : 1;
    bool m_bFlush : 1; // Used only for dynamic buffers, indicates to discard the next time
    bool m_bDestination;

#ifdef VPROF_ENABLED
    int m_nVProfFrame;
    int *m_pFrameCounter;
    int *m_pGlobalCounter;
#endif

#ifdef _DEBUG
    static int s_nBufferCount;
#endif
};

#endif // VERTEXBUFFERVK_H