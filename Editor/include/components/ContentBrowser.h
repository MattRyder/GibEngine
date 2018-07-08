#pragma once

#include <map>
#include "nfd.h"

#include "BaseEntity.h"
#include "IComponent.h"
#include "Observer.h"
#include "MeshService.h"
#include "renderer/api/IGraphicsApi.h"
#include "filesystem/IFileSystem.h"

namespace GibEditor
{
	namespace Components
	{
		class ContentBrowser : public IComponent
		{
			std::shared_ptr<GibEngine::BaseEntity> rootEntity;
			std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> graphicsApi;
			std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem;

			std::vector<std::string> meshFileList;

			json11::Json defaultGenerationData;

		public:
			ContentBrowser(
				std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem,
				std::shared_ptr<GibEngine::Renderer::API::IGraphicsApi> graphicsApi,
				std::shared_ptr<GibEngine::BaseEntity> rootEntity);
			
			void Render() override;
		};
	}
}