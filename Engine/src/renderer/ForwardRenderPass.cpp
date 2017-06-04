#include "renderer/ForwardRenderPass.h"

GibEngine::Renderer::ForwardRenderPass::ForwardRenderPass(Shader *shader) : RenderPass(shader) { }

void GibEngine::Renderer::ForwardRenderPass::Render()
{
	shader->Begin();

	camera->BindUBO(shader->GetShaderId(), uboIndices.at(RenderPassUniform::PLAYER_CAMERA), RenderPassUniform::PLAYER_CAMERA);

	for (auto model : drawablesList)
	{
		model->BindUBO(shader->GetShaderId(), uboIndices.at(RenderPassUniform::MATERIAL), RenderPassUniform::MATERIAL);
		model->Render(shader->GetShaderId(), 0.0f);
	}
	shader->End();
}