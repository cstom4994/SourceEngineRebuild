
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME shadercompile_standalone)

################################################################################
# Source groups
################################################################################

set(src__MaterialSystem__shadercompile
        "../../utils/shadercompile_standalone/basetypes.h"
        "../../utils/shadercompile_standalone/cfgprocessor.cpp"
        "../../utils/shadercompile_standalone/cfgprocessor.h"
        "../../utils/shadercompile_standalone/cmdsink.h"
        "../../utils/shadercompile_standalone/d3dxfxc.cpp"
        "../../utils/shadercompile_standalone/d3dxfxc.h"
        "../../utils/shadercompile_standalone/LZMA.hpp"
        "../../utils/shadercompile_standalone/movingaverage.hpp"
        "../../utils/shadercompile_standalone/shader_vcs_version.h"
        "../../utils/shadercompile_standalone/ShaderCompile.cpp"
        "../../utils/shadercompile_standalone/shadercompile.h"
        "../../utils/shadercompile_standalone/shaderparser.cpp"
        "../../utils/shadercompile_standalone/shaderparser.h"
        "../../utils/shadercompile_standalone/strmanip.hpp"
        "../../utils/shadercompile_standalone/termcolors.hpp"
        "../../utils/shadercompile_standalone/utlbuffer.cpp"
        "../../utils/shadercompile_standalone/utlbuffer.h"
        "../../utils/shadercompile_standalone/utlintrusivelist.h"
        "../../utils/shadercompile_standalone/utlmemory.h"
        "../../utils/shadercompile_standalone/utlnodehash.h"
        "../../utils/shadercompile_standalone/utlstringmap.h"
        "../../utils/shadercompile_standalone/utlsymbol.cpp"
        "../../utils/shadercompile_standalone/utlsymbol.h"
        )
source_group("src\\MaterialSystem\\shadercompile" FILES ${src__MaterialSystem__shadercompile})

set(src__MaterialSystem__shadercompile__inc
        "../../utils/shadercompile_standalone/inc/CRC32.hpp"
        "../../utils/shadercompile_standalone/inc/ezOptionParser.hpp"
        "../../utils/shadercompile_standalone/inc/jsoncpp.cpp"
        "../../utils/shadercompile_standalone/inc/robin_hood.h"
        )
source_group("src\\MaterialSystem\\shadercompile\\inc" FILES ${src__MaterialSystem__shadercompile__inc})

set(src__MaterialSystem__shadercompile__inc__C
        #    "../../utils/shadercompile_standalone/inc/C/7z.h"
        #    "../../utils/shadercompile_standalone/inc/C/7zAlloc.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zAlloc.h"
        #    "../../utils/shadercompile_standalone/inc/C/7zArcIn.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zBuf.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zBuf.h"
        #    "../../utils/shadercompile_standalone/inc/C/7zBuf2.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zCrc.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zCrc.h"
        #    "../../utils/shadercompile_standalone/inc/C/7zCrcOpt.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zDec.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zFile.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zFile.h"
        #    "../../utils/shadercompile_standalone/inc/C/7zStream.c"
        #    "../../utils/shadercompile_standalone/inc/C/7zTypes.h"
        #    "../../utils/shadercompile_standalone/inc/C/7zVersion.h"
        #    "../../utils/shadercompile_standalone/inc/C/Aes.c"
        #    "../../utils/shadercompile_standalone/inc/C/Aes.h"
        #    "../../utils/shadercompile_standalone/inc/C/AesOpt.c"
        #    "../../utils/shadercompile_standalone/inc/C/Alloc.c"
        #    "../../utils/shadercompile_standalone/inc/C/Alloc.h"
        #    "../../utils/shadercompile_standalone/inc/C/Bcj2.c"
        #    "../../utils/shadercompile_standalone/inc/C/Bcj2.h"
        #    "../../utils/shadercompile_standalone/inc/C/Bra.c"
        #    "../../utils/shadercompile_standalone/inc/C/Bra.h"
        #    "../../utils/shadercompile_standalone/inc/C/Bra86.c"
        #    "../../utils/shadercompile_standalone/inc/C/BraIA64.c"
        #    "../../utils/shadercompile_standalone/inc/C/Compiler.h"
        #    "../../utils/shadercompile_standalone/inc/C/CpuArch.c"
        #    "../../utils/shadercompile_standalone/inc/C/CpuArch.h"
        #    "../../utils/shadercompile_standalone/inc/C/Delta.c"
        #    "../../utils/shadercompile_standalone/inc/C/Delta.h"
        #    "../../utils/shadercompile_standalone/inc/C/LzFind.c"
        #    "../../utils/shadercompile_standalone/inc/C/LzFind.h"
        #    "../../utils/shadercompile_standalone/inc/C/LzFindMt.c"
        #    "../../utils/shadercompile_standalone/inc/C/LzFindMt.h"
        #    "../../utils/shadercompile_standalone/inc/C/LzHash.h"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma2Dec.c"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma2Dec.h"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma2Enc.c"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma2Enc.h"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma86.h"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma86Dec.c"
        #    "../../utils/shadercompile_standalone/inc/C/Lzma86Enc.c"
        #    "../../utils/shadercompile_standalone/inc/C/LzmaDec.c"
        #    "../../utils/shadercompile_standalone/inc/C/LzmaDec.h"
        #    "../../utils/shadercompile_standalone/inc/C/LzmaEnc.c"
        #    "../../utils/shadercompile_standalone/inc/C/LzmaEnc.h"
        #    "../../utils/shadercompile_standalone/inc/C/LzmaLib.c"
        #    "../../utils/shadercompile_standalone/inc/C/LzmaLib.h"
        #    "../../utils/shadercompile_standalone/inc/C/MtCoder.c"
        #    "../../utils/shadercompile_standalone/inc/C/MtCoder.h"
        #    "../../utils/shadercompile_standalone/inc/C/Ppmd.h"
        #    "../../utils/shadercompile_standalone/inc/C/Ppmd7.c"
        #    "../../utils/shadercompile_standalone/inc/C/Ppmd7.h"
        #    "../../utils/shadercompile_standalone/inc/C/Ppmd7Dec.c"
        #    "../../utils/shadercompile_standalone/inc/C/Ppmd7Enc.c"
        #    "../../utils/shadercompile_standalone/inc/C/Precomp.h"
        #    "../../utils/shadercompile_standalone/inc/C/RotateDefs.h"
        #    "../../utils/shadercompile_standalone/inc/C/Sha256.c"
        #    "../../utils/shadercompile_standalone/inc/C/Sha256.h"
        #    "../../utils/shadercompile_standalone/inc/C/Sort.c"
        #    "../../utils/shadercompile_standalone/inc/C/Sort.h"
        #    "../../utils/shadercompile_standalone/inc/C/Threads.c"
        #    "../../utils/shadercompile_standalone/inc/C/Threads.h"
        #    "../../utils/shadercompile_standalone/inc/C/Xz.c"
        #    "../../utils/shadercompile_standalone/inc/C/Xz.h"
        #    "../../utils/shadercompile_standalone/inc/C/XzCrc64.c"
        #    "../../utils/shadercompile_standalone/inc/C/XzCrc64.h"
        #    "../../utils/shadercompile_standalone/inc/C/XzCrc64Opt.c"
        #    "../../utils/shadercompile_standalone/inc/C/XzDec.c"
        #    "../../utils/shadercompile_standalone/inc/C/XzEnc.c"
        #    "../../utils/shadercompile_standalone/inc/C/XzEnc.h"
        #    "../../utils/shadercompile_standalone/inc/C/XzIn.c"
        )
source_group("src\\MaterialSystem\\shadercompile\\inc\\C" FILES ${src__MaterialSystem__shadercompile__inc__C})

set(src__MaterialSystem__shadercompile__inc__json
        "../../utils/shadercompile_standalone/inc/json/json-forwards.h"
        "../../utils/shadercompile_standalone/inc/json/json.h"
        )
source_group("src\\MaterialSystem\\shadercompile\\inc\\json" FILES ${src__MaterialSystem__shadercompile__inc__json})

set(src__MaterialSystem__shadercompile__inc__termcolor
        "../../utils/shadercompile_standalone/inc/termcolor/style.hpp"
        "../../utils/shadercompile_standalone/inc/termcolor/termcolor.hpp"
        )
source_group("src\\MaterialSystem\\shadercompile\\inc\\termcolor" FILES ${src__MaterialSystem__shadercompile__inc__termcolor})

set(ALL_FILES
        ${src__MaterialSystem__shadercompile}
        ${src__MaterialSystem__shadercompile__inc}
        ${src__MaterialSystem__shadercompile__inc__C}
        ${src__MaterialSystem__shadercompile__inc__json}
        ${src__MaterialSystem__shadercompile__inc__termcolor}
        )

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Shaders")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE shadercompile_standalone)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "shadercompile_standalone"
        TARGET_NAME_DEVELOPMENT "shadercompile_standalone"
        TARGET_NAME_RELEASE "shadercompile_standalone"
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

target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../game/shared;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../utils/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/Include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/re2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../utils/shadercompile_standalone/inc"
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
        /std:c++latest;
        /Gm-;
        /Od;
        /RTC1;
        /Gy;

        /wd4819;
        /bigobj;
        )

target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /DEBUG:FULL
        >
        $<$<CONFIG:Development>:
        /DEBUG:FULL
        >
        /SUBSYSTEM:CONSOLE;
        /INCREMENTAL;
        /SAFESEH:NO
        )


################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
        re2
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "DbgHelp;"
        "winmm;"
        "opengl32;"
        "dsound;"
        "kernel32;"
        "user32;"
        "gdi32;"
        "iphlpapi;"
        "Shlwapi;"
        "wsock32;"
        "ws2_32;"
        "advapi32;"
        "dinput8;"
        "dxguid;"
        "imm32;"
        "bcrypt;"
        "Avrt;"
        "dwmapi;"
        "Version;"
        "Usp10;"
        "userenv;"
        "psapi;"
        "setupapi;"
        "Shell32;"
        "Rpcrt4;"
        "wininet"
        )

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/Lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common/win32"
        )


