set(PROJECT_NAME tier1)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../../common/xbox/xboxstubs.h"
        "../../public/datamap.h"
        "../../public/tier1/bitbuf.h"
        "../../public/tier1/byteswap.h"
        "../../public/tier1/callqueue.h"
        "../../public/tier1/characterset.h"
        "../../public/tier1/checksum_crc.h"
        "../../public/tier1/checksum_md5.h"
        "../../public/tier1/checksum_sha1.h"
        "../../public/tier1/CommandBuffer.h"
        "../../public/tier1/convar.h"
        "../../public/tier1/datamanager.h"
        "../../public/tier1/delegates.h"
        "../../public/tier1/diff.h"
        "../../public/tier1/fmtstr.h"
        "../../public/tier1/functors.h"
        "../../public/tier1/generichash.h"
        "../../public/tier1/iconvar.h"
        "../../public/tier1/ilocalize.h"
        "../../public/tier1/interface.h"
        "../../public/tier1/KeyValues.h"
        "../../public/tier1/keyvaluesjson.h"
        "../../public/tier1/kvpacker.h"
        "../../public/tier1/lzmaDecoder.h"
        "../../public/tier1/lzss.h"
        "../../public/tier1/mempool.h"
        "../../public/tier1/memstack.h"
        "../../public/tier1/netadr.h"
        "../../public/tier1/processor_detect.h"
        "../../public/tier1/rangecheckedvar.h"
        "../../public/tier1/refcount.h"
        "../../public/tier1/smartptr.h"
        "../../public/tier1/snappy-sinksource.h"
        "../../public/tier1/snappy.h"
        "../../public/tier1/stringpool.h"
        "../../public/tier1/strtools.h"
        "../../public/tier1/tier1.h"
        "../../public/tier1/tokenreader.h"
        "../../public/tier1/uniqueid.h"
        "../../public/tier1/utlbidirectionalset.h"
        "../../public/tier1/utlbinaryblock.h"
        "../../public/tier1/utlblockmemory.h"
        "../../public/tier1/utlbuffer.h"
        "../../public/tier1/utlbufferutil.h"
        "../../public/tier1/utlcommon.h"
        "../../public/tier1/utldict.h"
        "../../public/tier1/utlenvelope.h"
        "../../public/tier1/utlfixedmemory.h"
        "../../public/tier1/utlhandletable.h"
        "../../public/tier1/utlhash.h"
        "../../public/tier1/utlhashtable.h"
        "../../public/tier1/utllinkedlist.h"
        "../../public/tier1/utlmap.h"
        "../../public/tier1/utlmemory.h"
        "../../public/tier1/utlmultilist.h"
        "../../public/tier1/utlpriorityqueue.h"
        "../../public/tier1/utlqueue.h"
        "../../public/tier1/utlrbtree.h"
        "../../public/tier1/UtlSortVector.h"
        "../../public/tier1/utlstack.h"
        "../../public/tier1/utlstring.h"
        "../../public/tier1/UtlStringMap.h"
        "../../public/tier1/utlsymbol.h"
        "../../public/tier1/utlsymbollarge.h"
        "../../public/tier1/utlvector.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Internal_Header_Files
        "snappy-internal.h"
        "snappy-stubs-internal.h"
        )
source_group("Header Files\\Internal Header Files" FILES ${Header_Files__Internal_Header_Files})

set(LZMA_Decompression_Support
        "../../../thirdparty/lzma/C/7zTypes.h"
        "../../../thirdparty/lzma/C/LzmaDec.c"
        "../../../thirdparty/lzma/C/LzmaDec.h"
        )
source_group("LZMA Decompression Support" FILES ${LZMA_Decompression_Support})

set(Source_Files
        "../../common/debug_lib_check.cpp"
        "bitbuf.cpp"
        "byteswap.cpp"
        "characterset.cpp"
        "checksum_crc.cpp"
        "checksum_md5.cpp"
        "checksum_sha1.cpp"
        "commandbuffer.cpp"
        "convar.cpp"
        "datamanager.cpp"
        "diff.cpp"
        "generichash.cpp"
        "ilocalize.cpp"
        "interface.cpp"
        "KeyValues.cpp"
        "keyvaluesjson.cpp"
        "kvpacker.cpp"
        "lzmaDecoder.cpp"
        "lzss.cpp"
        "mempool.cpp"
        "memstack.cpp"
        "NetAdr.cpp"
        "newbitbuf.cpp"
        #    "pathmatch.cpp"
        "processor_detect.cpp"
        #    "processor_detect_linux.cpp"
        #    "qsort_s.cpp"
        "rangecheckedvar.cpp"
        "reliabletimer.cpp"
        "snappy-sinksource.cpp"
        "snappy-stubs-internal.cpp"
        "snappy.cpp"
        "sparsematrix.cpp"
        "splitstring.cpp"
        "stringpool.cpp"
        "strtools.cpp"
        "strtools_unicode.cpp"
        "tier1.cpp"
        "tokenreader.cpp"
        "uniqueid.cpp"
        "utlbinaryblock.cpp"
        "utlbuffer.cpp"
        "utlbufferutil.cpp"
        "utlstring.cpp"
        "utlsymbol.cpp"
        "interval.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Header_Files}
        ${Header_Files__Internal_Header_Files}
        ${LZMA_Decompression_Support}
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
        TARGET_NAME_DEBUG "tier1"
        TARGET_NAME_RELEASE "tier1"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../game/bin"
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
        "${MYROOTDIR}/../thirdparty/SDL2;"
        "${MYROOTDIR}/public/tier0;"
        "${MYROOTDIR}/public/tier1"
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
        "LIBNAME=tier1;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "TIER1_STATIC_LIB;"
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


endif ()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "Rpcrt4"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

