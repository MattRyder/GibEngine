#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

const char* GibEngine::Texture::TextureTypeStrings[4] = {
    "diffuse", "specular", "height", "normal"
};

GibEngine::Texture::Texture()
{
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
	std::mutex mutex;
	std::vector<std::thread> sideThreads;
	std::vector<TextureData*> sideTextures;

	Texture* texture = new Texture();

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureId());

	auto threadFunctor = [&](GLuint cubemapSide, std::string sideFilepath) {
		TextureData* textureData = texture->Load(&sideFilepath);
		textureData->Target = cubemapSide;

		mutex.lock();
		sideTextures.push_back(textureData);
		mutex.unlock();
	};

	sideThreads.push_back(std::thread(threadFunctor, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front));
	sideThreads.push_back(std::thread(threadFunctor, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back));
	sideThreads.push_back(std::thread(threadFunctor, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));
	sideThreads.push_back(std::thread(threadFunctor, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top));
	sideThreads.push_back(std::thread(threadFunctor, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left));
	sideThreads.push_back(std::thread(threadFunctor, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right));

	for (unsigned int i = 0; i < sideThreads.size(); i++) {
		sideThreads.at(i).join();
	}

	for (TextureData* sideTexture : sideTextures) {
		glTexImage2D(sideTexture->Target, 0, GL_RGBA, sideTexture->Width, sideTexture->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sideTexture->Data);
		delete[] sideTexture->Data;
		delete sideTexture;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	return texture;
}

GLuint GibEngine::Texture::GetTextureId()
{
    return textureId;
}

GibEngine::Texture::TextureData* GibEngine::Texture::Load(std::string *fileName)
{
    TextureData *textureData = new TextureData();
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
