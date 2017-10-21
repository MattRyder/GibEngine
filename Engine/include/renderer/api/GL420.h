#pragma once

#include "IGraphicsApi.h"
#include "renderer/UniformBufferManager.h"

namespace GibEngine
{
    namespace Renderer
    {
        namespace API
        {
            class GL420 : public IGraphicsApi
            {
				UniformBufferManager* uniformBufferManager;

            public:
				GL420();
				virtual ~GL420();

                virtual void BindCamera(CameraBase *camera) override;
                virtual void BindFramebuffer(GibEngine::Renderer::Framebuffer *framebuffer) override;
				virtual void BindMaterial(GibEngine::Material *material) override;
				virtual void BindShader(unsigned int shaderId) override;
                virtual void BindTexture2D(unsigned int textureSlot, unsigned int textureId) override;
				virtual void BindTextureCubemap(unsigned int textureSlot, unsigned int cubemapTextureId) override;

				virtual void BindUniform1f(unsigned int uniformLocation, unsigned int uniformValue) override;
				virtual void BindUniform3fv(unsigned int uniformLocation, unsigned int count, const float *uniformValue) override;

                virtual GibEngine::Renderer::Framebuffer* CreateFramebuffer(int framebufferWidth, int framebufferHeight) override;             
				virtual MeshUploadTicket* CreateFullscreenQuad() override;                

				virtual void ClearFramebuffer() override;

                virtual void DrawPrimitive(MeshUploadTicket* meshUploadTicket) override;
                virtual void DrawMesh(GibEngine::Mesh *mesh) override;
                virtual void DrawSkybox(GibEngine::Skybox *skybox) override;

				virtual int GetUniformLocation(const char* uniformName) override;

				virtual unsigned char* ReadFramebuffer(GibEngine::Renderer::Framebuffer *framebuffer) override;

				virtual bool UpdateMeshInstances(MeshUploadTicket *meshUploadTicket, std::vector<glm::mat4> instanceMatrixList) override;
				virtual bool UpdateCamera(CameraBase *camera) override;

				virtual MeshUploadTicket* UploadMesh(std::vector<GibEngine::Vertex> vertexList, std::vector<unsigned int> indexList) override;
                virtual MeshUploadTicket* UploadMesh(GibEngine::Mesh *mesh) override;
                virtual void UploadTexture2D(GibEngine::Texture *texture) override;     
                virtual void UploadTextureCubemap(GibEngine::Texture *texture) override;                

                virtual void UnbindFramebuffer() override;
				virtual void UnbindShader() override;
			};
        }
    }
}