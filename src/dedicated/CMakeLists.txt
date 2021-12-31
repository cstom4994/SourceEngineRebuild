set(PROJECT_NAME Dedicated)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../common/GameUI/ObjectList.h"
        "../common/IAdminServer.h"
        "../common/IManageServer.h"
        "../common/netapi.h"
        "../common/SteamAppStartup.h"
        "../filesystem/filetracker.h"
        "../filesystem/threadsaferefcountedobject.h"
        "../public/appframework/IAppSystem.h"
        "../public/engine_hlds_api.h"
        "../public/filesystem.h"
        "../public/idedicatedexports.h"
        "../public/ifilelist.h"
        "../public/mathlib/mathlib.h"
        "../public/mathlib/vector.h"
        "../public/mathlib/vector2d.h"
        "../public/string_t.h"
        "../public/tier0/basetypes.h"
        "../public/tier0/commonmacros.h"
        "../public/tier0/dbg.h"
        "../public/tier0/fasttimer.h"
        "../public/tier0/icommandline.h"
        "../public/tier0/platform.h"
        "../public/tier0/protected_things.h"
        "../public/tier0/vcr_shared.h"
        "../public/tier0/vcrmode.h"
        "../public/tier1/interface.h"
        "../public/tier1/strtools.h"
        "../public/vstdlib/vstdlib.h"
        "dedicated.h"
        "isys.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Console_Headers
        "../common/IObjectContainer.h"
        "console/conproc.h"
        "console/textconsole.h"
        "console/TextConsoleWin32.h"
        )
source_group("Header Files\\Console Headers" FILES ${Header_Files__Console_Headers})

set(Header_Files__VGUI_Headers
        "vgui/CreateMultiplayerGameServerPage.h"
        "vgui/MainPanel.h"
        "vgui/vguihelpers.h"
        )
source_group("Header Files\\VGUI Headers" FILES ${Header_Files__VGUI_Headers})

set(Source_Files
        "../common/crypto.cpp"
        "../common/debug_dll_check.cpp"
        "../common/netapi.cpp"
        "../common/SteamAppStartup.cpp"
        "../public/filesystem_init.cpp"
        "../public/tier0/memoverride.cpp"
        "filesystem.cpp"
        "sys_common.cpp"
        "sys_ded.cpp"
        #    "sys_linux.cpp"
        "sys_windows.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Console
        "console/conproc.cpp"
        "console/textconsole.cpp"
        #    "console/TextConsoleUnix.cpp"
        "console/TextConsoleWin32.cpp"
        )
source_group("Source Files\\Console" FILES ${Source_Files__Console})

set(Source_Files__FileSystem
        "../filesystem/basefilesystem.cpp"
        "../filesystem/filesystem_async.cpp"
        "../filesystem/filesystem_stdio.cpp"
        "../filesystem/filetracker.cpp"
        #    "../filesystem/linux_support.cpp"
        "../filesystem/packfile.cpp"
        "../filesystem/QueuedLoader.cpp"
        "../public/zip_utils.cpp"
        )
source_group("Source Files\\FileSystem" FILES ${Source_Files__FileSystem})

set(Source_Files__VGUI
        "../public/vgui_controls/vgui_controls.cpp"
        "vgui/CreateMultiplayerGameServerPage.cpp"
        "vgui/MainPanel.cpp"
        "vgui/vguihelpers.cpp"
        )
source_group("Source Files\\VGUI" FILES ${Source_Files__VGUI})

set(VPC_Scripts
        "../vpc_scripts/loadaddress.vpc"
        "../vpc_scripts/platform_dirs.vpc"
        "../vpc_scripts/source_base.vpc"
        "../vpc_scripts/source_cryptlib_include.vpc"
        "../vpc_scripts/source_dll_base.vpc"
        "../vpc_scripts/source_dll_win32_base.vpc"
        "../vpc_scripts/source_dll_win32_debug.vpc"
        "../vpc_scripts/source_dll_win32_release.vpc"
        "../vpc_scripts/source_video_base.vpc"
        "../vpc_scripts/source_win32_base.vpc"
        "../vpc_scripts/version.vpc"
        "dedicated.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
        ${Header_Files}
        ${Header_Files__Console_Headers}
        ${Header_Files__VGUI_Headers}
        ${Source_Files}
        ${Source_Files__Console}
        ${Source_Files__FileSystem}
        ${Source_Files__VGUI}
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
        TARGET_NAME_DEBUG "dedicated"
        TARGET_NAME_RELEASE "dedicated"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../engine"
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
        "DLLNAME=dedicated;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "DEDICATED;"
        "LAUNCHERONLY;"
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
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../common/crypto.cpp ${FILE_CL_OPTIONS})
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
        appframework
        mathlib
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vpklib
        vstdlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        appframework
        mathlib
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vpklib
        vstdlib

        steam_api

        cryptlib

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "wsock32;"
        "odbc32;"
        "odbccp32;"
        "winmm"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/common;"

        )

