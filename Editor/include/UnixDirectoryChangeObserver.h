#pragma once

#include "IObserver.h"

namespace GibEditor
{
	class UnixDirectoryChangeObserver : public Observer
	{
	public:
		UnixDirectoryChangeObserver(std::string directoryPath, bool searchSubdirectories, std::function<void(std::string)> onChangeFunc);

		virtual void Update() override;
	};
}