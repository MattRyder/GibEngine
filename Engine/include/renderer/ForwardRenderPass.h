#pragma once

#include "renderer/RenderPass.h"

namespace GibEngine
{
  namespace Renderer
  {
    class ForwardRenderPass : public RenderPass
    {
    public:
      ForwardRenderPass(API::IGraphicsApi* graphicsApi, Shader *shader);
      void Render(const Scene::VisibleSet* visibleSet) override;
    };

  }
}