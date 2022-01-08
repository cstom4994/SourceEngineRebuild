set(PROJECT_NAME gcsdk)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../../public/gcsdk/enumutils.h"
        "../../public/gcsdk/gcclient.h"
        "../../public/gcsdk/gcclient_sharedobjectcache.h"
        "../../public/gcsdk/gcclientjob.h"
        "../../public/gcsdk/gcclientsdk.h"
        "../../public/gcsdk/gcconstants.h"
        "../../public/gcsdk/gclogger.h"
        "../../public/gcsdk/gcmsg.h"
        "../../public/gcsdk/gcschema.h"
        "../../public/gcsdk/gcsdk.h"
        "../../public/gcsdk/gcsession.h"
        "../../public/gcsdk/gcsystemmsgs.h"
        "../../public/gcsdk/job.h"
        "../../public/gcsdk/jobmgr.h"
        "../../public/gcsdk/jobtime.h"
        "../../public/gcsdk/messagelist.h"
        "../../public/gcsdk/msgbase.h"
        "../../public/gcsdk/msgprotobuf.h"
        "../../public/gcsdk/netpacket.h"
        "../../public/gcsdk/netpacketpool.h"
        "../../public/gcsdk/protobufsharedobject.h"
        "../../public/gcsdk/refcount.h"
        "../../public/gcsdk/sharedobject.h"
        "../../public/gcsdk/sharedobjectcache.h"
        "../../public/gcsdk/workthreadpool.h"
        "stdafx.h"
        "steamextra/clientenums.h"
        "steamextra/gamecoordinator/igamecoordinator.h"
        "steamextra/gamecoordinator/igamecoordinatorhost.h"
        "steamextra/gamecoordinator/igcsqlquery.h"
        "steamextra/gamecoordinator/igcsqlresultsetlist.h"
        "steamextra/misc.h"
        "steamextra/rtime.h"
        "steamextra/tier0/t0constants.h"
        "steamextra/tier1/pearsonshash.h"
        "steamextra/tier1/tsmempool.h"
        "steamextra/tier1/tsmultimempool.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Protobuf_Files
        "gcsdk_gcmessages.proto"
        "gcsystemmsgs.proto"
        "steammessages.proto"
        )
source_group("Protobuf Files" FILES ${Protobuf_Files})

set(Protobuf_Files__Generated_Files
        "generated_proto/gcsdk_gcmessages.pb.cc"
        "generated_proto/gcsdk_gcmessages.pb.h"
        "generated_proto/gcsystemmsgs.pb.cc"
        "generated_proto/gcsystemmsgs.pb.h"
        "generated_proto/steammessages.pb.cc"
        "generated_proto/steammessages.pb.h"
        )
source_group("Protobuf Files\\Generated Files" FILES ${Protobuf_Files__Generated_Files})

set(Source_Files
        #    "../common/debug_lib_check.cpp"
        "../../thirdparty/JSON_parser/JSON_parser.c"
        "gcclient.cpp"
        "gcclient_sharedobjectcache.cpp"
        "gcconstants.cpp"
        "gclogger.cpp"
        "gcmsg.cpp"
        "job.cpp"
        "jobmgr.cpp"
        "jobtime.cpp"
        "messagelist.cpp"
        "msgprotobuf.cpp"
        "netpacket.cpp"
        "netpacketpool.cpp"
        "protobufsharedobject.cpp"
        "sharedobject.cpp"
        "sharedobjectcache.cpp"
        "stdafx.cpp"
        "steamextra/misc.cpp"
        "steamextra/rtime.cpp"
        "steamextra/steamid.cpp"
        "steamextra/tier1/hashglobals.cpp"
        "steamextra/tier1/tsmempool.cpp"
        "steamextra/tier1/tsmultimempool.cpp"
        "webapi_response.cpp"
        "workthreadpool.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(VPC_Scripts
        "../../vpc_scripts/platform_dirs.vpc"
        "../../vpc_scripts/protobuf_builder.vpc"
        "../../vpc_scripts/source_base.vpc"
        "../../vpc_scripts/source_lib_base.vpc"
        "../../vpc_scripts/source_lib_win32_base.vpc"
        "../../vpc_scripts/source_lib_win32_debug.vpc"
        "../../vpc_scripts/source_lib_win32_release.vpc"
        "../../vpc_scripts/source_video_base.vpc"
        "../../vpc_scripts/source_win32_base.vpc"
        "../../vpc_scripts/version.vpc"
        "gcsdk_game.vpc"
        "gcsdk_gcmessages_include.vpc"
        "steammessages_include.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
        ${Header_Files}
        ${Protobuf_Files}
        ${Protobuf_Files__Generated_Files}
        ${Source_Files}
        ${VPC_Scripts}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
        )

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "gcsdk"
        TARGET_NAME_RELEASE "gcsdk"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/generated_proto;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/protobuf-2.6.1/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/steamextra;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/gcsdk;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/JSON_parser;"
        "."
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
        "LIBNAME=gcsdk;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "TF;"
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
            /YlGCSDK_PCH_Symbol;
            /GS;
            /Zc:wchar_t;
            /Zc:forScope;

            )
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(generated_proto/gcsdk_gcmessages.pb.cc ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(generated_proto/gcsystemmsgs.pb.cc ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(generated_proto/steammessages.pb.cc ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../thirdparty/JSON_parser/JSON_parser.c ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(steamextra/steamid.cpp ${FILE_CL_OPTIONS})
endif ()























