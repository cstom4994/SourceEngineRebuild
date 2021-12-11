#define _CRT_SECURE_NO_WARNINGS

#include "FakeSteamAPI_LogSys.h"

#include <Windows.h>
#include <CommCtrl.h>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <io.h>

#pragma comment(lib, "comctl32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")

using namespace std;

char g_static_str_storage[8192];
char g_strLogFilePath[8192] = "FakeSteamAPI.log";
bool g_bUseLogWindow = false;
HWND g_hwLogger;

#define FakeSteamAPI_LogWindowClassName "FakeSteamAPI_LogWindowClass"

#define EDIT_CONTROL_ID 100001
#define EDIT_SUBCLASS_ID 100001
#define SYSMENU_ALWAYS_ON_TOP_ID (1001 << 16)
#define SYSMENU_PROCESS_MESSAGE_IN_RUNCALLBACKS (1002 << 16)
#define SYSMENU_USE_ABSOLUTE_ADDRESS (1003 << 16)

void FakeSteamAPI_Internal_GenerateCurrentTimeString(char *buf) {
    struct timespec timespec;
    struct tm tm;
    time_t t;

#ifdef _WIN32
    time(&t);
    tm = *localtime(&t);
    timespec_get(&timespec, TIME_UTC);

    strftime(buf, 64, "%T", &tm);
    sprintf(buf + strlen(buf), ".%03d", (int) (timespec.tv_nsec / 1e6));
#else
    time(&t);
    tm = *localtime(&t);

    strftime(buf, 64, "%T", &tm);
#endif //defined _WIN32
}

void FakeSteamAPI_SpecifyLog(const char *path) {
    strcpy(g_strLogFilePath, path);
}

LRESULT CALLBACK Edit_SubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR nIdSubClass,
                                   DWORD_PTR dwRefData) {
    switch (msg) {
        case WM_NCMOUSEMOVE:
        case WM_MOUSEMOVE:
            while (ShowCursor(TRUE) < 0);
            break;
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

//Sets the caret to the end of the text and append the text
void Edit_AppendTextA(HWND hwEdit, char *str) {
    int nTextLen;
    //nTextLen = GetWindowTextLengthA(hwEdit);
    nTextLen = 1024 * 1024;
    SendMessageA(hwEdit, EM_SETSEL, nTextLen, nTextLen);
    SendMessageA(hwEdit, EM_REPLACESEL, FALSE, (LPARAM) str);
}

bool FakeSteamAPI_AppendLog(int level, const char *str, ...) {
    const char *const strPrefixTable[] = {NULL, "Info", "Warn", "Error", "Debug"};
    char buf[64];
    va_list vl;
    FILE *fp;

            va_start(vl, str);
    vsprintf(g_static_str_storage, str, vl);
            va_end(vl);

    fp = fopen(g_strLogFilePath, "a");
    if (fp == NULL)
        return false;

    FakeSteamAPI_Internal_GenerateCurrentTimeString(buf);
    fprintf(fp, "[%s][%s] %s\n", buf, strPrefixTable[level], g_static_str_storage);

    fclose(fp);

    if (g_bUseLogWindow) {
        char strBuf[8192];
        HWND hwEdit;

        sprintf(strBuf, "[%s][%s] %s\r\n", buf, strPrefixTable[level], g_static_str_storage);
        hwEdit = GetDlgItem(g_hwLogger, EDIT_CONTROL_ID);
        Edit_AppendTextA(hwEdit, strBuf);
    }

    return true;
}

bool FakeSteamAPI_NewLogLine(void) {
    bool bNewFile;
    FILE *fp;

    bNewFile = (bool) _access(g_strLogFilePath, 00);

    fp = fopen(g_strLogFilePath, "a");
    if (fp == NULL)
        return false;

    if (!bNewFile)
        putc('\n', fp);

    fclose(fp);

    return true;
}

bool FakeSteamAPI_EmptyLog(void) {
    FILE *fp;

    fp = fopen(g_strLogFilePath, "w");
    if (fp == NULL)
        return false;

    fclose(fp);

    return true;
}

bool FakeSteamAPI_Internal_RetrieveMenuCheck(HMENU hMenu, UINT nItemId) {
    MENUITEMINFO mii;
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STATE;
    GetMenuItemInfo(hMenu, nItemId, false, &mii);
    return (bool) (mii.fState & MFS_CHECKED);
}

bool FakeSteamAPI_Internal_InvertMenuCheck(HMENU hMenu, UINT nItemId) {
    MENUITEMINFO mii;
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STATE;
    GetMenuItemInfo(hMenu, nItemId, false, &mii);
    CheckMenuItem(hMenu, nItemId, (mii.fState & MFS_CHECKED) ? MF_UNCHECKED : MF_CHECKED);
    return (bool) (mii.fState & MFS_CHECKED);
}

HFONT FakeSteamAPI_Internal_EasyCreateFontA(HDC hdc, const char *strFont, int nPointSize) {
    int nLogPixelsX, nLogPixelsY;
    bool bMarkHdcDelete;
    LOGFONTA logFont;
    HFONT hFont;

    if (strFont == NULL)
        return false;

    bMarkHdcDelete = false;
    if (hdc == NULL) {
        bMarkHdcDelete = true;
        hdc = CreateDCA("DISPLAY", NULL, NULL, NULL);
        if (hdc == NULL)
            return NULL;
    }

    nLogPixelsX = GetDeviceCaps(hdc, LOGPIXELSX);
    nLogPixelsY = GetDeviceCaps(hdc, LOGPIXELSY);

    if (bMarkHdcDelete)
        DeleteDC(hdc);

    (void) nLogPixelsX;    //Mark as used

    logFont.lfWidth = 0;
    logFont.lfHeight = -MulDiv(nPointSize, nLogPixelsY, 72);
    logFont.lfEscapement = 0;
    logFont.lfOrientation = 0;
    logFont.lfWeight = FW_NORMAL;
    logFont.lfItalic = false;
    logFont.lfUnderline = false;
    logFont.lfStrikeOut = false;
    logFont.lfCharSet = DEFAULT_CHARSET;
    logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    logFont.lfQuality = DEFAULT_QUALITY;
    logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    strncpy(logFont.lfFaceName, strFont, LF_FACESIZE - 1);
    logFont.lfFaceName[LF_FACESIZE - 1] = L'\0';

    hFont = CreateFontIndirectA(&logFont);

    return hFont;
}

LRESULT CALLBACK FakeSteamAPI_Internal_LogWindowCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HMENU hMenuSys;
    RECT rtClient;
    HFONT hFont;
    HWND hwEdit;

    switch (msg) {
        case WM_CREATE:
            GetClientRect(hwnd, &rtClient);

            hwEdit = CreateWindowA(
                    "edit",
                    NULL,
                    WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
                    0, 0,
                    rtClient.right, rtClient.bottom,
                    hwnd,
                    (HMENU) EDIT_CONTROL_ID,
                    ((LPCREATESTRUCT) lParam)->hInstance,
                    NULL
            );
            SetWindowSubclass(hwEdit, Edit_SubclassProc, EDIT_SUBCLASS_ID, 0);

            hFont = FakeSteamAPI_Internal_EasyCreateFontA(NULL, "Consolas", 10);
            SendMessage(hwEdit, WM_SETFONT, (WPARAM) hFont, FALSE);

            hMenuSys = GetSystemMenu(hwnd, FALSE);
            AppendMenuA(hMenuSys, MF_SEPARATOR, 0, NULL);
            AppendMenuA(hMenuSys, MF_STRING, SYSMENU_ALWAYS_ON_TOP_ID, "Always on top");
            AppendMenuA(hMenuSys, MF_STRING, SYSMENU_PROCESS_MESSAGE_IN_RUNCALLBACKS,
                        "Process message in SteamAPI_RunCallbacks()");
            AppendMenuA(hMenuSys, MF_STRING | MF_CHECKED, SYSMENU_USE_ABSOLUTE_ADDRESS, "Display absolute address");

            FakeSteamAPI_SetSettingsItemInt32(FakeSteamAPI_SettingsIndex_ProcessMessageInRunCallbacks, 0);
            FakeSteamAPI_SetSettingsItemInt32(FakeSteamAPI_SettingsIndex_UseAbsoluteAddress, 1);
            break;
        case WM_CLOSE:
            hwEdit = GetDlgItem(hwnd, EDIT_CONTROL_ID);
            hFont = (HFONT) SendMessage(hwEdit, WM_GETFONT, 0, 0);
            DestroyWindow(hwEdit);
            DeleteObject(hFont);
            RemoveWindowSubclass(hwEdit, Edit_SubclassProc, EDIT_SUBCLASS_ID);
            FakeSteamAPI_FreeLogWindow();
            return 0;
        case WM_NCMOUSEMOVE:
        case WM_MOUSEMOVE:
            while (ShowCursor(TRUE) < 0);
            break;
        case WM_SIZE:
            hwEdit = GetDlgItem(hwnd, EDIT_CONTROL_ID);
            MoveWindow(hwEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
            break;
        case WM_SYSCOMMAND:
            switch (wParam) {
                case SYSMENU_ALWAYS_ON_TOP_ID:
                    hMenuSys = GetSystemMenu(hwnd, FALSE);
                    if (FakeSteamAPI_Internal_InvertMenuCheck(hMenuSys, SYSMENU_ALWAYS_ON_TOP_ID))
                        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    else
                        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    break;
                case SYSMENU_PROCESS_MESSAGE_IN_RUNCALLBACKS:
                    hMenuSys = GetSystemMenu(hwnd, FALSE);
                    FakeSteamAPI_SetSettingsItemInt32(
                            FakeSteamAPI_SettingsIndex_ProcessMessageInRunCallbacks,
                            !FakeSteamAPI_Internal_InvertMenuCheck(hMenuSys, SYSMENU_PROCESS_MESSAGE_IN_RUNCALLBACKS)
                    );
                    break;
                case SYSMENU_USE_ABSOLUTE_ADDRESS:
                    hMenuSys = GetSystemMenu(hwnd, FALSE);
                    FakeSteamAPI_SetSettingsItemInt32(
                            FakeSteamAPI_SettingsIndex_UseAbsoluteAddress,
                            !FakeSteamAPI_Internal_InvertMenuCheck(hMenuSys, SYSMENU_USE_ABSOLUTE_ADDRESS)
                    );
                    if (FakeSteamAPI_GetSettingsItemInt32(FakeSteamAPI_SettingsIndex_UseAbsoluteAddress) == 0)
                        FakeSteamAPI_AppendLog(LogLevel_Debug, "BASE = 0x%08X", (int) FakeSteamAPI_GetImageBase());
                    break;
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool FakeSteamAPI_AllocLogWindow(void) {
    WNDCLASSA wc;

    if (g_bUseLogWindow)
        return false;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra = wc.cbClsExtra = 0;
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = NULL;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = FakeSteamAPI_Internal_LogWindowCallback;
    wc.lpszClassName = FakeSteamAPI_LogWindowClassName;
    wc.lpszMenuName = NULL;
    if (RegisterClassA(&wc) == 0)
        return false;

    g_hwLogger = CreateWindowA(
            FakeSteamAPI_LogWindowClassName,
            (char *) L"FakeSteamAPI Log Window",
            WS_VISIBLE | WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL
    );
    if (g_hwLogger == NULL) {
        UnregisterClassA(FakeSteamAPI_LogWindowClassName, GetModuleHandle(NULL));
        return false;
    }

    g_bUseLogWindow = true;

    return true;
}

bool FakeSteamAPI_FreeLogWindow(void) {
    if (!g_bUseLogWindow)
        return false;

    DestroyWindow(g_hwLogger);
    UnregisterClassA(FakeSteamAPI_LogWindowClassName, GetModuleHandle(NULL));

    g_bUseLogWindow = false;

    return true;
}