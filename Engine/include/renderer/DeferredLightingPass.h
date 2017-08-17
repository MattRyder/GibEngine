#pragma once

#include "RenderPass.h"
#include "Framebuffer.h"

namespace GibEngine
{
	namespace Renderer
	{
		class DeferredLightingPass : public RenderPass
		{
			static GLfloat QuadTextureData[];

			//std::vector<Light> lights;

			GLuint quadVAO, quadVBO;
			void LoadQuadData();
			
		public:
			DeferredLightingPass(UniformBufferManager* uniformBufferManager, Shader* shader, Framebuffer* framebuffer);
			void Render() override;
			void Update(float deltaTime) override;
		};
	}
}