#include "Game.h"

GibEngine::Game::Game(const char *windowTitle)
{
	this->windowTitle = windowTitle;

	if (!initializeGL())
	{
		Logger::Instance->error("Failed to initialize OpenGL!");
		return;
	}

	if (GL_KHR_debug)
	{
		GibEngine::Logger::Instance->info("GL_KHR_debug extension available");
		//glDebugMessageCallback(GLDebugCallback, GLDebugCallback);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		GibEngine::Logger::Instance->info("GL_KHR_debug extension enabled");
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);

	this->playerCamera = new FreeCamera(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 250.0f, 65.0f);
	this->playerCamera->LookAt(0, 0, 0);
	this->model = new Model("brickwall/brickwall.obj");
	//this->model = new Model("teapot/teapot.obj");
	//this->model = new Model("ruin/ruin.obj");
	//this->model = new Model("sponza/sponza.obj");

	this->skybox = new Skybox("default", "png");

	glm::mat4 modelMatrix;
	int a = 64;
	for (int x = -a; x < a; x++)
		for (int y = -a; y < a; y++)
		{
			modelMatrix = glm::mat4();
			modelMatrix[3] = glm::vec4(x * 5, rand() % 10, y * 5, 1.0);
			this->model->AddInstance(modelMatrix);
		}

	//Renderer::RenderPass* colorPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::FORWARD_LIGHTING);
	//colorPass->SetCameraBase(playerCamera);
	//colorPass->AddDrawable(model);

	Renderer::RenderPass* deferredGeoPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_GEOMETRY);
	deferredGeoPass->SetCameraBase(playerCamera);
	deferredGeoPass->AddDrawable(model);

	Renderer::RenderPass* deferredLightingPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_LIGHTING);

	//Renderer::RenderPass* renderPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::SKYBOX);
	//Renderer::SkyboxRenderPass *skyboxPass = reinterpret_cast<Renderer::SkyboxRenderPass*>(renderPass);
	//skyboxPass->SetSkybox(this->skybox);
}

GibEngine::Game::~Game()
{
	glfwDestroyWindow(this->window);
	delete this->windowTitle;
}

void GibEngine::Game::Render()
{
	this->renderPipeline->Render();

	glfwSwapBuffers(window);
	Update();
}

void GibEngine::Game::Update()
{
	currentFrameTime = static_cast<float>(glfwGetTime());
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	this->playerCamera->Update(deltaTime, GibEngine::Input::MouseState.x, GibEngine::Input::MouseState.y, GibEngine::Input::KeyboardState);

	this->renderPipeline->Update(deltaTime);

	glfwPollEvents();
}

bool GibEngine::Game::initializeGL()
{
	int glfwInitResult = glfwInit();
	if (glfwInitResult != GL_TRUE)
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, this->windowTitle, NULL, NULL);

	// Setup GLFW callbacks:
	glfwSetKeyCallback(window, GibEngine::Input::UpdateKeyboardCallback);
	glfwSetCursorPosCallback(window, GibEngine::Input::UpdateMousePositionCallback);
	glfwSetErrorCallback(GlfwErrorCallback);
	glfwSetFramebufferSizeCallback(window, GlfwSetWindowSizeCallback);

	if (!this->window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit())
	{
		return false;
	}

	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	Logger::Instance->info("Renderer: {}", renderer);
	Logger::Instance->info("OpenGL Version: {} - GLSL Version: {}", version, glslVersion);

	GibEngine::Renderer::UniformBufferManager *uniformBufferManager = new GibEngine::Renderer::UniformBufferManager();
	GibEngine::Renderer::Framebuffer *framebuffer = new GibEngine::Renderer::Framebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Set the Render pipeline up with known OpenGL supported types:
	this->renderPipeline = new Renderer::Pipeline(uniformBufferManager, framebuffer, GibEngine::Renderer::ShaderLanguage::GLSL_420);

	return true;
}

void GibEngine::Game::ToggleVsync() { }

GLFWwindow* GibEngine::Game::GetWindow()
{
	return this->window;
}

void GibEngine::Game::SetWindowTitle(const char *windowTitle)
{
	this->windowTitle = windowTitle;
	glfwSetWindowTitle(this->window, this->windowTitle);
}

void GibEngine::Game::SetWindowSize(int windowWidth, int windowHeight)
{
	windowWidth = windowWidth > 1 ? windowWidth : 1;
	windowHeight = windowHeight > 1 ? windowHeight : 1;
	glfwSetWindowSize(this->window, windowWidth, windowHeight);
}