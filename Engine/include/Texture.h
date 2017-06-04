#pragma once

#include <string>

#include "GL/gl3w.h"

#include "Logger.h"
#include "File.h"

namespace GibEngine
{
    enum class TextureType
    {
        DIFFUSE,
        SPECULAR,
        HEIGHT,
        NORMAL
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
        Texture(TextureType type, std::string *fileName);
        ~Texture();

		static const char* TextureTypeStrings[4];

        GLuint GetTextureId();
    };
}