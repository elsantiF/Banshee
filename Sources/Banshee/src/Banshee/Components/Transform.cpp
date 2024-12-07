#include "Banshee/Components/Transform.h"

namespace Banshee {
    glm::mat4 Transform::GetModelMatrix() {
        if (!this->m_Dirty) {
            return this->m_ModelMatrix;
        }

        this->m_ModelMatrix = glm::identity<glm::mat4>();
        this->m_ModelMatrix = glm::translate(this->m_ModelMatrix, this->m_Position);
        this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        this->m_ModelMatrix = glm::rotate(this->m_ModelMatrix, glm::radians(this->m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        this->m_ModelMatrix = glm::scale(this->m_ModelMatrix, this->m_Scale);
        this->m_Dirty = false;
        return this->m_ModelMatrix;
    }

    Transform &Transform::SetPosition(const glm::vec3 &position) {
        this->m_Position = position;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::SetRotation(const glm::vec3 &rotation) {
        this->m_Rotation = rotation;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::SetScale(const glm::vec3 &scale) {
        this->m_Scale = scale;
        this->m_Dirty = true;
        return *this;
    }

    glm::vec3 Transform::GetPosition() const {
        return this->m_Position;
    }

    glm::vec3 Transform::GetRotation() const {
        return this->m_Rotation;
    }

    glm::vec3 Transform::GetScale() const {
        return this->m_Scale;
    }

    Transform &Transform::Translate(const glm::vec3 &translation) {
        this->m_Position += translation;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::TranslateX(const f32 x) {
        return this->Translate(glm::vec3(x, 0.0f, 0.0f));
    }

    Transform &Transform::TranslateY(const f32 y) {
        return this->Translate(glm::vec3(0.0f, y, 0.0f));
    }

    Transform &Transform::TranslateZ(const f32 z) {
        return this->Translate(glm::vec3(0.0f, 0.0f, z));
    }

    Transform &Transform::Scale(const glm::vec3 &scale) {
        this->m_Scale *= scale;
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::Scale(const f32 scale) {
        return this->Scale(glm::vec3(scale));
    }

    Transform &Transform::ScaleX(const f32 x) {
        return this->Scale(glm::vec3(x, 1.0f, 1.0f));
    }

    Transform &Transform::ScaleY(const f32 y) {
        return this->Scale(glm::vec3(1.0f, y, 1.0f));
    }

    Transform &Transform::ScaleZ(const f32 z) {
        return this->Scale(glm::vec3(1.0f, 1.0f, z));
    }

    Transform &Transform::Rotate(const glm::vec3 &rotation) {
        this->m_Rotation += rotation;
        this->m_Rotation.x = glm::mod(this->m_Rotation.x, 360.0f);
        this->m_Rotation.y = glm::mod(this->m_Rotation.y, 360.0f);
        this->m_Rotation.z = glm::mod(this->m_Rotation.z, 360.0f);
        this->m_Dirty = true;
        return *this;
    }

    Transform &Transform::RotateX(const f32 x) {
        return this->Rotate(glm::vec3(x, 0.0f, 0.0f));
    }

    Transform &Transform::RotateY(const f32 y) {
        return this->Rotate(glm::vec3(0.0f, y, 0.0f));
    }

    Transform &Transform::RotateZ(const f32 z) {
        return this->Rotate(glm::vec3(0.0f, 0.0f, z));
    }
}
