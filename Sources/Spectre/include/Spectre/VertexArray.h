#pragma once

#include <glad/glad.h>
#include <Poltergeist/Poltergeist.h>

#include "GraphicBuffer.h"

// TODO: Add support to multiple vertex buffers
namespace Spectre {
    using namespace Poltergeist; // TODO: This is temporary

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
