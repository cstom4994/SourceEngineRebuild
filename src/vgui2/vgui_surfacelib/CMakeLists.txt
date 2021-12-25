set(PROJECT_NAME vgui_surfacelib)

################################################################################
# Source groups
################################################################################
set(Public_Header_Files
    "../../common/vgui_surfacelib/BitmapFont.h"
    "../../common/vgui_surfacelib/FontAmalgam.h"
    "../../common/vgui_surfacelib/FontManager.h"
#    "../../common/vgui_surfacelib/osxfont.h"
    "../../common/vgui_surfacelib/vguifont.h"
    "../../common/vgui_surfacelib/Win32Font.h"
    "../../public/appframework/IAppSystem.h"
    "../../public/mathlib/vector2d.h"
    "../../public/tier0/basetypes.h"
    "../../public/tier1/interface.h"
    "../../public/tier1/strtools.h"
    "../../public/tier1/utlbuffer.h"
    "../../public/tier1/utlmemory.h"
    "../../public/tier1/utlvector.h"
    "../../public/vstdlib/vstdlib.h"
)
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
    "../../common/debug_lib_check.cpp"
    "BitmapFont.cpp"
    "FontAmalgam.cpp"
    "FontEffects.cpp"
    "FontEffects.h"
    "FontManager.cpp"
#    "linuxfont.cpp"
#    "osxfont.cpp"
    "Win32Font.cpp"
#    "Win32Font_x360.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(VPC_Scripts
    "../../vpc_scripts/platform_dirs.vpc"
    "../../vpc_scripts/source_base.vpc"
    "../../vpc_scripts/source_lib_base.vpc"
    "../../vpc_scripts/source_lib_win32_base.vpc"
    "../../vpc_scripts/source_lib_win32_debug.vpc"
    "../../vpc_scripts/source_lib_win32_release.vpc"
    "../../vpc_scripts/source_video_base.vpc"
    "../../vpc_scripts/source_win32_base.vpc"
    "../../vpc_scripts/version.vpc"
    "vgui_surfacelib.vpc"
)
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
    ${Public_Header_Files}
    ${Source_Files}
    ${VPC_Scripts}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "vgui_surfacelib"
    TARGET_NAME_RELEASE "vgui_surfacelib"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../game/bin"
    OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
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
    "_LIB;"
    "_CRT_SECURE_NO_DEPRECATE;"
    "_CRT_NONSTDC_NO_DEPRECATE;"
    "PLATFORM_32BITS;"
    "COMPILER_MSVC32;"
    "COMPILER_MSVC;"
    "_DLL_EXT=.dll;"
    "LIBNAME=vgui_surfacelib;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "_EXTERNAL_DLL_EXT=.dll;"
    "VPCGAMECAPS=VANCE;"
    "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\vgui2\\vgui_surfacelib;"
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
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
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
        /Gw;
        /Zc:inline;
        /Zc:threadSafeInit-;
        /Wv:18;
        /GS;
        /Zc:wchar_t;
        /Zc:forScope;
        
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
endif()

