#include "renderer/ForwardRenderPass.h"

GibEngine::Renderer::ForwardRenderPass::ForwardRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader) : RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::ForwardRenderPass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	glEnable(GL_BLEND);

	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(visibleSet.GetCamera());

	for (auto meshInstancePair : visibleSet.GetMeshInstanceMap())
	{
		auto mesh = meshInstancePair.first;
		if (!Mesh::FlagMask(mesh->GetFlags() & Mesh::Flags::RENDER_FORWARD))
		{
			continue;
		}

		if (mesh->GetMeshUploadTicket() == nullptr)
		{
			mesh->SetMeshUploadTicket(graphicsApi->UploadMesh(mesh));
		}

		graphicsApi->UpdateMeshInstances(mesh->GetMeshUploadTicket(), meshInstancePair.second);

		if (mesh->GetMaterials().size() > 0)
		{
			graphicsApi->BindMaterial(mesh->GetMaterials()[0]);
		}

		graphicsApi->DrawMesh(mesh, meshInstancePair.second.size());
	}

	graphicsApi->UnbindShader();

	glDisable(GL_BLEND);
}
