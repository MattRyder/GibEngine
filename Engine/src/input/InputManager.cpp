#include "input/InputManager.h"

int GibEngine::Input::InputManager::keyboardState[GLFW_KEY_LAST] = { 0 };
int GibEngine::Input::InputManager::mouseButtonState[GLFW_MOUSE_BUTTON_LAST] = { 0 };
GibEngine::Input::Controller* GibEngine::Input::InputManager::controllers[GLFW_JOYSTICK_LAST] = { 0 };
glm::vec2 GibEngine::Input::InputManager::mouseState = glm::vec2();
glm::vec2 GibEngine::Input::InputManager::scrollState = glm::vec2();
bool GibEngine::Input::InputManager::isUpdatingMouseState = true;
bool GibEngine::Input::InputManager::isUpdatingKeyboardState = true;
bool GibEngine::Input::InputManager::isUpdatingScrollState = true;

GibEngine::Input::InputManager::InputManager(GLFWwindow *window)
{
	if (window != nullptr)
	{
		glfwSetMouseButtonCallback(window, this->MouseButtonCallback);
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
		controllers[controllerId] = new Controller(controllerId, event == GLFW_CONNECTED);
		controller = controllers[controllerId];
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
	if (isUpdatingMouseState)
	{
		mouseState.x = static_cast<float>(mouseX);
		mouseState.y = static_cast<float>(mouseY);
	}
}

void GibEngine::Input::InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
	{
		mouseButtonState[button] = action;
	}
}

void GibEngine::Input::InputManager::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (isUpdatingKeyboardState && key >= 0 && key < GLFW_KEY_LAST)
	{
		keyboardState[key] = action;
	}
}

void GibEngine::Input::InputManager::ScrollCallback(GLFWwindow * window, int offsetX, int offsetY)
{
	if (isUpdatingScrollState)
	{
		scrollState.x = offsetX;
		scrollState.y = offsetY;
	}
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

const int* GibEngine::Input::InputManager::GetMouseButtonState() const
{
	return mouseButtonState;
}

bool GibEngine::Input::InputManager::GetUpdatingMouseState() const
{
	return isUpdatingMouseState;
}

bool GibEngine::Input::InputManager::GetUpdatingKeyboardState() const
{
	return isUpdatingKeyboardState;
}

bool GibEngine::Input::InputManager::GetUpdatingScrollState() const
{
	return isUpdatingScrollState;
}

void GibEngine::Input::InputManager::SetUpdatingMouseState(bool isUpdatingMouseState)
{
	this->isUpdatingMouseState = isUpdatingMouseState;
}

void GibEngine::Input::InputManager::SetUpdatingScrollState(bool isUpdatingScrollState)
{
	this->isUpdatingScrollState = isUpdatingScrollState;
}

void GibEngine::Input::InputManager::SetUpdatingKeyboardState(bool isUpdatingKeyboardState)
{
	this->isUpdatingKeyboardState = isUpdatingKeyboardState;
}
