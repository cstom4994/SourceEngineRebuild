/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#pragma once

#include "vgui2d/panel2d.h"
#include "mainmenu.h"

class BasePanel : public Panel2D
{
	DECLARE_CLASS_SIMPLE(BasePanel, Panel2D);

public:
	BasePanel(vgui::VPANEL Parent);

	static void Create();
	virtual void OnThink();
	virtual void PaintBlurMask();
	
	virtual bool IsBackgroundMusicPlaying();
	virtual bool StartBackgroundMusic(float Volume);
	virtual void UpdateBackgroundMusicVolume(float Volume);
	virtual void ReleaseBackgroundMusic();

	virtual vgui::VPANEL GetVPanel();
	virtual MainMenu* GetMainMenuPanel() const { return MainMenuPanel; }
	virtual MainMenuHelper* GetMainMenuHelperPanel() const { return MainMenuHelperPanel; }

private:
	CUtlString BackgroundMusic;
	int32 BackgroundMusicGUID;

	MainMenu* MainMenuPanel;
	MainMenuHelper* MainMenuHelperPanel;
};

extern BasePanel* GetBasePanel();