#pragma once

#include "Core/Core.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

namespace BansheeEngine {
    class Mesh {
        Vector<Vertex> m_Vertices;
        Vector<unsigned int> m_Indices;

        UniquePtr<VertexArray> m_VAO;
        UniquePtr<Buffer> m_VBO;
        UniquePtr<Buffer> m_EBO;

    public:
        Mesh() = delete;
        Mesh(const Vector<Vertex> &vertices, const Vector<unsigned int> &indices);
        void Draw(Shader &shader) const;
    };
}
