/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#pragma once

#include "vgui2d/frame2d.h"
#include "vgui_controls/AnimationController.h"

#include "button_panel.h"

class Panel_Options : public Frame2D
{
	DECLARE_CLASS_SIMPLE(Panel_Options, Frame2D);

public:
	Panel_Options(vgui::VPANEL Parent, const char* PanelName);

	virtual void ApplySchemeSettings(vgui::IScheme* Scheme);
	virtual void OnThink();
	virtual void SetContentBounds();
	virtual void Paint();
	virtual void PaintBlurMask();
	virtual void Animations();
	virtual void DrawBackground();
	virtual void DrawTitle();
	virtual void DrawTabs();
	virtual void DrawBasicButtons();
	virtual void OnCommand(char const* Command);

private:
	vgui::AnimationController* AnimationController;

	Button_Panel* ButtonApply;
	Button_Panel* ButtonDone;
	Button_Panel* ButtonBack;

	int32 ContentX0;
	int32 ContentY0;
	int32 ContentX1;
	int32 ContentY1;
	int32 ContentW;
	int32 ContentH;

	wchar_t* PanelTitle;

	int32 TitlePositionX;
	int32 TitlePositionY;
	int32 TitleSizeX;
	int32 TitleSizeY;

	Color BackgroundGradientTop;
	Color BackgroundGradientBottom;

	Color TitleColor;

	float TitleOffsetX;
	float TitleOffsetY;

	vgui::HFont TitleFont;
};