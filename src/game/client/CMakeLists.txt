set(PROJECT_NAME ClientSDK)

################################################################################
# Source groups
################################################################################
set(Game_Shared_Header_Files
    "../shared/activitylist.h"
    "../shared/ai_activity.h"
    "../shared/ai_debug_shared.h"
    "../shared/ammodef.h"
    "../shared/animation.h"
    "../shared/apparent_velocity_helper.h"
    "../shared/base_playeranimstate.h"
    "../shared/baseentity_shared.h"
    "../shared/basegrenade_shared.h"
    "../shared/baseparticleentity.h"
    "../shared/baseplayer_shared.h"
    "../shared/baseviewmodel_shared.h"
    "../shared/beam_flags.h"
    "../shared/beam_shared.h"
    "../shared/choreoactor.h"
    "../shared/choreochannel.h"
    "../shared/choreoevent.h"
    "../shared/choreoscene.h"
    "../shared/collisionproperty.h"
    "../shared/death_pose.h"
    "../shared/decals.h"
    "../shared/effect_color_tables.h"
    "../shared/effect_dispatch_data.h"
    "../shared/ehandle.h"
    "../shared/entitydatainstantiator.h"
    "../shared/entitylist_base.h"
    "../shared/entityparticletrail_shared.h"
    "../shared/env_detail_controller.h"
    "../shared/env_wind_shared.h"
    "../shared/eventlist.h"
    "../shared/func_dust_shared.h"
    "../shared/func_ladder.h"
    "../shared/gameeventdefs.h"
    "../shared/gamemovement.h"
    "../shared/gamerules.h"
    "../shared/gamerules_register.h"
    "../shared/gamestats.h"
    "../shared/gamestringpool.h"
    "../shared/gamevars_shared.h"
    "../shared/groundlink.h"
    "../shared/hl2/basehlcombatweapon_shared.h"
    "../shared/hl2/hl2_player_shared.h"
    "../shared/hl2/hl_movedata.h"
    "../shared/ichoreoeventcallback.h"
    "../shared/IEffects.h"
    "../shared/igamemovement.h"
    "../shared/igamesystem.h"
    "../shared/imovehelper.h"
    "../shared/in_buttons.h"
    "../shared/interval.h"
    "../shared/iplayeranimstate.h"
    "../shared/ipredictionsystem.h"
    "../shared/itempents.h"
    "../shared/IVehicle.h"
    "../shared/mapdata_shared.h"
    "../shared/mapentities_shared.h"
    "../shared/movevars_shared.h"
    "../shared/mp_shareddefs.h"
    "../shared/multiplay_gamerules.h"
    "../shared/npcevent.h"
    "../shared/obstacle_pushaway.h"
    "../shared/physics_saverestore.h"
    "../shared/physics_shared.h"
    "../shared/playernet_vars.h"
    "../shared/point_posecontroller.h"
    "../shared/positionwatcher.h"
    "../shared/precache_register.h"
    "../shared/precipitation_shared.h"
    "../shared/predictable_entity.h"
    "../shared/predictableid.h"
    "../shared/predictioncopy.h"
    "../shared/ragdoll_shared.h"
    "../shared/rope_helpers.h"
    "../shared/saverestore.h"
    "../shared/saverestore_bitstring.h"
    "../shared/saverestore_utlclass.h"
    "../shared/saverestore_utlsymbol.h"
    "../shared/saverestore_utlvector.h"
    "../shared/sceneentity_shared.h"
    "../shared/scriptevent.h"
    "../shared/sequence_Transitioner.h"
    "../shared/shared_classnames.h"
    "../shared/shareddefs.h"
    "../shared/sharedInterface.h"
    "../shared/sheetsimulator.h"
    "../shared/shot_manipulator.h"
    "../shared/simtimer.h"
    "../shared/singleplay_gamerules.h"
    "../shared/smoke_fog_overlay_shared.h"
    "../shared/solidsetdefaults.h"
    "../shared/soundenvelope.h"
    "../shared/Sprite.h"
    "../shared/SpriteTrail.h"
    "../shared/sun_shared.h"
    "../shared/takedamageinfo.h"
    "../shared/teamplay_gamerules.h"
    "../shared/teamplayroundbased_gamerules.h"
    "../shared/tempentity.h"
    "../shared/touchlink.h"
    "../shared/usercmd.h"
    "../shared/usermessages.h"
    "../shared/util_shared.h"
    "../shared/vehicle_choreo_generic_shared.h"
    "../shared/vehicle_viewblend_shared.h"
    "../shared/vgui_defaultinputsignal.h"
    "../shared/viewport_panel_names.h"
    "../shared/voice_banmgr.h"
    "../shared/voice_common.h"
    "../shared/voice_gamemgr.h"
    "../shared/voice_status.h"
    "../shared/vphysics_sound.h"
    "../shared/weapon_ifmsteadycam.h"
    "../shared/weapon_parse.h"
    "../shared/weapon_proficiency.h"
)
source_group("Game Shared Header Files" FILES ${Game_Shared_Header_Files})

set(Header_Files
    "../../common/language.h"
    "../../public/steam/steam_api.h"
    "../shared/econ/ihasowner.h"
    "../shared/GameEventListener.h"
    "../shared/hintmessage.h"
    "../shared/hintsystem.h"
    "animationlayer.h"
    "baseanimatedtextureproxy.h"
    "baseclientrendertargets.h"
    "basepresence.h"
    "beamdraw.h"
    "bone_merge_cache.h"
    "c_ai_basenpc.h"
    "c_baseanimating.h"
    "c_baseanimatingoverlay.h"
    "c_basecombatcharacter.h"
    "c_basecombatweapon.h"
    "c_basedoor.h"
    "c_baseentity.h"
    "c_baseflex.h"
    "c_baseplayer.h"
    "c_basetempentity.h"
    "c_baseviewmodel.h"
    "c_breakableprop.h"
    "c_effects.h"
    "c_entitydissolve.h"
    "c_env_fog_controller.h"
    "c_fire_smoke.h"
    "c_func_dust.h"
    "c_func_reflective_glass.h"
    "c_gib.h"
    "c_impact_effects.h"
    "c_physbox.h"
    "c_physicsprop.h"
    "c_pixel_visibility.h"
    "c_playerlocaldata.h"
    "c_playerresource.h"
    "c_point_camera.h"
    "c_prop_vehicle.h"
    "c_recipientfilter.h"
    "c_rope.h"
    "c_rumble.h"
    "c_sceneentity.h"
    "c_smoke_trail.h"
    "c_soundscape.h"
    "c_sprite.h"
    "c_sun.h"
    "c_te_basebeam.h"
    "c_te_effect_dispatch.h"
    "c_te_legacytempents.h"
    "c_te_particlesystem.h"
    "c_team.h"
    "c_tesla.h"
    "c_tracer.h"
    "c_user_message_register.h"
    "c_vehicle_jeep.h"
    "c_vguiscreen.h"
    "c_weapon__stubs.h"
    "c_world.h"
    "cbase.h"
    "cdll_client_int.h"
    "cdll_util.h"
    "cl_animevent.h"
    "cl_mat_stub.h"
    "client_factorylist.h"
    "client_thinklist.h"
    "clienteffectprecachesystem.h"
    "cliententitylist.h"
    "clientleafsystem.h"
    "clientmode.h"
    "clientmode_shared.h"
    "clientsideeffects.h"
    "colorcorrectionmgr.h"
    "detailobjectsystem.h"
    "enginesprite.h"
    "flashlighteffect.h"
    "fontabc.h"
    "functionproxy.h"
    "fx.h"
    "fx_blood.h"
    "fx_discreetline.h"
    "fx_envelope.h"
    "fx_explosion.h"
    "fx_fleck.h"
    "fx_impact.h"
    "fx_interpvalue.h"
    "fx_line.h"
    "fx_quad.h"
    "fx_sparks.h"
    "fx_staticline.h"
    "fx_trail.h"
    "fx_water.h"
    "glow_outline_effect.h"
    "glow_overlay.h"
    "history_resource.h"
    "hltvcamera.h"
    "hud.h"
    "hud_basechat.h"
    "hud_basetimer.h"
    "hud_bitmapnumericdisplay.h"
    "hud_chat.h"
    "hud_closecaption.h"
    "hud_crosshair.h"
    "hud_element_helper.h"
    "hud_lcd.h"
    "hud_macros.h"
    "hud_numericdisplay.h"
    "hud_pdump.h"
    "hud_vehicle.h"
    "hudelement.h"
    "hudtexturehandle.h"
    "iclassmap.h"
    "icliententityinternal.h"
    "iclientmode.h"
    "iclientshadowmgr.h"
    "iclientvehicle.h"
    "iconsole.h"
    "idebugoverlaypanel.h"
    "ifpspanel.h"
    "ihudlcd.h"
    "iinput.h"
    "iloadingdisc.h"
    "imessagechars.h"
    "in_main.h"
    "inetgraphpanel.h"
    "initializer.h"
    "input.h"
    "interpolatedvar.h"
    "ipresence.h"
    "iprofiling.h"
    "itextmessage.h"
    "ivieweffects.h"
    "iviewrender.h"
    "iviewrender_beams.h"
    "ivmodemanager.h"
    "kbutton.h"
    "lerp_functions.h"
    "menu.h"
    "movehelper_client.h"
    "mumble.h"
    "networkstringtable_clientdll.h"
    "panelmetaclassmgr.h"
    "particle_collision.h"
    "particle_iterators.h"
    "particle_litsmokeemitter.h"
    "particle_prototype.h"
    "particle_simple3d.h"
    "particle_util.h"
    "particledraw.h"
    "particlemgr.h"
    "particles_attractor.h"
    "particles_ez.h"
    "particles_localspace.h"
    "particles_new.h"
    "particles_simple.h"
    "particlesphererenderer.h"
    "perfvisualbenchmark.h"
    "physics.h"
    "physpropclientside.h"
    "playerandobjectenumerator.h"
    "playerenumerator.h"
    "playerspawncache.h"
    "prediction.h"
    "prediction_private.h"
    "proxyentity.h"
    "ragdoll.h"
    "ragdollexplosionenumerator.h"
    "recvproxy.h"
    "rendertexture.h"
    "ScreenSpaceEffects.h"
    "simple_keys.h"
    "smoke_fog_overlay.h"
    "splinepatch.h"
    "TeamBitmapImage.h"
    "tempent.h"
    "text_message.h"
    "timedevent.h"
    "toggletextureproxy.h"
    "vgui_basepanel.h"
    "vgui_bitmapbutton.h"
    "vgui_bitmapimage.h"
    "vgui_bitmappanel.h"
    "vgui_entityimagepanel.h"
    "vgui_entitypanel.h"
    "vgui_grid.h"
    "vgui_helpers.h"
    "vgui_imagehealthpanel.h"
    "vgui_int.h"
    "vgui_schemevisualizer.h"
    "vgui_video.h"
    "vgui_video_player.h"
    "vguicenterprint.h"
    "view.h"
    "view_scene.h"
    "viewangleanim.h"
    "ViewConeImage.h"
    "viewrender.h"
    "weapon_selection.h"
    "weapons_resource.h"
)
source_group("Header Files" FILES ${Header_Files})

set(MP3
    "mp3player.cpp"
    "mp3player.h"
)
source_group("MP3" FILES ${MP3})

set(Public_Header_Files
    "../../public/appframework/IAppSystem.h"
    "../../public/basehandle.h"
    "../../public/bitvec.h"
    "../../public/bone_accessor.h"
    "../../public/bone_setup.h"
    "../../public/bspfile.h"
    "../../public/bspflags.h"
    "../../public/bsptreedata.h"
    "../../public/cdll_int.h"
    "../../public/client_class.h"
    "../../public/client_render_handle.h"
    "../../public/client_textmessage.h"
    "../../public/clientstats.h"
    "../../public/cmodel.h"
    "../../public/collisionutils.h"
    "../../public/Color.h"
    "../../public/con_nprint.h"
    "../../public/const.h"
    "../../public/coordsize.h"
    "../../public/crtmemdebug.h"
    "../../public/datamap.h"
    "../../public/dlight.h"
    "../../public/dt_common.h"
    "../../public/dt_recv.h"
    "../../public/dt_send.h"
    "../../public/dt_utlvector_common.h"
    "../../public/dt_utlvector_recv.h"
    "../../public/edict.h"
    "../../public/engine/IClientLeafSystem.h"
    "../../public/engine/ICollideable.h"
    "../../public/engine/IEngineSound.h"
    "../../public/engine/IEngineTrace.h"
    "../../public/engine/ishadowmgr.h"
    "../../public/engine/IStaticPropMgr.h"
    "../../public/engine/ivdebugoverlay.h"
    "../../public/engine/ivmodelinfo.h"
    "../../public/engine/ivmodelrender.h"
    "../../public/filesystem.h"
    "../../public/filesystem_helpers.h"
    "../../public/game/client/iclientrendertargets.h"
    "../../public/game/client/iviewport.h"
    "../../public/gamebspfile.h"
    "../../public/gametrace.h"
    "../../public/globalvars_base.h"
    "../../public/haptics/haptic_utils.h"
    "../../public/haptics/ihaptics.h"
    "../../public/iachievementmgr.h"
    "../../public/icliententity.h"
    "../../public/icliententitylist.h"
    "../../public/iclientnetworkable.h"
    "../../public/iclientrenderable.h"
    "../../public/iclientthinkable.h"
    "../../public/iclientunknown.h"
    "../../public/icvar.h"
    "../../public/iefx.h"
    "../../public/ienginevgui.h"
    "../../public/igameevents.h"
    "../../public/igameresources.h"
    "../../public/IGameUIFuncs.h"
    "../../public/ihandleentity.h"
    "../../public/imapoverview.h"
    "../../public/inetchannelinfo.h"
    "../../public/interpolatortypes.h"
    "../../public/iprediction.h"
    "../../public/irecipientfilter.h"
    "../../public/isaverestore.h"
    "../../public/iscratchpad3d.h"
    "../../public/iserverentity.h"
    "../../public/iservernetworkable.h"
    "../../public/iserverunknown.h"
    "../../public/ispatialpartition.h"
    "../../public/istudiorender.h"
    "../../public/ivguicenterprint.h"
    "../../public/ivrenderview.h"
    "../../public/jigglebones.h"
    "../../public/materialsystem/imaterial.h"
    "../../public/materialsystem/imaterialproxy.h"
    "../../public/materialsystem/imaterialsystem.h"
    "../../public/materialsystem/imaterialsystemhardwareconfig.h"
    "../../public/materialsystem/imaterialsystemstub.h"
    "../../public/materialsystem/imaterialvar.h"
    "../../public/materialsystem/imesh.h"
    "../../public/materialsystem/itexture.h"
    "../../public/mathlib/amd3dx.h"
    "../../public/mathlib/bumpvects.h"
    "../../public/mathlib/compressed_light_cube.h"
    "../../public/mathlib/compressed_vector.h"
    "../../public/mathlib/mathlib.h"
    "../../public/mathlib/polyhedron.h"
    "../../public/mathlib/vector.h"
    "../../public/mathlib/vector2d.h"
    "../../public/mathlib/vector4d.h"
    "../../public/mathlib/vmatrix.h"
    "../../public/mathlib/vplane.h"
    "../../public/model_types.h"
    "../../public/mouthinfo.h"
    "../../public/networkstringtabledefs.h"
    "../../public/networkvar.h"
    "../../public/overlaytext.h"
    "../../public/pixelwriter.h"
    "../../public/PlayerState.h"
    "../../public/r_efx.h"
    "../../public/renamed_recvtable_compat.h"
    "../../public/rope_physics.h"
    "../../public/rope_shared.h"
    "../../public/saverestoretypes.h"
    "../../public/scratchpad3d.h"
    "../../public/ScratchPadUtils.h"
    "../../public/sentence.h"
    "../../public/server_class.h"
    "../../public/shake.h"
    "../../public/shattersurfacetypes.h"
    "../../public/simple_physics.h"
    "../../public/soundchars.h"
    "../../public/SoundEmitterSystem/isoundemittersystembase.h"
    "../../public/soundflags.h"
    "../../public/soundinfo.h"
    "../../public/string_t.h"
    "../../public/stringregistry.h"
    "../../public/studio.h"
    "../../public/surfinfo.h"
    "../../public/texture_group_names.h"
    "../../public/tier0/basetypes.h"
    "../../public/tier0/commonmacros.h"
    "../../public/tier0/dbg.h"
    "../../public/tier0/fasttimer.h"
    "../../public/tier0/icommandline.h"
    "../../public/tier0/l2cache.h"
    "../../public/tier0/mem.h"
    "../../public/tier0/memalloc.h"
    "../../public/tier0/memdbgoff.h"
    "../../public/tier0/memdbgon.h"
    "../../public/tier0/platform.h"
    "../../public/tier0/protected_things.h"
    "../../public/tier0/vprof.h"
    "../../public/tier1/bitbuf.h"
    "../../public/tier1/characterset.h"
    "../../public/tier1/checksum_md5.h"
    "../../public/tier1/convar.h"
    "../../public/tier1/fmtstr.h"
    "../../public/tier1/interface.h"
    "../../public/tier1/KeyValues.h"
    "../../public/tier1/mempool.h"
    "../../public/tier1/processor_detect.h"
    "../../public/tier1/rangecheckedvar.h"
    "../../public/tier1/smartptr.h"
    "../../public/tier1/stringpool.h"
    "../../public/tier1/strtools.h"
    "../../public/tier1/utlbidirectionalset.h"
    "../../public/tier1/utlbuffer.h"
    "../../public/tier1/utldict.h"
    "../../public/tier1/utlfixedmemory.h"
    "../../public/tier1/utlhash.h"
    "../../public/tier1/utllinkedlist.h"
    "../../public/tier1/utlmap.h"
    "../../public/tier1/utlmemory.h"
    "../../public/tier1/utlmultilist.h"
    "../../public/tier1/utlpriorityqueue.h"
    "../../public/tier1/utlqueue.h"
    "../../public/tier1/utlrbtree.h"
    "../../public/tier1/utlstack.h"
    "../../public/tier1/utlsymbol.h"
    "../../public/tier1/utlvector.h"
    "../../public/vallocator.h"
    "../../public/vcollide.h"
    "../../public/vcollide_parse.h"
    "../../public/vgui/Cursor.h"
    "../../public/vgui/Dar.h"
    "../../public/vgui/IClientPanel.h"
    "../../public/vgui/IHTML.h"
    "../../public/vgui/IImage.h"
    "../../public/vgui/IInput.h"
    "../../public/vgui/IInputInternal.h"
    "../../public/vgui/ILocalize.h"
    "../../public/vgui/IPanel.h"
    "../../public/vgui/IScheme.h"
    "../../public/vgui/ISurface.h"
    "../../public/vgui/ISystem.h"
    "../../public/vgui/IVGui.h"
    "../../public/vgui/KeyCode.h"
    "../../public/vgui/MouseCode.h"
    "../../public/vgui/VGUI.h"
    "../../public/vgui_controls/AnimationController.h"
    "../../public/vgui_controls/Button.h"
    "../../public/vgui_controls/ComboBox.h"
    "../../public/vgui_controls/Controls.h"
    "../../public/vgui_controls/EditablePanel.h"
    "../../public/vgui_controls/FocusNavGroup.h"
    "../../public/vgui_controls/HTML.h"
    "../../public/vgui_controls/Image.h"
    "../../public/vgui_controls/ImageList.h"
    "../../public/vgui_controls/ImagePanel.h"
    "../../public/vgui_controls/Label.h"
    "../../public/vgui_controls/ListPanel.h"
    "../../public/vgui_controls/Menu.h"
    "../../public/vgui_controls/MenuItem.h"
    "../../public/vgui_controls/MessageMap.h"
    "../../public/vgui_controls/Panel.h"
    "../../public/vgui_controls/PanelAnimationVar.h"
    "../../public/vgui_controls/PanelListPanel.h"
    "../../public/vgui_controls/PHandle.h"
    "../../public/vgui_controls/RichText.h"
    "../../public/vgui_controls/ScrollBar.h"
    "../../public/vgui_controls/SectionedListPanel.h"
    "../../public/vgui_controls/TextEntry.h"
    "../../public/vgui_controls/TextImage.h"
    "../../public/vgui_controls/TreeView.h"
    "../../public/vgui_controls/WizardPanel.h"
    "../../public/vgui_controls/WizardSubPanel.h"
    "../../public/VGuiMatSurface/IMatSystemSurface.h"
    "../../public/view_shared.h"
    "../../public/vphysics/collision_set.h"
    "../../public/vphysics/constraints.h"
    "../../public/vphysics/friction.h"
    "../../public/vphysics/object_hash.h"
    "../../public/vphysics_interface.h"
    "../../public/vstdlib/IKeyValuesSystem.h"
    "../../public/vstdlib/random.h"
    "../../public/vstdlib/vstdlib.h"
    "../../public/vtf/vtf.h"
    "../../public/worldsize.h"
    "../../public/zip_uncompressed.h"
)
source_group("Public Header Files" FILES ${Public_Header_Files})

set(Replay
#    "../shared/replay_gamestats_shared.cpp"
#    "../shared/replay_gamestats_shared.h"
    "replay/cdll_replay.cpp"
    "replay/cdll_replay.h"
#    "replay/gamedefs.cpp"
#    "replay/gamedefs.h"
#    "replay/genericclassbased_replay.cpp"
#    "replay/genericclassbased_replay.h"
#    "replay/replay_ragdoll.cpp"
#    "replay/replay_ragdoll.h"
#    "replay/replay_screenshot.cpp"
#    "replay/replay_screenshot.h"
    "replay/replaycamera.cpp"
    "replay/replaycamera.h"
#    "replay/replayperformanceplaybackhandler.cpp"
#    "replay/replayperformanceplaybackhandler.h"
#    "replay/replayrenderer.cpp"
#    "replay/replayrenderer.h"
#    "replay/replayvideo.cpp"
#    "replay/replayvideo.h"
#    "youtubeapi.h"
)
source_group("Replay" FILES ${Replay})

set(Source_Files
    "../../common/compiledcaptionswap.cpp"
    "../../common/language.cpp"
    "../../common/randoverride.cpp"
    "../../public/bone_accessor.cpp"
    "../../public/bone_setup.cpp"
    "../../public/client_class.cpp"
    "../../public/collisionutils.cpp"
    "../../public/crtmemdebug.cpp"
    "../../public/dt_recv.cpp"
    "../../public/dt_utlvector_common.cpp"
    "../../public/dt_utlvector_recv.cpp"
    "../../public/filesystem_helpers.cpp"
    "../../public/haptics/haptic_msgs.cpp"
    "../../public/haptics/haptic_utils.cpp"
    "../../public/interpolatortypes.cpp"
    "../../public/jigglebones.cpp"
    "../../public/networkvar.cpp"
    "../../public/posedebugger.cpp"
    "../../public/renamed_recvtable_compat.cpp"
    "../../public/rope_physics.cpp"
    "../../public/scratchpad3d.cpp"
    "../../public/ScratchPadUtils.cpp"
    "../../public/sentence.cpp"
    "../../public/simple_physics.cpp"
    "../../public/SoundParametersInternal.cpp"
    "../../public/stringregistry.cpp"
    "../../public/studio.cpp"
    "../../public/tier0/memoverride.cpp"
    "../../public/vallocator.cpp"
    "../../public/vgui_controls/vgui_controls.cpp"
    "../shared/achievement_saverestore.cpp"
    "../shared/achievement_saverestore.h"
    "../shared/achievementmgr.cpp"
    "../shared/achievementmgr.h"
    "../shared/achievements_and_stats_interface.h"
    "../shared/achievements_hlx.cpp"
    "../shared/activitylist.cpp"
    "../shared/ammodef.cpp"
    "../shared/animation.cpp"
    "../shared/base_playeranimstate.cpp"
    "../shared/baseachievement.cpp"
    "../shared/baseachievement.h"
    "../shared/basecombatcharacter_shared.cpp"
    "../shared/basecombatweapon_shared.cpp"
    "../shared/baseentity_shared.cpp"
    "../shared/basegrenade_shared.cpp"
    "../shared/baseparticleentity.cpp"
    "../shared/baseplayer_shared.cpp"
    "../shared/baseprojectile.cpp"
    "../shared/baseprojectile.h"
    "../shared/baseviewmodel_shared.cpp"
    "../shared/beam_shared.cpp"
    "../shared/cam_thirdperson.cpp"
    "../shared/cam_thirdperson.h"
    "../shared/collisionproperty.cpp"
    "../shared/death_pose.cpp"
    "../shared/debugoverlay_shared.cpp"
    "../shared/decals.cpp"
    "../shared/effect_dispatch_data.cpp"
    "../shared/ehandle.cpp"
    "../shared/entitylist_base.cpp"
    "../shared/EntityParticleTrail_Shared.cpp"
    "../shared/env_detail_controller.cpp"
    "../shared/env_wind_shared.cpp"
    "../shared/eventlist.cpp"
    "../shared/func_ladder.cpp"
    "../shared/gamemovement.cpp"
    "../shared/gamerules.cpp"
    "../shared/gamerules_register.cpp"
    "../shared/GameStats.cpp"
    "../shared/gamestringpool.cpp"
    "../shared/gamevars_shared.cpp"
    "../shared/hintmessage.cpp"
    "../shared/hintsystem.cpp"
    "../shared/igamesystem.cpp"
    "../shared/interval.cpp"
    "../shared/mapentities_shared.cpp"
    "../shared/movevars_shared.cpp"
    "../shared/mp_shareddefs.cpp"
    "../shared/multiplay_gamerules.cpp"
    "../shared/Multiplayer/multiplayer_animstate.h"
    "../shared/obstacle_pushaway.cpp"
    "../shared/particle_parse.cpp"
    "../shared/particle_parse.h"
    "../shared/particle_property.cpp"
    "../shared/particle_property.h"
    "../shared/particlesystemquery.cpp"
    "../shared/physics_main_shared.cpp"
    "../shared/physics_saverestore.cpp"
    "../shared/physics_shared.cpp"
    "../shared/point_bonusmaps_accessor.cpp"
    "../shared/point_bonusmaps_accessor.h"
    "../shared/point_posecontroller.cpp"
    "../shared/precache_register.cpp"
    "../shared/predictableid.cpp"
    "../shared/predictioncopy.cpp"
    "../shared/props_shared.cpp"
    "../shared/ragdoll_shared.cpp"
    "../shared/rope_helpers.cpp"
    "../shared/saverestore.cpp"
    "../shared/sceneentity_shared.cpp"
    "../shared/sequence_Transitioner.cpp"
    "../shared/sheetsimulator.cpp"
    "../shared/simtimer.cpp"
    "../shared/singleplay_gamerules.cpp"
    "../shared/SoundEmitterSystem.cpp"
    "../shared/soundenvelope.cpp"
    "../shared/Sprite.cpp"
    "../shared/SpriteTrail.cpp"
    "../shared/studio_shared.cpp"
    "../shared/takedamageinfo.cpp"
    "../shared/teamplay_gamerules.cpp"
    "../shared/teamplayroundbased_gamerules.cpp"
    "../shared/test_ehandle.cpp"
    "../shared/usercmd.cpp"
    "../shared/usermessages.cpp"
    "../shared/util_shared.cpp"
    "../shared/vehicle_viewblend_shared.cpp"
    "../shared/voice_banmgr.cpp"
    "../shared/voice_status.cpp"
    "../shared/weapon_parse.cpp"
    "achievement_notification_panel.cpp"
    "achievement_notification_panel.h"
    "alphamaterialproxy.cpp"
    "animatedentitytextureproxy.cpp"
    "animatedoffsettextureproxy.cpp"
    "animatedtextureproxy.cpp"
    "AnimateSpecificTextureProxy.cpp"
    "baseanimatedtextureproxy.cpp"
    "baseclientrendertargets.cpp"
    "basepresence.cpp"
#    "basepresence_xbox.cpp"
    "beamdraw.cpp"
    "bone_merge_cache.cpp"
    "c_ai_basehumanoid.cpp"
    "c_ai_basenpc.cpp"
    "c_baseanimating.cpp"
    "c_baseanimatingoverlay.cpp"
    "c_basecombatcharacter.cpp"
    "c_basecombatweapon.cpp"
    "c_basedoor.cpp"
    "c_baseentity.cpp"
    "c_baseflex.cpp"
    "c_baseplayer.cpp"
    "c_baseviewmodel.cpp"
    "c_breakableprop.cpp"
    "c_colorcorrection.cpp"
    "c_colorcorrectionvolume.cpp"
    "c_dynamiclight.cpp"
    "c_entitydissolve.cpp"
    "c_entityparticletrail.cpp"
    "c_env_fog_controller.cpp"
    "c_env_particlescript.cpp"
    "c_env_projectedtexture.cpp"
    "c_env_screenoverlay.cpp"
    "c_env_tonemap_controller.cpp"
    "c_fire_smoke.cpp"
    "c_fish.cpp"
    "c_func_areaportalwindow.cpp"
    "c_func_breakablesurf.cpp"
    "c_func_conveyor.cpp"
    "c_func_dust.cpp"
    "c_func_lod.cpp"
    "c_func_occluder.cpp"
    "c_func_reflective_glass.cpp"
    "c_func_rotating.cpp"
    "c_func_smokevolume.cpp"
    "c_func_tracktrain.cpp"
    "c_gib.cpp"
    "c_hairball.cpp"
    "c_info_overlay_accessor.cpp"
    "c_lightglow.cpp"
    "C_MaterialModifyControl.cpp"
    "c_particle_system.cpp"
    "c_physbox.cpp"
    "c_physicsprop.cpp"
    "c_physmagnet.cpp"
    "c_pixel_visibility.cpp"
    "c_plasma.cpp"
    "c_playerresource.cpp"
    "c_point_camera.cpp"
    "c_point_commentary_node.cpp"
    "c_props.cpp"
    "c_props.h"
    "c_ragdoll_manager.cpp"
    "c_rope.cpp"
    "c_rumble.cpp"
    "c_sceneentity.cpp"
    "c_shadowcontrol.cpp"
    "c_slideshow_display.cpp"
    "c_slideshow_display.h"
    "c_soundscape.cpp"
    "c_spotlight_end.cpp"
    "c_sprite.cpp"
    "c_sprite_perfmonitor.cpp"
    "c_sun.cpp"
    "c_team.cpp"
    "c_team_objectiveresource.cpp"
    "c_team_objectiveresource.h"
    "c_tesla.cpp"
    "c_test_proxytoggle.cpp"
    "c_user_message_register.cpp"
    "c_vehicle_choreo_generic.cpp"
    "c_vehicle_jeep.cpp"
    "c_vguiscreen.cpp"
    "c_vote_controller.cpp"
    "c_vote_controller.h"
    "C_WaterLODControl.cpp"
    "c_world.cpp"
    "camomaterialproxy.cpp"
    "cdll_bounded_cvars.cpp"
    "cdll_bounded_cvars.h"
    "cdll_client_int.cpp"
    "cdll_util.cpp"
    "cl_mat_stub.cpp"
    "classmap.cpp"
    "client_factorylist.cpp"
    "client_thinklist.cpp"
    "client_virtualreality.cpp"
    "client_virtualreality.h"
    "clienteffectprecachesystem.cpp"
    "cliententitylist.cpp"
    "clientleafsystem.cpp"
    "clientmode_shared.cpp"
    "clientshadowmgr.cpp"
    "clientsideeffects.cpp"
    "clientsideeffects_test.cpp"
    "clientsteamcontext.cpp"
    "clientsteamcontext.h"
    "colorcorrectionmgr.cpp"
    "commentary_modelviewer.cpp"
    "commentary_modelviewer.h"
    "detailobjectsystem.cpp"
    "dummyproxy.cpp"
    "EffectsClient.cpp"
    "entityoriginmaterialproxy.cpp"
    "flashlighteffect.cpp"
    "functionproxy.cpp"
    "fx_blood.cpp"
    "fx_cube.cpp"
    "fx_explosion.cpp"
    "fx_fleck.cpp"
    "fx_impact.cpp"
    "fx_interpvalue.cpp"
    "fx_quad.cpp"
    "fx_shelleject.cpp"
    "fx_staticline.cpp"
    "fx_tracer.cpp"
    "fx_trail.cpp"
    "fx_water.cpp"
    "gametrace_client.cpp"
    "geiger.cpp"
    "glow_outline_effect.cpp"
    "glow_overlay.cpp"
    "history_resource.cpp"
    "hl2/C_Func_Monitor.cpp"
    "hl2/c_waterbullet.cpp"
    "hl2/hud_autoaim.cpp"
    "hl2/hud_filmdemo.cpp"
    "hl2/hud_hdrdemo.cpp"
    "hltvcamera.cpp"
    "hud.cpp"
    "hud_animationinfo.cpp"
    "hud_basechat.cpp"
    "hud_basetimer.cpp"
    "hud_bitmapnumericdisplay.cpp"
    "hud_chat.cpp"
    "hud_closecaption.cpp"
    "hud_crosshair.cpp"
    "hud_element_helper.cpp"
    "hud_hintdisplay.cpp"
    "hud_lcd.cpp"
    "hud_msg.cpp"
    "hud_numericdisplay.cpp"
    "hud_pdump.cpp"
    "hud_redraw.cpp"
    "hud_vehicle.cpp"
    "hud_weapon.cpp"
    "in_camera.cpp"
    "in_joystick.cpp"
    "in_main.cpp"
    "in_mouse.cpp"
    "initializer.cpp"
    "interpolatedvar.cpp"
    "IsNPCProxy.cpp"
    "lampbeamproxy.cpp"
    "lamphaloproxy.cpp"
    "mathproxy.cpp"
    "matrixproxy.cpp"
    "menu.cpp"
    "message.cpp"
    "movehelper_client.cpp"
    "mumble.cpp"
    "panelmetaclassmgr.cpp"
    "particle_collision.cpp"
    "particle_litsmokeemitter.cpp"
    "particle_proxies.cpp"
    "particle_simple3d.cpp"
    "particlemgr.cpp"
    "particles_attractor.cpp"
    "particles_ez.cpp"
    "particles_localspace.cpp"
    "particles_new.cpp"
    "particles_simple.cpp"
    "perfvisualbenchmark.cpp"
    "physics.cpp"
    "physics_main_client.cpp"
    "physpropclientside.cpp"
    "playerandobjectenumerator.cpp"
    "playerspawncache.cpp"
    "prediction.cpp"
    "proxyentity.cpp"
    "ProxyHealth.cpp"
    "proxyplayer.cpp"
    "proxypupil.cpp"
    "ragdoll.cpp"
    "recvproxy.cpp"
    "rendertexture.cpp"
    "ScreenSpaceEffects.cpp"
    "simple_keys.cpp"
    "splinepatch.cpp"
    "spritemodel.cpp"
    "studio_stats.cpp"
    "studio_stats.h"
    "text_message.cpp"
    "texturescrollmaterialproxy.cpp"
    "timematerialproxy.cpp"
    "toggletextureproxy.cpp"
    "train.cpp"
    "vgui_avatarimage.cpp"
    "vgui_avatarimage.h"
    "vgui_basepanel.cpp"
    "vgui_bitmapbutton.cpp"
    "vgui_bitmapimage.cpp"
    "vgui_bitmappanel.cpp"
    "vgui_centerstringpanel.cpp"
    "vgui_consolepanel.cpp"
    "vgui_debugoverlaypanel.cpp"
    "vgui_fpspanel.cpp"
    "vgui_game_viewport.cpp"
    "vgui_grid.cpp"
    "vgui_int.cpp"
    "vgui_loadingdiscpanel.cpp"
    "vgui_messagechars.cpp"
    "vgui_netgraphpanel.cpp"
    "vgui_schemevisualizer.cpp"
    "vgui_slideshow_display_screen.cpp"
    "vgui_video.cpp"
    "vgui_video_player.cpp"
    "view.cpp"
    "view_beams.cpp"
    "view_effects.cpp"
    "view_scene.cpp"
    "viewangleanim.cpp"
    "ViewConeImage.cpp"
    "viewdebug.cpp"
    "viewdebug.h"
    "viewpostprocess.cpp"
    "viewpostprocess.h"
    "viewrender.cpp"
    "warp_overlay.cpp"
    "WaterLODMaterialProxy.cpp"
    "weapon_selection.cpp"
    "weapons_resource.cpp"
    "WorldDimsProxy.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__HL2_DLL
    "../shared/episodic/achievements_ep1.cpp"
    "../shared/episodic/achievements_ep2.cpp"
    "../shared/episodic/achievements_epx.cpp"
    "../shared/episodic/npc_advisor_shared.h"
    "../shared/hl2/basehlcombatweapon_shared.cpp"
    "../shared/hl2/citadel_effects_shared.h"
    "../shared/hl2/env_headcrabcanister_shared.cpp"
    "../shared/hl2/env_headcrabcanister_shared.h"
    "../shared/hl2/hl2_gamerules.cpp"
    "../shared/hl2/hl2_gamerules.h"
    "../shared/hl2/hl2_shareddefs.h"
    "../shared/hl2/hl2_usermessages.cpp"
    "../shared/hl2/hl_gamemovement.cpp"
    "../shared/hl2/hl_gamemovement.h"
    "../shared/hl2/survival_gamerules.cpp"
    "../shared/script_intro_shared.cpp"
    "death.cpp"
    "episodic/c_npc_advisor.cpp"
    "episodic/c_npc_puppet.cpp"
    "episodic/c_prop_scalable.cpp"
    "episodic/c_vehicle_jeep_episodic.cpp"
    "episodic/c_vort_charge_token.cpp"
    "episodic/c_weapon_hopwire.cpp"
    "episodic/episodic_screenspaceeffects.cpp"
    "episodic/episodic_screenspaceeffects.h"
    "episodic/flesh_internal_material_proxy.cpp"
    "hl2/c_antlion_dust.cpp"
    "hl2/c_ar2_explosion.cpp"
    "hl2/c_barnacle.cpp"
    "hl2/c_barney.cpp"
    "hl2/c_basehelicopter.cpp"
    "hl2/c_basehelicopter.h"
    "hl2/c_basehlcombatweapon.cpp"
    "hl2/c_basehlcombatweapon.h"
    "hl2/c_basehlplayer.cpp"
    "hl2/c_basehlplayer.h"
    "hl2/c_citadel_effects.cpp"
    "hl2/c_corpse.cpp"
    "hl2/c_corpse.h"
    "hl2/c_env_alyxtemp.cpp"
    "hl2/c_env_headcrabcanister.cpp"
    "hl2/c_env_starfield.cpp"
    "hl2/c_func_tankmortar.cpp"
    "hl2/c_hl2_playerlocaldata.cpp"
    "hl2/c_hl2_playerlocaldata.h"
    "hl2/c_info_teleporter_countdown.cpp"
    "hl2/c_npc_antlionguard.cpp"
    "hl2/c_npc_combinegunship.cpp"
    "hl2/c_npc_manhack.cpp"
    "hl2/c_npc_rollermine.cpp"
    "hl2/c_plasma_beam_node.cpp"
    "hl2/c_prop_combine_ball.cpp"
    "hl2/c_prop_combine_ball.h"
    "hl2/c_rotorwash.cpp"
    "hl2/c_script_intro.cpp"
    "hl2/c_strider.cpp"
    "hl2/c_te_concussiveexplosion.cpp"
    "hl2/c_te_flare.cpp"
    "hl2/c_thumper_dust.cpp"
    "hl2/c_vehicle_airboat.cpp"
    "hl2/c_vehicle_cannon.cpp"
    "hl2/c_vehicle_crane.cpp"
    "hl2/c_vehicle_crane.h"
    "hl2/c_vehicle_prisoner_pod.cpp"
    "hl2/c_weapon__stubs_hl2.cpp"
    "hl2/c_weapon_crossbow.cpp"
    "hl2/c_weapon_physcannon.cpp"
    "hl2/c_weapon_stunstick.cpp"
    "hl2/clientmode_hlnormal.cpp"
    "hl2/clientmode_hlnormal.h"
    "hl2/fx_antlion.cpp"
    "hl2/fx_bugbait.cpp"
    "hl2/fx_hl2_impacts.cpp"
    "hl2/fx_hl2_tracers.cpp"
    "hl2/hl2_clientmode.cpp"
    "hl2/hl_in_main.cpp"
    "hl2/hl_prediction.cpp"
    "hl2/hud_ammo.cpp"
    "hl2/hud_battery.cpp"
    "hl2/hud_blood.cpp"
    "hl2/hud_credits.cpp"
    "hl2/hud_damageindicator.cpp"
    "hl2/hud_flashlight.cpp"
    "hl2/hud_health.cpp"
    "hl2/hud_locator.cpp"
    "hl2/hud_poisondamageindicator.cpp"
    "hl2/hud_quickinfo.cpp"
    "hl2/hud_radar.cpp"
    "hl2/hud_radar.h"
    "hl2/hud_suitpower.cpp"
    "hl2/hud_suitpower.h"
    "hl2/hud_zoom.cpp"
    "hl2/shieldproxy.cpp"
    "hl2/vgui_rootpanel_hl2.cpp"
    "hud_posture.cpp"
    "hud_squadstatus.cpp"
)
source_group("Source Files\\HL2 DLL" FILES ${Source_Files__HL2_DLL})

set(Source_Files__Precompiled_Header
    "stdafx.cpp"
)
source_group("Source Files\\Precompiled Header" FILES ${Source_Files__Precompiled_Header})

set(Source_Files__Sixense
    "../shared/sixense/sixense_convars.cpp"
    "../shared/sixense/sixense_convars_extern.h"
    "sixense/in_sixense.cpp"
    "sixense/in_sixense.h"
    "sixense/in_sixense_gesture_bindings.cpp"
    "sixense/in_sixense_gesture_bindings.h"
)
source_group("Source Files\\Sixense" FILES ${Source_Files__Sixense})

set(Source_Files__Temporary_Entities
    "c_basetempentity.cpp"
    "c_effects.cpp"
    "c_impact_effects.cpp"
    "c_movie_explosion.cpp"
    "c_particle_fire.cpp"
    "c_particle_smokegrenade.cpp"
    "c_prop_vehicle.cpp"
    "c_recipientfilter.cpp"
    "c_smoke_trail.cpp"
    "c_smokestack.cpp"
    "c_steamjet.cpp"
    "c_stickybolt.cpp"
    "c_te.cpp"
    "c_te_armorricochet.cpp"
    "c_te_basebeam.cpp"
    "c_te_beamentpoint.cpp"
    "c_te_beaments.cpp"
    "c_te_beamfollow.cpp"
    "c_te_beamlaser.cpp"
    "c_te_beampoints.cpp"
    "c_te_beamring.cpp"
    "c_te_beamringpoint.cpp"
    "c_te_beamspline.cpp"
    "c_te_bloodsprite.cpp"
    "c_te_bloodstream.cpp"
    "c_te_breakmodel.cpp"
    "c_te_bspdecal.cpp"
    "c_te_bubbles.cpp"
    "c_te_bubbletrail.cpp"
    "c_te_clientprojectile.cpp"
    "c_te_decal.cpp"
    "c_te_dynamiclight.cpp"
    "c_te_effect_dispatch.cpp"
    "c_te_energysplash.cpp"
    "c_te_explosion.cpp"
    "c_te_fizz.cpp"
    "c_te_footprint.cpp"
    "c_te_glassshatter.cpp"
    "c_te_glowsprite.cpp"
    "c_te_impact.cpp"
    "c_te_killplayerattachments.cpp"
    "c_te_largefunnel.cpp"
    "c_te_legacytempents.cpp"
    "c_te_muzzleflash.cpp"
    "c_te_particlesystem.cpp"
    "c_te_physicsprop.cpp"
    "c_te_playerdecal.cpp"
    "c_te_projecteddecal.cpp"
    "c_te_showline.cpp"
    "c_te_smoke.cpp"
    "c_te_sparks.cpp"
    "c_te_sprite.cpp"
    "c_te_spritespray.cpp"
    "c_te_worlddecal.cpp"
    "c_testtraceline.cpp"
    "c_tracer.cpp"
    "fx.cpp"
    "fx_discreetline.cpp"
    "fx_envelope.cpp"
    "fx_line.cpp"
    "fx_sparks.cpp"
    "particlesphererenderer.cpp"
    "smoke_fog_overlay.cpp"
)
source_group("Source Files\\Temporary Entities" FILES ${Source_Files__Temporary_Entities})

set(Source_Files__VANCE
    "../shared/vance/singleplayer_animstate.cpp"
    "../shared/vance/singleplayer_animstate.h"
    "../shared/vance/vance_baseweapon_shared.cpp"
    "../shared/vance/vance_baseweapon_shared.h"
    "../shared/vance/vance_gamerules.cpp"
    "../shared/vance/vance_gamerules.h"
    "../shared/vance/vance_shareddefs.h"
    "../shared/vance/vance_viewmodel.cpp"
    "../shared/vance/vance_viewmodel.h"
    "../shared/vance/vance_weapon_parse.cpp"
    "../shared/vance/vance_weapon_parse.h"
    "../shared/vance/weapon_akms.cpp"
    "../shared/vance/weapon_melee.cpp"
    "vance/c_bobmodel.cpp"
    "vance/c_bobmodel.h"
    "vance/c_env_global_light.cpp"
    "vance/c_env_global_light.h"
    "vance/c_env_skydome.cpp"
    "vance/c_env_skydome.h"
    "vance/c_light_manager.cpp"
    "vance/c_lights_deferred.cpp"
    "vance/c_vance_player.cpp"
    "vance/c_vance_player.h"
    "vance/c_weapon_hacktool.cpp"
    "vance/c_weapon_sniper.cpp"
    "vance/deferred_material_passthru.h"
    "vance/deferred_material_replace.cpp"
    "vance/deferred_screenspace_effects.cpp"
    "vance/deferred_screenspace_effects.h"
    "vance/deferred_screenspace_effects_order.cpp"
    "vance/hud_weaponselection.cpp"
    "vance/viewmodel_attachment.cpp"
    "vance/viewmodel_attachment.h"
)
source_group("Source Files\\VANCE" FILES ${Source_Files__VANCE})

set(Source_Files__game_controls
    "game_controls/basemodel_panel.cpp"
    "game_controls/basemodel_panel.h"
    "game_controls/basemodelpanel.cpp"
    "game_controls/basemodelpanel.h"
    "game_controls/baseviewport.cpp"
    "game_controls/ClientScoreBoardDialog.cpp"
    "game_controls/commandmenu.cpp"
    "game_controls/IconPanel.cpp"
    "game_controls/intromenu.cpp"
    "game_controls/MapOverview.cpp"
    "game_controls/NavProgress.cpp"
    "game_controls/SpectatorGUI.cpp"
    "game_controls/teammenu.cpp"
    "game_controls/vguitextwindow.cpp"
)
source_group("Source Files\\game_controls" FILES ${Source_Files__game_controls})

set(Tool_Framework
    "../../public/tools/bonelist.cpp"
    "../../public/tools/bonelist.h"
    "entity_client_tools.cpp"
    "toolframework_client.cpp"
    "toolframework_client.h"
)
source_group("Tool Framework" FILES ${Tool_Framework})

set(game_controls_Header_Files
    "game_controls/baseviewport.h"
    "game_controls/clientscoreboarddialog.h"
    "game_controls/commandmenu.h"
    "game_controls/IconPanel.h"
    "game_controls/imagemouseoverbutton.h"
    "game_controls/intromenu.h"
    "game_controls/mapoverview.h"
    "game_controls/mouseoverhtmlbutton.h"
    "game_controls/mouseoverpanelbutton.h"
    "game_controls/spectatorgui.h"
    "game_controls/teammenu.h"
    "game_controls/vguitextwindow.h"
)
source_group("game_controls Header Files" FILES ${game_controls_Header_Files})

set(tymeta_Files
        "tymeta/c_baselesson.cpp"
        "tymeta/c_baselesson.h"
        "tymeta/c_gameinstructor.cpp"
        "tymeta/c_gameinstructor.h"
        "tymeta/hud_locator_target.cpp"
        "tymeta/hud_locator_target.h"
        )
source_group("Tymeta Files" FILES ${tymeta_Files})

set(SEE_Files
        "shadereditor/isedit_modelrender.h"
        "shadereditor/ivshadereditor.h"
        "shadereditor/sedit_modelrender.cpp"
        "shadereditor/sedit_modelrender.h"
        "shadereditor/shadereditorsystem.cpp"
        "shadereditor/shadereditorsystem.h"
        "shadereditor/grass/cgrasscluster.cpp"
        "shadereditor/grass/cgrasscluster.h"
        )
source_group("Shader Editor Files" FILES ${SEE_Files})




set(Source_Files__deferred
        "../../materialsystem/swarmshaders/deferred_global_common.h"
        "deferred/cascade_t.cpp"
        "deferred/cascade_t.h"
        "deferred/cdeferred_manager_client.cpp"
        "deferred/cdeferred_manager_client.h"
        "deferred/clight_editor.cpp"
        "deferred/clight_editor.h"
        "deferred/clight_manager.cpp"
        "deferred/clight_manager.h"
        "deferred/def_light_t.cpp"
        "deferred/def_light_t.h"
        "deferred/DefCookieProjectable.cpp"
        "deferred/DefCookieProjectable.h"
        "deferred/DefCookieTexture.cpp"
        "deferred/DefCookieTexture.h"
        "deferred/deferred_client_common.cpp"
        "deferred/deferred_client_common.h"
        "deferred/deferred_rt.cpp"
        "deferred/deferred_rt.h"
        "deferred/flashlighteffect_deferred.cpp"
        "deferred/flashlighteffect_deferred.h"
        "deferred/materialsystem_passthru.cpp"
        "deferred/materialsystem_passthru.h"
        "deferred/viewrender_deferred.cpp"
        "deferred/viewrender_deferred.h"
        )
source_group("Source Files\\deferred" FILES ${Source_Files__deferred})

set(Source_Files__deferred__interface
        "../../materialsystem/swarmshaders/IDeferredExt.h"
        "deferred/IDefCookie.h"
        "deferred/IDeferredExtClient.cpp"
        )
source_group("Source Files\\deferred\\interface" FILES ${Source_Files__deferred__interface})

set(Source_Files__deferred__shared
        "../shared/deferred/CDefLight.cpp"
        "../shared/deferred/CDefLight.h"
        "../shared/deferred/CDefLightContainer.cpp"
        "../shared/deferred/CDefLightContainer.h"
        "../shared/deferred/CDefLightGlobal.cpp"
        "../shared/deferred/CDefLightGlobal.h"
        "../shared/deferred/deferred_shared_common.cpp"
        "../shared/deferred/deferred_shared_common.h"
        )
source_group("Source Files\\deferred\\shared" FILES ${Source_Files__deferred__shared})

set(Source_Files__deferred__vgui
        "deferred/vgui/projectable_factory.cpp"
        "deferred/vgui/projectable_factory.h"
        "deferred/vgui/vgui_deferred.h"
        "deferred/vgui/vgui_editor_controls.cpp"
        "deferred/vgui/vgui_editor_controls.h"
        "deferred/vgui/vgui_editor_props.cpp"
        "deferred/vgui/vgui_editor_props.h"
        "deferred/vgui/vgui_editor_root.cpp"
        "deferred/vgui/vgui_marquee.cpp"
        "deferred/vgui/vgui_marquee.h"
        "deferred/vgui/vgui_particles.cpp"
        "deferred/vgui/vgui_particles.h"
        "deferred/vgui/vgui_projectable.cpp"
        "deferred/vgui/vgui_projectable.h"
        )
source_group("Source Files\\deferred\\vgui" FILES ${Source_Files__deferred__vgui})














set(ALL_FILES
    ${Game_Shared_Header_Files}
    ${Header_Files}
    ${MP3}
    ${Public_Header_Files}
    ${Replay}
    ${Source_Files}
    ${Source_Files__HL2_DLL}
    ${Source_Files__Precompiled_Header}
    ${Source_Files__Sixense}
    ${Source_Files__Temporary_Entities}
    ${Source_Files__VANCE}
    ${Source_Files__game_controls}
    ${Tool_Framework}
    ${game_controls_Header_Files}
    ${tymeta_Files}
    ${SEE_Files}
    ${Source_Files__deferred}
    ${Source_Files__deferred__interface}
    ${Source_Files__deferred__shared}
    ${Source_Files__deferred__vgui}
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
    TARGET_NAME_DEBUG   "client"
    TARGET_NAME_RELEASE "client"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/vance/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/vance/bin"
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
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier0;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../public/tier1;"
    "${CMAKE_CURRENT_SOURCE_DIR}/generated_proto_vance;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/protobuf-2.3.0/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../vgui2/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../vgui2/controls;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../shared;"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_controls;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/sixensesdk/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../shared/hl2;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../shared/episodic;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../shared/vance;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../gameui2;"
    "${CMAKE_CURRENT_SOURCE_DIR}/hl2;"
    "${CMAKE_CURRENT_SOURCE_DIR}/episodic;"
    "${CMAKE_CURRENT_SOURCE_DIR}/shadereditor;"
    "${CMAKE_CURRENT_SOURCE_DIR}/deferred;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vance"
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
    "WIN32;"
    "_WIN32;"
    "_WINDOWS;"
    "_USRDLL;"
    "_CRT_SECURE_NO_DEPRECATE;"
    "_CRT_NONSTDC_NO_DEPRECATE;"
    "_ALLOW_RUNTIME_LIBRARY_MISMATCH;"
    "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH;"
    "_ALLOW_MSC_VER_MISMATCH;"
    "COMPILER_MSVC32;"
    "COMPILER_MSVC;"
    "_DLL_EXT=.dll;"
    "DLLNAME=client;"
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
    "fopen=dont_use_fopen;"
    "HL2_CLIENT_DLL;"
    "HL2_EPISODIC;"
    "VANCE;"
    "_EXTERNAL_DLL_EXT=.dll;"
    "VPCGAMECAPS=VANCE;"
    "PROJECTDIR=E:\\Projects\\TymetaWorks\\AboutSource\\vance\\src\\game\\client;"
    "SOURCE1=1;"
    "VPCGAME=vance;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
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
            /Zo
        >
        /MP;
        /GF;
        /arch:SSE;

        /TP;
        /fp:fast;
        /GR;
        /wd4316;
        /Zm200;
        /Gw;
        /Zc:inline;
        /GS;
        /Zc:forScope
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/bone_setup.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/client_class.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/collisionutils.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../common/compiledcaptionswap.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/crtmemdebug.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/dt_recv.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/dt_utlvector_common.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/dt_utlvector_recv.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/filesystem_helpers.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(hud_lcd.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(in_mouse.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/interpolatortypes.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../shared/interval.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/jigglebones.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../common/language.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/tier0/memoverride.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(mumble.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/networkvar.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/posedebugger.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../common/randoverride.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/renamed_recvtable_compat.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(rendertexture.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/rope_physics.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/scratchpad3d.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/ScratchPadUtils.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/sentence.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../shared/sheetsimulator.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/simple_physics.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/stringregistry.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/studio.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/vallocator.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(../../public/vgui_controls/vgui_controls.cpp ${FILE_CL_OPTIONS})
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
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        Dmxloader
        bitmap
        choreoobjects
        gcsdk
        mathlib
        matsys_controls
        particles
        replay_common
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
        Dmxloader
        bitmap
        choreoobjects
        gcsdk
        mathlib
        matsys_controls
        particles
        replay_common
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

        steamemu

        cryptlib


        libprotobuf

        "shell32;"
        "user32;"
        "advapi32;"
        "gdi32;"
        "comdlg32;"
        "ole32;"
        "winmm;"
        "wsock32;"
        "Ws2_32"
        )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/common;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/public"
        )
