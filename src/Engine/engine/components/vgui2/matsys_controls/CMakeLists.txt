set(PROJECT_NAME matsys_controls)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "../../../../public/matsys_controls/assetpicker.h"
    "../../../../public/matsys_controls/baseassetpicker.h"
    "../../../../public/matsys_controls/colorpickerpanel.h"
    "../../../../public/matsys_controls/gamefiletreeview.h"
    "../../../../public/matsys_controls/manipulator.h"
    "../../../../public/matsys_controls/matsyscontrols.h"
    "../../../../public/matsys_controls/mdlpanel.h"
    "../../../../public/matsys_controls/mdlpicker.h"
    "../../../../public/matsys_controls/mdlsequencepicker.h"
    "../../../../public/matsys_controls/picker.h"
    "../../../../public/matsys_controls/potterywheelpanel.h"
    "../../../../public/matsys_controls/proceduraltexturepanel.h"
    "../../../../public/matsys_controls/QCGenerator.h"
    "../../../../public/matsys_controls/sequencepicker.h"
    "../../../../public/matsys_controls/tgapreviewpanel.h"
    "../../../../public/matsys_controls/vmtpanel.h"
    "../../../../public/matsys_controls/vmtpicker.h"
    "../../../../public/matsys_controls/vmtpreviewpanel.h"
    "../../../../public/matsys_controls/vtfpicker.h"
    "../../../../public/matsys_controls/vtfpreviewpanel.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "../../../../common/debug_lib_check.cpp"
    "assetpicker.cpp"
    "baseassetpicker.cpp"
    "colorpickerpanel.cpp"
    "curveeditorpanel.cpp"
    "gamefiletreeview.cpp"
    "manipulator.cpp"
    "matsyscontrols.cpp"
    "mdlpanel.cpp"
    "mdlpicker.cpp"
    "mdlsequencepicker.cpp"
    "picker.cpp"
    "potterywheelpanel.cpp"
    "proceduraltexturepanel.cpp"
    "QCGenerator.cpp"
    "sequencepicker.cpp"
    "tgapreviewpanel.cpp"
    "vmtpanel.cpp"
    "vmtpicker.cpp"
    "vmtpreviewpanel.cpp"
    "vtfpicker.cpp"
    "vtfpreviewpanel.cpp"
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
    TARGET_NAME_DEBUG   "matsys_controls"
    TARGET_NAME_RELEASE "matsys_controls"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../../game/bin"
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
    "${MYROOTDIR}/public/tier0;"
    "../../../../public/tier1"
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
    "LIBNAME=matsys_controls;"
    "BINK_VIDEO;"
    "AVI_VIDEO;"
    "WMV_VIDEO;"
    "DEV_BUILD;"
    "FRAME_POINTER_OMISSION_DISABLED;"
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

endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    bitmap
)

