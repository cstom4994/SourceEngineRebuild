#include "awesomium/MainMenu.h"

#include <vgui/VGUI.h>
#include <vgui_controls/Panel.h>

using namespace Awesomium;


void MainMenu::OnDocumentReady(WebView* caller, const WebURL& url)
{

}

void MainMenu::OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, const Awesomium::WebString& method_name, const Awesomium::JSArray& args)
{
	if (method_name == WSLit("StartNewGame"))
	{
		
	}
}