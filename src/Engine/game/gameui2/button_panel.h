/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#pragma once

#include "vgui2d/button2d.h"

class Button_Panel : public Button2D
{
	DECLARE_CLASS_SIMPLE(Button_Panel, Button2D);

public:
	Button_Panel(vgui::Panel* Parent, vgui::Panel* ActionSignalTarget = nullptr, const char* Command = NULL);

	virtual void Initialize();
	virtual void ApplySchemeSettings(vgui::IScheme* Scheme);
	virtual void OnThink();
	virtual void DrawButton();
	virtual void DrawButton_Blur();
	virtual void DrawText();
	virtual void DrawDescription();
	virtual void Paint();
	virtual void PaintBlurMask();
	virtual void Animations();

	virtual void OnMouseReleased(vgui::MouseCode MouseCode);
	virtual void OnMousePressed(vgui::MouseCode MouseCode);

	virtual void SetButtonText(const char* Text);
	virtual void SetButtonDescription(const char* Description);

private:
	ButtonState PreviousState;
	wchar_t* ButtonText;
	wchar_t* ButtonDescription;
	int32 Priority;
	int32 TextPositionX;
	int32 TextPositionY;
	int32 TextSizeX;
	int32 TextSizeY;

	CPanelAnimationVar(float, Width, "Width", "0");
	CPanelAnimationVar(float, Height, "Height", "0");
	CPanelAnimationVar(Color, BackgroundColor, "BackgroundColor", "0 0 0 0");
	CPanelAnimationVar(Color, BackgroundOutlineColor, "BackgroundOutlineColor", "0 0 0 0");
	CPanelAnimationVar(Color, TextColor, "TextColor", "0 0 0 0");
	CPanelAnimationVar(Color, DescriptionColor, "DescriptionColor", "0 0 0 0");
	CPanelAnimationVar(Color, BackgroundBlurAlpha, "BackgroundBlurAlpha", "0 0 0 0");

	float WidthOut;
	float WidthOver;
	float WidthPressed;
	float WidthReleased;

	float HeightOut;
	float HeightOver;
	float HeightPressed;
	float HeightReleased;

	float TextOffsetX;
	float TextOffsetY;

	float DescriptionOffsetX;
	float DescriptionOffsetY;

	bool bDescriptionHideOut;
	bool bDescriptionHideOver;
	bool bDescriptionHidePressed;
	bool bDescriptionHideReleased;

	float AnimationWidth;
	float AnimationHeight;
	float AnimationBackground;
	float AnimationText;
	float AnimationDescription;

	Color BackgroundColorOut;
	Color BackgroundColorOver;
	Color BackgroundColorPressed;
	Color BackgroundColorReleased;

	Color BackgroundOutlineColorOut;
	Color BackgroundOutlineColorOver;
	Color BackgroundOutlineColorPressed;
	Color BackgroundOutlineColorReleased;

	Color TextColorOut;
	Color TextColorOver;
	Color TextColorPressed;
	Color TextColorReleased;

	Color DescriptionColorOut;
	Color DescriptionColorOver;
	Color DescriptionColorPressed;
	Color DescriptionColorReleased;

	bool bBackgroundBlurOut;
	bool bBackgroundBlurOver;
	bool bBackgroundBlurPressed;
	bool bBackgroundBlurReleased;

	vgui::HFont TextFont;
	vgui::HFont DescriptionFont;
};