#pragma once

#include "gtest/gtest.h"
#include "glm/gtc/matrix_transform.hpp"

#include "FreeCamera.h"

using namespace GibEngine;

class FreeCameraTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    camera = std::unique_ptr<FreeCamera>(new FreeCamera(WIDTH, HEIGHT, Z_NEAR, Z_FAR, FOV));
    camera->LookAt(glm::vec3(0, 10, 0));
  }
  
  std::unique_ptr<FreeCamera> camera;

  const unsigned int WIDTH = 800;
  const unsigned int HEIGHT = 600;
  const float Z_NEAR = 0.1f;
  const float Z_FAR = 500.0f;
  const float FOV = 90.0f; 
};

