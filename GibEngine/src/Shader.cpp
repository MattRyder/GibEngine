#include "Shader.h"

GibEngine::Shader::Shader(const char *vertexFilename, const char *fragmentFilename)
{
    this->vertexFile = File::GetAssetPath(std::string("Shaders\\").append(vertexFilename).c_str());
    this->fragmentFile = File::GetAssetPath(std::string("Shaders\\").append(fragmentFilename).c_str());

    this->shaderId = Load();
}

GibEngine::Shader::~Shader()
{
    delete this->vertexFile;
    delete this->fragmentFile;

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

    std::string *vsData = this->vertexFile->ReadFile();
    std::string *fsData = this->fragmentFile->ReadFile();

    Compile(vShader, vsData->c_str());
    Compile(fShader, fsData->c_str());

    GLuint program = Link(vShader, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    delete vsData;
    delete fsData;

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

void GibEngine::Shader::Compile(GLuint shaderId, const char *shaderSourceCode)
{
    glShaderSource(shaderId, 1, &shaderSourceCode, NULL);
    glCompileShader(shaderId);
    
    GLint res = GL_FALSE;
    int logLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
        std::vector<char> shaderErr(logLength);
        glGetShaderInfoLog(shaderId, logLength, nullptr, &shaderErr[0]);
        Logger::Instance->error("Failed to compile shader!\nShader Log:\n{}", &shaderErr[0]);
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

