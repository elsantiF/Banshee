#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <imgui.h>
#include <Poltergeist/Poltergeist.hpp>
#include "ComponentBase.hpp"
#include "Transform.hpp"

namespace Banshee {
    class Camera final : public ComponentBase {
        f32 m_Fov{};
        f32 m_Aspect{};
        f32 m_Near{};
        f32 m_Far{};

        glm::mat4 m_ProjectionMatrix{};
        Ref<Transform> m_Transform{};

    public:
        Camera() = default;
        Camera(const f32 fov, const f32 near, const f32 far) : m_Fov{fov}, m_Near{near}, m_Far{far} {}

        [[nodiscard]] f32 &Fov() { return m_Fov; }

        // TODO: Add an m_ViewDirty flag to avoid recalculating the view matrix every frame
        [[nodiscard]] glm::mat4 GetViewMatrix() {
            PROFILE_SCOPE();
            return GetOwner()->GetComponent<class Transform>()->GetInverseModelMatrix();
        }

        // TODO: Add an m_ProjectionDirty flag to avoid recalculating the projection matrix every frame
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const {
            PROFILE_SCOPE();
            return glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
        }

        void SetAspect(const f32 aspect) { m_Aspect = aspect; }

        [[nodiscard]] String GetName() const override { return "Camera"; }
        void OnCreate() override { m_Transform = GetOwner()->GetComponent<Transform>(); }
        void OnTick(f64 delta) override {}
        void OnRender(Camera *camera) const override {} // This have a little to no sense lol
        void OnDestroy() override {}

        void OnImGui() override {
            ImGui::InputFloat("FOV", &m_Fov);
            ImGui::InputFloat("Near Plane", &m_Near);
            ImGui::InputFloat("Far Plane", &m_Far);
        }
    };
}
