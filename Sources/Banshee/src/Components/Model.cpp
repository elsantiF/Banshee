#include "Banshee/Components/Camera.hpp"
#include "Banshee/Components/Model.hpp"

namespace Banshee {
    Model::Model(Vector<StaticMesh> &meshes) : m_Meshes{std::move(meshes)} {}

    void Model::OnRender(Camera *camera) const {
        PROFILE_SCOPE();
        m_Shader->Bind();
        m_Shader->Set("u_MatProjection", camera->GetProjectionMatrix());
        m_Shader->Set("u_MatView", camera->GetViewMatrix());
        m_Shader->Set("u_LightPosition", glm::vec3(0.f, 0.f, 2.f)); // TODO: This is temporary
        m_Shader->Set("u_MatModel", m_Transform->GetModelMatrix());
        for (auto &mesh : m_Meshes) {
            mesh.Draw(m_Shader);
        }
    }
}
