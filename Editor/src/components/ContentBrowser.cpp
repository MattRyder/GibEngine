#include "components/ContentBrowser.h"

GibEditor::Components::ContentBrowser::ContentBrowser(std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem, std::shared_ptr<GibEngine::Scene::Node> rootSceneNode, std::shared_ptr<GibEngine::Renderer::Pipeline> pipeline)
	: rootSceneNode(rootSceneNode), pipeline(pipeline), fileSystem(fileSystem)
{
	defaultGenerationData = json11::Json::object { { "MeshFlags", json11::Json::array{ "RENDER_DEFERRED" } } };
}

GibEditor::Components::ContentBrowser::~ContentBrowser()
{
	delete contentDirectoryObserver;
}

void GibEditor::Components::ContentBrowser::Render()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Import Directory"))
			{
				nfdchar_t* importPath = nullptr;
				nfdresult_t res = NFD_PickFolder(fileSystem->GetWorkingDirectory().c_str(), &importPath);

				if (res == NFD_OKAY)
				{
					meshFileList = fileSystem->GetFileList(importPath, ".obj", true);
				}

				delete(importPath);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	float windowWidth = ImGui::GetWindowWidth();
	int columns = 3;

	if (windowWidth > 350 && windowWidth < 600)
	{
		columns = 2;
	}
	else if (windowWidth < 350)
	{
		columns = 1;
	}

	ImVec2 buttonSize = ImVec2(windowWidth / columns - 10.0f, 45.0f);
	if (ImGui::TreeNode("Mesh"))
	{
		ImGui::Columns(columns, (const char*)0, false);
		

		for (auto meshFilePath : meshFileList)
		{
			auto idx = meshFilePath.find_last_of("/");
			if (idx != meshFilePath.npos)
			{
				auto displayName = meshFilePath.substr(idx + 1, meshFilePath.size() - idx);

				if (ImGui::Button(displayName.c_str(), buttonSize))
				{
					//GibEngine::Scene::Node* meshNode = GibEngine::MeshService::Load(meshFilePath, defaultGenerationData);
					//meshNode->SetEntityState(GibEngine::World::DatabaseRecord::State::NEW);
					//meshNode->SetNodeState(GibEngine::World::DatabaseRecord::State::NEW);
					//rootSceneNode->AddChildNode(meshNode);
				}
			}


			ImGui::NextColumn();
		}
		

		ImGui::Columns(1);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Lighting"))
	{
		ImGui::Columns(columns, (const char*)0, false);

		if (ImGui::Button("Point Light", buttonSize))
		{
			GibEngine::PointLight* light = new GibEngine::PointLight();
			GibEngine::Scene::Node* lightNode = new GibEngine::Scene::Node("New Point Light");
			lightNode->SetEntity(light);
			lightNode->SetEntityState(GibEngine::World::DatabaseRecord::State::NEW);

			//GibEngine::MeshService::AttachVisibleSphere(lightNode);

			rootSceneNode->AddChildNode(lightNode);
		}

		ImGui::TreePop();
	}

	ImGui::Columns(1);

}

void GibEditor::Components::ContentBrowser::SetObserver(Observer* observer)
{
	delete this->contentDirectoryObserver;
	this->contentDirectoryObserver = observer;
}