#pragma once

#include <functional>

namespace GibEditor
{
	class Observer
	{
	protected:
		std::function<void(std::string)> onChangeFunc;

	public:
		Observer(std::function<void(std::string)> onChangeFunc) : onChangeFunc(onChangeFunc) {}
		virtual void Update() = 0;
	};
}