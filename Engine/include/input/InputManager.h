#pragma once

#include <glm/vec2.hpp>

#include "Controller.h"


namespace GibEngine
{
	namespace Input
	{
		class InputManager
		{
			static Controller* controllers[GLFW_JOYSTICK_LAST];

			static glm::vec2 mouseState;
			static glm::vec2 scrollState;
			static int keyboardState[GLFW_KEY_LAST];

		public:
			InputManager(GLFWwindow *window);

			static void ControllerConnectionCallback(int controllerId, int event);
			static void MouseCallback(GLFWwindow *window, double mouseX, double mouseY);
			static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void ScrollCallback(GLFWwindow *window, int offsetX, int offsetY);

			glm::vec2 GetMousePosition() const;
			glm::vec2 GetScrollState() const;
			int* GetKeyboardState();
		};
	}
}