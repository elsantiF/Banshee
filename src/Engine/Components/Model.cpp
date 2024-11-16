#include "Model.h"

namespace BansheeEngine {
    Model::Model(std::vector<Mesh> &&meshes) : m_Meshes(std::move(meshes)) {
        CalculateModelMatrix();
    }

    void Model::CalculateModelMatrix() {
        m_ModelMatrix = glm::identity<glm::mat4>();
        m_ModelMatrix = glm::translate(m_ModelMatrix, m_Transform.translation);
        m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        m_ModelMatrix = glm::scale(m_ModelMatrix, m_Transform.scale);
    }

    void Model::Translate(const glm::vec3 &translation) {
        m_Transform.translation = translation;
        CalculateModelMatrix();
    }

    void Model::Rotate(const glm::vec3 &axis, const float angle) {
        m_Transform.rotation = axis * angle;
        CalculateModelMatrix();
    }

    void Model::Scale(const glm::vec3 &scale) {
        m_Transform.scale = scale;
        CalculateModelMatrix();
    }

    void Model::Scale(const float scale) {
        m_Transform.scale = glm::vec3(scale);
        CalculateModelMatrix();
    }

    glm::mat4 Model::GetModelMatrix() const {
        return m_ModelMatrix;
    }

    void Model::Draw(Shader &shader) {
        shader.SetMat4Uniform("u_MatModel", m_ModelMatrix);
        for (Mesh &mesh: m_Meshes) {
            mesh.Draw(shader);
        }
    }
}
