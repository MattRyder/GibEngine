#include "Game.h"

GibEngine::Game::Game(int argc, char** argv)
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

	//this->chaseCamera = new ChaseCamera(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 2500.0f, 45.0f, nullptr);

	int size = 1500;
	gridPlane = new Plane(size, size, 10);

	glm::mat4 mat = glm::mat4();
	mat[3] = glm::vec4(-(size / 2), 0, -(size / 2), 1.0);

	Mesh::Instance* instance = new Mesh::Instance(mat);
	World::DatabaseEntity<Mesh::Instance>* planeInstance = new World::DatabaseEntity<Mesh::Instance>(0, instance);

	gridPlane->AddInstance(planeInstance);
	gridPlane->SetWireframeMode(true);

	this->inputManager = new Input::InputManager(window);

	if (currentLevel != nullptr)
	{
		Logger::Instance->info("Loading Level: \"{}\"", currentLevel->GetName());
		this->LoadLevel(currentLevel);
	}

	if(!true)
	{
		GibEngine::World::Database* worldDb = new World::Database("demo.gwo");

		PointLight* light = new PointLight(
			glm::vec3(0, 1.65f, 0),
			glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.9f, 0.9f, 0.9f),
			0.75f, // -1.0 -- 1.0
			1.0f); // 0.0 -- 1.0

		// Keep to rebuild a demo world when schema changes:
		GibEngine::Model* model = new GibEngine::Model("woodhouse/woodhouse.obj");

		glm::mat4 m = glm::mat4();
		m = glm::scale(m, glm::vec3(3.0f, 3.0f, 3.0f));

		Mesh::Instance* instance = new Mesh::Instance(m);
		World::DatabaseEntity<Mesh::Instance>* dbInstance = new World::DatabaseEntity<Mesh::Instance>(0, instance);
		model->AddInstance(dbInstance);

		World::Level* lvl = worldDb->CreateLevel("E1M1: At Doom's Gate");

		World::DatabaseEntity<Model>* modelDb = new World::DatabaseEntity<Model>(0, model);
		lvl->AddModel(modelDb);

		Skybox* skybox = new Skybox("stormy", "png");
		World::DatabaseEntity<Skybox>* skyboxDb = new World::DatabaseEntity<Skybox>(0, skybox);
		lvl->SetSkybox(skyboxDb);

		World::DatabaseEntity<PointLight>* lightInstance = new World::DatabaseEntity<PointLight>(0, light);
		lvl->AddLight(lightInstance);

		worldDb->SaveLevel(lvl);

		delete lvl;
	}
}

GibEngine::Game::~Game()
{
	glfwDestroyWindow(window);
	glfwTerminate();

	delete currentLevel;
	delete inputManager;
	delete renderPipeline;
	delete playerCamera;
	//delete chaseCamera;
	delete gridPlane;
}

void GibEngine::Game::Render()
{
	if (this->renderPipeline != nullptr)
	{
		this->renderPipeline->Render();
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
	//this->chaseCamera->Update(deltaTime, inputManager->GetMousePosition(), inputManager->GetScrollState(), inputManager->GetKeyboardState());

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

void GibEngine::Game::LoadLevel(World::Level* level)
{
	// TODO: Replace with a clearPipeline() func:
	if (this->renderPipeline != nullptr)
	{
		delete this->renderPipeline;
	}

	this->renderPipeline = new Renderer::Pipeline(requestedWindowSize.x, requestedWindowSize.y, shaderLanguage, playerCamera);

	Renderer::RenderPass* deferredGeoPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_GEOMETRY);
	for (auto m : level->GetModelEntities())
	{
		deferredGeoPass->SetPassEnabled(true);
		deferredGeoPass->AddDrawable(m->GetEntity());
	}

	Renderer::RenderPass* deferredLightingPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::DEFERRED_LIGHTING);
	deferredLightingPass->SetPassEnabled(true);

	for (auto pointLight : level->GetPointLightEntities())
	{
		deferredLightingPass->AddLight(pointLight->GetEntity());
	}

	Renderer::RenderPass* renderPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::SKYBOX);
	Renderer::SkyboxRenderPass *skyboxPass = reinterpret_cast<Renderer::SkyboxRenderPass*>(renderPass);
	skyboxPass->SetPassEnabled(true);

	skyboxPass->SetSkybox(level->GetSkyboxEntity()->GetEntity());

	Renderer::RenderPass* forwardPass = this->renderPipeline->GetRenderPass(Renderer::RenderPassType::FORWARD_RENDERING);
	forwardPass->SetPassEnabled(true);

	Model* sphere = new Model("default/sphere/sphere.obj");
	sphere->SetWireframeMode(true);

	for (auto light : deferredLightingPass->GetLights())
	{
		glm::mat4 imat = glm::mat4();
		imat[3] = glm::vec4(light->GetPosition(), 1.0f);

		Mesh::Instance* instance = new Mesh::Instance(imat);
		World::DatabaseEntity<Mesh::Instance>* dbInstance = new World::DatabaseEntity<Mesh::Instance>(0, instance);
		sphere->AddInstance(dbInstance);
	}

	forwardPass->AddDrawable(gridPlane);
	forwardPass->AddDrawable(sphere);

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
		
		GibEngine::World::Database* db = new World::Database(worldPath.c_str());
		currentLevel = db->FindLevel(levelID);

		delete db;
	}
}

void GibEngine::Game::ToggleVsync() { }

GLFWwindow* GibEngine::Game::GetWindow()
{
	return this->window;
}

GibEngine::Renderer::Pipeline * GibEngine::Game::GetRenderPipeline() const
{
	return renderPipeline;
}

float GibEngine::Game::GetDeltaTime()
{
	float currentFrameTime = static_cast<float>(glfwGetTime());
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

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