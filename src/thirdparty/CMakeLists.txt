
add_subdirectory(libspeex)
add_subdirectory(zlib-1.2.5)
add_subdirectory(cryptopp860)
add_subdirectory(bzip2)
add_subdirectory(jpeglib)
add_subdirectory(lzma)
add_subdirectory(protobuf-2.6.1/vsprojects)














set(PROJECT_NAME libutilities)

set(src__lua
        "lua/lapi.c"
        "lua/lapi.h"
        "lua/lauxlib.c"
        "lua/lauxlib.h"
        "lua/lbaselib.c"
        "lua/lbitlib.c"
        "lua/lcode.c"
        "lua/lcode.h"
        "lua/lcorolib.c"
        "lua/lctype.c"
        "lua/lctype.h"
        "lua/ldblib.c"
        "lua/ldebug.c"
        "lua/ldebug.h"
        "lua/ldo.c"
        "lua/ldo.h"
        "lua/ldump.c"
        "lua/lfunc.c"
        "lua/lfunc.h"
        "lua/lgc.c"
        "lua/lgc.h"
        "lua/linit.c"
        "lua/liolib.c"
        "lua/llex.c"
        "lua/llex.h"
        "lua/llimits.h"
        "lua/lmathlib.c"
        "lua/lmem.c"
        "lua/lmem.h"
        "lua/loadlib.c"
        "lua/lobject.c"
        "lua/lobject.h"
        "lua/lopcodes.c"
        "lua/lopcodes.h"
        "lua/loslib.c"
        "lua/lparser.c"
        "lua/lparser.h"
        "lua/lprefix.h"
        "lua/lstate.c"
        "lua/lstate.h"
        "lua/lstring.c"
        "lua/lstring.h"
        "lua/lstrlib.c"
        "lua/ltable.c"
        "lua/ltable.h"
        "lua/ltablib.c"
        "lua/ltm.c"
        "lua/ltm.h"
        "lua/lua.h"
        "lua/lua.hpp"
        "lua/luaconf.h"
        "lua/lualib.h"
        "lua/lundump.c"
        "lua/lundump.h"
        "lua/lutf8lib.c"
        "lua/lvm.c"
        "lua/lvm.h"
        "lua/lzio.c"
        "lua/lzio.h"
        )
source_group("src\\lua" FILES ${src__lua})

set(ALL_FILES
        ${src__lua}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libs")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE libutilities)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG       "libutilities_d"
        TARGET_NAME_RELEASE     "libutilities"
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
        MultiThreaded
        )
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lua;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../."
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
        "DEV_BUILD;"
        "_DLL_EXT=.dll;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING;"
        "WINDOWS_IGNORE_PACKING_MISMATCH;"
        "HAVE_STAT;"
        "HAVE_STDINT_H;"
        "WITHOUT_ICONV_FILTER;"
        "FMT_LOCALE;"
        "LUA_COMPAT_ALL;"
        "LUA_COMPAT_5_1;"
        "NO_STEAM"
        )

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /MP;
            /Gm-;
            /Od;
            /RTC1;
            /Gy;
            /W1;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /wd4819;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /diagnostics:caret
            )
    target_link_options(${PROJECT_NAME} PRIVATE
            /SUBSYSTEM:WINDOWS
            )
endif()