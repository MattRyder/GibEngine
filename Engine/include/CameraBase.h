#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EnumFlags.h"
#include "Entity.h"

namespace GibEngine
{
	class CameraBase : public Entity
	{
	protected:
		glm::vec3 cameraRight, cameraUp, cameraFront;
		double cameraYaw, cameraPitch;

		glm::mat4 viewMatrix, projectionMatrix;

		virtual void UpdatePosition(double deltaTime, int *keyState) = 0;
		virtual void UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) = 0;

	public:

		enum class Direction
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		CameraBase(Entity::Type entityType, int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees);

		virtual void Update(double deltaTime) override { }
		virtual void Update(double deltaTime, glm::vec2 mouseState, glm::vec2 scrollState, int *keyState) = 0;

		static glm::mat4 ConstructProjectionMatrix(float width, float height, float zNear, float zFar, float fov);

		virtual glm::mat4 GetProjectionMatrix();
		virtual glm::mat4 GetViewMatrix();
		virtual const std::string GetAllocatedBufferName() const;

		void LookAt(const glm::vec3& target);

	};
	
	GIB_FLAGS(CameraBase::Direction);
}