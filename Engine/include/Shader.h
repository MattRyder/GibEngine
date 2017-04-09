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

        File *vertexFile;
        File *fragmentFile;

        void Compile(GLuint shaderId, const char *shaderSourceCode);
        GLuint Link(GLuint vertexShader, GLuint fragmentShader);

    public:
        Shader(const char *vertexFilename, const char *fragmentFilename);
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