#pragma once

#include <map>
#include <vector>

#include "Shader.h"
#include "FreeCamera.h"
#include "UniformBufferManager.h"
#include "Framebuffer.h"

namespace GibEngine
{
	namespace Renderer
	{
		class RenderPass
		{
			bool passEnabled = true;

		protected:
			Shader *shader;
			UniformBufferManager *uniformBufferManager;
			Framebuffer* framebuffer;

			FreeCamera *camera;
			std::vector<Model *> drawablesList;

		public:
			RenderPass(UniformBufferManager *uniformBufferManager, Shader *shader);
			RenderPass(UniformBufferManager* uniformBufferManager, Shader* shader, Framebuffer* framebuffer);

			virtual void Render();
			virtual void Update(float deltaTime) = 0;

			virtual void AddDrawable(Model *drawable);
			virtual void SetCameraBase(FreeCamera *camera);

			void TakeScreenshot(int framebufferWidth, int framebufferHeight);

			void SetPassEnabled(bool value);
		};
	}
}