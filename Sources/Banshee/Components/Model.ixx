export module Banshee.Components.Model;

import Poltergeist;
import Spectre.Shader;
import Banshee.Components.Transform;
import Banshee.Components.StaticMesh;

export namespace Banshee {
    class Model {
        Vector<StaticMesh> m_Meshes;
        Transform m_Transform;

        void CalculateModelMatrix();

    public:
        Model() = default;
        explicit Model(Vector<StaticMesh> &&meshes);

        Transform &GetTransform();

        void Draw(const ShaderProgram &shader);

        Vector<StaticMesh> &GetMeshes() { return m_Meshes; } // TODO: This is only for debug
    };
}
