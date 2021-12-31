set(PROJECT_NAME GameUI2)

################################################################################
# Source groups
################################################################################
set(Base_Files
    "../../common/language.cpp"
    "../../public/vgui_controls/vgui_controls.cpp"
)
source_group("Base Files" FILES ${Base_Files})

set(Header_Files
    "igameui2.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../public/tier0/memoverride.cpp"
    "basepanel.cpp"
    "basepanel.h"
    "gameui2_interface.cpp"
    "gameui2_interface.h"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Buttons
    "button_mainmenu.cpp"
    "button_mainmenu.h"
    "button_panel.cpp"
    "button_panel.h"
)
source_group("Source Files\\Buttons" FILES ${Source_Files__Buttons})

set(Source_Files__Main_menu
    "mainmenu.cpp"
    "mainmenu.h"
)
source_group("Source Files\\Main menu" FILES ${Source_Files__Main_menu})

set(Source_Files__Panels
    "panel_options.cpp"
    "panel_options.h"
    "panel_quitgame.cpp"
    "panel_quitgame.h"
)
source_group("Source Files\\Panels" FILES ${Source_Files__Panels})

set(Source_Files__VGUI_2D
    "vgui2d/button2d.cpp"
    "vgui2d/button2d.h"
    "vgui2d/frame2d.cpp"
    "vgui2d/frame2d.h"
    "vgui2d/panel2d.cpp"
    "vgui2d/panel2d.h"
)
source_group("Source Files\\VGUI 2D" FILES ${Source_Files__VGUI_2D})

set(ALL_FILES
    ${Base_Files}
    ${Header_Files}
    ${Source_Files}
    ${Source_Files__Buttons}
    ${Source_Files__Main_menu}
    ${Source_Files__Panels}
    ${Source_Files__VGUI_2D}
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
    TARGET_NAME_DEBUG   "gameui2"
    TARGET_NAME_RELEASE "gameui2"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/mod_hl2mp/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/mod_hl2mp/bin"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../vgui2/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../vgui2/controls"
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
    "DLLNAME=gameui2;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "GAMEUI2_DLL;"
    "VERSION_SAFE_STEAM_API_INTERFACES;"
    "strncpy=use_Q_strncpy_instead;"
    "_snprintf=use_Q_snprintf_instead;"
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
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
        Dmxloader
        bitmap
        choreoobjects
        gcsdk
        mathlib
        matsys_controls
        particles
        replay_common
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vpklib
        vstdlib
        vtf
        zlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        Dmxloader
        bitmap
        choreoobjects
        mathlib
        matsys_controls
        particles
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vpklib
        vstdlib
        vtf
        zlib
        Jpeglib

        steam_api

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "winmm;"
        "wsock32;"
        "Ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )

