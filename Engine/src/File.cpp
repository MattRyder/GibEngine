#include "File.h"

std::string GibEngine::File::GetWorkingDirectory()
{
    #ifdef WIN32
        char buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
    #elif __linux__
        char buffer[PATH_MAX];
        if(getcwd(buffer, sizeof(buffer)) == NULL) 
        {
            return NULL;
        }
    #endif

    std::string::size_type position = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, position);
}

const char* GibEngine::File::GetPathForType(const char* filePath)
{
    return File::GetWorkingDirectory().append(filePath).c_str();
}

GibEngine::File* GibEngine::File::GetModelFile(const char* modelFile) 
{
    return new File(std::string(GetPathForType(MODEL_RELATIVE_PATH)).append(modelFile).c_str());
}

GibEngine::File* GibEngine::File::GetShaderFile(const char* shaderFile)
{
    return new File(std::string(GetPathForType(SHADER_RELATIVE_PATH)).append(shaderFile).c_str());
}

GibEngine::File::File(const char *filePath)
{
    this->path = filePath;
}

GibEngine::File::~File()
{
    free((char *)this->path);
}

const char* GibEngine::File::GetDirectory()
{
    std::string pathStr = path;
    std::string::size_type position = pathStr.find_last_of("\\/");
    return pathStr.substr(0, position).c_str();
}

const char* GibEngine::File::GetPath()
{
    return this->path;
}

const char* GibEngine::File::ReadFile()
{
    std::string *content, line;
    std::ifstream fileStream(path, std::ios::in);

    if (!fileStream.is_open())
    {
        Logger::Instance->error("Failed to open File for read: {}", path);
        return nullptr;
    }

    content = new std::string();

    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content->append(line);
    }

    fileStream.close();
    return content->c_str();
}
