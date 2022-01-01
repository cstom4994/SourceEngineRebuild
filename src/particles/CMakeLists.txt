set(PROJECT_NAME particles)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../public/particles/particles.h"
        "particles_internal.h"
        "random_floats.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../common/debug_lib_check.cpp"
        "addbuiltin_ops.cpp"
        "builtin_constraints.cpp"
        "builtin_initializers.cpp"
        "builtin_particle_emitters.cpp"
        "builtin_particle_forces.cpp"
        "builtin_particle_ops.cpp"
        "builtin_particle_render_ops.cpp"
        "particle_sort.cpp"
        "particles.cpp"
        "psheet.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(VPC_Scripts
        "../vpc_scripts/platform_dirs.vpc"
        "../vpc_scripts/source_base.vpc"
        "../vpc_scripts/source_lib_base.vpc"
        "../vpc_scripts/source_lib_win32_base.vpc"
        "../vpc_scripts/source_lib_win32_debug.vpc"
        "../vpc_scripts/source_lib_win32_release.vpc"
        "../vpc_scripts/source_video_base.vpc"
        "../vpc_scripts/source_win32_base.vpc"
        "../vpc_scripts/version.vpc"
        "particles.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        ${VPC_Scripts}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "particles"
        TARGET_NAME_RELEASE "particles"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public/tier1"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "DISABLE_ETW;"
        "_DEBUG;"
        "DEBUG;"
        "_SCL_SECURE_NO_WARNINGS"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
        "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
        "_ALLOW_MSC_VER_MISMATCH"
        ">"
        "VPC;"
        "RAD_TELEMETRY_DISABLED;"
        "LIBNAME=particles;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "SOURCE1=1;"
        "FUCK_STEAM;"
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
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /Ot;
            /Zo;
            /Oy-
            >
            /MP;
            /permissive;
            /GF;
            /W4;
            /WX-;
            /TP;
            /fp:fast;
            /GR;
            /wd4316;
            /wd4577;
            /wd4091;
            /Gw;
            /Zc:inline;
            /Zc:threadSafeInit-;
            /Wv:18;
            /GS;
            /Zc:wchar_t;
            /Zc:forScope;

            )
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
endif ()

