#pragma once

#include <imgui.h>
#include <Poltergeist/Poltergeist.hpp>
#include "ComponentBase.hpp"

namespace Banshee {
    class Transform final : public ComponentBase {
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 m_Scale = glm::vec3(1.0f);

        glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
        glm::mat4 m_InverseModelMatrix = glm::identity<glm::mat4>();
        bool m_IsDirty = true;

    public:
        void UpdateMatrices();

        [[nodiscard]] String GetName() const override { return "Transform"; }
        void OnCreate() override {}
        void OnTick(f64 delta) override {}
        void OnRender(Camera *camera) const override {}
        void OnDestroy() override {}

        void OnImGui() override {
            auto position = GetPosition();
            if (ImGui::InputFloat3("Position", &position.x)) {
                SetPosition(position);
            }

            auto rotation = GetRotationEuler();
            if (ImGui::InputFloat3("Rotation", &rotation.x)) {
                SetRotation(rotation);
            }

            auto scale = GetScale();
            if (ImGui::InputFloat3("Scale", &scale.x)) {
                SetScale(scale);
            }
        }

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

        [[nodiscard]] glm::vec3 GetRotationEuler() const {
            // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
            // TODO: There is a little problem when a axis is near abs(pi/2), set one of the other axis to -0.0f
            //     Don't know if is my problem or glm problem, have to investigate. For now it's not a big deal.
            glm::vec3 angles{};
            const double test = m_Rotation.x * m_Rotation.y + m_Rotation.z * m_Rotation.w;

            if (test > 0.499) { // singularity at north pole
                angles.y = 2 * atan2(m_Rotation.x, m_Rotation.w);
                angles.x = std::numbers::pi / 2;
                angles.z = 0;
                return angles;
            }

            if (test < -0.499) { // singularity at south pole
                angles.y = -2 * atan2(m_Rotation.x, m_Rotation.w);
                angles.x = -std::numbers::pi / 2;
                angles.z = 0;
                return angles;
            }

            const f32 sqx = m_Rotation.x * m_Rotation.x;
            const f32 sqy = m_Rotation.y * m_Rotation.y;
            const f32 sqz = m_Rotation.z * m_Rotation.z;

            angles.y = atan2(2 * m_Rotation.y * m_Rotation.w - 2 * m_Rotation.x * m_Rotation.z, 1 - 2 * sqy - 2 * sqz);
            angles.x = asin(2 * test);
            angles.z = atan2(2 * m_Rotation.x * m_Rotation.w - 2 * m_Rotation.y * m_Rotation.z, 1 - 2 * sqx - 2 * sqz);
            return glm::degrees(angles);
        }

        Transform &Translate(const glm::vec3 &translation);

        Transform &Scale(const glm::vec3 &scale);
        Transform &Scale(f32 scale);

        Transform &Rotate(const glm::vec3 &rotation);
    };
}
