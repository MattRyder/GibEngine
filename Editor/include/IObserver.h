#pragma once

#include <functional>
#include <iostream>

namespace GibEditor
{
	class Observer
	{
	protected:
		std::function<void(std::string)> onChangeFunc;

	public:
		Observer(std::function<void(std::string)> onChangeFunc)
		{
			this->onChangeFunc = onChangeFunc;
		}

		virtual void Update() = 0;
	};
}