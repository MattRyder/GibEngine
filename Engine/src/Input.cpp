#include "Input.h"
#include "Logger.h"

int GibEngine::Input::KeyboardState[GLFW_KEY_LAST] = { 0 };
glm::vec2 GibEngine::Input::MouseState;

GibEngine::Input::Input(int controllerId) : controllerId(controllerId) {}

int GibEngine::Input::GetControllerId()
{
    return this->controllerId;
}

void GibEngine::Input::UpdateMousePositionCallback(GLFWwindow * window, double mouseX, double mouseY)
{
    MouseState.x = static_cast<float>(mouseX);
    MouseState.y = static_cast<float>(mouseY);
}

void GibEngine::Input::UpdateKeyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < GLFW_KEY_LAST)
    {
        KeyboardState[key] = action;
    }
}