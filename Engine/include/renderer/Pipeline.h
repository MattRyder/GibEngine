#pragma once

#include <map>

#include "RenderPass.h"
#include "RenderPassType.h"
#include "ForwardRenderPass.h"
#include "SkyboxRenderPass.h"
#include "DeferredGeometryPass.h"
#include "DeferredLightingPass.h"

#include "UniformBufferManager.h"
#include "Framebuffer.h"

namespace GibEngine
{
	namespace Renderer
	{
		enum class ShaderLanguage
		{
			GLSL_130,
			GLSL_420
		};

		class Pipeline
		{
			static const char* ShaderLanguageStrings[];

			UniformBufferManager *uniformBufferManager;
			Framebuffer *framebuffer;

			ShaderLanguage shaderLanguage;
			std::map<RenderPassType, RenderPass*> passes;

			const char* GetShaderLanguageString(ShaderLanguage language);

		public:
			Pipeline(UniformBufferManager* uniformBufferManager, Framebuffer* framebuffer, ShaderLanguage supportedShaderLanguage);
			~Pipeline();

			void AddPass(RenderPassType type);
			void Render();
			void Update(float deltaTime);

			RenderPass* GetRenderPass(RenderPassType type);
		};
	}
}