#pragma once

#include <vector>

#include "Vertex.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

class Mesh {
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;

    VertexArray m_VAO;
    Buffer m_VBO;
    Buffer m_EBO;

public:
    Mesh() = default;
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
    void Draw(Shader &shader) const;
};
