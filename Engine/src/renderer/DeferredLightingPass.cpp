#include "renderer/DeferredLightingPass.h"

GibEngine::Renderer::DeferredLightingPass::DeferredLightingPass(API::IGraphicsApi* graphicsApi, Shader *shader, Framebuffer* framebuffer)
	: RenderPass(graphicsApi, shader, framebuffer)
{
	LoadQuadData();
}

void GibEngine::Renderer::DeferredLightingPass::Render()
{
	const int FRAMEBUFFER_TEXTURE_COUNT = 3;

	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(RenderPass::camera);

	RenderPass::BindLights();

	buffer_t buffer = framebuffer->GetBuffer();
	const char* framebufferStrings[FRAMEBUFFERTYPE_LAST] = { "framebuffer_Position", "framebuffer_Albedo", "framebuffer_Normal" };

	for (unsigned int i = 0; i < FRAMEBUFFER_TEXTURE_COUNT; i++)
	{
		unsigned int fbTextureLocation = graphicsApi->GetUniformLocation(framebufferStrings[i]); 

		graphicsApi->BindUniform1f(fbTextureLocation, i);

		graphicsApi->BindTexture2D(i, buffer.textures[i]);
	}

	graphicsApi->DrawPrimitive(quadMesh->GetMeshUploadTicket());

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::DeferredLightingPass::Update(float deltaTime)
{
	for (auto light : lights)
	{
		light->Update(deltaTime);
	}

	FlagLightingBindRequired();
}