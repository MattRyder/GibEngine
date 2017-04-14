#pragma once

#include "mock/MockCameraBase.h"

using namespace GibEngine;

class CameraBaseTest : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
      cameraBase = new MockCameraBase();
    }
  
  public:
    MockCameraBase *cameraBase;
};