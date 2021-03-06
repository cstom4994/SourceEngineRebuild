cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(SourceEngineRebuild)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if (NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "Win32")
endif ()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

set(MYROOTDIR ${CMAKE_SOURCE_DIR}/Engine)

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

ADD_DEFINITIONS(
        -DUSE_SDL
        -DWIN32
        -D_WIN32
        -D_WINDOWS
        -D_USRDLL
        -D_CRT_SECURE_NO_DEPRECATE
        -D_CRT_NONSTDC_NO_DEPRECATE
        -DCOMPILER_MSVC32
        -DCOMPILER_MSVC
)

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

set(BUILD_HAMMER 0)
set(BUILD_HL2 0)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(cmake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Engine)
add_subdirectory(ThirdParty)

