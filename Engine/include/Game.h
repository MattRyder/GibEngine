#pragma once

#include <iostream>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "glfw/glfw_callback.h"

#include "File.h"
#include "Model.h"
#include "Shader.h"
#include "Skybox.h"
#include "FreeCamera.h"
#include "PointLight.h"
#include "renderer/Pipeline.h"
#include "input/InputManager.h"

#include "cxxopts.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
 
namespace GibEngine
{
	static const char* ENGINE_NAME = "GibEngine";

	class Game
	{
		GLFWwindow* window;
		const char* windowTitle = ENGINE_NAME;

		float currentFrameTime = 0, lastFrameTime = 0;

		// TODO: MOVE THESE WHEN I CAN SCRIPT/REFACTOR THEM IN
		FreeCamera* playerCamera;
		Model* model;
		Skybox* skybox;
		PointLight* light;

		Renderer::ShaderLanguage shaderLanguage = GibEngine::Renderer::ShaderLanguage::GLSL_420;

		Renderer::Pipeline* renderPipeline;
		Input::InputManager* inputManager;

		void ParseOptions(int argc, char** argv);

	public:
		Game(int argc, char** argv);
		virtual ~Game();

		virtual void Render();
		virtual void Update();

		bool initializeGL(GibEngine::Renderer::ShaderLanguage shaderVersion);
		void ToggleVsync();

		void SetWindowTitle(const char *windowTitle);
		void SetWindowSize(int windowWidth, int windowHeight);

		GLFWwindow* GetWindow();
		glm::vec2 GetWindowSize();
	};
}