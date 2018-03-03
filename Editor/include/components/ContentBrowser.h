#pragma once

#include <map>
#include "nfd.h"

#include "Entity.h"
#include "IComponent.h"
#include "Observer.h"
#include "MeshService.h"
#include "scene/Node.h"
#include "renderer/Pipeline.h"
#include "filesystem/IFileSystem.h"

namespace GibEditor
{
	namespace Components
	{
		class ContentBrowser : public IComponent
		{
			std::shared_ptr<GibEngine::Scene::Node> rootSceneNode;
			std::shared_ptr<GibEngine::Renderer::Pipeline> pipeline;
			std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem;

			Observer* contentDirectoryObserver;
			std::vector<std::string> meshFileList;

			json11::Json defaultGenerationData;

		public:
			ContentBrowser(std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem, std::shared_ptr<GibEngine::Scene::Node> rootSceneNode, std::shared_ptr<GibEngine::Renderer::Pipeline> pipeline);
			~ContentBrowser();
			
			void Render() override;

			void SetObserver(Observer* observer);
		};
	}
}