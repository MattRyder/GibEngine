
#include <iostream>
//#include <vld.h>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "glfw/glfw_callback.h"

#include "File.h"
#include "Model.h"
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
		GLFWwindow* window;
		const char* windowTitle = ENGINE_NAME;

		float lastFrameTime = 0;
		glm::vec2 requestedWindowSize;

		// TODO: MOVE THESE WHEN I CAN SCRIPT/REFACTOR THEM IN
		FreeCamera* playerCamera = nullptr;
		//ChaseCamera* chaseCamera = nullptr;

		void ParseOptions(int argc, char** argv);

	protected:
		Renderer::ShaderLanguage shaderLanguage = Renderer::ShaderLanguage::GLSL_420;
		
		Scene::Node* rootSceneNode = nullptr;
		
		Renderer::Pipeline* renderPipeline = nullptr;
		Input::InputManager* inputManager = nullptr;

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

		GLFWwindow* GetWindow();
		Renderer::Pipeline* GetRenderPipeline() const;
		float GetDeltaTime();
	};
}