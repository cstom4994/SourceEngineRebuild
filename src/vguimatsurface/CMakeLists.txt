set(PROJECT_NAME vguimatsurface)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../vgui2/src/vgui_key_translation.h"
        "Clip2D.h"
        "Cursor.h"
        "FontTextureCache.h"
        "Input.h"
        "MatSystemSurface.h"
        "memorybitmap.h"
        "TextureDictionary.h"
        "vguimatsurface.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
        "../common/vgui_surfacelib/FontAmalgam.h"
        "../common/vgui_surfacelib/FontManager.h"
        "../common/vgui_surfacelib/Win32Font.h"
        "../public/appframework/IAppSystem.h"
        "../public/filesystem.h"
        "../public/filesystem_helpers.h"
        "../public/materialsystem/imaterial.h"
        "../public/materialsystem/imaterialsystem.h"
        "../public/materialsystem/imaterialvar.h"
        "../public/materialsystem/imesh.h"
        "../public/materialsystem/itexture.h"
        "../public/mathlib/vector.h"
        "../public/mathlib/vector2d.h"
        "../public/mathlib/vector4d.h"
        "../public/pixelwriter.h"
        "../public/tier0/basetypes.h"
        "../public/tier0/commonmacros.h"
        "../public/tier1/characterset.h"
        "../public/tier1/checksum_crc.h"
        "../public/tier1/interface.h"
        "../public/tier1/strtools.h"
        "../public/tier1/utllinkedlist.h"
        "../public/tier1/utlmemory.h"
        "../public/tier1/utlrbtree.h"
        "../public/tier1/utlvector.h"
        "../public/VGuiMatSurface/IMatSystemSurface.h"
        "../public/vstdlib/vstdlib.h"
        "../public/vtf/vtf.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../common/debug_dll_check.cpp"
        "../public/filesystem_helpers.cpp"
        "../public/tier0/memoverride.cpp"
        "../public/vgui_controls/vgui_controls.cpp"
        "../vgui2/src/vgui_key_translation.cpp"
        "Clip2D.cpp"
        "Cursor.cpp"
        "FontTextureCache.cpp"
        "Input.cpp"
        "MatSystemSurface.cpp"
        "memorybitmap.cpp"
        "TextureDictionary.cpp"
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
        "vguimatsurface.vpc"
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
        TARGET_NAME_DEBUG "vguimatsurface"
        TARGET_NAME_RELEASE "vguimatsurface"
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
        "WIN32;"
        "_WIN32;"
        "_WINDOWS;"
        "_USRDLL;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "PLATFORM_32BITS;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "DLLNAME=vguimatsurface;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "BENCHMARK;"
        "VGUIMATSURFACE_DLL_EXPORT;"
        "GAMEUI_EXPORTS;"
        "DONT_PROTECT_FILEIO_FUNCTIONS;"
        "PROTECTED_THINGS_ENABLE;"
        "fopen=dont_use_fopen;"
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
            /std:c++17;
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
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
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
        bitmap
        mathlib
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vgui_surfacelib
        vstdlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vgui_surfacelib
        vstdlib

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/common;"

        )

