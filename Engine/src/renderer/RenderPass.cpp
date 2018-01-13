#include "renderer/RenderPass.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

GLfloat GibEngine::Renderer::RenderPass::QuadTextureData[] = {
	// Positions			// Texture Coords
	-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
	1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
};

GibEngine::Renderer::RenderPass::RenderPass(API::IGraphicsApi* graphicsApi, Shader *shader)
{
	this->quadMesh = nullptr;
	this->graphicsApi = graphicsApi;
	this->shader = shader;
}

GibEngine::Renderer::RenderPass::RenderPass(API::IGraphicsApi* graphicsApi, Shader *shader, Framebuffer *framebuffer)
	: RenderPass(graphicsApi, shader)
{
	this->framebuffer = framebuffer;
}

GibEngine::Renderer::RenderPass::~RenderPass()
{
	if (quadMesh != nullptr)
	{
		delete quadMesh;
	}
}

void GibEngine::Renderer::RenderPass::LoadQuadData()
{
	std::vector<Vertex> quadVerts;

	for (unsigned int i = 0; i < 20; i += 5)
	{
		Vertex v;
		v.Position = glm::vec3(QuadTextureData[i], QuadTextureData[i + 1], QuadTextureData[i + 2]);
		v.TexCoord = glm::vec2(QuadTextureData[i + 3], QuadTextureData[i + 4]);

		quadVerts.push_back(v);
	}

	quadMesh = new Mesh("RenderPassQuad", nullptr, quadVerts);
	quadMesh->SetMeshUploadTicket(graphicsApi->UploadMesh(quadMesh));
}

void GibEngine::Renderer::RenderPass::Render(const GibEngine::Scene::VisibleSet& visibleSet) { }


GibEngine::Shader* GibEngine::Renderer::RenderPass::GetShader() const
{
	return shader;
}

bool GibEngine::Renderer::RenderPass::IsEnabled() const
{
	return passEnabled;
}

void GibEngine::Renderer::RenderPass::BindLights(const GibEngine::Scene::VisibleSet& visibleSet)
{
	int pl = glGetUniformLocation(shader->GetShaderId(), "pointLightCount");
	glUniform1i(pl, visibleSet.GetLights().size());

	for (unsigned int i = 0; i < visibleSet.GetLights().size(); i++)
	{
		const Scene::Node* lightNode = visibleSet.GetLights()[i];
		PointLight* light = reinterpret_cast<PointLight*>(lightNode->GetEntity());

		std::string lightId, position, ambient, diffuse, specular,
			linearAttenuation, quadraticAttenuation, volumeRadius, direction;

		switch (light->GetType())
		{
		case EntityType::DIRECTIONAL_LIGHT:
			lightId = "directional";
			break;
		case EntityType::POINT_LIGHT:
			lightId = "point";
			break;
		}

		// Queue up the uniform attribute names:
		lightId = lightId + "Lights[" + std::to_string(i) + "]";
		position = lightId + ".position";
		ambient = lightId + ".ambientColor";
		diffuse = lightId + ".diffuseColor";
		specular = lightId + ".specularColor";
		linearAttenuation = lightId + ".linearAttenuation";
		quadraticAttenuation = lightId + ".quadraticAttenuation";
		volumeRadius = lightId + ".volumeRadius";
		direction = lightId + ".direction";

		if (light->GetType() != EntityType::DIRECTIONAL_LIGHT)
		{
			auto lightWorldTrans = lightNode->GetWorldTransform();
			auto lightPosition = glm::vec3(lightWorldTrans[3][0], lightWorldTrans[3][1], lightWorldTrans[3][2]);
			BindLightUniform3f(position.c_str(), lightPosition);
		}

		// Currently unused by the deferred lighting shader:
		//BindLightUniform3f(ambient.c_str(), light->GetAmbientColor());

		BindLightUniform3f(diffuse.c_str(), light->GetDiffuseColor());

		BindLightUniform3f(specular.c_str(), light->GetSpecularColor());

		if (light->GetType() == EntityType::POINT_LIGHT)
		{
			PointLight *pointLight = reinterpret_cast<PointLight *>(light);

			glUniform1f(
				glGetUniformLocation(shader->GetShaderId(), linearAttenuation.c_str()),
				pointLight->GetLinearAttenuation()
			);

			glUniform1f(
				glGetUniformLocation(shader->GetShaderId(), quadraticAttenuation.c_str()),
				pointLight->GetQuadraticAttenuation()
			);

			glUniform1f(
				glGetUniformLocation(shader->GetShaderId(), volumeRadius.c_str()),
				pointLight->GetVolumeRadius()
			);
		}
	}
}

void GibEngine::Renderer::RenderPass::FlagLightingBindRequired()
{
	this->lightingBindRequired = true;
}

void GibEngine::Renderer::RenderPass::RenderPass::SetPassEnabled(bool value) { this->passEnabled = value; }

void GibEngine::Renderer::RenderPass::RenderPass::TakeScreenshot()
{
	const size_t DATE_MAX_LENGTH = 64;
	char* date = new char[DATE_MAX_LENGTH];

	std::string filename = std::string();

	time_t now = time(nullptr);
	struct tm *timeinfo = localtime(&now);

	// Prepend Date to the log message:
	strftime(date, DATE_MAX_LENGTH, "%F-%H-%M-%S", timeinfo);

	filename.append("GibEngine_").append(date).append(".png");
	File *screenshotFile = File::GetScreenshotFile(filename.c_str());

	unsigned char *frameBuffer = graphicsApi->ReadFramebufferTexture(this->framebuffer, FramebufferType::RENDER_TO_TEXTURE);
	unsigned char *lastRow = frameBuffer + (framebuffer->GetBufferWidth() * 3 * (framebuffer->GetBufferHeight() - 1));
	const char *filePath = screenshotFile->GetPath();

	 if (!stbi_write_png(filePath, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), 3, lastRow, -3 * framebuffer->GetBufferWidth()))
	 {
	 	Logger::Instance->error("Failed to write screenshot '{}'", filePath);
	 }
	 else
	 {
	 	Logger::Instance->info("Screenshot saved to '{}'", filePath);
	 }

	delete[] date;
	delete[] frameBuffer;
}

void GibEngine::Renderer::RenderPass::BindLightUniform3f(const char* lightUniformName, const glm::vec3 lightUniformValue)
{
	unsigned int uniformLocation = graphicsApi->GetUniformLocation(lightUniformName);
	graphicsApi->BindUniform3fv(uniformLocation, 1, glm::value_ptr(lightUniformValue));
}