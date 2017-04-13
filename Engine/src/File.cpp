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
    std::string *filePathStr = new std::string(File::GetWorkingDirectory().append(ASSET_RELATIVE_PATH).append(assetName));
    File *fp = new File(filePathStr->c_str());
    return fp;
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
    std::string pathStr = std::string(pathStr);
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
        content->append(line + '\n');
    }

    fileStream.close();
    return content->c_str();
}
