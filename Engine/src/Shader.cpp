#include "Shader.h"

GibEngine::Shader::Shader(File *vertexShaderFile, File *fragmentShaderFile)
{
    this->vertexShader = vertexShaderFile;
    this->fragmentShader = fragmentShaderFile;

    this->shaderId = this->Load();
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
    //if (shaderId > 0)
    //{
    //    glDeleteShader(shaderId);
    //    shaderId = 0;
    //}

	if (!vertexShader->Exists())
	{
		Logger::Instance->error("GibEngine::Shader::Load failed: Vertex Shader does not exist.");
		return 0;
	}
	else if(!fragmentShader->Exists())
	{
		Logger::Instance->error("GibEngine::Shader::Load failed: Fragment Shader does not exist.");
		return 0;
	}

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    Compile(vShader, vertexShader);
    Compile(fShader, fragmentShader);

    GLuint program = Link(vShader, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

GLuint GibEngine::Shader::GetShaderId()
{
    return this->shaderId;
}

bool GibEngine::Shader::IsComplete()
{
    return this->isComplete;
}

void GibEngine::Shader::SetComplete(bool isComplete)
{
    this->isComplete = isComplete;
}

void GibEngine::Shader::Begin()
{
    if(!isComplete)
    {
        Logger::Instance->error("Shader is not complete!");
        return;
    }

    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    if (currentProgram > 0 && currentProgram != shaderId)
    {
        Logger::Instance->error("Shader::End() must be called before Shader::Begin()");
    }

    glUseProgram(this->shaderId);
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

	delete shaderSrc;
}

GLuint GibEngine::Shader::Link(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    
    glBindAttribLocation(program, 0, "v_Position");
	glBindAttribLocation(program, 1, "v_Normal");
	glBindAttribLocation(program, 2, "v_TexCoords");	
	glBindAttribLocation(program, 3, "v_Tangent");	
	glBindAttribLocation(program, 4, "v_Bitangent");	

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint res = GL_FALSE;
    int logLength;

    glGetProgramiv(program, GL_LINK_STATUS, &res);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
        std::vector<char> programErr(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, &programErr[0]);
		Logger::Instance->error("Failed to link shader!\nVertex: {}\nFragment:{}\nShader Log:\n{}",
			this->vertexShader->GetPath(), this->fragmentShader->GetPath(), &programErr[0]);
        return -1;
    }

    SetComplete(true);

    return program;
}

