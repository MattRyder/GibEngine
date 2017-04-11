#include "Main.h"

int main(int argc, char** argv)
{
    GibEditor::Editor *editor = new GibEditor::Editor();

    // editor->SetWindowTitle("GibEditor");
    editor->SetWindowSize(1280, 720);

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
       editor->Render();
    }
}