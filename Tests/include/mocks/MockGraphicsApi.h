#pragma once

#include "gmock/gmock.h"
#include "renderer/api/IGraphicsApi.h"

namespace GibEngine {
	namespace Renderer {
		namespace API {

			class MockGraphicsApi : public IGraphicsApi {
			public:
				MOCK_METHOD0(GetVersionString,
					const std::string());
				MOCK_METHOD5(BlitFramebuffer,
					void(unsigned int framebufferSource, unsigned int framebufferDest, unsigned int framebufferWidth, unsigned int framebufferHeight, unsigned int framebufferFlags));
				MOCK_METHOD1(BindCamera,
					void(CameraBase *camera));
				MOCK_METHOD1(BindFramebuffer,
					void(const GibEngine::Renderer::Framebuffer& framebuffer));
				MOCK_METHOD1(BindMaterial,
					void(GibEngine::Material *material));
				MOCK_METHOD1(BindShader,
					void(unsigned int shaderId));
				MOCK_METHOD2(BindTexture2D,
					void(unsigned int textureSlot, unsigned int textureId));
				MOCK_METHOD2(BindTextureCubemap,
					void(unsigned int textureSlot, unsigned int cubemapTextureId));
				MOCK_METHOD2(BindUniform1f,
					void(unsigned int uniformLocation, unsigned int uniformValue));
				MOCK_METHOD3(BindUniform3fv,
					void(unsigned int uniformLocation, unsigned int count, const float *uniformValue));
				MOCK_METHOD3(BindUniform4fv,
					void(unsigned int uniformLocation, unsigned int count, const float * uniformValue));
				MOCK_METHOD3(CreateFramebuffer,
					bool(GibEngine::Renderer::Framebuffer* framebuffer, int framebufferWidth, int framebufferHeight));
				MOCK_METHOD1(DeleteFramebuffer,
					void(GibEngine::Renderer::Framebuffer* framebuffer));
				MOCK_METHOD0(ClearFramebuffer,
					void());
				MOCK_METHOD1(DrawPrimitive,
					void(const MeshUploadTicket& meshUploadTicket));
				MOCK_METHOD2(DrawMesh,
					void(const GibEngine::Mesh& mesh, size_t instanceCount));
				MOCK_METHOD1(DrawSkybox,
					void(const GibEngine::MeshUploadTicket& skyboxMeshTicket));
				MOCK_METHOD1(GetUniformLocation,
					int(const char* uniformName));
				MOCK_METHOD1(ReadFramebuffer,
					unsigned char*(GibEngine::Renderer::Framebuffer *framebuffer));
				MOCK_METHOD2(ReadFramebufferTexture,
					unsigned char*(GibEngine::Renderer::Framebuffer *framebuffer, GibEngine::Renderer::FramebufferType framebufferTextureType));
				MOCK_METHOD1(RegisterCamera,
					void(std::shared_ptr<CameraBase> camera));
				MOCK_METHOD2(UpdateMeshInstances,
					bool(const MeshUploadTicket& meshUploadTicket, const std::vector<glm::mat4>& instanceMatrixList));
				MOCK_METHOD1(UpdateCamera,
					bool(const CameraBase& camera));
				MOCK_METHOD2(UploadMesh,
					std::shared_ptr<MeshUploadTicket>(const std::vector<GibEngine::Vertex>& vertexList, const std::vector<unsigned int>& indexList));
				MOCK_METHOD4(UploadTexture2D,
					void(unsigned int* textureId, const TextureData& textureData, SamplerFiltering filtering, SamplerEdgeClamping edgeClamping));
				MOCK_METHOD2(UploadTextureCubemap,
					void(unsigned int* textureId, std::vector<TextureData>& cubemapSideData));
				MOCK_METHOD0(UnbindFramebuffer,
					void());
				MOCK_METHOD0(UnbindShader,
					void());
			};

		}  // namespace API
	}  // namespace Renderer
}  // namespace GibEngine