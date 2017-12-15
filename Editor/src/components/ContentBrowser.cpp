#include "components/ContentBrowser.h"

GibEditor::Components::ContentBrowser::ContentBrowser(GibEngine::World::Level* level, GibEngine::Renderer::Pipeline* pipeline)
	: level(level), pipeline(pipeline)
{
	SetupAvailableContentMap();
}

GibEditor::Components::ContentBrowser::~ContentBrowser()
{
	delete contentDirectoryObserver;
}

void GibEditor::Components::ContentBrowser::SetupAvailableContentMap()
{
	availableContent.clear();

	availableContent =
	{
		{ GibEngine::EntityType::MODEL, std::vector<GibEngine::File*>() }
	};
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
				nfdresult_t res = NFD_PickFolder(GibEngine::File::GetWorkingDirectory().c_str(), &importPath);

				if (res == NFD_OKAY)
				{
					std::vector<GibEngine::File*> files = GibEngine::File::GetDirectoryList(importPath);

					for (auto file : files)
					{
						// filter out the files into entity types we can load:
						const char* extension = file->GetExtension();

						if (strcmp(extension, "obj") == 0)
						{
							availableContent.at(GibEngine::EntityType::MODEL).push_back(file);
						}

						delete extension;
					}

					free(importPath);
				}

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
	for (auto contentList : availableContent)
	{
		if (ImGui::TreeNode(GibEngine::Entity::GetTypeString(contentList.first)))
		{
			ImGui::Columns(columns, (const char*)0, false);

			for (unsigned int i = 0; i < contentList.second.size(); i++)
			{
				auto contentFile = contentList.second[i];

				if (ImGui::Button(contentFile->GetFilename(), buttonSize))
				{
					auto modelEntity = level->AddModel(contentFile->GetFilename());
					GibEngine::Renderer::RenderPass* pass =
						pipeline->GetRenderPass(GibEngine::Renderer::RenderPassType::DEFERRED_GEOMETRY);
					pass->AddDrawable(modelEntity->GetEntity());

				}

				ImGui::NextColumn();
			}

			ImGui::TreePop();

			ImGui::Columns(1);
		}
	}
}

void GibEditor::Components::ContentBrowser::SetObserver(Observer* observer)
{
	delete this->contentDirectoryObserver;
	this->contentDirectoryObserver = observer;
}