set(PROJECT_NAME Dme_controls)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "../../../../public/dme_controls/AssetBuilder.h"
        "../../../../public/dme_controls/attributeassetpickerpanel.h"
        "../../../../public/dme_controls/AttributeBasePickerPanel.h"
        "../../../../public/dme_controls/AttributeBoolChoicePanel.h"
        "../../../../public/dme_controls/AttributeColorPickerPanel.h"
        "../../../../public/dme_controls/attributedetailtypepickerpanel.h"
        "../../../../public/dme_controls/AttributeElementPanel.h"
        "../../../../public/dme_controls/AttributeElementPickerPanel.h"
        "../../../../public/dme_controls/AttributeFilePickerPanel.h"
        "../../../../public/dme_controls/AttributeIntChoicePanel.h"
        "../../../../public/dme_controls/AttributeInterpolatorChoicePanel.h"
        "../../../../public/dme_controls/AttributeMDLPickerPanel.h"
        "../../../../public/dme_controls/AttributeSequencePickerPanel.h"
        "../../../../public/dme_controls/attributeshaderpickerpanel.h"
        "../../../../public/dme_controls/attributeslider.h"
        "../../../../public/dme_controls/AttributeSoundPickerPanel.h"
        "../../../../public/dme_controls/AttributeStringChoicePanel.h"
        "../../../../public/dme_controls/attributesurfacepropertypickerpanel.h"
        "../../../../public/dme_controls/AttributeTextEntry.h"
        "../../../../public/dme_controls/AttributeTextPanel.h"
        "../../../../public/dme_controls/AttributeWidgetFactory.h"
        "../../../../public/dme_controls/BaseAttributeChoicePanel.h"
        "../../../../public/dme_controls/BaseAttributeDoubleChoicePanel.h"
        "../../../../public/dme_controls/BaseAttributePanel.h"
        "../../../../public/dme_controls/ChannelGraphPanel.h"
        "../../../../public/dme_controls/dmecombinationsystemeditorpanel.h"
        "../../../../public/dme_controls/dmecontrols.h"
        "../../../../public/dme_controls/dmecontrols_utils.h"
        "../../../../public/dme_controls/dmedageditpanel.h"
        "../../../../public/dme_controls/dmedagrenderpanel.h"
        "../../../../public/dme_controls/dmemdlpanel.h"
        "../../../../public/dme_controls/dmepanel.h"
        "../../../../public/dme_controls/dmepicker.h"
        "../../../../public/dme_controls/dmepresetgroupeditorpanel.h"
        "../../../../public/dme_controls/DmeSourceDCCFilePanel.h"
        "../../../../public/dme_controls/DmeSourceSkinPanel.h"
        "../../../../public/dme_controls/ElementPropertiesTree.h"
        "../../../../public/dme_controls/FileListManager.h"
        "../../../../public/dme_controls/filtercombobox.h"
        "../../../../public/dme_controls/inotifyui.h"
        "../../../../public/dme_controls/particlesystempanel.h"
        "../../../../public/dme_controls/particlesystempropertiespanel.h"
        "../../../../public/dme_controls/soundpicker.h"
        "../../../../public/dme_controls/soundrecordpanel.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../../../common/debug_lib_check.cpp"
        "AssetBuilder.cpp"
        "attributeassetpickerpanel.cpp"
        "AttributeBasePickerPanel.cpp"
        "AttributeBoolChoicePanel.cpp"
        "AttributeColorPickerPanel.cpp"
        "attributedetailtypepickerpanel.cpp"
        "AttributeElementPanel.cpp"
        "AttributeElementPickerPanel.cpp"
        "AttributeFilePickerPanel.cpp"
        "AttributeIntChoicePanel.cpp"
        "AttributeInterpolatorChoicePanel.cpp"
        "AttributeMDLPickerPanel.cpp"
        "AttributeSequencePickerPanel.cpp"
        "attributeshaderpickerpanel.cpp"
        "attributeslider.cpp"
        "AttributeSoundPickerPanel.cpp"
        "AttributeStringChoicePanel.cpp"
        "attributesurfacepropertypickerpanel.cpp"
        "AttributeTextEntry.cpp"
        "AttributeTextPanel.cpp"
        "AttributeWidgetFactory.cpp"
        "BaseAttributeChoicePanel.cpp"
        "BaseAttributeDoubleChoicePanel.cpp"
        "BaseAttributePanel.cpp"
        "ChannelGraphPanel.cpp"
        "dmecombinationsystemeditorpanel.cpp"
        "dmecontrols.cpp"
        "dmedageditpanel.cpp"
        "dmedagrenderpanel.cpp"
        "dmelogeditpanel.cpp"
        "dmemdlpanel.cpp"
        "dmepanel.cpp"
        "dmepicker.cpp"
        "dmepresetgroupeditorpanel.cpp"
        "DmeSourceDCCFilePanel.cpp"
        "DmeSourceSkinPanel.cpp"
        "ElementPropertiesTree.cpp"
        "FileListManager.cpp"
        "filtercombobox.cpp"
        "particlesystempanel.cpp"
        "particlesystempropertiespanel.cpp"
        "soundpicker.cpp"
        "soundrecordpanel.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Animation_Set_Editor
        "../../../../public/dme_controls/AnimSetAttributeValue.h"
        "../../../../public/dme_controls/BaseAnimationSetEditor.h"
        "../../../../public/dme_controls/BaseAnimSetAttributeSliderPanel.h"
        "../../../../public/dme_controls/BaseAnimSetControlGroupPanel.h"
        "../../../../public/dme_controls/BaseAnimSetPresetFaderPanel.h"
        "../../../../public/dme_controls/LogPreview.h"
        "../../../../public/dme_controls/presetpicker.h"
        "../../../../public/dme_controls/RecordingState.h"
        "../../../../public/phonemeconverter.cpp"
        "BaseAnimationSetEditor.cpp"
        "BaseAnimSetAttributeSliderPanel.cpp"
        "BaseAnimSetControlGroupPanel.cpp"
        "BaseAnimSetPresetFaderPanel.cpp"
        "presetpicker.cpp"
        )
source_group("Source Files\\Animation Set Editor" FILES ${Source_Files__Animation_Set_Editor})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        ${Source_Files__Animation_Set_Editor}
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
        TARGET_NAME_DEBUG "dme_controls"
        TARGET_NAME_RELEASE "dme_controls"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public/tier0;"
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
        "WIN32;"
        "_WIN32;"
        "_LIB;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "PLATFORM_32BITS;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "LIBNAME=dme_controls;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "DMECONTROLS_LIB;"
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
    source_file_compile_options(../../../../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
endif ()

