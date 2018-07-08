#include "input/InputManager.h"

std::vector<std::shared_ptr<GibEngine::Input::Controller>> GibEngine::Input::InputManager::controllers;

GibEngine::Event::EventManager* GibEngine::Input::InputManager::GetEventManager(GLFWwindow* window)
{
	return reinterpret_cast<Event::EventManager*>(glfwGetWindowUserPointer(window));
}

GibEngine::Input::InputManager::InputManager(GLFWwindow* window)
{
	Install(window);
}

void GibEngine::Input::InputManager::ControllerConnectionCallback(int controllerId, int event)
{
	auto controller = controllers[controllerId];
	if (!controller)
	{
		controllers[controllerId] = std::make_shared<Controller>(controllerId, event == GLFW_CONNECTED);
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

void GibEngine::Input::InputManager::MouseCallback(GLFWwindow* window, double mouseX, double mouseY)
{
	auto mouseMoveEvent = std::make_shared<Event::MouseMoveEvent>(glm::vec2(mouseX, mouseY));
	GetEventManager(window)->Raise(mouseMoveEvent);
}

void GibEngine::Input::InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::shared_ptr<Event::IEvent> btnEvent;

	switch (action)
	{
	case GLFW_PRESS:
		btnEvent = std::make_shared<Event::MouseButtonDownEvent>(button);
		break;
	case GLFW_RELEASE:
		btnEvent = std::make_shared<Event::MouseButtonUpEvent>(button);
		break;
	}

	GetEventManager(window)->Raise(btnEvent);
}

void GibEngine::Input::InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::shared_ptr<Event::IEvent> keyEvent;

	switch (action)
	{
	case GLFW_PRESS:
		keyEvent = std::make_shared<Event::KeyDownEvent>(key, scancode);
		break;
	case GLFW_RELEASE:
		keyEvent = std::make_shared<Event::KeyUpEvent>(key, scancode);
		break;
	default:
		return;
	}

	GetEventManager(window)->Raise(keyEvent);
}

void GibEngine::Input::InputManager::ScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
	GetEventManager(window)->Raise(std::make_shared<Event::ScrollEvent>(glm::vec2(offsetX, offsetY)));
}

void GibEngine::Input::InputManager::Install(GLFWwindow* window)
{
	if (window != nullptr)
	{
		glfwSetMouseButtonCallback(window, this->MouseButtonCallback);
		glfwSetJoystickCallback(this->ControllerConnectionCallback);
		glfwSetKeyCallback(window, this->KeyCallback);
		glfwSetCursorPosCallback(window, this->MouseCallback);
		glfwSetScrollCallback(window, this->ScrollCallback);
	}
}