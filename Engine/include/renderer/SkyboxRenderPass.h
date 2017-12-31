#pragma once

#include "renderer/RenderPass.h"
#include "Skybox.h"

namespace GibEngine
{
	namespace Renderer
	{
		class SkyboxRenderPass : public RenderPass
		{
		public:
			SkyboxRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader);

			virtual void Render(const Scene::VisibleSet& visibleSet) override;
			void UploadSkybox(Skybox* skybox);
		};

	}
}