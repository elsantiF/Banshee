#pragma once

#include <glad/glad.h>

#include "Core/Core.h"
#include "GraphicBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

// TODO: Refactor this to use Mesh and Texture instead of m_VAO and m_VBO and m_Texture
namespace Banshee {
    class Framebuffer {
        u32 m_Framebuffer;
        u32 m_Renderbuffer;
        UniquePtr<ShaderProgram> m_Shader;
        UniquePtr<VertexArray> m_VAO;
        UniquePtr<VertexBuffer> m_VBO;
        u32 m_Texture;

        u32 m_Width;
        u32 m_Height;
        u32 m_ColorDepth;

    public:
        Framebuffer(u32 width, u32 height, u32 colorDepth);
        ~Framebuffer();

        void Bind() const;
        static void Unbind();
        void Draw() const;
    };
}
