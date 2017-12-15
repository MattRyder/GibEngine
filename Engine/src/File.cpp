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
	if (getcwd(buffer, sizeof(buffer)) == NULL) { return NULL; }
	return std::string(buffer);
#endif
}

std::string* GibEngine::File::GetSkyboxPath(const char* skyboxTextureName)
{
	std::string *fileBase = GetPathForType(SKYBOX_RELATIVE_PATH);
	fileBase->append(skyboxTextureName);
	return fileBase;
}

std::string* GibEngine::File::GetScreenshotPath()
{
	return GetPathForType(SCREENSHOT_RELATIVE_PATH);
}

std::vector<GibEngine::File*> GibEngine::File::GetDirectoryList(const char * rootDirectory)
{
	return GetDirectoryListInternal(rootDirectory);
}

std::string* GibEngine::File::GetPathForType(const char* filePath)
{
    std::string *pathStr = new std::string(File::GetWorkingDirectory());
    pathStr->append(filePath);
    return pathStr;
}

std::vector<GibEngine::File*> GibEngine::File::GetDirectoryListInternal(const char* rootDirectory)
{
	std::vector<File*> directoryList = std::vector<File*>();

#ifdef WIN32
	HANDLE hFind;
	WIN32_FIND_DATA data;

	hFind = FindFirstFile(std::string(rootDirectory).append("/*").c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0)
			{
				continue;
			}

			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				std::string subdir = std::string(rootDirectory) + "//" + data.cFileName;
				const char* subdirectoryPath = subdir.c_str();
				std::vector<File*> dirList = GetDirectoryListInternal(subdirectoryPath);
				directoryList.insert(directoryList.end(), dirList.begin(), dirList.end());
			}
			else
			{
				// rootDir + "\\" + cFileName + NULL
				char* filepath = new char[strlen(rootDirectory) + strlen(data.cFileName) + 3];
				strcpy(filepath, rootDirectory);
				strcat(filepath, "\\");
				strcat(filepath, data.cFileName);

				File* file = new File(filepath);
				directoryList.push_back(file);
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
#elif __unix__
#endif

	return directoryList;
}

GibEngine::File* GibEngine::File::GetFontFile(const char * fontName)
{
	std::string *fileBase = GetPathForType(FONT_RELATIVE_PATH);
	fileBase->append(fontName);
	return new File(fileBase->c_str());
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

GibEngine::File* GibEngine::File::GetSkyboxFile(const char* skyboxTextureName, const char* skyboxSideName)
{
	std::string *fileBase = GetPathForType(SKYBOX_RELATIVE_PATH);
	fileBase->append(skyboxTextureName);
	fileBase->append((std::string("/") + std::string(skyboxSideName)).c_str());

	return new File(fileBase->c_str());
}

GibEngine::File* GibEngine::File::GetScreenshotFile(const char* screenshotName)
{
	std::string *fileBase = GetPathForType(SCREENSHOT_RELATIVE_PATH);
	fileBase->append(screenshotName);
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
	std::string* directory = new std::string(pathStr.substr(0, position));
    return directory->c_str();
}

const char* GibEngine::File::GetPath()
{
    return this->path;
}

const char * GibEngine::File::GetExtension()
{
	std::string pathStr(path);
	return strdup(pathStr.substr(pathStr.find_last_of(".") + 1).c_str());
}

const char * GibEngine::File::GetFilename()
{
	std::string pathStr(path);
	return strdup(pathStr.substr(pathStr.find_last_of("/") + 1).c_str());
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
		content->append(line).append("\n");
    }

    fileStream.close();
    return content->c_str();
}

bool GibEngine::File::Exists()
{
    std::ifstream fileStream(this->path);
    return (bool)fileStream;
}
