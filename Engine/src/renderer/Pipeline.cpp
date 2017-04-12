#include "renderer/Pipeline.h"

GibEngine::Renderer::Pipeline::Pipeline()
{
  this->passes = std::map<RenderPassType, RenderPass *>();
}

GibEngine::Renderer::Pipeline::~Pipeline() { }

void GibEngine::Renderer::Pipeline::Render()
{
  for(auto const & pass : this->passes)
  {
    RenderPass *rpass = pass.second;
    rpass->Render();
  }
}