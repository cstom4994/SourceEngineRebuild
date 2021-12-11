//

#ifndef VIEWPORTVK_H
#define VIEWPORTVK_H

#ifdef _WIN32
#pragma once
#endif

#include "indexbuffervk.h"
#include "meshvk.h"
#include "vertexbuffervk.h"

struct SwapchainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class CViewportVk
{
    ImageFormat _backBufferFormat;
    int _backBufferSize[2];

    struct MeshOffset
    {
        int vertexCount;
        int indexCount;
        int firstVertex;
        int firstIndex;
        VkPrimitiveTopology topology;
        UniformBufferObject ubo;
    };

  public:
    CViewportVk();
    ~CViewportVk();

    SwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice device);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    void InitDevice(void *hWnd);
    void CleanupSwapchain();
    void RecreateSwapchain();
    void CreateSwapchain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateDescriptorSetlayout();
    void CreateDescriptorSets();
    void CreateDescriptorPool();
    void CreateGraphicsPipeline();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateUniformBuffers();
    void CreateCommandBuffers();
    void Present();
    void CreateSyncObjects();
    void GetWindowSize(int &nWidth, int &nHeight);
    void ShutdownDevice();
    void CreateVkSurface();
    void DestroyVkSurface();
    VkSurfaceKHR GetSurface();

    ImageFormat GetBackBufferFormat();
    void GetBackBufferDimensions(int &width, int &height);

    void GetMatrices(VMatrix *view, VMatrix *proj, VMatrix *model);
    UniformBufferObject GetUniformBufferObject();
    void UpdateUniformBuffer(uint32_t currentImage);

    // Update command buffer with all meshes that want to be drawn
    void UpdateCommandBuffer(uint32_t currentImage);

    void DrawMesh(CBaseMeshVk *pMesh);

    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size);

    void SetClearColor(VkClearValue color) { m_ClearColor = color; }

    void *GetViewHandle() { return m_ViewHWnd; }

    bool IsResizing() { return m_bIsResizing; }

  private:
    VkSurfaceKHR m_hSurface;

    VkSwapchainKHR m_Swapchain;
    std::vector<VkImage> m_SwapchainImages;
    VkFormat m_SwapchainImageFormat;
    std::vector<VkImageView> m_SwapchainImageViews;
    VkExtent2D m_SwapchainExtent;

    VkShaderModule m_VertShaderModule;
    VkShaderModule m_FragShaderModule;

    VkRenderPass m_RenderPass;
    VkDescriptorSetLayout m_DescriptorSetLayout;
    VkDescriptorPool m_DescriptorPool;
    std::vector<VkDescriptorSet> m_DescriptorSets;
    VkPipelineLayout m_PipelineLayout;
    VkPipeline m_GraphicsPipeline;

    std::vector<VkFramebuffer> m_SwapchainFramebuffers;
    std::vector<VkBuffer> m_UniformBuffers;
    std::vector<VkDeviceMemory> m_UniformBuffersMemory;

    VkCommandPool m_CommandPool;
    std::vector<VkCommandBuffer> m_CommandBuffers;

    std::vector<VkSemaphore> m_ImageAvailableSemaphores;
    std::vector<VkSemaphore> m_RenderFinishedSemaphores;
    std::vector<VkFence> m_InFlightFences;
    size_t m_iCurrentFrame;

    CVertexBufferVk *m_pVertexBuffer;
    CIndexBufferVk *m_pIndexBuffer;
    VkDeviceSize m_VertexBufferOffset;
    VkDeviceSize m_IndexBufferOffset;

    VkClearValue m_ClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

    std::vector<MeshOffset> m_DrawMeshes;

    // VK_TODO: detect window resize and modify this
    bool m_bFrameBufferResized = false;

    bool m_bIsMinimized : 1;
    // The current view hwnd
    void *m_ViewHWnd;
    int m_nWindowWidth;
    int m_nWindowHeight;

    bool m_bIsResizing;
};

#endif // VIEWPORTVK_H