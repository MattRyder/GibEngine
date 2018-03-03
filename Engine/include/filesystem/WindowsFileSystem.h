#pragma once

#include <windows.h>
#include "IFileSystem.h"

namespace GibEngine
{
	namespace FileSystem
	{
		class WindowsFileSystem : public IFileSystem
		{
		public:
			virtual const std::string GetWorkingDirectory() override;

			virtual std::vector<std::string> GetFileList(const std::string& absolutePath, const std::string& extension, bool includeSubdirectories = false) override;

			virtual void ReadFile(const std::string& absolutePath, std::shared_ptr<std::string> buffer) override;

			virtual bool CreateDir(const std::string & absolutePath) override;

			virtual bool WriteFile(const std::string & absolutePath, std::shared_ptr<std::string> buffer) override;
		};
	}
}
