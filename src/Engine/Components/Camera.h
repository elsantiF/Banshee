#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/InputManager.h"
#include "Core/Window.h"

// TODO: Refactor this class to use Transform class
// TODO: Refactor this to remove m_Window
namespace BansheeEngine {
    class Camera {
        float m_Fov;
        float m_Aspect;
        float m_Near;
        float m_Far;

        glm::mat4 m_ProjectionMatrix{};

        glm::vec3 m_Position{};
        glm::vec3 m_Front{};
        glm::vec3 m_Up{};
        glm::vec3 m_Right{};
        glm::vec3 m_WorldUp{};

        float m_Yaw = 0.f;
        float m_Pitch = 0.f;

        void UpdateCameraVectors();

    public:
        Camera() = default;
        Camera(float fov, float aspect, float near, float far);
        void Update(double delta);

        float GetFov() const;
        void SetFov(float fov);

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
        [[nodiscard]] glm::vec3 GetCameraPosition() const;
    };
}
