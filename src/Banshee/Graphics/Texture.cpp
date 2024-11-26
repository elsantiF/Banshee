#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

namespace Banshee {
    Texture::Texture(const String &texturePath): m_FilePath{texturePath} {
        glGenTextures(1, &m_TextureID); // Can textureID be 0?

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
        if (!data) {
            Logger::CRITICAL("Error loading texture: " + texturePath);
        }

        GLenum format;
        if (channels == 1) {
            format = GL_RED;
        } else if (channels == 3) {
            format = GL_RGB;
        } else if (channels == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }

    Texture::~Texture() {
        // TODO: Fix this, this is called from ModelLoader and deletes the texture
        // glDeleteTextures(1, &m_TextureID);
    }

    void Texture::Bind() const {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    String Texture::GetType() const {
        return m_TextureType;
    }

    void Texture::SetType(const String &type) {
        m_TextureType = type;
    }

    String Texture::GetFilePath() const {
        return m_FilePath;
    }
}
