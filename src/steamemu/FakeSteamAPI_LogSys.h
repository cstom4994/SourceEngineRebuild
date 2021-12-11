#pragma once

#include "FakeSteamAPI_Utilities.h"
#include "FakeSteamAPI_Settings.h"


#define FakeSteamAPI_LogFuncBeingCalled()
//FakeSteamAPI_AppendLog(LogLevel_Debug, "0x%08X -> 0x%08X -> %s()", (int)FakeSteamAPI_GetEIP1(), (int)FakeSteamAPI_GetEIP0(), __FUNCTION__)

//
//#define FakeSteamAPI_LogFuncBeingCalled()														\
//	( FakeSteamAPI_GetSettingsItemInt32(FakeSteamAPI_SettingsIndex_UseAbsoluteAddress) != 0 ? (	\
//		FakeSteamAPI_AppendLog(																	\
//			LogLevel_Debug,																		\
//			"0x%08X -> 0x%08X -> %s()",															\
//			(int)FakeSteamAPI_GetEIP1(),														\
//			(int)FakeSteamAPI_GetEIP0(),														\
//			__FUNCTION__																		\
//		)																						\
//	)																							\
//	: (																							\
//		FakeSteamAPI_AppendLog(																	\
//			LogLevel_Debug,																		\
//			"BASE+0x%08X -> BASE+0x%08X -> %s()",												\
//			(int)FakeSteamAPI_GetEIP1() - (int)FakeSteamAPI_GetImageBase(),						\
//			(int)FakeSteamAPI_GetEIP0() - (int)FakeSteamAPI_GetImageBase(),						\
//			__FUNCTION__																		\
//		)																						\
//	) )

#define LogLevel_Info 1
#define LogLevel_Warn 2
#define LogLevel_Err 3
#define LogLevel_Debug 4

void FakeSteamAPI_SpecifyLog(const char *path);

bool FakeSteamAPI_AppendLog(int level, const char *str, ...);

bool FakeSteamAPI_NewLogLine(void);

bool FakeSteamAPI_EmptyLog(void);

bool FakeSteamAPI_AllocLogWindow(void);

bool FakeSteamAPI_FreeLogWindow(void);