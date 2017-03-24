#pragma once

#include <Windows.h>
#include <string>
#include <fstream>

#include "Logger.h"

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