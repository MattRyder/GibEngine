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

GibEngine::File* GibEngine::File::GetAssetPath(const char *assetName)
{
    std::string *filePathStr = new std::string(File::GetWorkingDirectory().append("\\..\\..\\Assets\\").append(assetName));
    File *fp = new File(filePathStr);
    return fp;
}

GibEngine::File::File(std::string *filePath)
{
    this->path = filePath;
}

GibEngine::File::~File()
{
    delete this->path;
}

std::string GibEngine::File::GetDirectory()
{
    std::string::size_type position = path->find_last_of("\\/");
    return path->substr(0, position);
}

const char* GibEngine::File::GetPath()
{
    return this->path->c_str();
}

std::string* GibEngine::File::ReadFile()
{
    std::string *content, line;
    std::ifstream fileStream(path->c_str(), std::ios::in);

    if (!fileStream.is_open())
    {
        Logger::Instance->error("Failed to open Shader file: {}", path->c_str());
        return nullptr;
    }

    content = new std::string();

    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content->append(line + '\n');
    }

    fileStream.close();
    return content;
}
