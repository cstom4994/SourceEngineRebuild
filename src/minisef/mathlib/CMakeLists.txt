set(PROJECT_NAME mathlib)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "3dnow.h"
        "noisedata.h"
        "sse.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Public_Header_Files
        "../../public/mathlib/amd3dx.h"
        "../../public/mathlib/anorms.h"
        "../../public/mathlib/bumpvects.h"
        "../../public/mathlib/compressed_3d_unitvec.h"
        "../../public/mathlib/compressed_light_cube.h"
        "../../public/mathlib/compressed_vector.h"
        "../../public/mathlib/halton.h"
        "../../public/mathlib/IceKey.H"
        "../../public/mathlib/lightdesc.h"
        "../../public/mathlib/math_pfns.h"
        "../../public/mathlib/mathlib.h"
        "../../public/mathlib/noise.h"
        "../../public/mathlib/polyhedron.h"
        "../../public/mathlib/quantize.h"
        "../../public/mathlib/simdvectormatrix.h"
        "../../public/mathlib/spherical_geometry.h"
        "../../public/mathlib/ssemath.h"
        "../../public/mathlib/ssequaternion.h"
        "../../public/mathlib/vector.h"
        "../../public/mathlib/vector2d.h"
        "../../public/mathlib/vector4d.h"
        "../../public/mathlib/vmatrix.h"
        "../../public/mathlib/vplane.h"
        )
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Source_Files
        "../../common/debug_lib_check.cpp"
        "3dnow.cpp"
        "almostequal.cpp"
        "anorms.cpp"
        "bumpvects.cpp"
        "color_conversion.cpp"
        "halton.cpp"
        "IceKey.cpp"
        "imagequant.cpp"
        "lightdesc.cpp"
        "mathlib_base.cpp"
        "polyhedron.cpp"
        "powsse.cpp"
        "quantize.cpp"
        "randsse.cpp"
        "simdvectormatrix.cpp"
        "sparse_convolution_noise.cpp"
        "spherical.cpp"
        "sse.cpp"
        "sseconst.cpp"
        "ssenoise.cpp"
        "vector.cpp"
        "vmatrix.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Header_Files}
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
        TARGET_NAME_DEBUG "mathlib"
        TARGET_NAME_RELEASE "mathlib"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/mathlib"
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
        "LIBNAME=mathlib;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "MATHLIB_LIB;"
        "USE_SDL;"
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
    source_file_compile_options(../../common/debug_lib_check.cpp ${FILE_CL_OPTIONS})
endif ()

