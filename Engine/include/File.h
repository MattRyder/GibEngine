#pragma once

#ifdef WIN32
#include <windows.h>
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
#define ASSET_RELATIVE_PATH "/../Assets/"
#define SCREENSHOT_RELATIVE_PATH "/Screenshots/"

#define MODEL_RELATIVE_PATH ASSET_RELATIVE_PATH "Models/"
#define SHADER_RELATIVE_PATH ASSET_RELATIVE_PATH "Shaders/"
#define SKYBOX_RELATIVE_PATH ASSET_RELATIVE_PATH "Skybox/"
#define FONT_RELATIVE_PATH ASSET_RELATIVE_PATH "Fonts/"

namespace GibEngine
{
    class File
    {
        const char* path;
        static std::string* GetPathForType(const char* filePath);

    public:
        File(const char* filePath);
        ~File();

        static std::string GetWorkingDirectory();
		static std::string* GetSkyboxPath(const char* skyboxTextureName);

		static std::string* GetScreenshotPath();

		static File* GetFontFile(const char* fontName);
        static File* GetModelFile(const char* modelName);
        static File* GetShaderFile(const char* shaderName);
		static File* GetSkyboxFile(const char* skyboxTextureName, const char* skyboxSideName);
		static File* GetScreenshotFile(const char* screenshotName);

        const char* GetDirectory();
        const char* GetPath();
        
        const char* ReadFile();

		bool Exists();
    };
}