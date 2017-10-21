#include "Editor.h"

GibEditor::Editor::Editor(int argc, char** argv) : GibEngine::Game(argc, argv)
{
}

GibEditor::Editor::~Editor()
{
}

void GibEditor::Editor::Render()
{    
    Game::Render();
    
    this->Update();
}

void GibEditor::Editor::Update()
{
   Game::Update();
}
