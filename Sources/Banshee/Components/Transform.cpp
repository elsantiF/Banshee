module;
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Profiler/Profiler.hpp>

module Banshee.Components.Transform;

namespace Banshee {
    glm::mat4 Transform::GetModelMatrix() {
        PROFILE_SCOPE();
        if (!this->m_IsDirty) {
            return this->m_ModelMatrix;
        }

        this->m_ModelMatrix =
            glm::translate(glm::mat4(1.0f), this->m_Position) * glm::toMat4(this->m_Rotation) * glm::scale(glm::mat4(1.0f), this->m_Scale);
        this->m_IsDirty = false;
        return this->m_ModelMatrix;
    }

    Transform &Transform::SetPosition(const glm::vec3 &position) {
        this->m_Position = position;
        this->m_IsDirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::quat &rotation) {
        this->m_Rotation = rotation;
        this->m_IsDirty = true;
        return *this;
    }

    Transform &Transform::SetScale(const glm::vec3 &scale) {
        this->m_Scale = scale;
        this->m_IsDirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::vec3 &rotation) {
        this->m_Rotation = glm::quat(glm::radians(rotation));
        this->m_IsDirty = true;
        return *this;
    }

    Transform &Transform::Translate(const glm::vec3 &translation) {
        PROFILE_SCOPE();
        this->m_Position += translation;
        this->m_IsDirty = true;
        return *this;
    }

    Transform &Transform::Scale(const glm::vec3 &scale) {
        PROFILE_SCOPE();
        this->m_Scale *= scale;
        this->m_IsDirty = true;
        return *this;
    }

    Transform &Transform::Scale(const f32 scale) { return this->Scale(glm::vec3(scale)); }

    Transform &Transform::Rotate(const glm::vec3 &rotation) {
        PROFILE_SCOPE();
        this->m_Rotation *= glm::quat(glm::radians(rotation));
        this->m_IsDirty = true;
        return *this;
    }
}
