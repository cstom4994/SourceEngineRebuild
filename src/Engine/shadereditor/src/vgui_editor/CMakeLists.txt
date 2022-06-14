set(PROJECT_NAME vgui_controls_editor)

################################################################################
# Source groups
################################################################################
set(Public_Header_Files
        "../../../public/Color.h"
        "../../../public/filesystem.h"
        "../../../public/filesystem_helpers.h"
        "../../../public/tier0/memdbgoff.h"
        "../../../public/tier0/memdbgon.h"
        "../../../public/tier1/interface.h"
        "../../../public/tier1/KeyValues.h"
        "../../../public/tier1/mempool.h"
        "../../../public/tier1/utlmemory.h"
        "../../../public/tier1/utlrbtree.h"
        "../../../public/tier1/utlvector.h"
        "vgui_controls/analogbar.h"
        "vgui_controls/animatingimagepanel.h"
        "vgui_controls/animationcontroller.h"
        "vgui_controls/bitmapimagepanel.h"
        "vgui_controls/buildgroup.h"
        "vgui_controls/buildmodedialog.h"
        "vgui_controls/button.h"
        "vgui_controls/checkbutton.h"
        "vgui_controls/checkbuttonlist.h"
        "vgui_controls/circularprogressbar.h"
        "vgui_controls/combobox.h"
        "vgui_controls/controllermap.h"
        "vgui_controls/controls.h"
        "vgui_controls/cvartogglecheckbutton.h"
        "vgui_controls/dialogmanager.h"
        "vgui_controls/directoryselectdialog.h"
        "vgui_controls/divider.h"
        "vgui_controls/editablepanel.h"
        "vgui_controls/expandbutton.h"
        "vgui_controls/fileopendialog.h"
        "vgui_controls/fileopenstatemachine.h"
        "vgui_controls/focusnavgroup.h"
        "vgui_controls/frame.h"
        "vgui_controls/graphpanel.h"
        "vgui_controls/html.h"
        "vgui_controls/image.h"
        "vgui_controls/imagelist.h"
        "vgui_controls/imagepanel.h"
        "vgui_controls/inputdialog.h"
        "vgui_controls/keybindinghelpdialog.h"
        "vgui_controls/keybindingmap.h"
        "vgui_controls/keyboardeditordialog.h"
        "vgui_controls/keyrepeat.h"
        "vgui_controls/label.h"
        "vgui_controls/listpanel.h"
        "vgui_controls/listviewpanel.h"
        "vgui_controls/menu.h"
        "vgui_controls/menubar.h"
        "vgui_controls/menubutton.h"
        "vgui_controls/menuitem.h"
        "vgui_controls/messagebox.h"
        "vgui_controls/messagedialog.h"
        "vgui_controls/messagemap.h"
        "vgui_controls/panel.h"
        "vgui_controls/panelanimationvar.h"
        "vgui_controls/panellistpanel.h"
        "vgui_controls/perforcefileexplorer.h"
        "vgui_controls/perforcefilelist.h"
        "vgui_controls/perforcefilelistframe.h"
        "vgui_controls/phandle.h"
        "vgui_controls/progressbar.h"
        "vgui_controls/progressbox.h"
        "vgui_controls/propertydialog.h"
        "vgui_controls/propertypage.h"
        "vgui_controls/propertysheet.h"
        "vgui_controls/querybox.h"
        "vgui_controls/radiobutton.h"
        "vgui_controls/richtext.h"
        "vgui_controls/rotatingprogressbar.h"
        "vgui_controls/savedocumentquery.h"
        "vgui_controls/scalableimagepanel.h"
        "vgui_controls/scrollableeditablepanel.h"
        "vgui_controls/scrollbar.h"
        "vgui_controls/scrollbarslider.h"
        "vgui_controls/sectionedlistpanel.h"
        "vgui_controls/slider.h"
        "vgui_controls/splitter.h"
        "vgui_controls/subrectimage.h"
        "vgui_controls/textentry.h"
        "vgui_controls/textimage.h"
        "vgui_controls/togglebutton.h"
        "vgui_controls/tooltip.h"
        "vgui_controls/toolwindow.h"
        "vgui_controls/treeview.h"
        "vgui_controls/treeviewlistcontrol.h"
        "vgui_controls/urllabel.h"
        "vgui_controls/wizardpanel.h"
        "vgui_controls/wizardsubpanel.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../../../public/filesystem_helpers.cpp"
        "analogbar.cpp"
        "animatingimagepanel.cpp"
        "animationcontroller.cpp"
        "bitmapimagepanel.cpp"
        "buildfactoryhelper.cpp"
        "buildgroup.cpp"
        "buildmodedialog.cpp"
        "button.cpp"
        "checkbutton.cpp"
        "checkbuttonlist.cpp"
        "circularprogressbar.cpp"
        "colorpicker.cpp"
        "combobox.cpp"
        "controllermap.cpp"
        "controls.cpp"
        "cvartogglecheckbutton.cpp"
        "directoryselectdialog.cpp"
        "divider.cpp"
        "editablepanel.cpp"
        "expandbutton.cpp"
        "fileopendialog.cpp"
        "fileopenstatemachine.cpp"
        "focusnavgroup.cpp"
        "frame.cpp"
        "graphpanel.cpp"
        "html.cpp"
        "image.cpp"
        "imagelist.cpp"
        "imagepanel.cpp"
        "inputdialog.cpp"
        "keybindinghelpdialog.cpp"
        "keyboardeditordialog.cpp"
        "keyrepeat.cpp"
        "label.cpp"
        "listpanel.cpp"
        "listviewpanel.cpp"
        "menu.cpp"
        "menubar.cpp"
        "menubutton.cpp"
        "menuitem.cpp"
        "messagebox.cpp"
        "messagedialog.cpp"
        "panel.cpp"
        "panellistpanel.cpp"
        "perforcefileexplorer.cpp"
        "perforcefilelist.cpp"
        "perforcefilelistframe.cpp"
        "progressbar.cpp"
        "progressbox.cpp"
        "promptsimple.cpp"
        "propertydialog.cpp"
        "propertypage.cpp"
        "propertysheet.cpp"
        "querybox.cpp"
        "radiobutton.cpp"
        "richtext.cpp"
        "rotatingprogressbar.cpp"
        "savedocumentquery.cpp"
        "scalableimagepanel.cpp"
        "scrollableeditablepanel.cpp"
        "scrollbar.cpp"
        "scrollbarslider.cpp"
        "sectionedlistpanel.cpp"
        "slider.cpp"
        "splitter.cpp"
        "subrectimage.cpp"
        "textentry.cpp"
        "textimage.cpp"
        "togglebutton.cpp"
        "tokenchannels.cpp"
        "tooltip.cpp"
        "toolwindow.cpp"
        "treeview.cpp"
        "treeviewlistcontrol.cpp"
        "urllabel.cpp"
        "utilities.cpp"
        "wizardpanel.cpp"
        "wizardsubpanel.cpp"
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
        TARGET_NAME_DEBUG "vgui_controls_editor"
        TARGET_NAME_RELEASE "vgui_controls_editor"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${MYROOTDIR}/../../../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../../game/bin"
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
        "${MYROOTDIR}/shadereditor/src/vgui_editor;"
        "${MYROOTDIR}/shadereditor/src/shadereditor;"
        "${MYROOTDIR}/game/client/shadereditor;"
        "${MYROOTDIR}/thirdparty;"
        "${MYROOTDIR}/public;"
        "${MYROOTDIR}/public/tier0;"
        "${MYROOTDIR}/public/tier1;"
        "${MYROOTDIR}/common"
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
        "LIBNAME=vgui_controls_editor;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "SHADER_EDITOR_DLL_SER;"
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
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /Ot;
            /d2Zi+
            >
            /MP;
            /GF;
            /arch:SSE;
            /TP;
            /fp:fast;
            /GR;
            /GS;
            /Zc:wchar_t;
            /Zc:forScope;
    ;
    /Y-
            )
    target_link_options(${PROJECT_NAME} PRIVATE
            /NOLOGO
            )
endif ()

