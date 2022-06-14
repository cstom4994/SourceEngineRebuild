set(PROJECT_NAME ShadersLazuul)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "BaseVSShader.h"
    "common_fxc.h"
    "common_hlsl_cpp_consts.h"
    "common_ps_fxc.h"
    "common_vertexlitgeneric_dx9.h"
    "common_vs_fxc.h"
    "example_model_dx9_helper.h"
    "shader_constant_register_map.h"
    "tree_sway.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../public/tier0/memoverride.cpp"
    "BaseVSShader.cpp"
    "black.cpp"
    "Bloom.cpp"
    "c17_showz.cpp"
    "cloak_blended_pass_helper.cpp"
    "core_dx9.cpp"
    "DepthOfField_dx9.cpp"
    "depthwrite.cpp"
    "downsample.cpp"
    "downsample_nohdr.cpp"
    "emissive_scroll_blended_pass_helper.cpp"
    "Engine_Post_dx9.cpp"
    "example_model_dx9.cpp"
    "example_model_dx9_helper.cpp"
    "eye_refract.cpp"
    "eye_refract_helper.cpp"
    "flesh_interior_blended_pass_helper.cpp"
    "light_volumetrics.cpp"
    "lightmappedgeneric_dx9.cpp"
    "lightmappedgeneric_dx9_helper.cpp"
    "lightshafts.cpp"
    "lightshafts_helper.cpp"
    "lightshafts_helper.h"
    "object_motion_blur_dx9.cpp"
    "pbr_dx9.cpp"
    "pbr_dx9_helper.cpp"
    "portal_refract.cpp"
    "portal_refract_helper.cpp"
    "portalstaticoverlay.cpp"
    "PP_Fog.cpp"
    "pp_vertexlit_wetness_pass.cpp"
    "pp_vertexlit_wetness_pass.h"
    "refract.cpp"
    "refract_dx9_helper.cpp"
    "screenspace_general.cpp"
    "shadow.cpp"
    "shadowbuild_dx9.cpp"
    "shadowmodel_dx9.cpp"
    "skin_dx9_helper.cpp"
    "SkyMask.cpp"
    "solidenergy_dx9.cpp"
    "solidenergy_dx9_helper.cpp"
    "solidenergy_dx9_helper.h"
    "splinerope.cpp"
    "ssgi.cpp"
    "teeth.cpp"
    "unlitgeneric_dx9.cpp"
    "vertexlitgeneric_dx9.cpp"
    "vertexlitgeneric_dx9_helper.cpp"
    "water.cpp"
    "weapon_sheen_pass_helper.cpp"
    "weapon_sheen_pass_helper.h"
    "worldvertextransition.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "game_shader_dx9"
    TARGET_NAME_RELEASE "game_shader_dx9"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Debug_dx9_mod_lazuul"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Release_dx9_mod_lazuul"
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
target_include_directories(${PROJECT_NAME} PRIVATE
    "${MYROOTDIR}/common;"
    "${MYROOTDIR}/public;"
    "${MYROOTDIR}/public/tier0;"
    "${MYROOTDIR}/public/tier1;"
    "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9"
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
    "VPC;"
    "RAD_TELEMETRY_DISABLED;"
    "DLLNAME=game_shader_dx9;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "STDSHADER_DX9_DLL_EXPORT;"
    "FAST_MATERIALVAR_ACCESS;"
    "GAME_SHADER_DLL;"
    "USE_ACTUAL_DX;"
    "SOURCE1=1;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /ZI
        >
        $<$<CONFIG:Release>:
            /O2;
            /Ob2;
            /Oi;
            /Gy;
            /Zi;
            /Ot;
            /Zo
        >
        /MP;
        /GF;
        /arch:SSE2;
        /TP;
        /fp:fast;
        /GR;
        /wd4316;
        /wd4594;
        /wd4457;
        /wd4456;
        /wd4458;
        /wd4459;
        /wd4624;
        /wd4577;
        /wd4838;
        /Zm200;
        /Gw;
        /Zc:inline;
        /GS;
        /Zc:forScope;
        /Y-
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /NODEFAULTLIB:libcpmt;
            /NODEFAULTLIB:libcpmt1;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /NODEFAULTLIB:libcmtd;
            /NODEFAULTLIB:libcpmtd;
            /NODEFAULTLIB:libcpmtd0;
            /NODEFAULTLIB:libcpmtd1;
            /OPT:REF;
            /OPT:NOICF;
            /INCREMENTAL:NO
        >
        /NODEFAULTLIB:libc;
        /NODEFAULTLIB:libcd;
        /NOLOGO;
        /MANIFEST:NO;
        /DEBUG;
        /SAFESEH:NO;
        /SUBSYSTEM:WINDOWS;
        /DYNAMICBASE:NO;
        /ignore:4221
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    shaderlib
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "shell32;"
    "user32;"
    "advapi32;"
    "gdi32;"
    "comdlg32;"
    "ole32;"
    "legacy_stdio_definitions;"
    "version;"
    "winmm"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${MYROOTDIR}/lib/common/.;"
    "${MYROOTDIR}/lib/public/."
)

