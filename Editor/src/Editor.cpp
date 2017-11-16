#include "Editor.h"


GibEditor::Editor::Editor(int argc, char** argv) : GibEngine::Game(argc, argv)
{
	std::function<void()> exitCallback = [&]() -> void { glfwSetWindowShouldClose(GetWindow(), true); };
	auto openWorldFileCallback = [&]() -> void
	{
		nfdchar_t* outPath = nullptr;
		nfdresult_t res = NFD_OpenDialog("gwo", GibEngine::File::GetWorkingDirectory().c_str(), &outPath);

		if (res == NFD_OKAY)
		{
			GibEngine::Logger::Instance->info("Loading World: {}", outPath);
			GibEngine::World::Database* db = new GibEngine::World::Database(outPath);

			GibEngine::World::Level* level = db->FindLevel(1);
			this->LoadLevel(level);

			dock = new Components::Dock(level, this->GetRenderPipeline());

			db->Disconnect();
			delete db;
		}
		else if(res != NFD_CANCEL)
		{
			GibEngine::Logger::Instance->error("Error loading World: {}", outPath);
		}
	};

	menubar = new Components::Menubar();
	menubar->SetOnExitCallback(exitCallback);
	menubar->SetOnOpenFileDialogCallback(openWorldFileCallback);

	dock = new Components::Dock(nullptr, nullptr);
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
}

void GibEditor::Editor::Update()
{
   Game::Update();
}

void GibEditor::Editor::SetWindowShouldClose(bool value)
{
	glfwSetWindowShouldClose(GetWindow(), value);
}
