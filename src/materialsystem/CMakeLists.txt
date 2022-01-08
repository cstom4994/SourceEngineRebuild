set(PROJECT_NAME MaterialSystem)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../public/shaderapi/ishaderutil.h"
        "cmaterial_queuefriendly.h"
        "cmaterialdict.h"
        "cmaterialsystem.h"
        "cmatlightmaps.h"
        "cmatnullrendercontext.h"
        "cmatqueuedrendercontext.h"
        "cmatrendercontext.h"
        "colorspace.h"
        "ctexturecompositor.h"
        "IHardwareConfigInternal.h"
        "imagepacker.h"
        "imaterialinternal.h"
        "imaterialsysteminternal.h"
        "imatrendercontextinternal.h"
        "imorphinternal.h"
        "IShaderSystem.h"
        "itextureinternal.h"
        "materialsystem_global.h"
        "occlusionquerymgr.h"
        "shadersystem.h"
        "texturemanager.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
        "../common/cstringhash.h"
        "../public/appframework/IAppSystem.h"
        "../public/const.h"
        "../public/crtmemdebug.h"
        "../public/filesystem.h"
        "../public/materialsystem/combineoperations.h"
        "../public/materialsystem/IColorCorrection.h"
        "../public/materialsystem/imaterial.h"
        "../public/materialsystem/imaterialproxy.h"
        "../public/materialsystem/imaterialproxyfactory.h"
        "../public/materialsystem/imaterialsystem.h"
        "../public/materialsystem/imaterialsystemhardwareconfig.h"
        "../public/materialsystem/imaterialsystemstub.h"
        "../public/materialsystem/imaterialvar.h"
        "../public/materialsystem/imesh.h"
        "../public/materialsystem/imorph.h"
        "../public/materialsystem/IShader.h"
        "../public/materialsystem/ishaderapi.h"
        "../public/materialsystem/itexture.h"
        "../public/materialsystem/itexturecompositor.h"
        "../public/materialsystem/materialsystem_config.h"
        "../public/mathlib/amd3dx.h"
        "../public/mathlib/bumpvects.h"
        "../public/mathlib/mathlib.h"
        "../public/mathlib/vector.h"
        "../public/mathlib/vector2d.h"
        "../public/mathlib/vector4d.h"
        "../public/mathlib/vmatrix.h"
        "../public/mathlib/vplane.h"
        "../public/pixelwriter.h"
        "../public/renderparm.h"
        "../public/tier0/basetypes.h"
        "../public/tier1/convar.h"
        "../public/tier1/interface.h"
        "../public/tier1/KeyValues.h"
        "../public/tier1/mempool.h"
        "../public/tier1/strtools.h"
        "../public/tier1/utlbuffer.h"
        "../public/tier1/utlmemory.h"
        "../public/tier1/utlrbtree.h"
        "../public/tier1/utlsymbol.h"
        "../public/tier1/utlvector.h"
        "../public/vstdlib/vstdlib.h"
        "../public/vtf/vtf.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../common/debug_dll_check.cpp"
        "../public/filesystem_helpers.cpp"
        "../public/tier0/memoverride.cpp"
        "CColorCorrection.cpp"
        "cmaterial.cpp"
        "cmaterial_queuefriendly.cpp"
        "cmaterialdict.cpp"
        "CMaterialSubRect.cpp"
        "cmaterialsystem.cpp"
        "cmaterialvar.cpp"
        "cmatlightmaps.cpp"
        "cmatnullrendercontext.cpp"
        "cmatqueuedrendercontext.cpp"
        "cmatrendercontext.cpp"
        "colorspace.cpp"
        "ctexture.cpp"
        "ctexturecompositor.cpp"
        "imagepacker.cpp"
        "mat_stub.cpp"
        "materialsystem_global.cpp"
        "morph.cpp"
        "occlusionquerymgr.cpp"
        "pch_materialsystem.cpp"
        "shadersystem.cpp"
        "texturemanager.cpp"
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
        TARGET_NAME_DEBUG "materialsystem"
        TARGET_NAME_RELEASE "materialsystem"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../public/tier1"
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
        "DLLNAME=materialsystem;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "DEFINE_MATERIALSYSTEM_INTERFACE;"
        "MATERIALSYSTEM_EXPORTS;"
        "PROTECTED_THINGS_ENABLE;"
        "strncpy=use_Q_strncpy_instead;"
        "_snprintf=use_Q_snprintf_instead;"
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
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        vstdlib
        vtf


        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/common;"

        )

