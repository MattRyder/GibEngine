#include "FreeCamera.h"

GibEngine::FreeCamera::FreeCamera() : CameraBase(EntityType::CAMERA)
{
    this->cameraYaw = -90.0f;

    // Set default vectors:
    this->cameraUp = glm::vec3(0, 1.0f, 0);
    this->cameraFront = glm::vec3(0, 0, -1.0f);

	SetPosition(glm::vec3(0, 5, 15));

	this->viewMatrix = glm::mat4(glm::lookAt(GetPosition(), glm::vec3(GetPosition() + cameraFront), cameraUp));

	glGenBuffers(1, &uniformBufferObject);
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferObject);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 36, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uniformBufferObject, 0, sizeof(float) * 36);
}

GibEngine::FreeCamera::FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees)
    : FreeCamera()
{
    this->projectionMatrix = ConstructProjectionMatrix((float)cameraWidth, (float)cameraHeight, nearPlane, farPlane, fieldOfViewDegrees);
}

GibEngine::FreeCamera::~FreeCamera()
{
}

void GibEngine::FreeCamera::Render() { }

void GibEngine::FreeCamera::Update(double deltaTime) { }

void GibEngine::FreeCamera::Update(double deltaTime, double mouseDeltaX, double mouseDeltaY, int *keyState)
{
	bool mouseMovementDetected = mouseDeltaX != lastMouseX || mouseDeltaY != lastMouseY;
	glm::vec3 position = GetPosition();


    UpdateDirection(deltaTime, mouseDeltaX, mouseDeltaY);
    UpdatePosition(deltaTime, keyState);

    glm::vec3 newPosition = GetPosition();
	if (position != newPosition || mouseMovementDetected)
	{
		Logger::Instance->info("Mouse Delta ({}, {})", mouseDeltaX, mouseDeltaY);

		this->viewMatrix = glm::lookAt(newPosition, newPosition + cameraFront, cameraUp);
		SetUBORequiresUpdate();
	}
}

void GibEngine::FreeCamera::UpdatePosition(double deltaTime, int *keyState)
{
    glm::vec3 &position = GetPosition();
    float movementSpeed = static_cast<float>(cameraMovementSpeed * deltaTime);

    if (keyState[GLFW_KEY_W])
        position += (cameraFront + movementSpeed);
    if (keyState[GLFW_KEY_S])
        position -= cameraFront + movementSpeed;
    if (keyState[GLFW_KEY_A])
        position -= glm::normalize(glm::cross(cameraFront, cameraUp)) + movementSpeed;
    if (keyState[GLFW_KEY_D])
        position += glm::normalize(glm::cross(cameraFront, cameraUp)) + movementSpeed;

    //Logger::Instance->info("Position ({}, {}, {})", position.x, position.y, position.z);
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
	front.x = cos(cameraYaw) * cos(cameraPitch);
	front.y = sin(cameraPitch);
	front.z = sin(cameraYaw) * cos(cameraPitch);

	cameraFront = glm::normalize(front);
}