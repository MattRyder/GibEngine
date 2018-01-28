#include "renderer/DeferredGeometryPass.h"

GibEngine::Renderer::DeferredGeometryPass::DeferredGeometryPass(API::IGraphicsApi* graphicsApi, Shader* shader)
	: RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::DeferredGeometryPass::Render(const GibEngine::Scene::VisibleSet* visibleSet)
{
	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(visibleSet->GetCamera());

	auto instMap = visibleSet->GetMeshInstanceMap();
	for (auto iter = instMap->begin(); iter != instMap->end(); ++iter)
	{
		auto mesh = iter->first;
		if (!Mesh::FlagMask(mesh->GetFlags() & Mesh::Flags::RENDER_DEFERRED))
		{
			continue;
		}

		if (mesh->GetMeshUploadTicket() == nullptr)
		{
			mesh->SetMeshUploadTicket(graphicsApi->UploadMesh(mesh));
			graphicsApi->UpdateMeshInstances(mesh->GetMeshUploadTicket(), iter->second);
		}


		graphicsApi->BindMaterial(mesh->GetMaterial());
		graphicsApi->DrawMesh(mesh, iter->second.size());
	}

	graphicsApi->UnbindShader();
}