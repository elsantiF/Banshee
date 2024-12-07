module;
#include <memory>

module Banshee.Components.Model;

namespace Banshee {
    Model::Model(Vector<StaticMesh> &&meshes): m_Meshes{std::move(meshes)} {}

    Transform &Model::GetTransform() {
        return m_Transform;
    }

    void Model::Draw(const ShaderProgram &shader) {
        shader.SetMat4("u_MatModel", m_Transform.GetModelMatrix());
        for (auto &mesh: m_Meshes) {
            mesh.Draw(shader);
        }
    }
}
