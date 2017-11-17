#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

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
			GLuint bufferId = 0;

			// Which UBO index the buffer is bound to:
			GLuint bufferBindingIndex;

			// Name of the block in GLSL:
			const char* uniformBlockName;

			// Size of the UBO:
			size_t size;

		public:
			UniformBuffer(const char* bufferName, GLuint bufferIndex, size_t bufferSize)
			{
				this->uniformBlockName = bufferName;
				this->bufferBindingIndex = bufferIndex;
				this->size = bufferSize;

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

			const char* GetBufferName()
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
			UniformBufferManager();
			~UniformBufferManager();

			UniformBuffer* Create(const char* bufferName, size_t bufferSize);
			UniformBuffer* Create(const char* bufferName, size_t bufferSize, GLvoid *bufferData);

			UniformBuffer* Find(const char* bufferName);
			UniformBuffer* FindOrCreate(const char* bufferName, size_t bufferSize);

			void Bind(Shader* shader);

			void Update(UniformBuffer* uniformBuffer, GLvoid* newData);

			void Destroy(UniformBuffer* uniformBuffer);
		};
	}
}