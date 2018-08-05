#pragma once

#include <map>

#include "RenderPass.h"
#include "ForwardRenderPass.h"
#include "SkyboxRenderPass.h"
#include "DeferredGeometryPass.h"
#include "DeferredLightingPass.h"
#include "RenderToTexturePass.h"
#include "SsaoPass.h"

#include "filesystem/IFileSystem.h"

#include "UniformBufferManager.h"
#include "Framebuffer.h"

#include "api/GL420.h"
#include "api/GLES3.h"

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
			bool renderingPaused = false;

			std::shared_ptr<Framebuffer> framebuffer;

			RenderPass* passes[static_cast<int>(RenderPass::Type::RENDERPASSTYPE_LAST)] = {};

			std::vector<std::shared_ptr<CameraBase>> cameras;
			std::shared_ptr<FileSystem::IFileSystem> fileSystem;
			std::shared_ptr<API::IGraphicsApi> graphicsApi;

		public:
			Pipeline(int framebufferWidth, int framebufferHeight, std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem, std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi);
			~Pipeline();

			void AddCamera(std::shared_ptr<CameraBase> camera);
			void AddPass(RenderPass::Type type);

			void Render(const Scene::VisibleSet& visibleSet, const float deltaTime);

			bool IsRenderPaused();
			RenderPass* GetRenderPass(RenderPass::Type type);
			std::shared_ptr<Framebuffer> GetFramebuffer();

			void SetRenderPaused(bool renderingPaused);

			void ResizeFramebuffer(int width, int height);
		};
	}
}