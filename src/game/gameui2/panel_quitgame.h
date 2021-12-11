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

class Panel_QuitGame : public Frame2D
{
	DECLARE_CLASS_SIMPLE(Panel_QuitGame, Frame2D);

public:
	Panel_QuitGame(vgui::VPANEL Parent, const char* PanelName);

	virtual void OnThink();
	virtual void Paint();
	virtual void OnKillFocus();

private:
};