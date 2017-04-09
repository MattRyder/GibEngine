#include "Editor.h"

GibEditor::Editor::Editor() : GibEngine::Game("GibEditor")
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
