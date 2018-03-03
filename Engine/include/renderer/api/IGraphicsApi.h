#pragma once

#include "CameraBase.h"
#include "Skybox.h"
#include "renderer/Framebuffer.h"

namespace GibEngine
{
    namespace Renderer
    {
        namespace API
        {
            class IGraphicsApi
            {

            protected:
                unsigned int currentShaderID;
                
            public:
                enum BufferIndex { VERTEX, INDEX, INSTANCE_MATRIX, BUFFERINDEX_LAST };

				virtual ~IGraphicsApi() { }

				// meta information
				virtual const std::string GetVersionString() = 0;
                
				virtual void BlitFramebuffer(unsigned int framebufferSource, unsigned int framebufferDest, unsigned int framebufferWidth, unsigned int framebufferHeight, unsigned int framebufferFlags) = 0;

                virtual void BindCamera(GibEngine::CameraBase *camera) = 0;
                virtual void BindFramebuffer(const GibEngine::Renderer::Framebuffer& framebuffer) = 0;
				virtual void BindMaterial(GibEngine::Material *material) = 0;
                virtual void BindTexture2D(unsigned int textureSlot, unsigned int textureId) = 0;
				virtual void BindTextureCubemap(unsigned int textureSlot, unsigned int cubemapTextureId) = 0;
				virtual void BindShader(unsigned int shaderId) = 0;

				virtual void BindUniform1f(unsigned int uniformLocation, unsigned int uniformValue) = 0;
				virtual void BindUniform3fv(unsigned int uniformLocation, unsigned int count, const float *uniformValue) = 0;

                virtual bool CreateFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer, int framebufferWidth, int framebufferHeight) = 0;
				virtual void DeleteFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer) = 0;

				virtual void ClearFramebuffer() = 0;

                virtual void DrawPrimitive(const MeshUploadTicket& meshUploadTicket) = 0;
                virtual void DrawMesh(const GibEngine::Mesh& mesh, size_t instanceCount) = 0;
                virtual void DrawSkybox(const GibEngine::MeshUploadTicket& skyboxMeshTicket) = 0;

				virtual int GetUniformLocation(const char* uniformName) = 0;

				virtual unsigned char* ReadFramebuffer(GibEngine::Renderer::Framebuffer *framebuffer) = 0;
				virtual unsigned char* ReadFramebufferTexture(GibEngine::Renderer::Framebuffer *framebuffer, GibEngine::Renderer::FramebufferType framebufferTextureType) = 0;

				// REGISTER
				// Allocates any resources required for game objects within GFX API
				virtual void RegisterCamera(std::shared_ptr<CameraBase> camera) = 0;

				virtual bool UpdateMeshInstances(const MeshUploadTicket& meshUploadTicket, const std::vector<glm::mat4>& instanceMatrixList) = 0;
				virtual bool UpdateCamera(CameraBase *camera) = 0;

				virtual std::shared_ptr<MeshUploadTicket> UploadMesh(const std::vector<GibEngine::Vertex>& vertexList, const std::vector<unsigned int>& indexList) = 0;
                virtual void UploadTexture2D(unsigned int* textureId, const TextureData& textureData) = 0;
				virtual void UploadTextureCubemap(unsigned int* textureId, std::vector<TextureData>& cubemapSideData) = 0;
                
                virtual void UnbindFramebuffer() = 0;
				virtual void UnbindShader() = 0;
            };
        }
    }
}