#include "renderer/Framebuffer.h"

GibEngine::Renderer::Framebuffer::Framebuffer(int bufferWidth, int bufferHeight)
{
	this->bufferWidth = bufferWidth > 0 ? bufferWidth : 1;
	this->bufferHeight = bufferHeight > 0 ? bufferHeight : 1;

	// Create the Geometry buffer, and bind it to setup:
	this->geometryBuffer = { 0 };
}

GibEngine::Renderer::Framebuffer::~Framebuffer()
{
	geometryBuffer = { 0 };
}

GibEngine::Renderer::buffer_t GibEngine::Renderer::Framebuffer::GetBuffer() const
{
	return geometryBuffer;
}

int GibEngine::Renderer::Framebuffer::GetBufferWidth() const
{
	return bufferWidth;
}

int GibEngine::Renderer::Framebuffer::GetBufferHeight() const
{
	return bufferHeight;
}

void GibEngine::Renderer::Framebuffer::SetBuffer(int bufferWidth, int bufferHeight, buffer_t buffer)
{
	this->bufferWidth = bufferWidth;
	this->bufferHeight = bufferHeight;
	this->geometryBuffer = buffer;
}
