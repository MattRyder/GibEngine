#pragma once

#include "IComponent.h"
#include "scene/Node.h"

namespace GibEditor
{
	namespace Components
	{
		class Menubar : IComponent
		{
			std::shared_ptr<GibEngine::Scene::Node> rootSceneNode;
			std::function<void()> exitCallback, newWorldCallbackFunc, openFileDialogCallbackFunc,  toggleUiRenderCallbackFunc;
			std::function<void()> saveFileDialogCallbackFunc;

		public:
			Menubar(std::shared_ptr<GibEngine::Scene::Node> node);
			virtual void Render() override;

			void SetSceneNode(std::shared_ptr<GibEngine::Scene::Node> node);

			void SetOnNewWorldCallback(const std::function<void()>& newWorldCallbackFunc);
			void SetOnExitCallback(const std::function<void()>& exitCallbackFunc);
			void SetOnOpenFileDialogCallback(const std::function<void()>& openFileDialogCallbackFunc);
			void SetOnSaveFileDialogCallback(const std::function<void()>& saveFileDialogCallbackFunc);
			void SetToggleUiRenderCallback(const std::function<void()>& toggleUiRenderCallbackFunc);
		};
	}
}