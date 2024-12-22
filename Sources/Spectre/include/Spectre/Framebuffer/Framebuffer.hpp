#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include "Spectre/Buffer/Buffer.hpp"
#include "Spectre/Shader/Shader.hpp"
#include "Spectre/Texture/Texture.hpp"
#include "Spectre/VertexArray/VertexArray.hpp"
#include "Spectre/Renderbuffer/Renderbuffer.hpp"

// TODO: Refactor this to use Mesh instead of m_VAO and m_VBO
namespace Spectre {
    class Framebuffer {
        u32 m_Framebuffer{};
        Ref<ShaderProgram> m_Shader;
        Scope<VertexArray> m_VAO;
        Scope<Texture> m_Texture;
        Scope<Renderbuffer> m_Renderbuffer;

        u32 m_Width;
        u32 m_Height;

    public:
        Framebuffer(u32 width, u32 height);
        ~Framebuffer();

        void SetShader(const Ref<ShaderProgram> &shader);

        void Bind() const;
        void Unbind();
        void Draw() const;

        u32 GetWidth() const { return m_Width; }
        u32 GetHeight() const { return m_Height; }
    };
}
