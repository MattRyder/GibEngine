#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Logger.h"

namespace GibEngine
{
	namespace FileSystem
	{
		class IFileSystem
		{
		public:
			IFileSystem() = default;

			virtual const std::string GetWorkingDirectory() = 0;

			virtual std::vector<std::string> GetFileList(const std::string& absolutePath, const std::string& extension, bool includeSubdirectories = false) = 0;

			virtual bool CreateDir(const std::string& absolutePath) = 0;

			virtual void ReadFile(const std::string& absolutePath, std::shared_ptr<std::string> buffer) = 0;

			virtual bool WriteFile(const std::string& absolutePath, std::shared_ptr<std::string> buffer) = 0;
		};
	}
}