//========= Copyright � 2010, Gear Development, All rights reserved. ============//
//
// Purpose: I imagine a few of you are going to wonder dearly what this is is why we're doing this.
// Well, sit down. I'm going to tell you a story:
// When Valve created the screeneffects system, they did with 1 effect running at any given time, max;
// More if render order wasn't important or you wanted to stick to a single screeneffects file.
// In City17, we need a whopping 6 screeneffects on at all times, not including any of the stock screeneffects.
// This presented us with a problem, because there weren't any ways to scientifically control the render order of the effects.
// This is our "fix". If you want to add a new effect, include it's headers here, and then define it here within this render order stack.
//
// Note: Bottom renders first.
//
//===============================================================================//
#include "cbase.h"
#include "ScreenSpaceEffects.h"
#include "deferred_screenspace_effects.h"
#include "episodic\episodic_screenspaceeffects.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// FXAA
ADD_SCREENSPACE_EFFECT(CFXAA, vance_fxaa);

// Unsharp
ADD_SCREENSPACE_EFFECT(CUnsharpEffect, vance_unsharp);

// Episodic
ADD_SCREENSPACE_EFFECT(CStunEffect, episodic_stun);
ADD_SCREENSPACE_EFFECT(CEP2StunEffect, ep2_groggy);

// Underwater effects
ADD_SCREENSPACE_EFFECT(CWaterEffects, vance_waterfx);

// Episodic
ADD_SCREENSPACE_EFFECT(CEP1IntroEffect, episodic_intro);

// Tonemap
ADD_SCREENSPACE_EFFECT(CTonemap, vance_tonemap);

// Gaussian Bloom
ADD_SCREENSPACE_EFFECT(CBloom, vance_bloom);

// Volumetric lighting combine
ADD_SCREENSPACE_EFFECT(CVolumetrics, vance_volumetrics);

// SSR
ADD_SCREENSPACE_EFFECT(CSSR, vance_ssr);

// SSAO
ADD_SCREENSPACE_EFFECT(CSSAO, vance_ssao);
