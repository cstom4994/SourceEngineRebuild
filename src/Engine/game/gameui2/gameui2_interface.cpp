/*
Hyperborea (c) by Nicolas @ https://github.com/NicolasDe

Hyperborea is licensed under a
Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work.  If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
*/
#include "gameui2_interface.h"
#include "basepanel.h"
#include "vgui/ILocalize.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static CDllDemandLoader StaticGameUI("GameUI");

static GameUI2 StaticGameUI2;
GameUI2& GetGameUI2()
{
	return StaticGameUI2;
}

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(GameUI2, IGameUI2, GAMEUI2_DLL_INTERFACE_VERSION, StaticGameUI2);

void GameUI2::Initialize(CreateInterfaceFn AppFactory)
{
	MEM_ALLOC_CREDIT();
	ConnectTier1Libraries(&AppFactory, 1);
	ConnectTier2Libraries(&AppFactory, 1);
	ConVar_Register(FCVAR_CLIENTDLL);
	ConnectTier3Libraries(&AppFactory, 1);

	EngineClient = (IVEngineClient*)AppFactory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
	EngineSound = (IEngineSound*)AppFactory(IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL);
	EngineVGui = (IEngineVGui*)AppFactory(VENGINE_VGUI_VERSION, NULL);
	SoundEmitterSystemBase = (ISoundEmitterSystemBase*)AppFactory(SOUNDEMITTERSYSTEM_INTERFACE_VERSION, NULL);
	RenderView = (IVRenderView*)AppFactory(VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL);
	MaterialSystem = (IMaterialSystem*)AppFactory(MATERIAL_SYSTEM_INTERFACE_VERSION, NULL);
	MaterialSystemSurface = (IMatSystemSurface*)AppFactory(MAT_SYSTEM_SURFACE_INTERFACE_VERSION, NULL);

	CreateInterfaceFn GameUIFactory = StaticGameUI.GetFactory();
	if (GameUIFactory)
		GameUI = (IGameUI*)GameUIFactory(GAMEUI_INTERFACE_VERSION, NULL);

	if (EngineClient == nullptr ||
		EngineSound == nullptr ||
		EngineVGui == nullptr ||
		SoundEmitterSystemBase == nullptr ||
		RenderView == nullptr ||
		MaterialSystem == nullptr ||
		MaterialSystemSurface == nullptr ||
		GameUI == nullptr)
		Error("GameUI2 failed to get necessary interfaces.\n");

	GetBasePanel()->Create();

	if (GetBasePanel() != nullptr)
	{
		ConColorMsg(Color(255, 255, 0, 255), "Overriding original menu...\n");

		GameUI->SetMainMenuOverride(GetBasePanel()->GetVPanel());

		AnimationController = new vgui::AnimationController(GetBasePanel());
		AnimationController->SetProportional(false);
		AnimationController->SetScheme(GetBasePanel()->GetScheme());
	}
	else
	{
		ConColorMsg(Color(255, 255, 0, 255), "BasePanel initialization has failed.\n");
	}
//	IVDebugOverlay* debugoverlay = NULL;
}

void GameUI2::Shutdown()
{
	ConVar_Unregister();
	DisconnectTier3Libraries();
	DisconnectTier2Libraries();
	DisconnectTier1Libraries();
}

void GameUI2::OnInitialize()
{
	ConColorMsg(Color(255, 148, 0, 255), "On Initialize\n");

	GetBasePanel()->SetVisible(true);
	GetBasePanel()->GetMainMenuPanel()->Activate();
}

void GameUI2::OnShutdown()
{
	ConColorMsg(Color(255, 148, 0, 255), "On Shutdown\n");
}

void GameUI2::OnUpdate()
{
//	ConColorMsg(Color(255, 148, 0, 255), "On Update: %f\n", GetTime());
	
	if (AnimationController != nullptr)
		AnimationController->UpdateAnimations(GetTime());
}

void GameUI2::OnLevelInitializePreEntity()
{
	ConColorMsg(Color(255, 148, 0, 255), "On Level Initialize Pre Entity\n");
}

void GameUI2::OnLevelInitializePostEntity()
{
	ConColorMsg(Color(255, 148, 0, 255), "On Level Initialize Post Entity\n");
}

void GameUI2::OnLevelShutdown()
{
	ConColorMsg(Color(255, 148, 0, 255), "On Level Shutdown\n");

	if (AnimationController != nullptr)
	{
		AnimationController->UpdateAnimations(GetTime());
		AnimationController->RunAllAnimationsToCompletion();
	}
}

bool GameUI2::IsInLevel()
{
	if (EngineClient->IsInGame() == true && EngineClient->IsLevelMainMenuBackground() == false)
		return true;

	return false;
}

bool GameUI2::IsInBackgroundLevel()
{
//	if ((EngineClient->IsInGame() == true && EngineClient->IsLevelMainMenuBackground() == true) || EngineClient->IsInGame() == false) // ?!
	if (EngineClient->IsLevelMainMenuBackground() == true || EngineClient->IsInGame() == false)
		return true;

	return false;
}

bool GameUI2::IsInMultiplayer()
{
	return (IsInLevel() == true && EngineClient->GetMaxClients() > 1);
}

bool GameUI2::IsInLoading()
{
	return (EngineClient->IsDrawingLoadingImage() == true || EngineClient->GetLevelName() == 0) || (IsInLevel() == false && IsInBackgroundLevel() == false);
}

wchar_t* GameUI2::ConvertToLocalizedString(const char* Text)
{
	// The alt. version of LocalizedString if something is wrong with current one:
	// wchar_t* LocalizedString = new wchar_t[2048];
	wchar_t* LocalizedString = (wchar_t*)malloc(sizeof(wchar_t) * 2048);
	
	if (Text[0] == '#' && g_pVGuiLocalize != nullptr)
	{
		wchar_t* TempString = g_pVGuiLocalize->Find(Text);
		if (TempString != nullptr)
		{
			const size_t TextSize = wcslen(TempString) + 1;
			wcsncpy(LocalizedString, TempString, TextSize);
			LocalizedString[TextSize - 1] = 0;
		}
		else
		{
			const size_t TextSize = strlen(Text) + 1;
			mbstowcs(LocalizedString, Text, TextSize);
		}
	}
	else
	{
		const size_t TextSize = strlen(Text) + 1;
		mbstowcs(LocalizedString, Text, TextSize);
	}

	return LocalizedString;
}

void GameUI2::SetView(const CViewSetup& ViewSetup)
{
	View = ViewSetup;
}

void GameUI2::SetFrustum(VPlane* Plane)
{
	Frustum = Plane;
}

void GameUI2::SetMaskTexture(ITexture* Texture)
{
	MaskTexture = Texture;
}

void GameUI2::SetRenderContext(IMatRenderContext* Context)
{
	RenderContext = Context;
}

Vector2D GameUI2::GetViewport() const
{
//	return Vector2D(View.width, View.height);
	int32 ViewportX, ViewportY;
	EngineClient->GetScreenSize(ViewportX, ViewportY);
	return Vector2D(ViewportX, ViewportY);
}

vgui::VPANEL GameUI2::GetRootPanel() const
{
	return EngineVGui->GetPanel(PANEL_GAMEUIDLL);
}

vgui::VPANEL GameUI2::GetVPanel() const
{
	return GetBasePanel()->GetVPanel();
}

CON_COMMAND(gameui2, "List of arguments: version, help")
{
	if (args.ArgC() > 1)
	{
		if (Q_stristr(args.Arg(1), "version"))
		{
			ConColorMsg(Color(0, 148, 255, 255), "\nLabel:\t");
			Msg("%s\n", GAMEUI2_DLL_INTERFACE_VERSION);

			ConColorMsg(Color(0, 148, 255, 255), "Date:\t");
			Msg("%s\n", __DATE__);

			ConColorMsg(Color(0, 148, 255, 255), "Time:\t");
			Msg("%s\n", __TIME__);
		}
		else if (Q_stristr(args.Arg(1), "help"))
		{
			Msg("\nVisit ");
			ConColorMsg(Color(0, 148, 255, 255), "https://github.com/SourceEnginePlayground/Hyperborea");
			Msg(" to get the latest version or report an issue\n");
		}
	}
	else
	{
		ConColorMsg(Color(0, 148, 255, 255), "\nList of arguments: ");
		Msg("version, help\n");
	}
}