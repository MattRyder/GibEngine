#include "renderer/DeferredGeometryPass.h"

GibEngine::Renderer::DeferredGeometryPass::DeferredGeometryPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader* shader)
	: RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::DeferredGeometryPass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(visibleSet.GetCamera().get());

	auto instMap = visibleSet.GetMeshInstanceMap();
	for (auto iter = instMap->begin(); iter != instMap->end(); ++iter)
	{
		/*auto mesh = iter->first;*/
		const Mesh& mesh = *iter->first;
		if (!Mesh::FlagMask(mesh.GetFlags() & Mesh::Flags::RENDER_DEFERRED))
		{
			continue;
		}
		
		graphicsApi->UpdateMeshInstances(*mesh.GetMeshUploadTicket(), iter->second);

		graphicsApi->BindMaterial(mesh.GetMaterial().get());
		graphicsApi->DrawMesh(mesh, iter->second.size());
	}

	graphicsApi->UnbindShader();
}