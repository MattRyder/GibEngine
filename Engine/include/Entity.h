#pragma once

#include <string>

#include "glm/vec3.hpp"

namespace GibEngine
{
	class Entity
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

		Entity(Type type);
		Entity(Type type, std::string name);
		Entity(Type type, std::string name, glm::vec3 position);
		virtual ~Entity() = default;

		virtual void Update(double deltaTime) = 0;

		virtual int GetID() const;
		virtual glm::vec3 GetPosition() const;
		virtual std::string GetName() const;

		virtual void SetPosition(const glm::vec3 entityPosition);
		virtual void SetName(const std::string entityName);

		Type GetType() const;
		const std::string& GetTypeName() const;

		static const std::string GetTypeString(Type type);

	protected:
		glm::vec3 position;
		std::string name;
		Entity::Type type;

		const int id;

		static const std::string TypeStrings[static_cast<int>(Entity::Type::ENTITY_TYPE_END) + 1];
	
	private:
		static int _Id;
	};
}
