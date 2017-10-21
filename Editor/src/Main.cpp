#include "Main.h"

int main(int argc, char** argv)
{
    GibEditor::Editor *editor = new GibEditor::Editor(argc, argv);

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
       editor->Render();
    }
}