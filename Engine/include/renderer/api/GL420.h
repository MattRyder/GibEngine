#pragma once

#include "IGraphicsApi.h"
#include "renderer/UniformBufferManager.h"
#include "glfw/glfw_callback.h"

namespace GibEngine
{
    namespace Renderer
    {
        namespace API
        {
            class GL420 : public IGraphicsApi
            {
				struct ShaderCache
				{
					std::map<const char*, int> uniformLocations;
				};

				ShaderCache shaderCaches[256] = { };
				UniformBufferManager* uniformBufferManager;

            public:
				GL420();
				virtual ~GL420() override;

				virtual const std::string GetVersionString() override { return "420"; }

				virtual void BlitFramebuffer(unsigned int framebufferSource, unsigned int framebufferDest, unsigned int framebufferWidth, unsigned int framebufferHeight, unsigned int framebufferFlags) override;

                virtual void BindCamera(CameraBase *camera) override;
                virtual void BindFramebuffer(const GibEngine::Renderer::Framebuffer& framebuffer) override;
				virtual void BindMaterial(GibEngine::Material *material) override;
				virtual void BindShader(unsigned int shaderId) override;
                virtual void BindTexture2D(unsigned int textureSlot, unsigned int textureId) override;
				virtual void BindTextureCubemap(unsigned int textureSlot, unsigned int cubemapTextureId) override;

				virtual void BindUniform1f(unsigned int uniformLocation, unsigned int uniformValue) override;
				virtual void BindUniform3fv(unsigned int uniformLocation, unsigned int count, const float *uniformValue) override;
				virtual void BindUniform4fv(unsigned int uniformLocation, unsigned int count, const float * uniformValue) override;

                virtual bool CreateFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer, int framebufferWidth, int framebufferHeight) override;
				virtual void DeleteFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer) override;
				virtual void ClearFramebuffer() override;

                virtual void DrawPrimitive(const MeshUploadTicket& meshUploadTicket) override;
                virtual void DrawMesh(const GibEngine::Mesh& mesh, size_t instanceCount) override;
                virtual void DrawSkybox(const GibEngine::MeshUploadTicket& skyboxMeshTicket) override;

				virtual int GetUniformLocation(const char* uniformName) override;

				virtual unsigned char* ReadFramebuffer(GibEngine::Renderer::Framebuffer *framebuffer) override;
				virtual unsigned char* ReadFramebufferTexture(GibEngine::Renderer::Framebuffer *framebuffer, GibEngine::Renderer::FramebufferType framebufferTextureType) override;

				virtual void RegisterCamera(std::shared_ptr<CameraBase> camera) override;

				virtual bool UpdateMeshInstances(const MeshUploadTicket& meshUploadTicket, const std::vector<glm::mat4>& instanceMatrixList) override;
				virtual bool UpdateCamera(const CameraBase& camera) override;

				virtual std::shared_ptr<MeshUploadTicket> UploadMesh(const std::vector<GibEngine::Vertex>& vertexList, const std::vector<unsigned int>& indexList) override;
                virtual void UploadTexture2D(unsigned int* textureId, const TextureData& textureData, SamplerFiltering filtering, SamplerEdgeClamping edgeClamping) override;
                virtual void UploadTextureCubemap(unsigned int* textureId, std::vector<TextureData>& cubemapSideData) override;

                virtual void UnbindFramebuffer() override;
				virtual void UnbindShader() override;

			};
        }
    }
}