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

	auto toggleWireframeCallback = [&](GibEngine::World::Level* currentLevel) -> void
	{
		for (auto model : currentLevel->GetModels())
		{
			model->SetWireframeMode(true);
		}
	};

	auto toggleUiRenderCallback = [&]() -> void 
	{
		flags = static_cast<Flags>(flags ^ Flags::DISABLE_UI_RENDER);
	};

	auto saveWorldCallback = [&](GibEngine::World::Level* currentLevel) -> void
	{
		nfdchar_t* outPath = nullptr;
		nfdresult_t res = NFD_SaveDialog("gwo", GibEngine::File::GetWorkingDirectory().c_str(), &outPath);

		if (res == NFD_OKAY)
		{
			GibEngine::Logger::Instance->info("Saving World: {}", outPath);
			GibEngine::World::Database* db = new GibEngine::World::Database(outPath);

			if (db->SaveLevel(currentLevel))
			{
				GibEngine::Logger::Instance->info("Saved!");
			}

			db->Disconnect();
			delete outPath;
			delete db;
		}
	};

	menubar = new Components::Menubar(currentLevel);
	menubar->SetOnExitCallback(exitCallback);
	menubar->SetOnOpenFileDialogCallback(openWorldFileCallback);
	menubar->SetOnSaveFileDialogCallback(saveWorldCallback);
	menubar->SetToggleWireframeCallback(toggleWireframeCallback);
	menubar->SetToggleUiRenderCallback(toggleUiRenderCallback);

	dock = new Components::Dock(currentLevel, GetRenderPipeline());

	statusBar = new Components::StatusBar();
}

GibEditor::Editor::~Editor()
{
	delete statusBar;
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

	//statusBar->Render();

	ImGui::End();

	ImGui::Render();
}

void GibEditor::Editor::Update()
{
   Game::Update();

   bool isGameConsumingMouseInput = inputManager->GetMouseButtonState()[GLFW_MOUSE_BUTTON_1]
	   && dock->GetSelectedDock() == Components::Dock::Type::GAME;

   inputManager->SetUpdatingMouseState(isGameConsumingMouseInput);

   if (keydownInterval > 0.05f)
   {
	   if (inputManager->GetKeyboardState()[GLFW_KEY_TAB])
	   {
		   flags = static_cast<Flags>(flags ^ Flags::DISABLE_UI_RENDER);
		   keydownInterval = 0;
	   }
   }
   else
   {
	   keydownInterval += GetDeltaTime();
   }
}

void GibEditor::Editor::SetWindowShouldClose(bool value)
{
	glfwSetWindowShouldClose(GetWindow(), value);
}
