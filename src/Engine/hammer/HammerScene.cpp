﻿//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose:
//
//=============================================================================

#include "stdafx.h"
#include "scriplib.h"
#include "choreoscene.h"
#include "iscenetokenprocessor.h"
#include "filesystem_tools.h"


//-----------------------------------------------------------------------------
// Purpose: Helper to scene module for parsing the .vcd file
//-----------------------------------------------------------------------------
class CSceneTokenProcessor : public ISceneTokenProcessor {
public:
    const char *CurrentToken(void);

    bool GetToken(bool crossline);

    bool TokenAvailable(void);

    void Error(const char *fmt, ...);
};

//-----------------------------------------------------------------------------
// Purpose:
// Output : const
//-----------------------------------------------------------------------------
const char *CSceneTokenProcessor::CurrentToken(void) {
    return token;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : crossline -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CSceneTokenProcessor::GetToken(bool crossline) {
    return ::GetToken(crossline) ? true : false;
}

//-----------------------------------------------------------------------------
// Purpose:
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CSceneTokenProcessor::TokenAvailable(void) {
    return ::TokenAvailable() ? true : false;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *fmt -
//			... -
//-----------------------------------------------------------------------------
void CSceneTokenProcessor::Error(const char *fmt, ...) {
    char string[2048];
    va_list argptr;
            va_start(argptr, fmt);
    vsprintf(string, fmt, argptr);
            va_end(argptr);

    Warning("%s", string);
}

static CSceneTokenProcessor g_TokenProcessor;


//-----------------------------------------------------------------------------
// Purpose: Normally implemented in cmdlib.cpp but we don't want that in Hammer.
//-----------------------------------------------------------------------------
char *ExpandPath(char *path) {
    static char fullpath[512], fullpathCorrect[512];
    g_pFullFileSystem->RelativePathToFullPath(path, "GAME", fullpath, sizeof(fullpath));
    g_pFullFileSystem->GetCaseCorrectFullPath(fullpath, fullpathCorrect);
    return fullpathCorrect;
}

bool CmdLib_HasBasePath(const char *pFileName_, int &pathLength, const CSplitString &splitString) {
    char *pFileName = (char *) _alloca(strlen(pFileName_) + 1);
    strcpy(pFileName, pFileName_);
    Q_FixSlashes(pFileName);
    pathLength = 0;
    for (int i = 0; i < splitString.Count(); ++i) {
        // see if we can rip the base off of the filename.
        if (Q_strncasecmp(splitString[i], pFileName, strlen(splitString[i])) == 0) {
            pathLength = strlen(splitString[i]);
            return true;
        }
    }
    return false;
}

int CmdLib_ExpandWithBasePaths(CUtlVector<CUtlString> &expandedPathList, const char *pszPath) {
    int nPathLength = 0;

    pszPath = ExpandPath(
            const_cast< char * >( pszPath ));    // Kind of redundant but it's how CmdLib_HasBasePath needs things

    char searchPath[1024];
    g_pFullFileSystem->GetSearchPath_safe("GAME", false, searchPath);
    CSplitString splitString(searchPath, ";");

    if (CmdLib_HasBasePath(pszPath, nPathLength, splitString)) {
        pszPath = pszPath + nPathLength;
        for (int i = 0; i < splitString.Count(); ++i) {
            CUtlString &expandedPath = expandedPathList[expandedPathList.AddToTail(splitString[i])];
            expandedPath += pszPath;
        }
    } else {
        expandedPathList.AddToTail(pszPath);
    }

    return expandedPathList.Count();
}

//-----------------------------------------------------------------------------
// Purpose: Normally implemented in cmdlib.cpp but we don't want that in Hammer.
//-----------------------------------------------------------------------------
int LoadFile(const char *filename, void **bufferptr) {
    FileHandle_t f = g_pFullFileSystem->Open(filename, "rb");
    if (FILESYSTEM_INVALID_HANDLE != f) {
        int length = g_pFullFileSystem->Size(f);
        void *buffer = malloc(length + 1);
        ((char *) buffer)[length] = 0;
        g_pFullFileSystem->Read(buffer, length, f);
        g_pFullFileSystem->Close(f);
        *bufferptr = buffer;
        return length;
    } else {
        *bufferptr = NULL;
        return 0;
    }
}


CChoreoScene *HammerLoadScene(const char *pFilename) {
    if (g_pFullFileSystem->FileExists(pFilename)) {
        LoadScriptFile((char *) pFilename);
        CChoreoScene *scene = ChoreoLoadScene(pFilename, NULL, &g_TokenProcessor, Msg);
        return scene;
    }

    return NULL;
}


bool GetFirstSoundInScene(const char *pSceneFilename, char *pSoundName, int soundNameLen) {
    CChoreoScene *pScene = HammerLoadScene(pSceneFilename);
    if (!pScene)
        return false;

    for (int i = 0; i < pScene->GetNumEvents(); i++) {
        CChoreoEvent *e = pScene->GetEvent(i);
        if (!e || e->GetType() != CChoreoEvent::SPEAK)
            continue;

        const char *pParameters = e->GetParameters();
        V_strncpy(pSoundName, pParameters, soundNameLen);
        delete pScene;
        return true;
    }

    delete pScene;
    return false;
}