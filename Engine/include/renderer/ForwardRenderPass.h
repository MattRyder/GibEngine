#pragma once

#include "renderer/RenderPass.h"

namespace GibEngine
{
  namespace Renderer
  {
    class ForwardRenderPass : public RenderPass
    {
    public:
      ForwardRenderPass(UniformBufferManager *uniformBufferManager, Shader *shader);
      void Render() override;
	  void Update(float deltaTime) override;
    };

  }
}