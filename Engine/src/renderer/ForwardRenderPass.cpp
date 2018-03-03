#include "renderer/ForwardRenderPass.h"

GibEngine::Renderer::ForwardRenderPass::ForwardRenderPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader *shader) : RenderPass(graphicsApi, shader) { }

void GibEngine::Renderer::ForwardRenderPass::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{
	glEnable(GL_BLEND);

	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindCamera(visibleSet.GetCamera().get());

	auto instMap = visibleSet.GetMeshInstanceMap();
	for (auto iter = instMap->begin(); iter != instMap->end(); ++iter)
	{
		const Mesh& mesh = *iter->first;
		if (!Mesh::FlagMask(mesh.GetFlags() & Mesh::Flags::RENDER_FORWARD))
		{
			continue;
		}

		graphicsApi->UpdateMeshInstances(*mesh.GetMeshUploadTicket(), iter->second);

		//if (mesh->GetMaterials().size() > 0)
		//{
		//	graphicsApi->BindMaterial(mesh->GetMaterials()[0]);
		//}

		graphicsApi->DrawMesh(mesh, iter->second.size());
	}

	graphicsApi->UnbindShader();

	glDisable(GL_BLEND);
}
