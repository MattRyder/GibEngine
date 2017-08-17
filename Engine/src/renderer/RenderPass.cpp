#include "renderer/RenderPass.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

GibEngine::Renderer::RenderPass::RenderPass(UniformBufferManager *uniformBufferManager, Shader *shader)
{
	this->shader = shader;
	this->uniformBufferManager = uniformBufferManager;
}

GibEngine::Renderer::RenderPass::RenderPass(UniformBufferManager * uniformBufferManager, Shader * shader, Framebuffer * framebuffer)
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

	delete cameraData;
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