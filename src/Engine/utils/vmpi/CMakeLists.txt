set(PROJECT_NAME Vmpi)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../../public/tier1/bitbuf.h"
        "ichannel.h"
        "iphelpers.h"
        "IThreadedTCPSocket.h"
        "loopback_channel.h"
        "messbuf.h"
        "tcpsocket.h"
        "ThreadedTCPSocketEmu.h"
        "threadhelpers.h"
        "vmpi.h"
        "vmpi_defs.h"
        "vmpi_filesystem.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../common/debug_lib_check.cpp"
        "../../public/filesystem_init.cpp"
        "../common/filesystem_tools.cpp"
        "iphelpers.cpp"
        "loopback_channel.cpp"
        "messbuf.cpp"
        "ThreadedTCPSocket.cpp"
        "ThreadedTCPSocketEmu.cpp"
        "threadhelpers.cpp"
        "vmpi.cpp"
        "vmpi_distribute_tracker.cpp"
        "vmpi_distribute_work.cpp"
        "vmpi_distribute_work_default.cpp"
        "vmpi_distribute_work_sdk.cpp"
        "vmpi_filesystem.cpp"
        "vmpi_filesystem_internal.h"
        "vmpi_filesystem_master.cpp"
        "vmpi_filesystem_worker.cpp"
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
        TARGET_NAME_DEBUG "vmpi"
        TARGET_NAME_RELEASE "vmpi"
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
        "${MYROOTDIR}/public/tier1;"
        "${MYROOTDIR}/utils/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/ZLib;"
        "${CMAKE_CURRENT_SOURCE_DIR}"
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
        "LIBNAME=vmpi;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "PROTECTED_THINGS_DISABLE;"
        "MPI;"
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
add_dependencies(${PROJECT_NAME}
        tier0
        vstdlib
        zlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        tier0
        vstdlib
        zlib

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "winmm;"
        "ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/lib/common;"
        "${MYROOTDIR}/lib/public"
        )