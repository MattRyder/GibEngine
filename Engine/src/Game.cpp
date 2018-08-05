#include "Game.h"

GibEngine::Game::Game(int argc, char** argv)
	: deltaTime(0), framesPerSecond(0), lastFrameTime(0), fpsIntervalTimer(0), frameCounter(0)
{
	this->ParseOptions(argc, argv);

	this->eventManager = std::make_shared<Event::EventManager>();

	if (!InitializeGraphics(shaderLanguage))
	{
		Logger::Instance->error("Failed to initialize graphics!");
		return;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	this->playerCamera = std::shared_ptr<FreeCamera>(new FreeCamera(requestedWindowSize.x, requestedWindowSize.y, 0.1f, 2000.0f, glm::radians(66.0f)));
	this->playerCamera->SetPosition(glm::vec3(20, 15, 0));
	this->playerCamera->RegisterEvents(eventManager.get());

	//eventManager->PauseListener(this->playerCamera.get(), Event::Type::MOUSE_MOVE);

	this->inputManager = std::make_shared<Input::InputManager>(window);

	vset = std::shared_ptr<Scene::VisibleSet>(new Scene::VisibleSet(playerCamera, rootEntity));

#ifdef WIN32
	this->fileSystem = std::shared_ptr<FileSystem::IFileSystem>(new FileSystem::WindowsFileSystem());
#elif __unix__
	this->fileSystem = std::shared_ptr<FileSystem::IFileSystem>(new FileSystem::UnixFileSystem());
#endif

	SetupPipeline();

	if(!true)
	{
		GibEngine::World::Database* worldDb = new World::Database("demo_nodes.gwo", fileSystem, graphicsApi);

		std::shared_ptr<BaseEntity> rootNode = CreateWorld();

		//if (worldDb->SaveLevel(rootNode.get()))
		//{
		//	// TODO: attach rootNode to new Level record
		//}
	}
}

GibEngine::Game::~Game()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void GibEngine::Game::Render()
{
	// Generate the delta for the previous and this frame:
	float currentFrameTime = static_cast<float>(glfwGetTime());
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

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

	if (!rootEntity)
	{
		return;
	}

	auto visibleSet = Scene::VisibleSet(playerCamera, GetRootEntity());
	visibleSet.Parse(graphicsApi);

	this->pipeline->Render(visibleSet, GetDeltaTime());
}

void GibEngine::Game::Update()
{
	float deltaTime = GetDeltaTime();

	// Handle GLFW state changes
	if (GLFW::WindowResizeEvent.Raised)
	{
		this->pipeline->ResizeFramebuffer(GLFW::WindowResizeEvent.Width, GLFW::WindowResizeEvent.Height);
		GLFW::WindowResizeEvent.Raised = false;
	}

	eventManager->Poll(deltaTime);

	glfwPollEvents();
}

void GibEngine::Game::SetupPipeline()
{
	this->pipeline = std::shared_ptr<Renderer::Pipeline>(new Renderer::Pipeline(requestedWindowSize.x, requestedWindowSize.y, fileSystem, graphicsApi));

	Renderer::RenderPass* deferredGeoPass = this->pipeline->GetRenderPass(Renderer::RenderPass::Type::DEFERRED_GEOMETRY);
	deferredGeoPass->SetPassEnabled(true);

	Renderer::RenderPass* ssaoPass = this->pipeline->GetRenderPass(Renderer::RenderPass::Type::AMBIENT_OCCLUSION);
	ssaoPass->SetPassEnabled(true);
	
	Renderer::RenderPass* deferredLightingPass = this->pipeline->GetRenderPass(Renderer::RenderPass::Type::DEFERRED_LIGHTING);
	deferredLightingPass->SetPassEnabled(true);

	Renderer::RenderPass* renderPass = this->pipeline->GetRenderPass(Renderer::RenderPass::Type::SKYBOX);
	renderPass->SetPassEnabled(true);

	Renderer::RenderPass* forwardPass = this->pipeline->GetRenderPass(Renderer::RenderPass::Type::FORWARD_RENDERING);
	forwardPass->SetPassEnabled(true);

	Renderer::RenderPass* renderToTexturePass = this->pipeline->GetRenderPass(Renderer::RenderPass::Type::RENDER_TO_TEXTURE);
	renderToTexturePass->SetPassEnabled(true);

	// Add Cameras
	pipeline->AddCamera(playerCamera);
}

bool GibEngine::Game::InitializeGraphics(GibEngine::Renderer::ShaderLanguage shaderLanguage)
{
	if (!glfwInit())
	{
		return false;
	}

	switch(shaderLanguage)
	{
		case Renderer::ShaderLanguage::GLES_3:
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			break;
		case Renderer::ShaderLanguage::GLSL_420:
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 16);
			break;
	}

	this->window = glfwCreateWindow(requestedWindowSize.x, requestedWindowSize.y, this->windowTitle.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, eventManager.get());

	// Setup GLFW callbacks:
	glfwSetFramebufferSizeCallback(window, GLFW::SetWindowSizeCallback);

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

	switch (shaderLanguage)
	{
	case Renderer::ShaderLanguage::GLES_3:
		graphicsApi = std::shared_ptr<Renderer::API::IGraphicsApi>(new Renderer::API::GLES3());
		break;
	case Renderer::ShaderLanguage::GLSL_420:
		graphicsApi = std::shared_ptr<Renderer::API::IGraphicsApi>(new Renderer::API::GL420());
		break;
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
	if(title.size() > 0)
	{
		this->SetWindowTitle(title);
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
		
		GibEngine::World::Database* db = new World::Database(worldPath.c_str(), fileSystem, graphicsApi, true);
		//rootEntity = db->LoadLevel(levelID);
		vset->SetRootEntity(rootEntity);
		vset->Parse(graphicsApi);

		Logger::Instance->info("Loaded Level from Scene Root: {}", levelID);

		delete db;
	}
}

std::shared_ptr<GibEngine::BaseEntity> GibEngine::Game::CreateWorld()
{
	const json11::Json deferredGenerationData = json11::Json::object
	{
		{ "MeshFlags", json11::Json::array { "RENDER_DEFERRED" } }
	};

	const json11::Json forwardGenerationData = json11::Json::object
	{
		{ "MeshFlags", json11::Json::array { "RENDER_WIREFRAME", "RENDER_FORWARD" } }
	};

	auto sceneNode = std::make_shared<BaseEntity>(BaseEntity::Type::ENTITY, "Scene Root");

	auto skyboxMesh = MeshService::Generate(graphicsApi, MeshService::CUBE_GENERATION_JSON);
	auto cubemap = MeshService::LoadCubemap(graphicsApi, fileSystem->GetWorkingDirectory() + "/Assets/Skybox/stormy", "png");
	auto skybox = std::shared_ptr<Skybox>(new Skybox(skyboxMesh, cubemap));
	skybox->RegisterEvents(eventManager.get());
	
	auto light = std::make_shared<PointLight>(
		glm::vec3(3.3f, 1.6f, 7.7f),
		glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f), glm::vec3(0.7f),
		-0.5f, // linear atten
		1.2f); // quad atten

	// Attach the sphere mesh 
	auto sphereNode = MeshService::Load(graphicsApi, fileSystem->GetWorkingDirectory() + "/Assets/Models/default/sphere/sphere.obj", forwardGenerationData);
	light->AddChild(sphereNode);

	// Create a Model node:
	auto meshNode = MeshService::Load(graphicsApi, fileSystem->GetWorkingDirectory() + "/Assets/Models/brickwall/brickwall.obj", deferredGenerationData);
	meshNode->RegisterEvents(eventManager.get());
	//auto meshNode = MeshService::Load(graphicsApi, fileSystem->GetWorkingDirectory() + "/Assets/Models/sponza/sponza.fbx", deferredGenerationData);
	//auto meshNode = MeshService::Load(graphicsApi, fileSystem->GetWorkingDirectory() + "/Assets/Models/default/box/box.obj", deferredGenerationData);
	meshNode->AddChild(playerCamera);

	auto floorNode =  MeshService::Load(graphicsApi, fileSystem->GetWorkingDirectory() + "/Assets/Models/default/box/box.obj", deferredGenerationData);
	floorNode->SetPosition(glm::vec3(-230.0f, 0, -425.0f));
	floorNode->Scale(glm::vec3(75.0f, 0.0f, 75.0f));
	sceneNode->AddChild(meshNode);

	sceneNode->AddChild(skybox);
	sceneNode->AddChild(light);

	sceneNode->AddChild(floorNode);

	sceneNode->RecalculateWorldTransform();

	return sceneNode;
}

void GibEngine::Game::ToggleVsync()
{
	glfwSwapInterval((config.vsyncEnabled = !config.vsyncEnabled) ? 1 : 0);
}

GLFWwindow* GibEngine::Game::GetWindow() const
{
	return window;
}

std::shared_ptr<GibEngine::Renderer::Pipeline> GibEngine::Game::GetRenderPipeline() const
{
	return pipeline;
}

std::shared_ptr<GibEngine::Input::InputManager> GibEngine::Game::GetInputManager() const
{
	return inputManager;
}

std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> GibEngine::Game::GetGraphicsApi() const
{
	return graphicsApi;
}

std::shared_ptr<GibEngine::FileSystem::IFileSystem> GibEngine::Game::GetFileSystem() const
{
	return fileSystem;
}

std::shared_ptr<GibEngine::BaseEntity> GibEngine::Game::GetRootEntity() const
{
	return rootEntity;
}

int GibEngine::Game::GetFramesPerSecond() const
{
	return framesPerSecond;
}

bool GibEngine::Game::IsMinimized() const
{
	return !glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

float GibEngine::Game::GetDeltaTime() const
{
	return deltaTime;
}

void GibEngine::Game::SetWindowTitle(const std::string windowTitle)
{
	this->windowTitle = windowTitle;
	glfwSetWindowTitle(window, this->windowTitle.c_str());
}

void GibEngine::Game::SetWindowSize(int windowWidth, int windowHeight)
{
	windowWidth = windowWidth > 1 ? windowWidth : 1;
	windowHeight = windowHeight > 1 ? windowHeight : 1;
	glfwSetWindowSize(window, windowWidth, windowHeight);
}

void GibEngine::Game::SetSceneRoot(std::shared_ptr<GibEngine::BaseEntity> rootEntity)
{
	this->rootEntity = rootEntity;
	this->vset->SetRootEntity(rootEntity);
	this->vset->Parse(graphicsApi);
}