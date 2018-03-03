#pragma once

#include "renderer/RenderPass.h"

namespace GibEngine
{
	namespace Renderer
	{
		class DeferredGeometryPass : public RenderPass
		{
		public:
			DeferredGeometryPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader* shader);
			void Render(const Scene::VisibleSet& visibleSet) override;
		};
	}
}