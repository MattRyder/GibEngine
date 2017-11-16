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
#include "world/Database.h"

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
		FreeCamera* playerCamera = nullptr;
		PointLight* light = nullptr;

		void ParseOptions(int argc, char** argv);

	protected:
		Renderer::ShaderLanguage shaderLanguage = Renderer::ShaderLanguage::GLSL_420;
		Renderer::Pipeline* renderPipeline = nullptr;
		Input::InputManager* inputManager = nullptr;

	public:
		Game(int argc, char** argv);
		virtual ~Game();

		virtual void Render();
		virtual void Update();

		virtual void LoadLevel(World::Level* level);

		bool initializeGL(GibEngine::Renderer::ShaderLanguage shaderVersion);
		void ToggleVsync();

		void SetWindowTitle(const char* windowTitle);
		void SetWindowSize(int windowWidth, int windowHeight);

		GLFWwindow* GetWindow();
		Renderer::Pipeline* GetRenderPipeline() const;
	};
}