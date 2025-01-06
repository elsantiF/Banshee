#include <glad/glad.h>
#include <Poltergeist/Profiler/Profiler.hpp>
#include "Spectre/Texture/Texture.hpp"

namespace Spectre {
    Texture::Texture() { glGenTextures(1, &m_TextureID); }

    Texture::Texture(const TextureSpec spec) : m_TextureSpec{spec} {
        PROFILE_GPU_ZONE();
        glGenTextures(1, &m_TextureID);

        GLenum format = GL_RED;
        if (m_TextureSpec.channels == 1) {
            format = GL_RED;
        } else if (m_TextureSpec.channels == 3) {
            format = GL_RGB;
        } else if (m_TextureSpec.channels == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_TextureSpec.width, m_TextureSpec.height, 0, format, GL_UNSIGNED_BYTE, nullptr);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::Texture(const TextureSpec spec, const u8 *textureData) : m_TextureSpec{spec} {
        PROFILE_GPU_ZONE();
        glGenTextures(1, &m_TextureID);

        GLenum format = GL_RED;
        if (m_TextureSpec.channels == 1) {
            format = GL_RED;
        } else if (m_TextureSpec.channels == 3) {
            format = GL_RGB;
        } else if (m_TextureSpec.channels == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_TextureSpec.width, m_TextureSpec.height, 0, format, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::~Texture() { glDeleteTextures(1, &m_TextureID); }

    void Texture::Bind() const {
        PROFILE_GPU_ZONE();
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture::Unbind() {
        PROFILE_GPU_ZONE();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    u32 Texture::GetTextureID() const { return m_TextureID; }
}
