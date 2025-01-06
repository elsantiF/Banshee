#pragma once

#include <Poltergeist/Poltergeist.hpp>

namespace Spectre {
    struct TextureSpec {
        u32 width = 0;
        u32 height = 0;
        u32 channels = 0;
    };

    class Texture {
        u32 m_TextureID{};
        TextureSpec m_TextureSpec;

    public:
        Texture();
        explicit Texture(TextureSpec spec);
        explicit Texture(TextureSpec spec, const u8 *textureData);
        ~Texture();

        void Bind() const;
        void Unbind();

        [[nodiscard]] u32 GetTextureID() const;
    };
}
