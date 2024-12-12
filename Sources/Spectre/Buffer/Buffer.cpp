module;
#include <glad/glad.h>
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>

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
        ZoneScoped;
        TracyGpuZone("BufferBase::BufferBase");
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
        ZoneScoped;
        TracyGpuZone("BufferBase::Bind");
        glBindBuffer(GetBufferType(m_BufferType), m_BufferID);
    }

    void BufferBase::Unbind() const {
        ZoneScoped;
        TracyGpuZone("BufferBase::Unbind");
        glBindBuffer(GetBufferType(m_BufferType), 0);
    }

    void BufferBase::LoadData(const GLsizeiptr size, const void *data) const {
        ZoneScoped;
        TracyGpuZone("BufferBase::LoadData");
        Bind();
        glBufferData(GetBufferType(m_BufferType), size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer() : BufferBase{BufferType::VERTEX_BUFFER} {}

    ElementBuffer::ElementBuffer() : BufferBase{BufferType::ELEMENT_BUFFER} {}
}
