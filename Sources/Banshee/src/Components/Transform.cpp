#include "Banshee/Components/Transform.hpp"

namespace Banshee {
    void Transform::UpdateMatrices() {
        if (!m_IsDirty) {
            return;
        }

        m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(m_Rotation) * glm::scale(glm::mat4(1.0f), m_Scale);
        m_InverseModelMatrix = glm::inverse(m_ModelMatrix);
        m_IsDirty = false;
    }

    glm::mat4 Transform::GetModelMatrix() {
        PROFILE_SCOPE();
        UpdateMatrices();
        return m_ModelMatrix;
    }

    glm::mat4 Transform::GetInverseModelMatrix() {
        PROFILE_SCOPE();
        UpdateMatrices();
        return m_InverseModelMatrix;
    }

    Transform &Transform::SetPosition(const glm::vec3 &position) {
        m_Position = position;
        m_IsDirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::quat &rotation) {
        m_Rotation = rotation;
        m_IsDirty = true;
        return *this;
    }

    Transform &Transform::SetScale(const glm::vec3 &scale) {
        m_Scale = scale;
        m_IsDirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::vec3 &rotation) {
        m_Rotation = glm::quat(glm::radians(rotation));
        m_IsDirty = true;
        return *this;
    }

    Transform &Transform::Translate(const glm::vec3 &translation) {
        PROFILE_SCOPE();
        m_Position += translation;
        m_IsDirty = true;
        return *this;
    }

    Transform &Transform::Scale(const glm::vec3 &scale) {
        PROFILE_SCOPE();
        m_Scale *= scale;
        m_IsDirty = true;
        return *this;
    }

    Transform &Transform::Scale(const f32 scale) { return Scale(glm::vec3(scale)); }

    Transform &Transform::Rotate(const glm::vec3 &rotation) {
        PROFILE_SCOPE();
        m_Rotation *= glm::quat(glm::radians(rotation));
        m_IsDirty = true;
        return *this;
    }
}
