#include "components/Menubar.h"

GibEditor::Components::Menubar::Menubar() { }

void GibEditor::Components::Menubar::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem(" New World")) { this->newWorldCallbackFunc(); }
			if (ImGui::MenuItem(" Open World")) { this->openFileDialogCallbackFunc(); }
			if (ImGui::MenuItem(" Save World")) { this->saveFileDialogCallbackFunc(); }
			if (ImGui::MenuItem(" Exit GibEditor")) { this->exitCallback(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toggle UI Rendering")) { this->toggleUiRenderCallbackFunc(); }
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void GibEditor::Components::Menubar::SetRootEntity(std::shared_ptr<GibEngine::BaseEntity> rootEntity)
{
	this->rootEntity = rootEntity;
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
