#pragma once

struct ImDrawData;

bool ImGui_ImplSource_Init();

void ImGui_ImplSource_Shutdown();

void ImGui_ImplSource_RenderDrawData(ImDrawData *draw_data);

// Use if you want to reset your rendering device without losing Dear ImGui state.
bool ImGui_ImplSource_CreateDeviceObjects();

void ImGui_ImplSource_InvalidateDeviceObjects();
