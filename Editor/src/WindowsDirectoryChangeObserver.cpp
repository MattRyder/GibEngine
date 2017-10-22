#ifdef _WIN32

#include "WindowsDirectoryChangeObserver.h"

GibEditor::WindowsDirectoryChangeObserver::WindowsDirectoryChangeObserver(std::string directoryPath, bool searchSubdirectories, std::function<void(std::string)> onChangeFunc)
	: Observer(onChangeFunc)
{
	this->directory = directoryPath;
	this->directoryNotifyHandle = FindFirstChangeNotification(this->directory.c_str(), searchSubdirectories, FILE_NOTIFY_CHANGE_LAST_WRITE);
}

void GibEditor::WindowsDirectoryChangeObserver::Update()
{
	ReadDirectoryChangesW(directoryNotifyHandle, &fileNotifyInformation, sizeof(fileNotifyInformation),
		false, FILE_NOTIFY_CHANGE_LAST_WRITE, &changeByteLength, &o, nullptr);

	GetOverlappedResult(directoryNotifyHandle, &o, &changeByteLength, false);

	if (fileNotifyInformation.info.Action != 0)
	{
		std::wstring filenameWS(fileNotifyInformation.info.FileName);
		std::string filename(filenameWS.begin(), filenameWS.end());

		onChangeFunc(filename);

		fileNotifyInformation.info.Action = 0;
	}

}

#endif
