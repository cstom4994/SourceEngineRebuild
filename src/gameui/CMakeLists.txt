set(PROJECT_NAME GameUI)

################################################################################
# Source groups
################################################################################
set(Controls
        "../common/GameUI/cvarslider.cpp"
        "../common/GameUI/cvarslider.h"
        "BitmapImagePanel.cpp"
        "BitmapImagePanel.h"
        "CommandCheckButton.cpp"
        "CommandCheckButton.h"
        "CvarNegateCheckButton.cpp"
        "CvarNegateCheckButton.h"
        "CvarTextEntry.cpp"
        "CvarTextEntry.h"
        "CvarToggleCheckButton.cpp"
        "CvarToggleCheckButton.h"
        "HapticControlBox.cpp"
        "HapticControlBox.h"
        "KeyToggleCheckButton.cpp"
        "KeyToggleCheckButton.h"
        "LabeledCommandComboBox.cpp"
        "LabeledCommandComboBox.h"
        "URLButton.cpp"
        "URLButton.h"
        "vcontrolslistpanel.cpp"
        "vcontrolslistpanel.h"
        )
source_group("Controls" FILES ${Controls})

set(Dialogs
        "BaseSaveGameDialog.cpp"
        "BenchmarkDialog.cpp"
        "BenchmarkDialog.h"
        "BonusMapsDialog.cpp"
        "BonusMapsDialog.h"
        "ChangeGameDialog.cpp"
        "CommentaryDialog.cpp"
        "CommentaryDialog.h"
        "CommentaryExplanationDialog.cpp"
        "CommentaryExplanationDialog.h"
        "ContentControlDialog.cpp"
        "ContentControlDialog.h"
        "ControllerDialog.cpp"
        "ControllerDialog.h"
        "CreateMultiplayerGameBotPage.cpp"
        "CreateMultiplayerGameDialog.cpp"
        "CreateMultiplayerGameGameplayPage.cpp"
        "CreateMultiplayerGameServerPage.cpp"
        "CustomTabExplanationDialog.cpp"
        "CustomTabExplanationDialog.h"
        "GameConsoleDialog.cpp"
        "GameConsoleDialog.h"
        "LoadCommentaryDialog.cpp"
        "LoadGameDialog.cpp"
        "LoadGameDialog.h"
        "LoadGameDialog_Xbox.cpp"
        "LoadingDialog.cpp"
        "MultiplayerAdvancedDialog.cpp"
        "MultiplayerAdvancedDialog.h"
        "NewGameDialog.cpp"
        "NewGameDialog.h"
        "OptionsDialog_Xbox.cpp"
        "PlayerListDialog.cpp"
        "PlayerListDialog.h"
        "SaveGameDialog.cpp"
        "SaveGameDialog.h"
        "SaveGameDialog_Xbox.cpp"
        )
source_group("Dialogs" FILES ${Dialogs})

set(Header_Files
        "../common/GameUI/scriptobject.h"
        "../engine/components/vgui2/src/Memorybitmap.h"
        "BackgroundMenuButton.h"
        "BasePanel.h"
        "BaseSaveGameDialog.h"
        "CDKeyEntryDialog.h"
        "ChangeGameDialog.h"
        "CreateMultiplayerGameBotPage.h"
        "CreateMultiplayerGameDialog.h"
        "CreateMultiplayerGameGameplayPage.h"
        "CreateMultiplayerGameServerPage.h"
        "EngineInterface.h"
        "GameConsole.h"
        "GameUI_Interface.h"
        "LoadingDialog.h"
        "ModInfo.h"
        "MouseMessageForwardingPanel.h"
        "PanelListPanel.h"
        "SaveGameBrowserDialog.h"
        "Sys_Utils.h"
        "TextEntryBox.h"
        "TGAImagePanel.h"
        "VGuiSystemModuleLoader.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Matchmaking
        "matchmaking/achievementsdialog.cpp"
        "matchmaking/achievementsdialog.h"
        "matchmaking/basedialog.cpp"
        "matchmaking/basedialog.h"
        "matchmaking/dialogmenu.cpp"
        "matchmaking/dialogmenu.h"
        "matchmaking/leaderboarddialog.cpp"
        "matchmaking/leaderboarddialog.h"
        "matchmaking/matchmakingbasepanel.cpp"
        "matchmaking/matchmakingbasepanel.h"
        "matchmaking/pausedialog.cpp"
        "matchmaking/pausedialog.h"
        "matchmaking/sessionbrowserdialog.cpp"
        "matchmaking/sessionbrowserdialog.h"
        "matchmaking/sessionlobbydialog.cpp"
        "matchmaking/sessionlobbydialog.h"
        "matchmaking/sessionoptionsdialog.cpp"
        "matchmaking/sessionoptionsdialog.h"
        "matchmaking/welcomedialog.cpp"
        "matchmaking/welcomedialog.h"
        )
source_group("Matchmaking" FILES ${Matchmaking})

set(Options_Dialog
        "OptionsDialog.cpp"
        "OptionsDialog.h"
        "OptionsSubAudio.cpp"
        "OptionsSubAudio.h"
        "OptionsSubDifficulty.cpp"
        "OptionsSubDifficulty.h"
        "OptionsSubGame.cpp"
        "OptionsSubGame.h"
        "OptionsSubHaptics.cpp"
        "OptionsSubHaptics.h"
        "OptionsSubKeyboard.cpp"
        "OptionsSubKeyboard.h"
        "OptionsSubMouse.cpp"
        "OptionsSubMouse.h"
        "OptionsSubMultiplayer.cpp"
        "OptionsSubMultiplayer.h"
        "OptionsSubPortal.cpp"
        "OptionsSubPortal.h"
        "OptionsSubVideo.cpp"
        "OptionsSubVideo.h"
        "OptionsSubVoice.cpp"
        "OptionsSubVoice.h"
        )
source_group("Options Dialog" FILES ${Options_Dialog})

set(Public_Header_Files
        "../common/GameUI/IGameUI.h"
        "../common/GameUI/ObjectList.h"
        "../common/imageutils.h"
        "../common/IObjectContainer.h"
        "../common/IRunGameEngine.h"
        "../common/IVguiModule.h"
        "../common/IVGuiModuleLoader.h"
        "../common/language.h"
        "../common/ValveCDKeyGameAndTerritoryCodes.h"
        "../public/game/client/IGameClientExports.h"
        "../public/iachievementmgr.h"
        "../public/IGameUIFuncs.h"
        "../public/savegame_version.h"
        "../public/tier1/interface.h"
        "../tracker/common/TrackerMessageFlags.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../common/crypto.cpp"
        "../common/debug_dll_check.cpp"
        "../common/GameUI/ObjectList.cpp"
        "../common/GameUI/scriptobject.cpp"
        "../common/imageutils.cpp"
        "../common/language.cpp"
        "../public/tier0/memoverride.cpp"
        "../public/vgui_controls/vgui_controls.cpp"
        "../tracker/common/msgbuffer.cpp"
        "../tracker/common/netapi.cpp"
        "../tracker/common/Socket.cpp"
        "BackgroundMenuButton.cpp"
        "BasePanel.cpp"
        "BonusMapsDatabase.cpp"
        "BonusMapsDatabase.h"
        "GameConsole.cpp"
        "GameUI_Interface.cpp"
        "gameui_util.cpp"
        "gameui_util.h"
        "LogoFile.cpp"
        "ModInfo.cpp"
        "MouseMessageForwardingPanel.cpp"
        "PanelListPanel.cpp"
        "RunGameEngine.cpp"
        "SaveGameBrowserDialog.cpp"
        "Sys_Utils.cpp"
        "TextEntryBox.cpp"
        "TGAImagePanel.cpp"
        "VGuiSystemModuleLoader.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Controls}
        ${Dialogs}
        ${Header_Files}
        ${Matchmaking}
        ${Options_Dialog}
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
        TARGET_NAME_DEBUG "GameUI"
        TARGET_NAME_RELEASE "GameUI"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vgui2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vgui2/controls;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../common/GameUI"
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
        "_WINDOWS;"
        "_USRDLL;"
        "_CRT_SECURE_NO_DEPRECATE;"
        "_CRT_NONSTDC_NO_DEPRECATE;"
        "PLATFORM_32BITS;"
        "COMPILER_MSVC32;"
        "COMPILER_MSVC;"
        "DLLNAME=GameUI;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "GAMEUI_EXPORTS;"
        "VERSION_SAFE_STEAM_API_INTERFACES;"
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
    source_file_compile_options(../common/crypto.cpp ${FILE_CL_OPTIONS})
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
        matsys_controls
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vpklib
        vstdlib
        vtf
        zlib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        matsys_controls
        tier0
        tier1
        tier2
        tier3
        vgui_controls
        vpklib
        vstdlib
        vtf
        zlib
        Jpeglib

        cryptlib

        steamemu


        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "Ws2_32;"
        "odbc32;"
        "odbccp32;"
        "Shlwapi"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/common;"

        )

