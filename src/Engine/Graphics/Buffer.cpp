#include "Buffer.h"

namespace BansheeEngine {
    void Buffer::Init(const BufferType bufferType) {
        m_BufferType = bufferType;
        glGenBuffers(1, &m_BufferID);
    }

    void Buffer::Destroy() const {
        glDeleteBuffers(1, &m_BufferID);
    }

    void Buffer::Bind() const {
        glBindBuffer(m_BufferType, m_BufferID);
    }

    void Buffer::Unbind() const {
        glBindBuffer(m_BufferType, 0);
    }

    void Buffer::LoadData(const GLsizeiptr size, const void *data) const {
        glBufferData(m_BufferType, size, data, GL_STATIC_DRAW);
    }
}
