#include "components/Menubar.h"

GibEditor::Components::Menubar::Menubar(std::shared_ptr<GibEngine::Scene::Node> node) : rootSceneNode(node) { }

void GibEditor::Components::Menubar::Render()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New World", "CTRL + N")) { this->newWorldCallbackFunc(); }
			if (ImGui::MenuItem("Open World", "CTRL + O")) { this->openFileDialogCallbackFunc(); }
			if (ImGui::MenuItem("Save World", "CTRL + S")) { this->saveFileDialogCallbackFunc(); }
			if (ImGui::MenuItem("Exit GibEditor", "ALT + F4")) { this->exitCallback(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toggle UI Rendering")) { this->toggleUiRenderCallbackFunc(); }
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void GibEditor::Components::Menubar::SetSceneNode(std::shared_ptr<GibEngine::Scene::Node> node)
{
	rootSceneNode = node;
}

void GibEditor::Components::Menubar::SetOnNewWorldCallback(const std::function<void()>& newWorldCallbackFunc)
{
	this->newWorldCallbackFunc = newWorldCallbackFunc;
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

void GibEditor::Components::Menubar::SetToggleUiRenderCallback(const std::function<void()>& toggleUiRenderCallbackFunc)
{
	this->toggleUiRenderCallbackFunc = toggleUiRenderCallbackFunc;
}
