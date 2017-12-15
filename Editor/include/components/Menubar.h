#pragma once

#include "IComponent.h"
#include "world/Level.h"

namespace GibEditor
{
	namespace Components
	{
		class Menubar : IComponent
		{
			GibEngine::World::Level* level;
			std::function<void()> exitCallback, openFileDialogCallbackFunc,  toggleUiRenderCallbackFunc;
			std::function<void(GibEngine::World::Level*)> saveFileDialogCallbackFunc, toggleWireframeCallbackFunc;

		public:
			Menubar(GibEngine::World::Level* level);
			virtual void Render() override;

			void SetLevel(GibEngine::World::Level* level);

			void SetOnExitCallback(const std::function<void()>& exitCallbackFunc);
			void SetOnOpenFileDialogCallback(const std::function<void()>& openFileDialogCallbackFunc);
			void SetOnSaveFileDialogCallback(const std::function<void(GibEngine::World::Level*)>& saveFileDialogCallbackFunc);
			void SetToggleWireframeCallback(const std::function<void(GibEngine::World::Level*)>& toggleWireframeCallbackFunc);
			void SetToggleUiRenderCallback(const std::function<void()>& toggleUiRenderCallbackFunc);
		};
	}
}