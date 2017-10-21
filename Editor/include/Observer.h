#pragma once

#include <functional>

namespace GibEditor
{
	class Observer
	{
	protected:
		std::function<void(std::string)> onChangeFunc;

	public:
		virtual void Update() = 0;
	};
}