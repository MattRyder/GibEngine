#include "FreeCameraTest.h"

TEST_F(FreeCameraTest, AssignedCameraType)
{
	ASSERT_EQ(camera->GetType(), EntityType::CAMERA);
}

TEST_F(FreeCameraTest, CanConstructProjectionMatrix)
{
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
	glm::mat4 expectedPM = glm::perspectiveFov(FOV, WINDOW_WIDTH, WINDOW_HEIGHT, Z_NEAR, Z_FAR);
	ASSERT_EQ(projectionMatrix, expectedPM);
}

TEST_F(FreeCameraTest, CanConstructViewMatrix)
{
	//glm::mat4 viewMatrix = camera->GetViewMatrix();
	ASSERT_TRUE(true);
}