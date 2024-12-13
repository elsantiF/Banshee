export module Banshee.Components.StaticMesh;

import Poltergeist;
import Spectre;
import Banshee.Assets.Resource;
import Banshee.Components.Component;

export namespace Banshee {
    class StaticMesh : public Component {
        Vector<Spectre::Vertex> m_Vertices{};
        Vector<u32> m_Indices{};
        Vector<Resource<Spectre::Texture>> m_Textures{};
        u32 m_IndexCount{};

        Ref<Spectre::VertexArray> m_VAO{};

    public:
        StaticMesh() = default;
        StaticMesh(const Vector<Spectre::Vertex> &vertices, const Vector<u32> &indices, const Vector<Resource<Spectre::Texture>> &textures);

        void Draw(const Spectre::ShaderProgram &shader) const;

        Vector<Resource<Spectre::Texture>> &GetTextures() { return m_Textures; } // TODO: This is only for debug
    };
}
