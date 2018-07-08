#pragma once

#include <vector>
#include <random>
#include "RenderPass.h"

namespace GibEngine
{
	namespace Renderer
	{
		class SsaoPass : public RenderPass
		{
			std::vector<glm::vec3> kernel;
			std::shared_ptr<Texture> noiseTexture;
			std::shared_ptr<Framebuffer> ssaoFramebuffer;

			void InitializeKernel();

			float Lerp(float a, float b, float x)
			{
				return a + x * (b - a);
			}

		public:
			SsaoPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader *shader, Framebuffer* framebuffer);
			void Render(const Scene::VisibleSet& visibleSet) override;

			const std::shared_ptr<Framebuffer> GetFramebuffer() const;
		};
	}
}