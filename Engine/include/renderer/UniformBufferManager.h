#pragma once

#include "Entity.h"
#include "Shader.h"
#include "RenderPassType.h"

namespace GibEngine
{
	namespace Renderer
	{
		class UniformBuffer
		{
			// Where OpenGL has stored the buffer:
			GLuint bufferId;

			// Which UBO index the buffer is bound to:
			GLuint bufferBindingIndex;

			// Name of the block in GLSL:
			const std::string uniformBlockName;

			// Size of the UBO:
			size_t size;

		public:
			UniformBuffer(const std::string bufferName, GLuint bufferIndex, size_t bufferSize)
				: bufferId(0), uniformBlockName(bufferName), bufferBindingIndex(bufferIndex), size(bufferSize)
			{
				glGenBuffers(1, &bufferId);
				glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
				glBufferData(GL_UNIFORM_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);

				// Bind the buffer to the given buffer index:
				glBindBufferRange(GL_UNIFORM_BUFFER, bufferIndex, bufferId, 0, bufferSize);
			}

			virtual ~UniformBuffer()
			{
				glDeleteBuffers(1, &bufferId);
			}

			void Update(GLvoid* newData)
			{
				Update(newData, 0, size);
			}

			void Update(GLvoid* newData, unsigned int offset, size_t size)
			{
				glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
				glBufferSubData(GL_UNIFORM_BUFFER, offset, size, newData);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}

			GLuint GetBufferBindingIndex()
			{
				return this->bufferBindingIndex;
			}

			const std::string GetBufferName()
			{
				return uniformBlockName;
			}
		};

		class UniformBufferManager
		{
			const static unsigned int MAX_UNIFORM_BUFFER_COUNT = 64;
			const static unsigned int NO_AVAILABLE_INDEX = 0xBAADC0DE;

			UniformBuffer* buffers[MAX_UNIFORM_BUFFER_COUNT] = { 0 };

		protected:
			// Find and return a suitable uniform binding index
			unsigned int GetAvailableBufferIndex();
		public:
			UniformBufferManager() = default;
			~UniformBufferManager();

			UniformBuffer* Create(const std::string bufferName, size_t bufferSize);
			UniformBuffer* Create(const std::string bufferName, size_t bufferSize, GLvoid *bufferData);

			UniformBuffer* Find(const std::string bufferName);
			UniformBuffer* FindOrCreate(const std::string bufferName, size_t bufferSize);

			void Update(UniformBuffer* uniformBuffer, GLvoid* newData);

			void Destroy(UniformBuffer* uniformBuffer);
		};
	}
}