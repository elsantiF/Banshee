module;
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <tracy/Tracy.hpp>

module Banshee.Components.Transform;

namespace Banshee {
    glm::mat4 Transform::GetModelMatrix() {
        ZoneScoped;
        if (!this->m_Dirty) {
            return this->m_ModelMatrix;
        }

        this->m_ModelMatrix =
            glm::translate(glm::mat4(1.0f), this->m_Position) * glm::toMat4(this->m_Rotation) * glm::scale(glm::mat4(1.0f), this->m_Scale);
        this->m_Dirty = false;
        return this->m_ModelMatrix;
    }

    Transform &Transform::SetPosition(const glm::vec3 &position) {
        this->m_Position = position;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::quat &rotation) {
        this->m_Rotation = rotation;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::SetScale(const glm::vec3 &scale) {
        this->m_Scale = scale;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::vec3 &rotation) {
        this->m_Rotation = glm::quat(glm::radians(rotation));
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::Translate(const glm::vec3 &translation) {
        ZoneScoped;
        this->m_Position += translation;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::Scale(const glm::vec3 &scale) {
        ZoneScoped;
        this->m_Scale *= scale;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::Scale(const f32 scale) { return this->Scale(glm::vec3(scale)); }

    Transform &Transform::Rotate(const glm::vec3 &rotation) {
        ZoneScoped;
        this->m_Rotation *= glm::quat(glm::radians(rotation));
        this->m_Dirty = true;
        return *this;
    }
}
