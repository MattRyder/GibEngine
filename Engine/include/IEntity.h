#pragma once

#include <glm/vec3.hpp>

namespace GibEngine
{
	namespace Event
	{
		class EventManager;
	}

	class IEntity
	{
	public:
		virtual glm::vec3 GetPosition() const = 0;

		virtual void RegisterEvents(Event::EventManager* const eventManager) = 0;

		virtual void Translate(const glm::vec3& translation) = 0;

		virtual void Rotate(const float angle, const glm::vec3& axis) = 0;

		virtual void RotateX(const float angle) = 0;

		virtual void RotateY(const float angle) = 0;

		virtual void RotateZ(const float angle) = 0;

		virtual void Scale(const glm::vec3& scale) = 0;


	};
}