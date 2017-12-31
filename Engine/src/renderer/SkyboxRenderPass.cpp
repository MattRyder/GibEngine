#include "renderer/SkyboxRenderPass.h"

GibEngine::Renderer::SkyboxRenderPass::SkyboxRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader) 
	: RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::SkyboxRenderPass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	if (visibleSet.GetSkyboxNode() == nullptr)
	{
		return;
	}

	graphicsApi->BindShader(shader->GetShaderId());
	
	graphicsApi->BindCamera(visibleSet.GetCamera());

	glm::mat4 skyboxMatrix = visibleSet.GetSkyboxNode()->GetWorldTransform();
	glUniformMatrix4fv(
		glGetUniformLocation(shader->GetShaderId(), "skyboxModelMatrix"), 1, GL_FALSE, glm::value_ptr(skyboxMatrix)
	);

	auto skybox = reinterpret_cast<Skybox*>(visibleSet.GetSkyboxNode()->GetEntity());
	if (skybox->GetCubemap()->GetTextureId() == 0)
	{
		UploadSkybox(skybox);
	}

	graphicsApi->BindTextureCubemap(0, skybox->GetCubemap()->GetTextureId());

	graphicsApi->DrawSkybox(skybox);

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::SkyboxRenderPass::UploadSkybox(Skybox* skybox)
{
	if (skybox == nullptr)
	{
		return;
	}

	MeshUploadTicket* ticket = graphicsApi->UploadMesh(skybox);
	skybox->SetMeshUploadTicket(ticket);

	graphicsApi->UploadTextureCubemap(skybox->GetCubemap());
}
