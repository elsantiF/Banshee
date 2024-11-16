#pragma once

#include <glad/glad.h>

namespace BansheeEngine {
    enum BufferType {
        VertexBuffer = GL_ARRAY_BUFFER,
        ElementBuffer = GL_ELEMENT_ARRAY_BUFFER
    };

    class Buffer {
        unsigned int m_BufferID{};
        BufferType m_BufferType{};

    public:
        void Init(BufferType bufferType);
        void Destroy() const;
        void Bind() const;
        void Unbind() const;
        void LoadData(GLsizeiptr size, const void *data) const;
    };
}
