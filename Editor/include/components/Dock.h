#pragma once

#include "IComponent.h"
#include "imgui_dock.h"
#include "EntityInspector.h"
#include "ContentBrowser.h"

#include "world/World.h"
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

			Dock(GibEngine::World::Level* level, GibEngine::Renderer::Pipeline* pipeline);
			virtual void Render() override;

			Dock::Type GetSelectedDock() const;

		private:
			GibEngine::World::Level* level;
			GibEngine::Renderer::Pipeline* pipeline;
			
			Components::ContentBrowser* cbrowser = nullptr;
			EntityInspector<GibEngine::Model>* inspector = nullptr;
			Dock::Type selectedDock = Dock::Type::GAME;
		};
	}
}