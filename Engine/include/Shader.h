#pragma once

#include "GL/gl3w.h"

#include "Logger.h"
#include "Model.h"

namespace GibEngine
{
    class Shader
    {
        enum class ShaderType
        {
            COLOR
        };

        GLuint shaderId;

        File *vertexShader;
        File *fragmentShader;

        void Compile(GLuint shaderId, File *shaderFile);
        GLuint Link(GLuint vertexShader, GLuint fragmentShader);

    public:
        Shader(File *vertexShaderFile, File *fragmentShaderFile);
        ~Shader();
        
        GLuint Load();
        void Reload();
        
        GLuint GetShaderId();
        
        void Begin();
        void Draw(Entity *drawableEntity);
        void Draw(Model *drawableModel);
        void End();

    };
}