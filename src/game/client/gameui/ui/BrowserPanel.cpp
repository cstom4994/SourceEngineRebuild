//
// Created by KaoruXun
//

#include "cbase.h"
#include "IBrowserPanel.h"

using namespace vgui;

#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/Button.h>

#include "cef/src_cef.h"

//CBrowserPanel class: Tutorial example class
class CBrowserPanel : public vgui::Frame {
    DECLARE_CLASS_SIMPLE(CBrowserPanel, vgui::Frame);
    //CBrowserPanel : This Class / vgui::Frame : BaseClass

    CBrowserPanel(vgui::VPANEL parent);    // Constructor
    ~CBrowserPanel() {};                // Destructor

protected:
    //VGUI overrides:
    virtual void OnTick();

    virtual void OnCommand(const char *pcCommand);

private:
    //Other used VGUI control Elements:
    Button *m_pCloseButton;
    SrcCefBrowser *m_pCefMainMenu;
};

// Constuctor: Initializes the Panel
CBrowserPanel::CBrowserPanel(vgui::VPANEL parent)
        : BaseClass(NULL, "BrowserPanel") {
    SetParent(parent);

    SetKeyBoardInputEnabled(true);
    SetMouseInputEnabled(true);

    SetProportional(false);
    SetTitleBarVisible(true);
    SetMinimizeButtonVisible(false);
    SetMaximizeButtonVisible(false);
    SetCloseButtonVisible(false);
    SetSizeable(false);
    SetMoveable(false);
    SetVisible(true);


    SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

    LoadControlSettings("resource/UI/playermodelsel.res");

    vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

    DevMsg("BrowserPanel has been constructed\n");

    //Button done
    m_pCloseButton = new Button(this, "Button", "Close", this, "turnoff");
    m_pCloseButton->SetPos(433, 472);
    m_pCloseButton->SetDepressedSound("common/bugreporter_succeeded.wav");
    m_pCloseButton->SetReleasedSound("ui/buttonclick.wav");
}


class CBrowserPanelInterface : public IBrowserPanel {
private:
    CBrowserPanel *BrowserPanel;
public:
    CBrowserPanelInterface() {
        BrowserPanel = NULL;
    }

    void Create(vgui::VPANEL parent) {
        BrowserPanel = new CBrowserPanel(parent);
    }

    void Destroy() {
        if (BrowserPanel) {
            BrowserPanel->SetParent((vgui::Panel *) NULL);
            delete BrowserPanel;
        }
    }

    void Activate(void) {
        if (BrowserPanel) {
            BrowserPanel->Activate();
        }
    }
};

static CBrowserPanelInterface g_BrowserPanel;
IBrowserPanel *BrowserPanel = (IBrowserPanel *) &g_BrowserPanel;


ConVar cl_showBrowserPanel("cl_showBrowserPanel", "0", FCVAR_CLIENTDLL, "Sets the state of BrowserPanel <state>");

void CBrowserPanel::OnTick() {
    BaseClass::OnTick();
    SetVisible(cl_showBrowserPanel.GetBool());
}

CON_COMMAND(OpenTestPanelFenix, "Toggles testpanelfenix on or off") {
    cl_showBrowserPanel.SetValue(!cl_showBrowserPanel.GetBool());
    BrowserPanel->Activate();
};

void CBrowserPanel::OnCommand(const char *pcCommand) {
    BaseClass::OnCommand(pcCommand);

    if (!Q_stricmp(pcCommand, "turnoff"))
        cl_showBrowserPanel.SetValue(0);
}