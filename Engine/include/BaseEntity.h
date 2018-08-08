#pragma once

#include <string>
#include <memory>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"
#include "EnumFlags.h"
#include "IEntity.h"
#include "input/InputManager.h"

namespace GibEngine
{
	enum class Direction : int
	{
		NONE = 0,
		FORWARD = 1,
		BACKWARD = 2,
		LEFT = 4,
		RIGHT = 8,
		UP = 16,
		DOWN = 32,

	};
	GIB_FLAGS(Direction);


	class BaseEntity : public IEntity
	{
	public:
		enum class Type : char
		{
			ENTITY,
			MESH,
			LIGHT,
			POINT_LIGHT,
			DIRECTIONAL_LIGHT,
			CAMERA,
			PLAYER,
			SKYBOX,
			ENTITY_TYPE_END
		};

		const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
		const glm::vec3 Y_AXIS = glm::vec3(0, 1, 0);
		const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);

		BaseEntity(Type type);
		BaseEntity(Type type, std::string name);
		BaseEntity(Type type, std::string name, glm::vec3 position);
		virtual ~BaseEntity() = default;

		virtual int GetID() const;
		virtual std::string GetName() const;

		std::vector<std::shared_ptr<BaseEntity>>::const_iterator ChildrenBegin() const
		{
			return children.begin();
		}

		std::vector<std::shared_ptr<BaseEntity>>::const_iterator ChildrenEnd() const
		{
			return children.end();
		}

		virtual void AddChild(const std::shared_ptr<BaseEntity> childEntity);
		virtual void SetPosition(const glm::vec3 entityPosition);
		virtual void SetName(const std::string entityName);
		virtual void SetLocalTransform(const glm::mat4 localTransform);

		Type GetType() const;
		const std::string& GetTypeName() const;

		const std::string& GetNameKey() const;
		Transform GetWorldTransform() const;
		Transform GetLocalTransform() const;
		glm::quat GetRotationQuaternion() const { return rotationQuaternion; }

		const unsigned int GetChildCount() const;

		void RecalculateWorldTransform();

		static const std::string GetTypeString(Type type);

		virtual void RegisterEvents(Event::EventManager* const eventManager) override;
		virtual void OnTick(float deltaTime, Event::OnTickEvent& e);
		virtual void OnKeyDown(float deltaTime, Event::KeyDownEvent& e);
		virtual void OnKeyUp(float deltaTime, Event::KeyUpEvent& e);

		virtual void Translate(const glm::vec3& translation) override;
		virtual void Rotate(const float angle, const glm::vec3& axis) override;
		virtual void RotateX(const float angle) override;
		virtual void RotateY(const float angle) override;
		virtual void RotateZ(const float angle) override;
		virtual void Scale(const glm::vec3& scale) override;

		glm::vec3 GetFront() const;

	protected:
		const int id;

		BaseEntity const* parent;
		std::vector<std::shared_ptr<BaseEntity>> children;

		std::string name;
		BaseEntity::Type type;

		std::string nameKey;

		Transform worldTransform;
		Transform localTransform;
		glm::quat rotationQuaternion;

		glm::vec3 upVector;
		glm::vec3 frontVector;

		static const std::string TypeStrings[static_cast<int>(BaseEntity::Type::ENTITY_TYPE_END) + 1];
	
	private:
		static int _Id;

		Direction activeDirections;

		enum class InputRotation
		{
			NONE = 1 << 0,
			LEFT = 1 << 1,
			RIGHT = 1 << 2
		};

		InputRotation activeRotation = InputRotation::NONE;

		// Inherited from IEntity, unrequired
		virtual glm::vec3 GetPosition() const;

	};
}
