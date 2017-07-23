#include "CameraBase.h"

#define PI  3.14159265358979323846
#define ONE_DEG_IN_RAD (2.0 * PI) / 360.0 // 0.017444444
#define ONE_RAD_IN_DEG 360.0 / (2.0 * PI) //57.2957795

GibEngine::CameraBase::CameraBase(EntityType entityType) : Entity(entityType) { }

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
