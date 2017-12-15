#include "renderer/DeferredGeometryPass.h"

GibEngine::Renderer::DeferredGeometryPass::DeferredGeometryPass(API::IGraphicsApi* graphicsApi, Shader *shader, Framebuffer* framebuffer)
	: RenderPass(graphicsApi, shader, framebuffer) { }

void GibEngine::Renderer::DeferredGeometryPass::Render()
{
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

			graphicsApi->BindMaterial(mesh->GetMaterials()[0]);
			graphicsApi->DrawMesh(mesh);
		}
	}

	graphicsApi->UnbindShader();
}

void GibEngine::Renderer::DeferredGeometryPass::Update(float deltaTime)
{
	for (Model* model : drawablesList)
	{
		model->Update(deltaTime);
	}
}