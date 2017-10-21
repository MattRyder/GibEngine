#include "renderer/SkyboxRenderPass.h"

GibEngine::Renderer::SkyboxRenderPass::SkyboxRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader) 
	: RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::SkyboxRenderPass::Render()
{
	graphicsApi->BindShader(shader->GetShaderId());
	
	graphicsApi->BindCamera(RenderPass::camera);

	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "skyboxModelMatrix"), 1, GL_FALSE, glm::value_ptr(skybox->GetModelMatrix()));

	graphicsApi->BindTextureCubemap(0, skybox->GetCubemap()->GetTextureId());

	graphicsApi->DrawSkybox(skybox);

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::SkyboxRenderPass::Update(float deltaTime)
{
	glm::mat4 matrix = glm::rotate(skybox->GetModelMatrix(), glm::radians(skybox->SKYBOX_MOVE_SPEED * deltaTime), glm::vec3(0, 1, 0));
	skybox->SetModelMatrix(matrix);
}

void GibEngine::Renderer::SkyboxRenderPass::SetSkybox(Skybox* skybox)
{
	this->skybox = skybox;

	MeshUploadTicket* ticket = graphicsApi->UploadMesh(skybox);
	skybox->SetMeshUploadTicket(ticket);

	graphicsApi->UploadTextureCubemap(skybox->GetCubemap());
}
