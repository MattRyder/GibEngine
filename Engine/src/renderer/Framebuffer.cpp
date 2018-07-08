#include "renderer/Framebuffer.h"

GibEngine::Renderer::Framebuffer::Framebuffer(int bufferWidth, int bufferHeight)
	: bufferWidth(bufferWidth > 0 ? bufferWidth : 1), bufferHeight(bufferHeight > 0 ? bufferHeight : 1), geometryBuffer() { }

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
