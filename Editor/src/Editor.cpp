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
			GibEngine::World::Database db(outPath, GetFileSystem(), GetGraphicsApi(), true);

			//this->SetSceneRoot(db.LoadLevel(1));

			dock = std::shared_ptr<Components::Dock>(new Components::Dock(GetFileSystem(), GetGraphicsApi(), GetRootEntity()));
		}
		else if(res != NFD_CANCEL)
		{
			GibEngine::Logger::Instance->error("Error loading World: {}", outPath);
		}
	};

	auto newWorldCallback = [&]() -> void
	{
		std::shared_ptr<GibEngine::BaseEntity> rootEntity = CreateWorld();

		// Generate a plane for the Editor:
		json11::Json planeGenerationData = json11::Json::object
		{
			{ "MeshType", "Plane" },
			{ "Length", 250 },
			{ "Width", 250 },
			{ "IntervalSize", 5 },
			{ "MeshFlags", json11::Json::array{ "RENDER_ENABLED", "RENDER_FORWARD", "RENDER_WIREFRAME", "RENDER_ARRAYS" } }
		};

		//auto plane = std::shared_ptr<GibEngine::Mesh>(GibEngine::MeshService::Generate(graphicsApi, planeGenerationData));
		//rootEntity->AddChild(plane);

		SetSceneRoot(rootEntity);
		menubar->SetRootEntity(rootEntity);
		
		dock = std::shared_ptr<Components::Dock>(new Components::Dock(GetFileSystem(), GetGraphicsApi(), GetRootEntity())); 
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

			//if (db->SaveLevel(this->GetSceneNodeRoot().get()))
			//{
			//	GibEngine::Logger::Instance->info("Saved!");
			//}

			db->Disconnect();
			delete outPath;
			delete db;
		}
	};

	menubar = std::shared_ptr<Components::Menubar>(new Components::Menubar());
	menubar->SetOnExitCallback(exitCallback);
	menubar->SetOnNewWorldCallback(newWorldCallback);
	menubar->SetOnOpenFileDialogCallback(openWorldFileCallback);
	menubar->SetOnSaveFileDialogCallback(saveWorldCallback);
	menubar->SetToggleUiRenderCallback(toggleUiRenderCallback);

	dock = std::shared_ptr<Components::Dock>(new Components::Dock(GetFileSystem(), GetGraphicsApi(), GetRootEntity()));
	statusBar = std::shared_ptr<Components::StatusBar>(new Components::StatusBar());

	newWorldCallback();
}

void GibEditor::Editor::Render()
{    
    Game::Render();

	if (!FlagMask(flags & Flags::DISABLE_UI_RENDER))
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);

		auto framebuffer = GetRenderPipeline()->GetFramebuffer();
		ImGui::SetNextWindowSize(ImVec2(framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight() - ImGui::GetFontSize() * 1.5), ImGuiSetCond_Always);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

		if (ImGui::Begin("MainMenuWindow", (bool*)0, ROOT_PANEL_FLAGS))
		{
			menubar->Render();

			auto textureId = 0U;
			if (GetRenderPipeline() && GetRenderPipeline()->GetFramebuffer() != nullptr)
			{
				//auto ssaoPass = dynamic_cast<GibEngine::Renderer::SsaoPass*>(GetRenderPipeline()->GetRenderPass(GibEngine::Renderer::RenderPass::Type::AMBIENT_OCCLUSION));
				//textureId = ssaoPass->GetFramebuffer()->GetBuffer().textures[0];
				textureId = GetRenderPipeline()->GetFramebuffer()->GetBuffer().textures[GibEngine::Renderer::FramebufferType::NORMAL];
			}
			dock->Render(textureId);

			ImGui::End();
		}

		ImGui::SetNextWindowPos(ImVec2(0, framebuffer->GetBufferHeight() - ImGui::GetFontSize() * 1.5));
		ImGui::SetNextWindowSize(ImVec2(framebuffer->GetBufferWidth(), ImGui::GetFontSize() * 1.5));
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
		ImGui::PopStyleVar();
	}
}

void GibEditor::Editor::Update()
{
   Game::Update();
}

void GibEditor::Editor::SetWindowShouldClose(bool value)
{
	glfwSetWindowShouldClose(GetWindow(), value);
}

std::shared_ptr<GibEditor::Components::Dock> GibEditor::Editor::GetDock() const
{
	return dock;
}
