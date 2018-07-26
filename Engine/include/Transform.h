#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GibEngine
{
	class Transform
	{
		glm::mat4 transform;

	public:

		Transform(const glm::mat4& transformMatrix) : transform(transformMatrix) { }

		Transform() : Transform(glm::mat4(1.0)) { }

		void SetTransform(const glm::mat4 transform)
		{
			this->transform = transform;
		}

		void Scale(const glm::vec3& scale)
		{
			this->SetTransform(glm::scale(transform, scale));
		}

		void SetPosition(const glm::vec3& position)
		{
			auto tmp = transform;
			tmp[3] = glm::vec4(position, tmp[3][3]);
			this->SetTransform(tmp);
		}

		glm::mat4 GetTransformMatrix() const
		{
			return transform;
		}

		glm::vec3 GetPosition() const
		{
			return glm::vec3(transform[3]);
		}

		glm::vec3 GetScale() const
		{
			return glm::vec3(transform[0][0], transform[1][1], transform[2][2]);
		}
	};
}