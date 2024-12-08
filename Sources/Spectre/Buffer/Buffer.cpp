module;
#include <glad/glad.h>

module Spectre.Buffer;

namespace Spectre {
    BufferBase::BufferBase(const BufferType type) : m_BufferType{type} {
        glGenBuffers(1, &m_BufferID);
        Logger::PANIC(m_BufferID == 0, "Can't create buffer");
    }

    BufferBase::~BufferBase() {
        if (!m_BufferID) {
            Logger::ERROR("Trying to delete a non-existent buffer");
        }

        glDeleteBuffers(1, &m_BufferID);
    }

    u32 BufferBase::GetID() const { return m_BufferID; }

    BufferType BufferBase::GetType() const { return m_BufferType; }

    void BufferBase::Bind() const { glBindBuffer(m_BufferType, m_BufferID); }

    void BufferBase::Unbind() const { glBindBuffer(m_BufferType, 0); }

    void BufferBase::LoadData(const GLsizeiptr size, const void *data) const {
        Bind();
        glBufferData(m_BufferType, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer() : BufferBase{BufferType::VERTEX_BUFFER} {}

    ElementBuffer::ElementBuffer() : BufferBase{BufferType::ELEMENT_BUFFER} {}
}
