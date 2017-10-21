#pragma once

#include <map>

#include "RenderPass.h"
#include "RenderPassType.h"
#include "ForwardRenderPass.h"
#include "SkyboxRenderPass.h"
#include "DeferredGeometryPass.h"
#include "DeferredLightingPass.h"
#include "RenderToTexturePass.h"

#include "UniformBufferManager.h"
#include "Framebuffer.h"

#include "api/GL420.h"
#include "api/GLES3.h"

namespace GibEngine
{
	namespace Renderer
	{
		enum class ShaderLanguage
		{
			// OpenGL ES 3.00
			GLES_3,
			
			// OpenGL GLSL 4.20
			GLSL_420,
		};

		class Pipeline
		{
			static const char* ShaderLanguageStrings[];

			Framebuffer* framebuffer;
			CameraBase* camera;

			API::IGraphicsApi *graphicsApi = nullptr;
			ShaderLanguage shaderLanguage;
			std::map<RenderPassType, RenderPass*> passes;

			const char* GetShaderLanguageString(ShaderLanguage language);
			void SelectGraphicsApi(ShaderLanguage shaderLanguage);

		public:
			Pipeline(int framebufferWidth, int framebufferHeight, ShaderLanguage supportedShaderLanguage, CameraBase *camera);
			~Pipeline();

			void AddPass(RenderPassType type);
			void Render();
			void Update(float deltaTime);

			RenderPass* GetRenderPass(RenderPassType type);

			void SetCameraBase(CameraBase *camera);
		};
	}
}