#include "CameraBase.h"

GibEngine::CameraBase::CameraBase(BaseEntity::Type entityType, int cameraWidth, int cameraHeight,
	float nearPlane, float farPlane, float fieldOfViewDegrees) : BaseEntity(entityType)
{
	this->projectionMatrix = ConstructProjectionMatrix(
		(float)cameraWidth, (float)cameraHeight, nearPlane, farPlane, fieldOfViewDegrees);
}

glm::mat4 GibEngine::CameraBase::ConstructProjectionMatrix(float width, float height, float zNear, float zFar, float fov)
{
	return glm::mat4(glm::perspectiveFov(fov, width, height, zNear, zFar));
}

const glm::mat4& GibEngine::CameraBase::GetProjectionMatrix() const
{
	return this->projectionMatrix;
}

const glm::mat4& GibEngine::CameraBase::GetViewMatrix() const
{
	return this->viewMatrix;
}

void GibEngine::CameraBase::LookAt(const glm::vec3& target)
{
	this->viewMatrix = glm::mat4(glm::lookAt(GetLocalTransform().GetPosition(), target, upVector));
}
