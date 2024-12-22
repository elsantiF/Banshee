#include "Banshee/Components/StaticMesh.hpp"

namespace Banshee {
    StaticMesh::StaticMesh(const Vector<Spectre::Vertex> &vertices, const Vector<u32> &indices, const Vector<Ref<Spectre::Texture>> &textures)
        : m_Vertices{vertices}, m_Indices{indices}, m_Textures{textures} {
        PROFILE_GPU_ZONE();
        // TODO: All this code is temporary, it will be moved to another place
        m_IndexCount = m_Indices.size();

        m_VAO = MakeRef<Spectre::VertexArray>();

        const auto m_VBO = MakeRef<Spectre::VertexBuffer>();
        m_VBO->LoadData(m_Vertices.size() * sizeof(Spectre::Vertex), &m_Vertices[0]);
        m_VAO->SetVertexBuffer(m_VBO);

        const auto m_EBO = MakeRef<Spectre::ElementBuffer>();
        m_EBO->LoadData(m_Indices.size() * sizeof(u32), &m_Indices[0]);
        m_VAO->SetElementBuffer(m_EBO);

        m_VAO->Bind();
        // Position Attribute
        m_VAO->EnableAttribute(0, 3, sizeof(Spectre::Vertex), nullptr);

        // Normal Attribute
        m_VAO->EnableAttribute(1, 3, sizeof(Spectre::Vertex), reinterpret_cast<void *>(offsetof(Spectre::Vertex, normal)));

        // UVs Attribute
        m_VAO->EnableAttribute(2, 2, sizeof(Spectre::Vertex), reinterpret_cast<void *>(offsetof(Spectre::Vertex, texCoords)));

        // Tangent Attribute
        m_VAO->EnableAttribute(3, 3, sizeof(Spectre::Vertex), reinterpret_cast<void *>(offsetof(Spectre::Vertex, tangent)));

        // Bitangent Attribute
        m_VAO->EnableAttribute(4, 3, sizeof(Spectre::Vertex), reinterpret_cast<void *>(offsetof(Spectre::Vertex, bitangent)));

        m_VAO->Unbind();
    }

    void StaticMesh::Draw(const Ref<Spectre::ShaderProgram> &shader) const {
        PROFILE_GPU_ZONE();
        // TODO: Same as above, this will be moved to another place
        u32 diffuseNr = 1;
        u32 specularNr = 1;
        u32 normalNr = 1;
        u32 heightNr = 1;

        // TODO: Please, refactor this, is a mess and extremely slow
        for (u32 i = 0; i < m_Textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            String number;
            const String name = m_Textures[i]->GetType();
            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
            } else if (name == "texture_specular") {
                number = std::to_string(specularNr++);
            } else if (name == "texture_normal") {
                number = std::to_string(normalNr++);
            } else if (name == "texture_height") {
                number = std::to_string(heightNr++);
            }

            shader->Set(name + number, i);
            m_Textures[i]->Bind();
        }

        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
        m_VAO->Unbind();
        glActiveTexture(GL_TEXTURE0);
    }
}
