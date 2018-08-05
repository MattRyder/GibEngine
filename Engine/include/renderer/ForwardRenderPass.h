#pragma once

#include "renderer/RenderPass.h"

namespace GibEngine
{
  namespace Renderer
  {
    class ForwardRenderPass : public RenderPass
    {
    public:
      ForwardRenderPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, std::shared_ptr<Shader> shader);
      void Render(const Scene::VisibleSet& visibleSet) override;
    };

  }
}