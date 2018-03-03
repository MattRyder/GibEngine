#pragma once

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "CameraBase.h"

namespace GibEngine 
{
    class FreeCamera : public CameraBase
    {
        const float cameraMovementSpeed;
		glm::vec2 lastMouseDelta;

        FreeCamera();

	protected:
		virtual void UpdatePosition(double deltaTime, int *keyState) override;
		void UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) override;

    public:
		static unsigned int BUFFER_OBJECT_SIZE;

        FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees);
        ~FreeCamera();

        virtual void Render();

		virtual void Update(double deltaTime, glm::vec2 mouseState, glm::vec2 scrollState, int *keyState) override;
    };
}