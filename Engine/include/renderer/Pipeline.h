#pragma once

#include <map>
#include "RenderPass.h"
#include "RenderPassType.h"
#include "ForwardRenderPass.h"

namespace GibEngine
{
  namespace Renderer 
  {
    enum class ShaderLanguage
    {
        GLSL_130,
        GLSL_450
    };

    class Pipeline
    {
      static const char* ShaderLanguageStrings[];

      ShaderLanguage shaderLanguage;
      std::map<RenderPassType, RenderPass *> passes;

      const char* GetShaderLanguageString(ShaderLanguage language);

      public:
        Pipeline(ShaderLanguage supportedShaderLanguage);
        ~Pipeline();

        void AddPass(RenderPassType type);
        void Render();
    };
  }
}