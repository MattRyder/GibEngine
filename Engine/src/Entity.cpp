#include "Entity.h"

int GibEngine::Entity::Id;

GibEngine::Entity::Entity(EntityType type) : entityId(Id++)
{
    this->entityType = type;
    this->entityName = new std::string(GetTypeName() + " (#" + std::to_string(entityId) + ")");
    this->entityPosition = glm::vec3();
}

GibEngine::Entity::Entity(EntityType entityType, glm::vec3& entityPosition) : Entity(entityType)
{
    this->SetPosition(entityPosition);
}

GibEngine::Entity::~Entity()
{
    delete this->entityName;
}

GibEngine::EntityType GibEngine::Entity::GetType() const
{
    return this->entityType;
}

std::string GibEngine::Entity::GetTypeName() const
{
    return GibEngine::EntityTypeStrings[static_cast<int>(this->entityType)];
}

void GibEngine::Entity::BindUBO(GLuint shaderId, GLuint uniformBlockIndex, GLuint blockBinding)
{
	glUniformBlockBinding(shaderId, uniformBlockIndex, blockBinding);

	glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockIndex, Entity::GetUBO());
	if (uboRequiresUpdate)
	{
		UpdateUBO();
		uboRequiresUpdate = false;
	}
}

GLuint& GibEngine::Entity::GetUBO()
{
	return uniformBufferObject;
}

int GibEngine::Entity::GetID() const
{
    return this->entityId;
}

glm::vec3 GibEngine::Entity::GetPosition() const
{
    return entityPosition;
}

std::string& GibEngine::Entity::GetName() const
{
    return *entityName;
}

void GibEngine::Entity::Print()
{
    // TODO
}

bool GibEngine::Entity::IsUBOCreated()
{
	return uboInitialized;
}


void GibEngine::Entity::SetPosition(glm::vec3 entityPosition)
{
    this->entityPosition = entityPosition;
}

void GibEngine::Entity::SetName(std::string *entityName)
{
	this->entityName = entityName;
}
