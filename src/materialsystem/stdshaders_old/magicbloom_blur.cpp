// Magic Bloom Blur Pass

#include "basevsshader.h"
#include "convar.h"

#include "include/SDK_screenspaceeffect_vs30.inc"

#include "include/magicbloom_blur1_ps30.inc"
#include "include/magicbloom_blur2_ps30.inc"

BEGIN_VS_SHADER_FLAGS(magicbloom_blur_1, "First blur pass for Magicbloom", SHADER_NOT_EDITABLE)

    BEGIN_SHADER_PARAMS
    SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "Full framebuffer texture")

    END_SHADER_PARAMS

        SHADER_INIT_PARAMS() {
        }

        SHADER_FALLBACK {
            // This shader should not be *used* unless we're >= DX9  (bloomadd.vmt/screenspace_general_dx8 should be used for DX8)
            return 0;
        }

        SHADER_INIT {
            if (params[FBTEXTURE]->IsDefined()) {
                LoadTexture(FBTEXTURE);
            }
        }

        SHADER_DRAW {
            SHADOW_STATE {
                bool bForceSRGBReadAndWrite = IsOSX() && g_pHardwareConfig->CanDoSRGBReadFromRTs();
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER0, bForceSRGBReadAndWrite);
                pShaderShadow->EnableSRGBWrite(bForceSRGBReadAndWrite);

                pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);

                int format = VERTEX_POSITION;
                int numTexCoords = 1;
                int *pTexCoordDimensions = NULL;
                int userDataSize = 0;
                pShaderShadow->VertexShaderVertexFormat(format, numTexCoords, pTexCoordDimensions, userDataSize);

                DECLARE_STATIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
                SET_STATIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);

                DECLARE_STATIC_PIXEL_SHADER(magicbloom_blur1_ps30);
                SET_STATIC_PIXEL_SHADER(magicbloom_blur1_ps30);
            }
            DYNAMIC_STATE {
                BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);

                int w, h;
                pShaderAPI->GetBackBufferDimensions(w, h);

                float texelSize[2] = {1.0f / float(w), 1.0f / float(h)};

                pShaderAPI->SetPixelShaderConstant(1, texelSize);

                DECLARE_DYNAMIC_PIXEL_SHADER(magicbloom_blur1_ps30);
                SET_DYNAMIC_PIXEL_SHADER(magicbloom_blur1_ps30);

                DECLARE_DYNAMIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
                SET_DYNAMIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
            }
            Draw();
        }
END_SHADER

// ????
BEGIN_VS_SHADER_FLAGS(magicbloom_blur_2, "Other blur passes for Magicbloom", SHADER_NOT_EDITABLE)

    BEGIN_SHADER_PARAMS
    SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL1", "Full framebuffer texture")
    SHADER_PARAM(SCALE, SHADER_PARAM_TYPE_FLOAT, "4", "Blur Scale")

    END_SHADER_PARAMS

        SHADER_INIT_PARAMS() {
        }

        SHADER_FALLBACK {
            // This shader should not be *used* unless we're >= DX9  (bloomadd.vmt/screenspace_general_dx8 should be used for DX8)
            return 0;
        }

        SHADER_INIT {
            if (params[FBTEXTURE]->IsDefined()) {
                LoadTexture(FBTEXTURE);
            }
        }

        SHADER_DRAW {
            SHADOW_STATE {
                bool bForceSRGBReadAndWrite = IsOSX() && g_pHardwareConfig->CanDoSRGBReadFromRTs();
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER0, bForceSRGBReadAndWrite);
                pShaderShadow->EnableSRGBWrite(bForceSRGBReadAndWrite);

                pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);

                int format = VERTEX_POSITION;
                int numTexCoords = 1;
                int *pTexCoordDimensions = NULL;
                int userDataSize = 0;
                pShaderShadow->VertexShaderVertexFormat(format, numTexCoords, pTexCoordDimensions, userDataSize);

                DECLARE_STATIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
                SET_STATIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);

                DECLARE_STATIC_PIXEL_SHADER(magicbloom_blur2_ps30);
                SET_STATIC_PIXEL_SHADER(magicbloom_blur2_ps30);
            }
            DYNAMIC_STATE {
                BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);

                int w, h;
                pShaderAPI->GetBackBufferDimensions(w, h);

                float scale = params[SCALE]->GetFloatValue();
                float texelSize[2] = {1.0f / float(w), 1.0f / float(h)};

                pShaderAPI->SetPixelShaderConstant(0, &scale);
                pShaderAPI->SetPixelShaderConstant(1, texelSize);

                DECLARE_DYNAMIC_PIXEL_SHADER(magicbloom_blur2_ps30);
                SET_DYNAMIC_PIXEL_SHADER(magicbloom_blur2_ps30);

                DECLARE_DYNAMIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
                SET_DYNAMIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
            }
            Draw();
        }
END_SHADER

