#include "Entity.h"

// accumulator for the Entity ID system
int GibEngine::Entity::_Id;

const std::string GibEngine::Entity::TypeStrings[static_cast<int>(Entity::Type::ENTITY_TYPE_END) + 1] =
{
	"Entity",
	"Mesh",
	"Light",
	"Point Light",
	"Directional Light",
	"Camera",
	"Player",
	"Skybox",
	"Unknown"
};

GibEngine::Entity::Entity(Type type)
	: Entity(type, GetTypeString(type) + "__#" + std::to_string(id+1)) { }

GibEngine::Entity::Entity(Type type, std::string name) 
	: Entity(type, name, glm::vec3()) { }

GibEngine::Entity::Entity(Type type, std::string name, glm::vec3 position)
	: id(_Id++), type(type), name(name), position(position) { }



const std::string& GibEngine::Entity::GetTypeName() const
{
    return TypeStrings[static_cast<int>(this->type)];
}

const std::string GibEngine::Entity::GetTypeString(GibEngine::Entity::Type type)
{
	return TypeStrings[static_cast<int>(type)];
}

int GibEngine::Entity::GetID() const
{
    return this->id;
}

GibEngine::Entity::Type GibEngine::Entity::GetType() const
{
	return this->type;
}

glm::vec3 GibEngine::Entity::GetPosition() const
{
    return this->position;
}

std::string GibEngine::Entity::GetName() const
{
    return this->name;
}

void GibEngine::Entity::SetPosition(const glm::vec3 position)
{
    this->position = position;
}

void GibEngine::Entity::SetName(const std::string name)
{
	this->name = name;
}
