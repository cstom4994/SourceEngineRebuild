set(PROJECT_NAME Vbsp)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../../public/disp_powerinfo.h"
        "../../public/disp_vertindex.h"
        "../common/scratchpad_helpers.h"
        "boundbox.h"
        "csg.h"
        "ivp.h"
        "detail.h"
        "disp_vbsp.h"
        "disp_ivp.h"
        "faces.h"
        "manifest.h"
        "map.h"
        "materialpatch.h"
        "materialsub.h"
        "vbsp.h"
        "worldvertextransitionfixup.h"
        "writebsp.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Common_header_files
        "../../public/builddisp.h"
        "../../public/chunkfile.h"
        "../../public/filesystem.h"
        "../../public/filesystem_helpers.h"
        "../../public/gamebspfile.h"
        "../../public/tier1/interface.h"
        "../../public/tier1/tokenreader.h"
        "../../public/zip_uncompressed.h"
        "../common/bsplib.h"
        "../common/cmdlib.h"
        "../common/filesystem_tools.h"
        "../common/map_shared.h"
        "../common/pacifier.h"
        "../common/polylib.h"
        "../common/utilmatlib.h"
        "../vmpi/vmpi.h"
        )
source_group("Header Files\\Common header files" FILES ${Header_Files__Common_header_files})

set(Public_Headers
        "../../public/arraystack.h"
        "../../public/bspfile.h"
        "../../public/bspflags.h"
        "../../public/bsptreedata.h"
        "../../public/cmodel.h"
        "../../public/collisionutils.h"
        "../../public/disp_common.h"
        "../../public/iscratchpad3d.h"
        "../../public/mathlib/amd3dx.h"
        "../../public/mathlib/bumpvects.h"
        "../../public/mathlib/mathlib.h"
        "../../public/mathlib/vector.h"
        "../../public/mathlib/vector2d.h"
        "../../public/mathlib/vector4d.h"
        "../../public/mathlib/vmatrix.h"
        "../../public/mathlib/vplane.h"
        "../../public/nmatrix.h"
        "../../public/ntree.h"
        "../../public/nvector.h"
        "../../public/phyfile.h"
        "../../public/scratchpad3d.h"
        "../../public/studio.h"
        "../../public/tier0/basetypes.h"
        "../../public/tier0/commonmacros.h"
        "../../public/tier0/dbg.h"
        "../../public/tier1/byteswap.h"
        "../../public/tier1/utlbuffer.h"
        "../../public/tier1/utllinkedlist.h"
        "../../public/tier1/utlmemory.h"
        "../../public/tier1/utlrbtree.h"
        "../../public/tier1/utlsymbol.h"
        "../../public/tier1/utlvector.h"
        "../../public/vcollide.h"
        "../../public/vphysics_interface.h"
        "../../public/wadtypes.h"
        "../../public/worldsize.h"
        "../common/mstristrip.h"
        "../common/physdll.h"
        "../common/qfiles.h"
        "../common/scriplib.h"
        "../common/threads.h"
        )
source_group("Public Headers" FILES ${Public_Headers})

set(Source_Files
        "../../public/collisionutils.cpp"
        "../../public/disp_common.cpp"
        "../../public/disp_powerinfo.cpp"
        "../../public/loadcmdline.cpp"
        "../../public/lumpfiles.cpp"
        "../../public/scratchpad3d.cpp"
        "../../public/tier0/memoverride.cpp"
        "../../public/zip_utils.cpp"
        "../common/mstristrip.cpp"
        "../common/physdll.cpp"
        "../common/scratchpad_helpers.cpp"
        "../common/utilmatlib.cpp"
        "boundbox.cpp"
        "brushbsp.cpp"
        "csg.cpp"
        "ivp.cpp"
        "cubemap.cpp"
        "detail.cpp"
        "detailobjects.cpp"
        "disp_vbsp.cpp"
        "disp_ivp.cpp"
        "faces.cpp"
        "glfile.cpp"
        "leakfile.cpp"
        "manifest.cpp"
        "map.cpp"
        "materialpatch.cpp"
        "materialsub.cpp"
        "nodraw.cpp"
        "normals.cpp"
        "overlay.cpp"
        "portals.cpp"
        "prtfile.cpp"
        "staticprop.cpp"
        "textures.cpp"
        "tree.cpp"
        "vbsp.cpp"
        "worldvertextransitionfixup.cpp"
        "writebsp.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Common_Files
        "../../public/builddisp.cpp"
        "../../public/chunkfile.cpp"
        "../../public/filesystem_helpers.cpp"
        "../../public/filesystem_init.cpp"
        "../common/bsplib.cpp"
        "../common/cmdlib.cpp"
        "../common/filesystem_tools.cpp"
        "../common/map_shared.cpp"
        "../common/pacifier.cpp"
        "../common/polylib.cpp"
        "../common/scriplib.cpp"
        "../common/threads.cpp"
        "../common/tools_minidump.cpp"
        "../common/tools_minidump.h"
        )
source_group("Source Files\\Common Files" FILES ${Source_Files__Common_Files})

set(VPC_Scripts
        "../../vpc_scripts/loadaddress.vpc"
        "../../vpc_scripts/platform_dirs.vpc"
        "../../vpc_scripts/source_base.vpc"
        "../../vpc_scripts/source_exe_con_base.vpc"
        "../../vpc_scripts/source_exe_con_win32_base.vpc"
        "../../vpc_scripts/source_exe_win_win32_base.vpc"
        "../../vpc_scripts/source_exe_win_win32_debug.vpc"
        "../../vpc_scripts/source_exe_win_win32_release.vpc"
        "../../vpc_scripts/source_win32_base.vpc"
        "../../vpc_scripts/version.vpc"
        "vbsp.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
        ${Header_Files}
        ${Header_Files__Common_header_files}
        ${Public_Headers}
        ${Source_Files}
        ${Source_Files__Common_Files}
        ${VPC_Scripts}
        )

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "vbsp"
        TARGET_NAME_RELEASE "vbsp"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vmpi"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "DISABLE_ETW;"
        "_DEBUG;"
        "DEBUG;"
        "_LIB;"
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
        "EXENAME=vbsp;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "MACRO_MATHLIB;"
        "VBSP;"
        "PROTECTED_THINGS_DISABLE;"
        "SOURCE1=1;"
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
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /NODEFAULTLIB:libcpmt;
            /NODEFAULTLIB:libcpmt1;
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
            /MANIFEST;
            /DEBUG:FASTLINK;
            /SAFESEH:NO;
            /SUBSYSTEM:CONSOLE;
            /DYNAMICBASE:NO;
            /NXCOMPAT;
            /ignore:4221;
            )
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        tier0
        tier1
        tier2
        tier3
        vstdlib
        Vmpi
        vtf
        bitmap
        mathlib
        Raytrace
        fgdlib
        lzma
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        tier0
        tier1
        tier2
        tier3
        vstdlib
        Vmpi
        vtf
        bitmap
        mathlib
        Raytrace
        fgdlib
        lzma


        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "ws2_32;"
        "odbc32;"
        "odbccp32;"
        "winmm"
        )
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

