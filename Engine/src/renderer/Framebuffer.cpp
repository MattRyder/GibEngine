#include "renderer/Framebuffer.h"

GibEngine::Renderer::Framebuffer::Framebuffer(int bufferWidth, int bufferHeight)
{
	this->bufferWidth = bufferWidth > 0 ? bufferWidth : 1;
	this->bufferHeight = bufferHeight > 0 ? bufferHeight : 1;

	GLuint bufferAttachments[FRAMEBUFFERTYPE_LAST];

	// Create the Geometry buffer, and bind it to setup:
	this->geometryBuffer = { 0 };
	glGenFramebuffers(1, &geometryBuffer.framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, geometryBuffer.framebufferId);

	// Attach render target textures:
	for (unsigned int i = 0; i < FRAMEBUFFERTYPE_LAST; i++)
	{
		glGenTextures(1, &geometryBuffer.textures[i]);
		glBindTexture(GL_TEXTURE_2D, geometryBuffer.textures[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufferWidth, bufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);		

		switch (i)
		{
		case FramebufferType::POSITION:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		default:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, geometryBuffer.textures[i], 0);		
		bufferAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
	}
	
	glDrawBuffers(FRAMEBUFFERTYPE_LAST, bufferAttachments);

	glGenRenderbuffers(1, &geometryBuffer.depthTargetId);
	glBindRenderbuffer(GL_RENDERBUFFER, geometryBuffer.depthTargetId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, bufferWidth, bufferHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, geometryBuffer.depthTargetId);
  

	GLuint framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	const char *status = nullptr;

	switch(framebufferStatus)
	{
		case GL_FRAMEBUFFER_COMPLETE: break;
		case GL_FRAMEBUFFER_UNDEFINED:
			status = "UNDEFINED";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			status = "INCOMPLETE ATTACHMENT";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			status = "UNSUPPORTED";
			break;
	}

	if(status != nullptr)
	{
		Logger::Instance->error("OpenGL Framebuffer #{} ({}x{}): Status {}",
			geometryBuffer.framebufferId, bufferWidth, bufferHeight, status);		
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GibEngine::Renderer::Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, geometryBuffer.framebufferId);
}

void GibEngine::Renderer::Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
