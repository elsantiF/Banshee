export module Banshee.Components.Model;

import Poltergeist;
import Spectre.Shader;
import Banshee.Components.Component;
import Banshee.Components.StaticMesh;
import Banshee.Components.Transform;

export namespace Banshee {
    class Model : public Component {
        Vector<StaticMesh> m_Meshes{};
        Transform m_Transform{};

    public:
        Model() = default;
        explicit Model(Vector<StaticMesh> &meshes);

        Transform &Transform() { return m_Transform; }

        void Draw(const Spectre::ShaderProgram &shader);

        Vector<StaticMesh> &GetMeshes() { return m_Meshes; } // TODO: This is only for debug
    };
}
