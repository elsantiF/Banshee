#pragma once

#include <glad/glad.h>
#include <Poltergeist/Poltergeist.hpp>

namespace Spectre {
    enum class BufferType { VERTEX_BUFFER, ELEMENT_BUFFER };

    class BufferBase {
        u32 m_BufferID{};
        BufferType m_BufferType;

    public:
        explicit BufferBase(BufferType type);
        ~BufferBase();

        [[nodiscard]] u32 GetID() const;
        [[nodiscard]] BufferType GetType() const;

        void Bind() const;
        void Unbind() const;
        void LoadData(GLsizeiptr size, const void *data) const;
    };

    class VertexBuffer final : public BufferBase {
    public:
        VertexBuffer();
        ~VertexBuffer() = default;
    };

    class ElementBuffer final : public BufferBase {
    public:
        ElementBuffer();
        ~ElementBuffer() = default;
    };
}
