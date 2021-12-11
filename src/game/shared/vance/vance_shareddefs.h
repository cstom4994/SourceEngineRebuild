#ifndef VANCE_SHAREDDEFS_H
#define VANCE_SHAREDDEFS_H

#ifdef _WIN32
#pragma once
#endif

#include "shareddefs.h"

#define DMG_KICK            (DMG_LASTGENERICFLAG<<1)        // filter kick damage so we can kick doors open
#define DMG_BLEED			(DMG_KICK<<1)

#endif // VANCE_SHAREDDEFS_H