#pragma once

#ifdef WIN32
    #include <Windows.h>
#elif __linux__
    #include <unistd.h>
    #include <linux/limits.h>
#endif

#include <string>
#include <fstream>

#include "Logger.h"

#define ASSET_RELATIVE_PATH "/Assets/"

namespace GibEngine
{
    class File
    {
        std::string *path;

    public:
        File(std::string *filePath);
        ~File();

        static std::string GetWorkingDirectory();
        static File* GetAssetPath(const char *assetName);

        std::string GetDirectory();
        const char *GetPath();
        
        std::string *ReadFile();

    };
}