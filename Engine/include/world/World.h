#pragma once

#include <vector>

#include "Level.h"

namespace GibEngine
{
    namespace World
    {
        class World
        {
            std::vector<Level>* levels;

        public:
            World();
            ~World();
        };
    }
}