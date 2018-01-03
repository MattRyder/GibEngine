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
			static int mouseButtonState[GLFW_MOUSE_BUTTON_LAST];

			// Use these to prevent per-frame updates from the input sources
			static bool isUpdatingMouseState;
			static bool isUpdatingScrollState;
			static bool isUpdatingKeyboardState;

		public:
			InputManager(GLFWwindow* window);

			static void ControllerConnectionCallback(int controllerId, int event);
			static void MouseCallback(GLFWwindow *window, double mouseX, double mouseY);
			static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void ScrollCallback(GLFWwindow *window, int offsetX, int offsetY);

			void Install(GLFWwindow* window);

			glm::vec2 GetMousePosition() const;
			glm::vec2 GetScrollState() const;
			int* GetKeyboardState();
			const int* GetMouseButtonState() const;

			bool GetUpdatingMouseState() const;
			bool GetUpdatingKeyboardState() const;
			bool GetUpdatingScrollState() const;

			void SetUpdatingMouseState(bool isUpdatingMouseState);
			void SetUpdatingScrollState(bool isUpdatingScrollState);
			void SetUpdatingKeyboardState(bool isUpdatingKeyboardState);
		};
	}
}