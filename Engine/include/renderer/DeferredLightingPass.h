#pragma once

#include "RenderPass.h"
#include "Framebuffer.h"
#include "PointLight.h"

namespace GibEngine
{
	namespace Renderer
	{
		class DeferredLightingPass : public RenderPass
		{
			std::shared_ptr<Framebuffer> ssaoFramebuffer;

		public:
			DeferredLightingPass(std::shared_ptr<Renderer::API::IGraphicsApi>, std::shared_ptr<Shader> shader, Framebuffer* framebuffer);
			void Render(const Scene::VisibleSet& visibleSet) override;

			void SetSsaoFramebuffer(std::shared_ptr<Framebuffer> ssaoFramebuffer);
		};
	}
}