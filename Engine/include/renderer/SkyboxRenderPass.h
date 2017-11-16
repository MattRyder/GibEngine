#pragma once

#include "renderer/RenderPass.h"
#include "Skybox.h"

namespace GibEngine
{
	namespace Renderer
	{
		class SkyboxRenderPass : public RenderPass
		{
			Skybox *skybox = nullptr;

		public:
			SkyboxRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader);

			virtual void Render();
			void Update(float deltaTime);

			void SetSkybox(Skybox *skybox);
		};

	}
}