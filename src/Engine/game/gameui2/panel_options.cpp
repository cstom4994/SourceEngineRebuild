/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "panel_options.h"

#include "ienginevgui.h"
#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

Panel_Options::Panel_Options(vgui::VPANEL Parent, const char* PanelName) : BaseClass(nullptr, PanelName)
{
	vgui::HScheme Scheme = vgui::scheme()->LoadSchemeFromFile("resource2/schemepanel.res", "SchemePanel");
	SetScheme(Scheme);

	AnimationController = new vgui::AnimationController(this);
	AnimationController->SetScheme(Scheme);
	AnimationController->SetProportional(false);

	SetProportional(false);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetDeleteSelfOnClose(true);
	SetTitleBarVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetEnabled(true);
	SetVisible(false);
	SetParent(Parent);

	Activate();

	PanelTitle = GetGameUI2().ConvertToLocalizedString("#GameUI2_TitleOptions");
	PanelTitle = wcsupr(PanelTitle);

	ButtonDone = new Button_Panel(this, this, "");
	ButtonDone->SetButtonText("#GameUI2_Done");
	ButtonDone->SetButtonDescription("");

	ButtonApply = new Button_Panel(this, this, "");
	ButtonApply->SetButtonText("#GameUI2_Apply");
	ButtonApply->SetButtonDescription("");

	ButtonBack = new Button_Panel(this, this, "action_back");
	ButtonBack->SetButtonText("#GameUI2_Back");
	ButtonBack->SetButtonDescription("");
}

void Panel_Options::ApplySchemeSettings(vgui::IScheme* Scheme)
{
	BaseClass::ApplySchemeSettings(Scheme);

	BackgroundGradientTop = GetSchemeColor("Panel.Background.Gradient.Top", Scheme);
	BackgroundGradientBottom = GetSchemeColor("Panel.Background.Gradient.Bottom", Scheme);

	TitleColor = GetSchemeColor("Panel.Title.Color", Scheme);

	TitleOffsetX = atof(Scheme->GetResourceString("Panel.Title.OffsetX"));
	TitleOffsetY = atof(Scheme->GetResourceString("Panel.Title.OffsetY"));

	TitleFont = Scheme->GetFont("Panel.Title.Font");
}

void Panel_Options::Animations()
{
	if (AnimationController != nullptr)
		AnimationController->UpdateAnimations(GetGameUI2().GetTime());

	SetBounds(0, 0, GetGameUI2().GetViewport().x, GetGameUI2().GetViewport().y);
}

void Panel_Options::OnThink()
{
	BaseClass::OnThink();

	SetContentBounds();
	Animations();

	if (IsVisible() == false)
	{
		ConColorMsg(Color(0, 148, 255, 255), "Options panel is not visible, running all animations to completion...\n");

		if (AnimationController != nullptr)
			AnimationController->RunAllAnimationsToCompletion();
	}
}

void Panel_Options::SetContentBounds()
{	
	ContentW = (GetWide() / 100) * 75;
	if (ContentW > 1920)
		ContentW = 1920;
	else if (ContentW < 800)
		ContentW = 800;

	ContentH = (GetTall() / 100) * 75;
	if (ContentH > 1080)
		ContentH = 1080;
	else if (ContentH < 600)
		ContentH = 600;

	ContentX0 = GetWide() / 2 - ContentW / 2;
	ContentY0 = GetTall() / 2 - ContentH / 2;

	ContentX1 = ContentX0 + ContentW;
	ContentY1 = ContentY0 + ContentH;
}

void Panel_Options::Paint()
{
	BaseClass::Paint();

	DrawBackground();
	DrawTitle();
	DrawTabs();
	DrawBasicButtons();
}

void Panel_Options::PaintBlurMask()
{
	BaseClass::PaintBlurMask();
}

void Panel_Options::DrawBackground()
{
	vgui::surface()->DrawSetColor(BackgroundGradientTop);
	vgui::surface()->DrawFilledRectFade(0, 0, GetWide() + 0, GetTall() + 0, 255, 0, false);

	vgui::surface()->DrawSetColor(BackgroundGradientBottom);
	vgui::surface()->DrawFilledRectFade(0, 0, GetWide() + 0, GetTall() + 0, 0, 255, false);
}


void Panel_Options::DrawTitle()
{
	if (PanelTitle == nullptr)
		return;
	
	vgui::surface()->DrawSetTextColor(TitleColor);
	vgui::surface()->DrawSetTextFont(TitleFont);

	vgui::surface()->GetTextSize(TitleFont, PanelTitle, TitleSizeX, TitleSizeY);
	TitlePositionX = ContentX0 + TitleOffsetX;
	TitlePositionY = ContentY0 + TitleOffsetY;
	
	vgui::surface()->DrawSetTextPos(TitlePositionX, TitlePositionY);
	vgui::surface()->DrawPrintText(PanelTitle, wcslen(PanelTitle));
}

void Panel_Options::DrawTabs()
{
	// TEST!
	int32 X0, Y0;
	ButtonDone->GetPos(X0, Y0);
	
	int8 ObjectHeight = 48;
	int16 ContentHeight = Y0 - (TitlePositionY - TitleOffsetY + TitleSizeY);
	int8 ObjectsPerHeight = ContentHeight / ObjectHeight;

	for (int8 i = 0; i < ObjectsPerHeight; i++)
	{
		if (i % 2)
			vgui::surface()->DrawSetColor(Color(0, 0, 0, 20));
		else
			vgui::surface()->DrawSetColor(Color(255, 255, 255, 1));

		int32 ObjectY = TitlePositionY + TitleSizeY + (ObjectHeight * (i + 1)) - ObjectHeight;
		vgui::surface()->DrawFilledRect(ContentX0, ObjectY, ContentW + ContentX0, ObjectHeight + ObjectY);
	}
	// TEST!
}

void Panel_Options::DrawBasicButtons()
{
	ButtonDone->SetPos(ContentX0, ContentY1 - ButtonDone->GetTall());
	ButtonDone->SetVisible(true);

	int32 X0, Y0;
	ButtonDone->GetPos(X0, Y0);
	
	ButtonApply->SetPos(X0 + ButtonDone->GetWide(), ContentY1 - ButtonApply->GetTall());
	ButtonApply->SetVisible(true);
	
	ButtonBack->SetPos(ContentX1 - ButtonBack->GetWide(), ContentY1 - ButtonBack->GetTall());
	ButtonBack->SetVisible(true);
}

void Panel_Options::OnCommand(char const* Command)
{
	if (Q_stristr(Command, "action_back"))
	{
		Close();
	}
	else
	{
		BaseClass::OnCommand(Command);
	}
}

CON_COMMAND(gameui2_openoptionsdialog, "")
{
	new Panel_Options(GetGameUI2().GetVPanel(), "");
}