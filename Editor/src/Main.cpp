#include "Main.h"

int main(int argc, char** argv)
{
	auto editor = std::make_unique<GibEditor::Editor>(argc, argv);
	auto cwd = editor->GetFileSystem()->GetWorkingDirectory();

	auto imguiCtx = ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(editor->GetWindow(), false);
	SetupImGuiStyle(cwd);

	GibEditor::Components::Dock::Type lastSelectedDockType = GibEditor::Components::Dock::Type::GAME;

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
		ImGui_ImplGlfwGL3_NewFrame();

		editor->Render();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(editor->GetWindow());

		if (editor->GetDock() != nullptr)
		{
			// If input focus changes, reload the right input callbacks for the target:
			GibEditor::Components::Dock::Type dockType = editor->GetDock()->GetSelectedDock();
			if (dockType != lastSelectedDockType)
			{
				switch (dockType)
				{
				case GibEditor::Components::Dock::Type::ENTITY_INSPECTOR:
				case GibEditor::Components::Dock::Type::SCENE_TREE:
					ImGui_ImplGlfwGL3_InstallCallbacks(editor->GetWindow());
					break;
				case GibEditor::Components::Dock::Type::GAME:
					editor->GetInputManager()->Install(editor->GetWindow());
					break;
				}

				lastSelectedDockType = dockType;
			}
		}

		editor->Update();
    }

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext(imguiCtx);
}

void SetupImGuiStyle(const std::string& currentWorkingDirectory)
{
	const std::string ttfLocation = currentWorkingDirectory + "\\Assets\\Fonts\\Arimo-Regular.ttf";
	
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF(ttfLocation.c_str(), 24.0f);

	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(0, 0);
	style.WindowRounding = 5;
	style.ItemSpacing = ImVec2(10, 10);
	style.ItemInnerSpacing = ImVec2(8, 4);
	style.ScrollbarSize = 20;
	style.ScrollbarRounding = 0;
	style.IndentSpacing = 30;
	style.TouchExtraPadding = ImVec2(10, 10);
	style.FramePadding = ImVec2(10, 10);

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.18f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.19f, 0.18f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.39f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.13f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.165f, 0.396f, 0.750f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2f, 0.2f, 0.180f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.07f, 0.08f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.32f, 0.32f, 0.32f, 0.25f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.30f, 0.48f, 0.98f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.30f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.48f, 0.48f, 0.55f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.48f, 0.48f, 0.55f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.19f, 0.48f, 0.75f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.15f, 0.31f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.15f, 0.31f, 0.61f, 1.00f);
}