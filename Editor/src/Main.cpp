#include "Main.h"

int main(int argc, char** argv)
{
    GibEditor::Editor *editor = new GibEditor::Editor();

    editor->SetWindowTitle("GibEditor");

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
       editor->Render();
    }
}