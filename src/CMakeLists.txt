cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(InvadeEngine)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if (NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "Win32")
endif ()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

set(MYROOTDIR ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
        "Debug"
        "Release"
        CACHE STRING "" FORCE
        )

################################################################################
# Global compiler options
################################################################################
if (MSVC)
    # remove default flags provided with cmake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)

endif ()

################################################################################
# Global linker options
################################################################################
if (MSVC)
    # remove default flags provided with cmake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif ()

set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE "x86")


################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
            "Package \"${PACKAGE}\" with version \"${VERSION}\" "
            "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(cmake/Utils.cmake)
include(cmake/ProtobufBuilder.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(cmake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
add_subdirectory(game/gameui2)
add_subdirectory(game/server)

add_subdirectory(gcsdk)
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

add_subdirectory(SDKLauncher)
add_subdirectory(hammer)
add_subdirectory(hammer_launcher)
add_subdirectory(utils/vbsp)

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

add_subdirectory(thirdparty/libspeex)
add_subdirectory(thirdparty/zlib-1.2.5)
add_subdirectory(thirdparty/cryptopp860)
add_subdirectory(thirdparty/re2)
add_subdirectory(thirdparty/bzip2)
add_subdirectory(thirdparty/jpeglib)
add_subdirectory(thirdparty/lzma)
add_subdirectory(thirdparty/protobuf-2.6.1/vsprojects)
