set(PROJECT_NAME Movieobjects)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "movieobjects_interfaces.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Interface
        "../public/movieobjects/dmeanimationlist.h"
        "../public/movieobjects/dmeanimationset.h"
        "../public/movieobjects/dmeattachment.h"
        "../public/movieobjects/dmebalancetostereocalculatoroperator.h"
        "../public/movieobjects/dmebookmark.h"
        "../public/movieobjects/dmecamera.h"
        "../public/movieobjects/dmechannel.h"
        "../public/movieobjects/dmeclip.h"
        "../public/movieobjects/dmecombinationoperator.h"
        "../public/movieobjects/dmedag.h"
        "../public/movieobjects/dmedccmakefile.h"
        "../public/movieobjects/dmedrawsettings.h"
        "../public/movieobjects/dmeeditortypedictionary.h"
        "../public/movieobjects/dmeexpressionoperator.h"
        "../public/movieobjects/dmeeyeball.h"
        "../public/movieobjects/dmeeyeposition.h"
        "../public/movieobjects/dmefaceset.h"
        "../public/movieobjects/dmegamemodel.h"
        "../public/movieobjects/dmegamemodelinput.h"
        "../public/movieobjects/dmeinput.h"
        "../public/movieobjects/dmejoint.h"
        "../public/movieobjects/dmekeyboardinput.h"
        "../public/movieobjects/dmelight.h"
        "../public/movieobjects/dmelog.h"
        "../public/movieobjects/dmemakefile.h"
        "../public/movieobjects/dmemakefileutils.h"
        "../public/movieobjects/dmematerial.h"
        "../public/movieobjects/dmematerialoverlayfxclip.h"
        "../public/movieobjects/dmemdl.h"
        "../public/movieobjects/dmemdlmakefile.h"
        "../public/movieobjects/dmemesh.h"
        "../public/movieobjects/dmemodel.h"
        "../public/movieobjects/dmemorphoperator.h"
        "../public/movieobjects/dmemouseinput.h"
        "../public/movieobjects/dmeoperator.h"
        "../public/movieobjects/dmepackoperators.h"
        "../public/movieobjects/dmeparticlesystemdefinition.h"
        "../public/movieobjects/dmephonememapping.h"
        "../public/movieobjects/dmeselection.h"
        "../public/movieobjects/dmeshape.h"
        "../public/movieobjects/dmesound.h"
        "../public/movieobjects/dmetestmesh.h"
        "../public/movieobjects/dmetimeframe.h"
        "../public/movieobjects/dmetimeselection.h"
        "../public/movieobjects/dmetimeselectiontimes.h"
        "../public/movieobjects/dmetrack.h"
        "../public/movieobjects/dmetrackgroup.h"
        "../public/movieobjects/dmetransform.h"
        "../public/movieobjects/dmetransforminput.h"
        "../public/movieobjects/dmetransformlist.h"
        "../public/movieobjects/dmetransformoperator.h"
        "../public/movieobjects/dmeunpackoperators.h"
        "../public/movieobjects/dmevertexdata.h"
        "../public/movieobjects/dmmeshcomp.h"
        "../public/movieobjects/dmmeshutils.h"
        "../public/movieobjects/dmobjserializer.h"
        "../public/movieobjects/dmsmdserializer.h"
        "../public/movieobjects/idmemakefileutils.h"
        "../public/movieobjects/movieobjects.h"
        "../public/movieobjects/timeutils.h"
        )
source_group("Interface" FILES ${Interface})

set(Source_Files
        "../common/debug_lib_check.cpp"
        "../common/movieobjects/timeutils.cpp"
        "dmeanimationlist.cpp"
        "dmeanimationset.cpp"
        "dmeattachment.cpp"
        "dmebalancetostereocalculatoroperator.cpp"
        "dmebookmark.cpp"
        "dmecamera.cpp"
        "dmechannel.cpp"
        "dmeclip.cpp"
        "dmecombinationoperator.cpp"
        "dmedag.cpp"
        "dmedccmakefile.cpp"
        "dmedrawsettings.cpp"
        "dmeeditortypedictionary.cpp"
        "dmeexpressionoperator.cpp"
        "dmeeyeball.cpp"
        "dmeeyeposition.cpp"
        "dmefaceset.cpp"
        "dmegamemodel.cpp"
        "dmegamemodelinput.cpp"
        "dmeinput.cpp"
        "dmejoint.cpp"
        "dmekeyboardinput.cpp"
        "dmelight.cpp"
        "dmelog.cpp"
        "dmemakefile.cpp"
        "dmemakefileutils.cpp"
        "dmematerial.cpp"
        "dmematerialoverlayfxclip.cpp"
        "dmemdl.cpp"
        "dmemdlmakefile.cpp"
        "dmemesh.cpp"
        "dmemodel.cpp"
        "dmemorphoperator.cpp"
        "dmemouseinput.cpp"
        "dmeoperator.cpp"
        "dmepackoperators.cpp"
        "dmeparticlesystemdefinition.cpp"
        "dmephonememapping.cpp"
        "dmeselection.cpp"
        "dmeshape.cpp"
        "dmesound.cpp"
        "dmetimeframe.cpp"
        "dmetimeselection.cpp"
        "dmetrack.cpp"
        "dmetrackgroup.cpp"
        "dmetransform.cpp"
        "dmetransforminput.cpp"
        "dmetransformlist.cpp"
        "dmetransformoperator.cpp"
        "dmeunpackoperators.cpp"
        "dmevertexdata.cpp"
        "dmmeshcomp.cpp"
        "dmmeshutils.cpp"
        "dmobjserializer.cpp"
        "dmsmdserializer.cpp"
        "movieobjects_interfaces.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(VPC_Scripts
        "../vpc_scripts/platform_dirs.vpc"
        "../vpc_scripts/source_base.vpc"
        "../vpc_scripts/source_lib_base.vpc"
        "../vpc_scripts/source_lib_win32_base.vpc"
        "../vpc_scripts/source_lib_win32_debug.vpc"
        "../vpc_scripts/source_lib_win32_release.vpc"
        "../vpc_scripts/source_video_base.vpc"
        "../vpc_scripts/source_win32_base.vpc"
        "../vpc_scripts/version.vpc"
        "movieobjects.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(external
        "../public/bone_setup.cpp"
        "../public/collisionutils.cpp"
        "../public/mathlib/mathlib.h"
        "../public/mathlib/vector.h"
        "../public/phonemeconverter.cpp"
        "../public/phonemeconverter.h"
        "../public/studio.cpp"
        )
source_group("external" FILES ${external})

set(ALL_FILES
        ${Header_Files}
        ${Interface}
        ${Source_Files}
        ${VPC_Scripts}
        ${external}
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
        TARGET_NAME_DEBUG "movieobjects"
        TARGET_NAME_RELEASE "movieobjects"
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
target_include_directories(${PROJECT_NAME} PUBLIC
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
        "WIN32;"
        "_WIN32;"
        "_LIB;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "PLATFORM_32BITS;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "_DLL_EXT=.dll;"
        "LIBNAME=movieobjects;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "MOVIEOBJECTS_LIB;"
        "_EXTERNAL_DLL_EXT=.dll;"
        "VPCGAMECAPS=VANCE;"
        "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\movieobjects;"
        "SOURCE1=1;"
        "FUCK_STEAM;"
        "VPCGAME=tf;"
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
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
endif ()

