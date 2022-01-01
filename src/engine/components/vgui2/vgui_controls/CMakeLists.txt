set(PROJECT_NAME vgui_controls)

################################################################################
# Source groups
################################################################################
set(Public_Header_Files
        "../../../../public/Color.h"
        "../../../../public/filesystem.h"
        "../../../../public/filesystem_helpers.h"
        "../../../../public/tier0/memdbgoff.h"
        "../../../../public/tier0/memdbgon.h"
        "../../../../public/tier1/interface.h"
        "../../../../public/tier1/KeyValues.h"
        "../../../../public/tier1/mempool.h"
        "../../../../public/tier1/utlmemory.h"
        "../../../../public/tier1/utlrbtree.h"
        "../../../../public/tier1/utlvector.h"
        "../../../../public/vgui_controls/AnalogBar.h"
        "../../../../public/vgui_controls/AnimatingImagePanel.h"
        "../../../../public/vgui_controls/AnimationController.h"
        "../../../../public/vgui_controls/BitmapImagePanel.h"
        "../../../../public/vgui_controls/BuildGroup.h"
        "../../../../public/vgui_controls/BuildModeDialog.h"
        "../../../../public/vgui_controls/Button.h"
        "../../../../public/vgui_controls/CheckButton.h"
        "../../../../public/vgui_controls/CheckButtonList.h"
        "../../../../public/vgui_controls/CircularProgressBar.h"
        "../../../../public/vgui_controls/ComboBox.h"
        "../../../../public/vgui_controls/consoledialog.h"
        "../../../../public/vgui_controls/ControllerMap.h"
        "../../../../public/vgui_controls/Controls.h"
        "../../../../public/vgui_controls/cvartogglecheckbutton.h"
        "../../../../public/vgui_controls/DialogManager.h"
        "../../../../public/vgui_controls/DirectorySelectDialog.h"
        "../../../../public/vgui_controls/Divider.h"
        "../../../../public/vgui_controls/EditablePanel.h"
        "../../../../public/vgui_controls/ExpandButton.h"
        "../../../../public/vgui_controls/FileOpenDialog.h"
        "../../../../public/vgui_controls/FileOpenStateMachine.h"
        "../../../../public/vgui_controls/FocusNavGroup.h"
        "../../../../public/vgui_controls/Frame.h"
        "../../../../public/vgui_controls/GraphPanel.h"
        "../../../../public/vgui_controls/HTML.h"
        "../../../../public/vgui_controls/Image.h"
        "../../../../public/vgui_controls/ImageList.h"
        "../../../../public/vgui_controls/ImagePanel.h"
        "../../../../public/vgui_controls/InputDialog.h"
        "../../../../public/vgui_controls/KeyBindingHelpDialog.h"
        "../../../../public/vgui_controls/KeyBindingMap.h"
        "../../../../public/vgui_controls/KeyBoardEditorDialog.h"
        "../../../../public/vgui_controls/KeyRepeat.h"
        "../../../../public/vgui_controls/Label.h"
        "../../../../public/vgui_controls/ListPanel.h"
        "../../../../public/vgui_controls/ListViewPanel.h"
        "../../../../public/vgui_controls/Menu.h"
        "../../../../public/vgui_controls/MenuBar.h"
        "../../../../public/vgui_controls/MenuButton.h"
        "../../../../public/vgui_controls/MenuItem.h"
        "../../../../public/vgui_controls/MessageBox.h"
        "../../../../public/vgui_controls/MessageDialog.h"
        "../../../../public/vgui_controls/MessageMap.h"
        "../../../../public/vgui_controls/Panel.h"
        "../../../../public/vgui_controls/PanelAnimationVar.h"
        "../../../../public/vgui_controls/PanelListPanel.h"
        "../../../../public/vgui_controls/PerforceFileExplorer.h"
        "../../../../public/vgui_controls/PerforceFileList.h"
        "../../../../public/vgui_controls/perforcefilelistframe.h"
        "../../../../public/vgui_controls/PHandle.h"
        "../../../../public/vgui_controls/ProgressBar.h"
        "../../../../public/vgui_controls/ProgressBox.h"
        "../../../../public/vgui_controls/PropertyDialog.h"
        "../../../../public/vgui_controls/PropertyPage.h"
        "../../../../public/vgui_controls/PropertySheet.h"
        "../../../../public/vgui_controls/QueryBox.h"
        "../../../../public/vgui_controls/RadioButton.h"
        "../../../../public/vgui_controls/RichText.h"
        "../../../../public/vgui_controls/RotatingProgressBar.h"
        "../../../../public/vgui_controls/savedocumentquery.h"
        "../../../../public/vgui_controls/ScalableImagePanel.h"
        "../../../../public/vgui_controls/ScrollableEditablePanel.h"
        "../../../../public/vgui_controls/ScrollBar.h"
        "../../../../public/vgui_controls/ScrollBarSlider.h"
        "../../../../public/vgui_controls/SectionedListPanel.h"
        "../../../../public/vgui_controls/Slider.h"
        "../../../../public/vgui_controls/Splitter.h"
        "../../../../public/vgui_controls/subrectimage.h"
        "../../../../public/vgui_controls/TextEntry.h"
        "../../../../public/vgui_controls/TextImage.h"
        "../../../../public/vgui_controls/ToggleButton.h"
        "../../../../public/vgui_controls/Tooltip.h"
        "../../../../public/vgui_controls/ToolWindow.h"
        "../../../../public/vgui_controls/TreeView.h"
        "../../../../public/vgui_controls/TreeViewListControl.h"
        "../../../../public/vgui_controls/URLLabel.h"
        "../../../../public/vgui_controls/WizardPanel.h"
        "../../../../public/vgui_controls/WizardSubPanel.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../../../../common/debug_lib_check.cpp"
        "../../../../public/filesystem_helpers.cpp"
        "../src/vgui_key_translation.cpp"
        "AnalogBar.cpp"
        "AnimatingImagePanel.cpp"
        "AnimationController.cpp"
        "BitmapImagePanel.cpp"
        "BuildFactoryHelper.cpp"
        "BuildGroup.cpp"
        "BuildModeDialog.cpp"
        "Button.cpp"
        "CheckButton.cpp"
        "CheckButtonList.cpp"
        "CircularProgressBar.cpp"
        "ComboBox.cpp"
        "consoledialog.cpp"
        "ControllerMap.cpp"
        "controls.cpp"
        "cvartogglecheckbutton.cpp"
        "DirectorySelectDialog.cpp"
        "Divider.cpp"
        "EditablePanel.cpp"
        "ExpandButton.cpp"
        "FileOpenDialog.cpp"
        "FileOpenStateMachine.cpp"
        "FocusNavGroup.cpp"
        "Frame.cpp"
        "GraphPanel.cpp"
        "HTML.cpp"
        "Image.cpp"
        "ImageList.cpp"
        "ImagePanel.cpp"
        "InputDialog.cpp"
        "KeyBindingHelpDialog.cpp"
        "KeyBoardEditorDialog.cpp"
        "KeyRepeat.cpp"
        "Label.cpp"
        "ListPanel.cpp"
        "ListViewPanel.cpp"
        "Menu.cpp"
        "MenuBar.cpp"
        "MenuButton.cpp"
        "MenuItem.cpp"
        "MessageBox.cpp"
        "MessageDialog.cpp"
        "Panel.cpp"
        "PanelListPanel.cpp"
        "PerforceFileExplorer.cpp"
        "PerforceFileList.cpp"
        "perforcefilelistframe.cpp"
        "ProgressBar.cpp"
        "ProgressBox.cpp"
        "PropertyDialog.cpp"
        "PropertyPage.cpp"
        "PropertySheet.cpp"
        "QueryBox.cpp"
        "RadioButton.cpp"
        "RichText.cpp"
        "RotatingProgressBar.cpp"
        "savedocumentquery.cpp"
        "ScalableImagePanel.cpp"
        "ScrollableEditablePanel.cpp"
        "ScrollBar.cpp"
        "ScrollBarSlider.cpp"
        "SectionedListPanel.cpp"
        "Slider.cpp"
        "Splitter.cpp"
        "subrectimage.cpp"
        "TextEntry.cpp"
        "TextImage.cpp"
        "ToggleButton.cpp"
        "Tooltip.cpp"
        "ToolWindow.cpp"
        "TreeView.cpp"
        "TreeViewListControl.cpp"
        "URLLabel.cpp"
        "WizardPanel.cpp"
        "WizardSubPanel.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Public_Header_Files}
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
        TARGET_NAME_DEBUG "vgui_controls"
        TARGET_NAME_RELEASE "vgui_controls"
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
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/generated_proto;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../thirdparty/protobuf-2.6.1/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../thirdparty;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../thirdparty/cef"
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
        "LIBNAME=vgui_controls;"
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

