#include "glfw/glfw_callback.h"

void APIENTRY GibEngine::GLFW::GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
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

	errString += " ";

	switch (type)
	{
		case 0x824C: errString += "ERROR"; break;
		case 0x824D: errString += "DEPRECATED_BEHAVIOUR"; break;
		case 0x824E: errString += "UNDEFINED_BEHAVIOR"; break;
		case 0x824F: errString += "PORTABILITY"; break;
		case 0x8250: errString += "PERFORMANCE"; break;
		case 0x8251: errString += "OTHER"; break;
		case 0x8268: errString += "MARKER"; break;
		case 0x8269: errString += "PUSH_GROUP"; break;
		case 0x826A: errString += "POP_GROUP"; break;
		default: errString += "undefined"; break;
	}

	errString += " ";

	if (type == GL_DEBUG_TYPE_OTHER) return;

	GibEngine::Logger::Instance->info("OpenGL: {} [ID: {}] [{}]", errString.c_str(), id, message);
}

GibEngine::GLFW::_WindowResizeEvent GibEngine::GLFW::WindowResizeEvent = { 0 };

void GibEngine::GLFW::ErrorCallback(int error, const char* description)
{
	Logger::Instance->info("GLFW reported {}: {}", error, description);
}

void GibEngine::GLFW::SetWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	Logger::Instance->info("Window Resize Called: {} x {}", width, height);

	if (width <= 0 && height <= 0)
	{
		return;
	}

	WindowResizeEvent.Raised = true;
	WindowResizeEvent.Width = width;
	WindowResizeEvent.Height = height;
	WindowResizeEvent.ResizeFramebuffer = true;

	glViewport(0, 0, width, height);
}
