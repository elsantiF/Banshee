module;
#include <memory>
#include <Profiler/Profiler.hpp>
#include <vector>

module Banshee.Components.Model;

namespace Banshee {
    Model::Model(Vector<StaticMesh> &meshes) : m_Meshes{std::move(meshes)} {}

    void Model::Draw(const Spectre::ShaderProgram &shader) {
        PROFILE_SCOPE();
        shader.Set("u_MatModel", m_Transform.GetModelMatrix());
        for (auto &mesh : m_Meshes) {
            mesh.Draw(shader);
        }
    }
}
