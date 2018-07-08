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

GibEngine::Renderer::RenderPass::RenderPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader *shader)
	: graphicsApi(graphicsApi), shader(shader), quadMesh(nullptr), lightingBindRequired(false), passEnabled(true) { }

GibEngine::Renderer::RenderPass::RenderPass(std::shared_ptr<Renderer::API::IGraphicsApi> graphicsApi, Shader *shader, Framebuffer *framebuffer)
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

	auto meshUploadTicket = graphicsApi->UploadMesh(quadVerts, std::vector<unsigned int>());
	quadMesh = new Mesh("RenderPassQuad", meshUploadTicket, nullptr);
	quadMesh->SetGenerationData(json11::Json::object{});
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
	auto lightCount = static_cast<unsigned int>(visibleSet.GetLights().size());
	int pl = graphicsApi->GetUniformLocation("pointLightCount");
	glUniform1i(pl, lightCount);

	for (unsigned int i = 0; i < lightCount; i++)
	{
		auto light = std::dynamic_pointer_cast<PointLight>(visibleSet.GetLights().at(i));

		std::string lightId, position, ambient, diffuse, specular,
			linearAttenuation, quadraticAttenuation, volumeRadius, direction;

		switch (light->GetType())
		{
		case BaseEntity::Type::DIRECTIONAL_LIGHT:
			lightId = "directional";
			break;
		case BaseEntity::Type::POINT_LIGHT:
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

		if (light->GetType() != BaseEntity::Type::DIRECTIONAL_LIGHT)
		{
			auto lightWorldTrans = light->GetWorldTransform();
			auto lightPosition = glm::vec3(lightWorldTrans[3][0], lightWorldTrans[3][1], lightWorldTrans[3][2]);
			BindLightUniform3f(position.c_str(), lightPosition);
		}

		BindLightUniform3f(diffuse.c_str(), light->GetDiffuseColor());
		BindLightUniform3f(specular.c_str(), light->GetSpecularColor());

		if (light->GetType() == BaseEntity::Type::POINT_LIGHT)
		{
			glUniform1f(
				graphicsApi->GetUniformLocation(linearAttenuation.c_str()),
				light->GetLinearAttenuation()
			);

			glUniform1f(
				graphicsApi->GetUniformLocation(quadraticAttenuation.c_str()),
				light->GetQuadraticAttenuation()
			);

			glUniform1f(
				graphicsApi->GetUniformLocation(volumeRadius.c_str()),
				light->GetVolumeRadius()
			);
		}
	}
}

void GibEngine::Renderer::RenderPass::FlagLightingBindRequired()
{
	this->lightingBindRequired = true;
}

void GibEngine::Renderer::RenderPass::RenderPass::SetPassEnabled(bool value) { this->passEnabled = value; }

void GibEngine::Renderer::RenderPass::RenderPass::TakeScreenshot(const std::string& filePath)
{
	unsigned char *frameBuffer = graphicsApi->ReadFramebufferTexture(this->framebuffer, FramebufferType::ALBEDO);
	unsigned char *lastRow = frameBuffer + (framebuffer->GetBufferWidth() * 3 * (framebuffer->GetBufferHeight() - 1));

	 if (!stbi_write_png(filePath.c_str(), framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), 3, lastRow, -3 * framebuffer->GetBufferWidth()))
	 {
	 	Logger::Instance->error("Failed to write screenshot '{}'", filePath);
	 }
	 else
	 {
	 	Logger::Instance->info("Screenshot saved to '{}'", filePath);
	 }

	delete[] frameBuffer;
}

void GibEngine::Renderer::RenderPass::BindLightUniform3f(const char* lightUniformName, const glm::vec3 lightUniformValue)
{
	unsigned int uniformLocation = graphicsApi->GetUniformLocation(lightUniformName);
	graphicsApi->BindUniform3fv(uniformLocation, 1, glm::value_ptr(lightUniformValue));
}

void GibEngine::Renderer::RenderPass::BindLightUniform4fv(const char * lightUniformName, glm::mat4 lightUniformValue)
{
	unsigned int uniformLocation = graphicsApi->GetUniformLocation(lightUniformName);
	graphicsApi->BindUniform4fv(uniformLocation, 1, glm::value_ptr(lightUniformValue));
}
