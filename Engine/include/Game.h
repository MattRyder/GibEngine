
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
#include "event/EventManager.h"
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

		void ParseOptions(int argc, char** argv);

	protected:
		Config config;
		Renderer::ShaderLanguage shaderLanguage = Renderer::ShaderLanguage::GLSL_420;
		
		std::shared_ptr<BaseEntity> rootEntity;
		std::shared_ptr<Scene::VisibleSet> vset;
		
		std::shared_ptr<BaseEntity> activeEntity;

		std::shared_ptr<Renderer::Pipeline> pipeline;
		std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi;
		std::shared_ptr<FileSystem::IFileSystem> fileSystem;
		std::shared_ptr<Input::InputManager> inputManager;
		std::shared_ptr<Event::EventManager> eventManager;
		std::shared_ptr<FreeCamera> playerCamera;

		std::shared_ptr<BaseEntity> CreateWorld();

	public:
		Game(int argc, char** argv);
		virtual ~Game();

		virtual void Render();
		virtual void Update();

		virtual void SetupPipeline();

		bool InitializeGraphics(Renderer::ShaderLanguage shaderVersion);

		void ToggleVsync();

		void SetWindowTitle(const std::string windowTitle);
		void SetWindowSize(int windowWidth, int windowHeight);
		void SetSceneRoot(std::shared_ptr<BaseEntity> rootEntity);

		GLFWwindow* GetWindow() const;
		std::shared_ptr<GibEngine::Renderer::Pipeline> GetRenderPipeline() const;
		std::shared_ptr<Input::InputManager> GetInputManager() const;

		std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> GetGraphicsApi() const;
		std::shared_ptr<GibEngine::FileSystem::IFileSystem> GetFileSystem() const;
		std::shared_ptr<BaseEntity> GetRootEntity() const;

		float GetDeltaTime() const;
		int GetFramesPerSecond() const;

		bool IsMinimized() const;
	};
}