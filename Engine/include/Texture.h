#pragma once

#include <string>
#include <assimp/scene.h>
#include <GL/gl3w.h>

#include "Logger.h"
#include "File.h"

namespace GibEngine
{
	enum TextureType
	{
		DIFFUSE,
		SPECULAR,
		NORMAL,
		TEXTURETYPE_LAST
	};

	struct TextureData {
		unsigned int Target;
		int Width;
		int Height;
		int Channels;
		unsigned char *Data;

		bool IsPowerOfTwo()
		{
			return (Width & (Width - 1)) != 0 || (Height & (Height - 1)) != 0;
		}
	};

	struct Cubemap
	{
		std::string* directory;
		const char* extension;

		TextureData* textures[6];
	};


	class Texture
	{
		std::string *fileName;
		unsigned int textureId;
		bool isUploaded;

		Cubemap* cubemap;
		TextureData* imageData;
		bool isLoaded = false;

		TextureType type;

	protected:
		Texture();
		Texture(TextureType type, std::string *fileName);

		static TextureData* LoadTextureData(std::string *textureFilename);

	public:
		static const char* TextureTypeStrings[4];
		

		~Texture();

		static Texture* Load(TextureType type, std::string *fileName);
		static Texture* LoadCubemap(std::string *cubemapDirectory, const char *textureExtension);

		std::string* GetFilename();
		unsigned int GetTextureId();
		TextureType GetTextureType();
		const char* GetTextureTypeString();
		TextureData* GetTextureData();

		Cubemap* GetCubemap();

		bool IsLoaded() { return this->isLoaded; }

		void SetTextureData(TextureData *textureData);
		void SetTextureId(unsigned int textureId);
		void SetCubemap(Cubemap *cubemap);
		bool SetLoaded(bool loaded);

	};
}