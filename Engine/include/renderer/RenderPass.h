#pragma once

#include <vector>
#include "Shader.h"

namespace GibEngine 
{
  namespace Renderer 
  {
    class RenderPass 
    {
      bool passEnabled = true;

      protected:
        Shader *shader;
        std::vector<Entity *> drawables;

      public:
        RenderPass(Shader *shader);

        virtual void Render() = 0;
        virtual void AddDrawable(Entity *drawable) = 0;

        void SetPassEnabled(bool value) { this->passEnabled = value; }
    };
  }
}