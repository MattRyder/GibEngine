#pragma once

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "CameraBase.h"

namespace GibEngine 
{
    class FreeCamera : public CameraBase
    {
        int cameraMovementSpeed = 25;
        double lastMouseX, lastMouseY;

        FreeCamera();

    public:
        FreeCamera(int cameraWidth, int cameraHeight, float nearPlane, float farPlane, float fieldOfViewDegrees);
        ~FreeCamera();

        // Inherited via CameraBase
        virtual void Render() override;
        virtual void Update(double deltaTime) override;
        virtual void Update(double deltaTime, double mouseDeltaX, double mouseDeltaY, int *keyState) override;

        virtual void UpdatePosition(double deltaTime, int *keyState) override;
        void UpdateDirection(double deltaTime, double mouseDeltaX, double mouseDeltaY) override;
    };
}