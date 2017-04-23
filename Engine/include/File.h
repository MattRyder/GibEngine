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

/* Fast asset path descriptors, keep things consistent
 * All definitions must be terminated with a forward-slash:
*/
#define ASSET_RELATIVE_PATH "/Assets/"
#define MODEL_RELATIVE_PATH ASSET_RELATIVE_PATH "Models/"
#define SHADER_RELATIVE_PATH ASSET_RELATIVE_PATH "Shaders/"

namespace GibEngine
{
    class File
    {
        const char *path;
        static std::string* GetPathForType(const char* filePath);

    public:
        File(const char *filePath);
        ~File();

        static std::string GetWorkingDirectory();

        static File* GetModelFile(const char* modelName);
        static File* GetShaderFile(const char* shaderName);

        const char* GetDirectory();
        const char* GetPath();
        
        const char* ReadFile();

    };
}