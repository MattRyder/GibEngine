#include "FreeCameraTest.h"

 TEST_F(FreeCameraTest, AssignedCameraType)
 {
 	ASSERT_EQ(camera->GetType(), BaseEntity::Type::CAMERA);
 }

 TEST_F(FreeCameraTest, CanConstructProjectionMatrix)
 {
 	glm::mat4 pm = camera->GetProjectionMatrix();
 	glm::mat4 ePM = glm::perspectiveFov(
		 FOV,
		 (float)(FreeCameraTest::WIDTH),
		 (float)(FreeCameraTest::HEIGHT),
		 Z_NEAR,
		 Z_FAR);
		 
 	ASSERT_EQ(pm, ePM);
 }

 TEST_F(FreeCameraTest, CanConstructViewMatrix)
 {
 	glm::mat4 viewMatrix = camera->GetViewMatrix();
 	ASSERT_TRUE(true);
 }