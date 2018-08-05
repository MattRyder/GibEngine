#pragma once

#include "renderer/RenderPass.h"
#include "Texture.h"

namespace GibEngine
{
	namespace Renderer
	{
		class RenderToTexturePass : public RenderPass
		{
		public:
			RenderToTexturePass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, std::shared_ptr<Shader> shader, Framebuffer* framebuffer);
			virtual void Render(const Scene::VisibleSet& visibleSet) override;
		};
	}
}