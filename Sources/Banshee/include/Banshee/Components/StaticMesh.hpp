#pragma once

#include <Poltergeist/Poltergeist.hpp>
#include <Spectre/Spectre.hpp>
#include "ComponentBase.hpp"

namespace Banshee {
    class StaticMesh {
        Vector<Spectre::Vertex> m_Vertices{};
        Vector<u32> m_Indices{};
        Ref<Spectre::Texture> m_DiffuseTexture{};
        Ref<Spectre::Texture> m_NormalTexture{};

        u32 m_IndexCount{};

        Ref<Spectre::VertexArray> m_VAO{};

    public:
        StaticMesh() = default;
        StaticMesh(const Vector<Spectre::Vertex> &vertices, const Vector<u32> &indices, const Ref<Spectre::Texture> &diffuseTexture,
                   const Ref<Spectre::Texture> &normalTexture);

        void Draw(const Ref<Spectre::ShaderProgram> &shader) const;
    };
}
