#pragma once

#include <glad/glad.h>

#include "Core/Core.h"
#include "GraphicBuffer.h"

// TODO: Add support to multiple vertex buffers
namespace Banshee {
    class VertexArray {
        u32 m_VAO{};

        VertexBuffer m_VBO;
        ElementBuffer m_IBO;

    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        static void Unbind();
        static void EnableAttribute(u32 index, i32 size, i32 offset, const void *data);

        void SetVertexBuffer(const VertexBuffer &vbo);
        void SetElementBuffer(const ElementBuffer &ebo);
    };
}
