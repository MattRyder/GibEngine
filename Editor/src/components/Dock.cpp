#include "components/Dock.h"

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

		ImGui::Columns(1);

		ImGui::EndDock();
	}

	ImGui::EndDockspace();
}
