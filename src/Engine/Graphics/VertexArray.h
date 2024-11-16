#pragma once

#include <glad/glad.h>

namespace BansheeEngine {
    class VertexArray {
        unsigned int m_VAO{};

    public:
        void Init();
        void Destroy() const;
        void Bind() const;
        static void Unbind();
        static void EnableAttribute(unsigned int index, int size, int offset, const void *data);
    };
}
