#include "components/Dock.h"

GibEditor::Components::Dock::Dock(GibEngine::World::Level* level, GibEngine::Renderer::Pipeline* pipeline) : level(level), pipeline(pipeline)
{
	cbrowser = new Components::ContentBrowser(level, pipeline);
}

void GibEditor::Components::Dock::Render()
{
	ImGui::BeginDockspace();

	if (ImGui::BeginDock("Game"))
	{
		ImVec2 windowSize = ImGui::GetWindowSize();

		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::GAME;
		}

		if (pipeline != nullptr)
		{
			ImGui::Image((void*)pipeline->GetFramebuffer()->GetBuffer().textures[GibEngine::Renderer::FramebufferType::RENDER_TO_TEXTURE], windowSize, ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::EndDock();
	}

	ImGui::SetNextDock(ImGuiDockSlot_Left);

	if (ImGui::BeginDock("Scene Explorer"))
	{
		if (ImGui::IsWindowHovered())
		{
			selectedDock = Dock::Type::SCENE_TREE;
		}

		const int COLUMN_COUNT = 3;
		const char* COLUMN_TITLES[COLUMN_COUNT] = { "Name", "Type", "Instance Count" };

		ImGui::Columns(COLUMN_COUNT);

		for (unsigned int i = 0; i < COLUMN_COUNT; i++)
		{
			ImGui::Text("%s", COLUMN_TITLES[i]);
			ImGui::NextColumn();
		}

		if (level != nullptr)
		{
			for (auto model : level->GetModelEntities())
			{
				auto modelEntity = model->GetEntity();

				bool modelClicked = false;

				if (ImGui::Selectable(modelEntity->GetName()))
				{
					modelClicked = true;
				}
				ImGui::NextColumn();

				if (ImGui::Selectable(modelEntity->GetTypeName()))
				{
					modelClicked = true;
				}
				ImGui::NextColumn();

				if(ImGui::Selectable(std::to_string(modelEntity->GetModelInstances().size()).c_str()))
				{
					modelClicked = true;
				}
				ImGui::NextColumn();

				if (modelClicked)
				{
					delete inspector;
					inspector = new EntityInspector<GibEngine::Model>(model);
				}
			}

			ImGui::Columns(1);
		}

		ImGui::EndDock();

		ImGui::SetNextDock(ImGuiDockSlot_Bottom);

		if (ImGui::BeginDock("ContentExplorer", (bool*)0, ImGuiWindowFlags_MenuBar))
		{
			cbrowser->Render();

			ImGui::EndDock();
		}

		if (inspector != nullptr)
		{
			ImGui::SetNextDock(ImGuiDockSlot_Right);

			if (ImGui::BeginDock("Inspector"))
			{
				if (ImGui::IsWindowHovered())
				{
					selectedDock = Dock::Type::ENTITY_INSPECTOR;
				}

				inspector->Render();
				ImGui::EndDock();
			}
		}
	}

	ImGui::EndDockspace();
}

GibEditor::Components::Dock::Type GibEditor::Components::Dock::GetSelectedDock() const
{
	return selectedDock;
}