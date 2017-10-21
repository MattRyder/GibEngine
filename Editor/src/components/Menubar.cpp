#include "components/Menubar.h"

void GibEditor::Components::Menubar::Render()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New World", "Ctrl + N")) { }
			if (ImGui::MenuItem("Open World", "Ctrl + O")) { }
			if (ImGui::MenuItem("Save World", "Ctrl + S")) { }
			if (ImGui::MenuItem("Exit GibEditor", "ESC")) { this->exitCallback(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void GibEditor::Components::Menubar::SetOnExitCallback(const std::function<void()> &exitCallbackFunc)
{
	this->exitCallback = exitCallbackFunc;
}