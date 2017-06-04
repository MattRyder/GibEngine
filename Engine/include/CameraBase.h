#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity.h"
#include "File.h"

namespace GibEngine
{
	class CameraBase : public Entity
	{
	protected:
		glm::vec3 cameraRight, cameraUp, cameraFront;
		double cameraYaw, cameraPitch;

		glm::mat4 viewMatrix, projectionMatrix;

	public:
		CameraBase(EntityType entityType);

		virtual void Update(double deltaTime, double mouseDeltaX, double mouseDeltaY, int *keyState) = 0;
		virtual void UpdatePosition(double deltaTime, int *keyState) = 0;
		virtual void UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) = 0;

		static void TakeScreenshot(int framebufferWidth, int framebufferHeight);
		static glm::mat4 ConstructProjectionMatrix(float width, float height, float zNear, float zFar, float fov);

		virtual void UpdateUBO() override;

		virtual glm::mat4 GetProjectionMatrix();
		virtual glm::mat4 GetViewMatrix();
	};
}