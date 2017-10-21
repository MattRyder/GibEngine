#include "Main.h"

bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(1.00f, 0.0f, 0.0f, 1.00f);

int main(int argc, char** argv)
{    
    GibEditor::Editor *editor = new GibEditor::Editor(argc, argv);

    ImGui_ImplGlfwGL3_Init(editor->GetWindow(), false);

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
        ImGui_ImplGlfwGL3_NewFrame();

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //editor->Render();
        
        if(ImGui::Begin("Whoooo")) {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
        
    //    int display_w, display_h;
    //    glfwGetFramebufferSize(editor->GetWindow(), &display_w, &display_h);
    //    glViewport(0, 0, display_w, display_h);
    
        ImGui::Render();
    }
}