set(PROJECT_NAME Datamodel)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../public/datamodel/dmelementfactoryhelper.h"
        "../public/datamodel/dmelementhandle.h"
        "clipboardmanager.h"
        "datamodel.h"
        "dependencygraph.h"
        "dmattributeinternal.h"
        "dmelementdictionary.h"
        "DmElementFramework.h"
        "dmserializerbinary.h"
        "dmserializerkeyvalues.h"
        "dmserializerkeyvalues2.h"
        "undomanager.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Interface
        "../public/datamodel/attributeflags.h"
        "../public/datamodel/dmattributetypes.h"
        "../public/datamodel/dmattributevar.h"
        "../public/datamodel/dmehandle.h"
        "../public/datamodel/dmelement.h"
        "../public/datamodel/idatamodel.h"
        )
source_group("Interface" FILES ${Interface})

set(Source_Files
        "../common/debug_lib_check.cpp"
        "clipboardmanager.cpp"
        "datamodel.cpp"
        "dependencygraph.cpp"
        "dmattribute.cpp"
        "dmelement.cpp"
        "dmelementdictionary.cpp"
        "dmelementfactoryhelper.cpp"
        "DmElementFramework.cpp"
        "dmserializerbinary.cpp"
        "dmserializerkeyvalues.cpp"
        "dmserializerkeyvalues2.cpp"
        "undomanager.cpp"
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
        "datamodel.vpc"
        )
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(external
        "../public/appframework/IAppSystem.h"
        "../public/string_t.h"
        "../public/tier0/basetypes.h"
        "../public/tier0/commonmacros.h"
        "../public/tier0/dbg.h"
        "../public/tier0/fasttimer.h"
        "../public/tier0/platform.h"
        "../public/tier0/protected_things.h"
        "../public/tier1/interface.h"
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
        TARGET_NAME_DEBUG "datamodel"
        TARGET_NAME_RELEASE "datamodel"
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
        "LIBNAME=datamodel;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "DATAMODEL_LIB;"
        "_EXTERNAL_DLL_EXT=.dll;"
        "VPCGAMECAPS=VANCE;"
        "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\datamodel;"
        "VPCGAME=tf;"
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
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
endif ()

