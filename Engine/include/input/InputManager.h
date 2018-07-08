#pragma once

#include <glm/vec2.hpp>

#include "Controller.h"
#include "event/EventManager.h"
#include "event/InputEvents.h"

namespace GibEngine
{
	namespace Input
	{
		class InputManager
		{
			static std::vector<std::shared_ptr<Controller>> controllers;

			static Event::EventManager* GetEventManager(GLFWwindow* window);

		public:
			InputManager(GLFWwindow* window);

			static void ControllerConnectionCallback(int controllerId, int event);
			static void MouseCallback(GLFWwindow *window, double mouseX, double mouseY);
			static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void ScrollCallback(GLFWwindow *window, double offsetX, double offsetY);

			void Install(GLFWwindow* window);
		};
	}
}