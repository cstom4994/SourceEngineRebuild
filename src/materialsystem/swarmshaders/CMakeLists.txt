set(PROJECT_NAME game_shader_generic_deferred)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../../devtools/bin/fxc_prep.pl"
    "../../devtools/bin/psh_prep.pl"
    "../../devtools/bin/updateshaders.pl"
    "../../devtools/bin/valve_perl_helpers.pl"
    "../../devtools/bin/vsh_prep.pl"
    "bdef.bat"
    "buildshaders.bat"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "BaseVSShader.h"
    "commandbuilder.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Shader_Source
    "deferred_shaders.txt"
)
source_group("Shader Source" FILES ${Shader_Source})

set(Shader_Source__fxc
    "composite_ps30.fxc"
    "composite_vs30.fxc"
    "defconstruct_vs30.fxc"
    "gaussianblur_6_ps30.fxc"
    "gbuffer_defshading2_ps30.fxc"
    "gbuffer_defshading2_vs30.fxc"
    "gbuffer_defshading_ps30.fxc"
    "gbuffer_ps30.fxc"
    "gbuffer_vs30.fxc"
    "lightingpass_area_ps30.fxc"
    "lightingpass_global_ps30.fxc"
    "lightingpass_point_ps30.fxc"
    "lightingpass_spot_ps30.fxc"
    "radiosity_blend_ps30.fxc"
    "radiosity_gen_global_ps30.fxc"
    "radiosity_gen_vs30.fxc"
    "radiosity_propagate_ps30.fxc"
    "radiosity_propagate_vs30.fxc"
    "screenspace_combine_ps30.fxc"
    "screenspace_shading_ps30.fxc"
    "screenspace_vs30.fxc"
    "shadowpass_ps30.fxc"
    "shadowpass_vs30.fxc"
    "volume_blend_ps30.fxc"
    "volume_prepass_ps30.fxc"
    "volume_prepass_vs30.fxc"
    "volumpass_point_ps30.fxc"
    "volumpass_spot_ps30.fxc"
)
source_group("Shader Source\\fxc" FILES ${Shader_Source__fxc})

set(Shader_Source__fxc__debug
    "debug_lighting_ctrl_ps30.fxc"
    "debug_radiosity_grid_ps30.fxc"
    "debug_radiosity_grid_vs30.fxc"
    "debug_shadow_ortho_ps30.fxc"
)
source_group("Shader Source\\fxc\\debug" FILES ${Shader_Source__fxc__debug})

set(Shader_Source__inc
    "common_deferred_fxc.h"
    "common_fxc.h"
    "common_hlsl_cpp_consts.h"
    "common_lighting_fxc.h"
    "common_pragmas.h"
    "common_ps_fxc.h"
    "common_shadowmapping_fxc.h"
    "common_vertexlitgeneric_dx9.h"
    "common_vs_fxc.h"
    "cpp_shader_constant_register_map.h"
)
source_group("Shader Source\\inc" FILES ${Shader_Source__inc})

set(Source_Files
    "BaseVSShader.cpp"
    "blur.cpp"
    "deferred_brush.cpp"
    "deferred_decalModulate.cpp"
    "deferred_global_common.h"
    "deferred_model.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__debug
    "debug_lightingctrl.cpp"
    "debug_radiosity_grid.cpp"
    "debug_shadow.cpp"
)
source_group("Source Files\\debug" FILES ${Source_Files__debug})

set(Source_Files__interface
    "IDeferredExt.cpp"
    "IDeferredExt.h"
)
source_group("Source Files\\interface" FILES ${Source_Files__interface})

set(Source_Files__lighting
    "lighting_global.cpp"
    "lighting_helper.h"
    "lighting_pass_basic.cpp"
    "lighting_pass_basic.h"
    "lighting_pass_volum.cpp"
    "lighting_pass_volum.h"
    "lighting_volume.cpp"
    "lighting_world.cpp"
    "radiosity_blend.cpp"
    "radiosity_global.cpp"
    "radiosity_propagate.cpp"
    "screenspace_combine.cpp"
    "screenspace_shading.cpp"
    "volume_blend.cpp"
    "volume_prepass.cpp"
)
source_group("Source Files\\lighting" FILES ${Source_Files__lighting})

set(Source_Files__scene
    "defpass_composite.cpp"
    "defpass_composite.h"
    "defpass_gbuffer.cpp"
    "defpass_gbuffer.h"
    "defpass_shadow.cpp"
    "defpass_shadow.h"
)
source_group("Source Files\\scene" FILES ${Source_Files__scene})

set(Source_Files__util
    "deferred_context.h"
    "deferred_includes.h"
    "deferred_utility.cpp"
    "deferred_utility.h"
)
source_group("Source Files\\util" FILES ${Source_Files__util})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Shader_Source}
    ${Shader_Source__fxc}
    ${Shader_Source__fxc__debug}
    ${Shader_Source__inc}
    ${Source_Files}
    ${Source_Files__debug}
    ${Source_Files__interface}
    ${Source_Files__lighting}
    ${Source_Files__scene}
    ${Source_Files__util}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} Debug   "../../modProps.cmake")
use_props(${PROJECT_NAME} Release "../../modProps.cmake")

set(ROOT_NAMESPACE stdshader_dx9-2005)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "${PROJECT_NAME}"
    TARGET_NAME_RELEASE "${PROJECT_NAME}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug_dx9"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release_dx9"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PDB_OUTPUT_DIRECTORY         "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebug
    >
    $<$<CONFIG:Release>:
        MultiThreaded
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
    "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../dx9sdk/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "WIN32;"
    "_WIN32;"
    "_WINDOWS;"
    "_USRDLL;"
    "_CRT_SECURE_NO_DEPRECATE;"
    "_CRT_NONSTDC_NO_DEPRECATE;"
    "STDSHADER_DX9_DLL_EXPORT;"
    "FAST_MATERIALVAR_ACCESS;"
    "COMPILER_MSVC;"
    "COMPILER_MSVC32;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Gm;
            /Od;
            /RTC1;
            /ZI
        >
        $<$<CONFIG:Release>:
            /MP;
            /O2;
            /Ob2;
            /Oi;
            /Gy;
            /Zi;
            /Ot
        >
        /GF;
        /W4;
        /TP;
        /fp:fast;
        /GR;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /GS-;
        /Zc:forScope;
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /NODEFAULTLIB:libcmtd;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /NODEFAULTLIB:libc;
        /NODEFAULTLIB:libcd;
        /NOLOGO;
        /MANIFEST:NO;
        /DEBUG;
        /MACHINE:X86;
        /SUBSYSTEM:WINDOWS
    )
endif()

################################################################################
# Custom build events
################################################################################
add_custom_command_if(
    OUTPUT "$(appsDir)\Sourcemods\$(modName)\bin\$(ProjectName).dll;$(appsDir)\Sourcemods\$(modName)\bin\$(ProjectName).map;%(Outputs)"
    COMMANDS
    COMMAND   $<CONFIG:Debug> if exist "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin\\${PROJECT_NAME}.dll" attrib -r "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin\\${PROJECT_NAME}.dll"
    COMMAND   $<CONFIG:Debug> copy "${OUTPUT_DIRECTORY}"${PROJECT_NAME}.dll "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin"
    COMMAND   $<CONFIG:Debug> if exist "${OUTPUT_DIRECTORY}"${PROJECT_NAME}.map copy "${OUTPUT_DIRECTORY}"${PROJECT_NAME}.map "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin\\${PROJECT_NAME}.map"
    COMMAND $<CONFIG:Release> if exist "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin\\${PROJECT_NAME}.dll" attrib -r "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin\\${PROJECT_NAME}.dll"
    COMMAND $<CONFIG:Release> copy "${OUTPUT_DIRECTORY}"${PROJECT_NAME}.dll "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin"
    COMMAND $<CONFIG:Release> if exist "${OUTPUT_DIRECTORY}"${PROJECT_NAME}.map copy "${OUTPUT_DIRECTORY}"${PROJECT_NAME}.map "$ENV{appsDir}\\Sourcemods\\$ENV{modName}\\bin\\${PROJECT_NAME}.map"
    COMMENT "
      "
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    shaderlib
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Release>:"
        "tier1;"
        "interfaces"
    ">"
    "version;"
    "winmm"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
)

