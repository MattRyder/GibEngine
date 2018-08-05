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
		enum class Flags
		{
			DEFAULT = 1 << 0,
			TRACKING = 1 << 1
		};

		static unsigned int BUFFER_OBJECT_SIZE;
		Flags flags;

		FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees);

		virtual void RegisterEvents(Event::EventManager* const eventManager);

		void OnTick(float deltaTime, Event::OnTickEvent& e);
		void OnMouseMove(float deltaTime, Event::MouseMoveEvent& e);

		Flags GetFlags() const { return this->flags; }
		void SetFlags(Flags flags) { this->flags = flags; }
		static bool FlagMask(Flags x) { return static_cast<char>(x) != 0; };


		void ToggleTrackingParent();
	};

	GIB_FLAGS(FreeCamera::Flags);
}