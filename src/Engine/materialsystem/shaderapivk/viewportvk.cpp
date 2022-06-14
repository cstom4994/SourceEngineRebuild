#include "viewportvk.h"
#include <chrono>
#include <fstream>
#include "buffervkutil.h"
#include "shaderapivk.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
const int MAX_FRAMES_IN_FLIGHT = 2;
const uint64_t MAX_MESHES = 1024; // VK_TODO: find a way to remove these
const uint64_t MAX_VERTICES = 65535 * 64;
const uint64_t MAX_INDICES = 65535 * 64;

CViewportVk::CViewportVk()
{
    m_hSurface = VK_NULL_HANDLE;
    m_Swapchain = VK_NULL_HANDLE;
    m_VertShaderModule = VK_NULL_HANDLE;
    m_FragShaderModule = VK_NULL_HANDLE;
    m_RenderPass = VK_NULL_HANDLE;
    m_DescriptorSetLayout = VK_NULL_HANDLE;
    m_DescriptorPool = VK_NULL_HANDLE;
    m_PipelineLayout = VK_NULL_HANDLE;
    m_GraphicsPipeline = VK_NULL_HANDLE;
    m_CommandPool = VK_NULL_HANDLE;

    m_bIsMinimized = false;
    m_bIsResizing = false;

    m_iCurrentFrame = 0;
    m_IndexBufferOffset = 0;
    m_VertexBufferOffset = 0;
    m_nWindowHeight = 0;
    m_nWindowWidth = 0;

    m_pVertexBuffer = nullptr;
    m_pIndexBuffer = nullptr;
    m_ViewHWnd = nullptr;

    _backBufferFormat = IMAGE_FORMAT_UNKNOWN;
}

CViewportVk::~CViewportVk() {}

// Get details about swapchain support
SwapchainSupportDetails CViewportVk::QuerySwapchainSupport(VkPhysicalDevice device)
{
    SwapchainSupportDetails details{};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, GetSurface(), &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, GetSurface(), &formatCount, nullptr);
    if (formatCount != 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, GetSurface(), &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, GetSurface(), &presentModeCount, nullptr);
    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, GetSurface(), &presentModeCount, details.presentModes.data());
    }

    return details;
}

// Choose the present mode for swapchain
VkPresentModeKHR CViewportVk::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
    // VK_TODO:
    // Check for vsync settings
    // VK_PRESENT_MODE_IMMEDIATE_KHR	= no vsync
    // VK_PRESENT_MODE_FIFO_KHR			= vsync
    // VK_PRESENT_MODE_FIFO_RELAXED_KHR	= vsync unless frame is late
    // VK_PRESENT_MODE_MAILBOX_KHR		= triple buffering

    for (const auto &availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    // VK_PRESENT_MODE_FIFO_KHR should be available in all devices
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D CViewportVk::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    GetWindowSize(m_nWindowWidth, m_nWindowHeight);
    VkExtent2D actualExtent = {m_nWindowWidth, m_nWindowHeight};

    actualExtent.width = std::max(actualExtent.width, capabilities.minImageExtent.width);
    actualExtent.width = std::min(actualExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::max(actualExtent.height, capabilities.minImageExtent.height);
    actualExtent.height = std::min(actualExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}

VkSurfaceFormatKHR CViewportVk::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    for (const auto &availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

void CViewportVk::InitDevice(void *hWnd)
{
    m_ViewHWnd = hWnd;

    CreateVkSurface();
    CreateSwapchain();
    CreateImageViews();
    CreateRenderPass();
    CreateDescriptorSetlayout();
    CreateGraphicsPipeline();
    CreateFramebuffers();
    CreateCommandPool();
    m_pVertexBuffer = (CVertexBufferVk *)g_pShaderDevice->CreateVertexBuffer(SHADER_BUFFER_TYPE_STATIC, VERTEX_FORMAT_UNKNOWN, MAX_VERTICES,
                                                                             "CVertexBufferVk", true);
    m_pIndexBuffer = (CIndexBufferVk *)g_pShaderDevice->CreateIndexBuffer(SHADER_BUFFER_TYPE_STATIC, MATERIAL_INDEX_FORMAT_16BIT,
                                                                          MAX_INDICES, "CIndexBufferVk", true);
    CreateUniformBuffers();
    CreateDescriptorPool();
    CreateDescriptorSets();
    CreateCommandBuffers();
    CreateSyncObjects();
}

void CViewportVk::CreateSwapchain()
{
    VkPhysicalDevice adapter = g_pShaderDeviceMgr->GetAdapter();

    // Get details for swapchain
    SwapchainSupportDetails swapchainSupport = QuerySwapchainSupport(adapter);
    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapchainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapchainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(swapchainSupport.capabilities);

    // Maximum number of images in the swapchain
    uint32_t imageCount = swapchainSupport.capabilities.minImageCount + 1;
    if (swapchainSupport.capabilities.maxImageCount > 0 && imageCount > swapchainSupport.capabilities.maxImageCount)
    {
        imageCount = swapchainSupport.capabilities.maxImageCount;
    }

    // Swapchain settings
    VkSwapchainCreateInfoKHR swapchainCreateInfo{};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = GetSurface();
    swapchainCreateInfo.imageFormat = surfaceFormat.format;
    swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
    swapchainCreateInfo.imageExtent = extent;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCreateInfo.minImageCount = swapchainSupport.capabilities.minImageCount;
    // VK_TODO: support for VK_SHARING_MODE_CONCURRENT and multiple queues?
    swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainCreateInfo.queueFamilyIndexCount = 0;
    swapchainCreateInfo.pQueueFamilyIndices = nullptr;
    swapchainCreateInfo.preTransform = swapchainSupport.capabilities.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.presentMode = presentMode;
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    // Check surface support
    VkBool32 supported;
    uint32_t queueFamily;
    GetQueueFamily(adapter, queueFamily);
    vkCheck(vkGetPhysicalDeviceSurfaceSupportKHR(adapter, queueFamily, swapchainCreateInfo.surface, &supported),
            "failed to check surface support");

    if (supported != VK_TRUE)
    {
        Error("surface not supported");
    }

    // Create swapchain
    vkCheck(vkCreateSwapchainKHR(g_pShaderDevice->GetVkDevice(), &swapchainCreateInfo, g_pAllocCallbacks, &m_Swapchain),
            "failed to create swapchain");

    // Get images
    vkGetSwapchainImagesKHR(g_pShaderDevice->GetVkDevice(), m_Swapchain, &imageCount, nullptr);
    m_SwapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(g_pShaderDevice->GetVkDevice(), m_Swapchain, &imageCount, m_SwapchainImages.data());

    // Store swapchain variables for later use
    m_SwapchainImageFormat = surfaceFormat.format;
    m_SwapchainExtent = extent;
}

void CViewportVk::RecreateSwapchain()
{
    // VK_TODO: do we need to handle minimization here?
    // I don't think IShaderDevice::Present gets called
    // at all when minimized

    vkDeviceWaitIdle(g_pShaderDevice->GetVkDevice());

    CleanupSwapchain();

    CreateSwapchain();
    CreateImageViews();
    CreateRenderPass();
    CreateGraphicsPipeline();
    CreateFramebuffers();
    CreateUniformBuffers();
    CreateDescriptorPool();
    CreateDescriptorSets();
    CreateCommandBuffers();
}

void CViewportVk::CreateImageViews()
{
    m_SwapchainImageViews.resize(m_SwapchainImages.size());

    for (size_t i = 0; i < m_SwapchainImages.size(); i++)
    {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = m_SwapchainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = m_SwapchainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        vkCheck(vkCreateImageView(g_pShaderDevice->GetVkDevice(), &createInfo, g_pAllocCallbacks, &m_SwapchainImageViews[i]),
                "failed to create image view");
    }
}

void CViewportVk::CreateRenderPass()
{
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = m_SwapchainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    // Subpass dependecies
    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    vkCheck(vkCreateRenderPass(g_pShaderDevice->GetVkDevice(), &renderPassInfo, g_pAllocCallbacks, &m_RenderPass),
            "failed to create render pass");
}

void CViewportVk::CreateDescriptorSetlayout()
{
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    vkCheck(vkCreateDescriptorSetLayout(g_pShaderDevice->GetVkDevice(), &layoutInfo, g_pAllocCallbacks, &m_DescriptorSetLayout),
            "failed to create descriptor set layout");
}

void CViewportVk::CreateDescriptorSets()
{
    std::vector<VkDescriptorSetLayout> layouts(m_SwapchainImages.size(), m_DescriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = m_DescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(m_SwapchainImages.size());
    allocInfo.pSetLayouts = layouts.data();

    m_DescriptorSets.resize(m_SwapchainImages.size());
    vkCheck(vkAllocateDescriptorSets(g_pShaderDevice->GetVkDevice(), &allocInfo, m_DescriptorSets.data()),
            "failed to allocate descriptor sets");

    for (size_t i = 0; i < m_SwapchainImages.size(); i++)
    {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = m_UniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = m_DescriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = nullptr;
        descriptorWrite.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(g_pShaderDevice->GetVkDevice(), 1, &descriptorWrite, 0, nullptr);
    }
}

void CViewportVk::CreateDescriptorPool()
{
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    poolSize.descriptorCount = static_cast<uint32_t>(m_SwapchainImages.size());

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(m_SwapchainImages.size());
    poolInfo.flags = 0;

    vkCheck(vkCreateDescriptorPool(g_pShaderDevice->GetVkDevice(), &poolInfo, g_pAllocCallbacks, &m_DescriptorPool),
            "failed to create descriptor pool");
}

static std::vector<char> ReadFile(const std::string &filename)
{
    // TODO: replace with Source filesystem
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

void CViewportVk::CreateGraphicsPipeline()
{
    // Shader modules
    auto vertShaderCode = ReadFile("shaders/vert.spv");
    auto fragShaderCode = ReadFile("shaders/frag.spv");

    m_VertShaderModule =
        g_pShaderDevice->CreateShaderModule(reinterpret_cast<const uint32_t *>(vertShaderCode.data()), vertShaderCode.size());
    m_FragShaderModule =
        g_pShaderDevice->CreateShaderModule(reinterpret_cast<const uint32_t *>(fragShaderCode.data()), fragShaderCode.size());

    // Shader stages
    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = m_VertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = m_FragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    // Vertex input
    auto bindingDescription = Vertex::GetBindingDescription();
    auto attributeDescriptions = Vertex::GetAttributeDescriptions();
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    // Input assembly
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // Viewport and scissors
    VkViewport viewport = {};
    viewport.width = (float)m_SwapchainExtent.width;
    viewport.x = 0.0f;
    // Use bottom left as 0,0
    viewport.height = -(float)m_SwapchainExtent.height;
    viewport.y = (float)m_SwapchainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = m_SwapchainExtent;

    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    // Rasterizer
    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_LINE;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = g_pShaderAPI->GetCullMode();
    rasterizer.frontFace = g_pShaderAPI->GetFrontFace();
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;
    rasterizer.depthBiasClamp = 0.0f;
    rasterizer.depthBiasSlopeFactor = 0.0f;

    // Multisampling
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;

    // Depth and stencil testing
    VkPipelineDepthStencilStateCreateInfo *depthstencil = nullptr;

    // Color blending
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    // Dynamic states
    VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT};
    VkPipelineDynamicStateCreateInfo dynamicState = {};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = 1;
    dynamicState.pDynamicStates = dynamicStates;

    // Pipeline layout
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &m_DescriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    vkCheck(vkCreatePipelineLayout(g_pShaderDevice->GetVkDevice(), &pipelineLayoutInfo, g_pAllocCallbacks, &m_PipelineLayout),
            "failed to create pipeline layout");

    // Pipeline
    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = depthstencil;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = m_PipelineLayout;
    pipelineInfo.renderPass = m_RenderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;

    vkCheck(
        vkCreateGraphicsPipelines(g_pShaderDevice->GetVkDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, g_pAllocCallbacks, &m_GraphicsPipeline),
        "failed to create graphics pipeline");

    // Cleanup
    vkDestroyShaderModule(g_pShaderDevice->GetVkDevice(), m_FragShaderModule, g_pAllocCallbacks);
    vkDestroyShaderModule(g_pShaderDevice->GetVkDevice(), m_VertShaderModule, g_pAllocCallbacks);
}

void CViewportVk::CreateFramebuffers()
{
    m_SwapchainFramebuffers.resize(m_SwapchainImageViews.size());

    for (size_t i = 0; i < m_SwapchainImageViews.size(); i++)
    {
        VkImageView attachments[] = {m_SwapchainImageViews[i]};

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = m_RenderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = m_SwapchainExtent.width;
        framebufferInfo.height = m_SwapchainExtent.height;
        framebufferInfo.layers = 1;

        vkCheck(vkCreateFramebuffer(g_pShaderDevice->GetVkDevice(), &framebufferInfo, g_pAllocCallbacks, &m_SwapchainFramebuffers[i]),
                "failed to create framebuffers");
    }
}

void CViewportVk::CreateCommandPool()
{
    uint32_t queueFamily;
    GetQueueFamily(g_pShaderDeviceMgr->GetAdapter(), queueFamily);

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamily;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    vkCheck(vkCreateCommandPool(g_pShaderDevice->GetVkDevice(), &poolInfo, nullptr, &m_CommandPool), "failed to create command pool");
}

void CViewportVk::CreateUniformBuffers()
{
    const VkDeviceSize bufferSize = MAX_MESHES * g_pShaderDevice->GetUBOAlignment();

    m_UniformBuffers.resize(m_SwapchainImages.size());
    m_UniformBuffersMemory.resize(m_SwapchainImages.size());

    for (size_t i = 0; i < m_SwapchainImages.size(); i++)
    {
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, m_UniformBuffers[i],
                     m_UniformBuffersMemory[i]);
    }
}

void CViewportVk::CreateCommandBuffers()
{
    m_CommandBuffers.resize(m_SwapchainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_CommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

    vkCheck(vkAllocateCommandBuffers(g_pShaderDevice->GetVkDevice(), &allocInfo, m_CommandBuffers.data()),
            "failed to allocate command buffers");
}

void CViewportVk::CreateSyncObjects()
{
    m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkCheck(vkCreateSemaphore(g_pShaderDevice->GetVkDevice(), &semaphoreInfo, g_pAllocCallbacks, &m_ImageAvailableSemaphores[i]),
                "failed to create semaphore");
        vkCheck(vkCreateSemaphore(g_pShaderDevice->GetVkDevice(), &semaphoreInfo, g_pAllocCallbacks, &m_RenderFinishedSemaphores[i]),
                "failed to create semaphore");
        vkCheck(vkCreateFence(g_pShaderDevice->GetVkDevice(), &fenceInfo, g_pAllocCallbacks, &m_InFlightFences[i]),
                "failed to create fence");
    }
}

void CViewportVk::GetMatrices(VMatrix *view, VMatrix *proj, VMatrix *model)
{
    IMatRenderContext *renderContext = g_pMaterialSystem->GetRenderContext();
    renderContext->GetMatrix(MATERIAL_VIEW, view);
    renderContext->GetMatrix(MATERIAL_PROJECTION, proj);
    renderContext->GetMatrix(MATERIAL_MODEL, model);
}

UniformBufferObject CViewportVk::GetUniformBufferObject()
{
    VMatrix viewMatrix, projMatrix, modelMatrix;
    GetMatrices(&viewMatrix, &projMatrix, &modelMatrix);

    UniformBufferObject ubo = {};
    ubo.view = glm::make_mat4x4(viewMatrix.Base());
    ubo.proj = glm::make_mat4x4(projMatrix.Base());
    ubo.model = glm::make_mat4x4(modelMatrix.Base());

    // Source uses row-major storage,
    // we want column-major.
    ubo.view = glm::transpose(ubo.view);
    ubo.proj = glm::transpose(ubo.proj);
    ubo.model = glm::transpose(ubo.model);

    return ubo;
}

void CViewportVk::UpdateUniformBuffer(uint32_t currentImage)
{
    if (m_DrawMeshes.empty())
    {
        return;
    }

    const size_t bufferSize = m_DrawMeshes.size() * g_pShaderDevice->GetUBOAlignment();
    void *dynamicUBO = MemAlloc_AllocAligned(bufferSize, g_pShaderDevice->GetUBOAlignment());
    vkMapMemory(g_pShaderDevice->GetVkDevice(), m_UniformBuffersMemory[currentImage], 0, bufferSize, 0, &dynamicUBO);

    for (size_t i = 0; i < m_DrawMeshes.size(); i++)
    {
        UniformBufferObject *ubo = (UniformBufferObject *)((uint64_t)dynamicUBO + (i * g_pShaderDevice->GetUBOAlignment()));
        memcpy(ubo, &m_DrawMeshes[i].ubo, sizeof(UniformBufferObject));
    }

    // Flush to make changes visible to the host
    VkMappedMemoryRange memoryRange{};
    memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memoryRange.memory = m_UniformBuffersMemory[currentImage];
    memoryRange.size = bufferSize;
    vkFlushMappedMemoryRanges(g_pShaderDevice->GetVkDevice(), 1, &memoryRange);

    vkUnmapMemory(g_pShaderDevice->GetVkDevice(), m_UniformBuffersMemory[currentImage]);
    MemAlloc_FreeAligned(dynamicUBO);
}

void CViewportVk::UpdateCommandBuffer(uint32_t currentImage)
{
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    beginInfo.pInheritanceInfo = nullptr;

    vkCheck(vkBeginCommandBuffer(m_CommandBuffers[currentImage], &beginInfo), "failed to begin command buffer");

    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_RenderPass;
    renderPassInfo.framebuffer = m_SwapchainFramebuffers[currentImage];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = m_SwapchainExtent;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &m_ClearColor;

    vkCmdBeginRenderPass(m_CommandBuffers[currentImage], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(m_CommandBuffers[currentImage], VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);

    if (!m_DrawMeshes.empty())
    {
        VkBuffer vertexBuffers[] = {*(m_pVertexBuffer->GetVkBuffer())};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(m_CommandBuffers[currentImage], 0, 1, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(m_CommandBuffers[currentImage], *m_pIndexBuffer->GetVkBuffer(), 0, VK_INDEX_TYPE_UINT16);

        for (size_t i = 0; i < m_DrawMeshes.size(); i++)
        {
            // bind descriptor set for current mesh
            uint32_t dynamicOffset = i * g_pShaderDevice->GetUBOAlignment();
            vkCmdBindDescriptorSets(m_CommandBuffers[currentImage], VK_PIPELINE_BIND_POINT_GRAPHICS, m_PipelineLayout, 0, 1,
                                    &m_DescriptorSets[currentImage], 1, &dynamicOffset);

            /*
                VK_FIXME: Hammer draws line lists somewhere

                vkCmdDrawIndexed(): the last primitive topology VK_PRIMITIVE_TOPOLOGY_LINE_LIST state set by
                vkCmdSetPrimitiveTopologyEXT is not compatible with the pipeline topology VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST.
                The Vulkan spec states: If the bound graphics pipeline state was created with the
                VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT dynamic state enabled then vkCmdSetPrimitiveTopologyEXT must have been
                called in the current command buffer prior to this draw command, and the primitiveTopology parameter of
                vkCmdSetPrimitiveTopologyEXT must be of the same topology class as the pipeline
                VkPipelineInputAssemblyStateCreateInfo::topology state
                (https://vulkan.lunarg.com/doc/view/1.2.162.0/windows/1.2-extensions/vkspec.html#VUID-vkCmdDrawIndexed-primitiveTopology-03420)

                TL;DR: pipeline created with VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, so this can only be another triangle class
                (_LIST, _STRIP, _FAN, _LIST_WITH_ADJACENCY, _STRIP_WITH_ADJACENCY)
            */

            // set topology
            VULKAN_HPP_DEFAULT_DISPATCHER.vkCmdSetPrimitiveTopologyEXT(m_CommandBuffers[currentImage], m_DrawMeshes[i].topology);

            // draw
            Assert(m_DrawMeshes[i].firstIndex + m_DrawMeshes[i].indexCount <= m_pIndexBuffer->IndexCount());
            vkCmdDrawIndexed(m_CommandBuffers[currentImage], m_DrawMeshes[i].indexCount, 1, m_DrawMeshes[i].firstIndex,
                             m_DrawMeshes[i].firstVertex, 0);
        }
    }

    vkCmdEndRenderPass(m_CommandBuffers[currentImage]);

    vkCheck(vkEndCommandBuffer(m_CommandBuffers[currentImage]), "failed to end command buffer");

    // Meshes that want to be drawn should call Draw every frame
    m_VertexBufferOffset = 0;
    m_IndexBufferOffset = 0;
    m_DrawMeshes.resize(0);
}

void CViewportVk::Present()
{
    // Acquire image from swapchain
    uint32_t imageIndex;

    // Stop valve's min and max macro definitions from messing with numeric_limits::max()...
#pragma push_macro("max")
#undef max

    vkWaitForFences(g_pShaderDevice->GetVkDevice(), 1, &m_InFlightFences[m_iCurrentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

    VkResult result = vkAcquireNextImageKHR(g_pShaderDevice->GetVkDevice(), m_Swapchain, std::numeric_limits<uint64_t>::max(),
                                            m_ImageAvailableSemaphores[m_iCurrentFrame], VK_NULL_HANDLE, &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        RecreateSwapchain();
        return;
    }
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        Error("failed to acquire swapchain image!");
    }

#pragma pop_macro("max")

    UpdateUniformBuffer(imageIndex);

    UpdateCommandBuffer(imageIndex);

    // Submit commandbuffer
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {m_ImageAvailableSemaphores[m_iCurrentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_CommandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {m_RenderFinishedSemaphores[m_iCurrentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(g_pShaderDevice->GetVkDevice(), 1, &m_InFlightFences[m_iCurrentFrame]);

    vkCheck(vkQueueSubmit(g_pShaderDevice->GetGraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_iCurrentFrame]),
            "failed to submit queue");

    // Present
    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    VkSwapchainKHR swapchains[] = {m_Swapchain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapchains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;

    result = vkQueuePresentKHR(g_pShaderDevice->GetPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_bFrameBufferResized)
    {
        m_bFrameBufferResized = false;
        RecreateSwapchain();
    }
    else if (result != VK_SUCCESS)
    {
        Error("failed to present swapchain image!");
    }

    m_iCurrentFrame = (m_iCurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void CViewportVk::GetWindowSize(int &nWidth, int &nHeight)
{
    // If the window was minimized last time swap buffers happened, or if it's iconic now,
    // return 0 size
    if (!m_bIsMinimized && !IsIconic((HWND)m_ViewHWnd))
    {
        // NOTE: Use the 'current view' (which may be the same as the main window)
        Assert(m_ViewHWnd != nullptr);
        RECT rect;
        GetClientRect((HWND)m_ViewHWnd, &rect);
        nWidth = rect.right - rect.left;
        nHeight = rect.bottom - rect.top;
    }
    else
    {
        nWidth = nHeight = 0;
    }
}

void CViewportVk::CreateVkSurface()
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR; // VK_TODO: platform
    createInfo.hwnd = (HWND)m_ViewHWnd;
    createInfo.hinstance = GetModuleHandle(nullptr); // GetModuleHandle should be platform independent (defined in interface.h) on Linux/mac

    vkCheck(vkCreateWin32SurfaceKHR(g_pShaderDeviceMgr->GetInstance(), &createInfo, g_pAllocCallbacks, &m_hSurface),
            "failed to create surface");
}

void CViewportVk::DestroyVkSurface() { vkDestroySurfaceKHR(g_pShaderDeviceMgr->GetInstance(), m_hSurface, g_pAllocCallbacks); }

VkSurfaceKHR CViewportVk::GetSurface() { return m_hSurface; }

ImageFormat CViewportVk::GetBackBufferFormat() { return vkfmt2imgfmt(m_SwapchainImageFormat); }

void CViewportVk::GetBackBufferDimensions(int &width, int &height)
{
    width = m_SwapchainExtent.width;
    height = m_SwapchainExtent.height;
}

void CViewportVk::CleanupSwapchain()
{
    for (size_t i = 0; i < m_SwapchainFramebuffers.size(); i++)
    {
        vkDestroyFramebuffer(g_pShaderDevice->GetVkDevice(), m_SwapchainFramebuffers[i], g_pAllocCallbacks);
    }

    for (size_t i = 0; i < m_SwapchainImages.size(); i++)
    {
        vkDestroyBuffer(g_pShaderDevice->GetVkDevice(), m_UniformBuffers[i], g_pAllocCallbacks);
        vkFreeMemory(g_pShaderDevice->GetVkDevice(), m_UniformBuffersMemory[i], g_pAllocCallbacks);
    }

    vkDestroyDescriptorPool(g_pShaderDevice->GetVkDevice(), m_DescriptorPool, g_pAllocCallbacks);

    vkFreeCommandBuffers(g_pShaderDevice->GetVkDevice(), m_CommandPool, static_cast<uint32_t>(m_CommandBuffers.size()),
                         m_CommandBuffers.data());

    vkDestroyPipeline(g_pShaderDevice->GetVkDevice(), m_GraphicsPipeline, g_pAllocCallbacks);
    vkDestroyPipelineLayout(g_pShaderDevice->GetVkDevice(), m_PipelineLayout, g_pAllocCallbacks);
    vkDestroyRenderPass(g_pShaderDevice->GetVkDevice(), m_RenderPass, g_pAllocCallbacks);

    for (size_t i = 0; i < m_SwapchainImageViews.size(); i++)
    {
        vkDestroyImageView(g_pShaderDevice->GetVkDevice(), m_SwapchainImageViews[i], g_pAllocCallbacks);
    }

    vkDestroySwapchainKHR(g_pShaderDevice->GetVkDevice(), m_Swapchain, g_pAllocCallbacks);
}

void CViewportVk::ShutdownDevice()
{
    // InitDevice might not have been called if we crash on startup
    if (!g_pShaderDevice->GetVkDevice())
    {
        return;
    }

    vkDeviceWaitIdle(g_pShaderDevice->GetVkDevice());

    CleanupSwapchain();

    delete m_pVertexBuffer;
    delete m_pIndexBuffer;

    vkDestroyDescriptorSetLayout(g_pShaderDevice->GetVkDevice(), m_DescriptorSetLayout, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(g_pShaderDevice->GetVkDevice(), m_RenderFinishedSemaphores[i], g_pAllocCallbacks);
        vkDestroySemaphore(g_pShaderDevice->GetVkDevice(), m_ImageAvailableSemaphores[i], g_pAllocCallbacks);
        vkDestroyFence(g_pShaderDevice->GetVkDevice(), m_InFlightFences[i], g_pAllocCallbacks);
    }

    vkDestroyCommandPool(g_pShaderDevice->GetVkDevice(), m_CommandPool, g_pAllocCallbacks);

    DestroyVkSurface();
}

void CViewportVk::DrawMesh(CBaseMeshVk *pMesh)
{
    CVertexBufferVk *vertexBuffer = pMesh->GetVertexBuffer();
    CIndexBufferVk *indexBuffer = pMesh->GetIndexBuffer();

    int vertexCount = pMesh->VertexCount();
    int indexCount = pMesh->IndexCount();
    VkDeviceSize vertexRegionSize = vertexCount * vertexBuffer->VertexSize();
    VkDeviceSize indexRegionSize = indexCount * indexBuffer->IndexSize();

    // Copy mesh buffers to optimal destination buffers
    Assert(m_pVertexBuffer->GetBufferSize() >= m_VertexBufferOffset + vertexRegionSize);
    CopyBuffer(*vertexBuffer->GetVkBuffer(), *m_pVertexBuffer->GetVkBuffer(), 0, m_VertexBufferOffset, vertexRegionSize);
    Assert(m_pIndexBuffer->GetBufferSize() >= m_IndexBufferOffset + indexRegionSize);
    CopyBuffer(*indexBuffer->GetVkBuffer(), *m_pIndexBuffer->GetVkBuffer(), 0, m_IndexBufferOffset, indexRegionSize);

    // Store current byte offsets for copying into buffers
    m_VertexBufferOffset += vertexRegionSize;
    m_IndexBufferOffset += indexRegionSize;

    // Get vertex and index offsets for this mesh
    int firstVertex = 0;
    int firstIndex = 0;
    if (!m_DrawMeshes.empty())
    {
        auto back = m_DrawMeshes.back();
        firstVertex += back.firstVertex + back.vertexCount;
        firstIndex += back.firstIndex + back.indexCount;
    }

    MeshOffset m;
    m.vertexCount = vertexCount;
    m.indexCount = indexCount;
    m.firstVertex = firstVertex;
    m.firstIndex = firstIndex;
    m.topology = ComputeMode(pMesh->GetPrimitiveType());
    m.ubo = GetUniformBufferObject();

    m_DrawMeshes.push_back(m);
}

void CViewportVk::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = m_CommandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(g_pShaderDevice->GetVkDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = srcOffset;
    copyRegion.dstOffset = dstOffset;
    copyRegion.size = size;
    Assert(copyRegion.size > 0);
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(g_pShaderDevice->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(g_pShaderDevice->GetGraphicsQueue());
    vkFreeCommandBuffers(g_pShaderDevice->GetVkDevice(), m_CommandPool, 1, &commandBuffer);
}
