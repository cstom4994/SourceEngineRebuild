set(PROJECT_NAME game_shader_dx6)

################################################################################
# Source groups
################################################################################
set(Source_Files
    "../ivprocshader.cpp"
    "../ivprocshader.h"
    "../procshaderinterface.cpp"
    "../procshaderinterface.h"
    "basevsshader.cpp"
    "basevsshader.h"
    "nodeshader.cpp"
    "prev.cpp"
    "procshader.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
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
    TARGET_NAME_DEBUG   "game_shader_dx6"
    TARGET_NAME_RELEASE "game_shader_dx6"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../../game/lambdamod/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../game/lambdamod/bin"
        )
set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY         "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
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
    "${MYROOTDIR}/game/client/shadereditor;"
    "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9;"
    "${CMAKE_CURRENT_SOURCE_DIR}/..;"
    "${MYROOTDIR}/public;"
    "${MYROOTDIR}/public/tier0;"
    "${MYROOTDIR}/public/tier1"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "VPC;"
    "RAD_TELEMETRY_DISABLED;"
    "DLLNAME=game_shader_dx6;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "STDSHADER_DX9_DLL_EXPORT;"
    "FAST_MATERIALVAR_ACCESS;"
    "GAME_SHADER_DLL;"
    "USE_ACTUAL_DX;"
    "SHADER_EDITOR_DLL;"
    "SHADER_EDITOR_DLL_SER;"
    "PROCSHADER_DLL;"
    "SOURCE1=1;"
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
            /Zi;
            /Ot;
            /d2Zi+
        >
        /MP;
        /GF;
        /arch:SSE;
        /TP;
        /fp:fast;
        /GR;
        /Zm200;
        /GS;
        /Zc:forScope;
        /Y-
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /NODEFAULTLIB:libcmtd;
            /OPT:REF;
            /OPT:NOICF;
            /INCREMENTAL:NO
        >
        /NODEFAULTLIB:libc;
        /NODEFAULTLIB:libcd;
        /NOLOGO;
        /MANIFEST:NO;
        /DEBUG;
        /MACHINE:X86;
        /SAFESEH:NO;
        /SUBSYSTEM:WINDOWS;
        /DYNAMICBASE:NO;
        /ignore:4221
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf

        d3d9
        d3dx9



        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "version;"
        "winmm"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/../thirdparty/dxsdk/lib;"
        "${MYROOTDIR}/lib/common;"
        "${MYROOTDIR}/lib/public"
        )
