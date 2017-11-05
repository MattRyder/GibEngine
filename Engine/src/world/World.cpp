#include "world/World.h"

GibEngine::World::World::World()
{
    this->levels = new std::vector<Level>();
}

GibEngine::World::World::~World()
{
    delete this->levels;
}