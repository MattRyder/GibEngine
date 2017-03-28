#pragma once

#include <iostream>

#include "GL\gl3w.h"
#include "GLFW\glfw3.h"

#include "File.h"
#include "Input.h"
#include "Model.h"
#include "Shader.h"
#include "FreeCamera.h"

namespace GibEngine
{
    class Game
    {
        GLFWwindow *window;
        std::string *windowTitle;

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
        
        GLFWwindow *GetWindow();
    };
}