#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


const char* GibEngine::Texture::TextureTypeStrings[4] = {
    "diffuse", "specular", "normal"
};

GibEngine::Texture::Texture()
{
	this->fileName = nullptr;
	this->type = TextureType::TEXTURETYPE_LAST;
	this->textureId = 0;	
}

GibEngine::Texture::Texture(GibEngine::TextureType type, std::string *fileName) : Texture()
{
    this->type = type;
	this->fileName = fileName;
}

GibEngine::TextureData* GibEngine::Texture::LoadTextureData(std::string *textureFilename)
{
	TextureData* texData = new TextureData();
	texData->Data = stbi_load(textureFilename->c_str(), &texData->Width, &texData->Height, &texData->Channels, 0);

	if (texData->Data == nullptr)
	{
		Logger::Instance->error("Texture::Load Failed! Image data is null!\nTexture: {}", textureFilename->c_str());
		return nullptr;
	}

	return texData;
}

GibEngine::Texture::~Texture()
{
    delete this->fileName;
}

GibEngine::Texture* GibEngine::Texture::Load(GibEngine::TextureType type, std::string *fileName)
{
	Texture* texture = new Texture(type, fileName);
	TextureData* texData = Texture::LoadTextureData(fileName);

	texture->SetTextureData(texData);

	return texture;
}


GibEngine::Texture* GibEngine::Texture::LoadCubemap(std::string* cubemapDirectory, const char* textureExtension)
{
	Texture* cubemapTexture = new Texture();
	
	Cubemap* cubemap = new Cubemap();
	cubemap->directory = cubemapDirectory;
	cubemap->extension = textureExtension;

	const std::vector<const char*> cubeSides = { "left", "right", "bottom", "top", "front", "back" };

	for (unsigned int i = 0; i < 6; i++)
	{
		std::string* sideTextureFilename = new std::string(*cubemap->directory + "/" + cubeSides.at(i) + "." + cubemap->extension);
		cubemap->textures[i] = Texture::LoadTextureData(sideTextureFilename);
		delete sideTextureFilename;
	}

    cubemapTexture->SetCubemap(cubemap);
    
    return cubemapTexture;
}

GibEngine::TextureType GibEngine::Texture::GetTextureType()
{
	return this->type;
}

const char* GibEngine::Texture::GetTextureTypeString()
{
	return TextureTypeStrings[this->type];
}

GibEngine::TextureData* GibEngine::Texture::GetTextureData()
{
	return this->imageData;
}

GLuint GibEngine::Texture::GetTextureId()
{
    return textureId;
}

std::string* GibEngine::Texture::GetFilename()
{
	return this->fileName;
}

void GibEngine::Texture::SetTextureData(TextureData* textureData)
{
	this->imageData = textureData;
	this->isLoaded = true;
}

void GibEngine::Texture::SetTextureId(unsigned int textureId)
{
	this->textureId = textureId;
	this->isUploaded = true;
}

void GibEngine::Texture::SetCubemap(Cubemap *cubemap)
{
    this->cubemap = cubemap;
}

bool GibEngine::Texture::SetLoaded(bool loaded)
{
	return this->isLoaded;
}

GibEngine::Cubemap* GibEngine::Texture::GetCubemap()
{
    return this->cubemap;
}