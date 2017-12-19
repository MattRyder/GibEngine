#include "world/Level.h"

GibEngine::World::Level::Level(int id, const char* name) : DatabaseEntity(id), name(name)
{
	this->skybox = new DatabaseEntity<Skybox>(0);
}

GibEngine::World::Level::~Level()
{
	for (auto modelEntity : modelEntities)
	{
		delete modelEntity->GetEntity();
		delete modelEntity;
	}

	delete skybox->GetEntity();
	delete skybox;
}

void GibEngine::World::Level::SetSkybox(DatabaseEntity<GibEngine::Skybox>* skybox)
{
	if (this->skybox->GetEntity() != nullptr)
	{
		delete this->skybox->GetEntity();
	}
	delete this->skybox;

	this->skybox = skybox;
}

void GibEngine::World::Level::AddModel(GibEngine::World::DatabaseEntity<GibEngine::Model>* model)
{
    this->modelEntities.push_back(model);
}

void GibEngine::World::Level::AddLight(DatabaseEntity<GibEngine::PointLight>* light)
{
	this->pointLightEntities.push_back(light);
}

int GibEngine::World::Level::GetId()
{
	return DatabaseEntity::GetId();
}

const char* GibEngine::World::Level::GetName()
{
    return this->name;
}

GibEngine::Skybox* GibEngine::World::Level::GetSkybox()
{
	return this->skybox->GetEntity();
}

GibEngine::World::DatabaseEntity<GibEngine::Skybox>* GibEngine::World::Level::GetSkyboxEntity()
{
	return skybox;
}

GibEngine::World::DatabaseEntity<GibEngine::Model>* GibEngine::World::Level::AddModel(const char * modelFilename)
{
	DatabaseEntity<Model>* entity = nullptr;
	for (auto modelEntity : modelEntities)
	{
		if (modelEntity->GetEntity()->GetAssetName() == modelFilename)
		{
			entity = modelEntity;
			break;
		}
	}

	Mesh::Instance* instance = new Mesh::Instance();
	DatabaseEntity<Mesh::Instance>* instanceEntity = new DatabaseEntity<Mesh::Instance>(0, instance);

	if (entity != nullptr)
	{
		entity->GetEntity()->AddInstance(instanceEntity);
	}
	else
	{
		Model* model = new Model(modelFilename);
		model->AddInstance(instanceEntity);
		entity = new DatabaseEntity<Model>(0, model);
		modelEntities.push_back(entity);
	}

	return entity;
}

std::vector<GibEngine::World::DatabaseEntity<GibEngine::Model>*> GibEngine::World::Level::GetModelEntities()
{
	return this->modelEntities;
}

std::vector<GibEngine::World::DatabaseEntity<GibEngine::PointLight>*> GibEngine::World::Level::GetPointLightEntities()
{
	return this->pointLightEntities;
}
