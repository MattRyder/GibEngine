#pragma once

#include "imgui_dock.h"
#include "nfd.h"
#include "Game.h"
#include "components/Menubar.h"
#include "components/Dock.h"
#include "components/StatusBar.h"

#include "UnixDirectoryChangeObserver.h"
#include "WindowsDirectoryChangeObserver.h"

namespace GibEditor
{
    class Editor : public GibEngine::Game
    {
	public:
		Editor(int argc, char** argv);
		~Editor();

		enum Flags
		{
			DEFAULT = 1 << 0,
			DISABLE_UI_RENDER = 1 << 1,
		};

		virtual void Render() override;
		virtual void Update() override;

		Components::Dock* GetDock() const;

	private:
		Flags flags = Flags::DEFAULT;
		Components::Menubar* menubar;
		Components::Dock* dock;
		Components::StatusBar* statusBar;

		float keydownInterval = 0;
		float deltaDisplayIntervalTimer;
		float lastReadDeltaTime;

		const ImGuiWindowFlags ROOT_PANEL_FLAGS = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

		void SetWindowShouldClose(bool value);

    };
}