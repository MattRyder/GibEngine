#include "filesystem/WindowsFileSystem.h"

const std::string GibEngine::FileSystem::WindowsFileSystem::GetWorkingDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);

	std::string::size_type position = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, position);
}

std::vector<std::string> GibEngine::FileSystem::WindowsFileSystem::GetFileList(const std::string& absolutePath, const std::string& extension, bool includeSubdirectories)
{
	std::vector<std::string> fileList;

	HANDLE hFind;
	WIN32_FIND_DATA data;

	auto pathCopy = absolutePath;
	if (pathCopy.back() == '/')
	{
		pathCopy.pop_back();
	}
	else if ((pathCopy.substr(pathCopy.length() - 2, 2) == "/*"))
	{
		pathCopy.pop_back();
		pathCopy.pop_back();
	}

	hFind = FindFirstFile((pathCopy + "/*").c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do{ 
			std::string fileName = data.cFileName;
			if (fileName == "." || fileName == "..")
			{
				continue;
			}

			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && includeSubdirectories)
			{
				auto subFileList = GetFileList(pathCopy + "/" + fileName + "/", extension, true);

				fileList.insert(fileList.end(), subFileList.begin(), subFileList.end());
			}
			else
			{
				auto lastPeriodPos = fileName.find_last_of('.');
				if (lastPeriodPos != fileName.npos)
				{
					const std::string fileExtension = fileName.substr(lastPeriodPos, fileName.size() - lastPeriodPos);

					// If no extension, or wildcard, return all files:
					if (extension.empty() || extension == "*" || fileExtension == extension)
					{
						fileList.push_back(pathCopy + "/" + fileName);
					}
				}
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}

	return fileList;
}

void GibEngine::FileSystem::WindowsFileSystem::ReadFile(const std::string& relativePath, std::shared_ptr<std::string> buffer)
{
	std::string line;
	std::ifstream fileStream(relativePath);

	if (!fileStream.is_open())
	{
		Logger::Instance->error("Failed to open File for read: {}", relativePath);
		return;
	}

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		buffer->append(line + "\n");
	}

	fileStream.close();
}

bool GibEngine::FileSystem::WindowsFileSystem::CreateDir(const std::string & relativePath)
{
	return (CreateDirectory(relativePath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS);
}

bool GibEngine::FileSystem::WindowsFileSystem::WriteFile(const std::string & relativePath, std::shared_ptr<std::string> buffer)
{
	std::ofstream outputStream(relativePath.c_str());

	outputStream << *buffer;
	outputStream.close();

	return true;
}
