#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Core.h"
#include "Core/InputManager.h"
#include "Core/Window.h"
#include "Transform.h"

namespace Banshee {
    class Camera {
        f32 m_Fov{};
        f32 m_Aspect{};
        f32 m_Near{};
        f32 m_Far{};

        glm::mat4 m_ProjectionMatrix{};

        Transform m_Transform;

        glm::vec3 m_Front{};
        glm::vec3 m_Up{};
        glm::vec3 m_Right{};
        glm::vec3 m_WorldUp{};

        void UpdateCameraVectors();

    public:
        Camera() = default;
        Camera(f32 fov, f32 aspect, f32 near, f32 far);
        void Update(f64 delta);

        [[nodiscard]] f32 GetFov() const;
        void SetFov(f32 fov);

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
        [[nodiscard]] Transform GetTransform() const;
    };
}
