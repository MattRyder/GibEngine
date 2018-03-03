#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Logger.h"

namespace GibEngine
{
    class Shader
    {
        GLuint shaderId;
        bool isComplete;

        void Compile(GLuint shaderId, const std::string& shaderSource);
        GLuint Link(GLuint vertexShader, GLuint fragmentShader);

    public:
        Shader(std::shared_ptr<std::string> vertexSource, std::shared_ptr<std::string> fragmentSource);
        ~Shader();

        GLuint GetShaderId();
        bool IsComplete();

        void SetComplete(bool isComplete);
    };
}