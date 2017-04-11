#pragma once

#include <iostream>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

#include "glfw/glfw_callback.h"

#include "File.h"
#include "Input.h"
#include "Model.h"
#include "Shader.h"
#include "FreeCamera.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

namespace GibEngine
{
    class Game
    {
        GLFWwindow *window;
        const char *windowTitle;

        FreeCamera *playerCamera;

        Model *model;
        Shader *shader;
    
    public:
        Game(const char *windowTitle);
        virtual ~Game();

        virtual void Render();
        virtual void Update();

        bool initializeGL();
        void ToggleVsync();

        void SetWindowTitle(const char *windowTitle);
        void SetWindowSize(int windowWidth, int windowHeight);

        GLFWwindow *GetWindow();
    };
}