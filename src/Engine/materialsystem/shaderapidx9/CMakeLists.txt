set(PROJECT_NAME shaderapidx9)

################################################################################
# Source groups
################################################################################

set(Header_Files
    "colorformatdx8.h"
    "dynamicib.h"
    "dynamicvb.h"
    "hardwareconfig.h"
    "imeshdx8.h"
    "locald3dtypes.h"
    "meshbase.h"
    "recording.h"
    "shaderapibase.h"
    "shaderapidx8.h"
    "shaderapidx8_global.h"
    "shaderdevicebase.h"
    "shaderdevicedx8.h"
    "shadershadowdx8.h"
    "stubd3ddevice.h"
    "texturedx8.h"
#    "textureheap.h"
    "TransitionTable.h"
    "vertexdecl.h"
    "vertexshaderdx8.h"
#    "winutils.h"
    "wmi.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
    "../../public/materialsystem/idebugtextureinfo.h"
    "../../public/materialsystem/ivballoctracker.h"
    "../../public/materialsystem/shader_vcs_version.h"
    "../../public/shaderapi/ishaderapi.h"
    "../../public/shaderapi/IShaderDevice.h"
    "../../public/shaderapi/ishaderdynamic.h"
    "../../public/shaderapi/ishadershadow.h"
    "../../public/shaderapi/ishaderutil.h"
)
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
    "../../common/debug_dll_check.cpp"
    "../../public/filesystem_helpers.cpp"
    "../../public/tier0/memoverride.cpp"
    "colorformatdx8.cpp"
    "cvballoctracker.cpp"
    "hardwareconfig.cpp"
    "meshbase.cpp"
    "meshdx8.cpp"
    "recording.cpp"
    "shaderapibase.cpp"
    "shaderapidx8.cpp"
    "shaderdevicebase.cpp"
    "shaderdevicedx8.cpp"
    "shadershadowdx8.cpp"
    "texturedx8.cpp"
#    "textureheap.cpp"
    "TransitionTable.cpp"
    "vertexdecl.cpp"
    "vertexshaderdx8.cpp"
#    "winutils.cpp"
    "wmi.cpp"
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
    TARGET_NAME_DEBUG   "shaderapidx9"
    TARGET_NAME_RELEASE "shaderapidx9"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../../game/bin"
    OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../game/bin"
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
    "${MYROOTDIR}/common;"
    "${MYROOTDIR}/public;"
    "${MYROOTDIR}/public/tier0;"
    "${MYROOTDIR}/public/tier1;"
    "${MYROOTDIR}/../thirdparty/dxsdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
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
    "DLLNAME=shaderapidx9;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "SHADERAPIDX9;"
    "SHADER_DLL_EXPORT;"
    "PROTECTED_THINGS_ENABLE;"
    "strncpy=use_Q_strncpy_instead;"
    "_snprintf=use_Q_snprintf_instead;"
    "USE_ACTUAL_DX;"
    "SOURCE1=1;"
	"FUCK_STEAM;"
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
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    Bzip2
    bitmap
    mathlib
    tier0
    tier1
    tier2
    vstdlib
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    Bzip2
    bitmap
    mathlib
    tier0
    tier1
    tier2
    vstdlib

	d3d9
	d3dx9

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
    "${MYROOTDIR}/../thirdparty/dxsdk/lib;"
    "${MYROOTDIR}/lib/public"
)

