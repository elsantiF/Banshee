#include <glad/glad.h>
#include <Poltergeist/Profiler/Profiler.hpp>
#include "Spectre/VertexArray/VertexArray.hpp"

namespace Spectre {
    VertexArray::VertexArray() {
        PROFILE_GPU_ZONE();
        glGenVertexArrays(1, &m_VAO);
    }

    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_VAO); }

    void VertexArray::Bind() const {
        PROFILE_GPU_ZONE();
        glBindVertexArray(m_VAO);
    }

    void VertexArray::Unbind() {
        PROFILE_GPU_ZONE();
        glBindVertexArray(0);
    }

    void VertexArray::EnableAttribute(const u32 index, const i32 size, const i32 offset, const void *data) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data);
    }

    void VertexArray::SetVertexBuffer(const Ref<VertexBuffer> &vbo) {
        Bind();
        vbo->Bind();
        m_VBO = vbo;
        Unbind();
    }

    void VertexArray::SetElementBuffer(const Ref<ElementBuffer> &ebo) {
        Bind();
        ebo->Bind();
        m_IBO = ebo;
        Unbind();
    }
}
