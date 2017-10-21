#include "Editor.h"


GibEditor::Editor::Editor(int argc, char** argv) : GibEngine::Game(argc, argv)
{
	std::function<void()> exitCallback = [&]() -> void { glfwSetWindowShouldClose(GetWindow(), true); };
	std::function<void()> openWorldFileCallback = [&]() -> void
	{
		nfdchar_t* outPath = nullptr;
		nfdresult_t res = NFD_OpenDialog("gwo", GibEngine::File::GetWorkingDirectory().c_str(), &outPath);

		if (res == NFD_OKAY)
		{
			std::cout << "Success!" << std::endl;
		}
		else if(res != NFD_CANCEL)
		{
			std::cout << "Error: " << std::endl;
		}
	};

	menubar = new Components::Menubar();
	menubar->SetOnExitCallback(exitCallback);
	menubar->SetOnOpenFileDialogCallback(openWorldFileCallback);

	dock = new Components::Dock();
}

GibEditor::Editor::~Editor()
{
	delete menubar;
	delete dock;
}

void GibEditor::Editor::Render()
{    
    Game::Render();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), ImGuiSetCond_Always);

	if (ImGui::Begin("", (bool*)0, ROOT_PANEL_FLAGS))
	{
		menubar->Render();
	}

	dock->Render();

	ImGui::End();
    
    this->Update();
}

void GibEditor::Editor::Update()
{
   Game::Update();
}

void GibEditor::Editor::SetWindowShouldClose(bool value)
{
	glfwSetWindowShouldClose(GetWindow(), value);
}
