/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "button_mainmenu.h"

#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DECLARE_BUILD_FACTORY_DEFAULT_TEXT(Button_MainMenu, Button_MainMenu);

extern CUtlSymbolTable g_ButtonSoundNames;

Button_MainMenu::Button_MainMenu(vgui::Panel* Parent, vgui::Panel* ActionSignalTarget, const char* Command) : BaseClass(Parent, "", "", ActionSignalTarget, Command)
{
	// Use Initialize() instead
}

void Button_MainMenu::SetButtonText(const char* Text)
{
	ButtonText = GetGameUI2().ConvertToLocalizedString(Text);
}

void Button_MainMenu::SetButtonDescription(const char* Description)
{
	ButtonDescription = GetGameUI2().ConvertToLocalizedString(Description);
}

void Button_MainMenu::Initialize()
{
	BaseClass::Initialize();
	
	vgui::HScheme Scheme = vgui::scheme()->LoadSchemeFromFile("resource2/schememainmenu.res", "SchemeMainMenu");
	SetScheme(Scheme);

	SetProportional(false);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetEnabled(true);
	SetVisible(false);
}

void Button_MainMenu::ApplySchemeSettings(vgui::IScheme* Scheme)
{
	BaseClass::ApplySchemeSettings(Scheme);

	SetDefaultColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetArmedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetSelectedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetDepressedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetBlinkColor(Color(0, 0, 0, 0));
	SetArmedSound("interface/ui/button_over.wav");
	SetDepressedSound("interface/ui/button_click.wav");
	SetReleasedSound("interface/ui/button_release.wav");

	Width = WidthOut = atof(Scheme->GetResourceString("MainMenu.Button.Width.Out"));
	WidthOver = atof(Scheme->GetResourceString("MainMenu.Button.Width.Over"));
	WidthPressed = atof(Scheme->GetResourceString("MainMenu.Button.Width.Pressed"));
	WidthReleased = atof(Scheme->GetResourceString("MainMenu.Button.Width.Released"));

	Height = HeightOut = atof(Scheme->GetResourceString("MainMenu.Button.Height.Out"));
	HeightOver = atof(Scheme->GetResourceString("MainMenu.Button.Height.Over"));
	HeightPressed = atof(Scheme->GetResourceString("MainMenu.Button.Height.Pressed"));
	HeightReleased = atof(Scheme->GetResourceString("MainMenu.Button.Height.Released"));

	TextOffsetX = atof(Scheme->GetResourceString("MainMenu.Button.Text.OffsetX"));
	TextOffsetY = atof(Scheme->GetResourceString("MainMenu.Button.Text.OffsetY"));

//	DescriptionOffsetX = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetX"));
//	DescriptionOffsetY = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetY"));
	DescriptionOffsetX = DescriptionOffsetXOut = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetX.Out"));
	DescriptionOffsetXOver = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetX.Over"));
	DescriptionOffsetXPressed = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetX.Pressed"));
	DescriptionOffsetXReleased = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetX.Released"));

	DescriptionOffsetY = DescriptionOffsetYOut = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetY.Out"));
	DescriptionOffsetYOver = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetY.Over"));
	DescriptionOffsetYPressed = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetY.Pressed"));
	DescriptionOffsetYReleased = atof(Scheme->GetResourceString("MainMenu.Button.Description.OffsetY.Released"));

	bDescriptionHideOut = atoi(Scheme->GetResourceString("MainMenu.Button.Description.Hide.Out"));
	bDescriptionHideOver = atoi(Scheme->GetResourceString("MainMenu.Button.Description.Hide.Over"));
	bDescriptionHidePressed = atoi(Scheme->GetResourceString("MainMenu.Button.Description.Hide.Pressed"));
	bDescriptionHideReleased = atoi(Scheme->GetResourceString("MainMenu.Button.Description.Hide.Released"));

	AnimationWidth = atof(Scheme->GetResourceString("MainMenu.Button.Animation.Width"));
	AnimationHeight = atof(Scheme->GetResourceString("MainMenu.Button.Animation.Height"));
	AnimationBackground = atof(Scheme->GetResourceString("MainMenu.Button.Animation.Background"));
	AnimationText = atof(Scheme->GetResourceString("MainMenu.Button.Animation.Text"));
	AnimationDescription = atof(Scheme->GetResourceString("MainMenu.Button.Animation.Description"));

	BackgroundColor = BackgroundColorOut = GetSchemeColor("MainMenu.Button.Background.Out", Scheme);
	BackgroundColorOver = GetSchemeColor("MainMenu.Button.Background.Over", Scheme);
	BackgroundColorPressed = GetSchemeColor("MainMenu.Button.Background.Pressed", Scheme);
	BackgroundColorReleased = GetSchemeColor("MainMenu.Button.Background.Released", Scheme);

	BackgroundOutlineColor = BackgroundOutlineColorOut = GetSchemeColor("MainMenu.Button.Background.Outline.Out", Scheme);
	BackgroundOutlineColorOver = GetSchemeColor("MainMenu.Button.Background.Outline.Over", Scheme);
	BackgroundOutlineColorPressed = GetSchemeColor("MainMenu.Button.Background.Outline.Pressed", Scheme);
	BackgroundOutlineColorReleased = GetSchemeColor("MainMenu.Button.Background.Outline.Released", Scheme);

	TextColor = TextColorOut = GetSchemeColor("MainMenu.Button.Text.Out", Scheme);
	TextColorOver = GetSchemeColor("MainMenu.Button.Text.Over", Scheme);
	TextColorPressed = GetSchemeColor("MainMenu.Button.Text.Pressed", Scheme);
	TextColorReleased = GetSchemeColor("MainMenu.Button.Text.Released", Scheme);

	TextGlowColor = TextGlowColorOut = GetSchemeColor("MainMenu.Button.Text.Glow.Out", Scheme);
	TextGlowColorOver = GetSchemeColor("MainMenu.Button.Text.Glow.Over", Scheme);
	TextGlowColorPressed = GetSchemeColor("MainMenu.Button.Text.Glow.Pressed", Scheme);
	TextGlowColorReleased = GetSchemeColor("MainMenu.Button.Text.Glow.Released", Scheme);

	DescriptionColor = DescriptionColorOut = GetSchemeColor("MainMenu.Button.Description.Out", Scheme);
	DescriptionColorOver = GetSchemeColor("MainMenu.Button.Description.Over", Scheme);
	DescriptionColorPressed = GetSchemeColor("MainMenu.Button.Description.Pressed", Scheme);
	DescriptionColorReleased = GetSchemeColor("MainMenu.Button.Description.Released", Scheme);

	BackgroundBlurAlpha = Color(0, 0, 0, 0);
	bBackgroundBlurOut = atoi(Scheme->GetResourceString("MainMenu.Button.Background.Blur.Out"));
	bBackgroundBlurOver = atoi(Scheme->GetResourceString("MainMenu.Button.Background.Blur.Over"));
	bBackgroundBlurPressed = atoi(Scheme->GetResourceString("MainMenu.Button.Background.Blur.Pressed"));
	bBackgroundBlurReleased = atoi(Scheme->GetResourceString("MainMenu.Button.Background.Blur.Released"));

	TextFont = Scheme->GetFont("MainMenu.Button.Text.Font");
	TextGlowFont = Scheme->GetFont("MainMenu.Button.Text.Glow.Font");
	DescriptionFont = Scheme->GetFont("MainMenu.Button.Description.Font");

	PreviousState = State;
}

void Button_MainMenu::Animations()
{
	if (PreviousState != State)
	{
		switch (State)
		{
			case Out:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthOut, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightOut, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorOut, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorOut, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorOut, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextGlowColor", TextGlowColorOut, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurOut ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);

				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetX", DescriptionOffsetXOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetY", DescriptionOffsetYOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				break;

			case Over:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthOver, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightOver, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorOver, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorOver, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorOver, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextGlowColor", TextGlowColorOver, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorOver, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurOver ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);

				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetX", DescriptionOffsetXOver, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetY", DescriptionOffsetYOver, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				break;

			case Pressed:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthPressed, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightPressed, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorPressed, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorPressed, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorPressed, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextGlowColor", TextGlowColorPressed, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorPressed, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurPressed ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);

				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetX", DescriptionOffsetXPressed, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetY", DescriptionOffsetYPressed, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				break;

			case Released:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthReleased, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightReleased, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorReleased, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorReleased, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorReleased, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextGlowColor", TextGlowColorReleased, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorReleased, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurReleased ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);

				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetX", DescriptionOffsetXReleased, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetY", DescriptionOffsetYReleased, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				break;

			default:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthOut, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightOut, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorOut, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorOut, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorOut, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextGlowColor", TextGlowColorOut, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurOut ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);

				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetX", DescriptionOffsetXOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionOffsetY", DescriptionOffsetYOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_SIMPLESPLINE);
				break;
		}

		PreviousState = State;
	}

	SetSize(Width, Height);
}

void Button_MainMenu::OnThink()
{
	BaseClass::OnThink();

	Animations();
}

void Button_MainMenu::DrawButton()
{
	vgui::surface()->DrawSetColor(BackgroundColor);
	vgui::surface()->DrawFilledRect(0, 0, Width + 0, Height + 0);

	vgui::surface()->DrawSetColor(BackgroundOutlineColor);
	vgui::surface()->DrawOutlinedRect(0, 0, Width + 0, Height + 0);
}

void Button_MainMenu::DrawButton_Blur()
{
	vgui::surface()->DrawSetColor(BackgroundBlurAlpha);
	vgui::surface()->DrawFilledRect(0, 0, Width + 0, Height + 0);
}

void Button_MainMenu::DrawText()
{
	if (ButtonText == nullptr)
		return;

	// GLOW TEST
	int AnimatedAlpha = (TextGlowColor.a() * 0.2) + (TextGlowColor.a() * 0.2) * sin(GetGameUI2().GetTime() * 4.0f);
	vgui::surface()->DrawSetTextColor(Color(TextGlowColor.r(), TextGlowColor.g(), TextGlowColor.b(), AnimatedAlpha));
	vgui::surface()->DrawSetTextFont(TextGlowFont);

	vgui::surface()->GetTextSize(TextGlowFont, ButtonText, TextSizeX, TextSizeY);
	TextPositionX = TextOffsetX;
	TextPositionY = Height / 2 - TextSizeY / 2 + TextOffsetY;

	vgui::surface()->DrawSetTextPos(TextPositionX, TextPositionY);
	vgui::surface()->DrawPrintText(ButtonText, wcslen(ButtonText));
	// GLOW END
	
	vgui::surface()->DrawSetTextColor(TextColor);
	vgui::surface()->DrawSetTextFont(TextFont);

	vgui::surface()->GetTextSize(TextFont, ButtonText, TextSizeX, TextSizeY);
	TextPositionX = TextOffsetX;
	TextPositionY = Height / 2 - TextSizeY / 2 + TextOffsetY;

	vgui::surface()->DrawSetTextPos(TextPositionX, TextPositionY);
	vgui::surface()->DrawPrintText(ButtonText, wcslen(ButtonText));
}

void Button_MainMenu::DrawDescription()
{
	if (ButtonDescription == nullptr)
		return;
	
	if (State == Out && bDescriptionHideOut == true ||
		State == Over && bDescriptionHideOver == true ||
		State == Pressed && bDescriptionHidePressed == true ||
		State == Released && bDescriptionHideReleased == true)
		return;

	vgui::surface()->DrawSetTextColor(DescriptionColor);
	vgui::surface()->DrawSetTextFont(DescriptionFont);
	vgui::surface()->DrawSetTextPos(TextPositionX + DescriptionOffsetX, TextPositionY + TextSizeY + DescriptionOffsetY);
	vgui::surface()->DrawPrintText(ButtonDescription, wcslen(ButtonDescription));
}

void Button_MainMenu::Paint()
{
	BaseClass::Paint();

	DrawButton();
	DrawText();
	DrawDescription();
}

void Button_MainMenu::PaintBlurMask()
{
	BaseClass::PaintBlurMask();
	
	if (GetGameUI2().IsInBackgroundLevel() == true)
		DrawButton_Blur();
}

void Button_MainMenu::OnMousePressed(vgui::MouseCode MouseCode)
{
	BaseClass::OnMousePressed(MouseCode);

	if (MouseCode == MOUSE_LEFT)
	{
		if (m_sDepressedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sDepressedSoundName));
	}
}

void Button_MainMenu::OnMouseReleased(vgui::MouseCode MouseCode)
{
	BaseClass::OnMouseReleased(MouseCode);
	
	if (MouseCode == MOUSE_LEFT)
	{
		if (m_sReleasedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sReleasedSoundName));

		GetParent()->OnCommand(CommandShared);
	}
}