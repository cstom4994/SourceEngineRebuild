#include "cbase.h"

#include <vector>

#include "materialsystem\imaterialsystem.h"
#include "rendertexture.h"
#include "baseclientrendertargets.h"

class CMBRenderTargets : public CBaseClientRenderTargets {
    DECLARE_CLASS_GAMEROOT(CMBRenderTargets, CBaseClientRenderTargets);

public:
    virtual void
    InitClientRenderTargets(IMaterialSystem *pMaterialSystem, IMaterialSystemHardwareConfig *pHardwareConfig) {
        int w = 0, h = 0;
        pMaterialSystem->GetBackBufferDimensions(w, h);

        for (int i = 1; i <= 8; i++) {
            char szRTname[13];
            sprintf(szRTname, "_rt_MBloomL%d", i);

            int power = pow(2, i);

            auto rt = pMaterialSystem->CreateNamedRenderTargetTextureEx2(
                    szRTname, w / power, h / power, RT_SIZE_OFFSCREEN,
                    pMaterialSystem->GetBackBufferFormat(),
                    MATERIAL_RT_DEPTH_SHARED,
                    TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
                    CREATERENDERTARGETFLAGS_HDR
            );

            CTextureReference ref;
            ref.Init(rt);

            m_RenderTextures.push_back(ref);
        }

        BaseClass::InitClientRenderTargets(pMaterialSystem, pHardwareConfig);
    };

    virtual void ShutdownClientRenderTargets() {
        for (auto &rt: m_RenderTextures) {
            rt.Shutdown();
        }

        m_RenderTextures.clear();

        BaseClass::ShutdownClientRenderTargets();
    };

private:
    std::vector<CTextureReference> m_RenderTextures;
};

static CMBRenderTargets g_MBRenderTargets;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CMBRenderTargets, IClientRenderTargets, CLIENTRENDERTARGETS_INTERFACE_VERSION,
                                  g_MBRenderTargets);
CMBRenderTargets *MBRenderTargets = &g_MBRenderTargets;