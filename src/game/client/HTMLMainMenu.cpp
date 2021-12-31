#include "cbase.h"
#include "HTMLMainMenu.h"
#include "vgui_controls/Frame.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>

#include "FileSystem.h"

#include "vgui_controls/Button.h"
#include "vgui_controls/ImagePanel.h"

#include "awesomium/VAwesomium.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>

#include <Awesomium/WebString.h>
#include <Awesomium/STLHelpers.h>

#include <Awesomium/JSObject.h>
#include <Awesomium/JSValue.h>
#include <Awesomium/JSArray.h>

using namespace vgui;
using namespace Awesomium;

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef PostMessage
#undef PostMessage
#endif

static char *webstring_to_buf(const WebString &wstr, size_t *flen) {
    char *buf;
    unsigned int len = 0;
    len = wstr.ToUTF8(NULL, 0);
    buf = (char *) malloc(len + 1);
    wstr.ToUTF8(buf, len);
    buf[len] = '\0';
    if (flen) *flen = (size_t) len;
    return buf;
}

// HTML5���˵�������
class OIMainMenu : public VAwesomium {
    DECLARE_CLASS_SIMPLE(OIMainMenu, VAwesomium);
public:
    OIMainMenu(vgui::Panel *parent, const char *panelName) : VAwesomium(parent, panelName) {};

    virtual void OnDocumentReady(Awesomium::WebView *caller, const Awesomium::WebURL &url);

    virtual void
    OnMethodCall(Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name,
                 const Awesomium::JSArray &args);
};

void OIMainMenu::OnDocumentReady(WebView *caller, const WebURL &url) {
    JSValue result = caller->CreateGlobalJavascriptObject(WSLit("Game"));
    JSObject &gameObj = result.ToObject();
    gameObj.SetCustomMethod(WSLit("Quit"), false);
    gameObj.SetCustomMethod(WSLit("ClientCommand"), false);
    gameObj.SetCustomMethod(WSLit("HideUI"), false);
    gameObj.SetCustomMethod(WSLit("ShowUI"), false);
    gameObj.SetCustomMethod(WSLit("UpdateMapList"), false);
    //caller->ExecuteJavascript(WSLit("AwesomiumInitialized()"), WSLit(""));

    WebString mapList = WSLit("");

    FileFindHandle_t findHandle = NULL;

    const char *pszFilename = g_pFullFileSystem->FindFirst("maps/*.bsp", &findHandle);
    unsigned int i = 0;
    while (pszFilename) {
        char mapname[256];

        // FindFirst ignores the pszPathID, so check it here
        // TODO: this doesn't find maps in fallback dirs
        Q_snprintf(mapname, sizeof(mapname), "maps/%s", pszFilename);
        if (!g_pFullFileSystem->FileExists(mapname, "MOD")) {
            goto nextFile;
        }

        const char *str = Q_strstr(pszFilename, "maps");
        if (str) {
            Q_strncpy(mapname, str + 5, sizeof(mapname) - 1);    // maps + \\ = 5
        } else {
            Q_strncpy(mapname, pszFilename, sizeof(mapname) - 1);
        }
        char *ext = Q_strstr(mapname, ".bsp");
        if (ext) {
            *ext = 0;
        }

        // add to the map list
        mapList.Append(WSLit(mapname));
        mapList.Append(WSLit(","));
        i++;

        // get the next file
        nextFile:
        pszFilename = g_pFullFileSystem->FindNext(findHandle);
    }
    g_pFullFileSystem->FindClose(findHandle);

    gameObj.SetProperty(WSLit("MapList"), mapList);
}

void OIMainMenu::OnMethodCall(Awesomium::WebView *caller, unsigned int remote_object_id,
                              const Awesomium::WebString &method_name, const Awesomium::JSArray &args) {
    if (method_name == WSLit("Quit")) {
        engine->ClientCmd_Unrestricted("quit\n");
    } else if (method_name == WSLit("ClientCommand")) {
        engine->ClientCmd_Unrestricted(webstring_to_buf(args[0].ToString(), NULL));
    } else if (method_name == WSLit("HideUI")) {
        GetParent()->SetVisible(false);
    } else if (method_name == WSLit("ShowUI")) {
        GetParent()->SetVisible(true);
    } else if (method_name == WSLit("UpdateMapList")) {

    }
}

OIMainMenu *g_MainmenuUI;

class CMainMenu : public vgui::Panel {
    DECLARE_CLASS_SIMPLE(CMainMenu, vgui::Panel);

public:
    CMainMenu(vgui::VPANEL parent);

    ~CMainMenu();

    void CMainMenu::PerformDefaultLayout() {
        m_awesomium->SetPos(0, 0);
    }

    OIMainMenu *m_awesomium;
};

void ReloadUI(void) {
    g_MainmenuUI->OpenFile("lobby.html");
    g_MainmenuUI->GetParent()->SetVisible(true);
}

static ConCommand reloadpage("ui_reload", ReloadUI);

CMainMenu::CMainMenu(vgui::VPANEL parent) : BaseClass(NULL, "CMainMenu") {
    SetParent(parent);
    //SetTitleBarVisible( false );
    //SetMinimizeButtonVisible( false );
    //SetMaximizeButtonVisible( false );
    //SetCloseButtonVisible( false );
    //SetSizeable( false );
    //SetMoveable( false );
    SetProportional(true);
    SetVisible(true);

    SetSize(ScreenWidth(), ScreenHeight());
    SetZPos(-1); // we're behind everything


    m_awesomium = vgui::SETUP_PANEL(new OIMainMenu(this, "HTMLMainMenu"));
    m_awesomium->SetSize(ScreenWidth(), ScreenHeight());
    m_awesomium->OpenFile("mainmenu.html");

    g_MainmenuUI = m_awesomium;

    PerformDefaultLayout();
    SetBgColor(Color(0, 0, 0, 0));
}

CMainMenu::~CMainMenu() {
}

class LHTMLMainMenu : public IHTMLMainMenu {
private:
    CMainMenu *MainMenu;
    vgui::VPANEL m_hParent;

public:
    LHTMLMainMenu(void) {
        MainMenu = NULL;
    }

    void Create(vgui::VPANEL parent) {
        // Create immediately
        MainMenu = new CMainMenu(parent);
    }

    void Destroy(void) {
        if (MainMenu) {
            MainMenu->SetParent((vgui::Panel *) NULL);
            delete MainMenu;
        }
    }

};

static LHTMLMainMenu g_HtmlMenu;
IHTMLMainMenu *HTMLMainMenu = (IHTMLMainMenu *) &g_HtmlMenu;