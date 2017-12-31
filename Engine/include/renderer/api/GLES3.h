#pragma once

#include "IGraphicsApi.h"

namespace GibEngine
{
    namespace Renderer
    {
        namespace API
        {
            class GLES3 : public IGraphicsApi
            {
            public:
				GLES3() = default;
				virtual ~GLES3() override;

				virtual void BlitFramebuffer(unsigned int framebufferSource, unsigned int framebufferDest, unsigned int framebufferWidth, unsigned int framebufferHeight, unsigned int framebufferFlags) override;

                virtual void BindCamera(GibEngine::CameraBase *camera) override;
                virtual void BindFramebuffer(GibEngine::Renderer::Framebuffer *framebuffer) override;
				virtual void BindMaterial(GibEngine::Material *material) override;
				virtual void BindShader(unsigned int shaderId) override;
				virtual void BindTexture2D(unsigned int textureSlot, unsigned int textureId) override;
				virtual void BindTextureCubemap(unsigned int textureSlot, unsigned int cubemapTextureId) override;

				virtual void BindUniform1f(unsigned int uniformLocation, unsigned int uniformValue) override;
				virtual void BindUniform3fv(unsigned int uniformLocation, unsigned int count, const float *uniformValue) override;

                virtual bool CreateFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer, int framebufferWidth, int framebufferHeight) override;
				virtual void DeleteFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer) override;
				virtual void ClearFramebuffer() override;

                virtual void DrawPrimitive(MeshUploadTicket* meshUploadTicket) override;
                virtual void DrawMesh(GibEngine::Mesh *mesh, int instanceCount) override;
                virtual void DrawSkybox(GibEngine::Skybox *skybox) override;

				virtual int GetUniformLocation(const char* uniformName) override;

				virtual bool UpdateMeshInstances(MeshUploadTicket *meshUploadTicket, std::vector<glm::mat4> instanceMatrixList) override;
				virtual bool UpdateCamera(CameraBase *camera) override;

				virtual MeshUploadTicket* UploadMesh(std::vector<GibEngine::Vertex> vertexList, std::vector<unsigned int> indexList) override;
                virtual MeshUploadTicket* UploadMesh(GibEngine::Mesh *mesh) override;
                virtual void UploadTexture2D(GibEngine::Texture *texture) override;    
                virtual void UploadTextureCubemap(GibEngine::Texture *texture) override;

                virtual void UnbindFramebuffer() override;
				virtual void UnbindShader() override;

				virtual unsigned char * ReadFramebuffer(GibEngine::Renderer::Framebuffer * framebuffer) override;
				virtual unsigned char* ReadFramebufferTexture(GibEngine::Renderer::Framebuffer *framebuffer, GibEngine::Renderer::FramebufferType framebufferTextureType) override;
			};
        }
    }
}