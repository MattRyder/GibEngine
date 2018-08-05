#include "FreeCamera.h"

unsigned int GibEngine::FreeCamera::BUFFER_OBJECT_SIZE = sizeof(float) * 36;

GibEngine::FreeCamera::FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees)
	: CameraBase(BaseEntity::Type::CAMERA, cameraWidth, cameraHeight, nearPlane, farPlane, fieldOfViewDegrees), flags(FreeCamera::Flags::TRACKING)
{
	this->cameraYaw = -90.0f;
	LookAt(GetLocalTransform().GetPosition() + frontVector);
}

void GibEngine::FreeCamera::RegisterEvents(Event::EventManager* const eventManager)
{
	BaseEntity::RegisterEvents(eventManager);

	eventManager->AddEventListener(Event::Type::MOUSE_MOVE, this, [this](float deltaTime, std::shared_ptr<Event::IEvent> e) {
		auto mme = std::dynamic_pointer_cast<Event::MouseMoveEvent>(e);
		OnMouseMove(deltaTime, *mme);
	});
}

void GibEngine::FreeCamera::OnTick(float deltaTime, Event::OnTickEvent & e)
{
	BaseEntity::OnTick(deltaTime, e);

	if (FlagMask(flags & Flags::TRACKING))
	{
		auto back = parent->GetLocalTransform().GetPosition();
		back -= parent->GetFront() * 15.0f;
		back += upVector * 4.0f;

		SetPosition(back);

		this->viewMatrix = glm::lookAt(GetLocalTransform().GetPosition(), parent->GetLocalTransform().GetPosition(), upVector);
	}
	
}

void GibEngine::FreeCamera::OnMouseMove(float deltaTime, Event::MouseMoveEvent& e)
{
	auto offset = glm::vec2((e.Movement.x - lastMouseDelta.x), (lastMouseDelta.y - e.Movement.y));
	lastMouseDelta = e.Movement;

	float sensitivity = 0.45f;
	offset *= sensitivity;

	cameraYaw += offset.x * deltaTime;
	cameraPitch += offset.y * deltaTime;

	if (cameraPitch > 1.0f) cameraPitch = 1.0f;
	if (cameraPitch < -1.0f) cameraPitch = -1.0f;

	glm::vec3 front;
	front.x = float(cos(cameraYaw) * cos(cameraPitch));
	front.y = float(sin(cameraPitch));
	front.z = float(sin(cameraYaw) * cos(cameraPitch));

	frontVector = front;

	LookAt(GetLocalTransform().GetPosition() + frontVector);
}

void GibEngine::FreeCamera::ToggleTrackingParent()
{
	flags ^= Flags::TRACKING;
}