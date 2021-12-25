
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME re2)

################################################################################
# Source groups
################################################################################

set(src__thirdparty__re2__re2
        "../../thirdparty/re2/re2/bitmap256.h"
        "../../thirdparty/re2/re2/bitstate.cc"
        "../../thirdparty/re2/re2/compile.cc"
        "../../thirdparty/re2/re2/dfa.cc"
        "../../thirdparty/re2/re2/filtered_re2.cc"
        "../../thirdparty/re2/re2/filtered_re2.h"
        "../../thirdparty/re2/re2/mimics_pcre.cc"
        "../../thirdparty/re2/re2/nfa.cc"
        "../../thirdparty/re2/re2/onepass.cc"
        "../../thirdparty/re2/re2/parse.cc"
        "../../thirdparty/re2/re2/perl_groups.cc"
        "../../thirdparty/re2/re2/pod_array.h"
        "../../thirdparty/re2/re2/prefilter.cc"
        "../../thirdparty/re2/re2/prefilter.h"
        "../../thirdparty/re2/re2/prefilter_tree.cc"
        "../../thirdparty/re2/re2/prefilter_tree.h"
        "../../thirdparty/re2/re2/prog.cc"
        "../../thirdparty/re2/re2/prog.h"
        "../../thirdparty/re2/re2/re2.cc"
        "../../thirdparty/re2/re2/re2.h"
        "../../thirdparty/re2/re2/regexp.cc"
        "../../thirdparty/re2/re2/regexp.h"
        "../../thirdparty/re2/re2/set.cc"
        "../../thirdparty/re2/re2/set.h"
        "../../thirdparty/re2/re2/simplify.cc"
        "../../thirdparty/re2/re2/sparse_array.h"
        "../../thirdparty/re2/re2/sparse_set.h"
        "../../thirdparty/re2/re2/stringpiece.cc"
        "../../thirdparty/re2/re2/stringpiece.h"
        "../../thirdparty/re2/re2/tostring.cc"
        "../../thirdparty/re2/re2/unicode_casefold.cc"
        "../../thirdparty/re2/re2/unicode_casefold.h"
        "../../thirdparty/re2/re2/unicode_groups.cc"
        "../../thirdparty/re2/re2/unicode_groups.h"
        "../../thirdparty/re2/re2/walker-inl.h"
        )
source_group("src\\thirdparty\\re2\\re2" FILES ${src__thirdparty__re2__re2})

set(src__thirdparty__re2__util
        "../../thirdparty/re2/util/flags.h"
        "../../thirdparty/re2/util/logging.h"
        "../../thirdparty/re2/util/malloc_counter.h"
        "../../thirdparty/re2/util/mix.h"
        "../../thirdparty/re2/util/mutex.h"
        "../../thirdparty/re2/util/pcre.cc"
        "../../thirdparty/re2/util/pcre.h"
        "../../thirdparty/re2/util/rune.cc"
        "../../thirdparty/re2/util/strutil.cc"
        "../../thirdparty/re2/util/strutil.h"
        "../../thirdparty/re2/util/utf.h"
        "../../thirdparty/re2/util/util.h"
        )
source_group("src\\thirdparty\\re2\\util" FILES ${src__thirdparty__re2__util})

set(ALL_FILES
        ${src__thirdparty__re2__re2}
        ${src__thirdparty__re2__util}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE re2)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "re2"
        TARGET_NAME_DEVELOPMENT "re2"
        TARGET_NAME_RELEASE "re2"
        )

################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
        )
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)

string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreaded
        )

set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../game/shared;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../utils/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/Include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/re2"
        )


################################################################################
# Compile definitions
################################################################################

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "DEBUG;"
        "_DEBUG;"
        "ZLIB_DEBUG"
        ">"
        "$<$<CONFIG:Development>:"
        "NDEBUG;"
        "_NDEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "_NDEBUG"
        ">"
        "COMPILER_MSVC32;"
        "PLATFORM_WINDOWS_PC32;"
        "WIN32;"
        "_WIN32;"
        "WINDOWS;"
        "_WINDOWS;"
        "NOMINMAX;"
        "COMPILER_MSVC;"
        "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
        "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
        "_ALLOW_MSC_VER_MISMATCH;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "_X86_;"
        "_x86_;"
        "PLATFORM_32BITS;"
        "_I386_;"
        "_I386;"
        "DEV_BUILD;"
        "_DLL_EXT=.dll;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "VPC;"
        "_USRDLL;"
        "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING;"
        "WINDOWS_IGNORE_PACKING_MISMATCH;"
        "HAVE_STAT;"
        "HAVE_STDINT_H;"
        "EASTL_OPENSOURCE=1;"
        "WITHOUT_ICONV_FILTER;"
        "FMT_LOCALE;"
        "LUA_COMPAT_ALL;"
        "LUA_COMPAT_5_1;"
        "NO_STEAM"
        )


################################################################################
# Compile and link options
################################################################################

target_compile_options(${PROJECT_NAME} PRIVATE
        /MP;
        /Gm-;
        /Od;
        /RTC1;
        /Gy;

        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        /wd4819;
        /bigobj;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /diagnostics:caret
        )

target_link_options(${PROJECT_NAME} PRIVATE
        /SUBSYSTEM:WINDOWS
        )
