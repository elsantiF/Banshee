#pragma once

#include <glad/glad.h>

#include "Core/Core.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"

// TODO: Refactor this to use Mesh and Texture instead of m_VAO and m_VBO and m_Texture
namespace Banshee {
    class Framebuffer {
        unsigned int m_Framebuffer;
        unsigned int m_Renderbuffer;
        UniquePtr<Shader> m_Shader;
        UniquePtr<VertexArray> m_VAO;
        UniquePtr<Buffer> m_VBO;
        unsigned int m_Texture;

        unsigned int m_Width;
        unsigned int m_Height;
        unsigned int m_ColorDepth;

    public:
        Framebuffer(unsigned int width, unsigned int height, unsigned int colorDepth);
        ~Framebuffer();

        void Bind();
        void Unbind();
        void Draw();
    };
}
