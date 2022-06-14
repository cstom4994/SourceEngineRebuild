



################################################################################
# Sub-projects
################################################################################


add_subdirectory(minisef)

add_subdirectory(engine/ivp)

add_subdirectory(minisef/choreoobjects)
add_subdirectory(datacache)
add_subdirectory(datamodel)
add_subdirectory(dedicated)
add_subdirectory(fgdlib)
#add_subdirectory(dedicated_main)
add_subdirectory(dmserializers)
add_subdirectory(dmxloader)

add_subdirectory(filesystem)
add_subdirectory(engine)

add_subdirectory(game/client)
add_subdirectory(game/interfaces)
#add_subdirectory(game/rccpp)
#add_subdirectory(game/rocketui)
add_subdirectory(game/gameui2)
add_subdirectory(game/server)

add_subdirectory(launcher)
add_subdirectory(shadereditor/src)
add_subdirectory(materialsystem)
add_subdirectory(materialsystem/shaderapidx9)
add_subdirectory(materialsystem/shaderapiempty)
add_subdirectory(materialsystem/shaderlib)
add_subdirectory(materialsystem/stdshaders_old)
add_subdirectory(materialsystem/newshadersystem/stdshaders)

add_subdirectory(minisef/movieobjects)
add_subdirectory(particles)

add_subdirectory(replay)
add_subdirectory(replay/common)
add_subdirectory(minisef/scenefilecache)
add_subdirectory(soundemittersystem)
add_subdirectory(soundsystem)
add_subdirectory(sourcevr)

add_subdirectory(engine/components/vgui2/dme_controls)
add_subdirectory(engine/components/vgui2/matsys_controls)
add_subdirectory(engine/components/vgui2/vgui_controls)
add_subdirectory(engine/components/vgui2/vgui_surfacelib)

add_subdirectory(minisef/serverbrowser)
add_subdirectory(studiorender)
add_subdirectory(utils/vmpi)
add_subdirectory(utils/vbsp)

if (BUILD_HAMMER)
    add_subdirectory(SDKLauncher)
    add_subdirectory(hammer)
    add_subdirectory(hammer_launcher)
endif ()

if (BUILD_SHADER)
    add_subdirectory(utils/shadercompile)
    add_subdirectory(utils/shadercompile_launcher)
    add_subdirectory(utils/shadercompile_standalone)
    add_subdirectory(utils/vrad)
    add_subdirectory(utils/vrad_launcher)
    add_subdirectory(utils/vvis)
    add_subdirectory(utils/vvis_launcher)
endif ()

#add_subdirectory(engine/voice_codecs/celt)

