#include "input/InputManager.h"

int GibEngine::Input::InputManager::keyboardState[GLFW_KEY_LAST] = { 0 };
GibEngine::Input::Controller* GibEngine::Input::InputManager::controllers[GLFW_JOYSTICK_LAST] = { 0 };
glm::vec2 GibEngine::Input::InputManager::mouseState = glm::vec2();
glm::vec2 GibEngine::Input::InputManager::scrollState = glm::vec2();

GibEngine::Input::InputManager::InputManager(GLFWwindow *window)
{
	if (window != nullptr)
	{
		glfwSetJoystickCallback(this->ControllerConnectionCallback);
		glfwSetKeyCallback(window, this->KeyCallback);
		glfwSetCursorPosCallback(window, this->MouseCallback);
	}
}

void GibEngine::Input::InputManager::ControllerConnectionCallback(int controllerId, int event)
{
	Controller *controller = controllers[controllerId];
	if (controller == nullptr)
	{
		controller = new Controller(controllerId, event == GLFW_CONNECTED);
	}

	switch (event)
	{
	case GLFW_CONNECTED:
		controller->SetConnected(true);
	case GLFW_DISCONNECTED:
		controller->SetConnected(false);
	}
}

void GibEngine::Input::InputManager::MouseCallback(GLFWwindow * window, double mouseX, double mouseY)
{
	mouseState.x = static_cast<float>(mouseX);
	mouseState.y = static_cast<float>(mouseY);
}

void GibEngine::Input::InputManager::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < GLFW_KEY_LAST)
	{
		keyboardState[key] = action;
	}
}

void GibEngine::Input::InputManager::ScrollCallback(GLFWwindow * window, int offsetX, int offsetY)
{
	scrollState.x = offsetX;
	scrollState.y = offsetY;
}

glm::vec2 GibEngine::Input::InputManager::GetMousePosition() const
{
	return this->mouseState;
}

glm::vec2 GibEngine::Input::InputManager::GetScrollState() const
{
	return this->scrollState;
}

int* GibEngine::Input::InputManager::GetKeyboardState()
{
	return this->keyboardState;
}