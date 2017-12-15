#pragma once

#include <string>
#include <sstream>

#include "glm/vec3.hpp"

#include "Logger.h"

namespace GibEngine
{
	enum class EntityType
	{
		ENTITY,
		MODEL,
		INSTANCED_MODEL,
		LIGHT,
		POINT_LIGHT,
		DIRECTIONAL_LIGHT,
		CAMERA,
		PLAYER,
		SKYBOX,
		ENTITY_TYPE_END
	};

	static const char* EntityTypeStrings[static_cast<int>(EntityType::ENTITY_TYPE_END) + 1]
	{
	  "Entity",
	  "Model",
	  "Instanced Model",
	  "Light",
	  "Point Light",
	  "Directional Light",
	  "Camera",
	  "Player",
	  "Skybox",
	  "Unknown"
	};

	class Entity
	{
		static int Id;
		const int entityId;

	protected:
		glm::vec3 entityPosition;
		const char* entityName;
		EntityType entityType;

	public:
		Entity(EntityType entityType);
		Entity(EntityType entityType, glm::vec3& entityPosition);
		virtual ~Entity();

		virtual void Update(double deltaTime) = 0;

		virtual int GetID() const;
		virtual glm::vec3 GetPosition() const;
		virtual const char* GetName() const;

		virtual void SetPosition(glm::vec3 entityPosition);
		void SetName(const char* entityName);

		EntityType GetType() const;
		const char* GetTypeName() const;

		static const char* GetTypeString(EntityType type);
	};
}
