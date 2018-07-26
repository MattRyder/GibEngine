#include "BaseEntity.h"

// accumulator for the Entity ID system
int GibEngine::BaseEntity::_Id;

const std::string GibEngine::BaseEntity::TypeStrings[static_cast<int>(BaseEntity::Type::ENTITY_TYPE_END) + 1] =
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

GibEngine::BaseEntity::BaseEntity(Type type)
	: BaseEntity(type, "")
{
	SetName(GetTypeString(type) + "__#" + std::to_string(id+1));
}

GibEngine::BaseEntity::BaseEntity(Type type, std::string name) 
	: BaseEntity(type, name, glm::vec3()) { }

GibEngine::BaseEntity::BaseEntity(Type type, std::string name, glm::vec3 position)
	: id(_Id++), type(type), name(name), parent(nullptr), frontVector(-Z_AXIS), upVector(Y_AXIS), activeDirections(Direction::NONE),
		localTransform(glm::mat4(1.0)), worldTransform(glm::mat4(1.0)), rotationQuaternion()
{
	this->nameKey = GetTypeName() + "_" + std::to_string(GetID());
	SetPosition(position);
}

const std::string& GibEngine::BaseEntity::GetTypeName() const
{
    return TypeStrings[static_cast<int>(this->type)];
}

const std::string& GibEngine::BaseEntity::GetNameKey() const
{
	return nameKey;
}

const std::string GibEngine::BaseEntity::GetTypeString(GibEngine::BaseEntity::Type type)
{
	return TypeStrings[static_cast<int>(type)];
}

void GibEngine::BaseEntity::RegisterEvents(Event::EventManager* const eventManager) 
{
	eventManager->AddEventListener(Event::Type::ON_TICK, this, [this](float deltaTime, std::shared_ptr<Event::IEvent> e) {
		auto mme = std::dynamic_pointer_cast<Event::OnTickEvent>(e);
		OnTick(deltaTime, *mme);
	});

	eventManager->AddEventListener(Event::Type::KEY_DOWN, this, [this](float deltaTime, std::shared_ptr<Event::IEvent> e) {
		auto kde = std::dynamic_pointer_cast<Event::KeyDownEvent>(e);
		OnKeyDown(deltaTime, *kde);
	});

	eventManager->AddEventListener(Event::Type::KEY_UP, this, [this](float deltaTime, std::shared_ptr<Event::IEvent> e) {
		auto kue = std::dynamic_pointer_cast<Event::KeyUpEvent>(e);
		OnKeyUp(deltaTime, *kue);
	});
}

int GibEngine::BaseEntity::GetID() const
{
    return this->id;
}

GibEngine::BaseEntity::Type GibEngine::BaseEntity::GetType() const
{
	return this->type;
}

GibEngine::Transform GibEngine::BaseEntity::GetWorldTransform() const
{
	return worldTransform;
}

GibEngine::Transform GibEngine::BaseEntity::GetLocalTransform() const
{
	return localTransform;
}

const unsigned int GibEngine::BaseEntity::GetChildCount() const
{
	return children.size();
}

glm::vec3 GibEngine::BaseEntity::GetPosition() const
{
	return glm::vec3();
}

std::string GibEngine::BaseEntity::GetName() const
{
    return this->name;
}

void GibEngine::BaseEntity::AddChild(const std::shared_ptr<BaseEntity> childEntity)
{
	childEntity->parent = this;
	this->children.push_back(childEntity);
	 RecalculateWorldTransform();
}

void GibEngine::BaseEntity::SetPosition(const glm::vec3 position)
{
	localTransform.SetPosition(position);
	RecalculateWorldTransform();
}

void GibEngine::BaseEntity::SetName(const std::string name)
{
	this->name = name;
}

void GibEngine::BaseEntity::SetLocalTransform(const glm::mat4 localTransform)
{
	this->localTransform.SetTransform(localTransform);
	RecalculateWorldTransform();
}

void GibEngine::BaseEntity::RecalculateWorldTransform()
{
	const auto& rotationMatrix = glm::toMat4(rotationQuaternion);
	const auto& localTransMatrix = localTransform.GetTransformMatrix();

	if (parent != nullptr)
	{
		const auto& parentWorldTransMatrix = parent->GetWorldTransform().GetTransformMatrix();
		worldTransform.SetTransform(parentWorldTransMatrix * rotationMatrix * localTransMatrix);
		//worldTransform = parentWorldTransMatrix * glm::toMat4(rotationQuaternion) *  localTransform;
	}
	else
	{
		// Root node's word trans is the local trans:
		worldTransform.SetTransform(rotationMatrix * localTransMatrix);
		//worldTransform.SetTransform(glm::toMat4(rotationQuaternion) * localTransform;
	}

	for (auto child : children)
	{
		child->RecalculateWorldTransform();
	}
}

void GibEngine::BaseEntity::Translate(const glm::vec3& translation)
{
}

void GibEngine::BaseEntity::Rotate(const float angle, const glm::vec3& axis)
{
	rotationQuaternion = glm::rotate(rotationQuaternion, angle, axis);
	RecalculateWorldTransform();
}

void GibEngine::BaseEntity::RotateX(const float angle)
{
	Rotate(angle, X_AXIS);
}

void GibEngine::BaseEntity::RotateY(const float angle)
{
	Rotate(angle, Y_AXIS);
}

void GibEngine::BaseEntity::RotateZ(const float angle)
{
	Rotate(angle, Z_AXIS);
}

void GibEngine::BaseEntity::Scale(const glm::vec3& scale)
{
	localTransform.Scale(scale);
}

glm::vec3 GibEngine::BaseEntity::GetFront() const
{
	return frontVector;
}

void GibEngine::BaseEntity::OnTick(float deltaTime, Event::OnTickEvent & e)
{
	const float MOVEMENT_SPEED = 15.0f * deltaTime;
	glm::vec3 position = GetWorldTransform().GetPosition();

	bool positionChanged = false;
	auto activeDir = static_cast<int>(activeDirections);
	if (activeDir & static_cast<int>(Direction::FORWARD))
	{
		positionChanged = true;
		position += frontVector * MOVEMENT_SPEED;
	}
	if (activeDir & static_cast<int>(Direction::BACKWARD))
	{
		positionChanged = true;
		position -= frontVector * MOVEMENT_SPEED;
	}
	if (activeDir & static_cast<int>(Direction::LEFT))
	{
		positionChanged = true;

		// Rotate Left
		//Rotate(MOVEMENT_SPEED, upVector);

		// Strafe Left
		position -= glm::normalize(glm::cross(frontVector, upVector)) * MOVEMENT_SPEED;
	}
	if (activeDir & static_cast<int>(Direction::RIGHT))
	{
		positionChanged = true;

		// Rotate Left
		//Rotate(-MOVEMENT_SPEED, upVector);

		// Strafe Left
		position += glm::normalize(glm::cross(frontVector, upVector)) * MOVEMENT_SPEED;
	}

	if (positionChanged)
	{
		SetPosition(position);
	}
}

void GibEngine::BaseEntity::OnKeyDown(float deltaTime, Event::KeyDownEvent& e)
{
	switch (e.KeyCode)
	{
	case GLFW_KEY_W:
		activeDirections |= Direction::FORWARD;
		break;
	case GLFW_KEY_S:
		activeDirections |= Direction::BACKWARD;
		break;
	case GLFW_KEY_A:
		activeDirections |= Direction::LEFT;
		break;
	case GLFW_KEY_D:
		activeDirections |= Direction::RIGHT;
		break;
	}
}

void GibEngine::BaseEntity::OnKeyUp(float deltaTime, Event::KeyUpEvent& e)
{
	switch (e.KeyCode)
	{
	case GLFW_KEY_W:
		activeDirections &= ~Direction::FORWARD;
		break;
	case GLFW_KEY_S:
		activeDirections &= ~Direction::BACKWARD;
		break;
	case GLFW_KEY_A:
		activeDirections &= ~Direction::LEFT;
		break;
	case GLFW_KEY_D:
		activeDirections &= ~Direction::RIGHT;
		break;
	}
}