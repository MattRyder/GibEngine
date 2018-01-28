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

#include "scene/Node.h"
#include "scene/VisibleSet.h"

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
			bool renderingPaused = false;

			Framebuffer* framebuffer;
			CameraBase* camera;

			API::IGraphicsApi *graphicsApi = nullptr;
			ShaderLanguage shaderLanguage;
			std::map<RenderPassType, RenderPass*> passes;

			const char* GetShaderLanguageString(ShaderLanguage language);
			void SelectGraphicsApi(ShaderLanguage shaderLanguage);

		public:
			Pipeline(int framebufferWidth, int framebufferHeight, ShaderLanguage supportedShaderLanguage);
			~Pipeline();

			void AddPass(RenderPassType type);

			void Render(const Scene::VisibleSet* visibleSet, const float deltaTime);
			void Update(float deltaTime);

			bool IsRenderPaused();
			RenderPass* GetRenderPass(RenderPassType type);
			Framebuffer* GetFramebuffer();

			void SetCameraBase(CameraBase *camera);
			void SetRenderPaused(bool renderingPaused);

			void ResizeFramebuffer(int width, int height);
		};
	}
}