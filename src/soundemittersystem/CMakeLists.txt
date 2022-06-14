set(PROJECT_NAME SoundEmitterSystem)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "cbase.h"
        "soundemittersystembase.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
        "../public/appframework/IAppSystem.h"
        "../public/Color.h"
        "../public/engine/IEngineSound.h"
        "../public/filesystem.h"
        "../public/irecipientfilter.h"
        "../public/soundchars.h"
        "../public/SoundEmitterSystem/isoundemittersystembase.h"
        "../public/soundflags.h"
        "../public/string_t.h"
        "../public/tier0/basetypes.h"
        "../public/tier0/commonmacros.h"
        "../public/tier0/dbg.h"
        "../public/tier0/fasttimer.h"
        "../public/tier0/icommandline.h"
        "../public/tier0/mem.h"
        "../public/tier0/memdbgoff.h"
        "../public/tier0/memdbgon.h"
        "../public/tier0/platform.h"
        "../public/tier0/protected_things.h"
        "../public/tier1/interface.h"
        "../public/tier1/KeyValues.h"
        "../public/tier1/strtools.h"
        "../public/tier1/utlbuffer.h"
        "../public/tier1/utldict.h"
        "../public/tier1/utlmemory.h"
        "../public/tier1/utlrbtree.h"
        "../public/tier1/utlsymbol.h"
        "../public/tier1/utlvector.h"
        "../public/vstdlib/IKeyValuesSystem.h"
        "../public/vstdlib/random.h"
        "../public/vstdlib/vstdlib.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../common/debug_dll_check.cpp"
        "../public/SoundParametersInternal.cpp"
        "../public/tier0/memoverride.cpp"
        "soundemittersystembase.cpp"
        )
source_group("Source Files" FILES ${Source_Files})



set(ALL_FILES
        ${Header_Files}
        ${Public_Header_Files}
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
        TARGET_NAME_DEBUG "soundemittersystem"
        TARGET_NAME_RELEASE "soundemittersystem"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../../../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../../game/bin"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${MYROOTDIR}/common;"
        "${MYROOTDIR}/public;"
        "${MYROOTDIR}/public/tier0;"
        "${MYROOTDIR}/public/tier1;"
        "${MYROOTDIR}/game/shared"
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
        "DLLNAME=soundemittersystem;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "SOUNDEMITTERSYSTEM_EXPORTS;"
        "PROTECTED_THINGS_ENABLE;"
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
        tier0
        tier1
        vstdlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        tier0
        tier1
        vstdlib

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/lib/common;"

        )

