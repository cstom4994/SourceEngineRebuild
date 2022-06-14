set(PROJECT_NAME shaderapivk)

################################################################################
# Source groups
################################################################################
set(Public_Header_Files
    "../../public/materialsystem/idebugtextureinfo.h"
    "../../public/materialsystem/ivballoctracker.h"
    "../../public/materialsystem/shader_vcs_version.h"
    "../../public/shaderapi/ishaderapi.h"
    "../../public/shaderapi/IShaderDevice.h"
    "../../public/shaderapi/ishaderdynamic.h"
    "../../public/shaderapi/ishadershadow.h"
    "../../public/shaderapi/ishaderutil.h"
)
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
    "../../public/tier0/memoverride.cpp"
    "localvktypes.h"
    "shaderapivk_global.h"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__App_System
    "shaderdevicemgrvk.cpp"
    "shaderdevicemgrvk.h"
)
source_group("Source Files\\App System" FILES ${Source_Files__App_System})

set(Source_Files__Buffer
    "buffervkutil.h"
    "indexbuffervk.cpp"
    "indexbuffervk.h"
    "vertexbuffervk.cpp"
    "vertexbuffervk.h"
)
source_group("Source Files\\Buffer" FILES ${Source_Files__Buffer})

set(Source_Files__Device_/_Renderer
    "hardwareconfig.cpp"
    "hardwareconfig.h"
    "shaderapivk.cpp"
    "shaderapivk.h"
    "shaderdevicevk.cpp"
    "shaderdevicevk.h"
    "shadermanagervk.cpp"
    "shadermanagervk.h"
    "shadershadowvk.cpp"
    "shadershadowvk.h"
    "viewportvk.cpp"
    "viewportvk.h"
)
source_group("Source Files\\Device / Renderer" FILES ${Source_Files__Device_/_Renderer})

set(Source_Files__Mesh
    "meshmgrvk.cpp"
    "meshmgrvk.h"
    "meshvk.cpp"
    "meshvk.h"
)
source_group("Source Files\\Mesh" FILES ${Source_Files__Mesh})

set(Source_Files__Shaders
    "shaders/compile.bat"
    "shaders/shader.frag"
    "shaders/shader.vert"
)
source_group("Source Files\\Shaders" FILES ${Source_Files__Shaders})

set(Source_Files__Vertex
    "vertexvk.h"
)
source_group("Source Files\\Vertex" FILES ${Source_Files__Vertex})

set(Source_Files__Vulkan_Callbacks
    "vulkanimpl.cpp"
    "vulkanimpl.h"
)
source_group("Source Files\\Vulkan Callbacks" FILES ${Source_Files__Vulkan_Callbacks})

set(ALL_FILES
    ${Public_Header_Files}
    ${Source_Files}
    ${Source_Files__App_System}
    ${Source_Files__Buffer}
    ${Source_Files__Device_/_Renderer}
    ${Source_Files__Mesh}
    ${Source_Files__Shaders}
    ${Source_Files__Vertex}
    ${Source_Files__Vulkan_Callbacks}
)

################################################################################
# Target
################################################################################

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Compile definitions
################################################################################

################################################################################
# Compile and link options
################################################################################
################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    mathlib
    tier1
)

