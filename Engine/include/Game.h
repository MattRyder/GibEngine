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

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

namespace GibEngine
{
	class Game
	{
		GLFWwindow *window;
		const char *windowTitle;

		float currentFrameTime = 0, lastFrameTime = 0;

		// TODO: MOVE THESE WHEN I CAN SCRIPT/REFACTOR THEM IN
		FreeCamera *playerCamera;
		Model *model;
		Skybox *skybox;
		PointLight *light;

		Renderer::Pipeline *renderPipeline;
		Input::InputManager *inputManager;

	public:
		Game(const char *windowTitle);
		virtual ~Game();

		virtual void Render();
		virtual void Update();

		bool initializeGL();
		void ToggleVsync();

		void SetWindowTitle(const char *windowTitle);
		void SetWindowSize(int windowWidth, int windowHeight);

		GLFWwindow* GetWindow();
	};
}