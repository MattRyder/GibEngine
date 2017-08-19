#include "renderer/Pipeline.h"

const char* GibEngine::Renderer::Pipeline::ShaderLanguageStrings[] =
{
  "_300_es",
  "_420"
};

GibEngine::Renderer::Pipeline::Pipeline(UniformBufferManager* uniformBufferManager, Framebuffer* framebuffer, ShaderLanguage supportedShaderLanguage)
{
	this->uniformBufferManager = uniformBufferManager;
	this->framebuffer = framebuffer;
	this->shaderLanguage = supportedShaderLanguage;

	this->passes = std::map<RenderPassType, RenderPass *>();
}

GibEngine::Renderer::Pipeline::~Pipeline() { }

void GibEngine::Renderer::Pipeline::AddPass(RenderPassType type)
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
		break;
	case RenderPassType::DEFERRED_GEOMETRY:
		shaderFileName = "deferred_geometry";
		break;
	case RenderPassType::DEFERRED_LIGHTING:
		shaderFileName = "deferred_lighting";
		break;
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

	switch (type)
	{
	case RenderPassType::FORWARD_LIGHTING:
		renderPass = new ForwardRenderPass(uniformBufferManager, shader);
		break;
	case RenderPassType::SKYBOX:
		renderPass = new SkyboxRenderPass(uniformBufferManager, shader);
		break;
	case RenderPassType::DEFERRED_GEOMETRY:
		renderPass = new DeferredGeometryPass(uniformBufferManager, shader, framebuffer);
		break;
	case RenderPassType::DEFERRED_LIGHTING:
		renderPass = new DeferredLightingPass(uniformBufferManager, shader, framebuffer);
		break;
	}

	this->passes.emplace(type, renderPass);
}

void GibEngine::Renderer::Pipeline::Render()
{
	framebuffer->Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto const& pass : this->passes)
	{
		RenderPass *rpass = pass.second;
		rpass->Render();
	}
	
	framebuffer->Unbind();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer->GetBuffer().framebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(),
		0, 0, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GibEngine::Renderer::Pipeline::Update(float deltaTime)
{
	for (auto const& pass : this->passes)
	{
		RenderPass* rpass = pass.second;
		rpass->Update(deltaTime);
	}
}

GibEngine::Renderer::RenderPass* GibEngine::Renderer::Pipeline::GetRenderPass(RenderPassType type)
{
	std::map<RenderPassType, RenderPass*>::iterator passLookup = passes.find(type);
	if (passLookup == passes.end())
	{
		AddPass(type);
		return GetRenderPass(type);
	}
	
	return this->passes.at(type);
}

const char* GibEngine::Renderer::Pipeline::GetShaderLanguageString(ShaderLanguage language)
{
	return ShaderLanguageStrings[static_cast<int>(language)];
}