#pragma once

#include <string>
#include <assimp/scene.h>
#include <GL/gl3w.h>

#include "Logger.h"
#include "File.h"

namespace GibEngine
{
	enum class TextureType
	{
		DIFFUSE,
		SPECULAR,
		HEIGHT,
		NORMAL,
		TEXTURETYPE_LAST
	};

	class Texture
	{
		typedef struct texture_data_t
		{
			GLuint Target;
			int Width;
			int Height;
			int Channels;
			unsigned char *Data;

			bool IsPowerOfTwo()
			{
				return (Width & (Width - 1)) != 0 || (Height & (Height - 1)) != 0;
			}
		} TextureData;

		std::string *fileName;
		TextureData *data;
		TextureType type;

		GLuint textureId;

		TextureData* Load(std::string *fileName);

	public:
		Texture();
		Texture(TextureType type, std::string *fileName);
		~Texture();

		static Texture* LoadCubemap(std::string top, std::string bottom, std::string left,
			std::string right, std::string front, std::string back);

		static const char* TextureTypeStrings[4];

		GLuint GetTextureId();
	};
}