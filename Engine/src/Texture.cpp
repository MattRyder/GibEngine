#include "Texture.h"

const std::string GibEngine::Texture::TextureTypeStrings[TextureType::TEXTURETYPE_LAST + 1] = {
    "diffuse", "specular", "normal", "undefined"
};

GibEngine::Texture::Texture() : Texture(0, TextureType::TEXTURETYPE_LAST, {}) { }

GibEngine::Texture::Texture(int textureId, TextureType type, glm::vec2 size) : textureId(textureId), type(type), size(size) { }

GibEngine::TextureType GibEngine::Texture::GetTextureType() const
{
	return this->type;
}

const std::string GibEngine::Texture::GetTextureTypeString() const
{
	return TextureTypeStrings[this->type];
}

unsigned int GibEngine::Texture::GetTextureId() const
{
    return textureId;
}

const std::string GibEngine::Texture::GetFilename() const
{
	return this->fileName;
}