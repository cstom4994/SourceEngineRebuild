// Magic Bloom Blur Pass

#include "basevsshader.h"
#include "convar.h"

#include "include/SDK_screenspaceeffect_vs30.inc"
#include "include/magicbloom_blend_ps30.inc"

BEGIN_VS_SHADER_FLAGS(magicbloom_blend, "Blend pass for Magicbloom", SHADER_NOT_EDITABLE)

    BEGIN_SHADER_PARAMS
    SHADER_PARAM(FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "Full framebuffer texture")
    SHADER_PARAM(DIRTTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "dev/lensdirt", "Lens dirt Texture")
    SHADER_PARAM(BLOOM_LAYER1, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL1", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER2, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL2", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER3, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL3", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER4, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL4", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER5, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL5", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER6, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL6", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER7, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL7", "Magic Bloom Layers")
    SHADER_PARAM(BLOOM_LAYER8, SHADER_PARAM_TYPE_TEXTURE, "_rt_MBloomL8", "Magic Bloom Layers")

    END_SHADER_PARAMS

        SHADER_INIT_PARAMS() {
            SET_FLAGS2(MATERIAL_VAR2_NEEDS_FULL_FRAME_BUFFER_TEXTURE);
        }

        SHADER_FALLBACK {
            // This shader should not be *used* unless we're >= DX9  (bloomadd.vmt/screenspace_general_dx8 should be used for DX8)
            return 0;
        }

        SHADER_INIT {
            if (params[FBTEXTURE]->IsDefined())
                LoadTexture(FBTEXTURE);

            if (params[DIRTTEXTURE]->IsDefined())
                LoadTexture(DIRTTEXTURE);

            if (params[BLOOM_LAYER1]->IsDefined())
                LoadTexture(BLOOM_LAYER1);
            if (params[BLOOM_LAYER2]->IsDefined())
                LoadTexture(BLOOM_LAYER2);
            if (params[BLOOM_LAYER3]->IsDefined())
                LoadTexture(BLOOM_LAYER3);
            if (params[BLOOM_LAYER4]->IsDefined())
                LoadTexture(BLOOM_LAYER4);
            if (params[BLOOM_LAYER5]->IsDefined())
                LoadTexture(BLOOM_LAYER5);
            if (params[BLOOM_LAYER6]->IsDefined())
                LoadTexture(BLOOM_LAYER6);
            if (params[BLOOM_LAYER7]->IsDefined())
                LoadTexture(BLOOM_LAYER7);
            if (params[BLOOM_LAYER8]->IsDefined())
                LoadTexture(BLOOM_LAYER8);
        }

        SHADER_DRAW {
            SHADOW_STATE {
                pShaderShadow->EnableBlending(false);

                pShaderShadow->EnableTexture(SHADER_SAMPLER0, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER0, false);

                pShaderShadow->EnableTexture(SHADER_SAMPLER1, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER1, false);

                pShaderShadow->EnableTexture(SHADER_SAMPLER2, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER2, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER3, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER3, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER4, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER4, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER5, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER5, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER6, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER6, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER7, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER7, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER8, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER8, false);
                pShaderShadow->EnableTexture(SHADER_SAMPLER9, true);
                pShaderShadow->EnableSRGBRead(SHADER_SAMPLER9, false);

                int format = VERTEX_POSITION;
                int numTexCoords = 1;
                int *pTexCoordDimensions = NULL;
                int userDataSize = 0;
                pShaderShadow->VertexShaderVertexFormat(format, numTexCoords, pTexCoordDimensions, userDataSize);

                DECLARE_STATIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
                SET_STATIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);

                DECLARE_STATIC_PIXEL_SHADER(magicbloom_blend_ps30);
                SET_STATIC_PIXEL_SHADER(magicbloom_blend_ps30);
            }
            DYNAMIC_STATE {
                BindTexture(SHADER_SAMPLER0, FBTEXTURE, -1);
                BindTexture(SHADER_SAMPLER1, DIRTTEXTURE, -1);
                BindTexture(SHADER_SAMPLER2, BLOOM_LAYER1, -1);
                BindTexture(SHADER_SAMPLER3, BLOOM_LAYER2, -1);
                BindTexture(SHADER_SAMPLER4, BLOOM_LAYER3, -1);
                BindTexture(SHADER_SAMPLER5, BLOOM_LAYER4, -1);
                BindTexture(SHADER_SAMPLER6, BLOOM_LAYER5, -1);
                BindTexture(SHADER_SAMPLER7, BLOOM_LAYER6, -1);
                BindTexture(SHADER_SAMPLER8, BLOOM_LAYER7, -1);
                BindTexture(SHADER_SAMPLER9, BLOOM_LAYER8, -1);

                DECLARE_DYNAMIC_PIXEL_SHADER(magicbloom_blend_ps30);
                SET_DYNAMIC_PIXEL_SHADER(magicbloom_blend_ps30);

                DECLARE_DYNAMIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
                SET_DYNAMIC_VERTEX_SHADER(SDK_screenspaceeffect_vs30);
            }
            Draw();
        }
END_SHADER
