#include "Editor.h"


GibEditor::Editor::Editor(int argc, char** argv) 
	: GibEngine::Game(argc, argv), deltaDisplayIntervalTimer(0), lastReadDeltaTime(0)
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

			this->rootSceneNode = db->LoadLevel(1);

			dock = new Components::Dock(this->rootSceneNode, this->GetRenderPipeline());

			db->Disconnect();
			delete db;
		}
		else if(res != NFD_CANCEL)
		{
			GibEngine::Logger::Instance->error("Error loading World: {}", outPath);
		}
	};

	auto toggleUiRenderCallback = [&]() -> void 
	{
		flags = static_cast<Flags>(flags ^ Flags::DISABLE_UI_RENDER);
	};

	auto saveWorldCallback = [&](GibEngine::Scene::Node* node) -> void
	{
		nfdchar_t* outPath = nullptr;
		nfdresult_t res = NFD_SaveDialog("gwo", GibEngine::File::GetWorkingDirectory().c_str(), &outPath);

		if (res == NFD_OKAY)
		{
			GibEngine::Logger::Instance->info("Saving World: {}", outPath);
			GibEngine::World::Database* db = new GibEngine::World::Database(outPath);

			if (db->SaveLevel(node))
			{
				GibEngine::Logger::Instance->info("Saved!");
			}

			db->Disconnect();
			delete outPath;
			delete db;
		}
	};

	menubar = new Components::Menubar(rootSceneNode);
	menubar->SetOnExitCallback(exitCallback);
	menubar->SetOnOpenFileDialogCallback(openWorldFileCallback);
	menubar->SetOnSaveFileDialogCallback(saveWorldCallback);
	menubar->SetToggleUiRenderCallback(toggleUiRenderCallback);

	dock = new Components::Dock(rootSceneNode, GetRenderPipeline());

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

	auto framebuffer = GetRenderPipeline()->GetFramebuffer();
	ImGui::SetNextWindowSize(ImVec2(framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight() - ImGui::GetTextLineHeightWithSpacing()), ImGuiSetCond_Always);

	if (ImGui::Begin("MainMenuWindow", (bool*)0, ROOT_PANEL_FLAGS))
	{
		menubar->Render();
		dock->Render();
		ImGui::End();

	}


	ImGui::SetNextWindowPos(ImVec2(0, framebuffer->GetBufferHeight() - ImGui::GetTextLineHeightWithSpacing()));
	ImGui::SetNextWindowSize(ImVec2(framebuffer->GetBufferWidth(), ImGui::GetTextLineHeightWithSpacing()));
	if (ImGui::Begin("StatusBarWindow", 0, ROOT_PANEL_FLAGS))
	{
		if (ImGui::BeginMenuBar())
		{
			if (deltaDisplayIntervalTimer > 1.0f)
			{
				lastReadDeltaTime = GetDeltaTime();
				deltaDisplayIntervalTimer = 0;
			}
			else
			{
				deltaDisplayIntervalTimer += GetDeltaTime();
			}

			ImGui::Text("Frame Render: %.5fms (%i FPS)", lastReadDeltaTime, GetFramesPerSecond());

			ImGui::EndMenuBar();
		}
		ImGui::End();

	}


	//if (ImGui::Begin("Style Editor"))
	//{
	//	ImGui::ShowStyleEditor(&ImGui::GetStyle());
	//	ImGui::End();
	//}

	//statusBar->Render();

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

	   if (inputManager->GetKeyboardState()[GLFW_KEY_V])
	   {
		   ToggleVsync();
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

GibEditor::Components::Dock* GibEditor::Editor::GetDock() const
{
	return dock;
}
