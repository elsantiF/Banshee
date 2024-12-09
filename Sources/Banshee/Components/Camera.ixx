module;
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <tracy/Tracy.hpp>

export module Banshee.Components.Camera;

import Poltergeist;
import Banshee.Components.Transform;

export namespace Banshee {
    class Camera {
        f32 m_Fov{};
        f32 m_Aspect{};
        f32 m_Near{};
        f32 m_Far{};

        glm::mat4 m_ProjectionMatrix{};

        Transform m_Transform{};

    public:
        Camera() = default;
        Camera(f32 fov, f32 aspect, f32 near, f32 far);
        void Update(f64 delta);

        [[nodiscard]] f32 GetFov() const { return m_Fov; }

        // TODO: Add an m_ViewDirty flag to avoid recalculating the view matrix every frame
        [[nodiscard]] glm::mat4 GetViewMatrix() {
            ZoneScoped;
            return glm::lookAt(m_Transform.Position(), m_Transform.Position() + m_Transform.Forward(), m_Transform.Up());
        }

        // TODO: Add an m_ProjectionDirty flag to avoid recalculating the projection matrix every frame
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const {
            ZoneScoped;
            return glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
        }

        [[nodiscard]] Transform &Transform() { return m_Transform; }
    };
}
