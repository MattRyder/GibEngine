#pragma once

#include "RenderPass.h"

namespace GibEngine
{
  namespace Renderer
  {
    class ColorPass : RenderPass {
      virtual void Render() override;
    }
  }
}