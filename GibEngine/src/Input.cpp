#include "Input.h"
#include "Logger.h"

int GibEngine::Input::KeyboardState[GLFW_KEY_LAST] = { 0 };
glm::vec2 GibEngine::Input::MouseState;

void GibEngine::Input::UpdateMousePositionCallback(GLFWwindow * window, double mouseX, double mouseY)
{
    //Logger::Instance->info("Mouse: {} {}", mouseX, mouseY);
    MouseState.x = static_cast<float>(mouseX);
    MouseState.y = static_cast<float>(mouseY);
}

void GibEngine::Input::UpdateKeyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < GLFW_KEY_LAST)
    {
        //if (action == GLFW_PRESS)
        //    Logger::Instance->info("Keyboard State: {0} pressed", key);
        //else if (action == GLFW_RELEASE)
        //    Logger::Instance->info("Keyboard State: {0} released", key);
        //else if (action == GLFW_REPEAT)
        //    Logger::Instance->info("Keyboard State: {0} held down", key);
        
        KeyboardState[key] = action;
    }
}