#include "vertexbuffervk.h"
#include "buffervkutil.h"
#include "shaderdevicevk.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// globals
//-----------------------------------------------------------------------------
#ifdef _DEBUG
int CVertexBufferVk::s_nBufferCount = 0;
#endif

//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
CVertexBufferVk::CVertexBufferVk(ShaderBufferType_t type, VertexFormat_t fmt, int vertexCount,
                                 const char *pBudgetGroupName,
                                 bool destination)
    : BaseClass()
{
    if (vertexCount == 0)
        vertexCount = 65535;
    // Assert(vertexCount != 0);

    m_VertexFormat = fmt;
    m_pVertexBuffer = NULL;
    // m_Vertices = vertices;
    m_nVertexCount = vertexCount;
    m_nBufferSize = vertexCount * VertexSize();
    m_nFirstUnwrittenOffset = 0;
    m_bIsLocked = false;
    m_bIsDynamic = (type == SHADER_BUFFER_TYPE_DYNAMIC) || (type == SHADER_BUFFER_TYPE_DYNAMIC_TEMP);
    m_bFlush = false;
    m_bDestination = destination;
    m_Vertices = std::vector<Vertex>();

#ifdef VPROF_ENABLED
    if (!m_bIsDynamic)
    {
        char name[256];
        Q_strcpy(name, "TexGroup_global_");
        Q_strcat(name, pBudgetGroupName, sizeof(name));
        m_pGlobalCounter = g_VProfCurrentProfile.FindOrCreateCounter(name, COUNTER_GROUP_TEXTURE_GLOBAL);

        Q_strcpy(name, "TexGroup_frame_");
        Q_strcat(name, pBudgetGroupName, sizeof(name));
        m_pFrameCounter = g_VProfCurrentProfile.FindOrCreateCounter(name, COUNTER_GROUP_TEXTURE_PER_FRAME);
    }
    else
    {
        m_pGlobalCounter =
            g_VProfCurrentProfile.FindOrCreateCounter("TexGroup_global_" TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER, COUNTER_GROUP_TEXTURE_GLOBAL);
        m_pFrameCounter = NULL;
    }
    m_nVProfFrame = -1;
#endif
}

CVertexBufferVk::~CVertexBufferVk() { Free(); }

//-----------------------------------------------------------------------------
// Creates, destroys the vertex buffer
//-----------------------------------------------------------------------------
bool CVertexBufferVk::Allocate()
{
    Assert(!m_pVertexBuffer);
    m_nFirstUnwrittenOffset = 0;

    m_pVertexBuffer = new VkBuffer();
    m_pVertexBufferMemory = new VkDeviceMemory();
    if (m_bDestination)
    {
        CreateBuffer(m_nBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *m_pVertexBuffer, *m_pVertexBufferMemory);
    }
    else
    {
        CreateBuffer(m_nBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, *m_pVertexBuffer, *m_pVertexBufferMemory);
    }

#ifdef _DEBUG
    ++s_nBufferCount;
#endif

    return true;
}

void CVertexBufferVk::Free()
{
    if (m_pVertexBuffer)
    {
#ifdef _DEBUG
        --s_nBufferCount;
#endif
        // Destroy buffer
        vkDestroyBuffer(g_pShaderDevice->GetVkDevice(), *m_pVertexBuffer, nullptr);
        m_pVertexBuffer = nullptr;

        // Free memory
        vkFreeMemory(g_pShaderDevice->GetVkDevice(), *m_pVertexBufferMemory, nullptr);
        m_pVertexBufferMemory = nullptr;
    }
    // m_pVertexMemory.clear();
    // m_Vertices.clear();
}

//-----------------------------------------------------------------------------
// Vertex buffer information
//-----------------------------------------------------------------------------
int CVertexBufferVk::VertexCount() const
{
    if (m_bIsDynamic)
    {
        return m_nFirstUnwrittenOffset;
    }
    return m_nVertexCount;
}

VertexFormat_t CVertexBufferVk::GetVertexFormat() const
{
    Assert(!m_bIsDynamic);
    return m_VertexFormat;
}

//-----------------------------------------------------------------------------
// Returns true if the buffer is dynamic
//-----------------------------------------------------------------------------
bool CVertexBufferVk::IsDynamic() const { return m_bIsDynamic; }

//-----------------------------------------------------------------------------
// Only used by dynamic buffers, indicates the next lock should perform a discard.
//-----------------------------------------------------------------------------
void CVertexBufferVk::Flush()
{
    // This strange-looking line makes a flush only occur if the buffer is dynamic.
    m_bFlush = m_bIsDynamic;
}

//-----------------------------------------------------------------------------
// Returns the VkBuffer
//-----------------------------------------------------------------------------
VkBuffer *CVertexBufferVk::GetVkBuffer() { return m_pVertexBuffer; }

//-----------------------------------------------------------------------------
// Casts a dynamic buffer to be a particular vertex type
//-----------------------------------------------------------------------------
void CVertexBufferVk::BeginCastBuffer(VertexFormat_t format)
{
    Assert(format != MATERIAL_INDEX_FORMAT_UNKNOWN);
    Assert(m_bIsDynamic && (m_VertexFormat == 0 || m_VertexFormat == format));
    if (!m_bIsDynamic)
        return;

    m_VertexFormat = format;
    int nVertexSize = VertexSize();
    m_nVertexCount = m_nBufferSize / nVertexSize;

    // snap current position up to the next position based on expected size
    // so append can safely guarantee nooverwrite regardless of a format growth or shrinkage
    if (!g_pShaderDeviceMgr->GetCurrentAdapterInfo().caps.m_bSupportsStreamOffset)
    {
        m_nFirstUnwrittenOffset += 1;
        if (m_nFirstUnwrittenOffset > m_nVertexCount)
        {
            m_nFirstUnwrittenOffset = m_nVertexCount;
        }
    }
}

void CVertexBufferVk::EndCastBuffer()
{
    Assert(m_bIsDynamic && m_VertexFormat != 0);
    if (!m_bIsDynamic)
        return;
    m_VertexFormat = 0;
    m_nVertexCount = 0;
}

//-----------------------------------------------------------------------------
// Returns the number of vertices we can still write into the buffer
//-----------------------------------------------------------------------------
int CVertexBufferVk::GetRoomRemaining() const { return m_nBufferSize / VertexSize() - m_nFirstUnwrittenOffset; }

//-----------------------------------------------------------------------------
// Locks/unlocks the vertex buffer mesh
//-----------------------------------------------------------------------------
bool CVertexBufferVk::Lock(int nMaxVertexCount, bool bAppend, VertexDesc_t &desc)
{
    Assert(!m_bIsLocked);

    if (bAppend)
    {
        Error("Not supported");
    }

    m_nFirstUnwrittenOffset = 0;
    m_pVertexMemory.resize(nMaxVertexCount);

    m_bIsLocked = true;
    return true;
}

void CVertexBufferVk::Unlock(int nWrittenVertexCount, VertexDesc_t &desc)
{
    // Don't assert here; this can be called multiple times by studiorender for example.
    if (!m_bIsLocked)
        return;

    if (nWrittenVertexCount > 0)
    {
        m_Vertices.resize(m_nFirstUnwrittenOffset + nWrittenVertexCount);

        // Create vertices
        for (int i = 0; i < nWrittenVertexCount; i++)
        {
            Vertex vert;
            vert.position = VertexPosition(desc, i);
            vert.normal = VertexNormal(desc, i);
            vert.color = VertexColor(desc, i);
            m_Vertices[i + m_nFirstUnwrittenOffset] = vert;
        }

        m_nFirstUnwrittenOffset += nWrittenVertexCount;

        VkDeviceSize bufferSize = m_Vertices.size() * VertexSize();
        if (bufferSize > m_nBufferSize)
        {
            Warning("Writing more vertices than reserved buffer size! This probably shouldn't happen.\n");
            Free();
            m_nVertexCount = m_Vertices.size();
            m_nBufferSize = bufferSize;
            Allocate();
        }

        // Copy vertex data to the buffer
        void *data;
        vkCheck(vkMapMemory(g_pShaderDevice->GetVkDevice(), *m_pVertexBufferMemory, 0, bufferSize, 0, &data),
                "failed to map vertex buffer memory!");
        memcpy(data, m_Vertices.data(), bufferSize);
        vkUnmapMemory(g_pShaderDevice->GetVkDevice(), *m_pVertexBufferMemory);
    }

    m_bIsLocked = false;
}

void CVertexBufferVk::Spew(int nVertexCount, const VertexDesc_t &desc)
{
    char pTempBuf[1024];
    Q_snprintf(pTempBuf, sizeof(pTempBuf), "\nVerts %d (First %d, Offset %d) :\n", nVertexCount, desc.m_nFirstVertex, desc.m_nOffset);
    Warning("%s", pTempBuf);

    Assert((desc.m_NumBoneWeights == 2) || (desc.m_NumBoneWeights == 0));

    int nLen = 0;
    int nBoneWeightCount = desc.m_NumBoneWeights;
    for (int i = 0; i < nVertexCount; ++i)
    {
        nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "[%4d] ", i + desc.m_nFirstVertex);
        if (desc.m_VertexSize_Position)
        {
            glm::vec3 pos = VertexPosition(desc, i);
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "P %8.2f %8.2f %8.2f ", pos[0], pos[1], pos[2]);
        }

        if (desc.m_VertexSize_Wrinkle)
        {
            float flWrinkle = VertexWrinkle(desc, i);
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "Wr %8.2f ", flWrinkle);
        }

        if (nBoneWeightCount)
        {
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "BW ");
            float *pWeight = VertexBoneWeight(desc, i);
            for (int j = 0; j < nBoneWeightCount; ++j)
            {
                nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "%1.2f ", pWeight[j]);
            }
        }
        if (desc.m_VertexSize_BoneMatrixIndex)
        {
            unsigned char *pIndex = VertexBoneIndex(desc, i);
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "BI %d %d %d %d ", (int)pIndex[0], (int)pIndex[1], (int)pIndex[2],
                               (int)pIndex[3]);
            Assert(pIndex[0] >= 0 && pIndex[0] < 16);
            Assert(pIndex[1] >= 0 && pIndex[1] < 16);
            Assert(pIndex[2] >= 0 && pIndex[2] < 16);
            Assert(pIndex[3] >= 0 && pIndex[3] < 16);
        }

        if (desc.m_VertexSize_Normal)
        {
            glm::vec3 &normal = VertexNormal(desc, i);
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "N %1.2f %1.2f %1.2f ", normal[0], normal[1], normal[2]);
        }

        if (desc.m_VertexSize_Color)
        {
            glm::vec<4, uint8_t> color = VertexColor(desc, i);
            nLen +=
                Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "C b %3d g %3d r %3d a %3d ", color[0], color[1], color[2], color[3]);
        }

        for (int j = 0; j < VERTEX_MAX_TEXTURE_COORDINATES; ++j)
        {
            if (desc.m_VertexSize_TexCoord[j])
            {
                glm::vec2 texcoord = VertexTexCoord(desc, i, j);
                nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "T%d %.2f %.2f ", j, texcoord[0], texcoord[1]);
            }
        }

        if (desc.m_VertexSize_TangentS)
        {
            glm::vec3 tangentS = VertexTangentS(desc, i);
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "S %1.2f %1.2f %1.2f ", tangentS[0], tangentS[1], tangentS[2]);
        }

        if (desc.m_VertexSize_TangentT)
        {
            glm::vec3 tangentT = VertexTangentT(desc, i);
            nLen += Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "T %1.2f %1.2f %1.2f ", tangentT[0], tangentT[1], tangentT[2]);
        }

        Q_snprintf(&pTempBuf[nLen], sizeof(pTempBuf) - nLen, "\n");
        Warning("%s", pTempBuf);
        nLen = 0;
    }
}

void CVertexBufferVk::ValidateData(int nVertexCount, const VertexDesc_t &desc)
{
#ifdef VALIDATE_DEBUG
    // VK_TODO: validate
#endif
}

//-----------------------------------------------------------------------------
// Used to measure how much static buffer memory is touched each frame
//-----------------------------------------------------------------------------
void CVertexBufferVk::HandlePerFrameTextureStats(int nFrame)
{
#ifdef VPROF_ENABLED
    if (m_nVProfFrame != nFrame && !m_bIsDynamic)
    {
        m_nVProfFrame = nFrame;
        m_pFrameCounter += m_nBufferSize;
    }
#endif
}