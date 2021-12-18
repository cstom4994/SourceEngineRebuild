﻿//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Holds the CTFPlayerInfo object
//
// $NoKeywords: $
//=============================================================================//

#ifndef TFPLAYERINFO_H
#define TFPLAYERINFO_H
#ifdef _WIN32
#pragma once
#endif

#include "gcsdk/protobufsharedobject.h"
#include "tf_gcmessages.pb.h"

//---------------------------------------------------------------------------------
// Purpose: All the account-level information that the GC tracks for TF
//---------------------------------------------------------------------------------
class CTFPlayerInfo : public GCSDK::CProtoBufSharedObject< CSOTFPlayerInfo, k_EEconTypePlayerInfo >
{
#ifdef GC
	DECLARE_CLASS_MEMPOOL( CTFPlayerInfo );
public:
	virtual bool BIsDatabaseBacked() const { return false; }
#endif
};

#endif // TFPLAYERINFO_H
