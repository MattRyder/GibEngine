#include "renderer/SsaoPass.h"


GibEngine::Renderer::SsaoPass::SsaoPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, std::shared_ptr<Shader> shader, std::shared_ptr<Framebuffer> framebuffer)
	: RenderPass(graphicsApi, shader, framebuffer)
{
	LoadQuadData();
	InitializeKernel();

	ssaoFramebuffer = std::make_shared<Framebuffer>(framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight());

	auto ssaoFbuf = 0U;
	glGenFramebuffers(1, &ssaoFbuf);
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoFbuf);

	auto ssaoTex = 0U;
	glGenTextures(1, &ssaoTex);
	glBindTexture(GL_TEXTURE_2D, ssaoTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoTex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Logger::Instance->info("SSAO FBO Broke :(");
	}

	buffer_t buf = { 0 };
	buf.framebufferId = ssaoFbuf;
	buf.textures[0] = ssaoTex;
	ssaoFramebuffer->SetBuffer(ssaoFramebuffer->GetBufferWidth(), ssaoFramebuffer->GetBufferHeight(), buf);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GibEngine::Renderer::SsaoPass::Render(const Scene::VisibleSet& visibleSet)
{
	const std::string KERNEL_UNIFORM_NAME = "ssao_Kernel";
	const std::vector<std::string> TEXTURE_NAMES = { "texture_Position", "texture_Normal", "texture_Noise" };
	const unsigned int TEXTURE_IDS[3] =
	{
		framebuffer->GetBuffer().textures[FramebufferType::POSITION],
		framebuffer->GetBuffer().textures[FramebufferType::NORMAL],
		noiseTexture->GetTextureId()
	};

	graphicsApi->BindShader(shader->GetShaderId());

	graphicsApi->BindFramebuffer(*ssaoFramebuffer);

	graphicsApi->ClearFramebuffer();

	for (auto i = 0U; i < TEXTURE_NAMES.size(); i++)
	{
		auto ssaoNoiseTextureLocation = graphicsApi->GetUniformLocation(TEXTURE_NAMES.at(i).c_str());
		graphicsApi->BindUniform1f(ssaoNoiseTextureLocation, i);
		graphicsApi->BindTexture2D(i, TEXTURE_IDS[i]);
	}

	auto kernelLocation = graphicsApi->GetUniformLocation(KERNEL_UNIFORM_NAME.c_str());
	glUniform3fv(kernelLocation, 64, &kernel[0].x);

	graphicsApi->DrawPrimitive(*quadMesh->GetMeshUploadTicket());

	graphicsApi->UnbindFramebuffer();
	graphicsApi->UnbindShader();
}

const std::shared_ptr<GibEngine::Renderer::Framebuffer> GibEngine::Renderer::SsaoPass::GetFramebuffer() const
{
	return ssaoFramebuffer;
}

void GibEngine::Renderer::SsaoPass::InitializeKernel()
{
	std::uniform_real_distribution<float> floats(0, 1.0);
	std::default_random_engine rngen;

	// Generate random noise for use in the texture:
	std::vector<glm::vec3> noise;
	for (unsigned int i = 0; i < 16; i++)
	{
		auto sample = glm::vec3(
			floats(rngen) * 2.0 - 1.0,
			floats(rngen) * 2.0 - 1.0,
			0.0f);

		noise.push_back(sample);
	}

	// Generate samples within unit hemisphere
	for (auto i = 0U; i < 64; ++i)
	{
		auto sample = glm::vec3(
			floats(rngen) * 2.0 - 1.0,
			floats(rngen) * 2.0 - 1.0,
			floats(rngen)
		);

		sample = glm::normalize(sample);
		sample *= floats(rngen);

		// closer distribution to the edge of the sample kernel:
		float scale = i / 64.0f;
		scale = Lerp(0.1f, 1.0f, std::pow(scale, 2));
		sample *= scale;

		kernel.push_back(sample);
	}

	//TextureData textureData = { 0 };
	//textureData.DataType = StorageType::FLOAT;
	//textureData.Data = &noise[0];

	unsigned int textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &noise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//graphicsApi->UploadTexture2D(&textureId, textureData, Renderer::API::SamplerFiltering::NEAREST, Renderer::API::SamplerEdgeClamping::CLAMP_TO_EDGE);

	this->noiseTexture = std::shared_ptr<Texture>(new Texture(textureId, TextureType::DIFFUSE, { 4,4 }));
}
