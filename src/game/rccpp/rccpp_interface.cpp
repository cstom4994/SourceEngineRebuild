// Copyright(c) 2019 - 2021, KaoruXun All rights reserved.

#include "rccpp_interface.h"
#include "vgui/ILocalize.h"

#include <stdlib.h>

// imgui headers
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

// RCC++ headers
#include "RuntimeObjectSystem.h"

// headers from our example
#include "StdioLogSystem.h"
#include "SystemTable.h"
#include "RCCppMainLoop.h"

#include <GLFW/glfw3.h>

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

void WindowResizeCallback(GLFWwindow *window, int width, int height) { ResetPowerSaveCountDown(); }

void WindowPosCallback(GLFWwindow *window, int xpos, int ypos) { ResetPowerSaveCountDown(); }

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    ResetPowerSaveCountDown();
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void CharCallback(GLFWwindow *window, unsigned int character) {
    ResetPowerSaveCountDown();
    ImGui_ImplGlfw_CharCallback(window, character);
}

void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    ResetPowerSaveCountDown();
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void MousePosCallback(GLFWwindow *window, double x, double y) { ResetPowerSaveCountDown(); }

void MouseWheelCallback(GLFWwindow *window, double x, double y) {
    ResetPowerSaveCountDown();
    ImGui_ImplGlfw_ScrollCallback(window, x, y);
}

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

GLFWwindow *window;

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



    if (!glfwInit())
        exit(1);

    window = glfwCreateWindow(1280, 720, "Lambda Mod - RCCPP", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Power save - ensure callbacks point to the correct place
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSetWindowPosCallback(window, WindowPosCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCharCallback(window, CharCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MousePosCallback);
    glfwSetScrollCallback(window, MouseWheelCallback);

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL2_Init();

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

void RCCPP::OnInitialize() {
    ConColorMsg(Color(255, 148, 0, 255), "On Initialize\n");
}

void RCCPP::OnShutdown() {
    ConColorMsg(Color(255, 148, 0, 255), "On Shutdown\n");

    RCCppCleanup();
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void RCCPP::OnUpdate() {
//	ConColorMsg(Color(255, 148, 0, 255), "On Update: %f\n", GetTime());


    if (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Update RCC++
        RCCppUpdate();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Call the function in our RCC++ class
        g_SystemTable.pRCCppMainLoopI->MainLoop();

        // Rendering
        {
            glViewport(0, 0, (int) ImGui::GetIO().DisplaySize.x, (int) ImGui::GetIO().DisplaySize.y);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }

        // Power save
        if (g_pSys->power_save) {
            if (powerSaveCountDown) {
                --powerSaveCountDown;
                glfwPollEvents();
            } else {
                ResetPowerSaveCountDown();
                glfwWaitEvents();
            }
        }
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