#pragma once

#include "renderer/RenderPass.h"

namespace GibEngine
{
	namespace Renderer
	{
		class DeferredGeometryPass : public RenderPass
		{
		public:
			DeferredGeometryPass(API::IGraphicsApi* graphicsApi, Shader *shader, Framebuffer *framebuffer);
			void Render() override;
			void Update(float deltaTime) override;
		};
	}
}