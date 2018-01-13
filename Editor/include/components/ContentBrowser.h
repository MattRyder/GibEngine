#pragma once

#include <map>
#include "nfd.h"

#include "File.h"
#include "Entity.h"
#include "IComponent.h"
#include "Observer.h"
#include "scene/Node.h"
#include "renderer/Pipeline.h"
#include "MeshService.h"

namespace GibEditor
{
	namespace Components
	{
		class ContentBrowser : public IComponent
		{
			GibEngine::Scene::Node* rootSceneNode;
			GibEngine::Renderer::Pipeline* pipeline;

			Observer* contentDirectoryObserver;
			std::map<GibEngine::EntityType, std::vector<GibEngine::File*>> availableContent;

			json11::Json defaultGenerationData;

			void SetupAvailableContentMap();

		public:
			ContentBrowser(GibEngine::Scene::Node* rootSceneNode, GibEngine::Renderer::Pipeline* pipeline);
			~ContentBrowser();
			
			void Render() override;

			void SetObserver(Observer* observer);
		};
	}
}