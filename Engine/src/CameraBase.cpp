#include "CameraBase.h"

GibEngine::CameraBase::CameraBase(EntityType entityType, int cameraWidth, int cameraHeight,
	float nearPlane, float farPlane, float fieldOfViewDegrees) : Entity(entityType)
{
	this->projectionMatrix = ConstructProjectionMatrix(
		(float)cameraWidth, (float)cameraHeight, nearPlane, farPlane, fieldOfViewDegrees);
}

glm::mat4 GibEngine::CameraBase::ConstructProjectionMatrix(float width, float height, float zNear, float zFar, float fov)
{
	return glm::mat4(glm::perspectiveFov(fov, width, height, zNear, zFar));
}

glm::mat4 GibEngine::CameraBase::GetProjectionMatrix()
{
	return this->projectionMatrix;
}

glm::mat4 GibEngine::CameraBase::GetViewMatrix()
{
	return this->viewMatrix;
}

void GibEngine::CameraBase::LookAt(float x, float y, float z)
{
	LookAt(glm::vec3(x, y, z));
}

void GibEngine::CameraBase::LookAt(glm::vec3 target)
{
	this->viewMatrix = glm::mat4(glm::lookAt(GetPosition(), target, cameraUp));
}
