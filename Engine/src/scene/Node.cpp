#include "scene/Node.h"

GibEngine::Scene::Node::Node(const char* name) : parentNode(nullptr), entity(nullptr), name(strdup(name))
{
	dbRecord = new World::DatabaseRecord();
}

GibEngine::Scene::Node::Node(const char* name, World::DatabaseRecord* dbRecord)
	: name(name), parentNode(nullptr), entity(nullptr), dbRecord(dbRecord) { }

void GibEngine::Scene::Node::RecalculateWorldTransform()
{
	if (parentNode != nullptr)
	{
		worldTransform = parentNode->GetWorldTransform() * localTransform;
	}
	else
	{
		// Root node's word trans is the local trans:
		worldTransform = localTransform;
	}

	for (auto child : childNodes)
	{
		child->RecalculateWorldTransform();
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

GibEngine::Entity* GibEngine::Scene::Node::ModifyEntity()
{
	GetDatabaseRecord()->SetEntityState(World::DatabaseRecord::State::DIRTY);
	return entity;
}