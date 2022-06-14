set(PROJECT_NAME zlib)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "deflate.h"
    "gzguts.h"
    "inffast.h"
    "inftrees.h"
    "zutil.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "adler32.c"
    "compress.c"
    "crc32.c"
    "deflate.c"
    "gzclose.c"
    "gzlib.c"
    "gzread.c"
    "gzwrite.c"
    "infback.c"
    "inffast.c"
    "inflate.c"
    "inftrees.c"
    "trees.c"
    "uncompr.c"
    "zutil.c"
)
source_group("Source Files" FILES ${Source_Files})



set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
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
    TARGET_NAME_DEBUG   "libz"
    TARGET_NAME_RELEASE "libz"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../../../game/bin"
    OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../../game/bin"
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
    "${MYROOTDIR}/common;"
    "${MYROOTDIR}/public;"
    "${MYROOTDIR}/public/tier0;"
    "${MYROOTDIR}/public/tier1;"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
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
    "LIBNAME=libz;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "_CRT_SECURE_NO_WARNINGS;"
    "SOURCE1=1;"
	"FUCK_STEAM;"
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
        /TC;
        /fp:fast;
        /GR;
        /wd4316;
        /wd4577;
        /wd4091;
        /wd4131;
        /wd4244;
        /wd4127;
        /Gw;
        /Zc:inline;
        /Zc:threadSafeInit-;
        /Wv:18;
        /GS;
        /Zc:wchar_t;
        /Zc:forScope;
        
    )

endif()

