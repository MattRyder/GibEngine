#pragma once

#include "renderer/RenderPass.h"
#include "Skybox.h"

namespace GibEngine
{
	namespace Renderer
	{
		class SkyboxRenderPass : public RenderPass
		{
			int skyboxUniformLocation;
		public:
			SkyboxRenderPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, std::shared_ptr<Shader> shader);

			virtual void Render(const Scene::VisibleSet& visibleSet) override;
		};

	}
}