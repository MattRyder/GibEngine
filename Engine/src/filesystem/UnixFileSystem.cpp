#include "filesystem/UnixFileSystem.h"


const std::string GibEngine::FileSystem::UnixFileSystem::GetWorkingDirectory()
{
    char buffer[PATH_MAX];
    if(getcwd(buffer, sizeof(buffer)) == NULL)
    {
        return nullptr;
    }

    return std::string(buffer);
}

std::vector<std::string> GibEngine::FileSystem::UnixFileSystem::GetFileList(
	const std::string& absolutePath, const std::string& extension, bool includeSubdirectories)
{
	struct dirent* dirEntry;
    std::vector<std::string> fileList;

    auto directory = opendir(absolutePath.c_str());
	while((dirEntry = readdir(directory)) != NULL)
	{
		auto path = absolutePath + "/" + dirEntry->d_name;
		switch(dirEntry->d_type)
		{
			case DT_DIR:
				if(includeSubdirectories)
				{
					auto files = GetFileList(path, extension, true);
					fileList.insert(fileList.end(), files.begin(), files.end());
				}
				break;
			case DT_REG:
				fileList.push_back(path);
				break;
		}
	}
	closedir(directory);

	return fileList;
}

void GibEngine::FileSystem::UnixFileSystem::ReadFile(const std::string& absolutePath, std::shared_ptr<std::string> buffer)
{
    std::string line;
	std::ifstream fileStream(absolutePath);

	if (!fileStream.is_open())
	{
		Logger::Instance->error("Failed to open File for read: {}", absolutePath);
		return;
	}

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		buffer->append(line + "\n");
	}

	fileStream.close();
}

bool GibEngine::FileSystem::UnixFileSystem::CreateDir(const std::string & absolutePath)
{
	struct stat sbuf;

	// Check if the directory exists before attempting a create:
	if(stat(absolutePath.c_str(), &sbuf) == 0 && S_ISDIR(sbuf.st_mode))
	{
		return true;
	}

	const int res = mkdir(absolutePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(res != 0)
	{
		const std::string errorStr = std::strerror(res);
		Logger::Instance->error("Failed to create directory:\nDirectory: {}\nReason: {}", absolutePath, errorStr);
		return false;
	}
	
	return true;
}

bool GibEngine::FileSystem::UnixFileSystem::WriteFile(const std::string & absolutePath, std::shared_ptr<std::string> buffer)
{
	std::ofstream outputStream(absolutePath.c_str());

	outputStream << *buffer;
	outputStream.close();

	return true;
}
