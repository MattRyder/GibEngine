#include "renderer/ForwardRenderPass.h"

GibEngine::Renderer::ForwardRenderPass::ForwardRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader) : RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::ForwardRenderPass::Render()
{
	glEnable(GL_BLEND);

	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(RenderPass::camera);

	for (Model* model : drawablesList)
	{
		for (Mesh* mesh : model->GetMeshes())
		{
			if (mesh->IsInstanceMatricesDirty())
			{
				UpdateMeshInstances(mesh->GetMeshUploadTicket(), mesh->GetInstanceMatrices());
				mesh->SetInstanceMatricesDirty(false);
			}

			if (mesh->GetMaterials().size() > 0)
			{
				graphicsApi->BindMaterial(mesh->GetMaterials()[0]);
			}

			graphicsApi->DrawMesh(mesh);
		}
	}

	graphicsApi->UnbindShader();

	glDisable(GL_BLEND);
}

void GibEngine::Renderer::ForwardRenderPass::Update(float deltaTime)
{
	for (Model* model : drawablesList)
	{
		model->Update(deltaTime);
	}
}

