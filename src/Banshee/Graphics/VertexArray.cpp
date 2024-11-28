#include "VertexArray.h"

namespace Banshee {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_VAO);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_VAO);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(m_VAO);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::EnableAttribute(const u32 index, const i32 size, const i32 offset, const void *data) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data);
    }
}
