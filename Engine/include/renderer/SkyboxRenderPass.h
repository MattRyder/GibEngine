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

			void SetSkybox(Skybox *skybox);
		};

	}
}