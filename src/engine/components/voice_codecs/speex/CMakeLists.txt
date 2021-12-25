set(PROJECT_NAME vaudio_speex)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "../../../../public/tier1/interface.h"
    "../../../../public/vaudio/ivaudio.h"
    "VoiceEncoder_Speex.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../../../common/debug_dll_check.cpp"
    "../../../../public/tier0/memoverride.cpp"
    "../../../../minisef/tier1/interface.cpp"
    "../frame_encoder/voice_codec_frame.cpp"
    "VoiceEncoder_Speex.cpp"
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
    TARGET_NAME_DEBUG   "vaudio_speex"
    TARGET_NAME_RELEASE "vaudio_speex"
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
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public/tier0;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public/tier1;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../frame_encoder;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../..;"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/libspeex;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../audio/public"
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
    "DLLNAME=vaudio_speex;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "SPEEX_EXPORTS;"
    "_EXTERNAL_DLL_EXT=.dll;"
    "VPCGAMECAPS=VANCE;"
    "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\engine\\voice_codecs\\speex;"
    "SOURCE1=1;"
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
    source_file_compile_options(../../../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
	libspeex
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
	libspeex

    "shell32;"
    "user32;"
    "advapi32;"
    "gdi32;"
    "comdlg32;"
    "ole32"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/common/win32/2015/release;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/public/."
)

