#include "world/Level.h"

GibEngine::World::Level::Level(int id, const char* name) : DatabaseEntity(id)
{
    this->name = name;

    this->models = std::vector<GibEngine::Model*>();
}

GibEngine::World::Level::~Level()
{
	for (auto model : models)
	{
		delete model;
	}

	delete name;
	delete skybox;
}

void GibEngine::World::Level::SetSkybox(GibEngine::Skybox* skybox)
{
    this->skybox = skybox;
}

void GibEngine::World::Level::AddModel(GibEngine::Model* model)
{
    this->models.push_back(model);
}

int GibEngine::World::Level::GetId()
{
    return this->id;
}

const char* GibEngine::World::Level::GetName()
{
    return this->name;
}

GibEngine::Skybox* GibEngine::World::Level::GetSkybox()
{
    return this->skybox;
}

std::vector<GibEngine::Model*> GibEngine::World::Level::GetModels()
{
    return this->models;
}