module;
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

export module Banshee.Components.Transform;

import Poltergeist;

export namespace Banshee {
    class Transform {
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 m_Scale = glm::vec3(1.0f);

        glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
        bool m_IsDirty = true;

    public:
        [[nodiscard]] glm::mat4 GetModelMatrix();

        Transform &SetPosition(const glm::vec3 &position);
        Transform &SetRotation(const glm::quat &rotation);
        Transform &SetScale(const glm::vec3 &scale);

        [[nodiscard]] glm::vec3 &Position() { return m_Position; }
        [[nodiscard]] glm::quat &Rotation() { return m_Rotation; }
        [[nodiscard]] glm::vec3 &Scale() { return m_Scale; }

        [[nodiscard]] glm::vec3 Forward() const { return m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f); }
        [[nodiscard]] glm::vec3 Right() const { return m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f); }
        [[nodiscard]] glm::vec3 Up() const { return m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f); }

        // Euler angles support
        Transform &SetRotation(const glm::vec3 &rotation);
        [[nodiscard]] glm::vec3 RotationEuler() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }

        Transform &Translate(const glm::vec3 &translation);

        Transform &Scale(const glm::vec3 &scale);
        Transform &Scale(f32 scale);

        Transform &Rotate(const glm::vec3 &rotation);
    };
}
