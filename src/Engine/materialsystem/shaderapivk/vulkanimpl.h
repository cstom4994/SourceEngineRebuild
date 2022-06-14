//

#ifndef VULKAN_IMPL_H
#define VULKAN_IMPL_H

#ifdef _WIN32
#pragma once
#endif

#include "materialsystem/imaterialsystem.h"
#include "dbg.h"

// VK_TODO: Make this the correct platform define
#define VK_USE_PLATFORM_WIN32_KHR
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vulkan/vulkan.hpp>

extern VkAllocationCallbacks *g_pAllocCallbacks;

const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

inline void vkCheck(VkResult result, std::string msg = "vkCheck")
{
    if (result != VK_SUCCESS)
    {
        msg += ", VkResult: " + std::to_string(result);

#ifdef DEBUG
        // Error() doesn't pause in debugger
        throw std::runtime_error(msg);
#else
        Error(msg.c_str());
#endif
    }
}

#include "bitmap/imageformat.h"

inline ImageFormat vkfmt2imgfmt(VkFormat format)
{
    static ImageFormat conversions[] = {
        IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN,
        IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN,
        IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN,
        IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN,
        IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN,
        IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN, IMAGE_FORMAT_UNKNOWN,
    };
    return conversions[(size_t)format];
}

inline VkFormat imgfmt2vkfmt(ImageFormat format)
{
    static VkFormat conversions[] = {
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_UNDEFINED, // non existent
        VK_FORMAT_R8G8B8_UNORM,
        VK_FORMAT_B8G8R8_UNORM,
        VK_FORMAT_R5G6B5_UNORM_PACK16,
        VK_FORMAT_R8_UNORM,
        VK_FORMAT_R8G8_UNORM,
        VK_FORMAT_R8_UNORM,
        VK_FORMAT_R8_UNORM,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8_UNORM,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_B5G6R5_UNORM_PACK16,
        VK_FORMAT_B5G5R5A1_UNORM_PACK16,
        VK_FORMAT_B4G4R4A4_UNORM_PACK16,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_B5G5R5A1_UNORM_PACK16,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_R16G16B16A16_SFLOAT,
        VK_FORMAT_R16G16B16A16_UNORM,
        VK_FORMAT_UNDEFINED,
        VK_FORMAT_R32_SFLOAT,
        VK_FORMAT_R32G32B32_SFLOAT,
        VK_FORMAT_R32G32B32A32_SFLOAT,

        // todo: depth formats
    };

    return conversions[(size_t)format];
}

inline VkPrimitiveTopology ComputeMode(MaterialPrimitiveType_t type)
{
    switch (type)
    {
    case MATERIAL_POINTS:
        return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;

    case MATERIAL_LINES:
        return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;

    case MATERIAL_TRIANGLES:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    case MATERIAL_TRIANGLE_STRIP:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;

    case MATERIAL_LINE_STRIP:
    	return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;

    case MATERIAL_LINE_LOOP:
    	return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;

    // Here, we expect to have the type set later. only works for static meshes
    case MATERIAL_HETEROGENOUS:
        return (VkPrimitiveTopology)-1;

    default:
        Assert(0);
        return (VkPrimitiveTopology)-1;
    }
}

#endif