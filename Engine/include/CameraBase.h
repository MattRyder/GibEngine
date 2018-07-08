#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BaseEntity.h"

namespace GibEngine
{
	class CameraBase : public BaseEntity
	{
	protected:
		double cameraYaw, cameraPitch;

		glm::mat4 viewMatrix, projectionMatrix;

	public:
		CameraBase(BaseEntity::Type entityType, int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees);

		static glm::mat4 ConstructProjectionMatrix(float width, float height, float zNear, float zFar, float fov);

		virtual const glm::mat4& GetProjectionMatrix() const;

		virtual const glm::mat4& GetViewMatrix() const;

		void LookAt(const glm::vec3& target);
	};
	
}