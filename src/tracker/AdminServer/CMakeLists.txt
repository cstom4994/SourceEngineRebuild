set(PROJECT_NAME AdminServer)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "../../common/igameserverdata.h"
    "../../common/ivprofexport.h"
    "../../common/vgui/vgui_basebudgetpanel.h"
    "../../common/vgui/vgui_budgetbargraphpanel.h"
    "../../common/vgui/vgui_budgethistorypanel.h"
    "../../common/vgui/vgui_budgetpanelshared.h"
    "../../public/tier1/interface.h"
    "../../public/tier1/utlbuffer.h"
    "../../public/tier1/utllinkedlist.h"
    "../../public/tier1/utlsymbol.h"
    "../../public/tier1/utlvector.h"
    "../common/IServerRefreshResponse.h"
    "../common/msgbuffer.h"
    "AdminServer.h"
    "BanContextMenu.h"
    "BanPanel.h"
    "BudgetPanelContainer.h"
    "ChatPanel.h"
    "ConfigPanel.h"
    "DialogAddBan.h"
    "DialogCvarChange.h"
    "GamePanelInfo.h"
    "GraphPanel.h"
    "IManageServer.h"
    "MapCycleEditDialog.h"
    "PlayerContextMenu.h"
    "PlayerListCompare.h"
    "PlayerPanel.h"
    "RawLogPanel.h"
    "RemoteServer.h"
    "ServerConfigPanel.h"
    "serverinfopanel.h"
    "TokenLine.h"
    "VarEditDialog.h"
    "VarListPropertyPage.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../common/debug_dll_check.cpp"
    "../../common/vgui/vgui_basebudgetpanel.cpp"
    "../../common/vgui/vgui_budgetbargraphpanel.cpp"
    "../../common/vgui/vgui_budgethistorypanel.cpp"
    "../../common/vgui/vgui_budgetpanelshared.cpp"
    "../../public/tier0/memoverride.cpp"
    "../../public/vgui_controls/vgui_controls.cpp"
    "../common/msgbuffer.cpp"
    "AdminServer.cpp"
    "BanContextMenu.cpp"
    "ConfigPanel.cpp"
    "GamePanelInfo.cpp"
    "MapCycleEditDialog.cpp"
    "PlayerContextMenu.cpp"
    "PlayerListCompare.cpp"
    "RemoteServer.cpp"
    "VarEditDialog.cpp"
    "VarListPropertyPage.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Generic_Dialogs
    "DialogAddBan.cpp"
    "DialogCvarChange.cpp"
)
source_group("Source Files\\Generic Dialogs" FILES ${Source_Files__Generic_Dialogs})

set(Source_Files__Pages
    "BanPanel.cpp"
    "BudgetPanelContainer.cpp"
    "ChatPanel.cpp"
    "GraphPanel.cpp"
    "PlayerPanel.cpp"
    "RawLogPanel.cpp"
    "ServerConfigPanel.cpp"
    "serverinfopanel.cpp"
)
source_group("Source Files\\Pages" FILES ${Source_Files__Pages})

set(Source_Files__Utils
    "TokenLine.cpp"
)
source_group("Source Files\\Utils" FILES ${Source_Files__Utils})

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
    "AdminServer.vpc"
)
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
    ${Source_Files__Generic_Dialogs}
    ${Source_Files__Pages}
    ${Source_Files__Utils}
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
    TARGET_NAME_DEBUG   "AdminServer"
    TARGET_NAME_RELEASE "AdminServer"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../game/bin"
    OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1"
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
    "DLLNAME=AdminServer;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "ADMINSERVER_EXPORTS;"
    "BUDGET_ADMIN_SERVER;"
    "_EXTERNAL_DLL_EXT=.dll;"
    "VPCGAMECAPS=VANCE;"
    "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\tracker\\AdminServer;"
    "SOURCE1=1;"
	"FUCK_STEAM;"
    "VPCGAME=tf;"
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
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    Bzip2
    appframework
    bitmap
    mathlib
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
    appframework
    bitmap
    mathlib
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
    "ole32;"
    "wsock32"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common/win32/2015/release;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public/."
)

