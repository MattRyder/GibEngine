#include "scene/Node.h"

GibEngine::Scene::Node::Node(const char* name)
	: parentNode(nullptr), entity(nullptr), name(strdup(name)), flags(Flags::DEFAULT)
{
	dbRecord = new World::DatabaseRecord();
}

GibEngine::Scene::Node::Node(const char* name, World::DatabaseRecord* dbRecord)
	: name(name), parentNode(nullptr), entity(nullptr), dbRecord(dbRecord), flags(Flags::DEFAULT) { }

void GibEngine::Scene::Node::RecalculateWorldTransform()
{
	if (parentNode != nullptr)
	{
		worldTransform = parentNode->GetWorldTransform() * glm::toMat4(rotationQuaternion) * localTransform;
	}
	else
	{
		// Root node's word trans is the local trans:
		worldTransform = glm::toMat4(rotationQuaternion) * localTransform;
	}

	for (auto child : childNodes)
	{
		child->RecalculateWorldTransform();
	}
}

void GibEngine::Scene::Node::SetEntityDirty()
{
	if (dbRecord != nullptr)
	{
		dbRecord->SetEntityState(World::DatabaseRecord::State::DIRTY);
	}
}

void GibEngine::Scene::Node::Translate(const glm::vec3 & translation)
{
	glm::translate(localTransform, translation);
}

void GibEngine::Scene::Node::Rotate(const float angle, const glm::vec3& axis)
{
	rotationQuaternion = glm::rotate(rotationQuaternion, angle, axis);
}

void GibEngine::Scene::Node::RotateX(const float angle)
{
	Rotate(angle, X_AXIS);
}

void GibEngine::Scene::Node::RotateY(const float angle)
{
	Rotate(angle, Y_AXIS);
}

void GibEngine::Scene::Node::RotateZ(const float angle)
{
	Rotate(angle, Z_AXIS);
}

void GibEngine::Scene::Node::Scale(const glm::vec3& scale)
{
	glm::scale(localTransform, scale);
}

void GibEngine::Scene::Node::SetNodeDirty()
{
	if (dbRecord != nullptr)
	{
		dbRecord->SetState(World::DatabaseRecord::State::DIRTY);
	}
}

bool GibEngine::Scene::Node::IsRootNode() const
{
	return parentNode == nullptr;
}

GibEngine::World::DatabaseRecord* GibEngine::Scene::Node::GetDatabaseRecord() const
{
	return dbRecord;
}

GibEngine::Entity* GibEngine::Scene::Node::GetEntity() const
{
	return entity;
}

glm::mat4 GibEngine::Scene::Node::GetWorldTransform() const
{
	return worldTransform;
}

glm::mat4 GibEngine::Scene::Node::GetLocalTransform() const
{
	return localTransform;
}

const char* GibEngine::Scene::Node::GetName() const
{
	return name;
}

const glm::quat GibEngine::Scene::Node::GetRotation() const
{
	return rotationQuaternion;
}

size_t GibEngine::Scene::Node::GetChildNodeCount() const
{
	return childNodes.size();
}

void GibEngine::Scene::Node::AddChildNode(Node* child)
{
	child->SetParentNode(this);

	childNodes.push_back(child);
	child->RecalculateWorldTransform();
}

void GibEngine::Scene::Node::SetParentNode(Node* parent)
{
	parentNode = parent;
}

void GibEngine::Scene::Node::SetEntity(Entity* entity)
{
	this->entity = entity;
}

void GibEngine::Scene::Node::SetLocalTransform(glm::mat4 transformMatrix)
{
	localTransform = transformMatrix;
	RecalculateWorldTransform();
}

void GibEngine::Scene::Node::SetRotation(glm::quat rotationQuaternion)
{
	this->rotationQuaternion = rotationQuaternion;
	RecalculateWorldTransform();
}

GibEngine::Entity* GibEngine::Scene::Node::ModifyEntity()
{
	GetDatabaseRecord()->SetEntityState(World::DatabaseRecord::State::DIRTY);
	return entity;
}