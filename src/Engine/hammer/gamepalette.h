//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//=============================================================================//

#ifndef _GAMEPALETTE_H
#define _GAMEPALETTE_H

//#include "d3drmdef.h"
typedef enum _D3DRMPALETTEFLAGS {
    D3DRMPALETTE_FREE,
    D3DRMPALETTE_READONLY,
    D3DRMPALETTE_RESERVED
} D3DRMPALETTEFLAGS, *LPD3DRMPALETTEFLAGS;
typedef struct _D3DRMPALETTEENTRY {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char flags;
} D3DRMPALETTEENTRY, *LPD3DRMPALETTEENTRY;

class CGamePalette {
public:
    CGamePalette();

    ~CGamePalette();

    BOOL Create(LPCTSTR pszFile);

    void SetBrightness(float fValue);

    float GetBrightness();

    operator LOGPALETTE *() { return pPalette; }

    operator D3DRMPALETTEENTRY *() { return (D3DRMPALETTEENTRY *) pPalette->palPalEntry; }

    operator CPalette *() { return &GDIPalette; }

private:
    float fBrightness;

    // CPalette:
    CPalette GDIPalette;

    // palette working with:
    LOGPALETTE *pPalette;
    // to convert & store in pPalette:
    LOGPALETTE *pOriginalPalette;

    // file stored in:
    CString strFile;

    // sizeof each palette:
    size_t uPaletteBytes;
};

#endif