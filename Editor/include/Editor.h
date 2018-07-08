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

		enum Flags
		{
			DEFAULT = 1 << 0,
			DISABLE_UI_RENDER = 1 << 1,
		};

		virtual void Render() override;
		virtual void Update() override;

		std::shared_ptr<Components::Dock> GetDock() const;

		static bool FlagMask(Flags x) { return static_cast<char>(x) != 0; };

	private:
		Flags flags = Flags::DEFAULT;
		std::shared_ptr<Components::Menubar> menubar;
		std::shared_ptr<Components::StatusBar> statusBar;
		std::shared_ptr<Components::Dock> dock;

		float keydownInterval = 0;
		float deltaDisplayIntervalTimer;
		float lastReadDeltaTime;

		const ImGuiWindowFlags ROOT_PANEL_FLAGS = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

		void SetWindowShouldClose(bool value);
    };

	GIB_FLAGS(Editor::Flags)
}