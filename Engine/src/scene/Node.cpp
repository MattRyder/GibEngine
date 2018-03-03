#include "scene/Node.h"

GibEngine::Scene::Node::Node()
	: parentNode(nullptr), 
	childNodes(),
	flags(Flags::DEFAULT),
	entity(nullptr),
	name(),
	worldTransform(),
	localTransform(),
	rotationQuaternion()
{
}

GibEngine::Scene::Node::Node(const std::string name)
	: Node()
{
	this->name = name; 
}

void GibEngine::Scene::Node::Update(const float deltaTime, const Input::InputManager& inputManager)
{
	if (entity != nullptr)
	{
		switch (GetEntity()->GetType())
		{
		case Entity::Type::SKYBOX:
			RotateY(glm::radians((float)(1.0f * deltaTime)));
			break;
		}
	}


	for (auto childNode : childNodes)
	{
		childNode->Update(deltaTime, inputManager);
	}
}

void GibEngine::Scene::Node::RecalculateWorldTransform()
{
	if (parentNode != nullptr)
	{
		worldTransform = parentNode->GetWorldTransform() * localTransform * glm::toMat4(rotationQuaternion);
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

void GibEngine::Scene::Node::Translate(const glm::vec3 & translation)
{
	glm::translate(localTransform, translation);
}

void GibEngine::Scene::Node::Rotate(const float angle, const glm::vec3& axis)
{
	rotationQuaternion = glm::rotate(rotationQuaternion, angle, axis);
	RecalculateWorldTransform();
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

const GibEngine::World::DatabaseRecord GibEngine::Scene::Node::GetDatabaseRecord() const
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

std::string GibEngine::Scene::Node::GetName() const
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
	SetEntityState(World::DatabaseRecord::State::DIRTY);
	return entity;
}

void GibEngine::Scene::Node::SetNodeState(const World::DatabaseRecord::State state)
{
	dbRecord.SetState(state);
}

void GibEngine::Scene::Node::SetEntityState(const World::DatabaseRecord::State state)
{
	dbRecord.SetEntityState(state);
}

void GibEngine::Scene::Node::SetNodeId(const int id)
{
	dbRecord.SetId(id);
}

void GibEngine::Scene::Node::SetEntityId(const int id)
{
	dbRecord.SetAttachedEntityId(id);
}
