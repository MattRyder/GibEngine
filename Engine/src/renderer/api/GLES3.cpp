#include "renderer/api/GLES3.h"

GibEngine::Renderer::API::GLES3::~GLES3()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
}

void GibEngine::Renderer::API::GLES3::BlitFramebuffer(unsigned int framebufferSource, unsigned int framebufferDest, unsigned int framebufferWidth, unsigned int framebufferHeight, unsigned int framebufferFlags)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, framebufferSource);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferDest);

	// NB: This can fail with GL_INVALID_OPERATION, usually means the GPU is expecting a different renderbuffer storage format than the FB depth attachment
	glBlitFramebuffer(0, 0, framebufferWidth, framebufferHeight, 0, 0, framebufferWidth, framebufferHeight, framebufferFlags, GL_NEAREST);
}

void GibEngine::Renderer::API::GLES3::BindCamera(GibEngine::CameraBase *camera)
{	
	int projLoc = glGetUniformLocation(currentShaderID, "camera.ProjectionMatrix");
	const GLfloat* projMat = glm::value_ptr(camera->GetProjectionMatrix());
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projMat[0]);
	
	int viewLoc = glGetUniformLocation(currentShaderID, "camera.ViewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	int posLoc = glGetUniformLocation(currentShaderID, "camera.CameraPosition");
	glUniform3fv(posLoc, 1, glm::value_ptr(camera->GetPosition()));
}

void GibEngine::Renderer::API::GLES3::BindFramebuffer(GibEngine::Renderer::Framebuffer *framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetBuffer().framebufferId);
}

void GibEngine::Renderer::API::GLES3::BindMaterial(GibEngine::Material* material)
{
	std::map<TextureType, int> textureLocIndex = {
		{TextureType::DIFFUSE, 0}, {TextureType::NORMAL, 0}, {TextureType::SPECULAR, 0}
	};

	for (unsigned int i = 0; i < material->Textures.size(); i++)
	{
		Texture* texture = material->Textures[i];
		
		int locationIndex = textureLocIndex.at(texture->GetTextureType());
		const char *textureTypeStr = texture->GetTextureTypeString();
		std::string textureUniformName = std::string("texture_" + 
			std::string(textureTypeStr) + std::to_string(locationIndex));
		GLint textureLocation = glGetUniformLocation(currentShaderID, textureUniformName.c_str());

		if(textureLocation == -1)
		{
			Logger::Instance->error("Cannot find texture2D sampler: {}", textureUniformName.c_str());			
		}

		glUniform1i(textureLocation, static_cast<float>(i));
		
		BindTexture2D(i, texture->GetTextureId());

		textureLocIndex.at(texture->GetTextureType())++;
	}
}

void GibEngine::Renderer::API::GLES3::BindTexture2D(unsigned int textureSlot, unsigned int textureId)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void GibEngine::Renderer::API::GLES3::BindTextureCubemap(unsigned int textureSlot, unsigned int cubemapTextureId)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureId);
}

void GibEngine::Renderer::API::GLES3::BindUniform1f(unsigned int uniformLocation, unsigned int uniformValue)
{
	glUniform1i(uniformLocation, uniformValue);
}

void GibEngine::Renderer::API::GLES3::BindUniform3fv(unsigned int uniformLocation, unsigned int count, const float * uniformValue)
{
	glUniform3fv(uniformLocation, count, uniformValue);
}

bool GibEngine::Renderer::API::GLES3::CreateFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer, int framebufferWidth, int framebufferHeight)
{
	GLuint bufferAttachments[FRAMEBUFFERTYPE_LAST];
	buffer_t buffer = framebuffer->GetBuffer();

	glGenFramebuffers(1, &buffer.framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.framebufferId);

	// Attach render target textures:
	for (unsigned int i = 0; i < FRAMEBUFFERTYPE_LAST; i++)
	{
		glGenTextures(1, &buffer.textures[i]);
		glBindTexture(GL_TEXTURE_2D, buffer.textures[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, framebufferWidth, framebufferHeight, 0, GL_RGBA, GL_FLOAT, nullptr);

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

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, buffer.textures[i], 0);
		bufferAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
	}

	glDrawBuffers(FRAMEBUFFERTYPE_LAST, bufferAttachments);

	glGenRenderbuffers(1, &buffer.depthTargetId);
	glBindRenderbuffer(GL_RENDERBUFFER, buffer.depthTargetId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, framebufferWidth, framebufferHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer.depthTargetId);

	GLuint framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	const char *status = nullptr;

	switch (framebufferStatus)
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

	if (status != nullptr)
	{
		Logger::Instance->error("OpenGL Framebuffer #{} ({}x{}): Status {}",
			buffer.framebufferId, framebufferWidth, framebufferHeight, status);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void GibEngine::Renderer::API::GLES3::DeleteFramebuffer(GibEngine::Renderer::Framebuffer * framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteTextures(FRAMEBUFFERTYPE_LAST, &framebuffer->GetBuffer().textures[0]);

	auto depth = framebuffer->GetBuffer().depthTargetId;
	auto fb = framebuffer->GetBuffer().framebufferId;
	glDeleteFramebuffers(1, &depth);
	glDeleteFramebuffers(1, &fb);
}

void GibEngine::Renderer::API::GLES3::ClearFramebuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GibEngine::Renderer::API::GLES3::DrawPrimitive(MeshUploadTicket* meshUploadTicket)
{
	const unsigned int FIRST_INDEX = 0;

	glBindVertexArray(meshUploadTicket->vertexArrayObject);
	glDrawArrays(GL_TRIANGLE_STRIP, FIRST_INDEX, meshUploadTicket->totalVertices);
	glBindVertexArray(0);
}

void GibEngine::Renderer::API::GLES3::DrawMesh(GibEngine::Mesh *mesh)
{
	Mesh::Flags flags = mesh->GetFlags();
	if (flags && !Mesh::Flags::RENDER_ENABLED)
	{
		return;
	}

	MeshUploadTicket* meshUploadTicket = mesh->GetMeshUploadTicket();

	glBindVertexArray(meshUploadTicket->vertexArrayObject);

	GLuint drawMode = (flags & Mesh::Flags::RENDER_WIREFRAME) ? GL_LINES : GL_TRIANGLES;

	if (flags & Mesh::Flags::RENDER_ARRAYS)
	{
		glDrawArrays(drawMode, 0, meshUploadTicket->totalVertices);
	}
	else
	{
		glDrawElementsInstanced(drawMode, meshUploadTicket->totalIndices, GL_UNSIGNED_INT,
			0, mesh->GetInstanceMatrices().size());
	}

	glBindVertexArray(0);
}

void GibEngine::Renderer::API::GLES3::DrawSkybox(GibEngine::Skybox *skybox)
{
	glDepthRangef(0.999999f, 1.0f);
	glDepthFunc(GL_LEQUAL);
	
	MeshUploadTicket* meshUploadTicket = skybox->GetMeshUploadTicket();
		
	glBindVertexArray(meshUploadTicket->vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, meshUploadTicket->totalVertices);
	glBindVertexArray(0);
	
	glDepthFunc(GL_LESS);
	glDepthRangef(0.0f, 1.0f);	
}

int GibEngine::Renderer::API::GLES3::GetUniformLocation(const char *uniformName)
{
	GLint uniformLocation = glGetUniformLocation(currentShaderID, uniformName);

	if (uniformLocation == -1)
	{
		Logger::Instance->error("[{}] Failed to find Uniform: {}", __FUNCTION__, uniformName);
		return -1;
	}

	return uniformLocation;
}

unsigned char* GibEngine::Renderer::API::GLES3::ReadFramebuffer(GibEngine::Renderer::Framebuffer * framebuffer)
{
	BindFramebuffer(framebuffer);

	unsigned int pixelBufferSize = framebuffer->GetBufferWidth() * framebuffer->GetBufferHeight() * 3;
	unsigned char* buffer = new unsigned char[pixelBufferSize];

	glReadPixels(0, 0, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), GL_RGB, GL_UNSIGNED_BYTE, buffer);

	return buffer;
}

unsigned char * GibEngine::Renderer::API::GLES3::ReadFramebufferTexture(GibEngine::Renderer::Framebuffer * framebuffer, GibEngine::Renderer::FramebufferType framebufferTextureType)
{
	const int framebufferSize = framebuffer->GetBufferWidth() * framebuffer->GetBufferHeight() * 3;
	unsigned char* textureData = new unsigned char[framebufferSize];
	glBindTexture(GL_TEXTURE_2D, framebuffer->GetBuffer().textures[framebufferTextureType]);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, textureData);

	return textureData;
}

void GibEngine::Renderer::API::GLES3::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GibEngine::Renderer::API::GLES3::BindShader(unsigned int shaderId)
{
	GLint currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	if (currentProgram > 0 && currentProgram != shaderId)
	{
		Logger::Instance->error("Shader::End() must be called before Shader::Begin()");
	}

	glUseProgram(shaderId);
	this->currentShaderID = shaderId;
}

void GibEngine::Renderer::API::GLES3::UnbindShader()
{
	glUseProgram(0);
	this->currentShaderID = 0;
}

bool GibEngine::Renderer::API::GLES3::UpdateMeshInstances(MeshUploadTicket *meshUploadTicket, std::vector<glm::mat4> instanceMatrixList)
{
	const int VEC4_SIZE = sizeof(glm::vec4);

	glBindVertexArray(meshUploadTicket->vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, meshUploadTicket->buffers.at(BufferIndex::INSTANCE_MATRIX));
	glBufferData(GL_ARRAY_BUFFER, instanceMatrixList.size() * sizeof(glm::mat4), &instanceMatrixList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)VEC4_SIZE);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(VEC4_SIZE * 2));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(VEC4_SIZE * 3));

	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);

	return true;
}

bool GibEngine::Renderer::API::GLES3::UpdateCamera(CameraBase* camera)
{
	BindCamera(camera);
	return true;
}

GibEngine::MeshUploadTicket* GibEngine::Renderer::API::GLES3::UploadMesh(std::vector<Vertex> vertexList, std::vector<unsigned int> indexList)
{
	MeshUploadTicket* ticket = new MeshUploadTicket();

	ticket->totalVertices = vertexList.size();
	ticket->totalIndices = indexList.size();

	// Vertex, Element,BufferObjects
	GLuint buffers[BufferIndex::BUFFERINDEX_LAST] = { 0 };

	glGenVertexArrays(1, &ticket->vertexArrayObject);
	glGenBuffers(BufferIndex::BUFFERINDEX_LAST, &buffers[0]);

	ticket->buffers.insert(ticket->buffers.begin(), &buffers[0], &buffers[BufferIndex::BUFFERINDEX_LAST]);

	glBindVertexArray(ticket->vertexArrayObject);
	
	glBindBuffer(GL_ARRAY_BUFFER, ticket->buffers[BufferIndex::VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	if (indexList.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BufferIndex::INDEX]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexList.size() * sizeof(unsigned int), &indexList[0], GL_STATIC_DRAW);
	}

	// Setup Position:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	
	// Setup Normals:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	// Setup TexCoord:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));

	// Setup Tangents:
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

	// Setup Bitangents:
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);

	return ticket;
}

GibEngine::MeshUploadTicket* GibEngine::Renderer::API::GLES3::UploadMesh(GibEngine::Mesh *mesh)
{
	return UploadMesh(mesh->GetVertices(), mesh->GetIndices());
}

void GibEngine::Renderer::API::GLES3::UploadTexture2D(GibEngine::Texture *texture)
{
	unsigned int textureId = 0;

	TextureData* texData = texture->GetTextureData();

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	GLuint textureFormat = GL_RGB;
	/*	and what type am I using as the internal texture format?	*/
	switch (texData->Channels)
	{
	case 3:
		textureFormat = GL_RGB;
		break;
	case 4:
		textureFormat = GL_RGBA;
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, texData->Width, texData->Height, 0, textureFormat, GL_UNSIGNED_BYTE, texData->Data);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (textureId == 0)
	{
		Logger::Instance->error("GLES3::UploadTexture2D Failed!\nError: {}\nTexture: {}",
			0, texture->GetFilename()->c_str());
	}
	else
	{
		texture->SetTextureId(textureId);
	}
}

void GibEngine::Renderer::API::GLES3::UploadTextureCubemap(GibEngine::Texture *texture)
{
	const std::vector<GLuint> cubemapTargets = {
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	};

	unsigned int textureId = 0;
	Cubemap* cubemap = texture->GetCubemap();

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	for (unsigned int i = 0; i < 6; i++)
	{
		TextureData* imgData = cubemap->textures[i];

		GLuint textureFormat = GL_RGB;
		/*	and what type am I using as the internal texture format?	*/
		switch (imgData->Channels)
		{
		case 3:
			textureFormat = GL_RGB;
			break;
		case 4:
			textureFormat = GL_RGBA;
			break;
		}

		glTexImage2D(cubemapTargets[i], 0, textureFormat, imgData->Width, imgData->Height, 0, textureFormat, GL_UNSIGNED_BYTE, imgData->Data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);


	if (textureId > 0)
	{
		texture->SetTextureId(textureId);
	}
}