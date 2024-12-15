module;
#include <glad/glad.h>
#include <Profiler/Profiler.hpp>

module Spectre.Buffer;

namespace Spectre {
    constexpr GLenum GetBufferType(const BufferType type) {
        switch (type) {
        case BufferType::VERTEX_BUFFER:  return GL_ARRAY_BUFFER;
        case BufferType::ELEMENT_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
        default:                         static_assert("Invalid buffer type"); return GL_INVALID_ENUM;
        }
    }

    BufferBase::BufferBase(const BufferType type) : m_BufferType{type} {
        PROFILE_GPU_ZONE();
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

    void BufferBase::Bind() const {
        PROFILE_GPU_ZONE();
        glBindBuffer(GetBufferType(m_BufferType), m_BufferID);
    }

    void BufferBase::Unbind() const {
        PROFILE_GPU_ZONE();
        glBindBuffer(GetBufferType(m_BufferType), 0);
    }

    void BufferBase::LoadData(const GLsizeiptr size, const void *data) const {
        PROFILE_GPU_ZONE();
        Bind();
        glBufferData(GetBufferType(m_BufferType), size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer() : BufferBase{BufferType::VERTEX_BUFFER} {}

    ElementBuffer::ElementBuffer() : BufferBase{BufferType::ELEMENT_BUFFER} {}
}
