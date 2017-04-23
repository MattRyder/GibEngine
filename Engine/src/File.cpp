#include "File.h"

std::string GibEngine::File::GetWorkingDirectory()
{
    #ifdef WIN32
        char buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
        
        std::string::size_type position = std::string(buffer).find_last_of("\\/");
        return std::string(buffer).substr(0, position);
    #elif __linux__
        char buffer[PATH_MAX];
        if(getcwd(buffer, sizeof(buffer)) == NULL) { return NULL; }
        return std::string(buffer);
    #endif
}

std::string* GibEngine::File::GetPathForType(const char* filePath)
{
    std::string *pathStr = new std::string(File::GetWorkingDirectory());
    pathStr->append(filePath);
    return pathStr;
}

GibEngine::File* GibEngine::File::GetModelFile(const char* modelFile) 
{
    std::string *fileBase = GetPathForType(MODEL_RELATIVE_PATH);
    fileBase->append(modelFile);
    return new File(fileBase->c_str());
}

GibEngine::File* GibEngine::File::GetShaderFile(const char* shaderFile)
{
    std::string *fileBase = GetPathForType(SHADER_RELATIVE_PATH);
    fileBase->append(shaderFile);
    return new File(fileBase->c_str());
}

GibEngine::File::File(const char *filePath)
{
    this->path = filePath;
}

GibEngine::File::~File()
{
    free((void *)path);
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
