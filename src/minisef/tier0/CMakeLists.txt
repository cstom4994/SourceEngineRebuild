set(PROJECT_NAME tier0)

################################################################################
# Source groups
################################################################################
set(DESKey
        "DESKey/ALGO.H"
        "DESKey/DK2WIN32.H"
        )
source_group("DESKey" FILES ${DESKey})

set(Header_Files
        "../../public/tier0/basetypes.h"
        "../../public/tier0/commonmacros.h"
        "../../public/tier0/cpumonitoring.h"
        "../../public/tier0/dbg.h"
        "../../public/tier0/dbgflag.h"
        "../../public/tier0/etwprof.h"
        "../../public/tier0/EventMasks.h"
        "../../public/tier0/EventModes.h"
        "../../public/tier0/fasttimer.h"
        "../../public/tier0/ia32detect.h"
        "../../public/tier0/icommandline.h"
        "../../public/tier0/IOCTLCodes.h"
        "../../public/tier0/K8PerformanceCounters.h"
        "../../public/tier0/l2cache.h"
        "../../public/tier0/mem.h"
        "../../public/tier0/memalloc.h"
        "../../public/tier0/memdbgoff.h"
        "../../public/tier0/memdbgon.h"
        "../../public/tier0/minidump.h"
        "../../public/tier0/P4PerformanceCounters.h"
        "../../public/tier0/P5P6PerformanceCounters.h"
        "../../public/tier0/platform.h"
        #    "../../public/tier0/pmc360.h"
        "../../public/tier0/PMELib.h"
        "../../public/tier0/progressbar.h"
        "../../public/tier0/protected_things.h"
        "../../public/tier0/systeminformation.h"
        "../../public/tier0/threadtools.h"
        "../../public/tier0/tslist.h"
        "../../public/tier0/validator.h"
        "../../public/tier0/valobject.h"
        "../../public/tier0/valve_off.h"
        "../../public/tier0/valve_on.h"
        "../../public/tier0/vcr_shared.h"
        "../../public/tier0/vcrmode.h"
        "../../public/tier0/vprof.h"
        "../../public/tier0/wchartypes.h"
        "../../public/tier0/xbox_codeline_defines.h"
        "mem_helpers.h"
        "pch_tier0.h"
        "resource.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Manifest_Files
        "valveetwprovider.man"
        )
source_group("Manifest Files" FILES ${Manifest_Files})

set(Source_Files
        "../../common/debug_dll_check.cpp"
        #    "../../minisef/tier1/pathmatch.cpp"
        "assert_dialog.cpp"
        "commandline.cpp"
        "cpu.cpp"
        #    "cpu_posix.cpp"
        "cpu_usage.cpp"
        "cpumonitoring.cpp"
        "dbg.cpp"
        "dynfunction.cpp"
        "etwprof.cpp"
        "fasttimer.cpp"
        "mem.cpp"
        "mem_helpers.cpp"
        "memdbg.cpp"
        "memstd.cpp"
        "memvalidate.cpp"
        "minidump.cpp"
        "pch_tier0.cpp"
        "platform.cpp"
        #    "platform_posix.cpp"
        #    "pmc360.cpp"
        "pme.cpp"
        #    "pme_posix.cpp"
        "PMELib.cpp"
        "progressbar.cpp"
        "security.cpp"
        "stacktools.cpp"
        "systeminformation.cpp"
        "thread.cpp"
        "threadtools.cpp"
        "tier0_strtools.cpp"
        "tslist.cpp"
        "vcrmode.cpp"
        #    "vcrmode_posix.cpp"
        "vprof.cpp"
        "win32consoleio.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${DESKey}
        ${Header_Files}
        ${Manifest_Files}
        ${Source_Files}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch_tier0.h>"
        )

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "tier0"
        TARGET_NAME_RELEASE "tier0"
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
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/windowssdk"
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
        "WIN32;"
        "_WIN32;"
        "_WINDOWS;"
        "_USRDLL;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "PLATFORM_32BITS;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "_DLL_EXT=.dll;"
        "DLLNAME=tier0;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "TIER0_DLL_EXPORT;"
        "_EXTERNAL_DLL_EXT=.dll;"
        "VPCGAMECAPS=VANCE;"
        "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\tier0;"
        "VPCGAME=tf;"
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
    source_file_compile_options(../../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(PMELib.cpp ${FILE_CL_OPTIONS})
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
            ##        ../../lib/public/ftol3.obj
            )
endif ()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )

