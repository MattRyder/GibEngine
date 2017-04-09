#include "Main.h"

int main(int argc, char** argv)
{
    GibEditor::Editor *editor = new GibEditor::Editor();

    while (!glfwWindowShouldClose(editor->GetWindow()))
    {
       editor->Render();
    }
}