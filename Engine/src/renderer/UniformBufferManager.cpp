#include "renderer/UniformBufferManager.h"

GibEngine::Renderer::UniformBufferManager::UniformBufferManager()
{
}

GibEngine::Renderer::UniformBufferManager::~UniformBufferManager()
{
	for (unsigned int i = 0; i < MAX_UNIFORM_BUFFER_COUNT; i++)
	{
		delete buffers[i];
	}
}

GibEngine::Renderer::UniformBuffer* GibEngine::Renderer::UniformBufferManager::Create(const char* bufferName, size_t bufferSize)
{
	unsigned int bufferIndex = GetAvailableBufferIndex();

	if (bufferIndex == NO_AVAILABLE_INDEX)
	{
		Logger::Instance->error("Cannot allocate Uniform Buffer '{}', hit maximum indexes!", bufferName);
		return nullptr;
	}

	UniformBuffer* buffer = new UniformBuffer(bufferName, bufferIndex, bufferSize);
	this->buffers[bufferIndex] = buffer;

	return buffer;
}

GibEngine::Renderer::UniformBuffer* GibEngine::Renderer::UniformBufferManager::Create(const char* bufferName, size_t bufferSize, GLvoid * bufferData)
{
	UniformBuffer* buffer = Create(bufferName, bufferSize);

	if (buffer != nullptr)
	{
		buffer->Update(bufferData);
	}

	return buffer;
}

GibEngine::Renderer::UniformBuffer* GibEngine::Renderer::UniformBufferManager::FindOrCreate(const char * bufferName, size_t bufferSize)
{
	UniformBuffer* buffer = nullptr;
	if ((buffer = Find(bufferName)) != nullptr)
	{
		return buffer;
	}

	return Create(bufferName, bufferSize);
}

void GibEngine::Renderer::UniformBufferManager::Bind(Shader* shader)
{
}

void GibEngine::Renderer::UniformBufferManager::Update(UniformBuffer* uniformBuffer, GLvoid* newData)
{
	uniformBuffer->Update(newData);
}

void GibEngine::Renderer::UniformBufferManager::Destroy(UniformBuffer* uniformBuffer)
{
	this->buffers[uniformBuffer->GetBufferBindingIndex()] = nullptr;
	delete uniformBuffer;
}

GibEngine::Renderer::UniformBuffer* GibEngine::Renderer::UniformBufferManager::Find(const char* bufferName)
{
	for (unsigned int i = 0; i < MAX_UNIFORM_BUFFER_COUNT; i++)
	{
		if (buffers[i] != nullptr && strcmp(buffers[i]->GetBufferName(), bufferName) == 0)
		{
			return buffers[i];
		}
	}

	return nullptr;
}

unsigned int GibEngine::Renderer::UniformBufferManager::GetAvailableBufferIndex()
{
	for (unsigned int i = 0; i < MAX_UNIFORM_BUFFER_COUNT; i++)
	{
		if (buffers[i] == nullptr)
		{
			return i;
		}
	}

	return NO_AVAILABLE_INDEX;
}

