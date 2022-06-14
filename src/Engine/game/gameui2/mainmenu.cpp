/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "basepanel.h"
#include "mainmenu.h"

#include "vgui/ISurface.h"
#include "vgui/ILocalize.h"
#include "vgui/IVGui.h"

#include "KeyValues.h"
#include "filesystem.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

int32 __cdecl ButtonsPositionBottom(Button_MainMenu* const* s1, Button_MainMenu* const* s2)
{
	return ((*s1)->GetPriority() > (*s2)->GetPriority());
}

int32 __cdecl ButtonsPositionTop(Button_MainMenu* const* s1, Button_MainMenu* const* s2)
{
	return ((*s1)->GetPriority() < (*s2)->GetPriority());
}

MainMenu::MainMenu(vgui::Panel* Parent) : BaseClass(nullptr, "MainMenu")
{
	vgui::HScheme Scheme = vgui::scheme()->LoadSchemeFromFile("resource2/schememainmenu.res", "SchemeMainMenu");
	SetScheme(Scheme);

	SetProportional(false);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetDeleteSelfOnClose(true);
	SetSizeable(false);
	SetMoveable(false);
	SetCloseButtonVisible(false);
	SetMenuButtonVisible(false);

	bIsVisible = false;

	LogoLeftText = GetGameUI2().ConvertToLocalizedString("#GameUI2_LogoLeft");
	LogoRightText = GetGameUI2().ConvertToLocalizedString("#GameUI2_LogoRight");

	CreateMenu("resource2/mainmenu.res");
}

void MainMenu::CreateMenu(const char* MenuScript)
{
	KeyValues* DataFile = new KeyValues("MainMenu");
	DataFile->UsesEscapeSequences(true);
	if (DataFile->LoadFromFile(g_pFullFileSystem, MenuScript) == true)
	{
		for (KeyValues* Data = DataFile->GetFirstSubKey(); Data != nullptr; Data = Data->GetNextKey())
		{
			Button_MainMenu* Button = new Button_MainMenu(this, this, Data->GetString("command", ""));
			Button->SetPriority(atoi(Data->GetString("priority", "1")));
			Button->SetButtonText(Data->GetString("text", "no text"));
			Button->SetButtonDescription(Data->GetString("description", "no description"));

			const char* Specifics = Data->GetString("specifics", "shared");
			if (Q_stristr(Specifics, "ingame"))
			{
				ButtonsInGame.AddToTail(Button);
			}
			else if (Q_stristr(Specifics, "mainmenu"))
			{
				ButtonsBackground.AddToTail(Button);
			}
			else if (Q_stristr(Specifics, "shared"))
			{
				ButtonsShared.AddToTail(Button);
			}
		}
	}
}

void MainMenu::ApplySchemeSettings(vgui::IScheme* Scheme)
{
	BaseClass::ApplySchemeSettings(Scheme);

	ConColorMsg(Color(0, 148, 0, 255), "Loading main menu scheme...\n");
	
	ButtonsSpace = atof(Scheme->GetResourceString("MainMenu.Buttons.Space"));
	ButtonsOffsetX = atof(Scheme->GetResourceString("MainMenu.Buttons.OffsetX"));
	ButtonsOffsetY = atof(Scheme->GetResourceString("MainMenu.Buttons.OffsetY"));
	LogoOffsetX = atof(Scheme->GetResourceString("MainMenu.Logo.OffsetX"));
	LogoOffsetY = atof(Scheme->GetResourceString("MainMenu.Logo.OffsetY"));
	LogoLeftColor = GetSchemeColor("MainMenu.Logo.Left", Scheme);
	LogoRightColor = GetSchemeColor("MainMenu.Logo.Right", Scheme);
	bLogoAttachToMenu = atoi(Scheme->GetResourceString("MainMenu.Logo.AttachToMenu"));
	bLogoAlignToLeft = atoi(Scheme->GetResourceString("MainMenu.Logo.AlignToLeft"));
	LogoFont = Scheme->GetFont("MainMenu.Logo.Font");
}

void MainMenu::OnThink()
{
	BaseClass::OnThink();

	SetBounds(0, 0, GetGameUI2().GetViewport().x, GetGameUI2().GetViewport().y);
}

bool MainMenu::IsVisible()
{
	if (GetGameUI2().IsInLoading() == true || GetGameUI2().GetGameUI()->IsMainMenuVisible() == false)
		return false;

	return bIsVisible;
}

void MainMenu::DrawMainMenu()
{
	if (ActiveButtons.IsEmpty() == true)
		return;

	for (int8 i = 0; i < ActiveButtons.Count(); i++)
	{
		int8 NextButton = i + 1;
		
		if (NextButton < ActiveButtons.Count())
		{
			int32 NextButtonPositionX, NextButtonPositionY;
			ActiveButtons[NextButton]->GetPos(NextButtonPositionX, NextButtonPositionY);
			ActiveButtons[i]->SetPos(ButtonsOffsetX, NextButtonPositionY - (ActiveButtons[i]->GetTall() + ButtonsSpace));
		}
		else
		{
			ActiveButtons[i]->SetPos(ButtonsOffsetX, GetTall() - (ButtonsOffsetY + ActiveButtons[i]->GetTall()));
		}
	}
}

void MainMenu::DrawLogo()
{
	if (LogoLeftText == nullptr || LogoRightText == nullptr)
		return;
	
	vgui::surface()->DrawSetTextColor(LogoLeftColor);
	vgui::surface()->DrawSetTextFont(LogoFont);

	int32 LogoW, LogoH;
	vgui::surface()->GetTextSize(LogoFont, LogoLeftText, LogoW, LogoH);

	int32 LogoX, LogoY;
	if (ActiveButtons.IsEmpty() == true || bLogoAttachToMenu == false)
	{
		if (bLogoAlignToLeft == false)
		{
			wchar_t FullLogoText[256];
			wcscpy(FullLogoText, LogoLeftText);
			wcscat(FullLogoText, LogoRightText);

			int32 FullLogoW, FullLogoH;
			vgui::surface()->GetTextSize(LogoFont, FullLogoText, FullLogoW, FullLogoH);
			
			LogoX = GetWide() - (LogoOffsetX + FullLogoW);
		}
		else
		{
			LogoX = LogoOffsetX;
		}

		LogoY = GetTall() - (LogoOffsetY + LogoH);
	}
	else
	{
		int32 ButtonPositionX, ButtonPositionY;
		ActiveButtons[0]->GetPos(ButtonPositionX, ButtonPositionY);
		LogoX = ButtonsOffsetX + LogoOffsetX;
		LogoY = ButtonPositionY - (LogoH + LogoOffsetY);
	}

	vgui::surface()->DrawSetTextPos(LogoX, LogoY);
	vgui::surface()->DrawPrintText(LogoLeftText, wcslen(LogoLeftText));

	vgui::surface()->DrawSetTextColor(LogoRightColor);
	vgui::surface()->DrawSetTextFont(LogoFont);
	vgui::surface()->DrawSetTextPos(LogoX + LogoW, LogoY);
	vgui::surface()->DrawPrintText(LogoRightText, wcslen(LogoRightText));
}

void MainMenu::Paint()
{
	BaseClass::Paint();

	// TODO: Add script settings
	vgui::surface()->DrawSetColor(Color(0, 0, 0, 255));
	vgui::surface()->DrawFilledRectFade(0, 0, GetWide(), GetTall(), 255, 0, true);

	DrawMainMenu();
	DrawLogo();
}

void MainMenu::OnCommand(char const* Command)
{
	if (Q_stristr(Command, "cvar"))
	{
		const char* EngineCommand = strstr(Command, "cvar ") + strlen("cvar ");
		if (strlen(EngineCommand) > 0)
			GetGameUI2().GetEngineClient()->ClientCmd_Unrestricted(const_cast<char*>(EngineCommand));
	}
	else
	{
		BaseClass::OnCommand(Command);
	}
}

void MainMenu::OnSetFocus()
{
	BaseClass::OnSetFocus();

	UpdateMenu();
	
	bIsVisible = true;
	vgui::surface()->PlaySound("interface/ui/menu_open.wav");
}

void MainMenu::OnKillFocus()
{
	BaseClass::OnKillFocus();

	bIsVisible = false;
	vgui::surface()->PlaySound("interface/ui/menu_close.wav");
}

void MainMenu::UpdateMenu()
{
	for (int8 i = 0; i < ButtonsInGame.Count(); i++)
		ButtonsInGame[i]->SetVisible(GetGameUI2().IsInLevel());

	for (int8 i = 0; i < ButtonsBackground.Count(); i++)
		ButtonsBackground[i]->SetVisible(GetGameUI2().IsInBackgroundLevel());

	for (int8 i = 0; i < ButtonsShared.Count(); i++)
		ButtonsShared[i]->SetVisible(GetGameUI2().IsInLevel() || GetGameUI2().IsInBackgroundLevel());

	CUtlVector<Button_MainMenu*> UpdatedActiveButtons;

	if (GetGameUI2().IsInLevel() == true)
	{
		if (ButtonsInGame.IsEmpty() == false)
			UpdatedActiveButtons.AddVectorToTail(ButtonsInGame);
	}
	
	if (GetGameUI2().IsInBackgroundLevel() == true)
	{
		if (ButtonsBackground.IsEmpty() == false)
			UpdatedActiveButtons.AddVectorToTail(ButtonsBackground);
	}

	if (ButtonsShared.IsEmpty() == false)
		UpdatedActiveButtons.AddVectorToTail(ButtonsShared);

	if (UpdatedActiveButtons.IsEmpty() == false)
		UpdatedActiveButtons.Sort(ButtonsPositionTop);

	ActiveButtons = UpdatedActiveButtons;

	ConColorMsg(Color(0, 148, 0, 255), "Updating main menu...\n");
}

MainMenuHelper::MainMenuHelper(MainMenu* Menu, vgui::Panel* Parent) : BaseClass(Parent)
{
	Menu->SetParent(this);
	Menu->MakeReadyForUse();
	Menu->SetZPos(0);
}