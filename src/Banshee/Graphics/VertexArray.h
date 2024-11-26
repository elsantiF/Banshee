#pragma once

#include <glad/glad.h>

namespace Banshee {
    class VertexArray {
        unsigned int m_VAO{};

    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        static void Unbind();
        static void EnableAttribute(unsigned int index, int size, int offset, const void *data);
    };
}
