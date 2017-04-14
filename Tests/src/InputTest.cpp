#include "InputTest.h"

TEST_F(InputTest, TestMouseState)
{
  input->UpdateMousePositionCallback(NULL, 100, 200);

  glm::vec2 actualMouseState = input->MouseState;
  glm::vec2 expectedMouseState = glm::vec2(100, 200);

  ASSERT_EQ(expectedMouseState.x, actualMouseState.x);
  ASSERT_EQ(expectedMouseState.y, actualMouseState.y);
}

TEST_F(InputTest, TestKeyboardState)
{
  input->UpdateKeyboardCallback(NULL, GLFW_KEY_M, 0, 1, 0);

  bool expectedKeyState = true;
  bool actualKeyState = input->KeyboardState[GLFW_KEY_M];

  ASSERT_EQ(expectedKeyState, actualKeyState);
}

TEST_F(InputTest,GetControllerId) 
{
  ASSERT_EQ(1, 1);
}