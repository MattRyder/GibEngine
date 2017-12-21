#include "../include/ChaseCamera.h"

GibEngine::ChaseCamera::ChaseCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees, Entity* trackedEntity)
	: CameraBase(EntityType::CAMERA, cameraWidth, cameraHeight, nearPlane, farPlane, fieldOfViewDegrees)
{
	this->trackedEntity = trackedEntity;
}

void GibEngine::ChaseCamera::Update(double deltaTime, glm::vec2 mouseState, glm::vec2 scrollState, int * keyState)
{
	UpdatePosition(deltaTime, keyState);
}

void GibEngine::ChaseCamera::SetTrackedEntity(Entity* entity)
{
	this->trackedEntity = entity;
}

void GibEngine::ChaseCamera::UpdatePosition(double deltaTime, int * keyState)
{
	if (trackedEntity != nullptr)
	{
		glm::vec3 entityPosition = trackedEntity->GetPosition();
		entityPosition.y += 10;
		entityPosition.z -= 10;

		SetPosition(entityPosition);
	}
}

void GibEngine::ChaseCamera::UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) { }