#pragma once

#include "Game.h"

namespace GibEditor
{
    class Editor : public GibEngine::Game
    {
    public:
       Editor(int argc, char** argv);
       ~Editor();

       virtual void Render() override;
       virtual void Update() override;
    };
}