#include "input/Controller.h"

GibEngine::Input::Controller::Controller(int controllerId)
	: Controller(controllerId, false) { }

GibEngine::Input::Controller::Controller(int controllerId, bool connected)
	: controllerId(controllerId), connected(connected), axisCount(0), buttonCount(0) { }

void GibEngine::Input::Controller::Poll(float deltaTime)
{
	const float* axes = glfwGetJoystickAxes(this->controllerId, &axisCount);
	const unsigned char* buttons = glfwGetJoystickButtons(this->controllerId, &buttonCount);

	//if (axes != nullptr)
	//{
	//	for (int i = 0; i < axisCount; i++)
	//	{
	//		float axisValue = axes[i];
	//		Logger::Instance->info("Axis {} Value: {}", i, axisValue);
	//	}
	//}

	//if (buttons != nullptr)
	//{
	//	for (int i = 0; i < buttonCount; i++)
	//	{
	//		unsigned char buttonState = buttons[i];
	//		if (buttonState == GLFW_PRESS)
	//		{
	//			Logger::Instance->info("Button Press: {}", i);
	//		}
	//	}
	//}
}

bool GibEngine::Input::Controller::IsConnected() const
{
	return this->connected;
}

int GibEngine::Input::Controller::GetControllerId() const
{
	return this->controllerId;
}

void GibEngine::Input::Controller::SetConnected(bool value)
{
	this->connected = value;
}
