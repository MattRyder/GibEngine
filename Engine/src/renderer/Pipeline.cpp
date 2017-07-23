#include "renderer/Pipeline.h"

const char* GibEngine::Renderer::Pipeline::ShaderLanguageStrings[] =
{
  "_300_es",
  "_420"
};

GibEngine::Renderer::Pipeline::Pipeline(ShaderLanguage supportedShaderLanguage)
{
  this->shaderLanguage = supportedShaderLanguage;
  this->passes = std::map<RenderPassType, RenderPass *>();
  this->uniformBufferManager = new UniformBufferManager();
}

GibEngine::Renderer::Pipeline::~Pipeline() { }

void GibEngine::Renderer::Pipeline::AddPass(UniformBufferManager* uniformBufferManager, RenderPassType type)
{
	// Calculate the name of the shader to load for this RenderPass:
	std::string shaderFileName;
	switch (type)
	{
	case RenderPassType::FORWARD_LIGHTING:
		shaderFileName = "color";
		break;
	case RenderPassType::SKYBOX:
		shaderFileName = "skybox";
	}

  Renderer::RenderPass *renderPass;

  // Dynamically load the shader, for the appropriate GLSL version, for each OpenGL phase:
  File *vertexFile = GibEngine::File::GetShaderFile(
    (shaderFileName + std::string("_vs") +
      std::string(GetShaderLanguageString(this->shaderLanguage)) +
      std::string(".glsl")).c_str());

  File *fragmentFile = GibEngine::File::GetShaderFile(
    (shaderFileName + std::string("_fs") +
      std::string(GetShaderLanguageString(this->shaderLanguage)) +
      std::string(".glsl")).c_str());
    
  Shader *shader = new Shader(vertexFile, fragmentFile);

  switch(type) 
  {
    case RenderPassType::FORWARD_LIGHTING:
      renderPass = new ForwardRenderPass(uniformBufferManager, shader);
      break;
	case RenderPassType::SKYBOX:
	  renderPass = new SkyboxRenderPass(uniformBufferManager, shader);
	  break;
  }
  
  this->passes.emplace(type, renderPass);
}

void GibEngine::Renderer::Pipeline::Render()
{
  for(auto const& pass : this->passes)
  {
    RenderPass *rpass = pass.second;
    rpass->Render();
  }
}

GibEngine::Renderer::RenderPass* GibEngine::Renderer::Pipeline::GetRenderPass(RenderPassType type)
{
	return this->passes.at(type);
}

const char* GibEngine::Renderer::Pipeline::GetShaderLanguageString(ShaderLanguage language)
{
  return ShaderLanguageStrings[static_cast<int>(language)];
}