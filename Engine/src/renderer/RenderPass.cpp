#include "renderer/RenderPass.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

GibEngine::Renderer::RenderPass::RenderPass(UniformBufferManager *uniformBufferManager, Shader *shader)
{
	this->shader = shader;
	this->uniformBufferManager = uniformBufferManager;
}

GibEngine::Renderer::RenderPass::RenderPass(UniformBufferManager *uniformBufferManager, Shader *shader, Framebuffer *framebuffer)
	: RenderPass(uniformBufferManager, shader)
{
	this->framebuffer = framebuffer;
}

void GibEngine::Renderer::RenderPass::Render() { }

void GibEngine::Renderer::RenderPass::RenderPass::AddDrawable(Model *drawable)
{
	this->drawablesList.push_back(drawable);

	UniformBuffer* materialUBO = uniformBufferManager->FindOrCreate("materialUBO", sizeof(float) * 36);
	GLuint materialUBOIndex = glGetUniformBlockIndex(shader->GetShaderId(), "materialUBO");
	glUniformBlockBinding(shader->GetShaderId(), materialUBOIndex, materialUBO->GetBufferBindingIndex());
}

void GibEngine::Renderer::RenderPass::AddLight(LightBase *light)
{
	this->lights.push_back(light);
	lightingBindRequred = true;
}

void GibEngine::Renderer::RenderPass::RenderPass::SetCameraBase(FreeCamera *camera)
{
	this->camera = camera;

	UniformBuffer* cameraUBO = uniformBufferManager->FindOrCreate("cameraUBO", camera->BUFFER_OBJECT_SIZE);
	GLuint cameraUBOIndex = glGetUniformBlockIndex(shader->GetShaderId(), "cameraUBO");
	glUniformBlockBinding(shader->GetShaderId(), cameraUBOIndex, cameraUBO->GetBufferBindingIndex());

	float *cameraData = new float[camera->BUFFER_OBJECT_SIZE]{ 0 };

	memcpy(&cameraData[0], glm::value_ptr(camera->GetProjectionMatrix()), sizeof(float) * 16);
	memcpy(&cameraData[16], glm::value_ptr(camera->GetViewMatrix()), sizeof(float) * 16);
	memcpy(&cameraData[32], glm::value_ptr(camera->GetPosition()), sizeof(float) * 3);

	cameraUBO->Update(cameraData);

	delete[] cameraData;
}

void GibEngine::Renderer::RenderPass::BindLights()
{
	if (!lightingBindRequred)
	{
		return;
	}

	for (unsigned int i = 0; i < this->lights.size(); i++)
	{
		LightBase* light = this->lights[i];

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
			glUniform3fv(
				glGetUniformLocation(shader->GetShaderId(), position.c_str()),
				1,
				glm::value_ptr(light->GetPosition())
			);
		}

		glUniform3fv(
			glGetUniformLocation(shader->GetShaderId(), ambient.c_str()),
			1,
			glm::value_ptr(light->GetAmbientColor())
		);

		glUniform3fv(
			glGetUniformLocation(shader->GetShaderId(), diffuse.c_str()),
			1,
			glm::value_ptr(light->GetDiffuseColor())
		);

		glUniform3fv(
			glGetUniformLocation(shader->GetShaderId(), specular.c_str()),
			1,
			glm::value_ptr(light->GetSpecularColor())
		);

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

	lightingBindRequred = false;
}

void GibEngine::Renderer::RenderPass::RenderPass::SetPassEnabled(bool value) { this->passEnabled = value; }

void GibEngine::Renderer::RenderPass::RenderPass::TakeScreenshot(int framebufferWidth, int framebufferHeight)
{
	const size_t DATE_MAX_LENGTH = 64;
	size_t framebufferBytes = (size_t)(framebufferWidth * framebufferHeight * 3);

	unsigned char* frameBuffer = new unsigned char[framebufferBytes];
	char* date = new char[DATE_MAX_LENGTH];

	glReadPixels(0, 0, framebufferWidth, framebufferHeight, GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);

	std::string filename = std::string();

	time_t now = time(nullptr);
	struct tm *timeinfo = localtime(&now);

	// Prepend Date to the log message:
	strftime(date, DATE_MAX_LENGTH, "%F-%H-%M-%S", timeinfo);

	filename.append("GibEngine_").append(date);
	File *screenshotFile = File::GetScreenshotFile(filename.c_str());

	unsigned char *lastRow = frameBuffer + (framebufferWidth * 3 * (framebufferHeight - 1));
	const char *filePath = screenshotFile->GetPath();

	if (!stbi_write_png(filePath, framebufferWidth, framebufferHeight, 3, lastRow, -3 * framebufferWidth)) {
		Logger::Instance->error("Failed to write screenshot '{}'", filePath);
	}
	else {
		Logger::Instance->info("Screenshot saved to '{}'", filePath);
	}

	delete[] date;
	delete[] frameBuffer;
}