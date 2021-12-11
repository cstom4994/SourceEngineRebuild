/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "button_panel.h"

#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DECLARE_BUILD_FACTORY_DEFAULT_TEXT(Button_Panel, Button_Panel);

extern CUtlSymbolTable g_ButtonSoundNames;

Button_Panel::Button_Panel(vgui::Panel* Parent, vgui::Panel* ActionSignalTarget, const char* Command) : BaseClass(Parent, "", "", ActionSignalTarget, Command)
{
	// Use Initialize() instead
}

void Button_Panel::SetButtonText(const char* Text)
{
	ButtonText = GetGameUI2().ConvertToLocalizedString(Text);
	ButtonText = wcsupr(ButtonText);
}

void Button_Panel::SetButtonDescription(const char* Description)
{
	ButtonDescription = GetGameUI2().ConvertToLocalizedString(Description);
}

void Button_Panel::Initialize()
{
	BaseClass::Initialize();
	
	vgui::HScheme Scheme = vgui::scheme()->LoadSchemeFromFile("resource2/schemepanel.res", "SchemePanel");
	SetScheme(Scheme);

	SetProportional(false);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetEnabled(true);
	SetVisible(false);
}

void Button_Panel::ApplySchemeSettings(vgui::IScheme* Scheme)
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

	Width = WidthOut = atof(Scheme->GetResourceString("Panel.Button.Width.Out"));
	WidthOver = atof(Scheme->GetResourceString("Panel.Button.Width.Over"));
	WidthPressed = atof(Scheme->GetResourceString("Panel.Button.Width.Pressed"));
	WidthReleased = atof(Scheme->GetResourceString("Panel.Button.Width.Released"));

	Height = HeightOut = atof(Scheme->GetResourceString("Panel.Button.Height.Out"));
	HeightOver = atof(Scheme->GetResourceString("Panel.Button.Height.Over"));
	HeightPressed = atof(Scheme->GetResourceString("Panel.Button.Height.Pressed"));
	HeightReleased = atof(Scheme->GetResourceString("Panel.Button.Height.Released"));

	TextOffsetX = atof(Scheme->GetResourceString("Panel.Button.Text.OffsetX"));
	TextOffsetY = atof(Scheme->GetResourceString("Panel.Button.Text.OffsetY"));

	DescriptionOffsetX = atof(Scheme->GetResourceString("Panel.Button.Description.OffsetX"));
	DescriptionOffsetY = atof(Scheme->GetResourceString("Panel.Button.Description.OffsetY"));

	bDescriptionHideOut = atoi(Scheme->GetResourceString("Panel.Button.Description.Hide.Out"));
	bDescriptionHideOver = atoi(Scheme->GetResourceString("Panel.Button.Description.Hide.Over"));
	bDescriptionHidePressed = atoi(Scheme->GetResourceString("Panel.Button.Description.Hide.Pressed"));
	bDescriptionHideReleased = atoi(Scheme->GetResourceString("Panel.Button.Description.Hide.Released"));

	AnimationWidth = atof(Scheme->GetResourceString("Panel.Button.Animation.Width"));
	AnimationHeight = atof(Scheme->GetResourceString("Panel.Button.Animation.Height"));
	AnimationBackground = atof(Scheme->GetResourceString("Panel.Button.Animation.Background"));
	AnimationText = atof(Scheme->GetResourceString("Panel.Button.Animation.Text"));
	AnimationDescription = atof(Scheme->GetResourceString("Panel.Button.Animation.Description"));

	BackgroundColor = BackgroundColorOut = GetSchemeColor("Panel.Button.Background.Out", Scheme);
	BackgroundColorOver = GetSchemeColor("Panel.Button.Background.Over", Scheme);
	BackgroundColorPressed = GetSchemeColor("Panel.Button.Background.Pressed", Scheme);
	BackgroundColorReleased = GetSchemeColor("Panel.Button.Background.Released", Scheme);

	BackgroundOutlineColor = BackgroundOutlineColorOut = GetSchemeColor("Panel.Button.Background.Outline.Out", Scheme);
	BackgroundOutlineColorOver = GetSchemeColor("Panel.Button.Background.Outline.Over", Scheme);
	BackgroundOutlineColorPressed = GetSchemeColor("Panel.Button.Background.Outline.Pressed", Scheme);
	BackgroundOutlineColorReleased = GetSchemeColor("Panel.Button.Background.Outline.Released", Scheme);

	TextColor = TextColorOut = GetSchemeColor("Panel.Button.Text.Out", Scheme);
	TextColorOver = GetSchemeColor("Panel.Button.Text.Over", Scheme);
	TextColorPressed = GetSchemeColor("Panel.Button.Text.Pressed", Scheme);
	TextColorReleased = GetSchemeColor("Panel.Button.Text.Released", Scheme);

	DescriptionColor = DescriptionColorOut = GetSchemeColor("Panel.Button.Description.Out", Scheme);
	DescriptionColorOver = GetSchemeColor("Panel.Button.Description.Over", Scheme);
	DescriptionColorPressed = GetSchemeColor("Panel.Button.Description.Pressed", Scheme);
	DescriptionColorReleased = GetSchemeColor("Panel.Button.Description.Released", Scheme);

	BackgroundBlurAlpha = Color(0, 0, 0, 0);
	bBackgroundBlurOut = atoi(Scheme->GetResourceString("Panel.Button.Background.Blur.Out"));
	bBackgroundBlurOver = atoi(Scheme->GetResourceString("Panel.Button.Background.Blur.Over"));
	bBackgroundBlurPressed = atoi(Scheme->GetResourceString("Panel.Button.Background.Blur.Pressed"));
	bBackgroundBlurReleased = atoi(Scheme->GetResourceString("Panel.Button.Background.Blur.Released"));

	TextFont = Scheme->GetFont("Panel.Button.Text.Font");
	DescriptionFont = Scheme->GetFont("Panel.Button.Description.Font");

	PreviousState = State;
}

void Button_Panel::Animations()
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
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurOut ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Over:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthOver, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightOver, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorOver, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorOver, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorOver, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorOver, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurOver ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Pressed:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthPressed, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightPressed, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorPressed, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorPressed, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorPressed, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorPressed, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurPressed ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Released:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthReleased, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightReleased, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorReleased, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorReleased, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorReleased, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorReleased, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurReleased ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			default:
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Width", WidthOut, 0.0f, AnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "Height", HeightOut, 0.0f, AnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundColor", BackgroundColorOut, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundOutlineColor", BackgroundOutlineColorOut, 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "TextColor", TextColorOut, 0.0f, AnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "DescriptionColor", DescriptionColorOut, 0.0f, AnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				GetGameUI2().GetAnimationController()->RunAnimationCommand(this, "BackgroundBlurAlpha", bBackgroundBlurOut ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, AnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;
		}

		PreviousState = State;
	}

	SetSize(Width, Height);
}

void Button_Panel::OnThink()
{
	BaseClass::OnThink();

	Animations();
}

void Button_Panel::DrawButton()
{
	vgui::surface()->DrawSetColor(BackgroundColor);
	vgui::surface()->DrawFilledRect(0, 0, Width + 0, Height + 0);

	vgui::surface()->DrawSetColor(BackgroundOutlineColor);
	vgui::surface()->DrawOutlinedRect(0, 0, Width + 0, Height + 0);
}

void Button_Panel::DrawButton_Blur()
{
	vgui::surface()->DrawSetColor(BackgroundBlurAlpha);
	vgui::surface()->DrawFilledRect(0, 0, Width + 0, Height + 0);
}

void Button_Panel::DrawText()
{
	if (ButtonText == nullptr)
		return;
	
	vgui::surface()->DrawSetTextColor(TextColor);
	vgui::surface()->DrawSetTextFont(TextFont);

	vgui::surface()->GetTextSize(TextFont, ButtonText, TextSizeX, TextSizeY);
	TextPositionX = TextOffsetX;
	TextPositionY = Height / 2 - TextSizeY / 2 + TextOffsetY;

	vgui::surface()->DrawSetTextPos(TextPositionX, TextPositionY);
	vgui::surface()->DrawPrintText(ButtonText, wcslen(ButtonText));
}

void Button_Panel::DrawDescription()
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

void Button_Panel::Paint()
{
	BaseClass::Paint();

	DrawButton();
	DrawText();
	DrawDescription();
}

void Button_Panel::PaintBlurMask()
{
	BaseClass::PaintBlurMask();

	if (GetGameUI2().IsInBackgroundLevel() == true)
		DrawButton_Blur();
}

void Button_Panel::OnMousePressed(vgui::MouseCode MouseCode)
{
	BaseClass::OnMousePressed(MouseCode);
	
	if (MouseCode == MOUSE_LEFT)
	{
		if (m_sDepressedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sDepressedSoundName));
	}
}

void Button_Panel::OnMouseReleased(vgui::MouseCode MouseCode)
{
	BaseClass::OnMouseReleased(MouseCode);
	
	if (MouseCode == MOUSE_LEFT)
	{
		if (m_sReleasedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sReleasedSoundName));

		GetParent()->OnCommand(CommandShared);
	}
}