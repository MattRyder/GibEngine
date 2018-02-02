
#include <iostream>
//#include <vld.h>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "glfw/glfw_callback.h"

#include "File.h"
#include "Shader.h"
#include "Skybox.h"
#include "FreeCamera.h"
#include "ChaseCamera.h"
#include "PointLight.h"
#include "renderer/Pipeline.h"
#include "input/InputManager.h"
#include "world/Database.h"

#include "cxxopts.hpp"

namespace GibEngine
{
	static const char* ENGINE_NAME = "GibEngine";

	class Game
	{
		struct Config
		{
			bool vsyncEnabled;
		};

		Config config;
		GLFWwindow* window;
		const char* windowTitle = ENGINE_NAME;

		float fpsIntervalTimer;
		float lastFrameTime;
		float deltaTime;

		int frameCounter;
		int framesPerSecond;
		glm::vec2 requestedWindowSize;

		// TODO: MOVE THESE WHEN I CAN SCRIPT/REFACTOR THEM IN
		FreeCamera* playerCamera = nullptr;
		//ChaseCamera* chaseCamera = nullptr;

		void ParseOptions(int argc, char** argv);

	protected:
		Renderer::ShaderLanguage shaderLanguage = Renderer::ShaderLanguage::GLSL_420;
		
		Scene::Node* rootSceneNode = nullptr;
		Scene::VisibleSet* visibleSet;
		
		Renderer::Pipeline* renderPipeline = nullptr;
		Input::InputManager* inputManager = nullptr;

		Scene::Node* CreateWorld();

	public:
		Game(int argc, char** argv);
		virtual ~Game();

		virtual void Render();
		virtual void Update();

		virtual void SetupPipeline();

		bool InitializeGL(GibEngine::Renderer::ShaderLanguage shaderVersion);

		void ToggleVsync();

		void SetWindowTitle(const char* windowTitle);
		void SetWindowSize(int windowWidth, int windowHeight);
		void SetSceneRoot(Scene::Node* rootSceneNode);

		GLFWwindow* GetWindow();
		Renderer::Pipeline* GetRenderPipeline() const;
		Input::InputManager* GetInputManager() const;
		float GetDeltaTime() const;
		int GetFramesPerSecond() const;
	};
}