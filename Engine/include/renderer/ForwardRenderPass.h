#pragma once

#include "renderer/RenderPass.h"

namespace GibEngine
{
  namespace Renderer
  {
    class ForwardRenderPass : public RenderPass
    {
    public:
      ForwardRenderPass(Shader *shader);
      virtual void Render();// override;
      //virtual void AddDrawable(Model *drawableEntity) override;
    };

  }
}