/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#pragma once

#include "vgui_controls/Button.h"

enum ButtonState
{
	Out,
	Over,
	Pressed,
	Released
};

class Button2D : public vgui::Button
{
	DECLARE_CLASS_SIMPLE(Button2D, vgui::Button);

public:
	Button2D(vgui::Panel* Parent, const char* PanelName, const char* Text, vgui::Panel* ActionSignalTarget = nullptr, const char* Command = NULL);
	Button2D(vgui::Panel* Parent, const char* PanelName, const wchar_t* Text, vgui::Panel* ActionSignalTarget = nullptr, const char* Command = NULL);

	virtual void Initialize();
	virtual void Paint();
	virtual void PaintBlurMask();
	virtual void ApplySchemeSettings(vgui::IScheme* Scheme);
	virtual void AdditionalCursorCheck();
	virtual void OnThink();
	virtual void OnCursorEntered();
	virtual void OnCursorExited();
	virtual void OnMouseReleased(vgui::MouseCode MouseCode);
	virtual void OnMousePressed(vgui::MouseCode MouseCode);

	virtual bool IsBlur() const
	{
		return bBlurEnabled;
	}

	virtual bool IsFullyVisible()
	{
		return vgui::ipanel()->IsFullyVisible(GetVPanel());
	}

	virtual bool IsSchemeLoaded() const
	{
		return bSchemeLoaded;
	}

	ButtonState State;
	const char* CommandShared;

private:
	bool bBlurEnabled;
	bool bSchemeLoaded;
};
