#include "FreeCamera.h"

unsigned int GibEngine::FreeCamera::BUFFER_OBJECT_SIZE = sizeof(float) * 36;

GibEngine::FreeCamera::FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees)
    : CameraBase(EntityType::CAMERA, cameraWidth, cameraHeight, nearPlane, farPlane, fieldOfViewDegrees)
{
	this->cameraYaw = -90.0f;

	// Set default vectors:
	this->cameraUp = glm::vec3(0, 1.0f, 0);
	this->cameraFront = glm::vec3(0, 0, -1.0f);

	this->viewMatrix = glm::mat4(glm::lookAt(GetPosition(), glm::vec3(GetPosition() + cameraFront), cameraUp));
}

GibEngine::FreeCamera::~FreeCamera() { }

void GibEngine::FreeCamera::Render() { }

void GibEngine::FreeCamera::Update(double deltaTime, glm::vec2 mouseState, glm::vec2 scrollState, int *keyState)
{
	bool mouseMovementDetected = mouseState.x != lastMouseX || mouseState.y != lastMouseY;
	glm::vec3 position = GetPosition();

    UpdateDirection(deltaTime, mouseState.x, mouseState.y);
    UpdatePosition(deltaTime, keyState);

    glm::vec3 newPosition = GetPosition();
	if (position != newPosition || mouseMovementDetected)
	{
		this->viewMatrix = glm::lookAt(newPosition, newPosition + cameraFront, cameraUp);
	}
}

void GibEngine::FreeCamera::UpdatePosition(double deltaTime, int *keyState)
{
    glm::vec3 position = GetPosition();
    float movementSpeed = static_cast<float>(cameraMovementSpeed * deltaTime);

    if (keyState[GLFW_KEY_W])
        position += (cameraFront + movementSpeed);
    if (keyState[GLFW_KEY_S])
        position -= (cameraFront + movementSpeed);
    if (keyState[GLFW_KEY_A])
        position -= glm::normalize(glm::cross(cameraFront, cameraUp));
    if (keyState[GLFW_KEY_D])
        position += glm::normalize(glm::cross(cameraFront, cameraUp));

    SetPosition(position);
}

void GibEngine::FreeCamera::UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) 
{
    double offsetX = (mouseDeltaX - lastMouseX);
    double offsetY = lastMouseY - mouseDeltaY;
    lastMouseX = mouseDeltaX;
    lastMouseY = mouseDeltaY;

    GLfloat sensitivity = 0.005f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    cameraYaw += offsetX;
    cameraPitch += offsetY;

    if (cameraPitch > 1.0f) cameraPitch = 1.0f;
    if (cameraPitch < -1.0f) cameraPitch = -1.0f;

	glm::vec3 front;
	front.x = float(cos(cameraYaw) * cos(cameraPitch));
	front.y = float(sin(cameraPitch));
	front.z = float(sin(cameraYaw) * cos(cameraPitch));

	cameraFront = glm::normalize(front);
}