#pragma once

#include <vector>
#include "materialsystem/imesh.h"
#include "shaderapi/IShaderDevice.h"
#include "vprof.h"
#include "vulkanimpl.h"

class CIndexBufferVk : public IIndexBuffer
{
    typedef IIndexBuffer BaseClass;

    // Methods of IIndexBuffer
  public:
    virtual int IndexCount() const;
    virtual MaterialIndexFormat_t IndexFormat() const;
    virtual int GetRoomRemaining() const;
    virtual bool Lock(int nIndexCount, bool bAppend, IndexDesc_t &desc);
    virtual void Unlock(int nIndexCount, IndexDesc_t &desc);
    virtual void BeginCastBuffer(MaterialIndexFormat_t format);
    virtual void EndCastBuffer();
    virtual bool IsDynamic() const;
    virtual void ModifyBegin(bool bReadOnly, int nFirstIndex, int nIndexCount, IndexDesc_t &desc) { Assert(0); }
    virtual void ModifyEnd(IndexDesc_t &desc) { Assert(0); }
    virtual void Spew(int nIndexCount, const IndexDesc_t &desc);
    virtual void ValidateData(int nIndexCount, const IndexDesc_t &desc);

  public:
    // constructor
    CIndexBufferVk(ShaderBufferType_t bufferType, MaterialIndexFormat_t fmt, int indexCount, const char *pBudgetGroupName,
                   bool destination);
    virtual ~CIndexBufferVk();

    // Allocates, deallocates the index buffer
    bool Allocate();
    void Free();

    // Returns the index size
    int IndexSize() const;

    // Only used by dynamic buffers, indicates the next lock should perform a discard.
    void Flush();

    // Returns the VkBuffer
    VkBuffer *GetVkBuffer();

    // Used to measure how much static buffer memory is touched each frame
    void HandlePerFrameTextureStats(int nFrame);

    bool HasEnoughRoom(int indexCount) const { return indexCount <= GetRoomRemaining(); }

    uint16_t* GetIndexMemory() { return m_Indices.data(); }

    VkDeviceSize GetBufferSize() { return m_nBufferSize; }

  private:
    VkBuffer *m_pIndexBuffer;
    VkDeviceMemory *m_pIndexBufferMemory;
    std::vector<uint16_t> m_Indices;
    MaterialIndexFormat_t m_IndexFormat;
    std::vector<uint16_t> m_pIndices;
    int m_nIndexCount;
    VkDeviceSize m_nBufferSize;
    int m_nFirstUnwrittenOffset;

    // Is it locked?
    bool m_bIsLocked : 1;
    bool m_bIsDynamic : 1;
    bool m_bFlush : 1; // Used only for dynamic buffers, indicates to discard the next time
    bool m_bDestination;

#ifdef CHECK_INDICES
    unsigned char *m_pShadowIndices;
    void *m_pLockIndexBuffer;
    int m_nLockIndexBufferSize;
    int m_nLockIndexOffset;
#endif

#ifdef VPROF_ENABLED
    int m_nVProfFrame;
#endif

#ifdef _DEBUG
    static int s_nBufferCount;
#endif
};