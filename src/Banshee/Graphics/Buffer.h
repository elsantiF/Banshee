#pragma once

#include <glad/glad.h>

#include "Core/Core.h"

namespace Banshee {
    enum BufferType {
        VertexBuffer = GL_ARRAY_BUFFER,
        ElementBuffer = GL_ELEMENT_ARRAY_BUFFER
    };

    class Buffer {
        u32 m_BufferID{};
        BufferType m_BufferType{};

    public:
        Buffer() = delete;
        explicit Buffer(BufferType bufferType);
        ~Buffer();

        void Bind() const;
        void Unbind() const;
        void LoadData(GLsizeiptr size, const void *data) const;
    };
}
