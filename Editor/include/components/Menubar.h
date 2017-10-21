#pragma once

#include "IComponent.h"

namespace GibEditor
{
	namespace Components
	{
		class Menubar : IComponent
		{
			std::function<void()> exitCallback;

		public:
			virtual void Render() override;

			void SetOnExitCallback(const std::function<void()> &exitCallbackFunc);
		};
	}
}