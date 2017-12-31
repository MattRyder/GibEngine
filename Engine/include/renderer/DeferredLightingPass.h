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
			DeferredLightingPass(API::IGraphicsApi* graphicsApi, Shader *shader, Framebuffer* framebuffer);
			void Render(const Scene::VisibleSet& visibleSet) override;
		};
	}
}