#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "Core/Core.h"

namespace Banshee {
    class Texture {
        u32 m_TextureID;
        String m_TextureType;
        String m_FilePath;

    public:
        Texture() = default;
        explicit Texture(const String &texturePath);
        ~Texture();

        void Bind() const;
        static void Unbind();

        [[nodiscard]] String GetType() const;
        void SetType(const String &type);

        String GetFilePath() const;
    };
}
