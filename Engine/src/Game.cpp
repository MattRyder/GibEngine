#include "Game.h"

GibEngine::Game::Game(int argc, char** argv)
	: deltaTime(0), framesPerSecond(0), lastFrameTime(0), fpsIntervalTimer(0), frameCounter(0), visibleSet(new Scene::VisibleSet(nullptr, nullptr))
{
	this->ParseOptions(argc, argv);

	if (!InitializeGL(shaderLanguage))
	{
		Logger::Instance->error("Failed to initialize OpenGL!");
		return;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	this->playerCamera = new FreeCamera(requestedWindowSize.x, requestedWindowSize.y, 0.1f, 2500.0f, 45.0f);
	this->playerCamera->SetPosition(glm::vec3(15, 15, 0));
	this->playerCamera->LookAt(0, 0, 0);


	this->inputManager = new Input::InputManager(window);

	SetupPipeline();
	glfwSwapInterval(1);


	if(!true)
	{
		GibEngine::World::Database* worldDb = new World::Database("demo_nodes.gwo");

		Skybox* skybox = new Skybox("stormy", "png");

		PointLight* light = new PointLight(
			glm::vec3(0, 1.65f, 0),
			glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.9f, 0.9f, 0.9f),
			0.75f, // -1.0 -- 1.0
			1.0f); // 0.0 -- 1.0

		Scene::Node* rootNode = new Scene::Node("Root Node");

		// Create the Scene graph for the demo world:
		Scene::Node* skyboxNode = new Scene::Node("Skybox");
		skyboxNode->SetEntity(skybox);
		rootNode->AddChildNode(skyboxNode);

		// Create a Point Light node within the Scene:
		Scene::Node* pointLightNode = new Scene::Node("Test Point Light");
		pointLightNode->SetEntity(light);
		glm::mat4 lightPos = glm::mat4();
		lightPos[3] = glm::vec4(0.0f, 1.65f, 2.0f, 1.0f);
		pointLightNode->SetLocalTransform(lightPos);
		rootNode->AddChildNode(pointLightNode);
		
		// Create a Model node:
		File* modelFile = File::GetModelFile("brickwall/brickwall.obj");
		Scene::Node* meshNode = MeshService::Load(modelFile, nullptr);
		glm::mat4 meshPos = glm::scale(glm::mat4(), glm::vec3(2.0f));
		meshNode->SetLocalTransform(meshPos);
		rootNode->AddChildNode(meshNode);

		if (worldDb->SaveLevel(rootNode))
		{
			// TODO: attach rootNode to new Level record
		}
	}
}

GibEngine::Game::~Game()
{
	glfwDestroyWindow(window);
	glfwTerminate();

	delete inputManager;
	delete renderPipeline;
	delete playerCamera;
}

void GibEngine::Game::Render()
{
	// Generate the delta for the previous and this frame:
	float currentFrameTime = static_cast<float>(glfwGetTime());
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	visibleSet = new Scene::VisibleSet(playerCamera, rootSceneNode);
	
	if (fpsIntervalTimer > 1.0f)
	{
		framesPerSecond = frameCounter;
		frameCounter = 0;
		fpsIntervalTimer = 0;

	}
	else
	{
		frameCounter++;
		fpsIntervalTimer += deltaTime;
	}

	if (this->renderPipeline != nullptr)
	{
		
		this->renderPipeline->Render(visibleSet, GetDeltaTime());
	}
}

void GibEngine::Game::Update()
{
	float deltaTime = GetDeltaTime();

	// Handle GLFW state changes
	if (GLFW::WindowResizeEvent.Raised)
	{
		this->renderPipeline->ResizeFramebuffer(GLFW::WindowResizeEvent.Width, GLFW::WindowResizeEvent.Height);
		GLFW::WindowResizeEvent.Raised = false;
	}

	this->playerCamera->Update(deltaTime, inputManager->GetMousePosition(), inputManager->GetScrollState(), inputManager->GetKeyboardState());

	if (inputManager->GetKeyboardState()[GLFW_KEY_F11])
	{
		this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_LIGHTING)->TakeScreenshot();
	}

	if (inputManager->GetKeyboardState()[GLFW_KEY_Q])
	{
		this->renderPipeline->SetRenderPaused(!this->renderPipeline->IsRenderPaused());
	}

	if (this->renderPipeline != nullptr)
	{
		this->renderPipeline->Update(deltaTime);
	}

	glfwPollEvents();
}

void GibEngine::Game::SetupPipeline()
{
	// TODO: Replace with a clearPipeline() func:
	if (this->renderPipeline != nullptr)
	{
		delete this->renderPipeline;
	}

	this->renderPipeline = new Renderer::Pipeline(requestedWindowSize.x, requestedWindowSize.y, shaderLanguage);

	Renderer::RenderPass* deferredGeoPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_GEOMETRY);
	deferredGeoPass->SetPassEnabled(true);
	
	Renderer::RenderPass* deferredLightingPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_LIGHTING);
	deferredLightingPass->SetPassEnabled(true);

	Renderer::RenderPass* renderPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::SKYBOX);
	renderPass->SetPassEnabled(true);

	Renderer::RenderPass* forwardPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::FORWARD_RENDERING);
	forwardPass->SetPassEnabled(true);

	Renderer::RenderPass* renderToTexturePass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::RENDER_TO_TEXTURE);
	renderToTexturePass->SetPassEnabled(true);
}

bool GibEngine::Game::InitializeGL(GibEngine::Renderer::ShaderLanguage shaderLanguage)
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

	this->window = glfwCreateWindow(requestedWindowSize.x, requestedWindowSize.y, this->windowTitle, nullptr, nullptr);

	// Setup GLFW callbacks:
	glfwSetErrorCallback(GLFW::ErrorCallback);
	glfwSetFramebufferSizeCallback(window, GLFW::SetWindowSizeCallback);
	//glfwSetWindowSizeCallback(window, GLFW::SetWindowSizeCallback);

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
	int reqW = 0, reqH = 0;
	cxxopts::Options opts(argv[0]);

	opts.add_options()
		("v,version", "Returns the current GibEngine version")
		("h,help", "Outputs this help text");

	opts.add_options("Game")
		("title", "Set the window title", cxxopts::value<std::string>())
		("world", "Loads a GibEngine World Object (*.gwo)", cxxopts::value<std::string>())
		("levelID", "Loads the selected level from the GWO", cxxopts::value<unsigned int>())
		("windowWidth", "Width of the viewable window", cxxopts::value<int>(reqW))
		("windowHeight", "Height of the viewable window", cxxopts::value<int>(reqH));

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

	if (reqW > 0 && reqH > 0)
	{
		requestedWindowSize = glm::vec2(reqW, reqH);
	}
	else
	{
		requestedWindowSize = glm::vec2(800, 600);
	}

	// Load a level if world provided:
	std::string worldPath = opts["world"].as<std::string>();
	if (worldPath.size() > 0)
	{
		unsigned int levelID = opts["levelID"].as<unsigned int>();
		
		GibEngine::World::Database* db = new World::Database(worldPath.c_str(), true);
		rootSceneNode = db->LoadLevel(levelID);

		Logger::Instance->info("Loaded Level from Scene Root: {}", levelID);

		delete db;
	}
}

void GibEngine::Game::ToggleVsync()
{
	glfwSwapInterval((config.vsyncEnabled = !config.vsyncEnabled) ? 1 : 0);
}

GLFWwindow* GibEngine::Game::GetWindow()
{
	return this->window;
}

GibEngine::Renderer::Pipeline * GibEngine::Game::GetRenderPipeline() const
{
	return renderPipeline;
}

GibEngine::Input::InputManager* GibEngine::Game::GetInputManager() const
{
	return inputManager;
}

int GibEngine::Game::GetFramesPerSecond() const
{
	return framesPerSecond;
}

float GibEngine::Game::GetDeltaTime() const
{
	return deltaTime;
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