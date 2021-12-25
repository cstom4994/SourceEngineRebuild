#pragma once

struct GLFWwindow;

class ITexture;

class Vector;

// I would just merge this into CSteamAppLoader, but it makes such a mess
class CImGuiSourceApp {
public:
    void Init();

    void Destroy();

private:
    void DrawFrame();

    GLFWwindow *m_pWindow;
    ITexture *m_pWhiteTexture;

    float m_lastFrameTime;

    Vector *m_ambientLightColors;
};