
#include <iostream>
//#include <vld.h>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "glfw/glfw_callback.h"

#include "Shader.h"
#include "Skybox.h"
#include "FreeCamera.h"
#include "PointLight.h"
#include "renderer/Pipeline.h"
#include "input/InputManager.h"
#include "world/Database.h"

#ifdef WIN32
#include "filesystem/WindowsFileSystem.h"
#elif UNIX
#include "filesystem/UnixFileSystem.h"
#endif

#include "cxxopts.hpp"

namespace GibEngine
{
	static const std::string ENGINE_NAME = "GibEngine";

	class Game
	{
		struct Config
		{
			bool vsyncEnabled;
		};

		GLFWwindow* window;
		std::string windowTitle = ENGINE_NAME;

		float fpsIntervalTimer;
		float lastFrameTime;
		float deltaTime;

		int frameCounter;
		int framesPerSecond;
		glm::vec2 requestedWindowSize;

		// TODO: MOVE THESE WHEN I CAN SCRIPT/REFACTOR THEM IN
		FreeCamera* playerCamera = nullptr;

		void ParseOptions(int argc, char** argv);

	protected:
		Config config;
		Renderer::ShaderLanguage shaderLanguage = Renderer::ShaderLanguage::GLSL_420;
		
		std::shared_ptr<Scene::Node> rootSceneNode;
		std::shared_ptr<Scene::VisibleSet> vset;
		
		Input::InputManager* inputManager = nullptr;

		std::shared_ptr<Renderer::Pipeline> pipeline;
		std::shared_ptr<CameraBase> playerCameraSP;
		std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi;
		std::shared_ptr<FileSystem::IFileSystem> fileSystem;

		std::shared_ptr<Scene::Node> CreateWorld();

	public:
		Game(int argc, char** argv);
		virtual ~Game();

		virtual void Render();
		virtual void Update();

		virtual void SetupPipeline();

		bool InitializeGL(GibEngine::Renderer::ShaderLanguage shaderVersion);

		void ToggleVsync();

		void SetWindowTitle(const std::string windowTitle);
		void SetWindowSize(int windowWidth, int windowHeight);
		void SetSceneRoot(std::shared_ptr<Scene::Node> rootSceneNode);

		GLFWwindow* GetWindow();
		std::shared_ptr<GibEngine::Renderer::Pipeline> GetRenderPipeline() const;
		Input::InputManager* GetInputManager() const;

		std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> GetGraphicsApi() const;
		std::shared_ptr<GibEngine::FileSystem::IFileSystem> GetFileSystem() const;
		std::shared_ptr<Scene::Node> GetSceneNodeRoot() const;

		float GetDeltaTime() const;
		int GetFramesPerSecond() const;

		bool IsMinimized() const;
	};
}