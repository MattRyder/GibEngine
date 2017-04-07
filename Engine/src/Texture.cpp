#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb\stb_image.h"

const char* GibEngine::Texture::TextureTypeStrings[4] = {
    "diffuse", "specular", "height", "normal"
};

GibEngine::Texture::Texture(GibEngine::TextureType type, std::string *fileName)
{
    this->type = type;
    this->fileName = fileName;

    glGenTextures(1, &textureId);

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
        Logger::Instance->warn("Texture file `{}` is not sized as a power of two!", fileName->c_str());
    }

    return textureData;
}
