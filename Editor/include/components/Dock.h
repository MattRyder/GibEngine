#pragma once

#include "IComponent.h"
#include "imgui_dock.h"
#include "EntityInspector.h"
#include "ContentBrowser.h"

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

			Dock(std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem,
				std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> graphicsApi,
				std::shared_ptr<GibEngine::BaseEntity> rootEntity);

			virtual void Render(unsigned int gameWorldTextureId);

			Dock::Type GetSelectedDock() const;

		private:
			std::shared_ptr<GibEngine::BaseEntity> rootEntity;
			std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> graphicsApi;

			Components::ContentBrowser cbrowser;
			std::shared_ptr<Components::EntityInspector> entityInspector;

			std::string selectedSceneOutlineItem;
			Dock::Type selectedDock = Dock::Type::GAME;
			ActiveEntityInspector activeInspector = ActiveEntityInspector::NONE;
			
			void Render() override {}
			void RenderSceneTree(const std::shared_ptr<GibEngine::BaseEntity>& node);
		};
	}
}