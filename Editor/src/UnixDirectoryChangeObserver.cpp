#include "UnixDirectoryChangeObserver.h"

GibEditor::UnixDirectoryChangeObserver::UnixDirectoryChangeObserver(std::string directoryPath, bool searchSubdirectories, std::function<void(std::string)> onChangeFunc)
	: Observer(onChangeFunc) { }

void GibEditor::UnixDirectoryChangeObserver::Update()
{
}
