#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "Core/Core.h"

namespace BansheeEngine {
    class Texture {
        unsigned int m_TextureID;
        std::string m_TextureType;
        std::string m_FilePath;

    public:
        explicit Texture(const std::string &path);
        ~Texture();

        void Bind() const;
        static void Unbind();

        [[nodiscard]] std::string GetType() const;
        void SetType(const std::string &type);
    };
}
