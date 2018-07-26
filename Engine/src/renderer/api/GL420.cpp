#include "renderer/api/GL420.h"


GibEngine::Renderer::API::GL420::GL420() 
	: uniformBufferManager(new UniformBufferManager())
{
	currentShaderID = 0;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);

	// Enable Debug Messages:
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLFW::GLDebugCallback, nullptr);
}

GibEngine::Renderer::API::GL420::~GL420()
{
	delete uniformBufferManager;
}

void GibEngine::Renderer::API::GL420::BlitFramebuffer(unsigned int framebufferSource, unsigned int framebufferDest, unsigned int framebufferWidth, unsigned int framebufferHeight, unsigned int framebufferFlags)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, framebufferSource);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferDest);

	// NB: This can fail with GL_INVALID_OPERATION, usually means the GPU is expecting a different renderbuffer storage format than the FB depth attachment
	glBlitFramebuffer(0, 0, framebufferWidth, framebufferHeight, 0, 0, framebufferWidth, framebufferHeight, framebufferFlags, GL_NEAREST);

	UnbindFramebuffer();
}

// RegisterCamera/UpdateCamera supercede BindCamera for GL 4
void GibEngine::Renderer::API::GL420::BindCamera(GibEngine::CameraBase *camera) { }

void GibEngine::Renderer::API::GL420::BindFramebuffer(const GibEngine::Renderer::Framebuffer& framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.GetBuffer().framebufferId);
}

void GibEngine::Renderer::API::GL420::BindMaterial(GibEngine::Material* material)
{
	int textureLocIndex[TextureType::TEXTURETYPE_LAST] = { 0 };

	glUniform3fv(
		GetUniformLocation("material.ambientColor"),
		1,
		glm::value_ptr(material->AmbientColor)
	);

	glUniform3fv(
		GetUniformLocation("material.diffuseColor"),
		1,
		glm::value_ptr(material->DiffuseColor)
	);

	glUniform3fv(
		GetUniformLocation("material.specularColor"),
		1,
		glm::value_ptr(material->SpecularColor)
	);

	for (int i = 0; i < TextureType::TEXTURETYPE_LAST; i++)
	{
		BindTexture2D(i, 0);
	}

	for (unsigned int i = 0; i < material->Textures.size(); i++)
	{
		GLint textureLocation = -1;
		MaterialTexture* matTex = &material->Textures[i];

		if (matTex->textureUniformName.length() == 0)
		{
			int locationIndex = textureLocIndex[matTex->texture->GetTextureType()];

			std::string textureUniformName = std::string("texture_" +
				matTex->texture->GetTextureTypeString() + std::to_string(locationIndex));

			matTex->textureUniformName = textureUniformName;
			textureLocIndex[matTex->texture->GetTextureType()]++;
		}

		textureLocation = GetUniformLocation(matTex->textureUniformName.c_str());

		if (textureLocation == -1)
		{
			Logger::Instance->error("Cannot find texture2D sampler: {}", matTex->textureUniformName);
			return;
		}

		glUniform1i(textureLocation, static_cast<float>(i));

		BindTexture2D(i, matTex->texture->GetTextureId());
	}
}

void GibEngine::Renderer::API::GL420::BindTexture2D(unsigned int textureSlot, unsigned int textureId)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void GibEngine::Renderer::API::GL420::BindTextureCubemap(unsigned int textureSlot, unsigned int cubemapTextureId)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureId);
}

void GibEngine::Renderer::API::GL420::BindUniform1f(unsigned int uniformLocation, unsigned int uniformValue)
{
	glUniform1i(uniformLocation, uniformValue);
}

void GibEngine::Renderer::API::GL420::BindUniform3fv(unsigned int uniformLocation, unsigned int count, const float * uniformValue)
{
	glUniform3fv(uniformLocation, count, uniformValue);
}

void GibEngine::Renderer::API::GL420::BindUniform4fv(unsigned int uniformLocation, unsigned int count, const float * uniformValue)
{
	glUniformMatrix4fv(uniformLocation, count, false, &uniformValue[0]);
}

bool GibEngine::Renderer::API::GL420::CreateFramebuffer(GibEngine::Renderer::Framebuffer* framebuffer, int framebufferWidth, int framebufferHeight)
{
	GLuint bufferAttachments[FRAMEBUFFERTYPE_LAST];
	buffer_t buffer = { 0 };

	glGenFramebuffers(1, &buffer.framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.framebufferId);

	// Attach render target textures:
	for (unsigned int i = 0; i < FRAMEBUFFERTYPE_LAST; i++)
	{
		glGenTextures(1, &buffer.textures[i]);
		glBindTexture(GL_TEXTURE_2D, buffer.textures[i]);

		// Per render target mutations:
		switch (i)
		{
		case FramebufferType::AMBIENT_OCCLUSION:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, framebufferWidth, framebufferHeight, 0, GL_RGB, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case FramebufferType::POSITION:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, framebufferWidth, framebufferHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		default:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, framebufferWidth, framebufferHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
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

	framebuffer->SetBuffer(framebufferWidth, framebufferHeight, buffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void GibEngine::Renderer::API::GL420::DeleteFramebuffer(GibEngine::Renderer::Framebuffer * framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteTextures(FRAMEBUFFERTYPE_LAST, &framebuffer->GetBuffer().textures[0]);

	auto depth = framebuffer->GetBuffer().depthTargetId;
	auto fb = framebuffer->GetBuffer().framebufferId;
	glDeleteFramebuffers(1, &depth);
	glDeleteFramebuffers(1, &fb);
}

void GibEngine::Renderer::API::GL420::ClearFramebuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GibEngine::Renderer::API::GL420::DrawPrimitive(const MeshUploadTicket& meshUploadTicket)
{
	const unsigned int FIRST_INDEX = 0;

	glBindVertexArray(meshUploadTicket.vertexArrayObject);
	glDrawArrays(GL_TRIANGLE_STRIP, FIRST_INDEX, meshUploadTicket.totalVertices);
	glBindVertexArray(0);
}

void GibEngine::Renderer::API::GL420::DrawMesh(const GibEngine::Mesh& mesh, size_t instanceCount)
{
	Mesh::Flags flags = mesh.GetFlags();
	if (!Mesh::FlagMask(flags & Mesh::Flags::RENDER_ENABLED))
	{
		return;
	}

	const std::shared_ptr<MeshUploadTicket>& meshUploadTicket = mesh.GetMeshUploadTicket();

	glBindVertexArray(meshUploadTicket->vertexArrayObject);

	GLuint drawMode = Mesh::FlagMask(flags & Mesh::Flags::RENDER_WIREFRAME) ? GL_LINES : GL_TRIANGLES;

	if (Mesh::FlagMask(flags & Mesh::Flags::RENDER_ARRAYS))
	{
		glDrawArrays(drawMode, 0, meshUploadTicket->totalVertices);
	}
	else 
	{
		glDrawElementsInstanced(drawMode, meshUploadTicket->totalIndices, GL_UNSIGNED_INT,
			0, static_cast<GLsizei>(instanceCount));
	}

	glBindVertexArray(0);
}

void GibEngine::Renderer::API::GL420::DrawSkybox(const GibEngine::MeshUploadTicket& skyboxMeshTicket)
{
	glDepthRange(0.999999f, 1.0f);
	glDepthFunc(GL_LEQUAL);

	glBindVertexArray(skyboxMeshTicket.vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, skyboxMeshTicket.totalVertices);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);
}

int GibEngine::Renderer::API::GL420::GetUniformLocation(const char* uniformName)
{
	//ShaderCache shaderCache = shaderCaches[currentShaderID];
	//const auto cachedUniformLocation = shaderCaches[currentShaderID].uniformLocations.find(uniformName);

	//if (cachedUniformLocation != shaderCaches[currentShaderID].uniformLocations.end())
	//{
	//	//Logger::Instance->info("CACHE HIT: {}", uniformName);
	//	return cachedUniformLocation->second;
	//}

	// Cache miss, perform a lookup via OpenGL:
	int uniformLocation = glGetUniformLocation(currentShaderID, uniformName);

	//shaderCaches[currentShaderID].uniformLocations[uniformName] = uniformLocation;
	//[currentShaderID] = shaderCache;
	//Logger::Instance->info("CACHE MISS: {}", uniformName);


	return uniformLocation;
}

unsigned char* GibEngine::Renderer::API::GL420::ReadFramebuffer(GibEngine::Renderer::Framebuffer * framebuffer)
{
	BindFramebuffer(*framebuffer);

	unsigned int pixelBufferSize = framebuffer->GetBufferWidth() * framebuffer->GetBufferHeight() * 3;
	unsigned char* buffer = new unsigned char[pixelBufferSize];

	glReadPixels(0, 0, framebuffer->GetBufferWidth(), framebuffer->GetBufferHeight(), GL_RGB, GL_UNSIGNED_BYTE, buffer);

	return buffer;
}

unsigned char* GibEngine::Renderer::API::GL420::ReadFramebufferTexture(GibEngine::Renderer::Framebuffer * framebuffer, GibEngine::Renderer::FramebufferType framebufferTextureType)
{
	const int framebufferSize = framebuffer->GetBufferWidth() * framebuffer->GetBufferHeight() * 3;
	unsigned char* textureData = new unsigned char[sizeof(unsigned char) * framebufferSize];
	glBindTexture(GL_TEXTURE_2D, framebuffer->GetBuffer().textures[framebufferTextureType]);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	return textureData;
}

void GibEngine::Renderer::API::GL420::RegisterCamera(std::shared_ptr<CameraBase> camera)
{
	const unsigned int BUFFER_OBJECT_SIZE = sizeof(float) * 36;
	const unsigned int PROJECTION_MATRIX_INDEX = 0;
	const unsigned int VIEW_MATRIX_INDEX = 16;
	const unsigned int POSITION_INDEX = 32;

	UniformBuffer* cameraUBO = uniformBufferManager->FindOrCreate(camera->GetNameKey().c_str(), BUFFER_OBJECT_SIZE);

	if (cameraUBO == nullptr)
	{
		Logger::Instance->info("[{}] Failed to find or create UBO: {}", __FUNCTION__, camera->GetNameKey().c_str());
		return;
	}

	float cameraData[BUFFER_OBJECT_SIZE]{ 0 };

	memcpy(&cameraData[PROJECTION_MATRIX_INDEX], glm::value_ptr(camera->GetProjectionMatrix()), sizeof(float) * 16);
	memcpy(&cameraData[VIEW_MATRIX_INDEX], glm::value_ptr(camera->GetViewMatrix()), sizeof(float) * 16);
	memcpy(&cameraData[POSITION_INDEX], glm::value_ptr(camera->GetLocalTransform().GetPosition()), sizeof(float) * 3);

	cameraUBO->Update(cameraData);

	auto cameraUBOIndex = 0U;
	cameraUBOIndex = glGetUniformBlockIndex(currentShaderID, camera->GetNameKey().c_str());
	if (cameraUBOIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(currentShaderID, cameraUBOIndex, cameraUBO->GetBufferBindingIndex());
	}
}

void GibEngine::Renderer::API::GL420::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GibEngine::Renderer::API::GL420::BindShader(unsigned int shaderId)
{
	if (shaderId == currentShaderID)
	{
		return;
	}

	if (currentShaderID > 0 && currentShaderID != shaderId)
	{
		Logger::Instance->error("Shader::End() must be called before Shader::Begin()");
		return;
	}

	glUseProgram(shaderId);
	this->currentShaderID = shaderId;
}

void GibEngine::Renderer::API::GL420::UnbindShader()
{
	glUseProgram(0);
	this->currentShaderID = 0;
}


bool GibEngine::Renderer::API::GL420::UpdateMeshInstances(const MeshUploadTicket& meshUploadTicket, const std::vector<glm::mat4>& instanceMatrixList)
{
	const int VEC4_SIZE = sizeof(glm::vec4);

	glBindVertexArray(meshUploadTicket.vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, meshUploadTicket.buffers.at(BufferIndex::INSTANCE_MATRIX));
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

bool GibEngine::Renderer::API::GL420::UpdateCamera(const CameraBase& camera)
{
	const unsigned int BUFFER_OBJECT_SIZE = sizeof(float) * 36;
	const unsigned int PROJECTION_MATRIX_INDEX = 0;
	const unsigned int VIEW_MATRIX_INDEX = 16;
	const unsigned int POSITION_INDEX = 32;

	UniformBuffer* cameraUBO = uniformBufferManager->Find(camera.GetNameKey().c_str());

	if (cameraUBO == nullptr)
	{
		Logger::Instance->info("[{}] Failed to find or create UBO: {}", __FUNCTION__, camera.GetNameKey().c_str());
		return false;
	}

	float cameraData[BUFFER_OBJECT_SIZE] { 0 };

	memcpy(&cameraData[PROJECTION_MATRIX_INDEX], glm::value_ptr(camera.GetProjectionMatrix()), sizeof(float) * 16);
	memcpy(&cameraData[VIEW_MATRIX_INDEX], glm::value_ptr(camera.GetViewMatrix()), sizeof(float) * 16);
	memcpy(&cameraData[POSITION_INDEX], glm::value_ptr(camera.GetLocalTransform().GetPosition()), sizeof(float) * 3);

	cameraUBO->Update(cameraData);

	return true;
}

std::shared_ptr<GibEngine::MeshUploadTicket> GibEngine::Renderer::API::GL420::UploadMesh(const std::vector<GibEngine::Vertex>& vertexList, const std::vector<unsigned int>& indexList)
{
	auto ticket = std::shared_ptr<MeshUploadTicket>(new MeshUploadTicket());

	ticket->totalVertices = static_cast<int>(vertexList.size());
	ticket->totalIndices = static_cast<int>(indexList.size());

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

void GibEngine::Renderer::API::GL420::UploadTexture2D(unsigned int* textureId, const TextureData& textureData, SamplerFiltering filtering, SamplerEdgeClamping edgeClamping)
{
	glGenTextures(1, textureId);
	glBindTexture(GL_TEXTURE_2D, *textureId);

	GLuint textureFormat = GL_RGB,
		samplerFiltering = GL_LINEAR,
		samplerEdgeClamp = GL_REPEAT;

	/*	and what type am I using as the internal texture format?	*/
	switch (textureData.Channels)
	{
	case 3:
		textureFormat = GL_RGB;
		break;
	case 4:
		textureFormat = GL_RGBA;
		break;
	}

	/* what type of filtering to apply to the sampler */
	switch (filtering)
	{
	case SamplerFiltering::LINEAR:
		samplerFiltering = GL_LINEAR;
		break;
	case SamplerFiltering::NEAREST:
		samplerFiltering = GL_NEAREST;
		break;
	}

	/* what's happening at the edges if we're over? */
	switch (edgeClamping)
	{
	case SamplerEdgeClamping::CLAMP_TO_BORDER:
		samplerEdgeClamp = GL_CLAMP_TO_BORDER;
		break;
	case SamplerEdgeClamping::CLAMP_TO_EDGE:
		samplerEdgeClamp = GL_CLAMP_TO_EDGE;
		break;
	case SamplerEdgeClamping::MIRRORED_CLAMP_TO_EDGE:
		samplerEdgeClamp = GL_MIRROR_CLAMP_TO_EDGE;
		break;
	case SamplerEdgeClamping::MIRRORED_REPEAT:
		samplerEdgeClamp = GL_MIRROR_CLAMP_TO_EDGE;
		break;
	}

	unsigned int glDataType;
	switch (textureData.DataType)
	{
	case StorageType::FLOAT:
		glDataType = GL_FLOAT;
		break;
	case StorageType::UNSIGNED_CHAR:
	default:
		glDataType = GL_UNSIGNED_BYTE;
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, textureData.Width, textureData.Height, 0, textureFormat, glDataType, textureData.Data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplerFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplerFiltering);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, samplerEdgeClamp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, samplerEdgeClamp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplerEdgeClamp);

}

void GibEngine::Renderer::API::GL420::UploadTextureCubemap(unsigned int* textureId, std::vector<GibEngine::TextureData>& cubemapSideData)
{
	const std::vector<GLuint> cubemapTargets = {
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	};

	//unsigned int textureId = 0;
	//Cubemap cubemap = texture->GetCubemap();

	glGenTextures(1, textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *textureId);

	for (unsigned int i = 0; i < 6; i++)
	{
		//TextureData* imgData = cubemap.textures[i];
		auto cubemapSide = cubemapSideData.at(i);

		GLuint textureFormat = GL_RGB;
		/*	and what type am I using as the internal texture format?	*/
		switch (cubemapSide.Channels)
		{
		case 3:
			textureFormat = GL_RGB;
			break;
		case 4:
			textureFormat = GL_RGBA;
			break;
		}

		glTexImage2D(cubemapTargets[i], 0, textureFormat, cubemapSide.Width, cubemapSide.Height, 0, textureFormat, GL_UNSIGNED_BYTE, cubemapSide.Data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);


	//if (textureId > 0)
	//{
	//	texture->SetLoaded(true);
	//	texture->SetTextureId(textureId);
	//}
}