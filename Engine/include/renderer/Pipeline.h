#pragma once

#include <map>

#include "RenderPass.h"
#include "RenderPassType.h"
#include "ForwardRenderPass.h"
#include "SkyboxRenderPass.h"

#include "UniformBufferManager.h"

namespace GibEngine
{
  namespace Renderer 
  {
    enum class ShaderLanguage
    {
        GLSL_130,
        GLSL_420
    };

    class Pipeline
    {
      static const char* ShaderLanguageStrings[];

	  UniformBufferManager* uniformBufferManager;
      ShaderLanguage shaderLanguage;
      std::map<RenderPassType, RenderPass *> passes;

      const char* GetShaderLanguageString(ShaderLanguage language);

      public:
        Pipeline(ShaderLanguage supportedShaderLanguage);
        ~Pipeline();

        void AddPass(UniformBufferManager* uniformBufferManager, RenderPassType type);
        void Render();

		RenderPass* GetRenderPass(RenderPassType type);
    };
  }
}