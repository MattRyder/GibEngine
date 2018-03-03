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
		public:
			DeferredLightingPass(std::shared_ptr<Renderer::API::IGraphicsApi>, Shader *shader, Framebuffer* framebuffer);
			void Render(const Scene::VisibleSet& visibleSet) override;
		};
	}
}