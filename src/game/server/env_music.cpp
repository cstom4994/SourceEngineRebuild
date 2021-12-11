#include "cbase.h"
/*
class CEnvMusicChannel;

class CEnvMusicMaster : public CBaseEntity
{
	DECLARE_CLASS(CEnvMusicMaster, CBaseEntity);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
public:
	void Spawn();
	void Think();

	int GetBPM();

private:
	int m_iBPM;

	bool m_bStartEnabled;

	char* m_szMainLoopFile;
	char* m_szAlternateLoopFile;

	float m_flVolume; // must be range 1-9

	CEnvMusicChannel *m_pChannels;
};

LINK_ENTITY_TO_CLASS(env_music_master, CEnvMusicMaster);

BEGIN_DATADESC(CEnvMusicMaster)
DEFINE_KEYFIELD(m_szMainLoopFile, FIELD_STRING, "Master Loop"),
DEFINE_KEYFIELD(m_szAlternateLoopFile, FIELD_STRING, "Alternate Loop"),
DEFINE_KEYFIELD(m_flVolume, FIELD_FLOAT, "Volume"),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CEnvMusicMaster, DT_EnvMusicMaster)
SendPropBool()
END_SEND_TABLE()

void CEnvMusicMaster::Spawn()
{
	BaseClass::Spawn();

	if (m_bStartEnabled)
	{
		SetNextThink(gpGlobals->curtime);
	}
}

void CEnvMusicMaster::Think()
{
	BaseClass::Think();

	SetNextThink(gpGlobals->curtime + 0.15);
}

int CEnvMusicMaster::GetBPM()
{
	static bool bpmSet = false;
	if (!bpmSet)
	{
		m_iBPM = /* GET BPM FROM MAIN LOOP ;
	}

	return m_iBPM;
}

enum
{
	SF_QUANTIZE = (1 << 32),
	SF_LOOP = (1 << 33),
};

class CEnvMusicChannel : public CBaseEntity
{
	DECLARE_CLASS(CEnvMusicChannel, CBaseEntity);
	DECLARE_DATADESC();
public:
	void Spawn();
	void Think();

private:

	// Keyfields
	char *m_szLoopCue;
	float m_flVolume;
	int m_iPlayOnBeat;
	float m_flInterval;

	// Flags
	CNetworkVar(bool, m_bQuantize);
	CNetworkVar(bool, m_bLoop);
};

LINK_ENTITY_TO_CLASS(env_music_channel, CEnvMusicChannel);

BEGIN_DATADESC(CEnvMusicChannel)
DEFINE_KEYFIELD(m_szLoopCue, FIELD_STRING, "Alternate Loop"),
DEFINE_KEYFIELD(m_flVolume, FIELD_FLOAT, "Volume"),
DEFINE_KEYFIELD(m_iPlayOnBeat, FIELD_INTEGER, "Play on beat")
DEFINE_KEYFIELD(m_flInterval, FIELD_FLOAT, "Interval"),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CEnvMusicChannel, DT_EnvMusicChannel)
SendPropBool(SENDINFO(m_bLoop)),
SendPropBool(SENDINFO(m_bQuantize)),
END_SEND_TABLE()

void CEnvMusicChannel::Spawn()
{
	BaseClass::Spawn();

	if (GetSpawnFlags() & SF_QUANTIZE)
	{
		m_bQuantize = true;
	}

	if (GetSpawnFlags() & SF_LOOP)
	{
		m_bLoop = true;
	}
}

void CEnvMusicChannel::Think()
{
	BaseClass::Think();

	SetNextThink(gpGlobals->curtime + 0.15);
}*/