#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <Poltergeist/Poltergeist.hpp>
#include "Component.hpp"
#include "Transform.hpp"

namespace Banshee {
    class Camera : public Component {
        f32 m_Fov{};
        f32 m_Aspect{};
        f32 m_Near{};
        f32 m_Far{};

        glm::mat4 m_ProjectionMatrix{};

    public:
        Camera() = default;
        Camera(f32 fov, f32 aspect, f32 near, f32 far);

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
    };
}
