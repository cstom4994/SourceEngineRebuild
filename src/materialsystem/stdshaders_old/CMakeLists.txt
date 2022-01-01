set(PROJECT_NAME stdshader_dbg)

################################################################################
# Source groups
################################################################################
set(______
        "../../devtools/bin/fxc_prep.pl"
        "../../devtools/bin/psh_prep.pl"
        "../../devtools/bin/updateshaders.pl"
        "../../devtools/bin/vsh_prep.pl"
        )
source_group("
" FILES ${______})

set(Header_Files
        "BaseVSShader.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Shader_Source
        #    "stdshader_dx9_20b.txt"
        #    "stdshader_dx9_30.txt"
        )
source_group("Shader Source" FILES ${Shader_Source})

set(Shader_Source__fxc
        #    "AccumBuff4Sample_ps2x.fxc"
        #    "accumbuff5sample_ps2x.fxc"
        #    "aftershock_ps2x.fxc"
        #    "aftershock_vs20.fxc"
        #    "alphadist_ps11.fxc"
        #    "appchooser360movie_ps2x.fxc"
        #    "bik_ps2x.fxc"
        #    "bik_vs20.fxc"
        #    "Bloom_ps2x.fxc"
        #    "bloomadd_ps11.fxc"
        #    "bloomadd_ps2x.fxc"
        #    "BlurFilter_ps2x.fxc"
        #    "BlurFilter_vs11.fxc"
        #    "BlurFilter_vs20.fxc"
        #    "bufferclearobeystencil_ps2x.fxc"
        #    "bufferclearobeystencil_vs20.fxc"
        #    "bumpmappedlightmap_vs11.fxc"
        #    "cable_ps2x.fxc"
        #    "cable_vs20.fxc"
        #    "cloak_blended_pass_ps2x.fxc"
        #    "cloak_blended_pass_vs20.fxc"
        #    "cloak_ps2x.fxc"
        #    "cloak_vs20.fxc"
        #    "cloud_ps20.fxc"
        #    "cloud_vs20.fxc"
        #    "color_projection_ps2x.fxc"
        #    "color_projection_vs20.fxc"
        #    "colorcorrection_ps2x.fxc"
        #    "compositor_ps2x.fxc"
        #    "compositor_vs20.fxc"
        #    "constant_color_ps2x.fxc"
        #    "copy_fp_rt_ps2x.fxc"
        #    "core_ps2x.fxc"
        #    "core_vs11.fxc"
        #    "core_vs20.fxc"
        #    "DebugDrawDepth_ps2x.fxc"
        #    "DebugDrawDepth_vs20.fxc"
        #    "DebugDrawEnvmapMask_ps2x.fxc"
        #    "DebugDrawEnvmapMask_vs20.fxc"
        #    "debugluxel_ps2x.fxc"
        #    "debugluxel_vs20.fxc"
        #    "debugmorphaccumulator_ps30.fxc"
        #    "debugmorphaccumulator_vs30.fxc"
        #    "debugmrttexture_ps2x.fxc"
        #    "debugmrttexture_vs20.fxc"
        #    "debugtangentspace_vs11.fxc"
        #    "debugtangentspace_vs20.fxc"
        #    "DebugTextureView_ps2x.fxc"
        #    "DebugTextureView_vs20.fxc"
        #    "decalbasetimeslightmapalphablendselfillum2_ps2x.fxc"
        #    "decalmodulate_ps2x.fxc"
        #    "depthtodestalpha_ps20b.fxc"
        #    "depthtodestalpha_vs20.fxc"
        #    "depthwrite_ps2x.fxc"
        #    "depthwrite_vs20.fxc"
        #    "Downsample_nohdr_ps2x.fxc"
        #    "Downsample_ps2x.fxc"
        #    "Downsample_vs11.fxc"
        #    "Downsample_vs20.fxc"
        #    "emissive_scroll_blended_pass_ps2x.fxc"
        #    "emissive_scroll_blended_pass_vs20.fxc"
        #    "Engine_Post_ps2x.fxc"
        #    "example_model_ps20b.fxc"
        #    "example_model_vs20.fxc"
        #    "eye_refract_ps2x.fxc"
        #    "eye_refract_vs20.fxc"
        #    "eyeglint_ps2x.fxc"
        #    "eyeglint_vs20.fxc"
        #    "eyes_flashlight_ps11.fxc"
        #    "eyes_flashlight_ps2x.fxc"
        #    "eyes_flashlight_vs20.fxc"
        #    "eyes_ps2x.fxc"
        #    "Eyes_vs20.fxc"
        #    "fillrate_ps11.fxc"
        #    "fillrate_ps2x.fxc"
        #    "fillrate_vs11.fxc"
        #    "fillrate_vs20.fxc"
        #    "filmdust_ps11.fxc"
        #    "filmdust_ps20.fxc"
        #    "filmgrain_ps11.fxc"
        #    "filmgrain_ps20.fxc"
        #    "filmgrain_vs20.fxc"
        #    "flashlight_ps11.fxc"
        #    "flashlight_ps2x.fxc"
        #    "flesh_interior_blended_pass_ps2x.fxc"
        #    "flesh_interior_blended_pass_vs20.fxc"
        #    "floatcombine_autoexpose_ps2x.fxc"
        #    "floatcombine_ps2x.fxc"
        #    "floattoscreen_notonemap_ps2x.fxc"
        #    "floattoscreen_ps2x.fxc"
        #    "floattoscreen_vanilla_ps2x.fxc"
        #    "haloadd1d_ps2x.fxc"
        #    "haloadd_ps2x.fxc"
        #    "haloaddoutline_ps2x.fxc"
        #    "HDRCombineTo16Bit_ps2x.fxc"
        #    "HDRCombineTo16Bit_vs20.fxc"
        #    "HDRSelectRange_ps2x.fxc"
        #    "HDRSelectRange_vs20.fxc"
        #    "hsl_filmgrain_pass1_ps2x.fxc"
        #    "hsl_filmgrain_pass2_ps2x.fxc"
        #    "hsv_ps2x.fxc"
        #    "IntroScreenSpaceEffect_ps11.fxc"
        #    "IntroScreenSpaceEffect_ps2x.fxc"
        #    "lightmappedgeneric_decal_ps2x.fxc"
        #    "lightmappedgeneric_decal_vs20.fxc"
        #    "lightmappedgeneric_flashlight_vs11.fxc"
        #    "lightmappedgeneric_flashlight_vs20.fxc"
        #    "lightmappedgeneric_lightingonly_overbright2_ps11.fxc"
        #    "lightmappedgeneric_lightingonly_vs11.fxc"
        #    "lightmappedgeneric_ps2x.fxc"
        #    "lightmappedgeneric_vs20.fxc"
        #    "lightmappedreflective_ps2x.fxc"
        #    "lightmappedreflective_vs20.fxc"
        #    "lpreview1_ps2x.fxc"
        #    "lpreview_output_ps2x.fxc"
        #    "luminance_compare_ps2x.fxc"
        #    "modulate_ps2x.fxc"
        #    "monitorscreen_ps2x.fxc"
        #    "morphaccumulate_ps30.fxc"
        #    "morphaccumulate_vs30.fxc"
        #    "morphweight_ps30.fxc"
        #    "morphweight_vs30.fxc"
        #    "motion_blur_ps2x.fxc"
        #    "motion_blur_vs20.fxc"
        #    "particlesphere_ps11.fxc"
        #    "particlesphere_ps2x.fxc"
        #    "particlesphere_vs11.fxc"
        #    "particlesphere_vs20.fxc"
        #    "portal_ps11.fxc"
        #    "portal_ps2x.fxc"
        #    "portal_refract_ps11.fxc"
        #    "portal_refract_ps2x.fxc"
        #    "portal_refract_vs11.fxc"
        #    "portal_refract_vs20.fxc"
        #    "portal_vs11.fxc"
        #    "portal_vs20.fxc"
        #    "portalstaticoverlay_ps11.fxc"
        #    "portalstaticoverlay_ps2x.fxc"
        #    "portalstaticoverlay_vs11.fxc"
        #    "portalstaticoverlay_vs20.fxc"
        #    "pyro_vision_ps2x.fxc"
        #    "pyro_vision_vs20.fxc"
        #    "refract_ps2x.fxc"
        #    "Refract_vs20.fxc"
        #    "rendertargetblit_ps2x.fxc"
        #    "rendertargetblit_vs20.fxc"
        #    "sample4x4_blend_ps2x.fxc"
        #    "sample4x4_ps2x.fxc"
        #    "sample4x4delog_ps2x.fxc"
        #    "sample4x4log_ps2x.fxc"
        #    "sample4x4maxmin_ps2x.fxc"
        #    "screenspaceeffect_vs11.fxc"
        #    "screenspaceeffect_vs20.fxc"
        #    "sfm_combine_vs20.fxc"
        #    "sfm_integercombine_ps2x.fxc"
        #    "shadow_ps2x.fxc"
        #    "shadow_vs20.fxc"
        #    "shadowbuildtexture_ps2x.fxc"
        #    "shadowmodel_ps20.fxc"
        #    "shadowmodel_vs20.fxc"
        #    "ShatteredGlass_ps2x.fxc"
        #    "ShatteredGlass_vs20.fxc"
        #    "showz_ps2x.fxc"
        #    "showz_vs20.fxc"
        #    "skin_ps20b.fxc"
        #    "skin_vs20.fxc"
        #    "sky_hdr_compressed_ps2x.fxc"
        #    "sky_hdr_compressed_rgbs_ps2x.fxc"
        #    "sky_ps2x.fxc"
        #    "sky_vs20.fxc"
        #    "splinecard_vsxx.fxc"
        #    "sprite_ps2x.fxc"
        #    "sprite_vs20.fxc"
        #    "spritecard_ps11.fxc"
        #    "spritecard_ps2x.fxc"
        #    "spritecard_vsxx.fxc"
        #    "teeth_bump_ps2x.fxc"
        #    "teeth_bump_vs20.fxc"
        #    "teeth_flashlight_ps2x.fxc"
        #    "teeth_flashlight_vs20.fxc"
        #    "teeth_ps2x.fxc"
        #    "teeth_vs20.fxc"
        #    "TreeLeaf_ps2x.fxc"
        #    "TreeLeaf_vs20.fxc"
        #    "UnlitGeneric_MaskBaseByDetailAlpha_ps11.fxc"
        #    "unlitgeneric_notexture_ps11.fxc"
        #    "unlitgeneric_notexture_ps2x.fxc"
        #    "unlitgeneric_ps2x.fxc"
        #    "unlitgeneric_vs20.fxc"
        #    "unlittwotexture_ps2x.fxc"
        #    "unlittwotexture_vs20.fxc"
        #    "vertexlit_and_unlit_generic_bump_ps2x.fxc"
        #    "vertexlit_and_unlit_generic_bump_vs20.fxc"
        #    "vertexlit_and_unlit_generic_ps2x.fxc"
        #    "vertexlit_and_unlit_generic_vs20.fxc"
        #    "vertexlitgeneric_lightingonly_overbright2_ps11.fxc"
        #    "volume_clouds_ps2x.fxc"
        #    "volume_clouds_vs20.fxc"
        #    "vortwarp_ps2x.fxc"
        #    "vortwarp_vs20.fxc"
        #    "vr_distort_hud_ps2x.fxc"
        #    "vr_distort_hud_vs20.fxc"
        #    "vr_distort_texture_ps2x.fxc"
        #    "vr_distort_texture_vs20.fxc"
        #    "warp_ps2x.fxc"
        #    "warp_vs20.fxc"
        #    "water_ps2x.fxc"
        #    "Water_vs20.fxc"
        #    "WaterCheap_ps2x.fxc"
        #    "WaterCheap_vs20.fxc"
        #    "weapon_sheen_pass_ps2x.fxc"
        #    "weapon_sheen_pass_vs20.fxc"
        #    "white_ps2x.fxc"
        #    "windowimposter_ps11.fxc"
        #    "windowimposter_ps2x.fxc"
        #    "windowimposter_vs11.fxc"
        #    "windowimposter_vs20.fxc"
        #    "worldtwotextureblend_ps2x.fxc"
        #    "WorldVertexAlpha_ps2x.fxc"
        #    "writevertexalphatodestalpha_ps11.fxc"
        #    "writevertexalphatodestalpha_vs11.fxc"
        #    "writez_vs20.fxc"
        )
source_group("Shader Source\\fxc" FILES ${Shader_Source__fxc})

set(Shader_Source__psh
        #    "bik_ps11.psh"
        #    "bik_ps14.psh"
        #    "BlurFilter_ps11.psh"
        #    "BufferClearObeyStencil_ps11.psh"
        #    "BumpmappedEnvmap.psh"
        #    "BumpmappedLightmap_OverBright2.psh"
        #    "Cable.psh"
        #    "cloak_blended_pass_dx8_ps11.psh"
        #    "cloud_ps11.psh"
        #    "core_ps11.psh"
        #    "DecalBaseTimesLightmapAlphaBlendSelfIllum1_ps11.psh"
        #    "DecalBaseTimesLightmapAlphaBlendSelfIllum2_ps11.psh"
        #    "Downsample_nohdr_ps11.psh"
        #    "emissive_scroll_blended_pass_dx8_ps11.psh"
        #    "Eyes.psh"
        #    "Eyes_Overbright2.psh"
        #    "fillrate.psh"
        #    "flesh_interior_blended_pass_dx8_ps11.psh"
        #    "JellyFish.psh"
        #    "LightmappedGeneric.psh"
        #    "LightmappedGeneric_AddBaseAlphaMaskedEnvMap.psh"
        #    "LightmappedGeneric_AddEnvMapMaskNoTexture.psh"
        #    "LightmappedGeneric_AddEnvMapNoTexture.psh"
        #    "LightmappedGeneric_BaseAlphaMaskedEnvMapV2.psh"
        #    "LightmappedGeneric_BaseTexture.psh"
        #    "lightmappedgeneric_basetextureblend.psh"
        #    "LightmappedGeneric_BumpmappedEnvmap.psh"
        #    "LightmappedGeneric_BumpmappedEnvmap_ps14.psh"
        #    "LightmappedGeneric_BumpmappedLightmap.psh"
        #    "LightmappedGeneric_BumpmappedLightmap_base_ps14.psh"
        #    "LightmappedGeneric_BumpmappedLightmap_blend_ps14.psh"
        #    "LightmappedGeneric_Decal.psh"
        #    "LightmappedGeneric_Detail.psh"
        #    "LightmappedGeneric_DetailNoTexture.psh"
        #    "LightmappedGeneric_DetailSelfIlluminated.psh"
        #    "LightmappedGeneric_EnvMapNoTexture.psh"
        #    "LightmappedGeneric_EnvMapV2.psh"
        #    "LightmappedGeneric_LightingOnly_Overbright2.psh"
        #    "LightmappedGeneric_MaskedEnvMapNoTexture.psh"
        #    "LightmappedGeneric_MaskedEnvMapV2.psh"
        #    "LightmappedGeneric_MultiplyByLighting.psh"
        #    "LightmappedGeneric_MultiplyByLightingNoTexture.psh"
        #    "LightmappedGeneric_MultiplyByLightingSelfIllum.psh"
        #    "LightmappedGeneric_NoTexture.psh"
        #    "LightmappedGeneric_SelfIlluminated.psh"
        #    "LightmappedGeneric_SelfIlluminatedEnvMapV2.psh"
        #    "LightmappedGeneric_SelfIlluminatedMaskedEnvMapV2.psh"
        #    "LightmappedGeneric_SSBumpmappedLightmap.psh"
        #    "LightmappedTranslucentTexture.psh"
        #    "Modulate_ps11.psh"
        #    "MonitorScreen.psh"
        #    "overlay_fit_ps11.psh"
        #    "predator.psh"
        #    "Refract_ps11.psh"
        #    "Shadow.psh"
        #    "shadow_ps14.psh"
        #    "ShadowBuildTexture.psh"
        #    "ShadowModel.psh"
        #    "ShatteredGlass.psh"
        #    "ShatteredGlass_EnvMap.psh"
        #    "sprite_ps11.psh"
        #    "SpriteRenderNormal.psh"
        #    "SpriteRenderTransAdd.psh"
        #    "SpriteRenderTransColor.psh"
        #    "UnlitGeneric.psh"
        #    "UnlitGeneric_BaseAlphaMaskedEnvMap.psh"
        #    "unlitgeneric_basetimesdetail.psh"
        #    "UnlitGeneric_Detail.psh"
        #    "UnlitGeneric_DetailBaseAlphaMaskedEnvMap.psh"
        #    "UnlitGeneric_DetailEnvMap.psh"
        #    "UnlitGeneric_DetailEnvMapMask.psh"
        #    "UnlitGeneric_DetailEnvMapMaskNoTexture.psh"
        #    "UnlitGeneric_DetailEnvMapNoTexture.psh"
        #    "UnlitGeneric_DetailNoTexture.psh"
        #    "UnlitGeneric_EnvMap.psh"
        #    "UnlitGeneric_EnvMapMask.psh"
        #    "UnlitGeneric_EnvMapMaskNoTexture.psh"
        #    "UnlitGeneric_EnvMapNoTexture.psh"
        #    "UnlitGeneric_NoTexture.psh"
        #    "UnlitTwoTexture.psh"
        #    "VertexLitGeneric.psh"
        #    "VertexLitGeneric_BaseAlphaMaskedEnvMapV2.psh"
        #    "VertexLitGeneric_BlendTint.psh"
        #    "VertexLitGeneric_Detail.psh"
        #    "VertexLitGeneric_Detail_additive.psh"
        #    "VertexLitGeneric_Detail_additive_selfillum.psh"
        #    "VertexLitGeneric_Detail_LerpBase.psh"
        #    "VertexLitGeneric_DetailBaseAlphaMaskedEnvMapV2.psh"
        #    "VertexLitGeneric_DetailEnvMapV2.psh"
        #    "VertexLitGeneric_DetailMaskedEnvMapV2.psh"
        #    "VertexLitGeneric_DetailNoTexture.psh"
        #    "VertexLitGeneric_DetailSelfIlluminated.psh"
        #    "VertexLitGeneric_DetailSelfIlluminatedEnvMapV2.psh"
        #    "VertexLitGeneric_DetailSelfIlluminatedMaskedEnvMapV2.psh"
        #    "VertexLitGeneric_EnvMapNoTexture.psh"
        #    "VertexLitGeneric_EnvmappedBumpmapV2.psh"
        #    "VertexLitGeneric_EnvmappedBumpmapV2_MultByAlpha.psh"
        #    "VertexLitGeneric_EnvmappedBumpmapV2_MultByAlpha_ps14.psh"
        #    "VertexLitGeneric_EnvmappedBumpmapV2_ps14.psh"
        #    "VertexLitGeneric_EnvMapV2.psh"
        #    "vertexlitgeneric_lightingonly_overbright2.psh"
        #    "VertexLitGeneric_MaskedEnvMapNoTexture.psh"
        #    "VertexLitGeneric_MaskedEnvMapV2.psh"
        #    "VertexLitGeneric_NoTexture.psh"
        #    "VertexLitGeneric_SelfIlluminated.psh"
        #    "VertexLitGeneric_SelfIlluminatedEnvMapV2.psh"
        #    "VertexLitGeneric_SelfIlluminatedMaskedEnvMapV2.psh"
        #    "VertexLitTexture.psh"
        #    "VertexLitTexture_Overbright2.psh"
        #    "vortwarp_ps11.psh"
        #    "Water_ps14.psh"
        #    "WaterCheap_ps11.psh"
        #    "WaterCheap_ps14.psh"
        #    "WaterCheapFresnel_ps14.psh"
        #    "WaterCheapFresnelOpaque_ps14.psh"
        #    "WaterCheapNoFresnel_ps11.psh"
        #    "WaterCheapNoFresnelOpaque_ps11.psh"
        #    "WaterCheapOpaque_ps11.psh"
        #    "WaterCheapOpaque_ps14.psh"
        #    "WaterReflect_ps11.psh"
        #    "WaterRefract_ps11.psh"
        #    "WaterRefractFresnel_ps11.psh"
        #    "white.psh"
        #    "WorldTexture.psh"
        #    "WorldTwoTextureBlend.psh"
        #    "WorldTwoTextureBlend_DetailAlpha.psh"
        #    "WorldTwoTextureBlend_SelfIlluminated.psh"
        #    "WorldVertexAlpha.psh"
        #    "WorldVertexTransition.psh"
        #    "WorldVertexTransition_BlendBase2.psh"
        #    "WorldVertexTransition_Editor.psh"
        #    "WorldVertexTransition_ps14.psh"
        #    "WorldVertexTransition_Seamless.psh"
        #    "yuv.psh"
        )
source_group("Shader Source\\psh" FILES ${Shader_Source__psh})

set(Shader_Source__vsh
        #    "bik_vs11.vsh"
        #    "BufferClearObeyStencil_vs11.vsh"
        #    "BumpmappedEnvmap.vsh"
        #    "BumpmappedLightmap.vsh"
        #    "Cable.vsh"
        #    "cloak_blended_pass_dx8_vs11.vsh"
        #    "cloud_vs11.vsh"
        #    "debugtangentspace.vsh"
        #    "emissive_scroll_blended_pass_dx8_vs11.vsh"
        #    "eyes.vsh"
        #    "eyes_flashlight_vs11.vsh"
        #    "fillrate.vsh"
        #    "flesh_interior_blended_pass_dx8_vs11.vsh"
        #    "JellyFish.vsh"
        #    "LightingOnly.vsh"
        #    "LightmappedGeneric_BaseTexture.vsh"
        #    "LightmappedGeneric_BaseTextureBlend.vsh"
        #    "LightmappedGeneric_BumpmappedEnvmap.vsh"
        #    "LightmappedGeneric_BumpmappedEnvmap_ps14.vsh"
        #    "LightmappedGeneric_BumpmappedLightmap.vsh"
        #    "LightmappedGeneric_BumpmappedLightmap_base_ps14.vsh"
        #    "LightmappedGeneric_BumpmappedLightmap_blend_ps14.vsh"
        #    "LightmappedGeneric_Decal.vsh"
        #    "LightmappedGeneric_LightingOnly.vsh"
        #    "lightmappedgeneric_vs11.vsh"
        #    "overlay_fit_vs11.vsh"
        #    "predator.vsh"
        #    "Refract_model_vs11.vsh"
        #    "Refract_world_vs11.vsh"
        #    "ScreenSpaceEffect.vsh"
        #    "shadow_vs14.vsh"
        #    "ShadowModel.vsh"
        #    "ShatteredGlass.vsh"
        #    "ShatteredGlass_EnvMap.vsh"
        #    "ShatteredGlass_EnvMapSphere.vsh"
        #    "sprite_vs11.vsh"
        #    "Teeth.vsh"
        #    "UnlitGeneric_LightingOnly.vsh"
        #    "unlitgeneric_vs11.vsh"
        #    "UnlitTwoTexture.vsh"
        #    "VertexLitGeneric_EnvmappedBumpmap_NoLighting.vsh"
        #    "VertexLitGeneric_EnvmappedBumpmap_NoLighting_ps14.vsh"
        #    "vertexlitgeneric_flashlight_vs11.vsh"
        #    "VertexLitGeneric_SelfIllumOnly.vsh"
        #    "vertexlitgeneric_vs11.vsh"
        #    "vortwarp_vs11.vsh"
        #    "Water_ps14.vsh"
        #    "Water_vs11.vsh"
        #    "WaterCheap_vs11.vsh"
        #    "WaterCheap_vs14.vsh"
        #    "WaterCheapPerVertexFresnel_vs11.vsh"
        #    "WorldVertexAlpha.vsh"
        #    "WorldVertexTransition.vsh"
        #    "WorldVertexTransition_Seamless.vsh"
        #    "WorldVertexTransition_vs14.vsh"
        #    "writez.vsh"
        )
source_group("Shader Source\\vsh" FILES ${Shader_Source__vsh})

set(Source_Files
        "../../common/debug_dll_check.cpp"
        "../../public/tier0/memoverride.cpp"
        "BaseVSShader.cpp"
        "debugdepth.cpp"
        "DebugDrawEnvmapMask.cpp"
        "debugluxel.cpp"
        "debugnormalmap.cpp"
        "debugtangentspace.cpp"
        "fillrate.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${______}
        ${Header_Files}
        ${Shader_Source}
        ${Shader_Source__fxc}
        ${Shader_Source__psh}
        ${Shader_Source__vsh}
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
        TARGET_NAME_DEBUG "stdshader_dbg"
        TARGET_NAME_RELEASE "stdshader_dbg"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/include"
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
        "DLLNAME=stdshader_dbg;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "STDSHADER_DBG_DLL_EXPORT;"
        "FAST_MATERIALVAR_ACCESS;"
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
    source_file_compile_options(../../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
            /ignore:4221
            )
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf



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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )


set(PROJECT_NAME stdshader_dx9)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "BaseVSShader.h"
        "cloak_dx9_helper.h"
        "common_fxc.h"
        "common_hlsl_cpp_consts.h"
        "common_ps_fxc.h"
        "common_vertexlitgeneric_dx9.h"
        "common_vs_fxc.h"
        "lightmappedgeneric_dx9_helper.h"
        "lightmappedgeneric_ps2_3_x.h"
        "particlelitgeneric_dx9_helper.h"
        "refract_dx9_helper.h"
        "shader_constant_register_map.h"
        "skin_dx9_helper.h"
        "vertexlitgeneric_dx95_helper.h"
        "vortwarp_vs20_helper.h"
        "water_ps2x_helper.h"
        "worldvertextransition_dx8_helper.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files

        "pbr_dx9.cpp"
        "magicbloom_blend.cpp"
        "magicbloom_blur.cpp"

        "AccumBuff4Sample.cpp"
        "accumbuff5sample.cpp"
        "aftershock.cpp"
        "aftershock_helper.cpp"
        "BaseVSShader.cpp"
        "bik_dx90.cpp"
        "Bloom.cpp"
        "BlurFilterX.cpp"
        "BlurFilterY.cpp"
        "BufferClearObeyStencil_dx9.cpp"
        "cable_dx9.cpp"
        "cloak.cpp"
        "cloak_blended_pass_helper.cpp"
        "cloak_dx9_helper.cpp"
        "cloud_dx9.cpp"
        "color_projection.cpp"
        "colorcorrection.cpp"
        "compositor.cpp"
        "core_dx9.cpp"
        "debugmorphaccumulator_dx9.cpp"
        "debugmrttexture.cpp"
        "DebugTextureView.cpp"
        "DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.cpp"
        "DecalModulate_dx9.cpp"
        "depthwrite.cpp"
        "Downsample.cpp"
        "downsample_nohdr.cpp"
        "emissive_scroll_blended_pass_helper.cpp"
        "Engine_Post_dx9.cpp"
        "eye_refract.cpp"
        "eye_refract_helper.cpp"
        "eyeglint_dx9.cpp"
        "eyes_dx8_dx9_helper.cpp"
        "eyes_dx9.cpp"
        "filmdust_dx8_dx9.cpp"
        "filmgrain_dx8_dx9.cpp"
        "flesh_interior_blended_pass_helper.cpp"
        "floatcombine.cpp"
        "floatcombine_autoexpose.cpp"
        "floattoscreen.cpp"
        "floattoscreen_vanilla.cpp"
        "HDRCombineTo16Bit.cpp"
        "HDRSelectRange.cpp"
        "hsl_filmgrain_pass1.cpp"
        "hsl_filmgrain_pass2.cpp"
        "hsv.cpp"
        "introscreenspaceeffect.cpp"
        "lightmappedgeneric_dx9.cpp"
        "lightmappedgeneric_dx9_helper.cpp"
        "lightmappedreflective.cpp"
        "modulate_dx9.cpp"
        "MonitorScreen_dx9.cpp"
        "morphaccumulate_dx9.cpp"
        "morphweight_dx9.cpp"
        "motion_blur_dx9.cpp"
        "occlusion_dx9.cpp"
        "particlelitgeneric_dx9.cpp"
        "particlelitgeneric_dx9_helper.cpp"
        "particlesphere_dx9.cpp"
        "portal.cpp"
        "portal_refract.cpp"
        "portal_refract_helper.cpp"
        "portalstaticoverlay.cpp"
        "pyro_vision.cpp"
        "refract.cpp"
        "refract_dx9_helper.cpp"
        "sample4x4.cpp"
        "sample4x4_blend.cpp"
        "screenspace_general.cpp"
        "sfm_blurfilterx.cpp"
        "sfm_blurfiltery.cpp"
        "sfm_downsample.cpp"
        "sfm_integercombine.cpp"
        "shadow.cpp"
        "shadowbuild_dx9.cpp"
        "shadowmodel_dx9.cpp"
        "shatteredglass.cpp"
        "showz.cpp"
        "skin_dx9_helper.cpp"
        "sky_dx9.cpp"
        "sky_hdr_dx9.cpp"
        "sprite_dx9.cpp"
        "spritecard.cpp"
        "teeth.cpp"
        "TreeLeaf.cpp"
        "unlitgeneric_dx9.cpp"
        "unlittwotexture_dx9.cpp"
        "vertexlitgeneric_dx9.cpp"
        "vertexlitgeneric_dx9_helper.cpp"
        "volume_clouds.cpp"
        "volume_clouds_helper.cpp"
        "vortwarp_dx9.cpp"
        "vr_distort_hud.cpp"
        "vr_distort_texture.cpp"
        "warp.cpp"
        "water.cpp"
        "weapon_sheen_pass_helper.cpp"
        "windowimposter_dx90.cpp"
        "wireframe_dx9.cpp"
        "worldtwotextureblend.cpp"
        "worldvertexalpha.cpp"
        "worldvertextransition.cpp"
        "worldvertextransition_dx8_helper.cpp"
        "writestencil_dx9.cpp"
        "writez_dx9.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Remove_me_when_VAC2_is_out
        "../../minisef/tier1/checksum_crc.cpp"
        "../../minisef/tier1/checksum_md5.cpp"
        )
source_group("Source Files\\Remove me when VAC2 is out" FILES ${Source_Files__Remove_me_when_VAC2_is_out})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        ${Source_Files__Remove_me_when_VAC2_is_out}
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
        TARGET_NAME_DEBUG "stdshader_dx9"
        TARGET_NAME_RELEASE "stdshader_dx9"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/include"
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
        "DLLNAME=stdshader_dx9;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "STDSHADER_DX9_DLL_EXPORT;"
        "FAST_MATERIALVAR_ACCESS;"
        "USE_ACTUAL_DX;"
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
            /ignore:4221
            )
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf

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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )


set(PROJECT_NAME stdshader_dx8)

################################################################################
# Source groups
################################################################################
set(______
        "../../devtools/bin/fxc_prep.pl"
        "../../devtools/bin/psh_prep.pl"
        "../../devtools/bin/vsh_prep.pl"
        )
source_group("
" FILES ${______})

set(Header_Files
        "BaseVSShader.h"
        "eyes_dx8_dx9_helper.h"
        "worldvertextransition_dx8_helper.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../common/debug_dll_check.cpp"
        "../../public/tier0/memoverride.cpp"
        "BaseVSShader.cpp"
        "bik_dx80.cpp"
        "bik_dx81.cpp"
        "BlurFilterX_dx80.cpp"
        "BlurFilterY_dx80.cpp"
        "BufferClearObeyStencil_dx8.cpp"
        "cable_dx8.cpp"
        "cloak_blended_pass_dx8_helper.cpp"
        "cloud_dx8.cpp"
        "core_dx8.cpp"
        "DecalBaseTimesLightmapAlphaBlendSelfIllum_dx8.cpp"
        "detail.cpp"
        "downsample_nohdr_dx80.cpp"
        "dx8fallbacks.cpp"
        "emissive_scroll_blended_pass_dx8_helper.cpp"
        "eyes.cpp"
        "eyes_dx8_dx9_helper.cpp"
        "filmdust_dx8_dx9.cpp"
        "filmgrain_dx8_dx9.cpp"
        "flesh_interior_blended_pass_dx8_helper.cpp"
        "gooinglass.cpp"
        "introscreenspaceeffect_dx80.cpp"
        "lightmappedgeneric_decal.cpp"
        "lightmappedgeneric_dx8.cpp"
        "modulate_dx8.cpp"
        "MonitorScreen_dx8.cpp"
        "occlusion_dx8.cpp"
        "overlay_fit.cpp"
        "particlesphere_dx8.cpp"
        "portal_dx80.cpp"
        "portal_refract_dx8.cpp"
        "portal_refract_dx8_helper.cpp"
        "portalstaticoverlay_dx80.cpp"
        "predator.cpp"
        "refract_dx80.cpp"
        "screenspace_general_dx8.cpp"
        "shadow_dx8.cpp"
        "shadowbuild_dx8.cpp"
        "shadowmodel_dx8.cpp"
        "shatteredglass_dx8.cpp"
        "sprite.cpp"
        "spritecard.cpp"
        "teeth_dx8.cpp"
        "unlitgeneric_dx8.cpp"
        "unlittwotexture_dx8.cpp"
        "vertexlitgeneric_dx8.cpp"
        "vortwarp_dx8.cpp"
        "water_dx80.cpp"
        "water_dx81.cpp"
        "windowimposter_dx80.cpp"
        "wireframe_dx8.cpp"
        "worldtwotextureblend_dx8.cpp"
        "worldvertexalpha_dx8.cpp"
        "WorldVertexTransition_dx8.cpp"
        "worldvertextransition_dx8_helper.cpp"
        "writestencil_dx8.cpp"
        "writez_dx8.cpp"
        "yuv.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${______}
        ${Header_Files}
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
        TARGET_NAME_DEBUG "stdshader_dx8"
        TARGET_NAME_RELEASE "stdshader_dx8"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/fxctmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/vshtmp9;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/include"
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
        "DLLNAME=stdshader_dx8;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "STDSHADER_DX8_DLL_EXPORT;"
        "FAST_MATERIALVAR_ACCESS;"
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
            /Zo;
            /Oy-
            >
            /MP;

            /GF;
            /arch:SSE2;
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
    source_file_compile_options(../../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
            /ignore:4221
            )
endif ()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf



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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )


set(PROJECT_NAME Stdshader_dx7)

################################################################################
# Source groups
################################################################################
set(Source_Files
        "../../common/debug_dll_check.cpp"
        "../../public/tier0/memoverride.cpp"
        "core_dx7.cpp"
        "filmdust_dx7.cpp"
        "filmgrain_dx7.cpp"
        "shatteredglass_dx7.cpp"
        "vertexlitgeneric_dx7.cpp"
        "vortwarp_dx7.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__remove_me_when_VAC2_is_out
        "../../minisef/tier1/checksum_crc.cpp"
        "../../minisef/tier1/checksum_md5.cpp"
        )
source_group("Source Files\\remove me when VAC2 is out" FILES ${Source_Files__remove_me_when_VAC2_is_out})

set(ALL_FILES
        ${Source_Files}
        ${Source_Files__remove_me_when_VAC2_is_out}
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
        TARGET_NAME_DEBUG "stdshader_dx7"
        TARGET_NAME_RELEASE "stdshader_dx7"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/include"
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
        "DLLNAME=stdshader_dx7;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "STDSHADER_DX7_DLL_EXPORT;"
        "FAST_MATERIALVAR_ACCESS;"
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
            /Zo;
            /Oy-
            >
            /MP;

            /GF;
            /arch:SSE2;
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
    source_file_compile_options(../../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
            /ignore:4221
            )
endif ()
################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf

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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )


set(PROJECT_NAME Stdshader_dx6)

################################################################################
# Source groups
################################################################################
set(Header_Files
        "worldvertextransition_dx6_helper.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../common/debug_dll_check.cpp"
        "../../public/tier0/memoverride.cpp"
        "BufferClearObeyStencil_dx6.cpp"
        "cable_dx6.cpp"
        "cloud.cpp"
        "decal.cpp"
        "DecalBaseTimesLightmapAlphaBlendSelfIllum_dx6.cpp"
        "decalmodulate.cpp"
        "eyeball.cpp"
        "eyes_dx6.cpp"
        "introscreenspaceeffect_dx60.cpp"
        "lightmappedgeneric_dx6.cpp"
        "lightmappedtwotexture.cpp"
        "modulate_dx6.cpp"
        "portal_dx60.cpp"
        "portalstaticoverlay_dx60.cpp"
        "refract_dx60.cpp"
        "rift_dx6.cpp"
        "SetZ.cpp"
        "shadow_dx6.cpp"
        "shadowbuild_dx6.cpp"
        "sky_dx6.cpp"
        "sprite_dx6.cpp"
        "teeth_dx6.cpp"
        "unlitgeneric_dx6.cpp"
        "unlittwotexture_dx6.cpp"
        "vertexlitgeneric_dx6.cpp"
        "viewalpha.cpp"
        "volumetricfog.cpp"
        "water_dx60.cpp"
        "worldtwotextureblend_dx6.cpp"
        "worldvertextransition_dx6.cpp"
        "worldvertextransition_dx6_helper.cpp"
        "writez_dx6.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__remove_me_when_VAC2_is_out
        "../../minisef/tier1/checksum_crc.cpp"
        "../../minisef/tier1/checksum_md5.cpp"
        )
source_group("Source Files\\remove me when VAC2 is out" FILES ${Source_Files__remove_me_when_VAC2_is_out})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        ${Source_Files__remove_me_when_VAC2_is_out}
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
        TARGET_NAME_DEBUG "stdshader_dx6"
        TARGET_NAME_RELEASE "stdshader_dx6"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
        "${MYROOTDIR}/thirdparty/SDL2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/include"
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
        "DLLNAME=stdshader_dx6;"
        "BINK_VIDEO;"
        "AVI_VIDEO;"
        "WMV_VIDEO;"
        "DEV_BUILD;"
        "FRAME_POINTER_OMISSION_DISABLED;"
        "STDSHADER_DX6_DLL_EXPORT;"
        "FAST_MATERIALVAR_ACCESS;"
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
            /Zo;
            /Oy-
            >
            /MP;

            /GF;
            /arch:SSE2;
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
    source_file_compile_options(../../common/debug_dll_check.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
            "/Y-"
            )
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
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
            /ignore:4221
            )
endif ()
################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf
        )

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        bitmap
        mathlib
        shaderlib
        tier0
        tier1
        tier2
        vstdlib
        vtf

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
        "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/dxsdk/lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )
