#include "renderer/ForwardRenderPass.h"

GibEngine::Renderer::ForwardRenderPass::ForwardRenderPass(UniformBufferManager* uniformBufferManager, Shader *shader) : RenderPass(uniformBufferManager, shader) { }

void GibEngine::Renderer::ForwardRenderPass::Render()
{
	RenderPass::SetCameraBase(RenderPass::camera);
	shader->Begin();

	for (Model* model : drawablesList)
	{
		for (Mesh* mesh : model->GetMeshes())
		{
			mesh->LoadMaterial(shader->GetShaderId());
			glBindVertexArray(mesh->GetVAO());
			glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndicesSize(), GL_UNSIGNED_INT, 0, mesh->GetInstanceCount());
			glBindVertexArray(0);
		}
	}

	shader->End();
}

void GibEngine::Renderer::ForwardRenderPass::Update(float deltaTime)
{
	for (Model* model : drawablesList)
	{
		model->Update(deltaTime);
	}
}

