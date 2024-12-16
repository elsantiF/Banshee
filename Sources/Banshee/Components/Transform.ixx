module;
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

export module Banshee.Components.Transform;

import Poltergeist;
import Banshee.Components.Component;

export namespace Banshee {
    class Transform : public Component {
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 m_Scale = glm::vec3(1.0f);

        glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
        glm::mat4 m_InverseModelMatrix = glm::identity<glm::mat4>();
        bool m_IsDirty = true;

    public:
        void UpdateMatrices();

        [[nodiscard]] glm::mat4 GetModelMatrix();
        [[nodiscard]] glm::mat4 GetInverseModelMatrix();

        Transform &SetPosition(const glm::vec3 &position);
        Transform &SetRotation(const glm::quat &rotation);
        Transform &SetScale(const glm::vec3 &scale);

        [[nodiscard]] glm::vec3 GetPosition() const { return m_Position; }
        [[nodiscard]] glm::quat GetRotation() const { return m_Rotation; }
        [[nodiscard]] glm::vec3 GetScale() const { return m_Scale; }

        [[nodiscard]] glm::vec3 Forward() const { return glm::normalize(m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f)); }
        [[nodiscard]] glm::vec3 Right() const { return glm::normalize(m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f)); }
        [[nodiscard]] glm::vec3 Up() const { return glm::normalize(m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f)); }

        // Euler angles support
        Transform &SetRotation(const glm::vec3 &rotation);
        [[nodiscard]] glm::vec3 GetRotationEuler() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }

        Transform &Translate(const glm::vec3 &translation);

        Transform &Scale(const glm::vec3 &scale);
        Transform &Scale(f32 scale);

        Transform &Rotate(const glm::vec3 &rotation);
    };
}
