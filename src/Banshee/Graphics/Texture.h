#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "Core/Core.h"

// TODO: Do a big refactor on this class, consider create a TextureLoader class
namespace Banshee {
    class Texture {
        u32 m_TextureID{};
        String m_TextureType;
        String m_FilePath;

        u32 m_Width{};
        u32 m_Height{};
        u32 m_Channels{};

    public:
        Texture() = delete;
        explicit Texture(u32 width, u32 height, u32 channels);
        explicit Texture(const String &texturePath);
        ~Texture();

        void Bind() const;
        static void Unbind();

        [[nodiscard]] String GetType() const;
        void SetType(const String &type);

        [[nodiscard]] String GetFilePath() const;
    };
}
