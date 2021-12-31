
#include "imgui_impl_source.h"
#include "materialsystem/imesh.h"
#include "materialsystem/itexture.h"
#include "keyvalues.h"
#include "imgui.h"

static IVertexBuffer *g_pVB;
static IIndexBuffer *g_pIB;
static unsigned int g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;
static IMaterial *g_FontMat;

void ImGui_ImplSource_SetupRenderState(IMatRenderContext *ctx, ImDrawData *draw_data) {
    // Setup orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    ctx->MatrixMode(MATERIAL_PROJECTION);
    ctx->PushMatrix();
    ctx->LoadIdentity();

    float L = draw_data->DisplayPos.x + 0.5f;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x + 0.5f;
    float T = draw_data->DisplayPos.y + 0.5f;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y + 0.5f;
    ctx->Ortho(L, B, R, T, 0, 1800);
    g_pMaterialSystem->GetRenderContext()->MatrixMode(MATERIAL_VIEW);
    g_pMaterialSystem->GetRenderContext()->PushMatrix();
    g_pMaterialSystem->GetRenderContext()->LoadIdentity();
}

void SizeUpBufs(IMatRenderContext *ctx, unsigned int vtxCount, unsigned int idxCount) {
    // Create and grow buffers if needed
    if (!g_pVB || g_VertexBufferSize < vtxCount) {
        if (g_pVB) {
            ctx->DestroyVertexBuffer(g_pVB);
            g_pVB = NULL;
        }
        g_VertexBufferSize = vtxCount + 1000;
        g_pVB = ctx->CreateStaticVertexBuffer(VERTEX_POSITION | VERTEX_COLOR | VERTEX_TEXCOORD_SIZE(0, 2),
                                              g_VertexBufferSize, TEXTURE_GROUP_OTHER);
        if (!g_pVB)
            return;
    }
    if (!g_pIB || g_IndexBufferSize < idxCount) {
        if (g_pIB) {
            ctx->DestroyIndexBuffer(g_pIB);
            g_pIB = NULL;
        }
        g_IndexBufferSize = idxCount + 5000;
        g_pIB = ctx->CreateStaticIndexBuffer(MATERIAL_INDEX_FORMAT_16BIT, g_IndexBufferSize, TEXTURE_GROUP_OTHER);
        if (!g_pIB)
            return;
    }
}

// Render function.
////
// NOTICE:
// I despise this.
// Source refueses to let me set the position of the starting vertex, and I really do not want to allocate numerous VBOs
// Why are we even using static VBOs? Because using dynamics just crashes the whole thing. Why? Not sure!
// Could just cheese it with 32 bit indicies and then keep the offset correct, but index builder only allows shorts.
// SO we're just writing to the same vbo, over and over and over
// This could be nicer. This could be cleaner. This could have taken less time to debug.
// But, sometimes you have to compromise, right?
// If you know how to make this better, please do so
////
void ImGui_ImplSource_RenderDrawData(ImDrawData *draw_data) {
    // Avoid rendering when minimized
    if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
        return;

    IMatRenderContext *ctx = materials->GetRenderContext();

    ImGui_ImplSource_SetupRenderState(ctx, draw_data);

    // Render command lists
    // (Because we merged all buffers into a single one, we maintain our own offset into them)
    ImVec2 clip_off = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++) {

        const ImDrawList *cmd_list = draw_data->CmdLists[n];

        // Create the mesh
        SizeUpBufs(ctx, cmd_list->VtxBuffer.Size, cmd_list->IdxBuffer.Size);
        CVertexBuilder vtxBd;
        CIndexBuilder idxBd;

        vtxBd.Begin(g_pVB, cmd_list->VtxBuffer.Size);
        idxBd.Begin(g_pIB, cmd_list->IdxBuffer.Size, 0);

        const ImDrawVert *vtx_src = cmd_list->VtxBuffer.Data;
        for (int i = 0; i < cmd_list->VtxBuffer.Size; i++) {
            vtxBd.Position3f(vtx_src->pos.x, vtx_src->pos.y, 0);
            //vtxBd.Color4ub((vtx_src->col & 0xFF), (vtx_src->col >> 8 & 0xFF), (vtx_src->col >> 16 & 0xFF), (vtx_src->col >> 24 & 0xFF));
            vtxBd.Color4ubv(reinterpret_cast<const unsigned char *>(&vtx_src->col));
            vtxBd.TexCoord2f(0, vtx_src->uv.x, vtx_src->uv.y);
            vtxBd.AdvanceVertex();
            vtx_src++;
        }
        idxBd.FastIndexList(cmd_list->IdxBuffer.Data, 0, cmd_list->IdxBuffer.Size);

        vtxBd.End();
        idxBd.End();


        // Draw the mesh
        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
            const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != NULL) {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_ImplSource_SetupRenderState(ctx, draw_data);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            } else {
                if (pcmd->GetTexID()) {
                    ctx->SetScissorRect(pcmd->ClipRect.x - clip_off.x, pcmd->ClipRect.y - clip_off.y,
                                        pcmd->ClipRect.z - clip_off.x, pcmd->ClipRect.w - clip_off.y, true);
                    ctx->Bind(pcmd->GetTexID());
                    ctx->BindVertexBuffer(0, g_pVB, 0, pcmd->VtxOffset, cmd_list->VtxBuffer.Size,
                                          g_pVB->GetVertexFormat());
                    ctx->BindIndexBuffer(g_pIB, 0);
                    ctx->Draw(MATERIAL_TRIANGLES, pcmd->IdxOffset, pcmd->ElemCount);
                    ctx->SetScissorRect(-1, -1, -1, -1, false);
                }
            }
        }

    }
}

bool ImGui_ImplSource_Init() {
    // Setup backend capabilities flags
    ImGuiIO &io = ImGui::GetIO();
    io.BackendRendererName = "imgui_impl_source";
    io.BackendFlags = ImGuiBackendFlags_None;

    ImGui_ImplSource_CreateDeviceObjects();
    return true;
}

void ImGui_ImplSource_Shutdown() {
    ImGui_ImplSource_InvalidateDeviceObjects();
}

static bool ImGui_ImplSource_CreateFontsTexture() {
    if (g_FontMat)
        return true;

    // Build texture atlas
    ImGuiIO &io = ImGui::GetIO();
    unsigned char *pixels;
    int width, height, bytes_per_pixel;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytes_per_pixel);

    materials->CreateNamedTextureFromBitsEx("imgui_font", TEXTURE_GROUP_VGUI, width, height, 1, IMAGE_FORMAT_RGBA8888,
                                            width * height * bytes_per_pixel, pixels,
                                            TEXTUREFLAGS_NOMIP | TEXTUREFLAGS_IGNORE_PICMIP | TEXTUREFLAGS_POINTSAMPLE);
    KeyValues *vmt = new KeyValues("UnlitGeneric");
    vmt->SetString("$basetexture", "imgui_font");
    vmt->SetInt("$nocull", 1);
    vmt->SetInt("$vertexcolor", 1);
    vmt->SetInt("$alphatest", 1);
    g_FontMat = materials->CreateMaterial("imgui_font_mat", vmt);
    // Store our identifier
    io.Fonts->SetTexID(g_FontMat);

    return true;
}

bool ImGui_ImplSource_CreateDeviceObjects() {
    if (!ImGui_ImplSource_CreateFontsTexture())
        return false;
    return true;
}

void ImGui_ImplSource_InvalidateDeviceObjects() {
    IMatRenderContext *ctx = materials->GetRenderContext();

    if (g_pVB) {
        ctx->DestroyVertexBuffer(g_pVB);
        g_pVB = NULL;
    }
    if (g_pIB) {
        ctx->DestroyIndexBuffer(g_pIB);
        g_pIB = NULL;
    }
    if (g_FontMat) g_FontMat->DecrementReferenceCount();
}
