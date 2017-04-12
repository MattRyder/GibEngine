#pragma once

#include <map>
#include "RenderPass.h"
#include "RenderPassType.h"

namespace GibEngine
{
  namespace Renderer 
  {
    class Pipeline
    {
      std::map<RenderPassType, RenderPass *> passes;

      public:
        Pipeline();
        ~Pipeline();

        void Render();
    };
  }
}