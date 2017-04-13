#pragma once

#include "GLFW/glfw3.h"
#include "Logger.h"

void GlfwErrorCallback(int error, const char* description);
void GlfwSetWindowSizeCallback(GLFWwindow* window, int width, int height);
void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);