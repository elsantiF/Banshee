#include "Framebuffer.h"

float vertices[] = {
    //position     //texture
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

namespace Banshee {
    Framebuffer::Framebuffer(unsigned int width, unsigned int height, unsigned int colorDepth) : m_Width(width), m_Height(height), m_ColorDepth(colorDepth) {
        m_Shader = MakeUnique<Shader>("shaders/framebuffer");
        m_VAO = MakeUnique<VertexArray>();
        m_VAO->Bind();

        m_VBO = MakeUnique<Buffer>(BufferType::VertexBuffer);
        m_VBO->Bind();
        m_VBO->LoadData(sizeof(vertices), vertices);

        m_VAO->EnableAttribute(0, 2, 4 * sizeof(float), nullptr);
        m_VAO->EnableAttribute(1, 2, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));

        glGenFramebuffers(1, &m_Framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

        glGenTextures(1, &m_Texture);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

        glGenRenderbuffers(1, &m_Renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            Logger::ERROR("Framebuffer is not complete!");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &m_Framebuffer);
        glDeleteTextures(1, &m_Texture);
        glDeleteRenderbuffers(1, &m_Renderbuffer);
    }

    void Framebuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
        glViewport(0, 0, m_Width, m_Height);
    }

    void Framebuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Draw() {
        m_Shader->Bind();
        m_VAO->Bind();
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}