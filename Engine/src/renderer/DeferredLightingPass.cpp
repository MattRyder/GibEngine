#include "renderer/DeferredLightingPass.h"

GLfloat GibEngine::Renderer::DeferredLightingPass::QuadTextureData[] = {
	// Positions			// Texture Coords
	-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
	1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
};

GibEngine::Renderer::DeferredLightingPass::DeferredLightingPass(UniformBufferManager* uniformBufferManager, Shader* shader, Framebuffer* framebuffer)
	: RenderPass(uniformBufferManager, shader, framebuffer)
{
	this->framebuffer = framebuffer;
	LoadQuadData();
}

void GibEngine::Renderer::DeferredLightingPass::LoadQuadData()
{
	const int POSITION_SIZE = 3;
	const int TEX_COORD_SIZE = 2;

	glCreateVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glCreateBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QuadTextureData), &QuadTextureData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, POSITION_SIZE, GL_FLOAT, GL_FALSE, (POSITION_SIZE + TEX_COORD_SIZE) * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, TEX_COORD_SIZE, GL_FLOAT, GL_FALSE, (POSITION_SIZE + TEX_COORD_SIZE) * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
}

void GibEngine::Renderer::DeferredLightingPass::Render()
{
	const int QUAD_VERTICES_COUNT = 4;
	const int FRAMEBUFFER_TEXTURE_COUNT = 3;

	//framebuffer->Bind();

	shader->Begin();

	buffer_t buffer = framebuffer->GetBuffer();
	for (unsigned int i = 0; i < FRAMEBUFFER_TEXTURE_COUNT; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, buffer.textures[i]);
	}

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, QUAD_VERTICES_COUNT);
	glBindVertexArray(0);

	shader->End();

	//framebuffer->Unbind();
}

void GibEngine::Renderer::DeferredLightingPass::Update(float deltaTime) { }
