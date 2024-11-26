#include "Model.h"

namespace Banshee {
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
