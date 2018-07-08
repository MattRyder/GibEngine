#include "components/ContentBrowser.h"

GibEditor::Components::ContentBrowser::ContentBrowser(
	std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem, 
	std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> graphicsApi,
	std::shared_ptr<GibEngine::BaseEntity> rootEntity)
	: fileSystem(fileSystem), graphicsApi(graphicsApi), rootEntity(rootEntity)
{
	defaultGenerationData = json11::Json::object { { "MeshFlags", json11::Json::array{ "RENDER_DEFERRED" } } };
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
					auto mesh = GibEngine::MeshService::Load(graphicsApi, meshFilePath, defaultGenerationData);
					rootEntity->AddChild(mesh);
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
			auto light = std::shared_ptr<GibEngine::PointLight>(new GibEngine::PointLight());
			rootEntity->AddChild(light);
		}

		ImGui::TreePop();
	}

	ImGui::Columns(1);

}