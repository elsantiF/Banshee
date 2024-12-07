#include "Spectre/Framebuffer.h"

// TODO: Move this to a separate file
float vertices[] = {
    //position     //texture
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

namespace Spectre {
    Framebuffer::Framebuffer(const u32 width, const u32 height) : m_Width{width}, m_Height{height} {
        m_VAO = MakeUnique<VertexArray>();

        const auto m_VBO = MakeRef<VertexBuffer>();
        m_VBO->LoadData(sizeof(vertices), vertices);
        m_VAO->SetVertexBuffer(m_VBO);

        m_VAO->Bind();
        m_VAO->EnableAttribute(0, 2, 4 * sizeof(float), nullptr);
        m_VAO->EnableAttribute(1, 2, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));

        glGenFramebuffers(1, &m_Framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

        m_Texture = MakeUnique<Texture>(TextureSpec{width, height, 3});
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->GetTextureID(), 0);

        m_Renderbuffer = MakeUnique<Renderbuffer>(m_Width, m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer->GetID());

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            Logger::ERROR("Framebuffer is not complete!");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &m_Framebuffer);
    }

    void Framebuffer::SetShader(const Ref<ShaderProgram> &shader) {
        m_Shader = shader;
    }

    void Framebuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
        glViewport(0, 0, m_Width, m_Height);
    }

    void Framebuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Draw() const {
        m_Shader->Bind();
        m_VAO->Bind();
        m_Texture->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}