#include "glfw/glfw_callback.h"

void GlfwErrorCallback(int error, const char* description)
{
  GibEngine::Logger::Instance->info( "GLFW reported {}: {}", error, description);
}

void GlfwSetWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    GibEngine::Logger::Instance->info("Window Resized: {} x {}", width, height);
}

void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::string errString;

    switch(source)
    {
        case 0x8246: errString = "API"; break;
        case 0x8247: errString = "WINDOW_SYSTEM"; break;
        case 0x8248: errString = "SHADER_COMPILER"; break;
        case 0x8249: errString = "THIRD_PARTY"; break;
        case 0x824A: errString = "APPLICATION"; break;
        case 0x824B: errString = "OTHER"; break;
        default: errString = "undefined"; break;
    }
}