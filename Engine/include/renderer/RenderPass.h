#pragma once

#include <map>
#include <vector>

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

			CameraBase* camera;
			std::vector<Model*> drawablesList;
			std::vector<LightBase*> lights;

			static GLfloat QuadTextureData[];
			Mesh *quadMesh;

			void LoadQuadData();

		public:
			RenderPass(API::IGraphicsApi* graphicsApi, Shader* shader);
			RenderPass(API::IGraphicsApi* graphicsApi, Shader* shader, Framebuffer* framebuffer);

			virtual ~RenderPass();

			virtual void Render();
			virtual void Update(float deltaTime) = 0;

			virtual void AddDrawable(Model* drawable);
			virtual void AddLight(LightBase* light);
			virtual void SetCameraBase(CameraBase* camera);

			Shader* GetShader() const;
			std::vector<LightBase*> GetLights() const;

			bool IsEnabled() const;

			void BindLights();
			void FlagLightingBindRequired();

			void TakeScreenshot();

			void SetPassEnabled(bool value);
		};
	}
}