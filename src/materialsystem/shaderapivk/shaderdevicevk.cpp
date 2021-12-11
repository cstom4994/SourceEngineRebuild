#include "shaderdevicevk.h"
#include "shaderapivk.h"
#include "shadermanagervk.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
static CShaderDeviceVk g_ShaderDeviceVk;
CShaderDeviceVk *g_pShaderDevice = &g_ShaderDeviceVk;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderDeviceVk, IShaderDevice, SHADER_DEVICE_INTERFACE_VERSION, g_ShaderDeviceVk)

const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME};

CShaderDeviceVk::CShaderDeviceVk()
{
    m_PhysicalDevice = VK_NULL_HANDLE;
    m_Device = VK_NULL_HANDLE;
    m_CurrentViewport = -1;
    m_Viewports = std::vector<CViewportVk *>();
}

CShaderDeviceVk::~CShaderDeviceVk() {}

void CShaderDeviceVk::InitDevice(VkPhysicalDevice physicalDevice)
{
    m_PhysicalDevice = physicalDevice;

    uint32_t queueFamily;
    GetQueueFamily(physicalDevice, queueFamily);

    VkPhysicalDeviceFeatures features{};
    vkGetPhysicalDeviceFeatures(physicalDevice, &features);

    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(physicalDevice, &properties);

    // Get list of supported extensions
#ifdef DEBUG
    Msg("Supported device extensions:\n");
#endif
    std::vector<char *> supportedExtensions;
    uint32_t extCount = 0;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, nullptr);
    if (extCount > 0)
    {
        std::vector<VkExtensionProperties> extensions(extCount);
        if (vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
        {
            for (auto ext : extensions)
            {
#ifdef DEBUG
                Msg("  %s\n", ext.extensionName);
#endif
                supportedExtensions.push_back(ext.extensionName);
            }
        }
    }
    // VK_TODO: check if device extension are supported

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
    createInfo.enabledExtensionCount = deviceExtensions.size();
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    createInfo.pEnabledFeatures = &features;

    // Enable dynamic features
    VkPhysicalDeviceExtendedDynamicStateFeaturesEXT dynamicFeatures{};
    dynamicFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;
    dynamicFeatures.extendedDynamicState = true;
    createInfo.pNext = &dynamicFeatures;

    size_t minUboAlignment = properties.limits.minUniformBufferOffsetAlignment;
    m_DynamicUBOAlignment = sizeof(UniformBufferObject);
    if (minUboAlignment > 0)
    {
        m_DynamicUBOAlignment = (m_DynamicUBOAlignment + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }

    // Create logical device
    vkCheck(vkCreateDevice(physicalDevice, &createInfo, g_pAllocCallbacks, &m_Device), "failed to create device");

    // Get queue
    vkGetDeviceQueue(m_Device, queueFamily, 0, &m_GraphicsQueue);
    vkGetDeviceQueue(m_Device, queueFamily, 0, &m_PresentQueue);

    m_bInitialized = true;
}

CViewportVk *CShaderDeviceVk::GetCurrentViewport()
{
    if (m_CurrentViewport == -1)
    {
        return VK_NULL_HANDLE;
    }
    return m_Viewports[m_CurrentViewport];
}

void *CShaderDeviceVk::GetCurrentViewHandle()
{
    CViewportVk *viewport = GetCurrentViewport();
    if (viewport == VK_NULL_HANDLE)
    {
        return nullptr;
    }
    return viewport->GetViewHandle();
}

void CShaderDeviceVk::ReleaseResources() {}

void CShaderDeviceVk::ReacquireResources() {}

ImageFormat CShaderDeviceVk::GetBackBufferFormat() const
{
    Assert(m_CurrentViewport != -1);
    return m_Viewports[m_CurrentViewport]->GetBackBufferFormat();
}

void CShaderDeviceVk::GetBackBufferDimensions(int &width, int &height) const
{
    if (m_PhysicalDevice == nullptr)
    {
        width = 0;
        height = 0;
        return;
    }

    Assert(m_CurrentViewport != -1);
    m_Viewports[m_CurrentViewport]->GetBackBufferDimensions(width, height);
}

int CShaderDeviceVk::GetCurrentAdapter() const { return g_pShaderDeviceMgr->GetCurrentAdapter(); }

bool CShaderDeviceVk::IsUsingGraphics() const { return false; }

void CShaderDeviceVk::SpewDriverInfo() const { Warning("Vulkan\n"); }

int CShaderDeviceVk::StencilBufferBits() const { return 0; }

bool CShaderDeviceVk::IsAAEnabled() const { return false; }

void CShaderDeviceVk::Present()
{
    g_pShaderAPI->FlushBufferedPrimitives();

    CViewportVk *viewport = GetCurrentViewport();
    if (viewport)
    {
        viewport->Present();
    }

    MeshMgr()->DiscardVertexBuffers();
}

void CShaderDeviceVk::GetWindowSize(int &nWidth, int &nHeight) const
{
    Assert(m_CurrentViewport != -1);
    m_Viewports[m_CurrentViewport]->GetWindowSize(nWidth, nHeight);
}

void CShaderDeviceVk::SetHardwareGammaRamp(float fGamma, float fGammaTVRangeMin, float fGammaTVRangeMax, float fGammaTVExponent,
                                           bool bTVEnabled)
{
}

bool CShaderDeviceVk::AddView(void *hWnd)
{
    // Make sure no duplicate hwnds...
    if (FindView(hWnd) >= 0)
        return false;

    CViewportVk *viewport = new CViewportVk();
    m_Viewports.push_back(viewport);
    // if (m_CurrentViewport == -1)
    //{
    m_CurrentViewport = m_Viewports.size() - 1;
    //}
    viewport->InitDevice(hWnd);

    return true;
}

void CShaderDeviceVk::RemoveView(void *hWnd)
{
    // Get existing logical device for this viewport
    for (size_t i = 0; i < m_Viewports.size(); i++)
    {
        if (m_Viewports[i]->GetViewHandle() == hWnd)
        {
            // Remove
            m_Viewports[i]->ShutdownDevice();
            delete m_Viewports[i];
            m_Viewports.erase(m_Viewports.begin() + i);
            if (m_CurrentViewport >= i)
            {
                m_CurrentViewport--;
            }
            return;
        }
    }
}

int CShaderDeviceVk::FindView(void *hWnd)
{
    // Get existing logical device for this viewport
    for (size_t i = 0; i < m_Viewports.size(); i++)
    {
        if (m_Viewports[i]->GetViewHandle() == hWnd)
        {
            return i;
        }
    }

    return -1;
}

void CShaderDeviceVk::SetView(void *hWnd)
{
    // Engine will send nullptr here on game shutdown, etc.
    if (!hWnd)
    {
        m_CurrentViewport = -1;
        return;
    }

    // Switch view, add new one if necessary
    m_CurrentViewport = FindView(hWnd);
    if (m_CurrentViewport == -1)
    {
        AddView(hWnd);
    }
}

VkShaderModule CShaderDeviceVk::CreateShaderModule(const uint32_t *code, const size_t size)
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = size;
    createInfo.pCode = code;
    VkShaderModule shaderModule;
    vkCheck(vkCreateShaderModule(m_Device, &createInfo, g_pAllocCallbacks, &shaderModule), "failed to create shader module");
    return shaderModule;
}

IShaderBuffer *CShaderDeviceVk::CompileShader(const char *pProgram, size_t nBufLen, const char *pShaderVersion)
{
    return g_pShaderManager->CompileShader(pProgram, nBufLen, pShaderVersion);
}

VertexShaderHandle_t CShaderDeviceVk::CreateVertexShader(IShaderBuffer *pShaderBuffer)
{
    return g_pShaderManager->CreateVertexShader(pShaderBuffer);
}

void CShaderDeviceVk::DestroyVertexShader(VertexShaderHandle_t hShader) { g_pShaderManager->DestroyVertexShader(hShader); }

GeometryShaderHandle_t CShaderDeviceVk::CreateGeometryShader(IShaderBuffer *pShaderBuffer)
{
    Assert(0);
    return GEOMETRY_SHADER_HANDLE_INVALID;
}

void CShaderDeviceVk::DestroyGeometryShader(GeometryShaderHandle_t hShader) { Assert(hShader == GEOMETRY_SHADER_HANDLE_INVALID); }

PixelShaderHandle_t CShaderDeviceVk::CreatePixelShader(IShaderBuffer *pShaderBuffer)
{
    return g_pShaderManager->CreatePixelShader(pShaderBuffer);
}

void CShaderDeviceVk::DestroyPixelShader(PixelShaderHandle_t hShader) { g_pShaderManager->DestroyPixelShader(hShader); }

IMesh *CShaderDeviceVk::CreateStaticMesh(VertexFormat_t vertexFormat, const char *pTextureBudgetGroup, IMaterial *pMaterial)
{
    return g_pMeshMgr->CreateStaticMesh(vertexFormat, pTextureBudgetGroup, pMaterial);
}

void CShaderDeviceVk::DestroyStaticMesh(IMesh *pMesh) { g_pMeshMgr->DestroyStaticMesh(pMesh); }

IVertexBuffer *CShaderDeviceVk::CreateVertexBuffer(ShaderBufferType_t type, VertexFormat_t fmt, int nVertexCount, const char *pBudgetGroup)
{
    return CreateVertexBuffer(type, fmt, nVertexCount, pBudgetGroup, false);
}

IVertexBuffer *CShaderDeviceVk::CreateVertexBuffer(ShaderBufferType_t type, VertexFormat_t fmt, int nVertexCount, const char *pBudgetGroup,
                                                   bool destination)
{
    CVertexBufferVk *pVertexBufferVk = new CVertexBufferVk(type, fmt, nVertexCount, pBudgetGroup, destination);
    pVertexBufferVk->Allocate();
    return pVertexBufferVk;
}

void CShaderDeviceVk::DestroyVertexBuffer(IVertexBuffer *pVertexBuffer)
{
    if (pVertexBuffer)
    {
        delete pVertexBuffer;
    }
}

IIndexBuffer *CShaderDeviceVk::CreateIndexBuffer(ShaderBufferType_t type, MaterialIndexFormat_t fmt, int nIndexCount,
                                                 const char *pBudgetGroup)
{
    return CreateIndexBuffer(type, fmt, nIndexCount, pBudgetGroup, false);
}

IIndexBuffer *CShaderDeviceVk::CreateIndexBuffer(ShaderBufferType_t type, MaterialIndexFormat_t fmt, int nIndexCount,
                                                 const char *pBudgetGroup, bool destination)
{
    switch (type)
    {
    case SHADER_BUFFER_TYPE_STATIC:
    case SHADER_BUFFER_TYPE_DYNAMIC:
    {
        CIndexBufferVk *pIndexBufferVk = new CIndexBufferVk(type, fmt, nIndexCount, pBudgetGroup, destination);
        pIndexBufferVk->Allocate();
        return pIndexBufferVk;
    }
    case SHADER_BUFFER_TYPE_STATIC_TEMP:
    case SHADER_BUFFER_TYPE_DYNAMIC_TEMP:
        Assert(0);
        return NULL;
    default:
        Assert(0);
        return NULL;
    }
}

void CShaderDeviceVk::DestroyIndexBuffer(IIndexBuffer *pIndexBuffer)
{
    if (pIndexBuffer)
    {
        delete pIndexBuffer;
    }
}

IVertexBuffer *CShaderDeviceVk::GetDynamicVertexBuffer(int nStreamID, VertexFormat_t vertexFormat, bool bBuffered)
{
    return g_pMeshMgr->GetDynamicVertexBuffer(nStreamID, vertexFormat, bBuffered);
}

IIndexBuffer *CShaderDeviceVk::GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered)
{
    return g_pMeshMgr->GetDynamicIndexBuffer(fmt, bBuffered);
}

void CShaderDeviceVk::EnableNonInteractiveMode(MaterialNonInteractiveMode_t mode, ShaderNonInteractiveInfo_t *pInfo) {}

void CShaderDeviceVk::RefreshFrontBufferNonInteractive() {}

void CShaderDeviceVk::HandleThreadEvent(uint32 threadEvent) {}

char *CShaderDeviceVk::GetDisplayDeviceName() { return "(unspecified)"; }

void CShaderDeviceVk::ShutdownDevice()
{
    for (auto dev : m_Viewports)
    {
        dev->ShutdownDevice();
        delete dev;
    }

    m_Viewports.clear();
    m_CurrentViewport = -1;

    vkDestroyDevice(m_Device, g_pAllocCallbacks);
    m_Device = nullptr;

    m_bInitialized = false;
}

void CShaderDeviceVk::DrawMesh(CBaseMeshVk *pMesh) { GetCurrentViewport()->DrawMesh(pMesh); }
