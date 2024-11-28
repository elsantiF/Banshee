#include "Model.h"

namespace Banshee {
    Model::Model(Vector<Mesh> &&meshes): m_Meshes(std::move(meshes)) {}

    Transform &Model::GetTransform() {
        return m_Transform;
    }

    void Model::Draw(Shader &shader) {
        shader.SetMat4("u_MatModel", m_Transform.GetModelMatrix());
        for (Mesh &mesh: m_Meshes) {
            mesh.Draw(shader);
        }
    }
}
