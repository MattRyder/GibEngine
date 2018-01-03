#pragma once

#include "IComponent.h"
#include "imgui_dock.h"
#include "EntityInspector.h"
#include "ContentBrowser.h"

#include "scene/Node.h"
#include "renderer/Pipeline.h"

namespace GibEditor
{
	namespace Components
	{
		class Dock : IComponent
		{
		public:
			enum class Type
			{
				GAME,
				SCENE_TREE,
				ENTITY_INSPECTOR
			};

			enum class ActiveEntityInspector
			{
				NONE,
				MODEL,
				POINT_LIGHT,
			};

			Dock(GibEngine::Scene::Node* rootSceneNode, GibEngine::Renderer::Pipeline* pipeline);
			virtual void Render() override;

			Dock::Type GetSelectedDock() const;
			void RenderSceneTreeNode(GibEngine::Scene::Node* node);

		private:
			GibEngine::Scene::Node* rootSceneNode;
			GibEngine::Renderer::Pipeline* pipeline;
			
			Components::ContentBrowser* cbrowser = nullptr;
			Components::EntityInspector* entityInspector = nullptr;

			Dock::Type selectedDock = Dock::Type::GAME;
			ActiveEntityInspector activeInspector = ActiveEntityInspector::NONE;
		};
	}
}