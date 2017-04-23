#include "renderer/ForwardRenderPass.h"

GibEngine::Renderer::ForwardRenderPass::ForwardRenderPass(Shader *shader) : RenderPass(shader) { }

void GibEngine::Renderer::ForwardRenderPass::Render()
{
  
}

void GibEngine::Renderer::ForwardRenderPass::AddDrawable(Entity *drawableEntity)
{
  this->drawablesList.push_back(drawableEntity);
}