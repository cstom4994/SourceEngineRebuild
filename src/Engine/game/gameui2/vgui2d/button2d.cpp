/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "button2d.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

Button2D::Button2D(vgui::Panel* Parent, const char* PanelName, const char* Text, vgui::Panel* ActionSignalTarget, const char* Command) : BaseClass(Parent, PanelName, Text, ActionSignalTarget, Command)
{
	CommandShared = Command;

	Initialize();
}

Button2D::Button2D(vgui::Panel* Parent, const char* PanelName, const wchar_t* Text, vgui::Panel* ActionSignalTarget, const char* Command) : BaseClass(Parent, PanelName, Text, ActionSignalTarget, Command)
{
	CommandShared = Command;
	
	Initialize();
}

void Button2D::Initialize()
{
	SetBounds(0, 0, 0, 0);

	bSchemeLoaded = false;
}

void Button2D::OnThink()
{
	BaseClass::OnThink();

	AdditionalCursorCheck();
}

void Button2D::Paint()
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

void Button2D::PaintBlurMask()
{
	
}

void Button2D::ApplySchemeSettings(vgui::IScheme* Scheme)
{
	BaseClass::ApplySchemeSettings(Scheme);

	bSchemeLoaded = true;

	State = Out;
}

void Button2D::OnCursorExited()
{
	BaseClass::OnCursorExited();

	State = Out;
}

void Button2D::OnCursorEntered()
{
	BaseClass::OnCursorEntered();

	State = Over;
}

void Button2D::AdditionalCursorCheck()
{
	if (HasFocus() == true)
	{
		if (IsCursorOver() == false)
		{
			State = Out;
		}
		else if (IsCursorOver() == true && State == Out)
		{
			State = Over;
		}
	}
	else
	{
		if (IsCursorOver() == false)
			State = Out;
	}
}

void Button2D::OnMousePressed(vgui::MouseCode MouseCode)
{
	if (MouseCode == MOUSE_LEFT)
		State = Pressed;
}

void Button2D::OnMouseReleased(vgui::MouseCode MouseCode)
{
	if (MouseCode == MOUSE_LEFT)
		State = Released;
}