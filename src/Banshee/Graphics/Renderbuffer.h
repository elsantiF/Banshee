#pragma once

#include <glad/glad.h>

#include "Core/Core.h"

// TODO: Add support to other formats rather than just GL_DEPTH24_STENCIL8
namespace Banshee {
    class Renderbuffer {
        u32 m_Renderbuffer{};
        u32 m_Width;
        u32 m_Height;

    public:
        Renderbuffer(u32 width, u32 height);
        ~Renderbuffer();

        void Bind() const;
        void Unbind();

        [[nodiscard]] u32 GetID() const;
    };
}
