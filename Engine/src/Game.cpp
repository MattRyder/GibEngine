﻿#include "Game.h"

GibEngine::Game::Game(int argc, char** argv)
{
	this->ParseOptions(argc, argv);

	if (!initializeGL(shaderLanguage))
	{
		Logger::Instance->error("Failed to initialize OpenGL!");
		return;
	}

	if (GL_KHR_debug)
	{
		GibEngine::Logger::Instance->info("GL_KHR_debug extension available");
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//glDebugMessageCallback(GLDebugCallback, GLDebugCallback);

		GibEngine::Logger::Instance->info("GL_KHR_debug extension enabled");
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);

	this->playerCamera = new FreeCamera(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 2500.0f, 45.0f);
	this->playerCamera->SetPosition(glm::vec3(0, 15, 0));
	this->playerCamera->LookAt(0, 0, 0);

	this->inputManager = new Input::InputManager(window);

	PointLight* light = new PointLight(
		glm::vec3(0, 5.0f, 0),
		glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.9f, 0.9f, 0.9f),
		-3.8f,
		1.5f);

	this->worldDb = new World::Database("demo.gwo");

	if(!true)
	{
		// Keep to rebuild a demo world when schema changes:
		GibEngine::Model* model = new GibEngine::Model("woodhouse/woodhouse.obj");
		glm::mat4 inst = glm::mat4();
		inst = glm::scale(inst, glm::vec3(3.0f, 3.0f, 3.0f));
		model->AddInstance(inst);
		World::Level* lvl = worldDb->CreateLevel("E1M1: At Doom's Gate");
		lvl->AddModel(model);

		Skybox* skybox = new Skybox("stormy", "png");
		lvl->SetSkybox(skybox);

		worldDb->SaveLevel(lvl);		
	}

	World::Level* savedLevel = worldDb->FindLevel(1);

	// Set the Render pipeline up with known OpenGL supported types:
	this->renderPipeline = new Renderer::Pipeline(WINDOW_WIDTH, WINDOW_HEIGHT, shaderLanguage, playerCamera);

	Renderer::RenderPass* deferredGeoPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_GEOMETRY);	
	for(auto m : savedLevel->GetModels())
	{
		deferredGeoPass->AddDrawable(m);
	}

	Renderer::RenderPass* deferredLightingPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_LIGHTING);

	int b = 3;	
	for(int x = -b; x < b; x++)
		for (int y = -b; y < b; y++)
		{
			PointLight* lightDup = new PointLight(*light);
			lightDup->SetPosition(glm::vec3(1 * 2.5, 7.5, 1 * 2.5));

			float r = rand() % 100 / 100.0;
			float g = rand() % 100 / 100.0;
			float bb = rand() % 100 / 100.0;

			lightDup->SetDiffuseColor(glm::vec3(r, g, bb));
			deferredLightingPass->AddLight(lightDup);
		}

	 Renderer::RenderPass* renderPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::SKYBOX);	
	 Renderer::SkyboxRenderPass *skyboxPass = reinterpret_cast<Renderer::SkyboxRenderPass*>(renderPass);
	 skyboxPass->SetSkybox(savedLevel->GetSkybox());
}

GibEngine::Game::~Game()
{
	glfwDestroyWindow(this->window);
	delete this->windowTitle;
}

void GibEngine::Game::Render()
{
	this->renderPipeline->Render();
	Update();
}

void GibEngine::Game::Update()
{
	currentFrameTime = static_cast<float>(glfwGetTime());
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	this->playerCamera->Update(deltaTime, inputManager->GetMousePosition(), inputManager->GetScrollState(), inputManager->GetKeyboardState());

	if (inputManager->GetKeyboardState()[GLFW_KEY_T])
	{
		this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_LIGHTING)->TakeScreenshot();
	}

	this->renderPipeline->Update(deltaTime);

	glfwPollEvents();
}

bool GibEngine::Game::initializeGL(GibEngine::Renderer::ShaderLanguage shaderLanguage)
{
	int glfwInitResult = glfwInit();
	if (glfwInitResult != GL_TRUE)
	{
		return false;
	}

	switch(shaderLanguage)
	{
		case GibEngine::Renderer::ShaderLanguage::GLES_3:
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			break;
		case GibEngine::Renderer::ShaderLanguage::GLSL_420:
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 16);
			break;
	}

	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, this->windowTitle, nullptr, nullptr);

	// Setup GLFW callbacks:
	GLFW::ResizeFramebuffer = true;
	glfwSetErrorCallback(GLFW::ErrorCallback);
	//glfwSetFramebufferSizeCallback(window, GLFW::SetWindowSizeCallback);
	glfwSetWindowSizeCallback(window, GLFW::SetWindowSizeCallback);

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

	return true;
}

void GibEngine::Game::ParseOptions(int argc, char** argv)
{
	cxxopts::Options opts(argv[0]);

	opts.add_options()
		("v,version", "Returns the current GibEngine version")
		("h,help", "Outputs this help text");

	opts.add_options("Game")
		("title", "Set the window title", cxxopts::value<std::string>());

	opts.add_options("Rendering")
		("gles", "Use OpenGL ES 3 Client API")
		("gl420", "User OpenGL 4.0 Core Client API");

	opts.parse(argc, argv);

	if(opts.count("help") > 0)
	{
		Logger::Instance->info(opts.help({"", "Game", "Rendering"}).c_str());
	}

	if(opts.count("gles") > 0)
	{
		shaderLanguage = Renderer::ShaderLanguage::GLES_3;
	}

	if(opts.count("gl420") > 0)
	{
		shaderLanguage = Renderer::ShaderLanguage::GLSL_420;
	}

	std::string title = opts["title"].as<std::string>();
	std::string *windowTitle = new std::string(title);
	if(title.size() > 0)
	{
		this->SetWindowTitle(windowTitle->c_str());
	}
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