#pragma once

#include <glm/vec3.hpp>

namespace GibEngine
{
	class AABB
	{
		glm::vec3 position;
		glm::vec3 size;

	public:
		AABB();
		AABB(glm::vec3 position, glm::vec3 size);

		bool operator==(const AABB& other) const;

		bool Contains(const AABB& other) const;
		bool ContainsPoint(const glm::vec3 point) const;

		glm::vec3 GetPosition() const;
		glm::vec3 GetSize() const;
		glm::vec3 GetMaxBounds() const;

		void SetPosition(const glm::vec3 position);
		void SetSize(const glm::vec3 size);
	};
}