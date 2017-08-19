#include "InputManagerTest.h"

TEST_F(InputManagerTest, TestMouseState)
{
	inputManager->MouseCallback(nullptr, 100, 200);

	glm::vec2 actualMouseState = inputManager->GetMousePosition();
	glm::vec2 expectedMouseState = glm::vec2(100, 200);

	ASSERT_EQ(expectedMouseState.x, actualMouseState.x);
	ASSERT_EQ(expectedMouseState.y, actualMouseState.y);
}

TEST_F(InputManagerTest, TestKeyboardState)
{
	inputManager->KeyCallback(nullptr, GLFW_KEY_M, 0, 1, 0);

	int expectedKeyState = 1;
	int actualKeyState = inputManager->GetKeyboardState()[GLFW_KEY_M];

	ASSERT_EQ(expectedKeyState, actualKeyState);
}

TEST_F(InputManagerTest, TestScrollState)
{
	inputManager->ScrollCallback(nullptr, 25, 50);
	glm::vec2 scrollState = inputManager->GetScrollState();

	ASSERT_EQ(scrollState.x, 25);
	ASSERT_EQ(scrollState.y, 50);
}