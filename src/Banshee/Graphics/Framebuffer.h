#pragma once

#include <glad/glad.h>

#include "Core/Core.h"
#include "GraphicBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Renderbuffer.h"

// TODO: Refactor this to use Mesh instead of m_VAO and m_VBO
namespace Banshee {
    class Framebuffer {
        u32 m_Framebuffer{};
        UniquePtr<ShaderProgram> m_Shader;
        UniquePtr<VertexArray> m_VAO;
        UniquePtr<VertexBuffer> m_VBO;
        UniquePtr<Texture> m_Texture;
        UniquePtr<Renderbuffer> m_Renderbuffer;

        u32 m_Width;
        u32 m_Height;

    public:
        Framebuffer(u32 width, u32 height);
        ~Framebuffer();

        void Bind() const;
        static void Unbind();
        void Draw() const;
    };
}
