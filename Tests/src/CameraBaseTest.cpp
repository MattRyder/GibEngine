#include "CameraBaseTest.h"

TEST_F(CameraBaseTest, CanConstructProjectionMatrix)
{
  glm::mat4* expectedMatrix = new glm::mat4 {
    { 0.347270399, 0, 0, 0 },
    { 0, 0.617369592, 0, 0 },
    { 0, 0, -1.0100503, -1 },
    { 0, 0, -2.0100503, 0 },
  };

  float width = 1920, height = 1080, zFar = 200.0f, zNear = 1.0f, FoV = 90; 
  glm::mat4* actualMatrix = cameraBase->ConstructProjectionMatrix(width, height, zNear, zFar, FoV);
  ASSERT_EQ(*expectedMatrix, *actualMatrix);
}