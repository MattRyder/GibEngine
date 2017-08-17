#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

const char* GibEngine::Texture::TextureTypeStrings[4] = {
    "diffuse", "specular", "normal"
};

GibEngine::Texture::Texture()
{
	this->data = nullptr;
	this->fileName = nullptr;
	this->type = TextureType::TEXTURETYPE_LAST;
	this->textureId = 0;

	glGenTextures(1, &textureId);
	
}

GibEngine::Texture::Texture(GibEngine::TextureType type, std::string *fileName) : Texture()
{
    this->type = type;
    this->fileName = fileName;

    this->data = Load(fileName);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->Width, data->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->Data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data->Data);
    delete this->data;
    this->data = nullptr;
}

GibEngine::Texture::~Texture()
{
    delete this->fileName;
}

GibEngine::Texture* GibEngine::Texture::LoadCubemap(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back)
{
	std::vector<std::string> sides;
	sides.push_back(right);
	sides.push_back(left);
	sides.push_back(top);
	sides.push_back(bottom);
	sides.push_back(front);
	sides.push_back(back);

	Texture* texture = new Texture();
	texture->type = TextureType::DIFFUSE;

	GLuint textureID = texture->GetTextureId();
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, channels;
	for (unsigned int i = 0; i < sides.size(); i++)
	{
		unsigned char* textureData = stbi_load(sides.at(i).c_str(), &width, &height, &channels, STBI_rgb_alpha);
		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
			stbi_image_free(textureData);
		}
		else
		{
			Logger::Instance->error("Failed to load cubemap side {}", sides.at(i).c_str());
			stbi_image_free(textureData);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

GLuint GibEngine::Texture::GetTextureId()
{
    return textureId;
}

GibEngine::Texture::TextureData* GibEngine::Texture::Load(std::string *fileName)
{
    TextureData *textureData = new TextureData();
	textureData->Data = nullptr;
    textureData->Data = stbi_load(fileName->c_str(), &textureData->Width, &textureData->Height, &textureData->Channels, STBI_rgb_alpha);

    if (!textureData->Data)
    {
        Logger::Instance->error("Failed to load Texture from file: {}", fileName->c_str());
    }

    if (!textureData->IsPowerOfTwo())
    {
        Logger::Instance->trace("Texture file `{}` is not sized as a power of two!", fileName->c_str());
    }

    return textureData;
}
