#pragma once

#include "imgui_dock.h"
#include "Game.h"
#include "components/Menubar.h"
#include "components/Dock.h"

namespace GibEditor
{
    class Editor : public GibEngine::Game
    {
		Components::Menubar* menubar;
		Components::Dock* dock;

		const ImGuiWindowFlags ROOT_PANEL_FLAGS = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

		void SetWindowShouldClose(bool value);


    public:
       Editor(int argc, char** argv);
       ~Editor();

       virtual void Render() override;
       virtual void Update() override;
    };
}