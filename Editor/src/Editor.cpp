#include "Editor.h"


GibEditor::Editor::Editor(int argc, char** argv) 
	: GibEngine::Game(argc, argv), deltaDisplayIntervalTimer(0), lastReadDeltaTime(0)
{
	std::function<void()> exitCallback = [&]() -> void { glfwSetWindowShouldClose(GetWindow(), true); };
	auto openWorldFileCallback = [&]() -> void
	{
		nfdchar_t* outPath = nullptr;
		nfdresult_t res = NFD_OpenDialog("gwo", GetFileSystem()->GetWorkingDirectory().c_str(), &outPath);

		if (res == NFD_OKAY)
		{
			GibEngine::Logger::Instance->info("Loading World: {}", outPath);
			GibEngine::World::Database* db = new GibEngine::World::Database(outPath, fileSystem, GetGraphicsApi(), true);

			this->rootSceneNode = std::shared_ptr<GibEngine::Scene::Node>(db->LoadLevel(1));

			dock = new Components::Dock(this->GetFileSystem(), this->rootSceneNode, this->GetRenderPipeline());

			db->Disconnect();
			delete db;
		}
		else if(res != NFD_CANCEL)
		{
			GibEngine::Logger::Instance->error("Error loading World: {}", outPath);
		}
	};

	auto newWorldCallback = [&]() -> void
	{
		std::shared_ptr<GibEngine::Scene::Node> rootNode = CreateWorld();

		// Generate a plane for the Editor:
		json11::Json planeGenerationData = json11::Json::object
		{
			{ "MeshType", "Plane" },
			{ "Length", 250 },
			{ "Width", 250 },
			{ "IntervalSize", 5 },
			{ "MeshFlags", json11::Json::array{ "RENDER_ENABLED", "RENDER_FORWARD", "RENDER_WIREFRAME", "RENDER_ARRAYS" } }
		};


		auto node = new GibEngine::Scene::Node("Plane");
		node->SetEntity(GibEngine::MeshService::Generate(graphicsApi, planeGenerationData));

		node->SetNodeState(GibEngine::World::DatabaseRecord::State::NEW);
		node->SetEntityState(GibEngine::World::DatabaseRecord::State::NEW);
		rootNode->AddChildNode(node);

		SetSceneRoot(rootNode);
		menubar->SetSceneNode(rootNode);
		
		delete dock;
		dock = new Components::Dock(this->GetFileSystem(), rootNode, this->GetRenderPipeline());
	};

	auto toggleUiRenderCallback = [&]() -> void 
	{
		flags = static_cast<Flags>(flags ^ Flags::DISABLE_UI_RENDER);
	};

	auto saveWorldCallback = [&]() -> void
	{
		nfdchar_t* outPath = nullptr;
		nfdresult_t res = NFD_SaveDialog("gwo", GetFileSystem()->GetWorkingDirectory().c_str(), &outPath);

		if (res == NFD_OKAY)
		{
			GibEngine::Logger::Instance->info("Saving World: {}", outPath);
			GibEngine::World::Database* db = new GibEngine::World::Database(outPath, this->GetFileSystem(), this->GetGraphicsApi());

			if (db->SaveLevel(this->GetSceneNodeRoot().get()))
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
	menubar->SetOnNewWorldCallback(newWorldCallback);
	menubar->SetOnOpenFileDialogCallback(openWorldFileCallback);
	menubar->SetOnSaveFileDialogCallback(saveWorldCallback);
	menubar->SetToggleUiRenderCallback(toggleUiRenderCallback);

	dock = new Components::Dock(this->GetFileSystem(), rootSceneNode, GetRenderPipeline());

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

	if (!FlagMask(flags & Flags::DISABLE_UI_RENDER))
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);

		auto framebuffer = GetRenderPipeline()->GetFramebuffer();
		ImGui::SetNextWindowSize(ImVec2(framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight() - ImGui::GetFontSize() * 2), ImGuiSetCond_Always);

		if (ImGui::Begin("MainMenuWindow", (bool*)0, ROOT_PANEL_FLAGS))
		{
			menubar->Render();
			dock->Render();

			ImGui::End();
		}

		auto padding = ImGui::GetStyle().WindowPadding;
		ImGui::SetNextWindowPos(ImVec2(0, framebuffer->GetBufferHeight() - ImGui::GetFontSize() * 2));
		ImGui::SetNextWindowSize(ImVec2(framebuffer->GetBufferWidth(), ImGui::GetFontSize() * 2));
		if (ImGui::Begin("StatusBarWindow", 0, ROOT_PANEL_FLAGS))
		{
			if (ImGui::BeginMenuBar())
			{
				if (deltaDisplayIntervalTimer > 0.5f)
				{
					lastReadDeltaTime = GetDeltaTime();
					deltaDisplayIntervalTimer = 0;
				}
				else
				{
					deltaDisplayIntervalTimer += GetDeltaTime();
				}

				ImGui::Text("Frame Render: %.5fms (%i FPS)", lastReadDeltaTime, GetFramesPerSecond());
				ImGui::SameLine();

				ImVec4 vsyncColor = (config.vsyncEnabled) ? ImVec4(0.305, 0.949, 0.250, 1.0) : ImVec4(0.949, 0.250, 0.368, 1.0);
				ImGui::TextColored(vsyncColor, "VSYNC");

				ImGui::EndMenuBar();
			}
			ImGui::End();

		}

		//if (ImGui::Begin("Style Editor"))
		//{
		//	ImGui::ShowStyleEditor(&ImGui::GetStyle());
		//	ImGui::End();
		//}

	}

	ImGui::Render();
}

void GibEditor::Editor::Update()
{
   Game::Update();

   bool isGameConsumingMouseInput = inputManager->GetMouseButtonState()[GLFW_MOUSE_BUTTON_1]
	   && dock->GetSelectedDock() == Components::Dock::Type::GAME;

   inputManager->SetUpdatingMouseState(isGameConsumingMouseInput);

   if (keydownInterval > 0.5f)
   {
	   if (inputManager->GetKeyboardState()[GLFW_KEY_TAB])
	   {
		   flags = static_cast<Flags>(flags ^ Flags::DISABLE_UI_RENDER);
		   keydownInterval = 0;
	   }

	   if (inputManager->GetKeyboardState()[GLFW_KEY_V])
	   {
		   ToggleVsync();
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

GibEditor::Components::Dock* GibEditor::Editor::GetDock() const
{
	return dock;
}
