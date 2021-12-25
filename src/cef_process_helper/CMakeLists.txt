

set(PROJECT_NAME lambdawars_browser)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "resource.h"
        "stdafx.h"
        "targetver.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "client_app.cpp"
        "client_app.h"
        "process_helper.cpp"
        "render_browser.cpp"
        "render_browser.h"
        "render_browser_helpers.cpp"
        "render_browser_helpers.h"
        "stdafx.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        )

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE cef_process_helper)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/vance/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/vance/bin"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/cef;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "USE_SKIA;"
        "CHROMIUM_BUILD;"
        "ENABLE_GPU=1"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "_CONSOLE"
        ">"
        "WIN32;"
        "UNICODE;"
        "_UNICODE"
        )

################################################################################
# Compile and link options
################################################################################
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od
            >
            $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
            )
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /NODEFAULTLIB:LIBCMT.lib;
            /INCREMENTAL
            >
            $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
            )
endif ()


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
        Jpeglib
        steamemu
        cryptlib
        libprotobuf

        libcef
        libcef_dll_wrapper

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "winmm;"
        "imm32;"
        "wsock32;"
        "Ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/public"
        )


