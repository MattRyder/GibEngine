#pragma once

#include <vector>
#include <GL/gl3w.h>
#include <glm/detail/type_vec3.hpp>
//#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Logger.h"

namespace GibEngine
{
	namespace Renderer
	{
		enum FramebufferType
		{
			POSITION,
			ALBEDO,
			NORMAL,
			FRAMEBUFFERTYPE_LAST
		};

		struct buffer_t
		{
			GLuint framebufferId;
			GLuint textures[FRAMEBUFFERTYPE_LAST];
			GLuint depthTargetId;
		};

		class Framebuffer
		{
			buffer_t geometryBuffer;

			int bufferWidth;
			int bufferHeight;

		public:
			Framebuffer(int bufferWidth, int bufferHeight);

			void Bind();
			void Unbind();

			buffer_t GetBuffer() const;
			int GetBufferWidth() const;
			int GetBufferHeight() const;
		};
	}
}