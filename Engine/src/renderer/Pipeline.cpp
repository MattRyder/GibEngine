#include "renderer/Pipeline.h"

const char* GibEngine::Renderer::Pipeline::ShaderLanguageStrings[] =
{
  "300_es",
  "420"
};

GibEngine::Renderer::Pipeline::Pipeline(int framebufferWidth, int framebufferHeight, ShaderLanguage supportedShaderLanguage)
{
	this->shaderLanguage = supportedShaderLanguage;

	this->SelectGraphicsApi(this->shaderLanguage);

	this->framebuffer = new Framebuffer(framebufferWidth, framebufferHeight);
	graphicsApi->CreateFramebuffer(framebuffer, framebufferWidth, framebufferHeight);

	this->passes = std::map<RenderPassType, RenderPass*>();
}

GibEngine::Renderer::Pipeline::~Pipeline()
{
	for (auto passObj : this->passes)
	{
		delete passObj.second->GetShader();
		delete passObj.second;
	}
	
	delete graphicsApi;
	delete framebuffer;
}

void GibEngine::Renderer::Pipeline::AddPass(RenderPassType type)
{
	// Calculate the name of the shader to load for this RenderPass:
	std::string shaderFileName;
	switch (type)
	{
	case RenderPassType::FORWARD_RENDERING:
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
	case RenderPassType::RENDER_TO_TEXTURE:
		shaderFileName = "render_to_texture";
		break;
	default:
		Logger::Instance->info("[Pipeline::AddPass] Attempting to find shader filename failed, none set!");
		break;
	}

	Renderer::RenderPass *renderPass;

	// Dynamically load the shader, for the appropriate GLSL version, for each OpenGL phase:
	File *vertexFile = GibEngine::File::GetShaderFile(
		(std::string(GetShaderLanguageString(this->shaderLanguage)) +
		 std::string("/") +
		 shaderFileName + std::string("_vs") +
		 std::string(".glsl")).c_str());

	File *fragmentFile = GibEngine::File::GetShaderFile(
		(std::string(GetShaderLanguageString(this->shaderLanguage)) +
		 std::string("/") +
		 shaderFileName + std::string("_fs") +
		 std::string(".glsl")).c_str());

	Shader *shader = new Shader(vertexFile, fragmentFile);

	switch (type)
	{
	case RenderPassType::FORWARD_RENDERING:
		renderPass = new ForwardRenderPass(graphicsApi, shader);
		break;
	case RenderPassType::SKYBOX:
		renderPass = new SkyboxRenderPass(graphicsApi, shader);
		break;
	case RenderPassType::DEFERRED_GEOMETRY:
		renderPass = new DeferredGeometryPass(graphicsApi, shader);
		break;
	case RenderPassType::DEFERRED_LIGHTING:
		renderPass = new DeferredLightingPass(graphicsApi, shader, framebuffer);
		break;
	case RenderPassType::RENDER_TO_TEXTURE:
		renderPass = new RenderToTexturePass(graphicsApi, shader, framebuffer);
		break;
	default:
		Logger::Instance->error("[Pipeline::AddPass] Failed to find implementation for: {}", shaderFileName.c_str());
		break;
	}

	this->passes.emplace(type, renderPass);
}

void GibEngine::Renderer::Pipeline::Render(const GibEngine::Scene::VisibleSet& visibleSet)
{	
	if (renderingPaused)
	{
		return;
	}

	graphicsApi->BindFramebuffer(framebuffer);

	graphicsApi->ClearFramebuffer();

	graphicsApi->UpdateCamera(visibleSet.GetCamera());

	RenderPass* pass = GetRenderPass(RenderPassType::DEFERRED_GEOMETRY);
	if (pass->IsEnabled())
	{
		pass->Render(visibleSet);
	}
	
	graphicsApi->UnbindFramebuffer();

	graphicsApi->ClearFramebuffer();

	pass = GetRenderPass(RenderPassType::DEFERRED_LIGHTING);
	if (pass->IsEnabled())
	{
		pass->Render(visibleSet);
	}

	graphicsApi->BlitFramebuffer(framebuffer->GetBuffer().framebufferId, 0, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), GL_DEPTH_BUFFER_BIT);


	// Gotta do the skybox pass forward renderered:
	pass = GetRenderPass(RenderPassType::SKYBOX);
	if (pass->IsEnabled())
	{
		pass->Render(visibleSet);
	}

	pass = GetRenderPass(RenderPassType::FORWARD_RENDERING);
	if (pass->IsEnabled())
	{
		pass->Render(visibleSet);
	}

	pass = GetRenderPass(RenderPassType::RENDER_TO_TEXTURE);
	if (pass->IsEnabled())
	{
		// Blit the Game framebuffer to the default framebuffer
		graphicsApi->BlitFramebuffer(0, framebuffer->GetBuffer().framebufferId, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void GibEngine::Renderer::Pipeline::Update(float deltaTime)
{
}

bool GibEngine::Renderer::Pipeline::IsRenderPaused()
{
	return renderingPaused;
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

GibEngine::Renderer::Framebuffer* GibEngine::Renderer::Pipeline::GetFramebuffer()
{
	return framebuffer;
}

void GibEngine::Renderer::Pipeline::SetCameraBase(CameraBase* camera)
{
	this->camera = camera;
}

void GibEngine::Renderer::Pipeline::SetRenderPaused(bool renderingPaused)
{
	this->renderingPaused = renderingPaused;
}

void GibEngine::Renderer::Pipeline::ResizeFramebuffer(int width, int height)
{
	graphicsApi->DeleteFramebuffer(framebuffer);
	graphicsApi->CreateFramebuffer(framebuffer, width, height);
}

const char* GibEngine::Renderer::Pipeline::GetShaderLanguageString(ShaderLanguage language)
{
	return ShaderLanguageStrings[static_cast<int>(language)];
}

void GibEngine::Renderer::Pipeline::SelectGraphicsApi(ShaderLanguage shaderLanguage)
{
	if(this->graphicsApi != nullptr)
	{
		delete this->graphicsApi;
	}

	switch(shaderLanguage)
	{
		case ShaderLanguage::GLES_3:
			this->graphicsApi = new Renderer::API::GLES3();
			break;
		case ShaderLanguage::GLSL_420:
			this->graphicsApi = new Renderer::API::GL420();
			break;
	}
}