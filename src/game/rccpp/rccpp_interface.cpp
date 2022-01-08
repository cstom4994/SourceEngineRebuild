// Copyright(c) 2019 - 2021, KaoruXun All rights reserved.

#include "rccpp_interface.h"
#include "vgui/ILocalize.h"

#include <stdlib.h>

#include "SDL.h"

#undef main

// imgui headers
#include <imgui.h>
#include "imgui_sdl.h"

// RCC++ headers
#include "RuntimeObjectSystem.h"

// headers from our example
#include "StdioLogSystem.h"
#include "SystemTable.h"
#include "RCCppMainLoop.h"

// RCC++ Data
static StdioLogSystem g_Logger;
static SystemTable g_SystemTable;

// Power save
const int POWERSAVEDRAWNUM = 3;
int powerSaveCountDown = POWERSAVEDRAWNUM;

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static RCCPP StaticRCCPP;

RCCPP &GetRCCPP() {
    return StaticRCCPP;
}

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(RCCPP, IRCCPP, RCCPP_DLL_INTERFACE_VERSION, StaticRCCPP);


void ResetPowerSaveCountDown() { powerSaveCountDown = 3; }

//void WindowResizeCallback(GLFWwindow *window, int width, int height) { ResetPowerSaveCountDown(); }
//
//void WindowPosCallback(GLFWwindow *window, int xpos, int ypos) { ResetPowerSaveCountDown(); }
//
//void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    ResetPowerSaveCountDown();
//    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
//}
//
//void CharCallback(GLFWwindow *window, unsigned int character) {
//    ResetPowerSaveCountDown();
//    ImGui_ImplGlfw_CharCallback(window, character);
//}
//
//void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
//    ResetPowerSaveCountDown();
//    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
//}
//
//void MousePosCallback(GLFWwindow *window, double x, double y) { ResetPowerSaveCountDown(); }
//
//void MouseWheelCallback(GLFWwindow *window, double x, double y) {
//    ResetPowerSaveCountDown();
//    ImGui_ImplGlfw_ScrollCallback(window, x, y);
//}

bool RCCppInit() {
    g_SystemTable.pImContext = ImGui::GetCurrentContext();

    g_SystemTable.pRuntimeObjectSystem = new RuntimeObjectSystem;
    if (!g_SystemTable.pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable)) {
        delete g_SystemTable.pRuntimeObjectSystem;
        g_SystemTable.pRuntimeObjectSystem = 0;
        return false;
    }

    g_SystemTable.pRuntimeObjectSystem->CleanObjectFiles();
#ifndef _WIN32
    g_SystemTable.pRuntimeObjectSystem->SetAdditionalCompileOptions( "-std=c++11" );
#endif

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_SystemTable.pRuntimeObjectSystem->FindFile(__FILE__).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_SystemTable.pRuntimeObjectSystem->AddIncludeDir(imguiIncludeDir.c_str());

    return true;
}

void RCCppCleanup() {
    delete g_SystemTable.pRuntimeObjectSystem;
}

void RCCppUpdate() {
    //check status of any compile
    if (g_SystemTable.pRuntimeObjectSystem->GetIsCompiledComplete()) {
        // load module when compile complete
        g_SystemTable.pRuntimeObjectSystem->LoadCompiledModule();
    }

    if (!g_SystemTable.pRuntimeObjectSystem->GetIsCompiling()) {
        float deltaTime = 1.0f / ImGui::GetIO().Framerate;
        g_SystemTable.pRuntimeObjectSystem->GetFileChangeNotifier()->Update(deltaTime);
    } else {
        ResetPowerSaveCountDown();
    }
}


ImVec4 clear_color = ImColor(114, 144, 154);

SDL_Texture *texture;
SDL_Window *window;
SDL_Renderer *renderer;

void RCCPP::Initialize(CreateInterfaceFn AppFactory) {
    MEM_ALLOC_CREDIT();
    ConnectTier1Libraries(&AppFactory, 1);
    ConnectTier2Libraries(&AppFactory, 1);
    ConVar_Register(FCVAR_CLIENTDLL);
    ConnectTier3Libraries(&AppFactory, 1);

    EngineClient = (IVEngineClient *) AppFactory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
    EngineVGui = (IEngineVGui *) AppFactory(VENGINE_VGUI_VERSION, NULL);
    RenderView = (IVRenderView *) AppFactory(VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL);


    if (EngineClient == nullptr ||
        EngineVGui == nullptr ||
        RenderView == nullptr)
        Error("RCCPP failed to get necessary interfaces.\n");


    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Lambda Mod - RCCPP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                              SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ImGui::CreateContext();
    ImGuiSDL::Initialize(renderer, 800, 600);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
    {
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    // Initialize RCC++
    RCCppInit();

    // Setup style
    ImGui::StyleColorsDark();


    ConColorMsg(Color(255, 255, 0, 255), "RCCPP is running...\n");

//	IVDebugOverlay* debugoverlay = NULL;
}

void RCCPP::Shutdown() {
    ConVar_Unregister();
    DisconnectTier3Libraries();
    DisconnectTier2Libraries();
    DisconnectTier1Libraries();
}

void RCCPP::InitEditor() {

}

void RCCPP::OnInitialize() {
    ConColorMsg(Color(255, 148, 0, 255), "On Initialize\n");
}

void RCCPP::OnShutdown() {
    ConColorMsg(Color(255, 148, 0, 255), "On Shutdown\n");

    RCCppCleanup();

    ImGuiSDL::Deinitialize();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    ImGui::DestroyContext();
}

void RCCPP::OnUpdate() {

    static bool run = true;
    if (run) {
        ImGuiIO &io = ImGui::GetIO();

        int wheel = 0;
//
//        SDL_Event e;
//        while (SDL_PollEvent(&e)) {
//            if (e.type == SDL_QUIT) run = false;
//            else if (e.type == SDL_WINDOWEVENT) {
//                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//                    io.DisplaySize.x = static_cast<float>(e.window.data1);
//                    io.DisplaySize.y = static_cast<float>(e.window.data2);
//                }
//            } else if (e.type == SDL_MOUSEWHEEL) {
//                wheel = e.wheel.y;
//            }
//        }

        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

        // Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

        io.DeltaTime = 1.0f / 60.0f;
        io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
        io.MouseWheel = static_cast<float>(wheel);

        // Update RCC++
        RCCppUpdate();

        ImGui::NewFrame();

        // Call the function in our RCC++ class
        g_SystemTable.pRCCppMainLoopI->MainLoop();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Image");
        ImGui::Image(texture, ImVec2(100, 100));
        ImGui::End();

        SDL_SetRenderDrawColor(renderer, 114, 144, 154, 255);
        SDL_RenderClear(renderer);

        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());

        // Power save
        if (g_pSys->power_save) {
            if (powerSaveCountDown) {
                --powerSaveCountDown;
                //glfwPollEvents();
            } else {
                ResetPowerSaveCountDown();
                //glfwWaitEvents();
            }
        }

        SDL_RenderPresent(renderer);
    }
}

void RCCPP::OnLevelInitializePreEntity() {
    ConColorMsg(Color(255, 148, 0, 255), "On Level Initialize Pre Entity\n");
}

void RCCPP::OnLevelInitializePostEntity() {
    ConColorMsg(Color(255, 148, 0, 255), "On Level Initialize Post Entity\n");
}

void RCCPP::OnLevelShutdown() {
    ConColorMsg(Color(255, 148, 0, 255), "On Level Shutdown\n");
}

bool RCCPP::IsInLevel() {
    if (EngineClient->IsInGame() == true && EngineClient->IsLevelMainMenuBackground() == false)
        return true;

    return false;
}

bool RCCPP::IsInBackgroundLevel() {
//	if ((EngineClient->IsInGame() == true && EngineClient->IsLevelMainMenuBackground() == true) || EngineClient->IsInGame() == false) // ?!
    if (EngineClient->IsLevelMainMenuBackground() == true || EngineClient->IsInGame() == false)
        return true;

    return false;
}

bool RCCPP::IsInMultiplayer() {
    return (IsInLevel() == true && EngineClient->GetMaxClients() > 1);
}

bool RCCPP::IsInLoading() {
    return (EngineClient->IsDrawingLoadingImage() == true || EngineClient->GetLevelName() == 0) ||
           (IsInLevel() == false && IsInBackgroundLevel() == false);
}

wchar_t *RCCPP::ConvertToLocalizedString(const char *Text) {
    // The alt. version of LocalizedString if something is wrong with current one:
    // wchar_t* LocalizedString = new wchar_t[2048];
    wchar_t *LocalizedString = (wchar_t *) malloc(sizeof(wchar_t) * 2048);

    if (Text[0] == '#' && g_pVGuiLocalize != nullptr) {
        wchar_t *TempString = g_pVGuiLocalize->Find(Text);
        if (TempString != nullptr) {
            const size_t TextSize = wcslen(TempString) + 1;
            wcsncpy(LocalizedString, TempString, TextSize);
            LocalizedString[TextSize - 1] = 0;
        } else {
            const size_t TextSize = strlen(Text) + 1;
            mbstowcs(LocalizedString, Text, TextSize);
        }
    } else {
        const size_t TextSize = strlen(Text) + 1;
        mbstowcs(LocalizedString, Text, TextSize);
    }

    return LocalizedString;
}

void RCCPP::SetView(const CViewSetup &ViewSetup) {
    View = ViewSetup;
}

void RCCPP::SetFrustum(VPlane *Plane) {
    Frustum = Plane;
}

void RCCPP::SetMaskTexture(ITexture *Texture) {
    MaskTexture = Texture;
}

void RCCPP::SetRenderContext(IMatRenderContext *Context) {
    RenderContext = Context;
}

Vector2D RCCPP::GetViewport() const {
//	return Vector2D(View.width, View.height);
    int32 ViewportX, ViewportY;
    EngineClient->GetScreenSize(ViewportX, ViewportY);
    return Vector2D(ViewportX, ViewportY);
}

vgui::VPANEL RCCPP::GetRootPanel() const {
    return EngineVGui->GetPanel(PANEL_GAMEUIDLL);
}

CON_COMMAND(rccpp, "List of arguments: version, help") {
    if (args.ArgC() > 1) {
        if (Q_stristr(args.Arg(1), "version")) {
            ConColorMsg(Color(0, 148, 255, 255), "\nLabel:\t");
            Msg("%s\n", RCCPP_DLL_INTERFACE_VERSION);

            ConColorMsg(Color(0, 148, 255, 255), "Date:\t");
            Msg("%s\n", __DATE__);

            ConColorMsg(Color(0, 148, 255, 255), "Time:\t");
            Msg("%s\n", __TIME__);
        } else if (Q_stristr(args.Arg(1), "help")) {
            Msg("\nVisit ");
            ConColorMsg(Color(0, 148, 255, 255), "https://github.com/cstom4994");
            Msg(" to get the latest version or report an issue\n");
        }
    } else {
        ConColorMsg(Color(0, 148, 255, 255), "\nList of arguments: ");
        Msg("version, help\n");
    }
}