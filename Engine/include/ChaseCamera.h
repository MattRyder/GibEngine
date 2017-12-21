#pragma once

#include "CameraBase.h"

namespace GibEngine
{
	class ChaseCamera : public CameraBase
	{
		Entity* trackedEntity = nullptr;

	protected:
		virtual void UpdatePosition(double deltaTime, int * keyState) override;
		virtual void UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) override;

	public:
		ChaseCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees, Entity* trackedEntity);

		virtual void Update(double deltaTime, glm::vec2 mouseState, glm::vec2 scrollState, int * keyState) override;

		void SetTrackedEntity(Entity* entity);
	};
}