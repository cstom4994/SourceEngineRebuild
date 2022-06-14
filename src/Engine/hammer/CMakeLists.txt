set(PROJECT_NAME hammer_dll)

################################################################################
# Source groups
################################################################################
set(Common_Header_Files
        "../common/ConfigManager.h"
        "../public/arraystack.h"
        "../public/bone_setup.h"
        "../public/bspfile.h"
        "../public/bspflags.h"
        "../public/cmodel.h"
        "../public/const.h"
        "../public/fgdlib/entitydefs.h"
        "../public/fgdlib/gdclass.h"
        "../public/fgdlib/helperinfo.h"
        "../public/fgdlib/inputoutput.h"
        "../public/filesystem.h"
        "../public/IHammer.h"
        "../public/mathlib/amd3dx.h"
        "../public/mathlib/bumpvects.h"
        "../public/mathlib/mathlib.h"
        "../public/mathlib/vector.h"
        "../public/mathlib/vector2d.h"
        "../public/mathlib/vector4d.h"
        "../public/mathlib/vmatrix.h"
        "../public/mathlib/vplane.h"
        "../public/ntree.h"
        "../public/studio.h"
        "../public/tier0/basetypes.h"
        "../public/tier1/interface.h"
        "../public/tier1/tokenreader.h"
        "../public/tier1/utlbuffer.h"
        "../public/tier1/utllinkedlist.h"
        "../public/tier1/utlmemory.h"
        "../public/tier1/utlrbtree.h"
        "../public/tier1/utlvector.h"
        "../public/wadtypes.h"
        "../public/worldsize.h"
        "buildnum.h"
        "dispview.h"
        "FilteredComboBox.h"
        "hammerbar.h"
        "helperfactory.h"
        "ibsplightingthread.h"
        "lpreview_thread.h"
        "lprvwindow.h"
        "MapHelper.h"
        "mapsprite.h"
        "osver.h"
        "Render.h"
        "Selection.h"
        "SelectModeDlgBar.h"
        "shellmessagewnd.h"
        "SmoothingGroupMgr.h"
        "sprite.h"
        "subdiv.h"
        "texturesystem.h"
        )
source_group("Common Header Files" FILES ${Common_Header_Files})

set(Resource_Files
        "Hammer.rc"
        "facepaint.cur"
        "res/afx_idi_.ico"
        "res/bitmap1.bmp"
        "res/bmp00001.bmp"
        "res/bmp00002.bmp"
        "res/camera.ico"
        "res/crosshair.cur"
        "res/crosshair.ico"
        "res/cube.bmp"
        "res/cubechec.bmp"
        "res/cur00001.cur"
        "res/cur00002.cur"
        "res/cursor1.cur"
        "res/cursor2.cur"
        "res/cursor3.cur"
        "res/dispedit.bmp"
        "res/entity.cur"
        "res/eyedropper.cur"
        "res/eyedropper.ico"
        "res/forge.ico"
        "res/forgedoc.ico"
        "res/forgemap.bmp"
        "res/gizmoaxis.bmp"
        "res/gizmorotate.bmp"
        "res/gizmoscale.bmp"
        "res/gizmotranslate.bmp"
        "res/handclos.cur"
        "res/handcurs.cur"
        "res/ico00001.ico"
        "res/ico00002.ico"
        "res/ico00003.ico"
        "res/ico00004.ico"
        "res/icon1.ico"
        "res/input.ico"
        "res/input_grey.ico"
        "res/inputbad.ico"
        "res/inputbad_grey.ico"
        "res/magnify.cur"
        "res/mapdoc_n.bmp"
        "res/mapedit.bmp"
        "res/mapedit256.bmp"
        "res/mapeditt.bmp"
        "res/mapopera.bmp"
        "res/newsplash.bmp"
        "res/newtoolbar.bmp"
        "res/ouput.ico"
        "res/output_grey.ico"
        "res/outputbad.ico"
        "res/outputbad_grey.ico"
        "res/paktypes.bmp"
        "res/seltools.bmp"
        "res/set_u.bmp"
        "res/smartclick.cur"
        "res/splash7b.bmp"
        "res/texturew.ico"
        "res/toolbar.bmp"
        "res/toolbar1.bmp"
        "res/treeroot.bmp"
        "res/undoredo.bmp"
        "res/visgroup.bmp"
        "res/wcsplash.bmp"
        )
source_group("Resource Files" FILES ${Resource_Files})

set(Source_Files
        "../common/ConfigManager.cpp"
        "../common/SourceAppInfo.cpp"
        "../public/bone_setup.cpp"
        "../public/builddisp.cpp"
        "../public/builddisp.h"
        "../public/chunkfile.cpp"
        "../public/chunkfile.h"
        "../public/collisionutils.cpp"
        "../public/collisionutils.h"
        "../public/disp_common.cpp"
        "../public/disp_common.h"
        "../public/disp_powerinfo.cpp"
        "../public/filesystem_helpers.cpp"
        "../public/filesystem_init.cpp"
        "../public/interpolatortypes.cpp"
        "../public/ivraddll.h"
        "../public/keyframe/keyframe.cpp"
        "../public/keyframe/keyframe.h"
        "../public/rope_physics.cpp"
        "../public/simple_physics.cpp"
        "../public/studio.cpp"
        "../public/tier0/afxmem_override.cpp"
        "../public/tier0/memoverride.cpp"
        "../public/vgui_controls/vgui_controls.cpp"
        "../utils/common/scriplib.cpp"
        "activeitemlist.h"
        "AnchorMgr.cpp"
        "AnchorMgr.h"
        "anglebox.cpp"
        "anglebox.h"
        "autoselcombo.cpp"
        "autoselcombo.h"
        "axes2.cpp"
        "axes2.h"
        "blockarray.h"
        "boundbox.cpp"
        "boundbox.h"
        "brushops.cpp"
        "brushops.h"
        "bsplighting.cpp"
        "bsplighting.h"
        "bsplightingthread.cpp"
        "bsplightingthread.h"
        "buildnum.cpp"
        "camera.cpp"
        "camera.h"
        "childfrm.cpp"
        "childfrm.h"
        "clipcode.cpp"
        "clipcode.h"
        "clock.cpp"
        "controlbarids.h"
        "createarch.cpp"
        "culltreenode.cpp"
        "culltreenode.h"
        "custommessages.h"
        "DetailObjects.cpp"
        "detailobjects.h"
        "dispmanager.cpp"
        "dispmanager.h"
        "dispmapimagefilter.cpp"
        "dispmapimagefilter.h"
        "disppaint.cpp"
        "disppaint.h"
        "dispsew.cpp"
        "dispsew.h"
        "DispShore.cpp"
        "DispShore.h"
        "dispsubdiv.cpp"
        "dispsubdiv.h"
        "dynamicdialogwnd.cpp"
        "dynamicdialogwnd.h"
        "editgameclass.cpp"
        "editgameclass.h"
        "editgameconfigs.cpp"
        "editgameconfigs.h"
        "editgroups.h"
        "entityconnection.cpp"
        "entityconnection.h"
        "error3d.h"
        "events.cpp"
        "faceedit_disppage.h"
        "faceedit_materialpage.h"
        "faceeditsheet.h"
        "FileChangeWatcher.cpp"
        "FileChangeWatcher.h"
        "filtercontrol.h"
        "FilteredComboBox.cpp"
        "gameconfig.cpp"
        "gameconfig.h"
        "gamepalette.cpp"
        "gamepalette.h"
        "gizmo.cpp"
        "gizmo.h"
        "globalfunctions.h"
        "grouplist.cpp"
        "grouplist.h"
        "hammer.cpp"
        "hammer.h"
        "hammer_mathlib.cpp"
        "hammer_mathlib.h"
        "HammerScene.cpp"
        "HammerScene.h"
        "HammerVGui.cpp"
        "HammerVGui.h"
        "helperfactory.cpp"
        "history.cpp"
        "history.h"
        "ibsplighting.h"
        "iconcombobox.cpp"
        "iconcombobox.h"
        "keyboard.cpp"
        "keyboard.h"
        "listboxex.cpp"
        "listboxex.h"
        "loadsave_map.cpp"
        "loadsave_rmf.cpp"
        "lpreview_thread.cpp"
        "lprvwindow.cpp"
        "mainfrm.cpp"
        "mainfrm.h"
        "makeprefablibrary.cpp"
        "mapdefs.h"
        "Mapdoc.cpp"
        "maperrorsdlg.h"
        "mapinfodlg.h"
        "mappath.cpp"
        "mappath.h"
        "mapview.cpp"
        "mapview.h"
        "mapview2d.cpp"
        "mapview2d.h"
        "mapview2dbase.cpp"
        "mapview2dbase.h"
        "MapView3D.cpp"
        "mapview3d.h"
        "mapviewlogical.cpp"
        "mapviewlogical.h"
        "materialproxyfactory_wc.cpp"
        "materialproxyfactory_wc.h"
        "mdiclientwnd.cpp"
        "mdiclientwnd.h"
        "messagewnd.cpp"
        "messagewnd.h"
        "misc.cpp"
        "ModelBrowser.cpp"
        "ModelBrowser.h"
        "modelfactory.h"
        "mychecklistbox.h"
        "newdoctype.h"
        "newkeyvalue.h"
        "NewVisGroupDlg.h"
        "noise.cpp"
        "objectbar.cpp"
        "objectbar.h"
        "objectpage.h"
        "objectproperties.h"
        "op_entity.h"
        "op_flags.h"
        "op_groups.h"
        "op_input.h"
        "OP_Model.h"
        "op_output.h"
        "optbuild.h"
        "optconfigs.h"
        "optgeneral.h"
        "optionproperties.h"
        "options.cpp"
        "options.h"
        "opttextures.h"
        "optview2d.h"
        "optview3d.h"
        "osver.cpp"
        "pakdoc.h"
        "pakframe.h"
        "pakviewdirec.h"
        "pakviewfiles.h"
        "PopupMenus.h"
        "prefab3d.cpp"
        "prefab3d.h"
        "prefabs.cpp"
        "prefabs.h"
        "ProcessWnd.cpp"
        "processwnd.h"
        "progdlg.h"
        "Render.cpp"
        "Render2D.cpp"
        "render2d.h"
        "Render3DMS.cpp"
        "render3dms.h"
        "RenderUtils.cpp"
        "RenderUtils.h"
        "resource.h"
        "richeditctrlex.cpp"
        "RichEditCtrlEx.h"
        "runcommands.cpp"
        "runcommands.h"
        "runmap.cpp"
        "runmap.h"
        "saveinfo.cpp"
        "saveinfo.h"
        "ScenePreviewDlg.cpp"
        "ScenePreviewDlg.h"
        "searchbox.h"
        "Selection.cpp"
        "shell.h"
        "SoundBrowser.cpp"
        "SoundBrowser.h"
        "soundsystem.cpp"
        "soundsystem.h"
        "splash.cpp"
        "splash.h"
        "sprite.cpp"
        "ssolid.cpp"
        "ssolid.h"
        "statusbarids.h"
        "stdafx.cpp"
        "stdafx.h"
        "stocksolids.cpp"
        "stocksolids.h"
        "StudioModel.cpp"
        "studiomodel.h"
        "targetnamecombo.cpp"
        "targetnamecombo.h"
        "texturebar.h"
        "texturebox.cpp"
        "texturebox.h"
        "texturebrowser.h"
        "textureconverter.cpp"
        "textureconverter.h"
        "texturewindow.cpp"
        "texturewindow.h"
        "titlewnd.cpp"
        "titlewnd.h"
        "tooldefs.h"
        "undowarningdlg.h"
        "VGuiWnd.cpp"
        "VGuiWnd.h"
        "viewersettings.cpp"
        "viewersettings.h"
        "visgroup.cpp"
        "visgroup.h"
        "wndtex.h"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Dialogs
        "archdlg.cpp"
        "archdlg.h"
        "dispdlg.cpp"
        "dispdlg.h"
        "editgroups.cpp"
        "editpathdlg.cpp"
        "editpathdlg.h"
        "editpathnodedlg.cpp"
        "editpathnodedlg.h"
        "editprefabdlg.cpp"
        "editprefabdlg.h"
        "entityhelpdlg.cpp"
        "entityhelpdlg.h"
        "entityreportdlg.cpp"
        "entityreportdlg.h"
        "faceedit_disppage.cpp"
        "faceedit_materialpage.cpp"
        "faceeditsheet.cpp"
        "filtercontrol.cpp"
        "gotobrushdlg.cpp"
        "gotobrushdlg.h"
        "hammerbar.cpp"
        "mapanimationdlg.cpp"
        "mapanimationdlg.h"
        "mapcheckdlg.cpp"
        "mapcheckdlg.h"
        "MapDiffDlg.cpp"
        "MapDiffDlg.h"
        "maperrorsdlg.cpp"
        "mapinfodlg.cpp"
        "materialdlg.cpp"
        "materialdlg.h"
        "newdoctype.cpp"
        "newkeyvalue.cpp"
        "NewVisGroupDlg.cpp"
        "ObjectPage.cpp"
        "objectproperties.cpp"
        "OP_Entity.cpp"
        "op_flags.cpp"
        "op_groups.cpp"
        "op_input.cpp"
        "OP_Model.cpp"
        "op_output.cpp"
        "optbuild.cpp"
        "OPTConfigs.cpp"
        "optgeneral.cpp"
        "optionproperties.cpp"
        "opttextures.cpp"
        "optview2d.cpp"
        "optview3d.cpp"
        "pastespecialdlg.cpp"
        "pastespecialdlg.h"
        "prefabsdlg.cpp"
        "prefabsdlg.h"
        "progdlg.cpp"
        "replacetexdlg.cpp"
        "replacetexdlg.h"
        "runmapcfgdlg.cpp"
        "runmapcfgdlg.h"
        "runmapexpertdlg.cpp"
        "runmapexpertdlg.h"
        "scaleverticesdlg.cpp"
        "scaleverticesdlg.h"
        "SearchReplaceDlg.cpp"
        "SearchReplaceDlg.h"
        "selectentitydlg.cpp"
        "selectentitydlg.h"
        "selectmodedlgbar.cpp"
        "strdlg.cpp"
        "strdlg.h"
        "texturebar.cpp"
        "texturebrowser.cpp"
        "TorusDlg.cpp"
        "torusdlg.h"
        "transformdlg.cpp"
        "transformdlg.h"
        "undowarningdlg.cpp"
        )
source_group("Source Files\\Dialogs" FILES ${Source_Files__Dialogs})

set(Source_Files__Map_classes
        "mapalignedbox.cpp"
        "mapalignedbox.h"
        "mapanimator.cpp"
        "mapanimator.h"
        "mapatom.h"
        "MapAxisHandle.cpp"
        "MapAxisHandle.h"
        "mapclass.cpp"
        "mapclass.h"
        "mapcylinder.cpp"
        "mapcylinder.h"
        "mapdecal.cpp"
        "mapdecal.h"
        "mapdisp.cpp"
        "mapdisp.h"
        "mapdoc.h"
        "MapEntity.cpp"
        "mapentity.h"
        "mapface.cpp"
        "mapface.h"
        "mapfrustum.cpp"
        "mapfrustum.h"
        "mapgroup.cpp"
        "mapgroup.h"
        "maphelper.cpp"
        "mapkeyframe.cpp"
        "mapkeyframe.h"
        "maplight.cpp"
        "maplight.h"
        "maplightcone.cpp"
        "maplightcone.h"
        "mapline.cpp"
        "mapline.h"
        "mapoverlay.cpp"
        "mapoverlay.h"
        "mapoverlaytrans.cpp"
        "mapoverlaytrans.h"
        "mapplayerhullhandle.cpp"
        "mapplayerhullhandle.h"
        "mappoint.cpp"
        "mappoint.h"
        "mappointhandle.cpp"
        "mappointhandle.h"
        "mapquadbounds.cpp"
        "mapquadbounds.h"
        "mapsidelist.cpp"
        "mapsidelist.h"
        "MapSolid.cpp"
        "mapsolid.h"
        "mapsphere.cpp"
        "mapsphere.h"
        "mapsprite.cpp"
        "mapstudiomodel.cpp"
        "mapstudiomodel.h"
        "mapsweptplayerhull.cpp"
        "mapsweptplayerhull.h"
        "mapworld.cpp"
        "mapworld.h"
        )
source_group("Source Files\\Map classes" FILES ${Source_Files__Map_classes})

set(Source_Files__Shell
        "shell.cpp"
        "shellmessagewnd.cpp"
        )
source_group("Source Files\\Shell" FILES ${Source_Files__Shell})

set(Source_Files__Texture/materials_system
        "dummytexture.cpp"
        "dummytexture.h"
        "ieditortexture.h"
        "material.cpp"
        "material.h"
        "texture.cpp"
        "texture.h"
        "TextureSystem.cpp"
        "wadtexture.cpp"
        "wadtexture.h"
        )
source_group("Source Files\\Texture/materials system" FILES ${Source_Files__Texture/materials_system})

set(Source_Files__Tools
        "box3d.cpp"
        "box3d.h"
        "tool3d.cpp"
        "tool3d.h"
        "ToolAxisHandle.cpp"
        "ToolAxisHandle.h"
        "ToolBase.cpp"
        "ToolBlock.cpp"
        "ToolBlock.h"
        "ToolCamera.cpp"
        "ToolCamera.h"
        "ToolClipper.cpp"
        "ToolClipper.h"
        "ToolCordon.cpp"
        "ToolCordon.h"
        "ToolDecal.cpp"
        "ToolDecal.h"
        "tooldisplace.cpp"
        "tooldisplace.h"
        "ToolEntity.cpp"
        "ToolEntity.h"
        "toolinterface.h"
        "ToolMagnify.cpp"
        "ToolMagnify.h"
        "ToolManager.cpp"
        "ToolManager.h"
        "ToolMaterial.cpp"
        "ToolMaterial.h"
        "ToolMorph.cpp"
        "ToolMorph.h"
        "ToolOverlay.cpp"
        "ToolOverlay.h"
        "ToolPickAngles.cpp"
        "ToolPickAngles.h"
        "ToolPickEntity.cpp"
        "ToolPickEntity.h"
        "toolpickface.cpp"
        "toolpickface.h"
        "ToolPointHandle.cpp"
        "ToolPointHandle.h"
        "ToolSelection.cpp"
        "ToolSelection.h"
        "ToolSphere.cpp"
        "ToolSphere.h"
        "toolswepthull.cpp"
        "toolswepthull.h"
        )
source_group("Source Files\\Tools" FILES ${Source_Files__Tools})

set(ALL_FILES
        ${Common_Header_Files}
        ${Resource_Files}
        ${Source_Files}
        ${Source_Files__Dialogs}
        ${Source_Files__Map_classes}
        ${Source_Files__Shell}
        ${Source_Files__Texture/materials_system}
        ${Source_Files__Tools}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
        )

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "hammer_dll"
        TARGET_NAME_RELEASE "hammer_dll"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../../game/bin"
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
        "${MYROOTDIR}/common;"
        "${MYROOTDIR}/public;"
        "${MYROOTDIR}/public/tier0;"
        "${MYROOTDIR}/public/tier1;"
        "${MYROOTDIR}/common/shaderdll;"
        "${MYROOTDIR}/common/iostream;"
        "${MYROOTDIR}/engine;"
        "${MYROOTDIR}/game/shared;"
        "${MYROOTDIR}/utils/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/."
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
        "DLLNAME=hammer_dll;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "VALVE;"
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
            /Ot
            >
            /MP;
            /GF;
            /arch:SSE;
            /W4;
            /WX-;
            /TP;
            /fp:fast;
            /GR;
            /wd4316;
            /wd4594;
            /wd4457;
            /wd4456;
            /wd4458;
            /wd4459;
            /wd4624;
            /wd4577;
            /EHa;
            /GS;
            /Zc:forScope
            )























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
            /NOLOGO;
            /MANIFEST:NO;
            /DEBUG;
            /SAFESEH:NO;
            /SUBSYSTEM:WINDOWS;
            /DYNAMICBASE:NO;
            /ignore:4221
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
        lzma
        fgdlib
        choreoobjects
        matsys_controls
        vgui_controls
        Dmxloader
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
        lzma
        fgdlib
        choreoobjects
        matsys_controls
        vgui_controls
        Dmxloader

        steam_api

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "winmm;"
        "rpcrt4"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/lib/public;"
        )


