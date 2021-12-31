#include "awesomium/VAwesomium.h"

#include <vgui/VGUI.h>
#include <vgui_controls/Panel.h>

class MainMenu : public VAwesomium
{
	DECLARE_CLASS_SIMPLE(MainMenu, VAwesomium);
public:
	MainMenu(vgui::Panel *parent, const char *panelName) : VAwesomium(parent, panelName){ this->OpenFile("mainmenu.html"); };

	virtual void OnDocumentReady(Awesomium::WebView* caller, const Awesomium::WebURL& url);

	virtual void OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args);
};
