set(PROJECT_NAME Newdat)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "../../public/tier0/basetypes.h"
    "../../public/tier0/commonmacros.h"
    "../../public/tier1/checksum_md5.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../public/tier0/memoverride.cpp"
    "newdat.cpp"
)
source_group("Source Files" FILES ${Source_Files})

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
    "newdat.vpc"
)
source_group("VPC Scripts" FILES ${VPC_Scripts})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
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
    TARGET_NAME_DEBUG   "newdat"
    TARGET_NAME_RELEASE "newdat"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../game/bin"
    OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
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
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1"
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
    "WIN32;"
    "_WIN32;"
    "_WINDOWS;"
    "_CRT_SECURE_NO_DEPRECATE;"
    "_CRT_NONSTDC_NO_DEPRECATE;"
    "PLATFORM_32BITS;"
    "COMPILER_MSVC32;"
    "COMPILER_MSVC;"
    "EXENAME=newdat;"
    "_DLL_EXT=.dll;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
    "PROTECTED_THINGS_DISABLE;"
    "_EXTERNAL_DLL_EXT=.dll;"
    "VPCGAMECAPS=VANCE;"
    "PROJECTDIR=E:\\ReCrash\\ProjectRe\\InvadeEngine\\src\\utils\\newdat;"
    "VPCGAME=tf;"
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
endif()

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
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

