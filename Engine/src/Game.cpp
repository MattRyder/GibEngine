#include "Game.h"

GibEngine::Game::Game(const char *windowTitle)
{
    this->windowTitle = windowTitle;
    this->playerCamera = new FreeCamera(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 200.0f, 90.0f);

    if (!initializeGL())
    {
        Logger::Instance->error("Failed to initialize OpenGL!");
        return;
    }

    if (GL_KHR_debug)
    {
        GibEngine::Logger::Instance->info("GL_KHR_debug extension available");
        glDebugMessageCallback(GLDebugCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        GibEngine::Logger::Instance->info("GL_KHR_debug extension enabled");
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    this->model = new Model("brickwall/brickwall.obj");

}

GibEngine::Game::~Game()
{
    glfwDestroyWindow(this->window);
    delete this->windowTitle;
}

void GibEngine::Game::Render()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->renderPipeline->Render();
    
    //shader->Begin();

    //model->Render(shader->GetShaderId(), 0);

    //shader->End();

    glfwSwapBuffers(window);
    Update();
}

void GibEngine::Game::Update()
{
    double deltaTime = glfwGetTime();

    this->playerCamera->Update(deltaTime, GibEngine::Input::MouseState.x, GibEngine::Input::MouseState.y, GibEngine::Input::KeyboardState);

    glfwPollEvents();
}

bool GibEngine::Game::initializeGL()
{
    int glfwInitResult = glfwInit();
    if (glfwInitResult != GL_TRUE)
    {
        return false;
    }

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
    
    // Initialize GL3W
    if (gl3wInit())
    {
        // Failed to init GL3W!
        return false;
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    Logger::Instance->info("Renderer: {}", renderer);
    Logger::Instance->info("OpenGL Version: {} - GLSL Version: {}", version, glslVersion);

    // Set the Render pipeline up with known OpenGL supported types:
    this->renderPipeline = new Renderer::Pipeline(GibEngine::Renderer::ShaderLanguage::GLSL_130);
    this->renderPipeline->AddPass(Renderer::RenderPassType::FORWARD_LIGHTING);

    return true;
}

void GibEngine::Game::ToggleVsync()
{
}

GLFWwindow * GibEngine::Game::GetWindow()
{
    return this->window;
}

void GibEngine::Game::SetWindowTitle(const char *windowTitle) {
  this->windowTitle = windowTitle;
  glfwSetWindowTitle(this->window, this->windowTitle);
}

void GibEngine::Game::SetWindowSize(int windowWidth, int windowHeight)
{
    windowWidth = windowWidth > 1 ? windowWidth : 1;
    windowHeight = windowHeight > 1 ? windowHeight : 1; 
    glfwSetWindowSize(this->window, windowWidth, windowHeight);
}