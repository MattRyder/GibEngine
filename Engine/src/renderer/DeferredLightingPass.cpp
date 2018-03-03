#include "renderer/DeferredLightingPass.h"

GibEngine::Renderer::DeferredLightingPass::DeferredLightingPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader *shader, Framebuffer* framebuffer)
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
			//BindLights(visibleSet);
	//		//lastVisibleSet = visibleSet;
	//	}
	//}

	buffer_t buffer = framebuffer->GetBuffer();
	const char* framebufferStrings[FRAMEBUFFERTYPE_LAST] = { "framebuffer_Position", "framebuffer_Albedo", "framebuffer_Normal", "framebuffer_Texture" };

	for (unsigned int i = 0; i < FRAMEBUFFER_TEXTURE_COUNT; i++)
	{
		unsigned int fbTextureLocation = graphicsApi->GetUniformLocation(framebufferStrings[i]); 

		graphicsApi->BindUniform1f(fbTextureLocation, i);

		graphicsApi->BindTexture2D(i, buffer.textures[i]);
	}

	glDepthMask(GL_FALSE);
	graphicsApi->DrawPrimitive(*quadMesh->GetMeshUploadTicket());
	glDepthMask(GL_TRUE);

	graphicsApi->UnbindShader();
}