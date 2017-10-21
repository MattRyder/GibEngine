#pragma once

#include <Windows.h>
#include <fileapi.h>

#include "IObserver.h"

namespace GibEditor
{
	class WindowsDirectoryChangeObserver : public Observer
	{
		HANDLE directoryNotifyHandle;
		DWORD changeByteLength = 0;
		std::string directory;

		OVERLAPPED o = { 0 };

		union {
			FILE_NOTIFY_INFORMATION info;
			char d[sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH];
		} fileNotifyInformation = { 0 };

	public:
		WindowsDirectoryChangeObserver(std::string directoryPath, bool searchSubdirectories, std::function<void(std::string)> onChangeFunc);
		virtual void Update() override;
	};
}