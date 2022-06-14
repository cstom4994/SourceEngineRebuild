//

#ifndef SHADERDEVICEMGRVK_H
#define SHADERDEVICEMGRVK_H

#ifdef _WIN32
#pragma once
#endif

#include "hardwareconfig.h"
#include "shaderapi/IShaderDevice.h"
#include "shaderdevicevk.h"
#include <vulkan/vulkan.hpp>

struct MyVkAdapterInfo
{
    MaterialAdapterInfo_t matdata;
    VkPhysicalDeviceProperties props;
    HardwareCaps_t caps;
    VkPhysicalDevice device;
    ShaderDisplayMode_t shaderMode;
};

class CShaderDeviceMgrVk : public IShaderDeviceMgr
{
  public:
    CShaderDeviceMgrVk();
    ~CShaderDeviceMgrVk();

#pragma region IAppSystem
    // Here's where the app systems get to learn about each other
    virtual bool Connect(CreateInterfaceFn factory) override;
    virtual void Disconnect() override;

    // Here's where systems can access other interfaces implemented by this object
    // Returns NULL if it doesn't implement the requested interface
    virtual void *QueryInterface(const char *pInterfaceName) override;

    // Init, shutdown
    virtual InitReturnVal_t Init() override;
    virtual void Shutdown() override;
#pragma endregion

#pragma region IShaderDeviceMgr
    // Gets the number of adapters...
    virtual int GetAdapterCount() const override;

    // Returns info about each adapter
    virtual void GetAdapterInfo(int nAdapter, MaterialAdapterInfo_t &info) const override;

    MyVkAdapterInfo GetCurrentAdapterInfo() { return m_Adapters[m_nCurAdapter]; }

    int GetCurrentAdapter() { return m_nCurAdapter; }

    // Gets recommended congifuration for a particular adapter at a particular dx level
    virtual bool GetRecommendedConfigurationInfo(int nAdapter, int nDXLevel, KeyValues *pConfiguration) override;

    // Returns the number of modes
    virtual int GetModeCount(int nAdapter) const override;

    // Returns mode information..
    virtual void GetModeInfo(ShaderDisplayMode_t *pInfo, int nAdapter, int nMode) const override;

    // Returns the current mode info for the requested adapter
    virtual void GetCurrentModeInfo(ShaderDisplayMode_t *pInfo, int nAdapter) const override;

    // Initialization, shutdown
    virtual bool SetAdapter(int nAdapter, int nFlags) override;

    // Sets the mode
    // Use the returned factory to get at an IShaderDevice and an IShaderRender
    // and any other interfaces we decide to create.
    // A returned factory of NULL indicates the mode was not set properly.
    virtual CreateInterfaceFn SetMode(void *hWnd, int nAdapter, const ShaderDeviceInfo_t &mode) override;

    // Installs a callback to get called
    virtual void AddModeChangeCallback(ShaderModeChangeCallbackFunc_t func) override;
    virtual void RemoveModeChangeCallback(ShaderModeChangeCallbackFunc_t func) override;

    // Factory to return from SetMode
    static void *ShaderInterfaceFactory(const char *pInterfaceName, int *pReturnCode);
#pragma endregion

    void CreateVkInstance();

    void CleanupVulkan();

    VkPhysicalDevice GetAdapter(int nIndex = -1) const;

    void InitAdapterInfo();

    uint32_t FindMemoryType(int adapter, uint32_t typeFilter, VkMemoryPropertyFlags properties);

    bool CheckValidationLayerSupport();

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    void SetupDebugMessenger();

    void ReadHardwareCaps(HardwareCaps_t &caps);

    VkInstance GetInstance();

    HardwareCaps_t GetHardwareCaps(MyVkAdapterInfo adapterInfo);

  private:
    int m_nCurAdapter;

    ShaderDeviceInfo_t m_Mode;
    VkInstance m_hInstance;
    VkDebugUtilsMessengerEXT m_hDebugMessenger;
    CUtlVector<MyVkAdapterInfo> m_Adapters;
};

extern CShaderDeviceMgrVk *g_pShaderDeviceMgr;

inline VkInstance vkinstance() { return g_pShaderDeviceMgr->GetInstance(); }

static void GetQueueFamily(VkPhysicalDevice device, uint32_t &queueFamily)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    // Find the highest family with VK_QUEUE_GRAPHICS_BIT support
    int i = 0;
    for (const auto &family : queueFamilies)
    {
        if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            queueFamily = i;
        i++;
    }
}

#endif // SHADERDEVICEMGRVK_H