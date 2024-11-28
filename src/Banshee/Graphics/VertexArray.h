#pragma once

#include <glad/glad.h>

#include "Core/Core.h"

namespace Banshee {
    class VertexArray {
        u32 m_VAO{};

    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        static void Unbind();
        static void EnableAttribute(u32 index, i32 size, i32 offset, const void *data);
    };
}
