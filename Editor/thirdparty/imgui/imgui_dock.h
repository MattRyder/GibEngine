// based on https://github.com/nem0/LumixEngine/blob/master/external/imgui/imgui_dock.h
// modified from https://bitbucket.org/duangle/liminal/src/tip/src/liminal/imgui_dock.h

#pragma once

#include "imgui.h"

// Forward declarations
typedef int ImGuiWindowFlags;
    
typedef enum ImGuiDockSlot {
    ImGuiDockSlot_Left,
    ImGuiDockSlot_Right,
    ImGuiDockSlot_Top,
    ImGuiDockSlot_Bottom,
    ImGuiDockSlot_Tab,

    ImGuiDockSlot_Float,
    ImGuiDockSlot_None
} ImGuiDockSlot;

namespace ImGui{

IMGUI_API void BeginDockspace();
IMGUI_API void EndDockspace();
IMGUI_API void ShutdownDock();
IMGUI_API void SetNextDock(ImGuiDockSlot slot);
IMGUI_API bool BeginDock(const char* label, bool* opened = NULL, ImGuiWindowFlags extra_flags = 0);
IMGUI_API void EndDock();
IMGUI_API void SetDockActive();

IMGUI_API bool IsDockDragging();

IMGUI_API void SaveDock();
IMGUI_API void LoadDock(const char* dockConfigurationIniFilename);
IMGUI_API void PushDockBorderColor(ImColor color);
IMGUI_API void PopDockBorderColor();
};