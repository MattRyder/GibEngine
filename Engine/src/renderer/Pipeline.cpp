#include "renderer/Pipeline.h"

GibEngine::Renderer::Pipeline::Pipeline(int framebufferWidth, int framebufferHeight, std::shared_ptr<GibEngine::FileSystem::IFileSystem> fileSystem, std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi)
	: fileSystem(fileSystem), graphicsApi(graphicsApi)
{
	this->framebuffer = new Framebuffer(framebufferWidth, framebufferHeight);
	graphicsApi->CreateFramebuffer(framebuffer, framebufferWidth, framebufferHeight);
}

GibEngine::Renderer::Pipeline::~Pipeline()
{
	for (auto renderPass : this->passes)
	{
		delete renderPass->GetShader();
		delete renderPass;
	}

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

	
	std::shared_ptr<std::string> vertexSource, fragmentSource;
	const std::string glVersionDirectory = graphicsApi->GetVersionString();

	vertexSource = std::shared_ptr<std::string>(new std::string());
	fragmentSource = std::shared_ptr<std::string>(new std::string());

	const std::string shaderPath = fileSystem->GetWorkingDirectory() + "/../../Assets/Shaders";
	const std::string vertexRelativePath = shaderPath + std::string("/") + glVersionDirectory + std::string("/") + shaderFileName + std::string("_vs.glsl");
	const std::string fragmentRelativePath = shaderPath + std::string("/") + glVersionDirectory + std::string("/") + shaderFileName + std::string("_fs.glsl");
	fileSystem->ReadFile(vertexRelativePath, vertexSource);
	fileSystem->ReadFile(fragmentRelativePath, fragmentSource);

	Shader *shader = new Shader(vertexSource, fragmentSource);

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

	passes[static_cast<int>(type)] = renderPass;
}

void GibEngine::Renderer::Pipeline::AddCamera(std::shared_ptr<CameraBase> camera)
{
	if (std::find(cameras.begin(), cameras.end(), camera) == cameras.end())
	{
		this->cameras.push_back(camera);

		for (auto pass : passes)
		{
			graphicsApi->BindShader(pass->GetShader()->GetShaderId());
			graphicsApi->RegisterCamera(camera);
			graphicsApi->UnbindShader();
		}
	}
}


void GibEngine::Renderer::Pipeline::Render(const GibEngine::Scene::VisibleSet& visibleSet, const float deltaTime)
{	
	//if (renderingPaused)
	//{
	//	return;
	//}

	graphicsApi->BindFramebuffer(*framebuffer);

	graphicsApi->ClearFramebuffer();

	for (auto camera : cameras)
	{
		graphicsApi->UpdateCamera(camera.get());
	}

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

bool GibEngine::Renderer::Pipeline::IsRenderPaused()
{
	return renderingPaused;
}

GibEngine::Renderer::RenderPass* GibEngine::Renderer::Pipeline::GetRenderPass(RenderPassType type)
{
	auto val = static_cast<int>(type);
	if (passes[val] == nullptr)
	{
		AddPass(type);
	}

	return passes[val];
}

GibEngine::Renderer::Framebuffer* GibEngine::Renderer::Pipeline::GetFramebuffer()
{
	return framebuffer;
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