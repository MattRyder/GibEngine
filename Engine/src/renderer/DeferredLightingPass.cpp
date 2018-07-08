#include "renderer/DeferredLightingPass.h"

GibEngine::Renderer::DeferredLightingPass::DeferredLightingPass(
	std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, 
	Shader* shader,
	Framebuffer* framebuffer)
	: RenderPass(graphicsApi, shader, framebuffer)
{
	LoadQuadData();
}

void GibEngine::Renderer::DeferredLightingPass::Render(const Scene::VisibleSet& visibleSet)
{
	const int FRAMEBUFFER_TEXTURE_COUNT = 3;

	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(visibleSet.GetCamera().get());

	//if (visibleSet.GetLights().size() > 0 && lastVisibleSet.GetLights().size() > 0)
	//{
	//	if (std::is_permutation(visibleSet.GetLights().begin(), visibleSet.GetLights().end(), lastVisibleSet.GetLights().begin()))
	//	{
			BindLights(visibleSet);
	//		//lastVisibleSet = visibleSet;
	//	}
	//}

	buffer_t buffer = framebuffer->GetBuffer();
	const char* framebufferStrings[FRAMEBUFFER_TEXTURE_COUNT] = { "framebuffer_Position", "framebuffer_Albedo", "framebuffer_Normal" };

	for (unsigned int i = 0; i < FRAMEBUFFER_TEXTURE_COUNT; i++)
	{
		unsigned int fbTextureLocation = graphicsApi->GetUniformLocation(framebufferStrings[i]); 

		graphicsApi->BindUniform1f(fbTextureLocation, i);

		graphicsApi->BindTexture2D(i, buffer.textures[i]);
	}

	if (ssaoFramebuffer)
	{
		const auto ssaoUniformTextureLocation = FRAMEBUFFER_TEXTURE_COUNT + 1;
		const auto ssaoLocation = graphicsApi->GetUniformLocation("framebuffer_SSAO");
		graphicsApi->BindUniform1f(ssaoLocation, ssaoUniformTextureLocation);
		graphicsApi->BindTexture2D(ssaoUniformTextureLocation, ssaoFramebuffer->GetBuffer().textures[0]);
	}

	glDepthMask(GL_FALSE);
	graphicsApi->DrawPrimitive(*quadMesh->GetMeshUploadTicket());
	glDepthMask(GL_TRUE);

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::DeferredLightingPass::SetSsaoFramebuffer(std::shared_ptr<Framebuffer> ssaoFramebuffer)
{
	this->ssaoFramebuffer = ssaoFramebuffer;
}
