#include "indexbuffervk.h"
#include "buffervkutil.h"
#include "shaderdevicevk.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
#ifdef _DEBUG
int CIndexBufferVk::s_nBufferCount = 0;
#endif

void CIndexBufferVk::Spew(int nIndexCount, const IndexDesc_t &desc)
{
    char pTempBuf[512];
    int nLen = 0;
    pTempBuf[0] = '\0';
    char *pTemp = pTempBuf;
    Q_snprintf(pTempBuf, sizeof(pTempBuf), "\nIndices: %d (First %d, Offset %d)\n", nIndexCount, desc.m_nFirstIndex, desc.m_nOffset);
    Warning("%s", pTempBuf);
    for (int i = 0; i < nIndexCount; ++i)
    {
        nLen += Q_snprintf(pTemp, sizeof(pTempBuf) - nLen - 1, "%d ", (int)desc.m_pIndices[i]);
        pTemp = pTempBuf + nLen;
        if ((i & 0x0F) == 0x0F)
        {
            Q_snprintf(pTemp, sizeof(pTempBuf) - nLen - 1, "\n");
            Warning("%s", pTempBuf);
            pTempBuf[0] = '\0';
            nLen = 0;
            pTemp = pTempBuf;
        }
    }
    Q_snprintf(pTemp, sizeof(pTempBuf) - nLen - 1, "\n");
    Warning("%s", pTempBuf);
}

void CIndexBufferVk::ValidateData(int nIndexCount, const IndexDesc_t &desc){
#ifdef VALIDATE_DEBUG
// VK_TODO: validate
#endif
}

//-----------------------------------------------------------------------------
// Constructor, destructor
//-----------------------------------------------------------------------------
CIndexBufferVk::CIndexBufferVk(ShaderBufferType_t bufferType, MaterialIndexFormat_t fmt, int indexCount,
                               const char *pBudgetGroupName,
                               bool destination)
    : BaseClass()
{
    if (indexCount == 0)
        indexCount = 65535;
    // Assert(indexCount != 0);

    if (fmt == MATERIAL_INDEX_FORMAT_UNKNOWN)
    {
        fmt = MATERIAL_INDEX_FORMAT_16BIT;
    }

    m_pIndexBuffer = NULL;
    m_IndexFormat = fmt;
    m_nBufferSize = indexCount * IndexSize();
    m_nIndexCount = indexCount;
    m_nFirstUnwrittenOffset = 0;
    m_bIsLocked = false;
    m_bIsDynamic = IsDynamicBufferType(bufferType);
    m_bFlush = false;
    m_bDestination = destination;
    m_Indices = std::vector<uint16_t>();

#ifdef CHECK_INDICES
    m_pShadowIndices = NULL;
#endif

#ifdef VPROF_ENABLED
    m_nVProfFrame = -1;
#endif
}

CIndexBufferVk::~CIndexBufferVk() { Free(); }

//-----------------------------------------------------------------------------
// Returns the index size
//-----------------------------------------------------------------------------
int CIndexBufferVk::IndexSize() const
{
    // Assert( m_IndexFormat != MATERIAL_INDEX_FORMAT_UNKNOWN );
    // return ( m_IndexFormat == MATERIAL_INDEX_FORMAT_16BIT ) ? 2 : 4;
    return sizeof(uint16_t);
}

//-----------------------------------------------------------------------------
// Creates, destroys the index buffer
//-----------------------------------------------------------------------------
bool CIndexBufferVk::Allocate()
{
    Assert(!m_pIndexBuffer);
    m_nFirstUnwrittenOffset = 0;

    m_pIndexBuffer = new VkBuffer();
    m_pIndexBufferMemory = new VkDeviceMemory();
    if (m_bDestination)
    {
        CreateBuffer(m_nBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *m_pIndexBuffer, *m_pIndexBufferMemory);
    }
    else
    {
        CreateBuffer(m_nBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, *m_pIndexBuffer, *m_pIndexBufferMemory);
    }

    if (!m_bIsDynamic)
    {
        VPROF_INCREMENT_GROUP_COUNTER("TexGroup_global_" TEXTURE_GROUP_STATIC_INDEX_BUFFER, COUNTER_GROUP_TEXTURE_GLOBAL, m_nBufferSize);
    }
    else
    {
        VPROF_INCREMENT_GROUP_COUNTER("TexGroup_global_" TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER, COUNTER_GROUP_TEXTURE_GLOBAL, m_nBufferSize);
    }

#ifdef _DEBUG
    ++s_nBufferCount;
#endif

    return true;
}

void CIndexBufferVk::Free()
{
    if (m_pIndexBuffer)
    {
#ifdef _DEBUG
        --s_nBufferCount;
#endif

        // Destroy buffer
        vkDestroyBuffer(g_pShaderDevice->GetVkDevice(), *m_pIndexBuffer, nullptr);
        m_pIndexBuffer = nullptr;

        // Free memory
        vkFreeMemory(g_pShaderDevice->GetVkDevice(), *m_pIndexBufferMemory, nullptr);
        m_pIndexBufferMemory = nullptr;

        if (!m_bIsDynamic)
        {
            VPROF_INCREMENT_GROUP_COUNTER("TexGroup_global_" TEXTURE_GROUP_STATIC_INDEX_BUFFER, COUNTER_GROUP_TEXTURE_GLOBAL,
                                          -m_nBufferSize);
        }
        else
        {
            VPROF_INCREMENT_GROUP_COUNTER("TexGroup_global_" TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER, COUNTER_GROUP_TEXTURE_GLOBAL,
                                          -m_nBufferSize);
        }
    }
    // m_Indices.clear();
    // m_pIndices.clear();
}

//-----------------------------------------------------------------------------
// Index buffer information
//-----------------------------------------------------------------------------
int CIndexBufferVk::IndexCount() const
{
    if (m_bIsDynamic)
    {
        return m_nFirstUnwrittenOffset;
    }
    return m_nIndexCount;
}

MaterialIndexFormat_t CIndexBufferVk::IndexFormat() const
{
    Assert(!m_bIsDynamic);
    return m_IndexFormat;
}

//-----------------------------------------------------------------------------
// Returns true if the buffer is dynamic
//-----------------------------------------------------------------------------
bool CIndexBufferVk::IsDynamic() const { return m_bIsDynamic; }

//-----------------------------------------------------------------------------
// Only used by dynamic buffers, indicates the next lock should perform a discard.
//-----------------------------------------------------------------------------
void CIndexBufferVk::Flush()
{
    // This strange-looking line makes a flush only occur if the buffer is dynamic.
    m_bFlush = m_bIsDynamic;
}

//-----------------------------------------------------------------------------
// Returns the Vk buffer
//-----------------------------------------------------------------------------
VkBuffer *CIndexBufferVk::GetVkBuffer() { return m_pIndexBuffer; }

//-----------------------------------------------------------------------------
// Used to measure how much static buffer memory is touched each frame
//-----------------------------------------------------------------------------
void CIndexBufferVk::HandlePerFrameTextureStats(int nFrame)
{
#ifdef VPROF_ENABLED
    if (m_nVProfFrame != nFrame && !m_bIsDynamic)
    {
        m_nVProfFrame = nFrame;
        VPROF_INCREMENT_GROUP_COUNTER("TexGroup_frame_" TEXTURE_GROUP_STATIC_INDEX_BUFFER, COUNTER_GROUP_TEXTURE_PER_FRAME, m_nBufferSize);
    }
#endif
}

//-----------------------------------------------------------------------------
// Casts a dynamic buffer to be a particular index type
//-----------------------------------------------------------------------------
void CIndexBufferVk::BeginCastBuffer(MaterialIndexFormat_t format)
{
    // NOTE: This should have no effect under Dx9, since we can't recast index buffers.
    Assert(format != MATERIAL_INDEX_FORMAT_UNKNOWN);
    Assert(m_bIsDynamic && (m_IndexFormat == format));
}

void CIndexBufferVk::EndCastBuffer()
{
    // NOTE: This should have no effect under Dx9, since we can't recast index buffers.
}

int CIndexBufferVk::GetRoomRemaining() const { return m_nBufferSize / IndexSize() - m_nFirstUnwrittenOffset; }

//-----------------------------------------------------------------------------
// Locks/unlocks the index buffer
//-----------------------------------------------------------------------------
bool CIndexBufferVk::Lock(int nMaxIndexCount, bool bAppend, IndexDesc_t &desc)
{
    Assert(!m_bIsLocked);

    if (bAppend)
    {
        Error("Not implemented");
    }

    m_nFirstUnwrittenOffset = 0;

    m_pIndices.resize(nMaxIndexCount);

    desc.m_nFirstIndex = 0;
    desc.m_pIndices = &m_pIndices[0];
    desc.m_nIndexSize = 1;

    m_bIsLocked = true;
    return true;
}

void CIndexBufferVk::Unlock(int nWrittenIndexCount, IndexDesc_t &desc)
{
    // Don't assert here; this can be called multiple times by studiorender for example.
    if (!m_bIsLocked)
        return;

    if (nWrittenIndexCount > 0)
    {
        m_Indices.resize(nWrittenIndexCount + m_nFirstUnwrittenOffset);

        for (int i = 0; i < nWrittenIndexCount; i++)
        {
            m_Indices[i + m_nFirstUnwrittenOffset] = m_pIndices[i];
        }

        // VK_FIXME: index values start from weird values
        uint16_t lowest = std::numeric_limits<uint16_t>::max();
        for (size_t i = 0; i < m_Indices.size(); i++)
        {
            if (m_Indices[i] < lowest)
            {
                lowest = m_Indices[i];
            }
        }
        for (size_t i = 0; i < m_Indices.size(); i++)
        {
            m_Indices[i] -= lowest;
        }

        m_nFirstUnwrittenOffset += nWrittenIndexCount;

        VkDeviceSize bufferSize = m_Indices.size() * IndexSize();

        if (bufferSize > m_nBufferSize)
        {
            // VK_TODO: this gets called quite often, maybe create larger buffers to start with,
            // or increase buffer size by 2^x whenever we get here.
            Free();
            m_nIndexCount = m_Indices.size();
            m_nBufferSize = bufferSize;
            Allocate();
        }

        // Copy index data to the buffer
        void *data;
        vkCheck(vkMapMemory(g_pShaderDevice->GetVkDevice(), *m_pIndexBufferMemory, 0, bufferSize, 0, &data),
                "failed to map index buffer memory!");
        memcpy(data, m_Indices.data(), (size_t)bufferSize);
        vkUnmapMemory(g_pShaderDevice->GetVkDevice(), *m_pIndexBufferMemory);
    }

    m_bIsLocked = false;
}