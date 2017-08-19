#include "renderer/DeferredGeometryPass.h"

GibEngine::Renderer::DeferredGeometryPass::DeferredGeometryPass(UniformBufferManager* uniformBufferManager, Shader* shader, Framebuffer* framebuffer)
	: RenderPass(uniformBufferManager, shader, framebuffer) { }

void GibEngine::Renderer::DeferredGeometryPass::Render()
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

void GibEngine::Renderer::DeferredGeometryPass::Update(float deltaTime)
{
	for (Model* model : drawablesList)
	{
		model->Update(deltaTime);
	}
}


