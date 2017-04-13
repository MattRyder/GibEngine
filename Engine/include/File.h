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
        const char *path;

    public:
        File(const char *filePath);
        ~File();

        static std::string GetWorkingDirectory();
        static File* GetAssetPath(const char *assetName);

        const char* GetDirectory();
        const char* GetPath();
        
        const char* ReadFile();

    };
}