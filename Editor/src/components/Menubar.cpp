#include "components/Menubar.h"

GibEditor::Components::Menubar::Menubar(GibEngine::World::Level * level)
{
	this->level = level;
}

void GibEditor::Components::Menubar::Render()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New World", "Ctrl + N")) { }
			if (ImGui::MenuItem("Open World", "Ctrl + O")) { this->openFileDialogCallbackFunc(); }
			if (ImGui::MenuItem("Save World", "Ctrl + S")) { }
			if (ImGui::MenuItem("Exit GibEditor", "ESC")) { this->exitCallback(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toggle Wireframe Mode")) { this->toggleWireframeCallbackFunc(level); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void GibEditor::Components::Menubar::SetLevel(GibEngine::World::Level* level)
{
	this->level = level;
}

void GibEditor::Components::Menubar::SetOnExitCallback(const std::function<void()> &exitCallbackFunc)
{
	this->exitCallback = exitCallbackFunc;
}

void GibEditor::Components::Menubar::SetOnOpenFileDialogCallback(const std::function<void()>& openFileDialogCallbackFunc)
{
	this->openFileDialogCallbackFunc = openFileDialogCallbackFunc;
}

void GibEditor::Components::Menubar::SetOnSaveFileDialogCallback(const std::function<void()>& saveFileDialogCallbackFunc)
{
	this->saveFileDialogCallbackFunc = saveFileDialogCallbackFunc;
}

void GibEditor::Components::Menubar::SetToggleWireframeCallback(const std::function<void(GibEngine::World::Level*)>& toggleWireframeCallbackFunc)
{
	this->toggleWireframeCallbackFunc = toggleWireframeCallbackFunc;
}
