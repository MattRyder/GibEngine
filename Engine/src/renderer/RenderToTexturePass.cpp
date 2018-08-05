#include "renderer/RenderToTexturePass.h"

GibEngine::Renderer::RenderToTexturePass::RenderToTexturePass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, std::shared_ptr<Shader> shader, std::shared_ptr<Framebuffer> framebuffer)
	: RenderPass(graphicsApi, shader, framebuffer)
{
	LoadQuadData();
}

void GibEngine::Renderer::RenderToTexturePass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	const int TEXTURE_SLOT_ZERO = 0;
	const char* TEXTURE_SLOT_NAME = "renderedTexture";

	graphicsApi->BindShader(shader->GetShaderId());

	GLint textureLocation = graphicsApi->GetUniformLocation(TEXTURE_SLOT_NAME);

	if (textureLocation == -1)
	{
		Logger::Instance->error("[RenderToTexturePass::Render] Cannot find renderable Texture texture2D sampler: {}", TEXTURE_SLOT_NAME);
	}

	glUniform1i(textureLocation, static_cast<float>(TEXTURE_SLOT_ZERO));

	graphicsApi->BindTexture2D(TEXTURE_SLOT_ZERO, framebuffer->GetBuffer().framebufferId);

	graphicsApi->DrawPrimitive(*quadMesh->GetMeshUploadTicket());

	graphicsApi->UnbindShader();
}