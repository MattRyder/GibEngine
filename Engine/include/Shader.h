#pragma once

#include "GL/gl3w.h"

#include "Logger.h"
#include "Model.h"

namespace GibEngine
{
    class Shader
    {
        GLuint shaderId;
        bool isComplete;

        File *vertexShader;
        File *fragmentShader;

        void Compile(GLuint shaderId, File *shaderFile);
        GLuint Link(GLuint vertexShader, GLuint fragmentShader);

    public:
        Shader(File *vertexShaderFile, File *fragmentShaderFile);
        ~Shader();
        
		GLuint Load();
		void Begin();
		void End();

        GLuint GetShaderId();
        bool IsComplete();

        void SetComplete(bool isComplete);
    };
}