#pragma once

#include <map>
#include <vector>

#include "Shader.h"
#include "FreeCamera.h"
#include "UniformBufferManager.h"

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

			FreeCamera *camera;
			std::vector<Model *> drawablesList;

		public:
			RenderPass(UniformBufferManager *uniformBufferManager, Shader *shader);

			virtual void Render();
			virtual void Update(float deltaTime) = 0;

			virtual void AddDrawable(Model *drawable);
			virtual void SetCameraBase(FreeCamera *camera);

			void TakeScreenshot(int framebufferWidth, int framebufferHeight);

			void SetPassEnabled(bool value);
		};
	}
}