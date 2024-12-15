module;
#include <glad/glad.h>
#include <Profiler/Profiler.hpp>

module Spectre.Renderbuffer;

namespace Spectre {
    Renderbuffer::Renderbuffer(const u32 width, const u32 height) : m_Width{width}, m_Height{height} {
        PROFILE_GPU_ZONE();
        glGenRenderbuffers(1, &m_Renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    }

    Renderbuffer::~Renderbuffer() { glDeleteRenderbuffers(1, &m_Renderbuffer); }

    void Renderbuffer::Bind() const {
        PROFILE_GPU_ZONE();
        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
    }

    void Renderbuffer::Unbind() {
        PROFILE_GPU_ZONE();
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    u32 Renderbuffer::GetID() const { return m_Renderbuffer; }
}
