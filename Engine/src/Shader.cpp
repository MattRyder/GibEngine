#include "Shader.h"

GibEngine::Shader::Shader(File *vertexShaderFile, File *fragmentShaderFile)
{
    this->vertexShader = vertexShaderFile;
    this->fragmentShader = fragmentShaderFile;

    this->Load();
}

GibEngine::Shader::~Shader()
{
    delete this->vertexShader;
    delete this->fragmentShader;

    glDeleteProgram(this->shaderId);
}

GLuint GibEngine::Shader::Load()
{
    // Clear old shader if we're reloading:
    if (shaderId > 0)
    {
        glDeleteShader(shaderId);
        shaderId = 0;
    }

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderSrc = this->vertexShader->ReadFile();
    const char *fragmentShaderSrc = this->fragmentShader->ReadFile();

    Compile(vShader, vertexShader);
    Compile(fShader, fragmentShader);

    GLuint program = Link(vShader, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

void GibEngine::Shader::Reload()
{
}

GLuint GibEngine::Shader::GetShaderId()
{
    return this->shaderId;
}

void GibEngine::Shader::Begin()
{
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    if (currentProgram > 0 && currentProgram != shaderId)
    {
        Logger::Instance->error("Shader::End() must be called before Shader::Begin()");
    }

    glUseProgram(this->shaderId);
}

void GibEngine::Shader::Draw(Entity *drawableEntity)
{
    drawableEntity->Render();
}

void GibEngine::Shader::Draw(Model *drawableModel)
{
    drawableModel->Render(shaderId, 0);
}

void GibEngine::Shader::End()
{
    glUseProgram(0);
}

void GibEngine::Shader::Compile(GLuint shaderId, File *shaderFile)
{
    const char *shaderSrc = shaderFile->ReadFile();

    glShaderSource(shaderId, 1, &shaderSrc, NULL);
    glCompileShader(shaderId);
    
    GLint res = GL_FALSE;
    int logLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
        std::vector<char> shaderErr(logLength);
        glGetShaderInfoLog(shaderId, logLength, nullptr, &shaderErr[0]);
        Logger::Instance->error("Failed to compile shader!\nFile: {}\nShader Log:\n{}", shaderFile->GetPath(), &shaderErr[0]);
    }
}

GLuint GibEngine::Shader::Link(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint res = GL_FALSE;
    int logLength;

    glGetShaderiv(shaderId, GL_LINK_STATUS, &res);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
        std::vector<char> programErr(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, &programErr[0]);
        Logger::Instance->error("Failed to link shader!\nShader Log:\n{}", &programErr[0]);
        return -1;
    }

    return program;
}

