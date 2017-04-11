#include "Game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::string errString;

    switch(source)
    {
        case 0x8246: errString = "API"; break;
        case 0x8247: errString = "WINDOW_SYSTEM"; break;
        case 0x8248: errString = "SHADER_COMPILER"; break;
        case 0x8249: errString = "THIRD_PARTY"; break;
        case 0x824A: errString = "APPLICATION"; break;
        case 0x824B: errString = "OTHER"; break;
        default: errString = "undefined"; break;
    }
}

void GlfwErrorCallback(int error, const char* description)
{
    GibEngine::Logger::Instance->error("GLFW: #{} #{}", error, description);
}

GibEngine::Game::Game(const char *windowTitle)
{
    this->windowTitle = new std::string(windowTitle);
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

    //this->model = new Model("brickwall\\brickwall.obj");
    //this->shader = new Shader("color_vs.glsl", "color_fs.glsl");

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

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_SAMPLES, 16);

    this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, this->windowTitle->c_str(), NULL, NULL);

    // Setup GLFW callbacks:
    //glfwSetKeyCallback(window, GibEngine::Input::UpdateKeyboardCallback);
    //glfwSetCursorPosCallback(window, GibEngine::Input::UpdateMousePositionCallback);
    //glfwSetErrorCallback(GlfwErrorCallback);

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

    Logger::Instance->info("Renderer: {}", renderer);
    Logger::Instance->info("OpenGL Version: {}", version);
    return true;
}

void GibEngine::Game::ToggleVsync()
{
}

GLFWwindow * GibEngine::Game::GetWindow()
{
    return this->window;
}
