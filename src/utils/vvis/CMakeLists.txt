set(PROJECT_NAME Vvis_dll)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../../public/bspfile.h"
        "../../public/bspflags.h"
        "../../public/bsptreedata.h"
        "../../public/cmodel.h"
        "../../public/gamebspfile.h"
        "../../public/mathlib/amd3dx.h"
        "../../public/mathlib/bumpvects.h"
        "../../public/mathlib/mathlib.h"
        "../../public/mathlib/vector.h"
        "../../public/mathlib/vector2d.h"
        "../../public/tier0/basetypes.h"
        "../../public/tier0/commonmacros.h"
        "../../public/tier1/byteswap.h"
        "../../public/tier1/checksum_crc.h"
        "../../public/tier1/checksum_md5.h"
        "../../public/tier1/strtools.h"
        "../../public/tier1/utlbuffer.h"
        "../../public/tier1/utllinkedlist.h"
        "../../public/tier1/utlmemory.h"
        "../../public/tier1/utlrbtree.h"
        "../../public/tier1/utlsymbol.h"
        "../../public/tier1/utlvector.h"
        "../../public/vcollide.h"
        "../../public/vstdlib/vstdlib.h"
        "../../public/wadtypes.h"
        "../common/bsplib.h"
        "../common/cmdlib.h"
        "../common/ISQLDBReplyTarget.h"
        "../common/MySqlDatabase.h"
        "../common/pacifier.h"
        "../common/scriplib.h"
        "../common/threads.h"
        "../common/vmpi_tools_shared.h"
        "../vmpi/vmpi_distribute_work.h"
        "mpivis.h"
        "vis.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../common/debug_dll_check.cpp"
        "../../public/collisionutils.cpp"
        "../../public/filesystem_helpers.cpp"
        "../../public/loadcmdline.cpp"
        "../../public/lumpfiles.cpp"
        "../../public/scratchpad3d.cpp"
        "../../public/zip_utils.cpp"
        "../common/bsplib.cpp"
        "../common/cmdlib.cpp"
        "../common/mpi_stats.cpp"
        "../common/MySqlDatabase.cpp"
        "../common/pacifier.cpp"
        "../common/scratchpad_helpers.cpp"
        "../common/scriplib.cpp"
        "../common/threads.cpp"
        "../common/tools_minidump.cpp"
        "../common/tools_minidump.h"
        "../common/vmpi_tools_shared.cpp"
        "flow.cpp"
        "mpivis.cpp"
        "vvis.cpp"
        "WaterDist.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(VPC_Scripts
        "../../vpc_scripts/loadaddress.vpc"
        "../../vpc_scripts/platform_dirs.vpc"
        "../../vpc_scripts/source_base.vpc"
        "../../vpc_scripts/source_dll_base.vpc"
        "../../vpc_scripts/source_dll_win32_base.vpc"
        "../../vpc_scripts/source_dll_win32_debug.vpc"
        "../../vpc_scripts/source_dll_win32_release.vpc"
        "../../vpc_scripts/source_video_base.vpc"
        "../../vpc_scripts/source_win32_base.vpc"
        "../../vpc_scripts/version.vpc"
        "vvis_dll.vpc"
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
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "vvis_dll"
        TARGET_NAME_RELEASE "vvis_dll"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vmpi;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vmpi/mysql/include"
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
        "DLLNAME=vvis_dll;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "MPI;"
        "VVIS;"
        "PROTECTED_THINGS_DISABLE;"
        "_EXTERNAL_DLL_EXT=.dll;"
        "VPCGAMECAPS=VANCE;"
        "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\utils\\vvis;"
        "SOURCE1=1;"
        "VPCGAME=tf;"
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
        tier3
        vstdlib
        Vmpi
        vtf
        bitmap
        mathlib
        Raytrace
        lzma
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        tier0
        tier1
        tier2
        tier3
        vstdlib
        Vmpi
        vtf
        bitmap
        mathlib
        Raytrace
        lzma


        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "odbc32;"
        "odbccp32;"
        "ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common/win32/2015/release;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public/."
        )

