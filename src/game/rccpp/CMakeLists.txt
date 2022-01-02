set(PROJECT_NAME rccpp)

################################################################################
# Source groups
################################################################################
set(Base_Files
        "RuntimeCompiledCPlusPlus/RuntimeCompiler/BuildTool.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeCompiler/Compiler_PlatformWindows.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeCompiler/FileChangeNotifier.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeCompiler/SimpleFileWatcher/FileWatcher.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeCompiler/SimpleFileWatcher/FileWatcherWin32.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeObjectSystem/ObjectFactorySystem/ObjectFactorySystem.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeObjectSystem/SimpleSerializer/SimpleSerializer.cpp"

        "RuntimeCompiledCPlusPlus/RuntimeObjectSystem/ObjectInterfacePerModuleSource.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeObjectSystem/RuntimeObjectSystem.cpp"
        "RuntimeCompiledCPlusPlus/RuntimeObjectSystem/RuntimeObjectSystem_PlatformWindows.cpp"
        )
source_group("Base Files" FILES ${Base_Files})

set(Source_Files
        "imgui/imgui_impl_glfw.h"
        "imgui/imgui_impl_opengl2.h"
        "imgui/imconfig.h"
        "imgui/imgui.h"
        "imgui/imgui_internal.h"
        "RCCppMainLoop.h"
        "StdioLogSystem.h"
        "SystemTable.h"
        "rccpp_interface.h"
        "rccpp_invoke.h"

        "imgui/imgui_impl_glfw.cpp"
        "imgui/imgui_impl_opengl2.cpp"
        "imgui/imgui.cpp"
        "rccpp_interface.cpp"
        "RCCppMainLoop.cpp"
        "StdioLogSystem.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Base_Files}
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
        TARGET_NAME_DEBUG "rccpp"
        TARGET_NAME_RELEASE "rccpp"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/lambdamod/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/lambdamod/bin"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../vgui2/controls;"

        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/lua;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty;"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui;"
        "${CMAKE_CURRENT_SOURCE_DIR}/RuntimeCompiledCPlusPlus/RuntimeObjectSystem;"
        "${CMAKE_CURRENT_SOURCE_DIR}/RuntimeCompiledCPlusPlus/RuntimeCompiler"
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
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "RCCPP_DLL;"
        "VERSION_SAFE_STEAM_API_INTERFACES;"
        "strncpy=use_Q_strncpy_instead;"
        "_snprintf=use_Q_snprintf_instead;"
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
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        Dmxloader
        bitmap
        choreoobjects
        tier0
        tier1
        tier2
        tier3
        mathlib
        vstdlib
        libutilities
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        Dmxloader
        bitmap
        choreoobjects
        tier0
        tier1
        tier2
        tier3
        mathlib
        vstdlib
        libutilities

        steam_api
        glfw3

        "opengl32;"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )

