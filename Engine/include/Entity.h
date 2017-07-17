#pragma once

#include <string>

#include "GL/gl3w.h"
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
		std::string *entityName;
		EntityType entityType;

		GLuint uniformBufferObject = 100;
		bool uboInitialized = false;
		bool uboRequiresUpdate = true;

	public:
		const int GL_MAP_RANGE_BUFFER_OFFSET = 0;

		Entity(EntityType entityType);
		Entity(EntityType entityType, glm::vec3& entityPosition);
		virtual ~Entity();

		virtual void Update(double deltaTime) = 0;

		virtual int GetID() const;
		virtual glm::vec3 GetPosition() const;
		virtual std::string& GetName() const;

		virtual void Print();

		virtual void UpdateUBO() = 0;
		virtual void BindUBO(GLuint shaderId, GLuint uniformBlockIndex, GLuint blockBinding);
		virtual GLuint& GetUBO();
		virtual bool IsUBOCreated();
		void SetUBORequiresUpdate() { uboRequiresUpdate = true; }

		virtual void SetPosition(glm::vec3 entityPosition);
		void SetName(std::string *entityName);

		EntityType GetType() const;
		std::string GetTypeName() const;
	};
}
