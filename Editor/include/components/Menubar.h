#pragma once

#include "IComponent.h"
#include "scene/Node.h"

namespace GibEditor
{
	namespace Components
	{
		class Menubar : IComponent
		{
			GibEngine::Scene::Node* rootSceneNode;
			std::function<void()> exitCallback, openFileDialogCallbackFunc,  toggleUiRenderCallbackFunc;
			std::function<void(GibEngine::Scene::Node*)> saveFileDialogCallbackFunc;

		public:
			Menubar(GibEngine::Scene::Node*);
			virtual void Render() override;

			void SetSceneNode(GibEngine::Scene::Node* node);

			void SetOnExitCallback(const std::function<void()>& exitCallbackFunc);
			void SetOnOpenFileDialogCallback(const std::function<void()>& openFileDialogCallbackFunc);
			void SetOnSaveFileDialogCallback(const std::function<void(GibEngine::Scene::Node*)>& saveFileDialogCallbackFunc);
			void SetToggleUiRenderCallback(const std::function<void()>& toggleUiRenderCallbackFunc);
		};
	}
}