#include "Mesh.h"

namespace Banshee {
    Mesh::Mesh(const Vector<Vertex> &vertices, const Vector<u32> &indices, const Vector<Texture> &textures): m_Vertices{vertices},
        m_Indices{indices}, m_Textures{textures} {
        // TODO: All this code is temporary, it will be moved to another place
        m_IndexCount = m_Indices.size();

        m_VAO = MakeUnique<VertexArray>();
        m_VBO = MakeUnique<Buffer>(BufferType::VertexBuffer);
        m_EBO = MakeUnique<Buffer>(BufferType::ElementBuffer);

        m_VAO->Bind();

        m_VBO->Bind();
        m_VBO->LoadData(m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);

        m_EBO->Bind();
        m_EBO->LoadData(m_Indices.size() * sizeof(u32), &m_Indices[0]);

        // Position Attribute
        m_VAO->EnableAttribute(0, 3, sizeof(Vertex), nullptr);

        // Normal Attribute
        m_VAO->EnableAttribute(1, 3, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));

        //UVs Attribute
        m_VAO->EnableAttribute(2, 2, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texCoords)));

        // Tangent Attribute
        m_VAO->EnableAttribute(3, 3, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, tangent)));

        // Bitangent Attribute
        m_VAO->EnableAttribute(4, 3, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, bitangent)));

        m_VAO->Unbind();
    }

    void Mesh::Draw(const Shader &shader) const {
        // TODO: Same as above, this will be moved to another place
        u32 diffuseNr = 1;
        u32 specularNr = 1;
        u32 normalNr = 1;
        u32 heightNr = 1;

        for (u32 i = 0; i < m_Textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            String number;
            const String name = m_Textures[i].GetType();
            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
            } else if (name == "texture_specular") {
                number = std::to_string(specularNr++);
            } else if (name == "texture_normal") {
                number = std::to_string(normalNr++);
            } else if (name == "texture_height") {
                number = std::to_string(heightNr++);
            }

            shader.SetInt(name + number, i);
            m_Textures[i].Bind();
        }

        m_VAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, m_IndexCount);
        m_VAO->Unbind();
        glActiveTexture(GL_TEXTURE0);
    }
}
