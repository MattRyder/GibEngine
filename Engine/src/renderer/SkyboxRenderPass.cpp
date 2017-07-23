#include "..\..\include\renderer\SkyboxRenderPass.h"

GibEngine::Renderer::SkyboxRenderPass::SkyboxRenderPass(UniformBufferManager* uniformBufferManager, Shader * shader) : RenderPass(uniformBufferManager, shader)
{
	this->skybox = skybox;
}

void GibEngine::Renderer::SkyboxRenderPass::Render()
{
	shader->Begin();

	glDepthRange(0.999999f, 1.0f);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	glBindVertexArray(skybox->GetVAO());

	glActiveTexture(GL_TEXTURE0);
	GLuint cubemapLocation = glGetAttribLocation(shader->GetShaderId(), "skyboxCubemap");
	glUniform1i(cubemapLocation, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetCubemap()->GetTextureId());
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "skyboxModelMatrix"), 1, GL_FALSE, glm::value_ptr(skybox->GetModelMatrix()));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);

	glBindVertexArray(0);
	glDepthMask(GL_TRUE);

	shader->End();
}

void GibEngine::Renderer::SkyboxRenderPass::SetSkybox(Skybox * skybox)
{
	this->skybox = skybox;
}
