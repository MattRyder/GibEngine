#include "Entity.h"

int GibEngine::Entity::Id;

GibEngine::Entity::Entity(EntityType type) : entityId(Id++)
{
    this->entityType = type;

	std::string* nameStr = new std::string(GetTypeName() + " (#" + std::to_string(entityId) + ")");
	this->entityName = nameStr->c_str();
    this->entityPosition = glm::vec3();
}

GibEngine::Entity::Entity(EntityType entityType, glm::vec3& entityPosition) : Entity(entityType)
{
    this->SetPosition(entityPosition);
}

GibEngine::Entity::~Entity() { }

GibEngine::EntityType GibEngine::Entity::GetType() const
{
    return this->entityType;
}

std::string GibEngine::Entity::GetTypeName() const
{
    return GibEngine::EntityTypeStrings[static_cast<int>(this->entityType)];
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
