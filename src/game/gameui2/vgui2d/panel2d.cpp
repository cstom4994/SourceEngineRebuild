/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "panel2d.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

Panel2D::Panel2D() : BaseClass()
{
	SetBounds(0, 0, 0, 0);
	
	bSchemeLoaded = false;
}

Panel2D::Panel2D(vgui::Panel* Parent) : BaseClass(Parent)
{
	SetBounds(0, 0, 0, 0);
	
	bSchemeLoaded = false;
}

Panel2D::Panel2D(vgui::Panel* Parent, const char* PanelName) : BaseClass(Parent, PanelName)
{
	SetBounds(0, 0, 0, 0);
	
	bSchemeLoaded = false;
}

Panel2D::Panel2D(vgui::Panel* Parent, const char* PanelName, vgui::HScheme Scheme) : BaseClass(Parent, PanelName, Scheme)
{
	SetBounds(0, 0, 0, 0);
	
	bSchemeLoaded = false;
}

void Panel2D::Paint()
{
	if (bSchemeLoaded == false)
		return;
	
	BaseClass::Paint();

	if (GetGameUI2().GetMaterialSystem() != nullptr &&
		GetGameUI2().GetRenderView() != nullptr &&
		GetGameUI2().GetMaskTexture() != nullptr &&
		GetGameUI2().GetFrustum() != nullptr)
	{
		bBlurEnabled = true;

		GetGameUI2().GetRenderView()->Push2DView(GetGameUI2().GetView(), 0, GetGameUI2().GetMaskTexture(), GetGameUI2().GetFrustum());
		PaintBlurMask();
		GetGameUI2().GetRenderView()->PopView(GetGameUI2().GetFrustum());
	}

	bBlurEnabled = false;
}

void Panel2D::PaintBlurMask()
{
	
}

void Panel2D::ApplySchemeSettings(vgui::IScheme* Scheme)
{
	BaseClass::ApplySchemeSettings(Scheme);

	bSchemeLoaded = true;
}