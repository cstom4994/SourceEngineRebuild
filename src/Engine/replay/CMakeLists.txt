set(PROJECT_NAME replay)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../common/engine/idownloadsystem.h"
        "../common/imageutils.h"
        "../common/netmessages.h"
        "../common/replay/ienginereplay.h"
        "../common/replay/rendermovieparams.h"
        "baserecordingsession.h"
        "baserecordingsessionblock.h"
        "baserecordingsessionblockmanager.h"
        "baserecordingsessionmanager.h"
        "basethinker.h"
        "cl_downloader.h"
        "cl_performance_common.h"
        "cl_performancecontroller.h"
        "cl_performancemanager.h"
        "cl_recordingsession.h"
        "cl_recordingsessionblock.h"
        "cl_recordingsessionblockmanager.h"
        "cl_recordingsessionmanager.h"
        "cl_renderqueue.h"
        "cl_replaycontext.h"
        "cl_replaymanager.h"
        "cl_replaymovie.h"
        "cl_replaymoviemanager.h"
        "cl_screenshotmanager.h"
        "cl_sessionblockdownloader.h"
        "cl_sessioninfodownloader.h"
        "compression.h"
        "errorsystem.h"
        "genericpersistentmanager.h"
        "ithinker.h"
        "ithinkmanager.h"
        "managertest.h"
        "replay_dbg.h"
        "replay_reconstructor.h"
        "replaysystem.h"
        "sessioninfoheader.h"
        "shared_replaycontext.h"
        "spew.h"
        "sv_basejob.h"
        "sv_filepublish.h"
        "sv_fileservercleanup.h"
        "sv_publishtest.h"
        "sv_recordingsession.h"
        "sv_recordingsessionblock.h"
        "sv_recordingsessionblockmanager.h"
        "sv_recordingsessionmanager.h"
        "sv_replaycontext.h"
        "sv_sessionblockpublisher.h"
        "sv_sessioninfopublisher.h"
        "sv_sessionpublishmanager.h"
        "sv_sessionrecorder.h"
        "thinkmanager.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
        "../common/replay/iclientreplay.h"
        "../common/replay/iclientreplaycontext.h"
        "../common/replay/iqueryablereplayitem.h"
        "../common/replay/irecordingsession.h"
        "../common/replay/irecordingsessionblockmanager.h"
        "../common/replay/irecordingsessionmanager.h"
        "../common/replay/ireplaycamera.h"
        "../common/replay/ireplaycontext.h"
        "../common/replay/ireplayerrorsystem.h"
        "../common/replay/ireplayfactory.h"
        "../common/replay/ireplaymanager.h"
        "../common/replay/ireplaymovie.h"
        "../common/replay/ireplaymoviemanager.h"
        "../common/replay/ireplaymovierenderer.h"
        "../common/replay/ireplayperformancecontroller.h"
        "../common/replay/ireplayperformancemanager.h"
        "../common/replay/ireplayperformanceplaybackhandler.h"
        "../common/replay/ireplayrenderqueue.h"
        "../common/replay/ireplayscreenshotmanager.h"
        "../common/replay/ireplayscreenshotsystem.h"
        "../common/replay/ireplayserializeable.h"
        "../common/replay/ireplaysessionrecorder.h"
        "../common/replay/ireplaysystem.h"
        "../common/replay/iserverengine.h"
        "../common/replay/iserverreplaycontext.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../common/debug_dll_check.cpp"
        "../common/imageutils.cpp"
        "../common/netmessages.cpp"
        "../public/tier0/memoverride.cpp"
        "baserecordingsession.cpp"
        "baserecordingsessionblock.cpp"
        "baserecordingsessionblockmanager.cpp"
        "baserecordingsessionmanager.cpp"
        "basethinker.cpp"
        "cl_commands.cpp"
        "cl_cvars.cpp"
        "cl_downloader.cpp"
        "cl_performancecontroller.cpp"
        "cl_performancemanager.cpp"
        "cl_recordingsession.cpp"
        "cl_recordingsessionblock.cpp"
        "cl_recordingsessionblockmanager.cpp"
        "cl_recordingsessionmanager.cpp"
        "cl_renderqueue.cpp"
        "cl_replaycontext.cpp"
        "cl_replaymanager.cpp"
        "cl_replaymovie.cpp"
        "cl_replaymoviemanager.cpp"
        "cl_screenshotmanager.cpp"
        "cl_sessionblockdownloader.cpp"
        "cl_sessioninfodownloader.cpp"
        "compression.cpp"
        "errorsystem.cpp"
        "managertest.cpp"
        "replay_dbg.cpp"
        "replay_reconstructor.cpp"
        "replaysystem.cpp"
        "sessioninfoheader.cpp"
        "shared_cvars.cpp"
        "shared_replaycontext.cpp"
        "spew.cpp"
        "sv_basejob.cpp"
        "sv_commands.cpp"
        "sv_cvars.cpp"
        "sv_filepublish.cpp"
        "sv_fileservercleanup.cpp"
        "sv_publishtest.cpp"
        "sv_recordingsession.cpp"
        "sv_recordingsessionblock.cpp"
        "sv_recordingsessionblockmanager.cpp"
        "sv_recordingsessionmanager.cpp"
        "sv_replaycontext.cpp"
        "sv_sessionblockpublisher.cpp"
        "sv_sessioninfopublisher.cpp"
        "sv_sessionpublishmanager.cpp"
        "sv_sessionrecorder.cpp"
        "thinkmanager.cpp"
        )
source_group("Source Files" FILES ${Source_Files})



set(replay_common.lib_headers
        "../common/replay/performance.h"
        "../common/replay/replay.h"
        "../common/replay/replaylib.h"
        "../common/replay/replaytime.h"
        "../common/replay/replayutils.h"
        "../common/replay/screenshot.h"
        "../common/replay/shared_defs.h"
        )
source_group("replay_common.lib headers" FILES ${replay_common.lib_headers})

set(ALL_FILES
        ${Header_Files}
        ${Public_Header_Files}
        ${Source_Files}
        ${replay_common.lib_headers}
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
        TARGET_NAME_DEBUG "replay"
        TARGET_NAME_RELEASE "replay"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../game/bin"
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
        "${MYROOTDIR}/common;"
        "${MYROOTDIR}/public;"
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
        "DLLNAME=replay;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "REPLAY_DLL;"
        "REPLAY_ENABLED;"
        "CURL_STATICLIB;"
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
        Bzip2
        bitmap
        lzma
        mathlib
        replay_common
        tier0
        tier1
        tier2
        vstdlib
        vtf
        zlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        Bzip2
        bitmap
        lzma
        mathlib
        replay_common
        tier0
        tier1
        tier2
        vstdlib
        vtf
        zlib

        Jpeglib


        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/lib/common;"

        )

