#include "Shader.h"

GibEngine::Shader::Shader(std::shared_ptr<std::string> vertexSource, std::shared_ptr<std::string> fragmentSource)
	: shaderId(0), isComplete(false)
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	Compile(vShader, *vertexSource);


	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	Compile(fShader, *fragmentSource);
	
	this->shaderId = Link(vShader, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

GibEngine::Shader::~Shader()
{
    glDeleteProgram(this->shaderId);
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

void GibEngine::Shader::Compile(GLuint shaderId, const std::string& shaderSource)
{
	const char* shaderSrc = shaderSource.c_str();
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
        Logger::Instance->error("Failed to compile shader!\nShader Log:\n{}", &shaderErr[0]);
    }
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
		Logger::Instance->error("Failed to link shader!\nShader Log:\n{}", &programErr[0]);
        return -1;
    }

    SetComplete(true);

    return program;
}

