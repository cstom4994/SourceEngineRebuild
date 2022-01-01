
set(PROJECT_NAME SDKLauncher)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../common/ConfigManager.h"
        "../public/filesystem_init.h"
        "../public/tier1/interface.h"
        "configs.h"
        "min_footprint_files.h"
        "ModConfigsHelper.h"
        "ModWizard_CopyFiles.h"
        "ModWizard_GetModInfo.h"
        "ModWizard_Intro.h"
        "ModWizard_TemplateOptions.h"
        "SDKLauncherDialog.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Resource_Files
        "icon2.ico"
        "steam.ico"
        "script1.rc"
        )
source_group("Resource Files" FILES ${Resource_Files})

set(Source_Files
        "../common/ConfigManager.cpp"
        "../common/SourceAppInfo.cpp"
        "../public/filesystem_init.cpp"
        "../public/registry.cpp"
        "../public/tier0/memoverride.cpp"
        "../public/vgui_controls/vgui_controls.cpp"
        "configs.cpp"
        "CreateModWizard.cpp"
        "CreateModWizard.h"
        "Main.cpp"
        "min_footprint_files.cpp"
        "ModConfigsHelper.cpp"
        "ModWizard_CopyFiles.cpp"
        "ModWizard_Finished.cpp"
        "ModWizard_GetModInfo.cpp"
        "ModWizard_Intro.cpp"
        "ModWizard_TemplateOptions.cpp"
        "sdklauncher_main.h"
        "SDKLauncherDialog.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Header_Files}
        ${Resource_Files}
        ${Source_Files}
        )

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "SDKLauncher"
        TARGET_NAME_RELEASE "SDKLauncher"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../utils/common"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "DEBUG;"
        "_LIB;"
        "_SCL_SECURE_NO_WARNINGS"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
        "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
        "_ALLOW_MSC_VER_MISMATCH"
        ">"
        ";"
        "WIN32;"
        "_WIN32;"
        "_WINDOWS;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "EXENAME=SDKLauncher;"
        "VERSION_SAFE_STEAM_API_INTERFACES;"
        "USE_SDL;"
        "SOURCE1=1;"
        "_MBCS"
        )

################################################################################
# Compile and link options
################################################################################
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od;
            /ZI;
            /GS
            >
            $<$<CONFIG:Release>:
            /O2;
            /Ob2;
            /Oi;
            /Oy;
            /Gy;
            /Zi;
            /Ot;
            /Zo;
            /GS-
            >
            /MP;
            /std:c++17;
            /GF;
            /arch:SSE2;
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
            /Zc:wchar_t;
            /Zc:forScope;

            )
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /NODEFAULTLIB:libcpmt;
            /NODEFAULTLIB:libcpmt1;
            /DYNAMICBASE:NO;
            /INCREMENTAL
            >
            $<$<CONFIG:Release>:
            /NODEFAULTLIB:libcmtd;
            /NODEFAULTLIB:libcpmtd;
            /NODEFAULTLIB:libcpmtd0;
            /NODEFAULTLIB:libcpmtd1;
            /OPT:REF;
            /OPT:ICF;
            /DYNAMICBASE;
            /INCREMENTAL:NO
            >
            /NODEFAULTLIB:libc;
            /NODEFAULTLIB:libcd;
            /MANIFEST;
            /DEBUG:FASTLINK;
            /SAFESEH:NO;
            /SUBSYSTEM:WINDOWS;
            /NXCOMPAT;
            /ignore:4221
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
        appframework
        Vmpi
        vtf
        bitmap
        mathlib
        Raytrace
        lzma
        fgdlib
        choreoobjects
        matsys_controls
        vgui_controls
        Dmxloader
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        tier0
        tier1
        tier2
        tier3
        vstdlib
        appframework
        Vmpi
        vtf
        bitmap
        mathlib
        Raytrace
        lzma
        fgdlib
        choreoobjects
        matsys_controls
        vgui_controls
        Dmxloader

        steam_api

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "winmm;"
        "rpcrt4"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/public;"
        )

