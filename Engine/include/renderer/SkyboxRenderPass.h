#pragma once

#include "renderer/RenderPass.h"
#include "Skybox.h"

namespace GibEngine
{
	namespace Renderer
	{
		class SkyboxRenderPass : public RenderPass
		{
			Skybox *skybox;

		public:
			SkyboxRenderPass(UniformBufferManager* uniformBufferManager, Shader *shader);

			virtual void Render();
			void Update(float deltaTime);

			void SetSkybox(Skybox *skybox);
		};

	}
}