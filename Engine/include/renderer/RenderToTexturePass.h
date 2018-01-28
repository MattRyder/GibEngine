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
			RenderToTexturePass(API::IGraphicsApi* graphicsApi, Shader *shader, Framebuffer* framebuffer);
			virtual void Render(const Scene::VisibleSet* visibleSet) override;
		};
	}
}