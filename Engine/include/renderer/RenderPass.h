#pragma once

#include <map>
#include <vector>

#include "scene/VisibleSet.h"
#include "Shader.h"
#include "FreeCamera.h"
#include "UniformBufferManager.h"
#include "Framebuffer.h"
#include "PointLight.h"
#include "api/IGraphicsApi.h"

namespace GibEngine
{
	namespace Renderer
	{
		class RenderPass
		{
			bool passEnabled = false;
			bool lightingBindRequired;

			void BindLightUniform3f(const char* lightUniformName, const glm::vec3 lightUniformValue);

		protected:
			Shader* shader;
			Framebuffer* framebuffer;
			
			Renderer::API::IGraphicsApi* graphicsApi;

			static GLfloat QuadTextureData[];
			Mesh *quadMesh;

			void LoadQuadData();

		public:
			RenderPass(API::IGraphicsApi* graphicsApi, Shader* shader);
			RenderPass(API::IGraphicsApi* graphicsApi, Shader* shader, Framebuffer* framebuffer);

			virtual ~RenderPass();

			virtual void Render(const Scene::VisibleSet* visibleSet);

			Shader* GetShader() const;

			bool IsEnabled() const;

			void BindLights(const Scene::VisibleSet* visibleSet);
			void FlagLightingBindRequired();

			void TakeScreenshot();

			void SetPassEnabled(bool value);
		};
	}
}