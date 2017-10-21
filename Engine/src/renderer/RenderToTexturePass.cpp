#include "renderer/RenderToTexturePass.h"

GibEngine::Renderer::RenderToTexturePass::RenderToTexturePass(API::IGraphicsApi * graphicsApi, Shader * shader, Framebuffer* framebuffer)
	: RenderPass(graphicsApi, shader, framebuffer)
{
	LoadQuadData();
}

void GibEngine::Renderer::RenderToTexturePass::Render()
{
	const int TEXTURE_SLOT_ZERO = 0;
	const char* TEXTURE_SLOT_NAME = "renderedTexture";

	graphicsApi->BindShader(shader->GetShaderId());

	GLint textureLocation = glGetUniformLocation(shader->GetShaderId(), TEXTURE_SLOT_NAME);

	if (textureLocation == -1)
	{
		Logger::Instance->error("[RenderToTexturePass::Render] Cannot find renderable Texture texture2D sampler: {}", TEXTURE_SLOT_NAME);
	}

	glUniform1i(textureLocation, static_cast<float>(TEXTURE_SLOT_ZERO));

	graphicsApi->BindTexture2D(TEXTURE_SLOT_ZERO, framebuffer->GetBuffer().framebufferId);

	graphicsApi->DrawPrimitive(quadMesh->GetMeshUploadTicket());

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::RenderToTexturePass::Update(float deltaTime)
{
}

