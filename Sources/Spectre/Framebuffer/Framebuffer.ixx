module;
#include <glad/glad.h>

export module Spectre.Framebuffer;

import Poltergeist;
import Spectre.Buffer;
import Spectre.Shader;
import Spectre.Texture;
import Spectre.VertexArray;
import Spectre.Renderbuffer;

// TODO: Refactor this to use Mesh instead of m_VAO and m_VBO
export namespace Spectre {
    class Framebuffer {
        u32 m_Framebuffer{};
        Ref<ShaderProgram> m_Shader;
        UniquePtr<VertexArray> m_VAO;
        UniquePtr<Texture> m_Texture;
        UniquePtr<Renderbuffer> m_Renderbuffer;

        u32 m_Width;
        u32 m_Height;

    public:
        Framebuffer(u32 width, u32 height);
        ~Framebuffer();

        void SetShader(const Ref<ShaderProgram> &shader);

        void Bind() const;
        void Unbind();
        void Draw() const;
    };
}
