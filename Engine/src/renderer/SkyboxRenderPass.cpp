#include "renderer/SkyboxRenderPass.h"

GibEngine::Renderer::SkyboxRenderPass::SkyboxRenderPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, std::shared_ptr<Shader> shader)
	: RenderPass(graphicsApi, shader), skyboxUniformLocation(-1) { }

void GibEngine::Renderer::SkyboxRenderPass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	const auto& skybox = visibleSet.GetSkyboxNode();
	if (!skybox)
	{
		return;
	}

	graphicsApi->BindShader(shader->GetShaderId());
	
	// GL4+ uses UBOs so this isn't required, but is for GLES3!
	//graphicsApi->BindCamera(visibleSet.GetCamera());

	if (skyboxUniformLocation == -1)
	{
		skyboxUniformLocation = graphicsApi->GetUniformLocation("skyboxModelMatrix");
	}

	glm::mat4 skyboxMatrix = skybox->GetWorldTransform().GetTransformMatrix();
	glUniformMatrix4fv(skyboxUniformLocation, 1, GL_FALSE, glm::value_ptr(skyboxMatrix));

	graphicsApi->BindTextureCubemap(0, skybox->GetTexture()->GetTextureId());

	graphicsApi->DrawSkybox(*skybox->GetMeshUploadTicket());

	graphicsApi->UnbindShader();
}