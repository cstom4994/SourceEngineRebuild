#include "shaderdevicevk.h"

static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                         VkDeviceMemory &bufferMemory)
{
    // Create buffer
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    vkCheck(vkCreateBuffer(g_pShaderDevice->GetVkDevice(), &bufferInfo, g_pAllocCallbacks, &buffer), "failed to create buffer!");

    // Get memory requirements
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(g_pShaderDevice->GetVkDevice(), buffer, &memRequirements);

    // Allocate memory
    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = g_pShaderDeviceMgr->FindMemoryType(0, memRequirements.memoryTypeBits, properties);
    vkCheck(vkAllocateMemory(g_pShaderDevice->GetVkDevice(), &allocInfo, g_pAllocCallbacks, &bufferMemory),
            "failed to allocate buffer memory!");

    // Bind memory
    vkCheck(vkBindBufferMemory(g_pShaderDevice->GetVkDevice(), buffer, bufferMemory, 0), "failed to bind buffer memory!");
}