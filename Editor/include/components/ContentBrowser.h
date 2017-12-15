#pragma once

#include <map>
#include "nfd.h"

#include "File.h"
#include "Entity.h"
#include "IComponent.h"
#include "Observer.h"
#include "world/Level.h"
#include "renderer/Pipeline.h"

namespace GibEditor
{
	namespace Components
	{
		class ContentBrowser : public IComponent
		{
			GibEngine::World::Level* level;
			GibEngine::Renderer::Pipeline* pipeline;

			Observer* contentDirectoryObserver;
			std::map<GibEngine::EntityType, std::vector<GibEngine::File*>> availableContent;

			void SetupAvailableContentMap();

		public:
			ContentBrowser(GibEngine::World::Level* level, GibEngine::Renderer::Pipeline* pipeline);
			~ContentBrowser();
			
			void Render() override;

			void SetObserver(Observer* observer);
		};
	}
}