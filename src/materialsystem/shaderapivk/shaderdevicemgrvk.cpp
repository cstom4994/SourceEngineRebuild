#include "shaderdevicemgrvk.h"
#include <tier2/tier2.h>
#include "shaderapi/ishaderutil.h"
#include "shaderapivk.h"
#include "shaderapivk_global.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
IShaderUtil *g_pShaderUtil; // The main shader utility interface
static CShaderDeviceMgrVk g_ShaderDeviceMgrVk;
CShaderDeviceMgrVk *g_pShaderDeviceMgr = &g_ShaderDeviceMgrVk;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CShaderDeviceMgrVk, IShaderDeviceMgr, SHADER_DEVICE_MGR_INTERFACE_VERSION, g_ShaderDeviceMgrVk);

//-----------------------------------------------------------------------------
// FIXME: Hack related to setting command-line values for convars. Remove!!!
//-----------------------------------------------------------------------------
class CShaderAPIConVarAccessor : public IConCommandBaseAccessor
{
  public:
    virtual bool RegisterConCommandBase(ConCommandBase *pCommand)
    {
        // Link to engine's list instead
        g_pCVar->RegisterConCommand(pCommand);

        char const *pValue = g_pCVar->GetCommandLineValue(pCommand->GetName());
        if (pValue && !pCommand->IsCommand())
        {
            ((ConVar *)pCommand)->SetValue(pValue);
        }
        return true;
    }
};

static void InitShaderAPICVars()
{
    static CShaderAPIConVarAccessor g_ConVarAccessor;
    if (g_pCVar)
    {
        ConVar_Register(0, &g_ConVarAccessor);
    }
}

//-----------------------------------------------------------------------------
// Factory used to get at internal interfaces (used by shaderapi + shader dlls)
//-----------------------------------------------------------------------------
static CreateInterfaceFn s_TempFactory;
void *ShaderDeviceFactory(const char *pName, int *pReturnCode)
{
    if (pReturnCode)
    {
        *pReturnCode = IFACE_OK;
    }

    void *pInterface = s_TempFactory(pName, pReturnCode);
    if (pInterface)
        return pInterface;

    pInterface = Sys_GetFactoryThis()(pName, pReturnCode);
    if (pInterface)
        return pInterface;

    if (pReturnCode)
    {
        *pReturnCode = IFACE_FAILED;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// Helper for getting a pointer to vkCreateDebugUtilsMessengerEXT function
//-----------------------------------------------------------------------------
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

//-----------------------------------------------------------------------------
// Helper for getting a pointer to vkDestroyDebugUtilsMessengerEXT function
//-----------------------------------------------------------------------------
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

//-----------------------------------------------------------------------------
// Factory to return from SetMode
//-----------------------------------------------------------------------------
void *CShaderDeviceMgrVk::ShaderInterfaceFactory(const char *pInterfaceName, int *pReturnCode)
{
    if (pReturnCode)
    {
        *pReturnCode = IFACE_OK;
    }
    if (!Q_stricmp(pInterfaceName, SHADER_DEVICE_INTERFACE_VERSION))
        return static_cast<IShaderDevice *>(g_pShaderDevice);
    if (!Q_stricmp(pInterfaceName, SHADERAPI_INTERFACE_VERSION))
        return static_cast<IShaderAPI *>(g_pShaderAPI);
    if (!Q_stricmp(pInterfaceName, SHADERSHADOW_INTERFACE_VERSION))
        return static_cast<IShaderShadow *>(g_pShaderShadow);

    if (pReturnCode)
    {
        *pReturnCode = IFACE_FAILED;
    }
    return NULL;
}

//-----------------------------------------------------------------------------
// CShaderDeviceMgrVk implemention
//-----------------------------------------------------------------------------

CShaderDeviceMgrVk::CShaderDeviceMgrVk()
{

    m_hInstance = VK_NULL_HANDLE;
    m_hDebugMessenger = VK_NULL_HANDLE;
    m_nCurAdapter = NULL;
}

CShaderDeviceMgrVk::~CShaderDeviceMgrVk() {}

bool CShaderDeviceMgrVk::Connect(CreateInterfaceFn factory)
{
    s_TempFactory = factory;

    // Connection/convar registration
    CreateInterfaceFn actualFactory = ShaderDeviceFactory;
    ConnectTier1Libraries(&actualFactory, 1);
    InitShaderAPICVars();
    ConnectTier2Libraries(&actualFactory, 1);
    g_pShaderUtil = static_cast<IShaderUtil *>(ShaderDeviceFactory(SHADER_UTIL_INTERFACE_VERSION, nullptr));
    g_pShaderDeviceMgr = this;

    s_TempFactory = nullptr;

    if (!g_pShaderUtil || !g_pFullFileSystem || !g_pShaderDeviceMgr || !g_pMaterialSystem)
    {
        Warning("ShaderAPIVk was unable to access the required interfaces!\n");
        return false;
    }

    // NOTE! : Overbright is 1.0 so that Hammer will work properly with the white bumped and unbumped lightmaps.
    MathLib_Init(2.2f, 2.2f, 0.0f, 2.0f);

    // Initialize Vulkan
    CreateVkInstance();
    return true;
}

void CShaderDeviceMgrVk::Disconnect() { CleanupVulkan(); }

void *CShaderDeviceMgrVk::QueryInterface(const char *pInterfaceName)
{
    if (!Q_stricmp(pInterfaceName, SHADER_DEVICE_MGR_INTERFACE_VERSION))
        return this;
    return nullptr;
}

InitReturnVal_t CShaderDeviceMgrVk::Init()
{
    InitAdapterInfo();

    return INIT_OK;
}

void CShaderDeviceMgrVk::Shutdown()
{
    g_pShaderAPI->OnDeviceShutdown();

    if (g_pShaderDevice)
        g_pShaderDevice->ShutdownDevice();
}

int CShaderDeviceMgrVk::GetAdapterCount() const { return m_Adapters.Count(); }

void CShaderDeviceMgrVk::GetAdapterInfo(int nAdapter, MaterialAdapterInfo_t &info) const
{
    // index out of range checks are unnecessary :p never should happen
    info = m_Adapters[nAdapter].matdata;
}

bool CShaderDeviceMgrVk::GetRecommendedConfigurationInfo(int nAdapter, int nDXLevel, KeyValues *pConfiguration) { return true; }

int CShaderDeviceMgrVk::GetModeCount(int nAdapter) const { return 1; }

void CShaderDeviceMgrVk::GetModeInfo(ShaderDisplayMode_t *pInfo, int nAdapter, int nMode) const
{
    *pInfo = m_Adapters[nAdapter].shaderMode;
}

void CShaderDeviceMgrVk::GetCurrentModeInfo(ShaderDisplayMode_t *pInfo, int nAdapter) const { *pInfo = m_Adapters[nAdapter].shaderMode; }

bool CShaderDeviceMgrVk::SetAdapter(int nAdapter, int nFlags)
{
    m_nCurAdapter = nAdapter;
    return true;
}

CreateInterfaceFn CShaderDeviceMgrVk::SetMode(void *hWnd, int nAdapter, const ShaderDeviceInfo_t &mode)
{
    if (g_pShaderDevice->IsInitialized())
    {
        g_pShaderDevice->ShutdownDevice();
    }

    g_pShaderDevice->InitDevice(m_Adapters[nAdapter].device);
    g_pShaderDevice->SetView(hWnd);

    g_pHardwareConfig->SetupHardwareCaps(mode, GetHardwareCaps(m_Adapters[nAdapter]));

    m_Mode = mode;

    g_pShaderAPI->OnDeviceInit();

    return ShaderInterfaceFactory;
}

void CShaderDeviceMgrVk::AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func) {}

void CShaderDeviceMgrVk::RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func) {}

void CShaderDeviceMgrVk::CreateVkInstance()
{
    // Get enabled extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // Populate list
    std::vector<VkExtensionProperties> fextensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, fextensions.data());

#ifdef DEBUG
    Msg("Enabled vulkan extensions:\n");
#endif
    std::vector<const char *> extensions;
    for (auto &extension : fextensions)
    {
        extensions.push_back(extension.extensionName);
#ifdef DEBUG
        Msg("  %s\n", extension.extensionName);
#endif
    }

#ifdef DEBUG
    // Check validation layers
    if (!CheckValidationLayerSupport())
    {
        Error("validation layers requested, but not available!");
    }

    // Add message callback for validation layers
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    Msg("  %s\n", VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    // Set app info
    VkApplicationInfo appInfo = {
        VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr,           "shaderapivulkan", VK_MAKE_VERSION(0, 0, 1), "Source Engine",
        VK_MAKE_VERSION(1, 0, 0),           VK_API_VERSION_1_2};

    // Set instance create info
    VkInstanceCreateInfo instanceCreateInfo = {
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &appInfo, 0, nullptr, extensions.size(), extensions.data()};

#ifdef DEBUG
    // Set validation layers
    instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();

    // Create a temporary debug messenger before creating instance
    // so we can catch errors in vkCreateInstance.
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    PopulateDebugMessengerCreateInfo(debugCreateInfo);
    instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
#endif

    // Create instance
    vkCheck(vkCreateInstance(&instanceCreateInfo, g_pAllocCallbacks, &m_hInstance), "failed to create vulkan instance");

    // Create DynamicLoader for vulkan extensions
    vk::DynamicLoader dl;
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
    VULKAN_HPP_DEFAULT_DISPATCHER.init((vk::Instance)m_hInstance);

#if DEBUG
    SetupDebugMessenger();
#endif
}

void CShaderDeviceMgrVk::CleanupVulkan()
{
    // VK_TODO

    // Detroy Frame Buffers
    // Destroy Pipeline Cache
    // Destroy Render Pass
    // Destroy Render Targets
    // Destroy Swap Chain
    // Destroy Command Buffer & fence
    // Destroy Command Pool
    // Destroy Query Pools
    // Destroy Semaphores
    // Destroy Debug Callback

    // Destroy Logical Device
    if (g_pShaderDevice)
        g_pShaderDevice->ShutdownDevice();

#if DEBUG
    // Destroy debug messenger
    DestroyDebugUtilsMessengerEXT(m_hInstance, m_hDebugMessenger, nullptr);
#endif

    // Destroy the Instance
    vkDestroyInstance(m_hInstance, g_pAllocCallbacks);
}

VkPhysicalDevice CShaderDeviceMgrVk::GetAdapter(int nIndex) const
{
    if (nIndex == -1)
        return m_Adapters[m_nCurAdapter].device;

    return m_Adapters[nIndex].device;
}

// Get physical devices
void CShaderDeviceMgrVk::InitAdapterInfo()
{
    m_Adapters.RemoveAll();

    uint32_t count = 0;
    vkCheck(vkEnumeratePhysicalDevices(m_hInstance, &count, nullptr), "failed to enumerate devices");
    std::vector<VkPhysicalDevice> devices(count);
    vkCheck(vkEnumeratePhysicalDevices(m_hInstance, &count, devices.data()), "failed to enumerate devices");

    if (devices.size() == 0)
    {
        Error("failed to find GPUs with vulkan support!");
    }

    m_Adapters.SetSize(devices.size());

    CUtlVector<VkFormatProperties> formatProperties;

    for (uint32_t i = 0; i < devices.size(); i++)
    {
        auto &adapter = m_Adapters[i];
        memset(&adapter, 0, sizeof(MyVkAdapterInfo));

        vkGetPhysicalDeviceProperties(devices[i], &adapter.props);
        auto &properties = adapter.props;

        adapter.device = devices[i];
        adapter.matdata.m_DeviceID = properties.deviceID;
        adapter.matdata.m_nDriverVersionHigh = properties.driverVersion >> 16;
        adapter.matdata.m_nDriverVersionLow = properties.driverVersion & 0xFFFF;
        // CShaderSystem has some minimum dxlevel checks, make sure we don't hit those
        adapter.matdata.m_nDXSupportLevel = adapter.matdata.m_nMaxDXSupportLevel = 100;
        adapter.matdata.m_VendorID = properties.vendorID;
        strcpy(adapter.matdata.m_pDriverName, "(not retrieved)");
        adapter.matdata.m_SubSysID = 0;

        adapter.shaderMode.m_nWidth = adapter.props.limits.maxFramebufferWidth;
        adapter.shaderMode.m_nHeight = adapter.props.limits.maxFramebufferHeight;
        adapter.shaderMode.m_Format = ImageFormat::IMAGE_FORMAT_UNKNOWN;
        adapter.shaderMode.m_nRefreshRateNumerator = 1;
        adapter.shaderMode.m_nRefreshRateDenominator = 0;
        adapter.shaderMode.m_nVersion = 1;
    }
}

uint32_t CShaderDeviceMgrVk::FindMemoryType(int adapter, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(GetAdapter(adapter), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    Error("failed to find suitable memory type!");
}

bool CShaderDeviceMgrVk::CheckValidationLayerSupport()
{
    // Get available layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Check that validation layers we want exist
    for (const char *layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto &layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

// VK_TODO: move this somewhere else?
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData)
{
    Warning("validation layer: %s\n", pCallbackData->pMessage);
    return VK_FALSE;
}

void CShaderDeviceMgrVk::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = DebugCallback;
    createInfo.pUserData = nullptr;
}

void CShaderDeviceMgrVk::SetupDebugMessenger()
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    PopulateDebugMessengerCreateInfo(createInfo);

    vkCheck(CreateDebugUtilsMessengerEXT(m_hInstance, &createInfo, nullptr, &m_hDebugMessenger), "failed to create debug messenger");
}

void CShaderDeviceMgrVk::ReadHardwareCaps(HardwareCaps_t &caps)
{
    // VK_TODO
}

VkInstance CShaderDeviceMgrVk::GetInstance() { return m_hInstance; }

HardwareCaps_t CShaderDeviceMgrVk::GetHardwareCaps(MyVkAdapterInfo adapterInfo)
{
    HardwareCaps_t caps{};

    // VK_TODO: read caps for real
    caps.m_VendorID = adapterInfo.matdata.m_VendorID;
    caps.m_DeviceID = adapterInfo.matdata.m_DeviceID;
    caps.m_SubSysID = adapterInfo.matdata.m_SubSysID;
    caps.m_Revision = adapterInfo.matdata.m_Revision;
    caps.m_NumSamplers = 16;
    caps.m_NumTextureStages = 0;
    caps.m_HasSetDeviceGammaRamp = true;
    caps.m_bSoftwareVertexProcessing = false;
    caps.m_SupportsVertexShaders = true;
    caps.m_SupportsVertexShaders_2_0 = false;
    caps.m_SupportsPixelShaders = true;
    caps.m_SupportsPixelShaders_1_4 = false;
    caps.m_SupportsPixelShaders_2_0 = false;
    caps.m_SupportsPixelShaders_2_b = false;
    caps.m_SupportsShaderModel_3_0 = false;
    caps.m_SupportsCompressedTextures = COMPRESSED_TEXTURES_OFF;
    caps.m_SupportsCompressedVertices = VERTEX_COMPRESSION_NONE;
    caps.m_bSupportsAnisotropicFiltering = true;
    caps.m_bSupportsMagAnisotropicFiltering = true;
    caps.m_bSupportsVertexTextures = true;
    caps.m_nMaxAnisotropy = 16;
    caps.m_MaxTextureWidth = adapterInfo.props.limits.maxImageDimension2D;
    caps.m_MaxTextureHeight = adapterInfo.props.limits.maxImageDimension2D;
    caps.m_MaxTextureDepth = adapterInfo.props.limits.maxImageDimension3D;
    caps.m_MaxTextureAspectRatio = 1024;
    caps.m_MaxPrimitiveCount = 65536;
    caps.m_ZBiasAndSlopeScaledDepthBiasSupported = true;
    caps.m_SupportsMipmapping = true;
    caps.m_SupportsOverbright = true;
    caps.m_SupportsCubeMaps = true;
    caps.m_NumPixelShaderConstants = 1024;
    caps.m_NumVertexShaderConstants = 1024;
    caps.m_TextureMemorySize = 2048;
    caps.m_MaxNumLights = 4;
    caps.m_SupportsHardwareLighting = false;
    caps.m_MaxBlendMatrices = 0;
    caps.m_MaxBlendMatrixIndices = 0;
    caps.m_MaxVertexShaderBlendMatrices = 53;
    caps.m_SupportsMipmappedCubemaps = true;
    caps.m_SupportsNonPow2Textures = true;
    caps.m_nDXSupportLevel = 100;
    caps.m_PreferDynamicTextures = false;
    caps.m_HasProjectedBumpEnv = true;
    caps.m_MaxUserClipPlanes = 6;
    caps.m_HDRType = HDR_TYPE_FLOAT;
    caps.m_SupportsSRGB = true;
    caps.m_bSupportsSpheremapping = true;
    caps.m_UseFastClipping = false;
    caps.m_pShaderDLL[0] = 0;
    caps.m_bNeedsATICentroidHack = false;
    caps.m_bColorOnSecondStream = true;
    caps.m_bSupportsStreamOffset = true;
    caps.m_nMaxDXSupportLevel = 100;
    caps.m_bFogColorSpecifiedInLinearSpace = true;
    caps.m_nVertexTextureCount = 16;
    caps.m_nMaxVertexTextureDimension = adapterInfo.props.limits.maxImageDimension2D;
    caps.m_bSupportsAlphaToCoverage = false;
    caps.m_bSupportsShadowDepthTextures = true;
    caps.m_bSupportsFetch4 = false;
    caps.m_bSupportsNormalMapCompression = false;
    caps.m_bSupportsBorderColor = true;
    caps.m_ShadowDepthTextureFormat = IMAGE_FORMAT_UNKNOWN;
    caps.m_nMaxViewports = 1;
    caps.m_flMinGammaControlPoint = 0.0f;
    caps.m_flMaxGammaControlPoint = 0.0f;
    caps.m_nGammaControlPointCount = 0;

    return caps;
}
