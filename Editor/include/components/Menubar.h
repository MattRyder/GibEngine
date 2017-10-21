#pragma once

#include "IComponent.h"

namespace GibEditor
{
	namespace Components
	{
		class Menubar : IComponent
		{
			std::function<void()> exitCallback, openFileDialogCallbackFunc, saveFileDialogCallbackFunc;

		public:
			virtual void Render() override;

			void SetOnExitCallback(const std::function<void()> &exitCallbackFunc);
			void SetOnOpenFileDialogCallback(const std::function<void()> &openFileDialogCallbackFunc);
			void SetOnSaveFileDialogCallback(const std::function<void()> &saveFileDialogCallbackFunc);
		};
	}
}