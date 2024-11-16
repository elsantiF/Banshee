#include "Mesh.h"

#include <utility>

namespace BansheeEngine {
    Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices): m_Vertices{vertices},
        m_Indices{indices} {
        m_VAO.Init();
        m_VBO.Init(BufferType::VertexBuffer);
        m_EBO.Init(BufferType::ElementBuffer);

        m_VAO.Bind();

        m_VBO.Bind();
        m_VBO.LoadData(m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);

        m_EBO.Bind();
        m_EBO.LoadData(m_Indices.size() * sizeof(unsigned int), &m_Indices[0]);

        // Position Attribute
        m_VAO.EnableAttribute(0, 3, sizeof(Vertex), nullptr);

        // Normal Attribute
        m_VAO.EnableAttribute(1, 3, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));

        //UVs Attribute
        m_VAO.EnableAttribute(2, 2, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, uv)));

        m_VAO.Unbind();
    }

    void Mesh::Draw(Shader &shader) const {
        m_VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, m_Indices.size());
    }
}
