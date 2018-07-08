#pragma once

namespace GibEngine
{
	namespace Renderer
	{
		enum FramebufferType
		{
			POSITION,
			ALBEDO,
			NORMAL,
			AMBIENT_OCCLUSION,
			FRAMEBUFFERTYPE_LAST
		};

		struct buffer_t
		{
			unsigned int framebufferId;
			unsigned int textures[FRAMEBUFFERTYPE_LAST];
			unsigned int depthTargetId;
		};

		class Framebuffer
		{
			buffer_t geometryBuffer;

			int bufferWidth;
			int bufferHeight;

		public:
			Framebuffer(int bufferWidth, int bufferHeight);

			buffer_t GetBuffer() const;
			int GetBufferWidth() const;
			int GetBufferHeight() const;

			void SetBuffer(int bufferWidth, int bufferHeight, buffer_t buffer);
		};
	}
}