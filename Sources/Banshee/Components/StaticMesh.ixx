module;
#include <glad/glad.h>

export module Banshee.Components.StaticMesh;

import Poltergeist;
import Spectre;
import Banshee.Assets.Resource;

export namespace Banshee {
    class StaticMesh {
        Vector<Spectre::Vertex> m_Vertices;
        Vector<u32> m_Indices;
        Vector<Resource<Spectre::Texture>> m_Textures;
        u32 m_IndexCount{};

        Scope<Spectre::VertexArray> m_VAO;

    public:
        StaticMesh() = default;
        StaticMesh(const Vector<Spectre::Vertex> &vertices, const Vector<u32> &indices, const Vector<Resource<Spectre::Texture>> &textures);
        void Draw(const Spectre::ShaderProgram &shader) const;

        Vector<Resource<Spectre::Texture>> &GetTextures() { return m_Textures; } // TODO: This is only for debug
    };
}
