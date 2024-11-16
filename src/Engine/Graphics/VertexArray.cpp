#include "VertexArray.h"

namespace BansheeEngine {
    void VertexArray::Init() {
        glGenVertexArrays(1, &m_VAO);
    }

    void VertexArray::Destroy() const {
        glDeleteVertexArrays(1, &m_VAO);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(m_VAO);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::EnableAttribute(const unsigned int index, const int size,
                                      const int offset, const void *data) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data);
    }
}
