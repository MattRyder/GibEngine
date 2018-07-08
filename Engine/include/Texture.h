#pragma once

#include <string>
#include <glm/vec2.hpp>

#include "Logger.h"

namespace GibEngine
{
	enum TextureType
	{
		DIFFUSE,
		SPECULAR,
		NORMAL,
		TEXTURETYPE_LAST
	};

	enum class StorageType { FLOAT, UNSIGNED_CHAR };

	struct TextureData {
		unsigned int Target;
		TextureType Type;
		int Width;
		int Height;
		int Channels;
		void* Data;
		StorageType DataType;

		bool IsPowerOfTwo()
		{
			return (Width & (Width - 1)) != 0 || (Height & (Height - 1)) != 0;
		}
	};

	class Texture
	{
		const std::string fileName;

		unsigned int textureId;
		TextureType type;
		glm::vec2 size;

	public:
		static const std::string TextureTypeStrings[TextureType::TEXTURETYPE_LAST + 1];
		
		Texture();
		Texture(int textureId, TextureType type, glm::vec2 size);

		const std::string GetFilename() const;
		unsigned int GetTextureId() const;

		TextureType GetTextureType() const;
		const std::string GetTextureTypeString() const;
	};
}