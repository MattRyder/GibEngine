#include "Main.h"

bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int main(int argc, char** argv)
{    
    GibEditor::Editor *editor = new GibEditor::Editor(argc, argv);

    ImGui_ImplGlfwGL3_Init(editor->GetWindow(), true);
	SetupImGuiStyle();

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
		ImGui_ImplGlfwGL3_NewFrame();

		editor->Render();

		ImGui::Render();

		glfwSwapBuffers(editor->GetWindow());

		editor->Update();
    }

	delete editor;
}

void SetupImGuiStyle()
{
	ImGuiIO &io = ImGui::GetIO();

	GibEngine::File *uiFontFile = GibEngine::File::GetFontFile("Arimo-Regular.ttf");
	io.Fonts->AddFontFromFileTTF(uiFontFile->GetPath(), 22.0f);

	ImGui::GetStyle().WindowPadding = ImVec2(0, 0);
	ImGui::GetStyle().WindowRounding = 0;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.18f, 0.20f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.19f, 0.18f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.39f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.13f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.08f, 0.09f, 0.85f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.07f, 0.08f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.32f, 0.32f, 0.32f, 0.25f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.30f, 0.48f, 0.98f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.30f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.15f, 0.31f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.15f, 0.31f, 0.61f, 1.00f);

}