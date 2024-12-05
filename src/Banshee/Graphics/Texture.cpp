#include "Texture.h"

namespace Banshee {
    Texture::Texture() {
        glGenTextures(1, &m_TextureID);
    }

    Texture::Texture(const TextureSpec spec): m_TextureSpec{spec} {
        glGenTextures(1, &m_TextureID);

        GLenum format;
        if (m_TextureSpec.channels == 1) {
            format = GL_RED;
        } else if (m_TextureSpec.channels == 3) {
            format = GL_RGB;
        } else if (m_TextureSpec.channels == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_TextureSpec.width, m_TextureSpec.height, 0, format, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // TODO: This doesn't make sense
        m_TextureType = "undefined";
    }

    Texture::Texture(const TextureSpec spec, const u8 *textureData): m_TextureSpec{spec} {
        glGenTextures(1, &m_TextureID);

        GLenum format;
        if (m_TextureSpec.channels == 1) {
            format = GL_RED;
        } else if (m_TextureSpec.channels == 3) {
            format = GL_RGB;
        } else if (m_TextureSpec.channels == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_TextureSpec.width, m_TextureSpec.height, 0, format, GL_UNSIGNED_BYTE, textureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

    u32 Texture::GetTextureID() const {
        return m_TextureID;
    }
}
