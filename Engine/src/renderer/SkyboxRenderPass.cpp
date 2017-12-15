#include "renderer/SkyboxRenderPass.h"

GibEngine::Renderer::SkyboxRenderPass::SkyboxRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader) 
	: RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::SkyboxRenderPass::Render()
{
	graphicsApi->BindShader(shader->GetShaderId());
	
	graphicsApi->BindCamera(RenderPass::camera);

	glm::mat4 skyboxMatrix = skybox->GetInstanceMatrices().at(0)->GetEntity()->GetMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "skyboxModelMatrix"), 1, GL_FALSE, glm::value_ptr(skyboxMatrix));

	graphicsApi->BindTextureCubemap(0, skybox->GetCubemap()->GetTextureId());

	graphicsApi->DrawSkybox(skybox);

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::SkyboxRenderPass::Update(float deltaTime)
{
	if (skybox == nullptr)
	{
		return;
	}

	skybox->Update(deltaTime);
}

void GibEngine::Renderer::SkyboxRenderPass::SetSkybox(Skybox* skybox)
{
	this->skybox = skybox;

	if (skybox == nullptr)
	{
		return;
	}

	MeshUploadTicket* ticket = graphicsApi->UploadMesh(skybox);
	skybox->SetMeshUploadTicket(ticket);

	graphicsApi->UploadTextureCubemap(skybox->GetCubemap());
}
