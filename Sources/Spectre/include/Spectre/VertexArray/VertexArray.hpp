#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Buffer/Buffer.hpp>

// TODO: Add support to multiple vertex buffers
namespace Spectre {
    class VertexArray {
        u32 m_VAO{};

        Ref<VertexBuffer> m_VBO;
        Ref<ElementBuffer> m_IBO;

    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind();
        void EnableAttribute(u32 index, i32 size, i32 offset, const void *data);

        void SetVertexBuffer(const Ref<VertexBuffer> &vbo);
        void SetElementBuffer(const Ref<ElementBuffer> &ebo);
    };
}
