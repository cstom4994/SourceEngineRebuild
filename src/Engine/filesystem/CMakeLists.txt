set(PROJECT_NAME FileSystem_Stdio)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../public/appframework/IAppSystem.h"
        "../public/bspfile.h"
        "../public/bspflags.h"
        "../public/filesystem.h"
        "../public/filesystem/IQueuedLoader.h"
        "../public/ifilelist.h"
        "../public/keyvaluescompiler.h"
        "../public/mathlib/bumpvects.h"
        "../public/mathlib/mathlib.h"
        "../public/mathlib/vector.h"
        "../public/mathlib/vector2d.h"
        "../public/mathlib/vector4d.h"
        "../public/tier0/basetypes.h"
        "../public/tier0/dbg.h"
        "../public/tier0/fasttimer.h"
        "../public/tier0/platform.h"
        "../public/tier1/characterset.h"
        "../public/tier1/interface.h"
        "../public/tier1/strtools.h"
        "../public/tier1/utlmemory.h"
        "../public/tier1/utlrbtree.h"
        "../public/tier1/utlsymbol.h"
        "../public/tier1/utlvector.h"
        "../public/vstdlib/vstdlib.h"
        "basefilesystem.h"
        "filetracker.h"
        "packfile.h"
        "threadsaferefcountedobject.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../common/crypto.cpp"
        "../common/debug_dll_check.cpp"
        "../public/kevvaluescompiler.cpp"
        "../public/tier0/memoverride.cpp"
        "../public/zip_utils.cpp"
        "basefilesystem.cpp"
        "filesystem_async.cpp"
        "filesystem_stdio.cpp"
        "filetracker.cpp"
        #    "linux_support.cpp"
        "packfile.cpp"
        "QueuedLoader.cpp"
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
        TARGET_NAME_DEBUG "filesystem_stdio"
        TARGET_NAME_RELEASE "filesystem_stdio"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../game/bin"
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
        "${MYROOTDIR}/common;"
        "${MYROOTDIR}/public;"
        "${MYROOTDIR}/public/tier0;"
        "${MYROOTDIR}/public/tier1"
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
        "DLLNAME=filesystem_stdio;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "FILESYSTEM_STDIO_EXPORTS;"
        "DONT_PROTECT_FILEIO_FUNCTIONS;"
        "PROTECTED_THINGS_ENABLE;"
        "SUPPORT_PACKED_STORE;"
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
        tier0
        tier1
        tier2
        vpklib
        vstdlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        tier0
        tier1
        tier2
        vpklib
        vstdlib

        cryptlib

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/lib/public;"
        )

