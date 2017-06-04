#include "CameraBase.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#define PI  3.14159265358979323846
#define ONE_DEG_IN_RAD (2.0 * PI) / 360.0 // 0.017444444
#define ONE_RAD_IN_DEG 360.0 / (2.0 * PI) //57.2957795

GibEngine::CameraBase::CameraBase(EntityType entityType) : Entity(entityType) { }

void GibEngine::CameraBase::TakeScreenshot(int framebufferWidth, int framebufferHeight)
{
    size_t framebufferBytes = (size_t)(framebufferWidth * framebufferHeight * 3);
    unsigned char* frameBuffer = (unsigned char*)malloc(framebufferBytes);
    glReadPixels(0, 0, framebufferWidth, framebufferHeight, GL_RGB, GL_UNSIGNED_BYTE, frameBuffer);

    //char name[255];
    time_t now = time(nullptr);
    struct tm *timeinfo;
    timeinfo = localtime(&now);
    char* date = new char[64];

    // Prepend Date to the log message:
    strftime(date, 64, "%F-%H-%M-%S", timeinfo);
    // sprintf(name, "GibEngine_%s.png", date);
    // File *screenshotFile = std::string(File::GetScreenshotPath()).append(name).c_str());
    // delete[] date;

    // unsigned char *lastRow = frameBuffer + (framebufferWidth * 3 * (framebufferHeight - 1));
    // const char *filePath = screenshotFile->GetPath();

    // if (!stbi_write_png(filePath, framebufferWidth, framebufferHeight, 3, lastRow, -3 * framebufferWidth)) {
    //     Logger::Instance->error("Failed to write screenshot '{}'", filePath);
    // }
    // else {
    //     Logger::Instance->info("Screenshot saved to '{}'", filePath);
    // }

    free(frameBuffer);
}

glm::mat4 GibEngine::CameraBase::ConstructProjectionMatrix(float width, float height, float zNear, float zFar, float fov)
{
	return glm::mat4(glm::perspectiveFov(fov, width, height, zNear, zFar));
}

void GibEngine::CameraBase::UpdateUBO()
{
	void *bufferRange = glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(float) * 36, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

	float* cameraUniformPtr = reinterpret_cast<float*>(bufferRange);
	memcpy(&cameraUniformPtr[0], glm::value_ptr(projectionMatrix), sizeof(float) * 16);
	memcpy(&cameraUniformPtr[16], glm::value_ptr(viewMatrix), sizeof(float) * 16);
	memcpy(&cameraUniformPtr[32], glm::value_ptr(GetPosition()), sizeof(float) * 3);
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}

glm::mat4 GibEngine::CameraBase::GetProjectionMatrix()
{
	return this->projectionMatrix;
}

glm::mat4 GibEngine::CameraBase::GetViewMatrix()
{
	return this->viewMatrix;
}