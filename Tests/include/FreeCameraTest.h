#pragma once

#include "gtest/gtest.h"
#include "glm/gtc/matrix_transform.hpp"

#include "FreeCamera.h"

using namespace GibEngine;

#define WINDOW_WIDTH  800.0f
#define WINDOW_HEIGHT 600.0f
#define Z_NEAR		  0.1f
#define Z_FAR		  100.0f
#define FOV		      90.0f

class FreeCameraTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    camera = new FreeCamera(WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR, FOV);
  }
  
  FreeCamera *camera;
};

