#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CameraBase.h"

using namespace GibEngine;

class MockCameraBase : public CameraBase
{
  public:
    MOCK_METHOD4(Update, void(double deltaTime, double mouseDeltaX, double mouseDeltaY, int *keyState));
    MOCK_METHOD2(UpdatePosition, void(double deltaTime, int *keyState));
    MOCK_METHOD3(UpdateDirection, void(double deltaTime, double mouseDeltaX, double mouseDeltaY));

	MOCK_METHOD0(GetProjectionMatrix, glm::mat4());
	MOCK_METHOD0(GetViewMatrix, glm::mat4());

    MOCK_METHOD0(Render, void());
    MOCK_METHOD1(Update, void(double deltaTime));

    MockCameraBase() : CameraBase(EntityType::CAMERA) { }
};