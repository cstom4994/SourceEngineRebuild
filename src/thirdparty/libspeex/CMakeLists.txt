

set(PROJECT_NAME libspeex)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "libspeex/cb_search.h"
    "libspeex/filters.h"
    "libspeex/filters_sse.h"
    "libspeex/lpc.h"
    "libspeex/lsp.h"
    "libspeex/ltp.h"
    "libspeex/ltp_sse.h"
    "libspeex/math_approx.h"
    "libspeex/misc.h"
    "libspeex/modes.h"
    "libspeex/nb_celp.h"
    "libspeex/quant_lsp.h"
    "libspeex/sb_celp.h"
    "libspeex/stack_alloc.h"
    "libspeex/vbr.h"
    "libspeex/vq.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "libspeex/bits.c"
    "libspeex/cb_search.c"
    "libspeex/exc_10_16_table.c"
    "libspeex/exc_10_32_table.c"
    "libspeex/exc_20_32_table.c"
    "libspeex/exc_5_256_table.c"
    "libspeex/exc_5_64_table.c"
    "libspeex/exc_8_128_table.c"
    "libspeex/filters.c"
    "libspeex/gain_table.c"
    "libspeex/gain_table_lbr.c"
    "libspeex/hexc_10_32_table.c"
    "libspeex/hexc_table.c"
    "libspeex/high_lsp_tables.c"
    "libspeex/lpc.c"
    "libspeex/lsp.c"
    "libspeex/lsp_tables_nb.c"
    "libspeex/ltp.c"
    "libspeex/math_approx.c"
    "libspeex/misc.c"
    "libspeex/modes.c"
    "libspeex/nb_celp.c"
    "libspeex/quant_lsp.c"
    "libspeex/sb_celp.c"
    "libspeex/speex_callbacks.c"
    "libspeex/speex_header.c"
    "libspeex/stereo.c"
    "libspeex/vbr.c"
    "libspeex/vq.c"
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "libspeex"
        TARGET_NAME_RELEASE "libspeex"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "libspeex"
        TARGET_NAME_RELEASE "libspeex"
    )
endif()
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
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_HAS_ITERATOR_DEBUGGING=0;"
            "_DEBUG;"
            "DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "PLATFORM_WINDOWS_PC64;"
    "WIN32;"
    "_WIN32;"
        "PLATFORM_32BITS;"
    "COMPILER_MSVC32;"
        "WINDOWS;"
        "_WINDOWS;"
        "COMPILER_MSVC;"
        "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
        "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
        "_ALLOW_MSC_VER_MISMATCH;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "PLATFORM_32BITS;"
        "_X86_;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "VPC;"
        "_LIB;"
        "LIBNAME=libspeex;"
        "_MBCS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_HAS_ITERATOR_DEBUGGING=0;"
            "_DEBUG;"
            "DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "PLATFORM_32BITS;"
    "COMPILER_MSVC32;"
        "PLATFORM_WINDOWS_PC32;"
        "WIN32;"
    "_WIN32;"
    "WIN32;"
    "_WIN32;"
        "WINDOWS;"
        "_WINDOWS;"
        "COMPILER_MSVC;"
        "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
        "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
        "_ALLOW_MSC_VER_MISMATCH;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"

        "_X86_;"

        "_X86_;"
        "PLATFORM_32BITS;"
        "_I386_;"
        "_I386;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "VPC;"
        "_LIB;"
        "LIBNAME=libspeex;"
        "_MBCS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /RTC1;
                /Gm
            >
            $<$<CONFIG:Release>:
                /O2;
                /Ot;
                /Ob2;
                /Oi;
                /Gy
            >
            /MP;
            /W4;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /TP;
            /fp:fast;
            /GF;
            /GR;
            /errorReport:prompt;
            /Zc:forScope;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Zc:wchar_t;
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /ZI
            >
            $<$<CONFIG:Release>:
                /O2;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                /Ot;
                /Oy-;
                /d2Zi+;
                /Ob2;
                /Oi;
                /Gy
            >
            /MP;
            /W4;
            /TP;
            /fp:fast;
            /wd4316;
            /wd4594;
            /wd4457;
            /wd4456;
            /wd4458;
            /wd4459;
            /wd4624;
            /wd4577;
            /Gw;
            /arch:SSE;
            /GF;
            /GR;
            /errorReport:prompt;
            /Zc:forScope;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Zc:wchar_t;
            /Y-
        )
    endif()
endif()

