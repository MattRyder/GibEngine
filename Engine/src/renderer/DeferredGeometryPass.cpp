#include "renderer/DeferredGeometryPass.h"

GibEngine::Renderer::DeferredGeometryPass::DeferredGeometryPass(API::IGraphicsApi* graphicsApi, Shader* shader)
	: RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::DeferredGeometryPass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(visibleSet.GetCamera());

	for (auto meshInstancePair : visibleSet.GetMeshInstanceMap())
	{
		auto mesh = meshInstancePair.first;
		if (!(mesh->GetFlags() & Mesh::Flags::RENDER_DEFERRED))
		{
			continue;
		}

		if (mesh->GetMeshUploadTicket() == nullptr)
		{
			mesh->SetMeshUploadTicket(graphicsApi->UploadMesh(mesh));
		}

		graphicsApi->UpdateMeshInstances(mesh->GetMeshUploadTicket(), meshInstancePair.second);

		graphicsApi->BindMaterial(mesh->GetMaterials()[0]);
		graphicsApi->DrawMesh(mesh, meshInstancePair.second.size());
	}

	graphicsApi->UnbindShader();
}