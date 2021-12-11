set(PROJECT_NAME ShadersVANCE)

################################################################################
# Source groups
################################################################################
set(______
        "_buildallshaders.bat"
        "_buildshaders.bat"
        )
source_group("
" FILES ${______})

set(Header_Files
        "BaseVSShader.h"
        "common_fxc.h"
        "common_hlsl_cpp_consts.h"
        "common_ps_fxc.h"
        "common_vertexlitgeneric_dx9.h"
        "common_vs_fxc.h"
        "example_model_dx9_helper.h"
        "shader_constant_register_map.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Shader_Source
        #    "_shaderlist_dx9_20b.txt"
        #    "_shaderlist_dx9_30.txt"
        )
source_group("Shader Source" FILES ${Shader_Source})

set(Shader_Source__fxc
        #    "chromatic_ps2x.fxc"
        #    "chromatic_vs20.fxc"
        #    "depthwrite_ps2x.fxc"
        #    "depthwrite_vs20.fxc"
        #    "flashlight_ps2x.fxc"
        #    "fxaa_ps30.fxc"
        #    "fxaa_vs30.fxc"
        #    "gaussian_depthaware_ps30.fxc"
        #    "gaussian_depthaware_roughness_ps30.fxc"
        #    "gaussianx_ps2x.fxc"
        #    "gaussiany_ps2x.fxc"
        #    "light_mesh_ps30.fxc"
        #    "light_mesh_vs30.fxc"
        #    "light_volumetrics_ps20b.fxc"
        #    "light_volumetrics_vs20.fxc"
        #    "lightmappedgeneric_flashlight_vs20.fxc"
        #    "lightmappedgeneric_ps30.fxc"
        #    "lightmappedgeneric_vs30.fxc"
        #    "lightmappedPBR_ps30.fxc"
        #    "lightmappedPBR_vs30.fxc"
        #    "lightpass_ps30.fxc"
        #    "lightpass_vs30.fxc"
        #    "lpreview1_ps2x.fxc"
        #    "luma_ps30.fxc"
        #    "normalmapreconstruct_ps30.fxc"
        #    "passthru_vs20.fxc"
        #    "screenspace_simple_vs30.fxc"
        #    "screenwater_ps2x.fxc"
        #    "screenwater_vs20.fxc"
        #    "SDK_screenspaceeffect_vs20.fxc"
        #    "skydome_ps30.fxc"
        #    "skydome_vs30.fxc"
        #    "ssgi_combine_ps30.fxc"
        #    "ssgi_ps30.fxc"
        #    "ssr_ps30.fxc"
        #    "unsharp_blur_ps2x.fxc"
        #    "unsharp_blur_vs20.fxc"
        #    "unsharp_ps2x.fxc"
        #    "unsharp_vs20.fxc"
        #    "vance_bloom_combine_ps30.fxc"
        #    "vance_scope_ps30.fxc"
        #    "vance_scope_vs30.fxc"
        #    "Vance_Tonemap_ps30.fxc"
        #    "vertexlit_and_unlit_generic_bump_ps30.fxc"
        #    "vertexlit_and_unlit_generic_bump_vs30.fxc"
        #    "vertexlit_and_unlit_generic_ps30.fxc"
        #    "vertexlit_and_unlit_generic_vs30.fxc"
        #    "vertexlitPBR_ps30.fxc"
        #    "vertexlitPBR_vs30.fxc"
        )
source_group("Shader Source\\fxc" FILES ${Shader_Source__fxc})

set(Source_Files
        "../../../public/tier0/memoverride.cpp"
        "BaseVSShader.cpp"
        "deferred/IDeferredExt.cpp"
        "light_volumetrics.cpp"
        "lightmappedgeneric_dx9.cpp"
        "lightmappedgeneric_dx9_helper.cpp"
        "lightmappedgeneric_dx9_helper.h"
        "LightmappedPBR_dx9.cpp"
        "LightmappedPBR_dx9_helper.cpp"
        "LightmappedPBR_dx9_helper.h"
        "lightpass_helper.cpp"
        "lightpass_helper.h"
        "screenspace_general.cpp"
        "vance/light_mesh.cpp"
        "vance_scope_dx9.cpp"
        "vertexlitgeneric_dx9.cpp"
        "vertexlitgeneric_dx9_helper.cpp"
        "vertexlitgeneric_dx9_helper.h"
        "VertexlitPBR_dx9.cpp"
        "VertexlitPBR_dx9_helper.cpp"
        "VertexlitPBR_dx9_helper.h"
        "worldvertextransition.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Post-processing
        "vance/Bloom_combine.cpp"
        "vance/chromatic.cpp"
        "vance/fxaa.cpp"
        "vance/gaussian_depthaware.cpp"
        "vance/gaussian_depthaware_roughness.cpp"
        "vance/gaussianx.cpp"
        "vance/gaussiany.cpp"
        "vance/luma.cpp"
        "vance/screenwater.cpp"
        "vance/skydome_atmosphere.cpp"
        "vance/skydome_atmosphere_helper.cpp"
        "vance/skydome_atmosphere_helper.h"
        "vance/ssao_combine.cpp"
        "vance/SSGI.cpp"
        "vance/tonemap.cpp"
        "vance/unsharp.cpp"
        "vance/unsharp_blur.cpp"
        )
source_group("Source Files\\Post-processing" FILES ${Source_Files__Post-processing})

set(ALL_FILES
        ${______}
        ${Header_Files}
        ${Shader_Source}
        ${Shader_Source__fxc}
        ${Source_Files}
        ${Source_Files__Post-processing}
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
        TARGET_NAME_DEBUG "game_shader_dx9"
        TARGET_NAME_RELEASE "game_shader_dx9"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/vance/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/vance/bin"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vance;"
        "${CMAKE_CURRENT_SOURCE_DIR}/deferred"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_HAS_ITERATOR_DEBUGGING=0;"
        "_DEBUG;"
        "DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "VPC;"
        "RAD_TELEMETRY_DISABLED;"
        "WIN32;"
        "_WIN32;"
        "_WINDOWS;"
        "_USRDLL;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
        "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
        "_ALLOW_MSC_VER_MISMATCH;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "_DLL_EXT=.dll;"
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
        "VANCE;"
        "_EXTERNAL_DLL_EXT=.dll;"
        "VPCGAMECAPS=VANCE;"
        "SOURCE1=1;"
        "VPCGAME=vance;"
        "_MBCS"
        )

################################################################################
# Compile and link options
################################################################################
if (MSVC)
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
            /arch:SSE;
            /TP;
            /fp:fast;
            /GR;
            /wd4316;
            /Zm200;
            /Gw;
            /Zc:inline;
            /GS;
            /Zc:forScope;
            /Y-
            )
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        Bzip2
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        Bzip2
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib

        d3d9
        d3dx9

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "version;"
        "winmm"
        )

target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../thirdparty/dxsdk/lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/public"
        )
