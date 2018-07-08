#pragma once

#include "CameraBase.h"
#include "event/OnTickEvent.h"

namespace GibEngine
{
	class FreeCamera : public CameraBase
	{
		const float MOVEMENT_SPEED = 1.0f;

		glm::vec2 lastMouseDelta;

		FreeCamera();

	public:
		static unsigned int BUFFER_OBJECT_SIZE;

		FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees);

		virtual void RegisterEvents(Event::EventManager* const eventManager);

		void OnTick(float deltaTime, Event::OnTickEvent& e);
		void OnMouseMove(float deltaTime, Event::MouseMoveEvent& e);
	};
}