#include "Entity.h"

int GibEngine::Entity::Id;

GibEngine::Entity::Entity(EntityType type) : entityId(Id++)
{
    this->entityType = type;

	std::stringstream name;
	name << GetTypeName() << " (EID #" << std::to_string(entityId) << ")";

	this->entityName = strdup(name.str().c_str());
    this->entityPosition = glm::vec3();
}

GibEngine::Entity::Entity(EntityType entityType, const char* name) :
	entityId(Id++), entityType(entityType), entityName(strdup(name)) { }

GibEngine::Entity::~Entity() { }

GibEngine::EntityType GibEngine::Entity::GetType() const
{
    return this->entityType;
}

const char* GibEngine::Entity::GetTypeName() const
{
    return GibEngine::EntityTypeStrings[static_cast<int>(this->entityType)];
}

const char* GibEngine::Entity::GetTypeString(GibEngine::EntityType type)
{
	return EntityTypeStrings[static_cast<int>(type)];
}

int GibEngine::Entity::GetID() const
{
    return this->entityId;
}

glm::vec3 GibEngine::Entity::GetPosition() const
{
    return entityPosition;
}

const char* GibEngine::Entity::GetName() const
{
    return entityName;
}

void GibEngine::Entity::SetPosition(glm::vec3 entityPosition)
{
    this->entityPosition = entityPosition;
}

void GibEngine::Entity::SetName(const char* entityName)
{
	this->entityName = entityName;
}
