#include "components/Menubar.h"

GibEditor::Components::Menubar::Menubar(GibEngine::World::Level* level)
{
	this->level = level;
}

void GibEditor::Components::Menubar::Render()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New World", "CTRL + N")) { }
			if (ImGui::MenuItem("Open World", "CTRL + O")) { this->openFileDialogCallbackFunc(); }
			if (ImGui::MenuItem("Save World", "CTRL + S")) { this->saveFileDialogCallbackFunc(level); }
			if (ImGui::MenuItem("Exit GibEditor", "ALT + F4")) { this->exitCallback(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toggle Wireframe Mode")) { this->toggleWireframeCallbackFunc(level); }
			if (ImGui::MenuItem("Toggle UI Rendering")) { this->toggleUiRenderCallbackFunc(); }
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

void GibEditor::Components::Menubar::SetOnSaveFileDialogCallback(const std::function<void(GibEngine::World::Level*)>& saveFileDialogCallbackFunc)
{
	this->saveFileDialogCallbackFunc = saveFileDialogCallbackFunc;
}

void GibEditor::Components::Menubar::SetToggleWireframeCallback(const std::function<void(GibEngine::World::Level*)>& toggleWireframeCallbackFunc)
{
	this->toggleWireframeCallbackFunc = toggleWireframeCallbackFunc;
}

void GibEditor::Components::Menubar::SetToggleUiRenderCallback(const std::function<void()>& toggleUiRenderCallbackFunc)
{
	this->toggleUiRenderCallbackFunc = toggleUiRenderCallbackFunc;
}
