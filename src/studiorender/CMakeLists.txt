set(PROJECT_NAME StudioRender)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "flexrenderdata.h"
        "r_studiolight.h"
        "studiorender.h"
        "studiorendercontext.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
        "../public/appframework/IAppSystem.h"
        "../public/basehandle.h"
        "../public/bspflags.h"
        "../public/clientstats.h"
        "../public/cmodel.h"
        "../public/const.h"
        "../public/gametrace.h"
        "../public/ihandleentity.h"
        "../public/istudiorender.h"
        "../public/materialsystem/imaterial.h"
        "../public/materialsystem/imaterialsystem.h"
        "../public/materialsystem/imaterialsystemhardwareconfig.h"
        "../public/materialsystem/imaterialvar.h"
        "../public/materialsystem/imesh.h"
        "../public/materialsystem/itexture.h"
        "../public/mathlib/amd3dx.h"
        "../public/mathlib/compressed_vector.h"
        "../public/mathlib/mathlib.h"
        "../public/mathlib/vector.h"
        "../public/mathlib/vector2d.h"
        "../public/mathlib/vector4d.h"
        "../public/mathlib/vmatrix.h"
        "../public/mathlib/vplane.h"
        "../public/measure_section.h"
        "../public/model_types.h"
        "../public/optimize.h"
        "../public/pixelwriter.h"
        "../public/string_t.h"
        "../public/studio.h"
        "../public/tier0/basetypes.h"
        "../public/tier0/commonmacros.h"
        "../public/tier0/dbg.h"
        "../public/tier0/fasttimer.h"
        "../public/tier0/icommandline.h"
        "../public/tier0/mem.h"
        "../public/tier0/memalloc.h"
        "../public/tier0/memdbgoff.h"
        "../public/tier0/memdbgon.h"
        "../public/tier0/platform.h"
        "../public/tier0/protected_things.h"
        "../public/tier0/vprof.h"
        "../public/tier1/convar.h"
        "../public/tier1/interface.h"
        "../public/tier1/strtools.h"
        "../public/tier1/utlbuffer.h"
        "../public/tier1/utllinkedlist.h"
        "../public/tier1/utlmemory.h"
        "../public/tier1/UtlStringMap.h"
        "../public/tier1/utlvector.h"
        "../public/vcollide.h"
        "../public/vstdlib/vstdlib.h"
        "../public/vtf/vtf.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../common/debug_dll_check.cpp"
        "../public/tier0/memoverride.cpp"
        "flexrenderdata.cpp"
        "r_studio.cpp"
        "r_studiodecal.cpp"
        "r_studiodraw.cpp"
        "r_studiodraw_computeflexedvertex.cpp"
        "r_studioflex.cpp"
        "r_studiogettriangles.cpp"
        "r_studiolight.cpp"
        "r_studiostats.cpp"
        "studiorender.cpp"
        "studiorendercontext.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(VPC_Scripts
        "../vpc_scripts/loadaddress.vpc"
        "../vpc_scripts/platform_dirs.vpc"
        "../vpc_scripts/source_base.vpc"
        "../vpc_scripts/source_dll_base.vpc"
        "../vpc_scripts/source_dll_win32_base.vpc"
        "../vpc_scripts/source_dll_win32_debug.vpc"
        "../vpc_scripts/source_dll_win32_release.vpc"
        "../vpc_scripts/source_video_base.vpc"
        "../vpc_scripts/source_win32_base.vpc"
        "../vpc_scripts/version.vpc"
        "studiorender.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
        ${Header_Files}
        ${Public_Header_Files}
        ${Source_Files}
        ${VPC_Scripts}
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
        TARGET_NAME_DEBUG "studiorender"
        TARGET_NAME_RELEASE "studiorender"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
        )
set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
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
        "DLLNAME=studiorender;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "STUDIORENDER_EXPORTS;"
        "PROTECTED_THINGS_ENABLE;"
        "fopen=dont_use_fopen;"
        "USE_SDL;"
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
            /Zi;
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
            /Zm750;
            /Gw;
            /Zc:inline;
            /Zc:threadSafeInit-;
            /Wv:18;
            /GS;
            /Zc:forScope
            )
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /NODEFAULTLIB:libcpmt;
            /NODEFAULTLIB:libcpmt1;
            /NOLOGO;
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
            /MANIFEST:NO;
            /DEBUG:FASTLINK;
            /SAFESEH:NO;
            /SUBSYSTEM:WINDOWS;
            /DYNAMICBASE:NO;
            /ignore:4221;
            )
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        Bzip2
        Dmxloader
        appframework
        bitmap
        mathlib
        matsys_controls
        replay_common
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vstdlib
        vtf
        zlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        Bzip2
        Dmxloader
        appframework
        bitmap
        mathlib
        matsys_controls
        replay_common
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vstdlib
        vtf
        zlib

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/common/win32/2015/release;"

        )

