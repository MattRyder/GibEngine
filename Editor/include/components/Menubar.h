#pragma once

#include "IComponent.h"
#include "BaseEntity.h"

namespace GibEditor
{
	namespace Components
	{
		class Menubar : IComponent
		{
			std::shared_ptr<GibEngine::BaseEntity> rootEntity;
			std::function<void()> exitCallback, newWorldCallbackFunc, openFileDialogCallbackFunc,  toggleUiRenderCallbackFunc;
			std::function<void()> saveFileDialogCallbackFunc;

		public:
			Menubar();
			virtual void Render() override;

			void SetRootEntity(std::shared_ptr<GibEngine::BaseEntity> rootEntity);

			void SetOnNewWorldCallback(const std::function<void()>& newWorldCallbackFunc);
			void SetOnExitCallback(const std::function<void()>& exitCallbackFunc);
			void SetOnOpenFileDialogCallback(const std::function<void()>& openFileDialogCallbackFunc);
			void SetOnSaveFileDialogCallback(const std::function<void()>& saveFileDialogCallbackFunc);
			void SetToggleUiRenderCallback(const std::function<void()>& toggleUiRenderCallbackFunc);
		};
	}
}