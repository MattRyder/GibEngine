#include "components/Dock.h"

int gameTextureId = 2;

GibEditor::Components::Dock::Dock(GibEngine::World::Level* level, GibEngine::Renderer::Pipeline* pipeline) : level(level), pipeline(pipeline) { }

void GibEditor::Components::Dock::Render()
{
	ImGui::BeginDockspace();

	ImGui::SetNextDock(ImGuiDockSlot_Left);

	if (ImGui::BeginDock("Scene Explorer"))
	{
		const int COLUMN_COUNT = 2;
		const char* COLUMN_TITLES[COLUMN_COUNT] = { "Name", "Type" };

		ImGui::Columns(COLUMN_COUNT);

		for (unsigned int i = 0; i < COLUMN_COUNT; i++)
		{
			ImGui::Text("%s", COLUMN_TITLES[i]);
			ImGui::NextColumn();
		}

		if (level != nullptr)
		{
			for (auto model : level->GetModels())
			{
				ImGui::Text("%s", model->GetName());
				ImGui::NextColumn();
				ImGui::Text("%s", model->GetTypeName());
				ImGui::NextColumn();
			}

			ImGui::Columns(1);
		}

		ImGui::EndDock();
	}

	ImGui::SetNextDock(ImGuiDockSlot_Right);
	if (ImGui::BeginDock("Game")) 
	{
		ImVec2 windowSize = ImGui::GetWindowSize();
		if (pipeline != nullptr)
		{
			ImGui::Image((void*)pipeline->GetFramebuffer()->GetBuffer().textures[GibEngine::Renderer::FramebufferType::ALBEDO], windowSize, ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::EndDock();
	}


	ImGui::EndDockspace();
}
