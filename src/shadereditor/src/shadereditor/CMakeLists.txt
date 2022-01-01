set(PROJECT_NAME shadereditor)

################################################################################
# Source groups
################################################################################
set(Precompiled_Header
        "cbase.h"
        "stdafx.cpp"
        )
source_group("Precompiled Header" FILES ${Precompiled_Header})

set(Source_Files
        "../../../public/tier0/memoverride.cpp"
        "chlsl_image.cpp"
        "chlsl_mesh.cpp"
        "chlsl_variable.cpp"
        "ckvpacker.cpp"
        "cregex.cpp"
        "editorcommon.cpp"
        "exported_utilities.cpp"
        "gdirectories.cpp"
        "gpostprocessingcache.cpp"
        "grendertargetconfig.cpp"
        "gshaderdumps.cpp"
        "vbasediag.cpp"
        "vbridge.cpp"
        "vdialogconfig.cpp"
        "vdialogeditorconfig.cpp"
        "vdialognew.cpp"
        "vdialogppeconfig.cpp"
        "vdialogppeffectprecache.cpp"
        "vdialogrecompileall.cpp"
        "vdialogrtlist.cpp"
        "vdialogsprecache.cpp"
        "veditorflowgraphpage.cpp"
        "veditorflowgraphsheet.cpp"
        "veditorroot.cpp"
        "vgui_init.cpp"
        "vjack.cpp"
        "vnodeview.cpp"
        "vnodeviewerror.cpp"
        "vpreview.cpp"
        "vrenderpanel.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Base_Files
        "../vgui_editor/vgui_controls_editor.cpp"
        "util/client_factorylist.cpp"
        "util/igamesystem.cpp"
        )
source_group("Source Files\\Base Files" FILES ${Source_Files__Base_Files})

set(Source_Files__Interface
        "../materialsystem/ivprocshader.cpp"
        "interface/dll_init.cpp"
        "interface/editorinit.cpp"
        "interface/ppehelper.cpp"
        )
source_group("Source Files\\Interface" FILES ${Source_Files__Interface})

set(Source_Files__Nodes
        "nodes/vbasecontainer.cpp"
        "nodes/vbasenode.cpp"
        "nodes/vnode_add.cpp"
        "nodes/vnode_array.cpp"
        "nodes/vnode_baseevaluate.cpp"
        "nodes/vnode_baserange.cpp"
        "nodes/vnode_break.cpp"
        "nodes/vnode_callback.cpp"
        "nodes/vnode_combo.cpp"
        "nodes/vnode_comment.cpp"
        "nodes/vnode_condition.cpp"
        "nodes/vnode_constant.cpp"
        "nodes/vnode_cross.cpp"
        "nodes/vnode_custom.cpp"
        "nodes/vnode_divide.cpp"
        "nodes/vnode_dot.cpp"
        "nodes/vnode_envc.cpp"
        "nodes/vnode_final.cpp"
        "nodes/vnode_flashlight.cpp"
        "nodes/vnode_fog.cpp"
        "nodes/vnode_lerp.cpp"
        "nodes/vnode_lightscale.cpp"
        "nodes/vnode_loop.cpp"
        "nodes/vnode_matrices.cpp"
        "nodes/vnode_mcompose.cpp"
        "nodes/vnode_multiply.cpp"
        "nodes/vnode_parallax.cpp"
        "nodes/vnode_psinput.cpp"
        "nodes/vnode_psoutput.cpp"
        "nodes/vnode_sampler.cpp"
        "nodes/vnode_std_plight.cpp"
        "nodes/vnode_std_skinning.cpp"
        "nodes/vnode_std_vlight.cpp"
        "nodes/vnode_subtract.cpp"
        "nodes/vnode_swizzle.cpp"
        "nodes/vnode_texsample.cpp"
        "nodes/vnode_textransform.cpp"
        "nodes/vnode_utility.cpp"
        "nodes/vnode_vcompression.cpp"
        "nodes/vnode_vecappend.cpp"
        "nodes/vnode_vectorref.cpp"
        "nodes/vnode_vmtparam.cpp"
        "nodes/vnode_vsinput.cpp"
        "nodes/vnode_vsoutput.cpp"
        )
source_group("Source Files\\Nodes" FILES ${Source_Files__Nodes})

set(Source_Files__Nodes__Post_processing
        "nodes/postprocessing/vnode_pp_base.cpp"
        "nodes/postprocessing/vnode_pp_drawmat.cpp"
        "nodes/postprocessing/vnode_pp_mat.cpp"
        "nodes/postprocessing/vnode_pp_operations.cpp"
        "nodes/postprocessing/vnode_pp_renderview.cpp"
        "nodes/postprocessing/vnode_pp_rt.cpp"
        )
source_group("Source Files\\Nodes\\Post processing" FILES ${Source_Files__Nodes__Post_processing})

set(Source_Files__Properties
        "properties/vcodeeditor.cpp"
        "properties/vnodeproperties.cpp"
        "properties/vsheet_array.cpp"
        "properties/vsheet_base.cpp"
        "properties/vsheet_callback.cpp"
        "properties/vsheet_cmatrix.cpp"
        "properties/vsheet_combo.cpp"
        "properties/vsheet_comment.cpp"
        "properties/vsheet_condition.cpp"
        "properties/vsheet_constant.cpp"
        "properties/vsheet_custom.cpp"
        "properties/vsheet_final.cpp"
        "properties/vsheet_flashlight.cpp"
        "properties/vsheet_general.cpp"
        "properties/vsheet_lightscale.cpp"
        "properties/vsheet_loop.cpp"
        "properties/vsheet_mcomp.cpp"
        "properties/vsheet_multiply.cpp"
        "properties/vsheet_parallax.cpp"
        "properties/vsheet_psoutput.cpp"
        "properties/vsheet_stdplight.cpp"
        "properties/vsheet_stdpspeclight.cpp"
        "properties/vsheet_stdskinning.cpp"
        "properties/vsheet_stdvlight.cpp"
        "properties/vsheet_swizzle.cpp"
        "properties/vsheet_textransform.cpp"
        "properties/vsheet_texturesample.cpp"
        "properties/vsheet_vcompression.cpp"
        "properties/vsheet_vmtparam.cpp"
        "properties/vsheet_vsinput.cpp"
        "properties/vsheet_vsoutpsin.cpp"
        )
source_group("Source Files\\Properties" FILES ${Source_Files__Properties})

set(Source_Files__Properties__Post_processing
        "properties/postprocessing/vsheet_pp_drawmat.cpp"
        "properties/postprocessing/vsheet_pp_mat.cpp"
        "properties/postprocessing/vsheet_pp_operations.cpp"
        "properties/postprocessing/vsheet_pp_renderview.cpp"
        "properties/postprocessing/vsheet_pp_rt.cpp"
        )
source_group("Source Files\\Properties\\Post processing" FILES ${Source_Files__Properties__Post_processing})

set(Source_Files__Properties__Smart_text
        "properties/smarttext/vsmartautocomplete.cpp"
        "properties/smarttext/vsmartobject.cpp"
        "properties/smarttext/vsmartobjectlist.cpp"
        "properties/smarttext/vsmartrow.cpp"
        "properties/smarttext/vsmarttext.cpp"
        "properties/smarttext/vsmarttooltip.cpp"
        )
source_group("Source Files\\Properties\\Smart text" FILES ${Source_Files__Properties__Smart_text})

set(Source_Files__Solver
        "solver/chlsl_solver_add.cpp"
        "solver/chlsl_solver_append.cpp"
        "solver/chlsl_solver_array.cpp"
        "solver/chlsl_solver_baseevaluate.cpp"
        "solver/chlsl_solver_baserange.cpp"
        "solver/chlsl_solver_break.cpp"
        "solver/chlsl_solver_callback.cpp"
        "solver/chlsl_solver_constant.cpp"
        "solver/chlsl_solver_containerbasic.cpp"
        "solver/chlsl_solver_cross.cpp"
        "solver/chlsl_solver_custom.cpp"
        "solver/chlsl_solver_divide.cpp"
        "solver/chlsl_solver_dot.cpp"
        "solver/chlsl_solver_dummy.cpp"
        "solver/chlsl_solver_envc.cpp"
        "solver/chlsl_solver_final.cpp"
        "solver/chlsl_solver_flashlight.cpp"
        "solver/chlsl_solver_fog.cpp"
        "solver/chlsl_solver_lerp.cpp"
        "solver/chlsl_solver_lightscale.cpp"
        "solver/chlsl_solver_matrices.cpp"
        "solver/chlsl_solver_mcomp.cpp"
        "solver/chlsl_solver_multiply.cpp"
        "solver/chlsl_solver_parallax.cpp"
        "solver/chlsl_solver_readsemantics.cpp"
        "solver/chlsl_solver_stdplight.cpp"
        "solver/chlsl_solver_stdskinning.cpp"
        "solver/chlsl_solver_stdvlight.cpp"
        "solver/chlsl_solver_subtract.cpp"
        "solver/chlsl_solver_swizzle.cpp"
        "solver/chlsl_solver_textransform.cpp"
        "solver/chlsl_solver_texturesample.cpp"
        "solver/chlsl_solver_utility.cpp"
        "solver/chlsl_solver_vcompression.cpp"
        "solver/chlsl_solver_vecref.cpp"
        "solver/chlsl_solver_vmtparam.cpp"
        "solver/chlsl_solver_writesemantics.cpp"
        "solver/chlsl_solverbase.cpp"
        "solver/hlsl_solver.h"
        )
source_group("Source Files\\Solver" FILES ${Source_Files__Solver})

set(Source_Files__Solver__Post_processing
        "solver/postprocessing/chlsl_solver_pp_drawmat.cpp"
        "solver/postprocessing/chlsl_solver_pp_mat.cpp"
        "solver/postprocessing/chlsl_solver_pp_operations.cpp"
        "solver/postprocessing/chlsl_solver_pp_renderview.cpp"
        "solver/postprocessing/chlsl_solver_pp_rt.cpp"
        "solver/postprocessing/chlsl_solverpp_base.cpp"
        )
source_group("Source Files\\Solver\\Post processing" FILES ${Source_Files__Solver__Post_processing})

set(Source_Files__Threads
        "threads/cbasethread.cpp"
        "threads/ccompilethread.cpp"
        "threads/csolvercallback.cpp"
        "threads/cthreadmanager.cpp"
        )
source_group("Source Files\\Threads" FILES ${Source_Files__Threads})

set(ALL_FILES
        ${Precompiled_Header}
        ${Source_Files}
        ${Source_Files__Base_Files}
        ${Source_Files__Interface}
        ${Source_Files__Nodes}
        ${Source_Files__Nodes__Post_processing}
        ${Source_Files__Properties}
        ${Source_Files__Properties__Post_processing}
        ${Source_Files__Properties__Smart_text}
        ${Source_Files__Solver}
        ${Source_Files__Solver__Post_processing}
        ${Source_Files__Threads}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/cbase.h>"
        )

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "shadereditor"
        TARGET_NAME_RELEASE "shadereditor"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/mod_hl2mp/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/mod_hl2mp/bin"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../shadereditor;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../vgui_editor;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../materialsystem;"
        "${MYROOTDIR}/game/client/shadereditor;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../public;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../common"
        "${CMAKE_CURRENT_SOURCE_DIR}/util;"
        "${CMAKE_CURRENT_SOURCE_DIR}/interface;"
        "${CMAKE_CURRENT_SOURCE_DIR}/nodes;"
        "${CMAKE_CURRENT_SOURCE_DIR}/properties;"
        "${CMAKE_CURRENT_SOURCE_DIR}/solver;"
        "${CMAKE_CURRENT_SOURCE_DIR}/threads;"
        "${CMAKE_CURRENT_SOURCE_DIR}/solver/postprocessing;"
        "${CMAKE_CURRENT_SOURCE_DIR}/properties/postprocessing;"
        "${CMAKE_CURRENT_SOURCE_DIR}/properties/smarttext;"
        "${CMAKE_CURRENT_SOURCE_DIR}/nodes/postprocessing"
        )


################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_HAS_ITERATOR_DEBUGGING=0;"
        "_DEBUG;"
        "DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "VPC;"
        "RAD_TELEMETRY_DISABLED;"
        "DLLNAME=shadereditor;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "NO_STRING_T;"
        "CLIENT_DLL;"
        "VECTOR;"
        "VERSION_SAFE_STEAM_API_INTERFACES;"
        "PROTECTED_THINGS_ENABLE;"
        "strncpy=use_Q_strncpy_instead;"
        "_snprintf=use_Q_snprintf_instead;"
        "ENABLE_CHROMEHTMLWINDOW;"
        "fopen=dont_use_fopen;"
        "SHADER_EDITOR_DLL;"
        "SHADER_EDITOR_DLL_SER;"
        "VPCGAMECAPS=VALVE;"
        "USE_SDL;"
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
            /Ot;
            /d2Zi+
            >
            /MP;
            /GF;
            /arch:SSE;
            /TP;
            /fp:fast;
            /GR;
            /Zm200;
            /GS;
            /Zc:forScope
            )
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../../public/collisionutils.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../../public/crtmemdebug.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../vgui_editor/vgui_controls_editor.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../materialsystem/ivprocshader.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /NODEFAULTLIB:libcmt;
            /INCREMENTAL
            >
            $<$<CONFIG:Release>:
            /NODEFAULTLIB:libcmtd;
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
        bitmap
        choreoobjects
        matsys_controls
        particles
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        tier3
        vstdlib
        vtf
        vgui_controls_editor

        Jpeglib
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        choreoobjects
        matsys_controls
        particles
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        tier3
        vstdlib
        vtf
        vgui_controls_editor

        Jpeglib

        d3d9
        d3dx9

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "version;"
        "winmm"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${MYROOTDIR}/thirdparty/dxsdk/lib;"
        "${MYROOTDIR}/lib/common;"
        "${MYROOTDIR}/lib/public"
        )
