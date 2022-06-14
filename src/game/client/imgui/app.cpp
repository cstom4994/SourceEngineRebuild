#include "app.h"
#include "materialsystem/imaterialproxyfactory.h"
#include "materialsystem/ITexture.h"
#include "materialsystem/MaterialSystem_Config.h"
#include "istudiorender.h"
#include "tier2/camerautils.h"

// Bring in our non-source things
#include "memdbgoff.h"

#include <imgui_impl_source.h>
#include <imgui/imgui.h>

// Small struct to hold studiomdl info and render for us 
//class IMDLCache;
//
//extern IMDLCache *g_pMDLCache;
//
//struct studiomodel_t {
//    static studiomodel_t LoadModel(const char *path) {
//        MDLHandle_t mdlHandle = g_pMDLCache->FindMDL(path);
//
//        CStudioHdr *studiohdr = new CStudioHdr(g_pMDLCache->GetStudioHdr(mdlHandle), g_pMDLCache);
//        studiohwdata_t *studiohwdata = g_pMDLCache->GetHardwareData(mdlHandle);
//        if (studiohdr->GetRenderHdr()->version != STUDIO_VERSION) {
//            Error("Bad model version on %s! Expected %d, got %d!\n", path, STUDIO_VERSION,
//                  studiohdr->GetRenderHdr()->version);
//            return {0, 0};
//        }
//        return {studiohdr, studiohwdata};
//    }
//
//    void Draw(Vector &pos, QAngle &ang) {
//        if (!studiohdr || !studiohwdata)
//            return;
//
//        // Set the info
//        DrawModelInfo_t info;
//        memset(&info, 0, sizeof(info));
//        info.m_pStudioHdr = const_cast<studiohdr_t *>(studiohdr->GetRenderHdr());
//        info.m_pHardwareData = studiohwdata;
//        info.m_Lod = -1;
//
//        // Set the transform
//        matrix3x4_t matrix;
//        AngleMatrix(ang, matrix);
//        MatrixSetColumn(pos, 3, matrix);
//
//        // Draw it
//        g_pStudioRender->DrawModelStaticProp(info, matrix);
//    }
//
//    CStudioHdr *studiohdr;
//    studiohwdata_t *studiohwdata;
//};


// Currently blank, but might be worth filling in if you need mat proxies
//class CDummyMaterialProxyFactory : public IMaterialProxyFactory {
//public:
//    virtual IMaterialProxy *CreateProxy(const char *proxyName) { return nullptr; }
//
//    virtual void DeleteProxy(IMaterialProxy *pProxy) {}
//};
//
//CDummyMaterialProxyFactory g_DummyMaterialProxyFactory;

// glfw and imgui callbacks
static const char *getClipboardText(void *user_data) {
//    return glfwGetClipboardString((GLFWwindow *) user_data);
    return 0;
}

static void setClipboardText(void *user_data, const char *text) {
//    glfwSetClipboardString((GLFWwindow *) user_data, text);
}
//
//static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    ImGuiIO &io = ImGui::GetIO();
////    if (key >= 0 && key < IM_ARRAYSIZE(io.KeysDown))
////        io.KeysDown[key] = action != GLFW_RELEASE;
////
////    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
////    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
////    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
////    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
//}
//
//static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
//    ImGuiIO &io = ImGui::GetIO();
////    if (button >= 0 && button < IM_ARRAYSIZE(io.MouseDown))
////        io.MouseDown[button] = action != GLFW_RELEASE;
//}
//
//static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
//    ImGuiIO &io = ImGui::GetIO();
//    io.MousePos = ImVec2((float) xpos, (float) ypos);
//}
//
//static void charCallback(GLFWwindow *window, unsigned int c) {
//    ImGuiIO &io = ImGui::GetIO();
//    io.AddInputCharacter(c);
//}
//
//static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
//    ImGuiIO &io = ImGui::GetIO();
//    io.MouseWheelH += (float) xoffset;
//    io.MouseWheel += (float) yoffset;
//}


void CImGuiSourceApp::Init(CreateInterfaceFn AppFactory) {

    EngineClient = (IVEngineClient*)AppFactory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
    EngineSound = (IEngineSound*)AppFactory(IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL);
    EngineVGui = (IEngineVGui*)AppFactory(VENGINE_VGUI_VERSION, NULL);
    SoundEmitterSystemBase = (ISoundEmitterSystemBase*)AppFactory(SOUNDEMITTERSYSTEM_INTERFACE_VERSION, NULL);
    RenderView = (IVRenderView*)AppFactory(VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL);
    MaterialSystem = (IMaterialSystem*)AppFactory(MATERIAL_SYSTEM_INTERFACE_VERSION, NULL);
    MaterialSystemSurface = (IMatSystemSurface*)AppFactory(MAT_SYSTEM_SURFACE_INTERFACE_VERSION, NULL);

    if (EngineClient == nullptr ||
        EngineSound == nullptr ||
        EngineVGui == nullptr ||
        SoundEmitterSystemBase == nullptr ||
        RenderView == nullptr ||
        MaterialSystem == nullptr ||
        MaterialSystemSurface == nullptr)
        Error("ImGui failed to get necessary interfaces.\n");

    // Set up matsys
//    MaterialSystem_Config_t config;
//    config = g_pMaterialSystem->GetCurrentConfigForVideoCard();
//    config.SetFlag(MATSYS_VIDCFG_FLAGS_WINDOWED, true);
//    config.SetFlag(MATSYS_VIDCFG_FLAGS_RESIZING, true);

    // Feed material system our window
//    if (!g_pMaterialSystem->SetMode((void *)hwnd, config))
//        return;
//    g_pMaterialSystem->OverrideConfig(config, false);
//
//    // We want to set this before we load up any mats, else it'll reload em all
//    g_pMaterialSystem->SetMaterialProxyFactory(&g_DummyMaterialProxyFactory);
//
//    // White out our cubemap and lightmap, as we don't have either
//    m_pWhiteTexture = g_pMaterialSystem->FindTexture("white", NULL, true);
//    m_pWhiteTexture->AddRef();
//    g_pMaterialSystem->GetRenderContext()->BindLocalCubemap(m_pWhiteTexture);
//    g_pMaterialSystem->GetRenderContext()->BindLightmapTexture(m_pWhiteTexture);
//
//    // If we don't do this, all models will render black
//    int samples = g_pStudioRender->GetNumAmbientLightSamples();
//    m_ambientLightColors = new Vector[samples];
//    for (int i = 0; i < samples; i++)
//        m_ambientLightColors[i] = {1, 1, 1};
//    g_pStudioRender->SetAmbientLightColors(m_ambientLightColors);

    // Init Dear ImGui
    ImGui::CreateContext();
    ImGui_ImplSource_Init();
    ImGui::StyleColorsDark();

    // Wire up Dear ImGui into glfw
    ImGuiIO &io = ImGui::GetIO();

    // Looks crazy, I know, but ImGui only wants these. It takes in the rest of the keys as "char inputs"
//    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
//    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
//    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
//    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
//    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
//    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
//    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
//    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
//    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
//    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
//    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
//    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
//    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
//    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
//    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
//    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
//    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
//    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
//    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
//    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
//    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
//    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    io.SetClipboardTextFn = setClipboardText;
    io.GetClipboardTextFn = getClipboardText;
//    io.ClipboardUserData = m_pWindow;

    // Main app loop


}

void CImGuiSourceApp::Destroy() {
    // Clean up all of our assets, windows, etc
    if (m_ambientLightColors)
        delete[] m_ambientLightColors;

    if (m_pWhiteTexture)
        m_pWhiteTexture->DecrementReferenceCount();
}

// Current model in use
static char s_modelName[256] = "models/props_wasteland/laundry_cart002.mdl";

void CImGuiSourceApp::DrawFrame() {

    // Start Frame
    //g_pMaterialSystem->BeginFrame(0);

    // Clear out the old frame
//    CMatRenderContextPtr ctx(g_pMaterialSystem);
//    ctx->ClearColor3ub(0x30, 0x30, 0x30);
//    ctx->ClearBuffers(true, true);
//
//    // Let it know our window size
    int w, h;
    EngineClient->GetScreenSize(w, h);
//    ctx->Viewport(0, 0, w, h);

    // Begin ImGui
    // Ideally this happens before we branch off into other functions, as it needs to be setup for other sections of code to use imgui
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = {(float) w, (float) h};
    ImGui::NewFrame();

    // Make us a nice camera
//    VMatrix viewMatrix;
//    VMatrix projMatrix;
//    Camera_t m_cam = {{0, 0, 0}, {0, 0, 0}, 65, 1.0f, 20000.0f};
//    ComputeViewMatrix(&viewMatrix, m_cam);
//    ComputeProjectionMatrix(&projMatrix, m_cam, w, h);

    // 3D Rendering mode
//    ctx->MatrixMode(MATERIAL_PROJECTION);
//    ctx->LoadMatrix(projMatrix);
//    ctx->MatrixMode(MATERIAL_VIEW);
//    ctx->LoadMatrix(viewMatrix);

    // Draw our model
//    static studiomodel_t model = studiomodel_t::LoadModel(s_modelName);
//    static QAngle ang = {0, 0, 0};
//    static Vector pos = {80, 0, 0};
//    model.Draw(pos, ang);

    // Mouse input
    // If we're dragging a window, we don't want to be dragging our model too
//    if (!io.WantCaptureMouse) {
//        static double ox = 0, oy = 0, x = 0, y = 0;
//        if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_1)) {
//            glfwGetCursorPos(m_pWindow, &x, &y);
//            ang.y += x - ox;
//            ang.x -= y - oy;
//            ox = x;
//            oy = y;
//        } else {
//            glfwGetCursorPos(m_pWindow, &ox, &oy);
//        }
//    }

    // Model Properties
    if (ImGui::Begin("Model")) {
        ImGui::InputText("Path", s_modelName, sizeof(s_modelName));
        ImGui::SameLine();
//        if (ImGui::Button("Apply"))
//            model = studiomodel_t::LoadModel(s_modelName);
//
//        ImGui::InputFloat3("pos", pos.Base());
//        ImGui::SliderFloat3("ang", ang.Base(), -360, 360);
    }
    ImGui::End();

    // End ImGui, and let it draw
    ImGui::Render();
    ImGui_ImplSource_RenderDrawData(ImGui::GetDrawData());

    // End Frame
//    g_pMaterialSystem->SwapBuffers();
//    g_pMaterialSystem->EndFrame();
}
