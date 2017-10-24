#pragma once

#ifdef WIN32
#include <windows.h>
#endif

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "Logger.h"

namespace GibEngine
{
	class GLFW
	{
	public:
		// Whether to sync the framebuffer & window size, or keep framebuffer at default size
		static bool ResizeFramebuffer;

		static void ErrorCallback(int error, const char* description);
		static void SetWindowSizeCallback(GLFWwindow* window, int width, int height);
	};
}

void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);