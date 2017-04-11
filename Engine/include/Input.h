#pragma once

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "glm/vec2.hpp"

namespace GibEngine 
{
    class Input
    {
    public:    
        static glm::vec2 MouseState;
        static int KeyboardState[GLFW_KEY_LAST];
        
        static void UpdateMousePositionCallback(GLFWwindow *window, double mouseX, double mouseY);
        static void UpdateKeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    };
}